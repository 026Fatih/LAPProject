#include "StdAfx.h"
#include "Surface.h"

Surface::Surface(void)
{
	
	glEnable(GL_AUTO_NORMAL);

}

Surface::~Surface(void)
{
}

void Surface::draw()
{
	GLfloat ctrlPoints[4][4][3] = 
	{
		{
			{-1.5, -1.5, 4.0},
			{-0.5, -1.5, 2.0},
			{0.5, -1.5, -1.0},
			{1.5, -1.5, 2.0}
		},
		{
			{-1.5, -0.5, 1.0},
			{-0.5, -0.5, 3.0},
			{0.5, -0.5, 0.0},
			{1.5, -0.5, -1.0}
		},
		{
			{-1.5, 0.5, 4.0},
			{-0.5, 0.5, 0.0},
			{0.5, 0.5, 3.0},
			{1.5, 0.5, 4.0}
		},
		{
			{-1.5, 1.5, -2.0},
			{-0.5, 1.5, -2.0},
			{0.5, 1.5, 0.0},
			{1.5, 1.5, -1.0}
		}
	};

	glPushMatrix();
	glRotatef(this->xRot, 1.0f, 0.0f, 0.0f);
	glRotatef(this->yRot, 0.0f, 1.0f, 0.0f);	
	glRotatef(this->zRot, 0.0f, 0.0f, 1.0f);
	glMap2f(GL_MAP2_VERTEX_3,	// Type of data generated
	0.0f,						// Lower u range
	10.0f,						// Upper u range
	3,							// Distance between points in the data
	4,							// Dimension in u direction (order)
	0.0f,						// Lover v range
	10.0f,						// Upper v range
	9,							// Distance between points in the data
	3,							// Dimension in v direction (order)
	&ctrlPoints[0][0][0]);		// array of control points
	
	glEnable(GL_MAP2_VERTEX_3);
	glMapGrid2f(10,0.0f,10.0f,10,0.0f,10.0f);
	glEvalMesh2(GL_LINE, 0, 10, 0, 10);
	glPopMatrix();
}
