#include "StdAfx.h"
#include "STLFile.h"

STLFile::STLFile(void)
{
	this->bOpened = FALSE;
	this->bShow = TRUE;
	this->cTriangles = 0;
	this->xRot = this->yRot = 0;
	this->setSurfaceColor(RGB(0, 255, 0));
	this->setBorderColor(RGB(255, 0, 0));
	this->bLockRotation = FALSE;
	this->triangles = new Triangle[MAXTRIANGLE];
}

STLFile::STLFile(const TCHAR szSTLFilePath[], int *maxX, int *maxY, int *maxZ)
{

}

STLFile::~STLFile(void)
{
	delete[] this->triangles;
}

void STLFile::draw(void)
{
	int	i;

	// Save matrix state and do the rotation
	glPushMatrix();
	glRotatef(this->xRot, 1.0f, 0.0f, 0.0f);
	glRotatef(this->yRot, 0.0f, 1.0f, 0.0f);	

	for (i = 0; i < this->cTriangles; i++)
	{
		this->triangles[i].draw(this->rBorder, this->gBorder, this->bBorder,
			this->rSurface, this->gSurface, this->bSurface);
	}	

	// Restore transformations
	glPopMatrix();
}
void STLFile::draw(GLfloat rBorder, GLfloat gBorder, GLfloat bBorder,
				   GLfloat rSurface, GLfloat  gSurface, GLfloat  bSurface)
{
	int	i;
	for (i = 0; i < this->cTriangles; i++)
	{
		this->triangles[i].draw(rBorder, gBorder, bBorder,
			rSurface, gSurface, bSurface);
	}
}

int STLFile::GetTriangleCountFromSTLFile()
{
	char szLine[MAXLINE], *pTemp;
	std::ifstream	fileSTL;	
	int cTriangle = 0;
	
	if (!this->bOpened)
	return -1;	

	fileSTL.open(this->ofn.lpstrFile);
	fileSTL.getline(szLine, MAXLINE);
	while(!fileSTL.eof())
	{
		pTemp = strstr(szLine, "vertex");
		if (pTemp != NULL)
		{
			fileSTL.getline(szLine, MAXLINE);
			pTemp = strstr(szLine, "vertex");
			if (pTemp != NULL)
			{
				fileSTL.getline(szLine, MAXLINE);
				pTemp = strstr(szLine, "vertex");
				if (pTemp != NULL)
				{
					cTriangle++;
				}
			}
		}
		fileSTL.getline(szLine, MAXLINE);
	}
	fileSTL.close();
	return cTriangle;
}

void STLFile::incrementXRot(GLfloat amount)
{	
	if (!this->bLockRotation)
		this->xRot += amount;
	this->xRot = (GLfloat)((const int)this->xRot % 360);
}
void STLFile::incrementYRot(GLfloat amount)
{
	if (!this->bLockRotation)
		this->yRot += amount;	
	this->yRot = (GLfloat)((const int)this->yRot % 360);
}

BOOL STLFile::Locked()
{
	return this->bLockRotation;
}

void STLFile::LockRotation(BOOL bLock)
{
	this->bLockRotation = bLock;
}


void STLFile::Merge(STLFile *s, int iMergePos)
{
	//Triangle *resultTriangles = new Triangle[this->cTriangles + s->cTriangles];
	Point pxbiggest= s->GetBiggestXVertex();
	Point pxsmallest  = this->GetSmallestXVertex();
	s->AlterPositionX(pxsmallest.x - pxbiggest.x);
	if (pxsmallest.y < pxbiggest.y)
		s->AlterPositionY(pxsmallest.y - pxbiggest.y);
	else
		s->AlterPositionY(pxbiggest.y - pxsmallest.y);
	if (pxsmallest.z < pxbiggest.z)
		s->AlterPositionZ(pxsmallest.z - pxbiggest.z);
	else
		s->AlterPositionZ(pxbiggest.z - pxsmallest.z);

}

