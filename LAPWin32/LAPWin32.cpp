// LAPWin32.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "LAPWin32.h"

int APIENTRY _tWinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPTSTR    lpCmdLine,
	int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	
	INITCOMMONCONTROLSEX iccex;
	iccex.dwICC = sizeof(iccex);
		iccex.dwICC = ICC_ANIMATE_CLASS |
			ICC_BAR_CLASSES|
			ICC_COOL_CLASSES |
			ICC_DATE_CLASSES |
			ICC_HOTKEY_CLASS |
			ICC_INTERNET_CLASSES |
			ICC_LINK_CLASS |
			ICC_LISTVIEW_CLASSES |
			ICC_NATIVEFNTCTL_CLASS |
			ICC_PAGESCROLLER_CLASS |
			ICC_PROGRESS_CLASS |
			ICC_STANDARD_CLASSES |
			ICC_TAB_CLASSES |
			ICC_TREEVIEW_CLASSES |
			ICC_UPDOWN_CLASS |
			ICC_USEREX_CLASSES |
			ICC_WIN95_CLASSES;
		InitCommonControlsEx(&iccex);

	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_LAPWIN32, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAPWIN32));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage are only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	HBRUSH hbrBackground;
	WNDCLASSEX wcex;

	hbrBackground = CreateSolidBrush(RGB(106, 116, 131));

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAPWIN32));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= hbrBackground;
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_LAPWIN32);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;

	hInst = hInstance; // Store instance handle in our global variable

	hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int					wmId, wmEvent;
	static BOOL			bFirstSTLOpened, bSecondSTLOpened, bRotationMode = TRUE;
	static HANDLE
		hMoveModeIcon,
		hZoomInImage,
		hZoomOutImage;
	static HDC			hdcOpenGLStatic, hdcMain;
	static HGLRC		hRC;               // Permenant Rendering context
	static HMENU		hMenu;
	static HWND
		hwndBorderColorButton,
		hwndMoveMode,
		hwndOpenGLStatic,
		hwndRotationMode,
		hwndShowHideButton,
		hwndSTLComboBox,
		hwndSurfaceColorButton,
		hwndZoomInButton,
		hwndZoomOutButton;
	static int
		cxButton,
		cxChar,
		cxClient,
		cxSTLComboBox,
		cyButton,
		cyChar,
		cyClient,
		cxOpenGLStatic,
		cyOpenGLStatic,
		cySpacing,
		iItemIndex,
		xMoveBase,
		xBorderColorButton,
		xSurfaceColorButton,
		xStartingPos,
		yMoveBase,
		yStartingPos;
	LRESULT				lResult;
	static OPENFILENAME	ofnFirstSTL, ofnSecondSTL;       // common dialog box structure
	PAINTSTRUCT			ps;
	static TCHAR		szFirstSTLPath[MAX_PATH], szSecondSTLPath[MAX_PATH];       // buffer for file name	
	STLFile*			temp;	
	static std::vector<STLFile*>::iterator p;	
	static char szListItem[MAXSOLIDCHAR];

	switch (message)
	{
		// Window creation, setup for OpenGL
	case WM_CREATE:	
		cxChar = LOWORD(GetDialogBaseUnits());
		cyChar = HIWORD(GetDialogBaseUnits());
		cyButton = cxButton = 40;
		cySpacing = cyChar / 2;		

		hwndOpenGLStatic = CreateWindow(TEXT("static"), NULL,
			WS_CHILD | WS_VISIBLE,
			LEFTTOOLBARWIDTH, TOPTOOLBARHEIGHT, 200, 200,
			hWnd, (HMENU) ID_OPENGLSTATIC, hInst, NULL);

		hwndZoomInButton = CreateWindow(TEXT("button"), TEXT("Zoom In"),
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_ICON,
			cxChar, cySpacing, cxButton, cyButton,
			hWnd, (HMENU) ID_ZOOMINBUTTON, hInst, NULL);

		hwndZoomOutButton = CreateWindow(TEXT("button"), TEXT("Zoom Out"),
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_ICON,
			cxChar, cyButton + 2 * cySpacing, cxButton, cyButton,
			hWnd, (HMENU) ID_ZOOMOUTBUTTON, hInst, NULL);

		hwndRotationMode = CreateWindow(TEXT("button"), TEXT("Rotation Mode"),
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_ICON,
			cxChar, 2 * (cyButton + cySpacing) + cySpacing, cxButton, cyButton,
			hWnd, (HMENU) ID_ROTATIONMODEBUTTON, hInst, NULL);

		hwndMoveMode= CreateWindow(TEXT("button"), TEXT("Move Mode"),
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_ICON,
			cxChar, 3 * (cyButton + cySpacing) + cySpacing, cxButton, cyButton,
			hWnd, (HMENU) ID_MOVEMODEBUTTON, hInst, NULL);

		hwndBorderColorButton = CreateWindow(TEXT("button"),
			TEXT("Border Color"),
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON |BS_MULTILINE,
			0, 0, 0, 0,
			hWnd, (HMENU) ID_BORDERCOLORBUTTON, hInst, NULL);

		hwndSurfaceColorButton = CreateWindow(TEXT("button"),
			TEXT("Surface Color"),
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON |BS_MULTILINE,
			0, 0, 0, 0,
			hWnd, (HMENU) ID_SURFACECOLORBUTTON, hInst, NULL);

		hwndSTLComboBox = CreateWindowA(WC_COMBOBOXA, NULL, 
			CBS_DROPDOWNLIST | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE,
			LEFTTOOLBARWIDTH,  cySpacing, 10, 10,
			hWnd, (HMENU) ID_STLCOMBOBOX, hInst, NULL);

		hwndShowHideButton = CreateWindow(WC_BUTTON,
			TEXT("Show"),
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_TEXT,
			0, 0, 0, 0,
			hWnd, (HMENU) ID_SHOWHIDEBUTTON, hInst, NULL);

		hZoomInImage = LoadImage(hInst, MAKEINTRESOURCE(IDI_ZOOMIN),
			IMAGE_ICON, cxButton, cyButton, 0);
		if (hZoomInImage == NULL)
			ErrorExit(TEXT("LoadImage"));
		else
			lResult = SendMessage(hwndZoomInButton, BM_SETIMAGE, (WPARAM)IMAGE_ICON, (LPARAM)hZoomInImage);

		hZoomOutImage = LoadImage(hInst, MAKEINTRESOURCE(IDI_ZOOMOUT),
			IMAGE_ICON, cxButton, cyButton, 0);
		if (hZoomOutImage == NULL)
			ErrorExit(TEXT("LoadImage"));
		else
			lResult = SendMessage(hwndZoomOutButton, BM_SETIMAGE, (WPARAM)IMAGE_ICON, (LPARAM)hZoomOutImage);

		hMoveModeIcon = LoadImage(hInst, MAKEINTRESOURCE(IDI_MOVEMODE),
			IMAGE_ICON, cxButton, cyButton, 0);
		if (hMoveModeIcon == NULL)
			ErrorExit(TEXT("LoadImage"));
		else
			lResult = SendMessage(hwndMoveMode, BM_SETIMAGE, (WPARAM)IMAGE_ICON, (LPARAM)hMoveModeIcon);

		/*OpenGLStaticDefProc = (WNDPROC)SetWindowLongPtr(
		hwndOpenGLStatic, GWL_WNDPROC, (LONG)OpenGLStaticProc);*/

		// Store the device context
		hdcOpenGLStatic = GetDC(hwndOpenGLStatic);              

		// Select the pixel format
		SetDCPixelFormat(hdcOpenGLStatic);          

		hPalette = GetOpenGLPalette(hdcOpenGLStatic);

		// Create the rendering context and make it current
		hRC = wglCreateContext(hdcOpenGLStatic);
		wglMakeCurrent(hdcOpenGLStatic, hRC);
		SetupRC();

		return 0;

	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		hMenu	= GetMenu(hWnd);

		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;

		case IDM_FILE_ADDSTLFILE:
			temp = new STLFile();
			temp->read(&hWnd, &maxCoordinate);
			if (temp->bOpened)
			{
				STLFileVector.push_back(temp);
				for(p = STLFileVector.begin(); p != STLFileVector.end(); p++)
				{
					(*p)->ResetRotation();
				}
				SendMessageA(hwndSTLComboBox, (UINT) CB_ADDSTRING, (WPARAM) 0, (LPARAM) temp->getName()); 
				ChangeSize(cxOpenGLStatic, cyOpenGLStatic);
				RedrawWindow(hWnd, NULL, NULL, RDW_INTERNALPAINT);
			}
			else
				delete temp;
			break;

		case IDM_VIEW_ZOOMIN:
		case ID_ZOOMINBUTTON:
			maxCoordinate /= 1.5f;
			ChangeSize(cxOpenGLStatic, cyOpenGLStatic);
			RedrawWindow(hWnd, NULL, NULL, RDW_INTERNALPAINT);
			SetFocus(hWnd);
			break;

		case IDM_VIEW_ZOOMOUT:
		case ID_ZOOMOUTBUTTON:
			maxCoordinate *=1.5f;
			ChangeSize(cxOpenGLStatic, cyOpenGLStatic);
			RedrawWindow(hWnd, NULL, NULL, RDW_INTERNALPAINT);
			SetFocus(hWnd);
			break;

		case ID_MOVEMODEBUTTON:
			bRotationMode = FALSE;
			break;

		case ID_ROTATIONMODEBUTTON:
			bRotationMode = TRUE;
			break;

		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;

		case ID_STLCOMBOBOX:			
			switch (wmEvent)
			{
			case CBN_SELCHANGE:				
				ComboBoxSelChange(&hwndSTLComboBox, &hwndShowHideButton, &hWnd);
				break;
			}
			break;

		case ID_BORDERCOLORBUTTON:
			iItemIndex = SendMessage(hwndSTLComboBox, CB_GETCURSEL, 
				(WPARAM) 0, (LPARAM) 0);
			SendMessageA(hwndSTLComboBox, CB_GETLBTEXT, (WPARAM) iItemIndex, (LPARAM) szListItem);
			for(p = STLFileVector.begin(); p != STLFileVector.end(); p++)
			{
				if (strcmp((*p)->getName(), szListItem) == 0)
				{
					(*p)->promptBorderColor(hWnd);					
					RedrawWindow(hWnd, NULL, NULL, RDW_INTERNALPAINT);
					break;
				}
			}
			break;

		case ID_SURFACECOLORBUTTON:
			iItemIndex = SendMessage(hwndSTLComboBox, CB_GETCURSEL, 
				(WPARAM) 0, (LPARAM) 0);
			SendMessageA(hwndSTLComboBox, CB_GETLBTEXT, (WPARAM) iItemIndex, (LPARAM) szListItem);
			for(p = STLFileVector.begin(); p != STLFileVector.end(); p++)
			{
				if (strcmp((*p)->getName(), szListItem) == 0)
				{
					(*p)->promptSurfaceColor(hWnd);					
					RedrawWindow(hWnd, NULL, NULL, RDW_INTERNALPAINT);
					break;
				}
			}
			break;

		case ID_SHOWHIDEBUTTON:
			iItemIndex = SendMessage(hwndSTLComboBox, CB_GETCURSEL, 
				(WPARAM) 0, (LPARAM) 0);
			SendMessageA(hwndSTLComboBox, CB_GETLBTEXT, (WPARAM) iItemIndex, (LPARAM) szListItem);
			for(p = STLFileVector.begin(); p != STLFileVector.end(); p++)
			{
				if (strcmp((*p)->getName(), szListItem) == 0)
				{
					(*p)->bShow = !(*p)->bShow;
					break;
				}
			}
			RedrawWindow(hWnd, NULL, NULL, RDW_INTERNALPAINT);
			ComboBoxSelChange(&hwndSTLComboBox, &hwndShowHideButton, &hWnd);
			break;

		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		return 0;

	case WM_PAINT:
		hdcMain = BeginPaint(hWnd, &ps);		

		// Call OpenGL drawing code
		RenderScene();

		SwapBuffers(hdcOpenGLStatic);

		// Validate the newly painted client area
		ValidateRect(hwndOpenGLStatic, NULL);

		EndPaint(hWnd, &ps);
		return 0;

	case WM_LBUTTONDOWN:
		xStartingPos = LOWORD(lParam); 
		yStartingPos = HIWORD(lParam);
		if (bRotationMode)
		{
			for(p = STLFileVector.begin(); p != STLFileVector.end(); p++)
			{
				(*p)->yBaseRot = (GLfloat)((int)(*p)->yRot % 360);
				(*p)->xBaseRot = (GLfloat)((int)(*p)->xRot % 360);
			}
		}
		else
		{
			xMoveBase = xMove;
			yMoveBase = yMove;
		}
		return 0 ;

	case WM_RBUTTONDOWN:
		xStartingPos = LOWORD(lParam); 
		yStartingPos = HIWORD(lParam);
		if (bRotationMode)
		{
			for(p = STLFileVector.begin(); p != STLFileVector.end(); p++)
			{
				(*p)->zBaseRot = (GLfloat)((int)(*p)->zRot % 360);
			}
		}
		return 0 ;

	case WM_MOUSEMOVE:
		if (xStartingPos < LEFTTOOLBARWIDTH ||
			yStartingPos < TOPTOOLBARHEIGHT)
			return 0;
		if (bRotationMode)
		{
			if (wParam & MK_LBUTTON)
			{
				for(p = STLFileVector.begin(); p != STLFileVector.end(); p++)
				{
					(*p)->yRot = (*p)->yBaseRot + xStartingPos - LOWORD(lParam);
					(*p)->xRot = (*p)->xBaseRot + yStartingPos - HIWORD(lParam);
				}
				InvalidateRect(hWnd, NULL, FALSE);
			}

			else if (wParam & MK_RBUTTON)
			{
				for(p = STLFileVector.begin(); p != STLFileVector.end(); p++)
				{
					(*p)->zRot = (*p)->zBaseRot + xStartingPos - LOWORD(lParam);
				}
				InvalidateRect(hWnd, NULL, FALSE);
			}
		}
		else
		{
			if (wParam & MK_LBUTTON)
			{
				xMove = xMoveBase + (xStartingPos - LOWORD(lParam)) / xRatio;
				yMove = yMoveBase - (yStartingPos - HIWORD(lParam)) / yRatio;
				ChangeSize(cxOpenGLStatic, cyOpenGLStatic);
				RedrawWindow(hWnd, NULL, NULL, RDW_INTERNALPAINT);
			}
		}

		return 0 ;

	case WM_LBUTTONDBLCLK:
		xStartingPos = LOWORD(lParam); 
		yStartingPos = HIWORD(lParam);
		if (xStartingPos > LEFTTOOLBARWIDTH)
		{
			int xhalf = (cxClient - LEFTTOOLBARWIDTH) / 2,
				yhalf = cyClient / 2,
				xtocheck, ytocheck;

			xtocheck = (int)((xStartingPos - xhalf) / xRatio);
			ytocheck = (int)((yhalf - yStartingPos) / yRatio);

			for(p = STLFileVector.begin(); p != STLFileVector.end(); p++)
			{
				if ((*p)->Inside(xtocheck, ytocheck))
				{
					iItemIndex = SendMessageA(hwndSTLComboBox, CB_SELECTSTRING, -1, (LPARAM) (*p)->getName());

					ComboBoxSelChange(&hwndSTLComboBox, &hwndShowHideButton, &hWnd);
					break;
				}
			}
		}

		return 0;

		// Windows is telling the application that it may modify
		// the system palette.  This message in essance asks the 
		// application for a new palette.
	case WM_QUERYNEWPALETTE:
		// If the palette was created.
		if(hPalette)
		{
			int nRet;

			// Selects the palette into the current device context
			SelectPalette(hdcOpenGLStatic, hPalette, FALSE);

			// Map entries from the currently selected palette to
			// the system palette.  The return value is the number 
			// of palette entries modified.
			nRet = RealizePalette(hdcOpenGLStatic);

			// Repaint, forces remap of palette in current window
			InvalidateRect(hwndOpenGLStatic, NULL, FALSE);

			return nRet;
		}
		return 0;

		// This window may set the palette, even though it is not the 
		// currently active window.
	case WM_PALETTECHANGED:
		// Don't do anything if the palette does not exist, or if
		// this is the window that changed the palette.
		if((hPalette != NULL) && ((HWND)wParam != hwndOpenGLStatic))
		{
			// Select the palette into the device context
			SelectPalette(hdcOpenGLStatic,hPalette,FALSE);

			// Map entries to system palette
			RealizePalette(hdcOpenGLStatic);

			// Remap the current colors to the newly realized palette
			UpdateColors(hdcOpenGLStatic);
			return 0;
		}
		return 0;

		// Window is resized.
	case WM_SIZE:
		cxClient = LOWORD(lParam);
		cyClient = HIWORD(lParam);
		cxOpenGLStatic = cxClient - LEFTTOOLBARWIDTH;
		cyOpenGLStatic = cyClient - TOPTOOLBARHEIGHT;
		cxSTLComboBox = 100;
		xBorderColorButton = LEFTTOOLBARWIDTH + cxSTLComboBox + cxChar;
		xSurfaceColorButton = xBorderColorButton + cxButton + cxChar;

		// Call our function which modifies the clipping
		// volume and viewport		
		ChangeSize(cxOpenGLStatic, cyOpenGLStatic);

		MoveWindow(hwndOpenGLStatic, LEFTTOOLBARWIDTH, TOPTOOLBARHEIGHT, cxOpenGLStatic, cyOpenGLStatic, FALSE);
		MoveWindow(hwndSTLComboBox, LEFTTOOLBARWIDTH, cySpacing, cxSTLComboBox, TOPTOOLBARHEIGHT, FALSE);
		MoveWindow(hwndBorderColorButton, xBorderColorButton, cySpacing, cxButton, cyButton, TRUE);
		MoveWindow(hwndSurfaceColorButton, xSurfaceColorButton, cySpacing, cxButton, cyButton, TRUE);
		MoveWindow(hwndShowHideButton, xSurfaceColorButton + cxButton + cxChar, cySpacing, cxButton, cyButton, TRUE);
		return 0;

	case WM_KEYDOWN:
		{
			if(wParam == VK_UP)
			{
				for(p = STLFileVector.begin(); p != STLFileVector.end(); p++)
				{
					(*p)->incrementXRot(-5.0f);
				}
			}

			if(wParam == VK_DOWN)
			{
				for(p = STLFileVector.begin(); p != STLFileVector.end(); p++)
				{
					(*p)->incrementXRot(5.0f);
				}
			}

			if(wParam == VK_LEFT)
			{
				for(p = STLFileVector.begin(); p != STLFileVector.end(); p++)
				{
					(*p)->incrementYRot(-5.0f);
				}
			}

			if(wParam == VK_RIGHT)
			{
				for(p = STLFileVector.begin(); p != STLFileVector.end(); p++)
				{
					(*p)->incrementYRot(5.0f);
				}
			}

			InvalidateRect(hWnd, NULL, FALSE);
		}
		return 0;

	case WM_DESTROY:
		// Deselect the current rendering context and delete it
		wglMakeCurrent(hdcOpenGLStatic,NULL);
		wglDeleteContext(hRC);
		if(hPalette != NULL)
			DeleteObject(hPalette);

		PostQuitMessage(0);
		return 0;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}


