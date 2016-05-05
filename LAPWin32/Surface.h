#pragma once
#include "drawable.h"
class Surface :
	public Drawable
{
public:
	Surface(void);
	~Surface(void);
	
	virtual void draw();


};

