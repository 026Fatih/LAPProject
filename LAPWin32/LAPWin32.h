#pragma once

#include "resource.h"
#include "Triangle.h"
#include "STLFile.h"

#define ID_OPENGLSTATIC					1
#define ID_ZOOMINBUTTON					2
#define ID_ZOOMOUTBUTTON				3
#define	ID_FIRSTSTLBORDERCOLORBUTTON	4
#define	ID_FIRSTSTLSURFACECOLORBUTTON	5
#define	ID_SECONDSTLBORDERCOLORBUTTON	6
#define	ID_SECONDSTLSURFACECOLORBUTTON	7

#define MAX_LOADSTRING 100
#define	LEFTTOOLBARWIDTH	70

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

// Rotation amounts
static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;

STLFile
FirstSTLFile,
SecondSTLFile;

GLfloat maxCoordinate = 0;

HPALETTE hPalette = NULL;

std::vector<STLFile*> STLFileVector;

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
void				RenderScene(void);
void				SetupRC(void);
void				SetDCPixelFormat(HDC hdc);
HPALETTE			GetOpenGLPalette(HDC hDC);
void				ChangeSize(GLsizei w, GLsizei h);
void				ErrorExit(LPTSTR lpszFunction);
