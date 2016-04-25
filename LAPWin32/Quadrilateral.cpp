#include "StdAfx.h"
#include "Quadrilateral.h"


Quadrilateral::Quadrilateral(void)
{
}

Quadrilateral::Quadrilateral(int x1, int y1, int z1, int x2, int y2, int z2,
	int x3, int y3, int z3, int x4, int y4, int z4)
{
	lines[0] = new Line(x1, y1, z1, x2, y2, z2);
	lines[1] = new Line(x2, y2, z2, x3, y3, z3);
	lines[2] = new Line(x3, y3, z3, z4, y4, z4);
	lines[3] = new Line(x4, y4, z4, x1, y1, z1);
}

void Quadrilateral::draw()
{
	for (int i = 0; i < 4; i++)
	{
		lines[i]->xRot = this->xRot;
		lines[i]->yRot = this->yRot;
		lines[i]->zRot = this->zRot;
		lines[i]->draw();
	}
}

Quadrilateral::~Quadrilateral(void)
{
	for (int i = 0; i < 4; i++)
		delete lines[i];
}
