CC = g++ -O2

all:
	$(CC) *.cpp -o particle -lGLU `sdl-config --cflags --libs`

clean:
	@echo Cleaning up...
	@rm lesson19
	@echo Done.
