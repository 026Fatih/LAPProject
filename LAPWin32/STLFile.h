#pragma once
#include "Triangle.h"
#include "float.h"

#define MAXLINE				100


class STLFile
{
private:
	BOOL bLockRotation;
	char *szSolidName;

	int		GetTriangleCountFromSTLFile();
	Point	GetBiggestXVertex();
	Point	GetSmallestXVertex();
	Point	GetBiggestYVertex();
	Point	GetSmallestYVertex();
	void	AlterPositionX(GLfloat amount);
	void	AlterPositionY(GLfloat amount);
	void	AlterPositionZ(GLfloat amount);
	void	ReadBinary(GLfloat *maxCoordinate);
public:
	static const int
		MERGE_POSITIVE_X = 1,
		MERGE_NEGATIVE_X = 2,
		MERGE_POSITIVE_Y = 3,
		MERGE_NEGATIVE_Y = 4;

	BOOL			bOpened, bShow;
	CHOOSECOLOR		cc;                 // common dialog box structure 
	COLORREF
		acrCustClr[16],	// array of custom colors 
		rgbSurface,
		rgbBorder; 
	GLfloat
		rBorder, gBorder, bBorder,
		rSurface, gSurface, bSurface,
		xBaseRot,	// Used when rotating with mouse
		yBaseRot,	// Used when rotating with mouse
		zBaseRot,	// Used when rotating with mouse
		xRot, yRot, zRot;
	int				cTriangles;
	OPENFILENAME	ofn;
	TCHAR
		szSTLPath[MAX_PATH];		
	Triangle		*triangles;

	STLFile(void);
	STLFile(const TCHAR szSTLFilePath[], int *maxX, int *maxY, int *maxZ);
	~STLFile(void);

	void	draw(void);
	void	draw(GLfloat rBorder, GLfloat gBorder, GLfloat bBorder,
		GLfloat rSurface, GLfloat  gSurface, GLfloat  bSurface);
	void	incrementXRot(GLfloat amount);
	void	incrementYRot(GLfloat amount);

	/*
	Checks whether that point with given x and y values is
	inside of the rectangular area that surrounds the object.
	Parameters must be relative to coordinate axis of OpenGL.
	*/
	BOOL		Inside(int x, int y);
	BOOL		Locked();
	BOOL		Ascii();
	void		LockRotation(BOOL bLock);
	void		Merge(STLFile *s, int iMergePos);
	void		promptSurfaceColor(HWND hwndOwner);
	void		promptBorderColor(HWND hwndOwner);
	void		read(HWND *hwndOwner, GLfloat *maxCoordinate);
	void		ResetRotation();
	void		setSurfaceColor(COLORREF rgbSurface);
	void		setBorderColor(COLORREF rgbBorder);
	const char*	getName();
	void		setName(char szName[]);
	void		SetMaxCoordinate(GLfloat* maxCoordinate);
};
