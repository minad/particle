#include <stdio.h>
#include <stdlib.h>
#include "SDL.h"
#include "SDL_opengl.h"
#include "Matrix.h"
#include "Vector.h"

struct GLDriver {
#define GL_PROC(ret, name, args)\
ret (*name)args;
#include "GLFuncs.h"
#undef GL_PROC
};

enum {
	SCREEN_WIDTH = 640,
	SCREEN_HEIGHT = 480,
	SCREEN_BPP = 32,
	NUM_PARTICLES = 2000,
};

struct Particle {
	Vector pos, velocity;
	float size;
	float mass;
	float color[4];
	float liveTime;
};

SDL_Surface *surface;
GLDriver glDriver;
GLDriver* driver = &glDriver;
GLuint texture;
Vector gravityCenter(0, 0, 0);

Particle particle[NUM_PARTICLES];

void
quit (int exitCode)
{
	driver->glDeleteTextures (1, &texture);
	SDL_Quit ();
	exit (exitCode);
}

int
loadTextures ()
{
	SDL_Surface * image;
	if (!(image = SDL_LoadBMP ("particle.bmp")))
		return false;

	driver->glGenTextures (1, &texture);
	driver->glBindTexture (GL_TEXTURE_2D, texture);

	driver->glTexImage2D (GL_TEXTURE_2D, 0, 3, image->w,
			      image->h, 0, GL_BGR, GL_UNSIGNED_BYTE,
			      image->pixels);

	driver->glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
				 GL_LINEAR);
	driver->glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
				 GL_LINEAR);

	SDL_FreeSurface (image);

	return true;
}

void
resizeWindow (int width, int height)
{
	if (height == 0)
		height = 1;
	driver->glViewport (0, 0, width, height);
	driver->glMatrixMode(GL_PROJECTION);

	driver->glLoadMatrixf(perspectiveMatrix
			      (45.0f, (float) width / height, 0.1f,
			       200.0f));

	driver->glMatrixMode(GL_MODELVIEW);
	driver->glLoadIdentity ();
}

void
handleKeyPress (SDL_keysym * keysym)
{
	switch (keysym->sym) {
	case SDLK_ESCAPE:
		quit (0);
		break;

	case SDLK_F1:
		SDL_WM_ToggleFullScreen (surface);
		break;
	}
}

