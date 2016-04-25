#pragma once
#include "drawable.h"
#include "Line.h"

class Quadrilateral :
	public Drawable
{
private:
	Line* lines[4];
public:
	Quadrilateral(void);
	Quadrilateral(int x1, int y1, int z1, int x2, int y2, int z2, int x3, int y3, int z3, int x4, int y4, int z4);
	
	virtual void draw();

	~Quadrilateral(void);
};