Point STLFile::GetBiggestXVertex()
{
	int		i;
	Point	resultPoint(-FLT_MAX, 0, 0);
	
	for (i = 0; i < this->cTriangles; i++)
	{
		if (this->triangles[i].p1.x > resultPoint.x)
			resultPoint = this->triangles[i].p1;
		if (this->triangles[i].p2.x > resultPoint.x)
			resultPoint = this->triangles[i].p2;
		if (this->triangles[i].p3.x > resultPoint.x)
			resultPoint = this->triangles[i].p3;
	}
	return resultPoint;
}

Point STLFile::GetSmallestXVertex()
{
	int		i;
	Point	resultPoint(FLT_MAX, 0, 0);
	
	for (i = 0; i < this->cTriangles; i++)
	{
		if (this->triangles[i].p1.x < resultPoint.x)
			resultPoint = this->triangles[i].p1;
		if (this->triangles[i].p2.x < resultPoint.x)
			resultPoint = this->triangles[i].p2;
		if (this->triangles[i].p3.x < resultPoint.x)
			resultPoint = this->triangles[i].p3;
	}
	return resultPoint;
}

void STLFile::AlterPositionX(GLfloat amount)
{
	int i;
	for (i = 0; i < this->cTriangles; i++)
	{
		this->triangles[i].p1.x += amount;
		this->triangles[i].p2.x += amount;
		this->triangles[i].p3.x += amount;
	}
}

void STLFile::AlterPositionY(GLfloat amount)
{
	int i;
	for (i = 0; i < this->cTriangles; i++)
	{
		this->triangles[i].p1.y += amount;
		this->triangles[i].p2.y += amount;
		this->triangles[i].p3.y += amount;
	}
}

void STLFile::AlterPositionZ(GLfloat amount)
{
	int i;
	for (i = 0; i < this->cTriangles; i++)
	{
		this->triangles[i].p1.z += amount;
		this->triangles[i].p2.z += amount;
		this->triangles[i].p3.z += amount;
	}
}


