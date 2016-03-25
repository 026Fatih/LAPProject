#pragma once
#include "Triangle.h"
#include "float.h"

#define MAXLINE				100


class STLFile
{
private:
	BOOL bLockRotation;

	int		GetTriangleCountFromSTLFile();
	Point	GetBiggestXVertex();
	Point	GetSmallestXVertex();
	void	AlterPositionX(GLfloat amount);
	void	AlterPositionY(GLfloat amount);
	void	AlterPositionZ(GLfloat amount);
public:
	static const int
		MERGE_POSITIVE_X = 1,
		MERGE_NEGATIVE_X = 2,
		MERGE_POSITIVE_Y = 3,
		MERGE_NEGATIVE_Y = 4;

	BOOL			bOpened, bShow;
	CHOOSECOLOR		cc;                 // common dialog box structure 
	COLORREF		acrCustClr[16], rgbSurface, rgbBorder; // array of custom colors 
	GLfloat
		rBorder, gBorder, bBorder,
		rSurface, gSurface, bSurface,
		xBaseRot,	// Used when rotating with mouse
		yBaseRot,	// Used when rotating with mouse
		xRot, yRot;
	int				cTriangles;
	OPENFILENAME	ofn;
	TCHAR			szSTLPath[MAX_PATH];
	Triangle		*triangles;

	STLFile(void);
	STLFile(const TCHAR szSTLFilePath[], int *maxX, int *maxY, int *maxZ);
	~STLFile(void);

	void	draw(void);
	void	draw(GLfloat rBorder, GLfloat gBorder, GLfloat bBorder,
		GLfloat rSurface, GLfloat  gSurface, GLfloat  bSurface);
	void	incrementXRot(GLfloat amount);
	void	incrementYRot(GLfloat amount);
	BOOL	Locked();
	void	LockRotation(BOOL bLock);
	void	Merge(STLFile *s, int iMergePos);
	void	promptSurfaceColor(HWND hwndOwner);
	void	promptBorderColor(HWND hwndOwner);
	void	read(HWND *hwndOwner, GLfloat *maxCoordinate);
	void	ResetRotation();
	void	setSurfaceColor(COLORREF rgbSurface);
	void	setBorderColor(COLORREF rgbBorder);
};
