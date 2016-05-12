#pragma once
#include "drawable.h"
#include "Point.h"

class Line :
	public Drawable
{
private:
	GLfloat width;
public:	
	Point startPoint, endPoint;

	Line(void);
	Line(int xS, int yS, int zS, int xE, int yE, int zE);
	Line(GLfloat xS, GLfloat yS, GLfloat zS, GLfloat xE, GLfloat yE, GLfloat zE);

	virtual void draw();
	void setLineWidthMin();
	void setLineWidthMid();
	void setLineWidthMax();
	~Line(void);
};

