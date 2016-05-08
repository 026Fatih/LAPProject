#pragma once
#include "drawable.h"

class Cylinder :
	public Drawable
{
public:
	GLfloat
		radius,
		height,
		R,
		G,
		B;
	Cylinder(void);
	Cylinder(GLfloat r, GLfloat h);
	~Cylinder(void);

	virtual void draw();
};
