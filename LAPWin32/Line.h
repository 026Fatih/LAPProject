#pragma once
#include "drawable.h"
class Line :
	public Drawable
{
public:
	Line(void);

	virtual void draw();

	~Line(void);
};

