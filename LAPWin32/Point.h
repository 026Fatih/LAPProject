#pragma once
#include "StdAfx.h"

class Point
{
public:
	GLfloat x, y, z;
	
	Point(void);
	Point(GLfloat x,GLfloat y,GLfloat z);
	~Point(void);
};
