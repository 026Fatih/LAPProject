#pragma once
#include "drawable.h"
class BezierCurve :
	public Drawable
{
public:
	BezierCurve(void);
	BezierCurve(int x1, int y1, int z1, int x2, int y2, int z2, int x3, int y3, int z3);

	virtual void draw();

	~BezierCurve(void);
};

