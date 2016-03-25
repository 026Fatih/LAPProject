#include "StdAfx.h"
#include "Triangle.h"

Triangle::Triangle(void)
{
	TriangleBorderColorR = 1;
	TriangleSurfaceColorG = 1;
}

Triangle::~Triangle(void)
{
}

void Triangle::draw(void)
{
	glBegin(GL_TRIANGLES);
	glColor3f(TriangleSurfaceColorR, TriangleSurfaceColorG, TriangleSurfaceColorB);
	glVertex3f(p1.x, p1.y, p1.z);
	glVertex3f(p2.x, p2.y, p2.z);
	glVertex3f(p3.x, p3.y, p3.z);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glColor3f(TriangleBorderColorR, TriangleBorderColorG, TriangleBorderColorB);
	glVertex3f(p1.x, p1.y, p1.z);
	glVertex3f(p2.x, p2.y, p2.z);
	glVertex3f(p3.x, p3.y, p3.z);
	glEnd();
}

void Triangle::draw(GLfloat rBorder, GLfloat gBorder, GLfloat bBorder,
					GLfloat rSurface, GLfloat  gSurface, GLfloat  bSurface)
{
	glBegin(GL_TRIANGLES);
	glColor3f(rSurface, gSurface, bSurface);
	glVertex3f(p1.x, p1.y, p1.z);
	glVertex3f(p2.x, p2.y, p2.z);
	glVertex3f(p3.x, p3.y, p3.z);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glColor3f(rBorder, gBorder, bBorder);
	glVertex3f(p1.x, p1.y, p1.z);
	glVertex3f(p2.x, p2.y, p2.z);
	glVertex3f(p3.x, p3.y, p3.z);
	glEnd();
}
