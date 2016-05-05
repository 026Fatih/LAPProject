#include "stdafx.h"
#include "resource.h"
#include "Drawable.h"
#include "BezierCurve.h"

extern std::vector<Drawable*> DrawableVector;

INT_PTR CALLBACK CurveDlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HWND hwndx1Edit, hwndy1Edit, hwndz1Edit, hwndx2Edit, hwndy2Edit, hwndz2Edit,
		hwndx3Edit, hwndy3Edit, hwndz3Edit;
	TCHAR szBuffer[100];
	int x1, y1, z1, x2, y2, z2, x3, y3, z3;

	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		hwndx1Edit = GetDlgItem(hDlg, IDC_EDITX1);
		hwndy1Edit = GetDlgItem(hDlg, IDC_EDITY1);
		hwndz1Edit = GetDlgItem(hDlg, IDC_EDITZ1);
		hwndx2Edit = GetDlgItem(hDlg, IDC_EDITX2);
		hwndy2Edit = GetDlgItem(hDlg, IDC_EDITY2);
		hwndz2Edit = GetDlgItem(hDlg, IDC_EDITZ2);
		hwndx3Edit = GetDlgItem(hDlg, IDC_EDITX3);
		hwndy3Edit = GetDlgItem(hDlg, IDC_EDITY3);
		hwndz3Edit = GetDlgItem(hDlg, IDC_EDITZ3);
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK)
		{
			SendMessage(hwndx1Edit, WM_GETTEXT, 100, (LPARAM) szBuffer);
			x1 = _tstoi(szBuffer);
			SendMessage(hwndy1Edit, WM_GETTEXT, 100, (LPARAM) szBuffer);
			y1 = _tstoi(szBuffer);
			SendMessage(hwndz1Edit, WM_GETTEXT, 100, (LPARAM) szBuffer);
			z1 = _tstoi(szBuffer);
			SendMessage(hwndx2Edit, WM_GETTEXT, 100, (LPARAM) szBuffer);
			x2 = _tstoi(szBuffer);
			SendMessage(hwndy2Edit, WM_GETTEXT, 100, (LPARAM) szBuffer);
			y2 = _tstoi(szBuffer);
			SendMessage(hwndz2Edit, WM_GETTEXT, 100, (LPARAM) szBuffer);
			z2 = _tstoi(szBuffer);
			SendMessage(hwndx3Edit, WM_GETTEXT, 100, (LPARAM) szBuffer);
			x3 = _tstoi(szBuffer);
			SendMessage(hwndy3Edit, WM_GETTEXT, 100, (LPARAM) szBuffer);
			y3 = _tstoi(szBuffer);
			SendMessage(hwndz3Edit, WM_GETTEXT, 100, (LPARAM) szBuffer);
			z3 = _tstoi(szBuffer);

			DrawableVector.push_back(new BezierCurve(x1, y1, z1, x2, y2, z2, x3, y3, z3));

			EndDialog(hDlg, LOWORD(wParam));			
			RedrawWindow(GetParent(hDlg), NULL, NULL, RDW_INTERNALPAINT);
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
