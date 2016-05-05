#pragma once
#include "drawable.h"
class Cylinder :
	public Drawable
{
public:
	GLfloat radius,height;
	Cylinder(void);
	Cylinder(GLfloat r,
		GLfloat h,
		GLubyte R,// þunlar renlermi
		GLubyte G,
		GLubyte B);
	~Cylinder(void);
	virtual void draw(){

		GLfloat x              = 0.0;
		GLfloat y              = 0.0;
		GLfloat angle          = 0.0;
		GLfloat angle_stepsize = 0.1;

		/** Draw the tube */
		glColor3ub(R-40,G-40,B-40);//BUNADA 
		glBegin(GL_QUAD_STRIP);
		angle = 0.0;
		while( angle < 2*PI ) {
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

	{
		glClear(GL_COLOR_BUFFER_BIT);
		glLoadIdentity();

		glTranslatef(0.0,-0.4,-3.0);
		glRotatef(-40, 1.0, 0.0, 0.0);

		draw_cylinder(0.3, 1.0, 255, 160, 100);

		glFlush();
	}
}
};