bool initGLDriver() {
#define GL_PROC(ret, name, args)\
	driver->name = (ret (*)args)SDL_GL_GetProcAddress(#name);
#include "GLFuncs.h"
#undef GL_PROC
}

void initParticle(int i) {
	particle[i].pos = Vector(0, 0, 0);
	particle[i].size = (rand() % 10) / 10.f;
	particle[i].mass = (rand() % 10) / 10.f;
	particle[i].velocity = Vector((rand() % 10) / 10.f - .5f, (rand() % 10) / 10.f - .5f, (rand() % 10) / 10.f - .5f).normalize() * (rand() % 100) / 10.f;
	particle[i].color[0] = (rand() % 10) / 100.f + .9f;
	particle[i].color[1] = (rand() % 100) / 100.f;
	particle[i].color[2] = 0;
	particle[i].color[3] = (rand() % 100) / 100.f;
	particle[i].liveTime = (rand() % 100) / 40.f;
}

bool
initGL ()
{
	if (!initGLDriver())
		return false;

	if (!loadTextures ())
		return false;

	driver->glShadeModel (GL_SMOOTH);
	driver->glClearColor (0, 0, 0, 0);
	driver->glClearDepth (1);
	driver->glDisable (GL_DEPTH_TEST);
	driver->glEnable (GL_BLEND);
	driver->glBlendFunc (GL_SRC_ALPHA, GL_ONE);
	driver->glHint (GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	driver->glHint (GL_POINT_SMOOTH_HINT, GL_NICEST);
	driver->glEnable (GL_TEXTURE_2D);
	driver->glBindTexture (GL_TEXTURE_2D, texture);

	for (int i = 0; i < NUM_PARTICLES; ++i)
		initParticle(i);

	return true;
}

void
drawScene (float frameTime)
{
	static float rot = 0;

	driver->glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	driver->glLoadIdentity();

	Matrix transform = rotationMatrix(rot += .01, 0, 1, 1).translate(0, 0, -30);
	
	for (int i = 0; i < NUM_PARTICLES; ++i) {
		if (particle[i].liveTime > 0) {
		    Vector pos = particle[i].pos * transform;

		    driver->glColor4fv(particle[i].color);
		    driver->glBegin(GL_TRIANGLE_STRIP);
		      // Top Right
		      driver->glTexCoord2f(1, 1);
		      driver->glVertex3f(pos[0] + particle[i].size, pos[1] + particle[i].size, pos[2] );
		      // Top Left
		      driver->glTexCoord2f(0, 1);
		      driver->glVertex3f(pos[0] - particle[i].size, pos[1] + particle[i].size, pos[2] );
		      // Bottom Right
		      driver->glTexCoord2f(1, 0);
		      driver->glVertex3f(pos[0] + particle[i].size, pos[1] - particle[i].size, pos[2] );
		      // Bottom Left
		      driver->glTexCoord2f(0, 0);
		      driver->glVertex3f(pos[0] - particle[i].size, pos[1] - particle[i].size, pos[2] );
		    driver->glEnd( );

			particle[i].pos += frameTime * particle[i].velocity;
			particle[i].velocity += frameTime * particle[i].mass * (gravityCenter - particle[i].pos);
			particle[i].color[3] -= frameTime * particle[i].color[3] / particle[i].liveTime;
			particle[i].liveTime -= frameTime;
		}

		if (particle[i].liveTime < 0)
			initParticle(i);
	}

	SDL_GL_SwapBuffers ();
}

int
main (int argc, char *argv[])
{
	if (SDL_Init (SDL_INIT_VIDEO) < 0) {
		fprintf (stderr, "Video initialization failed: %s\n",
			 SDL_GetError ());
		quit (1);
	}

	const SDL_VideoInfo *
		videoInfo = SDL_GetVideoInfo ();

	if (!videoInfo) {
		fprintf (stderr, "Video query failed: %s\n", SDL_GetError ());
		quit (1);
	}

	int
	  videoFlags = SDL_OPENGL | SDL_GL_DOUBLEBUFFER | SDL_RESIZABLE;
	if (videoInfo->hw_available)
		videoFlags |= SDL_HWSURFACE;
	else
		videoFlags |= SDL_SWSURFACE;

	if (videoInfo->blit_hw)
		videoFlags |= SDL_HWACCEL;

	SDL_GL_SetAttribute (SDL_GL_DOUBLEBUFFER, 1);

	SDL_WM_SetCaption("Particle", NULL);

	surface = SDL_SetVideoMode (SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP,
				   videoFlags);

	if (!surface) {
		fprintf (stderr, "Video mode set failed: %s\n",
			 SDL_GetError ());
		quit (1);
	}

	if ((SDL_EnableKeyRepeat (100, SDL_DEFAULT_REPEAT_INTERVAL))) {
		fprintf (stderr, "Setting keyboard repeat failed: %s\n",
			 SDL_GetError ());
		quit (1);
	}

	if (!initGL ()) {
		fprintf (stderr, "Could not initialize OpenGL.\n");
		quit (1);
	}

	resizeWindow (SCREEN_WIDTH, SCREEN_HEIGHT);

	bool done = false, active = true;
	int lastTime = SDL_GetTicks(), frames = 0, lastFrameTime = SDL_GetTicks();
	while (!done) {
		/* handle the events in the queue */
		SDL_Event event;
		while (SDL_PollEvent (&event)) {
			switch (event.type) {
			case SDL_ACTIVEEVENT:
				if (event.active.gain == 0)
					active = false;
				else {
					active = true;
					 lastTime = SDL_GetTicks();
				}
				break;

			case SDL_VIDEORESIZE:
				surface = SDL_SetVideoMode (event.resize.w,
							    event.resize.h,
							    SCREEN_BPP,
							    videoFlags);
				if (!surface) {
					fprintf (stderr,
						 "Could not get a surface after resize: %s\n",
						 SDL_GetError ());
					quit (1);
				}
				resizeWindow (event.resize.w, event.resize.h);
				break;

			case SDL_KEYDOWN:
				handleKeyPress (&event.key.keysym);
				break;

			case SDL_QUIT:
				done = true;
				break;
			}
		}

		if (active) {
			int time =  SDL_GetTicks();

			if (++frames % 100 == 99) {
				printf("%.2f FPS\n", 1000.f * frames / (time - lastFrameTime));
				lastFrameTime = time;
				frames = 0;
			}

			drawScene ((time - lastTime) * .001f);
			lastTime = time;
		}
	}

	quit (0);
	return 0;
}