void RenderScene(void)
{
	GLfloat	fSizes[2];			// Line width range metrics

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glShadeModel(GL_SMOOTH);

	glGetFloatv(GL_LINE_WIDTH_RANGE,fSizes);
	glLineWidth(fSizes[0]);		

	static std::vector<STLFile*>::iterator p;
	for(p = STLFileVector.begin(); p != STLFileVector.end(); p++)
	{
		if ((*p)->bShow)
			(*p)->draw();
	}

	glFlush();
}

void SetupRC(void)
{
	// Light values and coordinates
	GLfloat  whiteLight[] = { 0.45f, 0.45f, 0.45f, 1.0f };
	GLfloat  sourceLight[] = { 0.25f, 0.25f, 0.25f, 1.0f };
	GLfloat	 lightPos[] = { -50.f, 25.0f, 250.0f, 0.0f };

	glEnable(GL_DEPTH_TEST);	// Hidden surface removal
	glFrontFace(GL_CCW);		// Counter clock-wise polygons face out

	// Enable lighting
	glEnable(GL_LIGHTING);

	// Setup and enable light 0
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT,whiteLight);
	glLightfv(GL_LIGHT0,GL_AMBIENT,sourceLight);
	glLightfv(GL_LIGHT0,GL_DIFFUSE,sourceLight);
	glLightfv(GL_LIGHT0,GL_POSITION,lightPos);
	glEnable(GL_LIGHT0);

	// Enable color tracking
	glEnable(GL_COLOR_MATERIAL);

	// Set Material properties to follow glColor values
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	glClearColor((52.0f / 255.0f), (61.0f / 255.0f), (75.0f / 255.0f), 1.0f );
}

