#include "StdAfx.h"
#include "Cylinder.h"


Cylinder::Cylinder(void)
{
}
Cylinder::Cylinder(GLfloat r, GLfloat h)
{
	this->radius=r;
	this->height=h;
}

void Cylinder::draw()
{
	GLfloat x              = 0.0;
	GLfloat y              = 0.0;
	GLfloat angle          = 0.0;
	GLfloat angle_stepsize = 0.1f;
	GLfloat	fSizes[2];			// Line width range metrics

	glGetFloatv(GL_LINE_WIDTH_RANGE,fSizes);
	glLineWidth(fSizes[0]);

	glPushMatrix();
	glRotatef(this->xRot, 1.0f, 0.0f, 0.0f);
	glRotatef(this->yRot, 0.0f, 1.0f, 0.0f);	
	glRotatef(this->zRot, 0.0f, 0.0f, 1.0f);

	/** Draw the tube */
	glBegin(GL_LINE_STRIP);
	angle = 0.0;
	while(angle < (2 * PI))
	{
		x = radius * cos(angle);
		y = radius * sin(angle);
		glVertex3f(x, y , height);
		glVertex3f(x, y , 0.0);
		angle = angle + angle_stepsize;
	}
	glVertex3f(radius, 0.0, height);
	glVertex3f(radius, 0.0, 0.0);
	glEnd();

	/** Draw the circle on top of cylinder */
	glBegin(GL_LINE_STRIP);
	angle = 0.0;
	while( angle < 2*PI ) {
		x = radius * cos(angle);
		y = radius * sin(angle);
		glVertex3f(x, y , height);
		angle = angle + angle_stepsize;
	}
	glVertex3f(radius, 0.0, height);
	glEnd();

	/** Draw the circle on bottom of cylinder */
	glBegin(GL_LINE_STRIP);
	angle = 0.0;
	while( angle < 2*PI ) {
		x = radius * cos(angle);
		y = radius * sin(angle);
		glVertex3f(x, y , 0.0);
		angle = angle + angle_stepsize;
	}
	glVertex3f(radius, 0.0, 0.0);
	glEnd();

	glPopMatrix();
}

Cylinder::~Cylinder(void)
{
}
