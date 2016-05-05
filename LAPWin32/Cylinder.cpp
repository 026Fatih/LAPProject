#include "StdAfx.h"
#include "Cylinder.h"


Cylinder::Cylinder(void)
{
}
Cylinder::Cylinder(GLfloat r,
	GLfloat h,
	GLubyte R,//bunlarý çýkarýyýmmý
	GLubyte G,
	GLubyte B){
		radius=r;
		height=h;}

void Cylinder::draw()
{
	GLfloat x              = 0.0;
	GLfloat y              = 0.0;
	GLfloat angle          = 0.0;
	GLfloat angle_stepsize = 0.1;

	/** Draw the tube */
	glColor3ub(R-40,G-40,B-40);//BUNADA 
	glBegin(GL_QUAD_STRIP);
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
	glColor3ub(R,G,B);// buna gerek vARMI

	glBegin(GL_POLYGON);
	angle = 0.0;
	while( angle < 2*PI ) {
		x = radius * cos(angle);
		y = radius * sin(angle);
		glVertex3f(x, y , height);
		angle = angle + angle_stepsize;
	}
	glVertex3f(radius, 0.0, height);
	glEnd();
}

Cylinder::~Cylinder(void)
{
}