void SetDCPixelFormat(HDC hdcOpenGLStatic)
{
	int nPixelFormat;

	static PIXELFORMATDESCRIPTOR pfd = {
		sizeof(PIXELFORMATDESCRIPTOR),  // Size of this structure
		1,                                                              // Version of this structure    
		PFD_DRAW_TO_WINDOW |                    // Draw to Window (not to bitmap)
		PFD_SUPPORT_OPENGL |					// Support OpenGL calls in window
		PFD_DOUBLEBUFFER,                       // Double buffered
		PFD_TYPE_RGBA,                          // RGBA Color mode
		24,                                     // Want 24bit color 
		0,0,0,0,0,0,                            // Not used to select mode
		0,0,                                    // Not used to select mode
		0,0,0,0,0,                              // Not used to select mode
		16,                                     // Size of depth buffer
		0,                                      // Not used to select mode
		0,                                      // Not used to select mode
		PFD_MAIN_PLANE,                         // Draw in main plane
		0,                                      // Not used to select mode
		0,0,0 };                                // Not used to select mode

		// Choose a pixel format that best matches that described in pfd
		nPixelFormat = ChoosePixelFormat(hdcOpenGLStatic, &pfd);

		// Set the pixel format for the device context
		SetPixelFormat(hdcOpenGLStatic, nPixelFormat, &pfd);
}