void STLFile::read(HWND *hwndOwner, GLfloat *maxCoordinate)
{
	// Initialize OPENFILENAME
	ZeroMemory(&(this->ofn), sizeof(this->ofn));
	this->ofn.lStructSize = sizeof(this->ofn);
	this->ofn.hwndOwner = *hwndOwner;
	this->ofn.lpstrFilter = TEXT("STereoLithography (.stl)\0*.stl*\0");
	this->ofn.lpstrCustomFilter = NULL;
	this->ofn.nFilterIndex = 0;
	this->ofn.lpstrFile = this->szSTLPath;
	//
	// Set lpstrFile[0] to '\0' so that GetOpenFileName does not 
	// use the contents of szFile to initialize itself.
	//
	this->ofn.lpstrFile[0] = '\0';
	this->ofn.nMaxFile = sizeof(this->szSTLPath);			
	this->ofn.lpstrFileTitle = NULL;
	this->ofn.lpstrInitialDir = NULL;
	this->ofn.lpstrTitle = NULL;
	this->ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	// Display the Open dialog box. 
	this->bOpened = GetOpenFileName(&this->ofn);

	if (!this->bOpened)
		return;
	// Reading STL File
	std::ifstream fileSTL;
	char szLine[MAXLINE], *pTemp;
	int i;

	this->cTriangles = 0;
	fileSTL.open(this->ofn.lpstrFile);
	fileSTL.getline(szLine, MAXLINE);
	while(!fileSTL.eof())
	{
		pTemp = strstr(szLine, "vertex");
		if (pTemp != NULL)
		{
			sscanf_s(pTemp + 7,
				"%f %f %f",
				&(this->triangles[this->cTriangles].p1.x),
				&(this->triangles[this->cTriangles].p1.y),
				&(this->triangles[this->cTriangles].p1.z));

			fileSTL.getline(szLine, MAXLINE);
			pTemp = strstr(szLine, "vertex");
			sscanf_s(pTemp + 7,
				"%f %f %f",
				&(this->triangles[this->cTriangles].p2.x),
				&(this->triangles[this->cTriangles].p2.y),
				&(this->triangles[this->cTriangles].p2.z));

			fileSTL.getline(szLine, MAXLINE);
			pTemp = strstr(szLine, "vertex");
			sscanf_s(pTemp + 7,
				"%f %f %f",
				&(this->triangles[this->cTriangles].p3.x),
				&(this->triangles[this->cTriangles].p3.y),
				&(this->triangles[this->cTriangles].p3.z));

			(this->cTriangles)++;
		}
		fileSTL.getline(szLine, MAXLINE);
	}
	fileSTL.close();
	//End of reading

	// Determine max and min coordinates
	for (i = 0; i < this->cTriangles; i++)
	{
		if (abs(this->triangles[i].p1.x) > *maxCoordinate)
			*maxCoordinate = abs(triangles[i].p1.x);
		if (abs(this->triangles[i].p2.x) > *maxCoordinate)
			*maxCoordinate = abs(triangles[i].p2.x);
		if (abs(this->triangles[i].p3.x) > *maxCoordinate)
			*maxCoordinate = abs(triangles[i].p3.x);

		if (abs(this->triangles[i].p1.y) > *maxCoordinate)
			*maxCoordinate = abs(triangles[i].p1.y);
		if (abs(this->triangles[i].p2.y) > *maxCoordinate)
			*maxCoordinate = abs(triangles[i].p2.y);
		if (abs(this->triangles[i].p3.y) > *maxCoordinate)
			*maxCoordinate = abs(triangles[i].p3.y);			

		if (abs(this->triangles[i].p1.z) > *maxCoordinate)
			*maxCoordinate = abs(triangles[i].p1.z);
		if (abs(this->triangles[i].p2.z) > *maxCoordinate)
			*maxCoordinate = abs(triangles[i].p2.z);
		if (abs(this->triangles[i].p3.z) > *maxCoordinate)
			*maxCoordinate = abs(triangles[i].p3.z);
	}		
}

void STLFile::ResetRotation()
{
	this->xRot = this->yRot = 0;
}

void STLFile::setSurfaceColor(COLORREF rgbSurface)
{
	this->rSurface = GetRValue(rgbSurface) / 255.0f;
	this->gSurface = GetGValue(rgbSurface) / 255.0f;
	this->bSurface = GetBValue(rgbSurface) / 255.0f;
}

void STLFile::setBorderColor(COLORREF rgbBorder)
{
	this->rBorder = GetRValue(rgbBorder) / 255.0f;
	this->gBorder = GetGValue(rgbBorder) / 255.0f;
	this->bBorder = GetBValue(rgbBorder) / 255.0f;
}

void STLFile::promptSurfaceColor(HWND hwndOwner)
{
	// Initialize CHOOSECOLOR 
	ZeroMemory(&this->cc, sizeof(cc));
	this->cc.lStructSize = sizeof(cc);
	this->cc.hwndOwner = hwndOwner;
	this->cc.lpCustColors = (LPDWORD) acrCustClr;
	this->cc.rgbResult = this->rgbSurface;
	this->cc.Flags = CC_FULLOPEN | CC_RGBINIT;

	if (ChooseColor(&cc)==TRUE)
	{
		this->setSurfaceColor(cc.rgbResult);
	}
}

void STLFile::promptBorderColor(HWND hwndOwner)
{
	// Initialize CHOOSECOLOR 
	ZeroMemory(&this->cc, sizeof(cc));
	this->cc.lStructSize = sizeof(cc);
	this->cc.hwndOwner = hwndOwner;
	this->cc.lpCustColors = (LPDWORD) acrCustClr;
	this->cc.rgbResult = this->rgbBorder;
	this->cc.Flags = CC_FULLOPEN | CC_RGBINIT;

	if (ChooseColor(&cc)==TRUE)
	{
		this->setBorderColor(cc.rgbResult);
	}
}
