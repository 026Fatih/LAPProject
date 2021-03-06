#pragma once
//#pragma comment(linker,"\"/manifestdependency:type='win32' \
//name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
//processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")


#include "resource.h"
#include "Triangle.h"
#include "STLFile.h"
#include "Drawable.h"
#include "Line.h"
#include "Quadrilateral.h"
#include "Surface.h"
#include "BezierCurve.h"
#include "Cylinder.h"

#define ID_OPENGLSTATIC					1
#define ID_ZOOMINBUTTON					2
#define ID_ZOOMOUTBUTTON				3
#define	ID_BORDERCOLORBUTTON			4
#define	ID_SURFACECOLORBUTTON			5
#define ID_STLCOMBOBOX					6
#define ID_SHOWHIDEBUTTON				7
#define ID_ROTATIONMODEBUTTON			8
#define ID_MOVEMODEBUTTON				9
#define	ID_RESETROTATIONBUTTON			10
#define	ID_DEMOBUTTON					11
#define	IDT_DEMO						12
#define ID_RECTANGLEBUTTON				13
#define ID_LINEBUTTON					14
#define	ID_CURVEBUTTON					15
#define ID_SURFACEBUTTON				16
#define ID_CYLINDERBUTTON				17
#define ID_ATILIMBUTTON					18
#define ID_CLEARBUTTON					19

#define MAX_LOADSTRING		100
#define MAXSOLIDCHAR		100
#define	LEFTTOOLBARWIDTH	70
#define	TOPTOOLBARHEIGHT	70
#define	ROTATIONRATIO		0.5f

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

// Rotation amounts
GLfloat xRot = 0.0f;
GLfloat yRot = 0.0f;

GLfloat xRatio, yRatio;

STLFile
	FirstSTLFile,
	SecondSTLFile;

GLfloat
	maxCoordinate = 100,
	xMove = 0,
	yMove = 0;

HPALETTE hPalette = NULL;

std::vector<STLFile*> STLFileVector;
std::vector<Drawable*> DrawableVector;

WNDPROC OpenGLStaticDefProc;

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	LineDlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK	Rectangle(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK CurveDlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
void				RenderScene(void);
void				SetupRC(void);
void				SetDCPixelFormat(HDC hdc);
HPALETTE			GetOpenGLPalette(HDC hDC);
void				ChangeSize(GLsizei w, GLsizei h);
void				ErrorExit(LPTSTR lpszFunction);
LRESULT CALLBACK	OpenGLStaticProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
void				ComboBoxSelChange(HWND *hwndSTLComboBox, HWND* hwndShowCheckBox, HWND* hwndMain);