HPALETTE GetOpenGLPalette(HDC hDC)
{
	HPALETTE hRetPal = NULL;	// Handle to palette to be created
	PIXELFORMATDESCRIPTOR pfd;	// Pixel Format Descriptor
	LOGPALETTE *pPal;			// Pointer to memory for logical palette
	int nPixelFormat;			// Pixel format index
	int nColors;				// Number of entries in palette
	int i;						// Counting variable
	BYTE RedRange,GreenRange,BlueRange;
	// Range for each color entry (7,7,and 3)


	// Get the pixel format index and retrieve the pixel format description
	nPixelFormat = GetPixelFormat(hDC);
	DescribePixelFormat(hDC, nPixelFormat, sizeof(PIXELFORMATDESCRIPTOR), &pfd);

	// Does this pixel format require a palette?  If not, do not create a
	// palette and just return NULL
	if(!(pfd.dwFlags & PFD_NEED_PALETTE))
		return NULL;

	// Number of entries in palette.  8 bits yeilds 256 entries
	nColors = 1 << pfd.cColorBits;	

	// Allocate space for a logical palette structure plus all the palette entries
	pPal = (LOGPALETTE*)malloc(sizeof(LOGPALETTE) +nColors*sizeof(PALETTEENTRY));

	// Fill in palette header 
	pPal->palVersion = 0x300;		// Windows 3.0
	pPal->palNumEntries = nColors; // table size

	// Build mask of all 1's.  This creates a number represented by having
	// the low order x bits set, where x = pfd.cRedBits, pfd.cGreenBits, and
	// pfd.cBlueBits.  
	RedRange = (1 << pfd.cRedBits) -1;
	GreenRange = (1 << pfd.cGreenBits) - 1;
	BlueRange = (1 << pfd.cBlueBits) -1;

	// Loop through all the palette entries
	for(i = 0; i < nColors; i++)
	{
		// Fill in the 8-bit equivalents for each component
		pPal->palPalEntry[i].peRed = (i >> pfd.cRedShift) & RedRange;
		pPal->palPalEntry[i].peRed = (unsigned char)(
			(double) pPal->palPalEntry[i].peRed * 255.0 / RedRange);

		pPal->palPalEntry[i].peGreen = (i >> pfd.cGreenShift) & GreenRange;
		pPal->palPalEntry[i].peGreen = (unsigned char)(
			(double)pPal->palPalEntry[i].peGreen * 255.0 / GreenRange);

		pPal->palPalEntry[i].peBlue = (i >> pfd.cBlueShift) & BlueRange;
		pPal->palPalEntry[i].peBlue = (unsigned char)(
			(double)pPal->palPalEntry[i].peBlue * 255.0 / BlueRange);

		pPal->palPalEntry[i].peFlags = (unsigned char) NULL;
	}


	// Create the palette
	hRetPal = CreatePalette(pPal);

	// Go ahead and select and realize the palette for this device context
	SelectPalette(hDC,hRetPal,FALSE);
	RealizePalette(hDC);

	// Free the memory used for the logical palette structure
	free(pPal);

	// Return the handle to the new palette
	return hRetPal;
}

