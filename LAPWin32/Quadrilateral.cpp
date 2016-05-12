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
	lines[2] = new Line(x3, y3, z3, x4, y4, z4);
	lines[3] = new Line(x4, y4, z4, x1, y1, z1);

	this->meshVector = this->mesh();
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

	for (this->meshIterator= this->meshVector.begin();
		this->meshIterator != this->meshVector.end();
		(this->meshIterator)++)
	{
		(*this->meshIterator)->xRot = this->xRot;
		(*this->meshIterator)->yRot = this->yRot;
		(*this->meshIterator)->zRot = this->zRot;
		(*this->meshIterator)->setLineWidthMin();
		(*this->meshIterator)->draw();
	}
}

Quadrilateral::~Quadrilateral(void)
{
	for (int i = 0; i < 4; i++)
		delete lines[i];
}

std::vector<Line*> Quadrilateral::mesh()
{
	std::vector<Line*> meshLines;

	GLfloat distX0 = lines[0]->startPoint.x-lines[0]->endPoint.x;
	GLfloat distY0 = lines[0]->startPoint.y-lines[0]->endPoint.y;
	GLfloat distZ0 = lines[0]->startPoint.z-lines[0]->endPoint.z;

	GLfloat distX2 = lines[2]->startPoint.x-lines[2]->endPoint.x;
	GLfloat distY2 = lines[2]->startPoint.y-lines[2]->endPoint.y;
	GLfloat distZ2 = lines[2]->startPoint.z-lines[2]->endPoint.z;

	GLfloat distX1 = lines[1]->startPoint.x-lines[1]->endPoint.x;
	GLfloat distY1 = lines[1]->startPoint.y-lines[1]->endPoint.y;
	GLfloat distZ1 = lines[1]->startPoint.z-lines[1]->endPoint.z;

	GLfloat distX3 = lines[3]->startPoint.x-lines[3]->endPoint.x;
	GLfloat distY3 = lines[3]->startPoint.y-lines[3]->endPoint.y;
	GLfloat distZ3 = lines[3]->startPoint.z-lines[3]->endPoint.z;

	for(int i = 1; i < 11; i++)
	{
		GLfloat tempX=lines[0]->startPoint.x + -distX0/10*i;
		GLfloat tempY=lines[0]->startPoint.y + -distY0/10*i;
		GLfloat tempZ=lines[0]->startPoint.z + -distZ0/10*i;


		GLfloat tempX2=lines[2]->endPoint.x - -distX2/10*i;
		GLfloat tempY2=lines[2]->endPoint.y - -distY2/10*i;
		GLfloat tempZ2=lines[2]->endPoint.z - -distZ2/10*i;

		meshLines.push_back(new Line(tempX,tempY,tempZ,tempX2,tempY2,tempZ2));

		GLfloat tempX1=lines[1]->startPoint.x + -distX1/10*i;
		GLfloat tempY1=lines[1]->startPoint.y + -distY1/10*i;
		GLfloat tempZ1=lines[1]->startPoint.z + -distZ1/10*i;


		GLfloat tempX3=lines[3]->endPoint.x - -distX3/10*i;
		GLfloat tempY3=lines[3]->endPoint.y - -distY3/10*i;
		GLfloat tempZ3=lines[3]->endPoint.z - -distZ3/10*i;

		meshLines.push_back(new Line(tempX1,tempY1,tempZ1,tempX3,tempY3,tempZ3));
	}
	return meshLines;
}
