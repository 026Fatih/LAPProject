#pragma once
#include "drawable.h"
class Surface :
	public Drawable
{
public:
	Surface(void);
	~Surface(void);
	
	virtual void draw(){
		glPushMatrix();
	 glRotatef(85.0, 1.0, 1.0, 1.0);
   glEvalMesh2(GL_FILL, 0, 20, 0, 20);
   glPopMatrix();
	}


};

