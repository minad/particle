#ifndef _BSP_H
#define _BSP_H

class BSPTree {
private:

	BSPTree*  negative;
	BSPTree*  positive;
	BSPTree*  parent;
	int       numTriangles;
	Triangle* triangles;
	Plane     plane;

public:

	struct Triangle {
		Vector a, b, c;

		Triangle(const Vector& a, const Vector& b, const Vector& c)
			: a(a), b(b), c(c) {}
	};

	typedef List<Triangle*>        TriangleList;
	typedef TriangleList::Iterator TriangleIterator;

	BSPTree(const TriangleList& triangles) {
		construct(triangles, numTriangles);
	}

	void construct(const TriangleList& triangles, int numPolys) {
		TriangleList negative, positive, coincident;
		Triangle* t = triangles.popFirst();
		plane = Plane(t->a, t->b, t->c);
		for (TriangleIterator i = triangles.begin(); i; ++i) {
		}
	}
};

#endf