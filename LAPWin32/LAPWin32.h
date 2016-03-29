#pragma once
#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")


#include "resource.h"
#include "Triangle.h"
#include "STLFile.h"

#define ID_OPENGLSTATIC					1
#define ID_ZOOMINBUTTON					2
#define ID_ZOOMOUTBUTTON				3
#define	ID_BORDERCOLORBUTTON			4
#define	ID_SURFACECOLORBUTTON			5
#define ID_STLCOMBOBOX					6
#define ID_SHOWHIDEBUTTON					7

#define MAX_LOADSTRING		100
#define MAXSOLIDCHAR		100
#define	LEFTTOOLBARWIDTH	70
#define	TOPTOOLBARHEIGHT	70

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

GLfloat maxCoordinate = 0;

HPALETTE hPalette = NULL;

std::vector<STLFile*> STLFileVector;

WNDPROC OpenGLStaticDefProc;

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
LRESULT CALLBACK	OpenGLStaticProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
void				ComboBoxSelChange(HWND *hwndSTLComboBox, HWND* hwndShowCheckBox, HWND* hwndMain);
