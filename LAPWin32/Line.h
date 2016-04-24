#pragma once
#include "drawable.h"
#include "Point.h"

class Line :
	public Drawable
{
private:
	Point startPoint, endPoint;
public:
	Line(void);
	Line(int xS, int yS, int zS, int xE, int yE, int zE);
	virtual void draw();

	~Line(void);
};

