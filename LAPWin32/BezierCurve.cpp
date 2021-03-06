#include "StdAfx.h"
#include "BezierCurve.h"


BezierCurve::BezierCurve(void)
{
	cControlPoints = 0;
}

BezierCurve::BezierCurve(int x1, int y1, int z1, int x2, int y2, int z2, int x3, int y3, int z3)
{	
	this->cControlPoints = 3;

	this->controlPoints = new Point[3];

	this->controlPoints[0].x = (GLfloat) x1;
	this->controlPoints[0].y = (GLfloat) y1;
	this->controlPoints[0].z = (GLfloat) z1;

	this->controlPoints[1].x = (GLfloat) x2;
	this->controlPoints[1].y = (GLfloat) y2;
	this->controlPoints[1].z = (GLfloat) z2;

	this->controlPoints[2].x = (GLfloat) x3;
	this->controlPoints[2].y = (GLfloat) y3;
	this->controlPoints[2].z = (GLfloat) z3;

	for (int i = 0; i < this->cControlPoints; i++)
	{
		this->controlPointsArray[i][0] = this->controlPoints[i].x;
		this->controlPointsArray[i][1] = this->controlPoints[i].y;
		this->controlPointsArray[i][2] = this->controlPoints[i].z;
	}
}

void BezierCurve::draw()
{
	glPushMatrix();
	glRotatef(this->xRot, 1.0f, 0.0f, 0.0f);
	glRotatef(this->yRot, 0.0f, 1.0f, 0.0f);	
	glRotatef(this->zRot, 0.0f, 0.0f, 1.0f);

	glMap1f(GL_MAP1_VERTEX_3,	// Type of data generated
		0.0f,						// Lower u range
		100.0f,						// Upper u range
		3,							// Distance between points in the data
		this->cControlPoints,					// number of control points
		&(this->controlPointsArray)[0][0]);			// array of control points

	// Enable the evaluator
	glEnable(GL_MAP1_VERTEX_3);

	// Map a grid of 100 points from 0 to 100
	glMapGrid1d(100,0.0,100.0);

	// Evaluate the grid, using lines
	glEvalMesh1(GL_LINE,0,100);

	glPopMatrix();
}

BezierCurve::~BezierCurve(void)
{
	if (cControlPoints != 0)
		delete[] controlPoints;
}