// Change viewing volume and viewport.  Called when window is resized
void ChangeSize(GLsizei w, GLsizei h)
{
	GLfloat nRange = 120.0f;
	// Prevent a divide by zero
	if(h == 0)
		h = 1;

	// Set Viewport to window dimensions
	glViewport(0, 0, w, h);

	// Reset coordinate system
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Establish clipping volume (left, right, bottom, top, near, far)
	if (w <= h) 
	{
		glOrtho(-maxCoordinate + xMove,
			maxCoordinate + xMove,
			(-maxCoordinate) * (GLfloat)h / w + yMove,
			maxCoordinate * (GLfloat)h / w + yMove,
			maxCoordinate, -maxCoordinate);
		xRatio = w / (2 * maxCoordinate);
		yRatio = h / (2 * maxCoordinate * ((GLfloat)h / w));
	}
	else 
	{
		glOrtho(-maxCoordinate * (GLfloat)w / h + xMove,
			maxCoordinate * (GLfloat)w / h + xMove,
			-maxCoordinate + yMove,
			maxCoordinate + yMove,
			maxCoordinate, -maxCoordinate);
		xRatio = w / (2 * maxCoordinate * ((GLfloat)w / h));
		yRatio = h / (2 * maxCoordinate);
	}

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void ComboBoxSelChange(HWND *hwndSTLComboBox, HWND* hwndShowHideButton, HWND* hwndMain)
{
	char szListItem[MAXSOLIDCHAR];
	int iItemIndex;	
	std::vector<STLFile*>::iterator p;	
	iItemIndex = SendMessage(*hwndSTLComboBox, CB_GETCURSEL, 
		(WPARAM) 0, (LPARAM) 0);
	SendMessageA(*hwndSTLComboBox, CB_GETLBTEXT, (WPARAM) iItemIndex, (LPARAM) szListItem);
	for(p = STLFileVector.begin(); p != STLFileVector.end(); p++)
	{
		if (strcmp((*p)->getName(), szListItem) == 0)
		{
			if ((*p)->bShow)
				SetWindowText(*hwndShowHideButton, TEXT("Hide"));
			else
				SetWindowText(*hwndShowHideButton, TEXT("Show"));
			RedrawWindow(*hwndMain, NULL, NULL, RDW_INTERNALPAINT);
			break;
		}
	}
}
