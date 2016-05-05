#pragma once
#include "Drawable.h"
#include "Point.h"

class BezierCurve :
	public Drawable
{
private:
	int cControlPoints;
	Point startingPoint, endPoint;
	Point* controlPoints;
	GLfloat controlPointsArray[3][3];
public:
	BezierCurve(void);
	BezierCurve(int x1, int y1, int z1, int x2, int y2, int z2, int x3, int y3, int z3);
	~BezierCurve(void);

	virtual void draw();
};
