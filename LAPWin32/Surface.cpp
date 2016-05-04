#include "StdAfx.h"
#include "Surface.h"


Surface::Surface(void)
{
	GLfloat ctrlpoints[4][4][3] = {
		{ {-1.5, -1.5, 4.0},
		{-0.5, -1.5, 2.0},
		{0.5, -1.5, -1.0},
		{1.5, -1.5, 2.0}},
		{ {-1.5, -0.5, 1.0},
		{-0.5, -0.5, 3.0},
		{0.5, -0.5, 0.0},
		{1.5, -0.5, -1.0}},
		{ {-1.5, 0.5, 4.0},
		{-0.5, 0.5, 0.0},
		{0.5, 0.5, 3.0},
		{1.5, 0.5, 4.0}},
		{ {-1.5, 1.5, -2.0},
		{-0.5, 1.5, -2.0},
		{0.5, 1.5, 0.0},
		{1.5, 1.5, -1.0}}
	};
  
   glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4,
           0, 1, 12, 4, &ctrlpoints[0][0][0]);
   glEnable(GL_MAP2_VERTEX_3);
   glEnable(GL_AUTO_NORMAL);
   glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);
          
}


Surface::~Surface(void)
{
}
