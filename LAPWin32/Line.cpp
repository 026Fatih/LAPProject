#include "StdAfx.h"
#include "Line.h"


Line::Line(void)
{
	width = 0;
}

Line::Line(int xS, int yS, int zS, int xE, int yE, int zE)
{
	this->startPoint.x = xS;
	this->startPoint.y = yS;
	this->startPoint.z = zS;
	this->endPoint.x = xE;
	this->endPoint.y = yE;
	this->endPoint.z = zE;

	this->xRot = this->yRot = this->zRot = 0;
}

Line::Line(GLfloat xS, GLfloat yS, GLfloat zS, GLfloat xE, GLfloat yE, GLfloat zE)
{
	this->startPoint.x = xS;
	this->startPoint.y = yS;
	this->startPoint.z = zS;
	this->endPoint.x = xE;
	this->endPoint.y = yE;
	this->endPoint.z = zE;

	this->xRot = this->yRot = this->zRot = 0;
}

Line::~Line(void)
{
}

void Line::setLineWidthMin()
{
	GLfloat	fSizes[2];			// Line width range metrics

	glGetFloatv(GL_LINE_WIDTH_RANGE,fSizes);
	this->width = fSizes[0];
}

void Line::setLineWidthMid()
{
	GLfloat	fSizes[2];			// Line width range metrics

	glGetFloatv(GL_LINE_WIDTH_RANGE,fSizes);
	this->width = (fSizes[0] + fSizes[1]) / 2;
}

void Line::setLineWidthMax()
{
	GLfloat	fSizes[2];			// Line width range metrics

	glGetFloatv(GL_LINE_WIDTH_RANGE,fSizes);
	this->width = fSizes[1];
}

void Line::draw()
{
	glPushMatrix();
	glRotatef(this->xRot, 1.0f, 0.0f, 0.0f);
	glRotatef(this->yRot, 0.0f, 1.0f, 0.0f);
	glRotatef(this->zRot, 0.0f, 0.0f, 1.0f);

	if (this->width != 0)
		glLineWidth(this->width);

	glBegin(GL_LINES);
	glVertex3f(startPoint.x, startPoint.y, startPoint.z);
	glVertex3f(endPoint.x, endPoint.y, endPoint.z);
	glEnd();
	glPopMatrix();
}
