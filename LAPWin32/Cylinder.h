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
	virtual void draw();
};
