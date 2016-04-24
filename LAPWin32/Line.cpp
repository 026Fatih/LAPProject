#include "StdAfx.h"
#include "Line.h"


Line::Line(void)
{
}

Line::Line(int xS, int yS, int zS, int xE, int yE, int zE)
{
	this->startPoint.x = xS;
	this->startPoint.y = yS;
	this->startPoint.z = zS;
	this->endPoint.x = xE;
	this->endPoint.x = yE;
	this->endPoint.x = zE;
}

Line::~Line(void)
{
}

void Line::draw()
{

}
