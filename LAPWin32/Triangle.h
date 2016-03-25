#pragma once
#include "Point.h"

#define MAXTRIANGLE		1300

class Triangle
{
public:
	GLfloat TriangleSurfaceColorR, TriangleSurfaceColorG, TriangleSurfaceColorB,
		TriangleBorderColorR, TriangleBorderColorG, TriangleBorderColorB;
	Point p1, p2, p3;

	Triangle(void);
	~Triangle(void);
	void draw(void);
	void draw(GLfloat rBorder, GLfloat gBorder, GLfloat bBorder,
		GLfloat rSurface, GLfloat  gSurface, GLfloat  bSurface);
};
