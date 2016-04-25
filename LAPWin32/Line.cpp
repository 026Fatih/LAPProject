#include "StdAfx.h"
#include "Line.h"


Line::Line(void)
{
}

Line::Line(int xS, int yS, int zS, int xE, int yE, int zE)
{
	this->startPoint.x = xS;
	this->startPoint.y = yS;
	this->startPoint.z = zS;
	this->endPoint.x = xE;
	this->endPoint.y = yE;
	this->endPoint.z = zE;
}

Line::~Line(void)
{
}

void Line::draw()
{
	glPushMatrix();
	glRotatef(this->xRot, 1.0f, 0.0f, 0.0f);
	glRotatef(this->yRot, 0.0f, 1.0f, 0.0f);	
	glRotatef(this->zRot, 0.0f, 0.0f, 1.0f);
	glBegin(GL_LINES);
	glVertex3f(startPoint.x, startPoint.y, startPoint.z);
	glVertex3f(endPoint.x, endPoint.y, endPoint.z);
	glEnd();
	glPopMatrix();
}
