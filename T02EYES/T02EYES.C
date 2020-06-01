/* Nikitin Egor, 01.06.2020 */

#include <windows.h>
#include <math.h>
#include <stdlib.h>

#define WND_CLASS_NAME "My window class"

LRESULT CALLBACK WinFunc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam );
VOID DrawEye( HDC hDC, INT X, INT Y, INT R1, INT R2, INT Mx, INT My );

/* Main program function */
INT WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, CHAR *CmdLine, INT CmdShow )
{
  HWND hWnd;
  MSG msg;
  WNDCLASS wc;

  wc.style = CS_VREDRAW | CS_HREDRAW;
  wc.cbClsExtra = 0;
  wc.cbWndExtra = 0;
  wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
  wc.hCursor = LoadIcon(NULL, IDI_ERROR);
  wc.hIcon = LoadIcon(NULL, IDI_SHIELD);
  wc.lpszMenuName = NULL;
  wc.hInstance = hInstance;
  wc.lpfnWndProc = WinFunc;
  wc.lpszClassName = WND_CLASS_NAME;

  if (!RegisterClass(&wc))
  {
    MessageBox(NULL, "Error regisrer window class", "ERROR", MB_OK);
    return 0;
  }

  hWnd = CreateWindow(WND_CLASS_NAME, "EN5", WS_OVERLAPPEDWINDOW,
    CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
    NULL, NULL, hInstance, NULL);

  ShowWindow(hWnd, SW_SHOWNORMAL);

  while (GetMessage(&msg, NULL, 0, 0))
    DispatchMessage(&msg);

  return 30;
} /* End of 'WinMain' function */

/* Main window message handle function */
LRESULT CALLBACK WinFunc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam )
{
  HDC hDC;
  PAINTSTRUCT ps;
  static INT w, h, x, y;

  switch (Msg)
  {
  case WM_CREATE:
    SetTimer(hWnd, 30, 102, NULL);
    return 0;
  case WM_TIMER:
    InvalidateRect(hWnd, NULL, TRUE);
    return 0;
  case WM_SIZE:
    w = LOWORD(lParam);
    h = HIWORD(lParam);
    return 0;
  case WM_MOUSEMOVE:
    x = LOWORD(lParam);
    y = HIWORD(lParam);
  case WM_PAINT:
    hDC = BeginPaint(hWnd, &ps);
    DrawEye(hDC, w / 2, h / 2, 80, 20, x, y);
    EndPaint(hWnd, &ps);
    return 0;
  case WM_CLOSE:
    if (MessageBox(hWnd, "Are you sure?", "Close",
      MB_YESNO | MB_DEFBUTTON2 | MB_ICONQUESTION) == IDYES)
      DestroyWindow(hWnd);
    return 0;
  case WM_DESTROY:
    PostMessage(hWnd, WM_QUIT, 0, 0);
    KillTimer(hWnd, 30);
    return 0;
  }
  return DefWindowProc(hWnd, Msg, wParam, lParam);
} /* End of 'WinFunc' function */

/* Draw eye function */
VOID DrawEye( HDC hDC, INT X, INT Y, INT R1, INT R2, INT Mx, INT My )
{
  INT A, B, C;

  if (R1 < R2)
    return;
  SelectObject(hDC, GetStockObject(DC_PEN));
  SelectObject(hDC, GetStockObject(DC_BRUSH));
  SetDCBrushColor(hDC, RGB(255, 255, 255));
  Ellipse(hDC, X - R1, Y + R1, X + R1, Y - R1);
  SetDCBrushColor(hDC, RGB(0, 100, 150));

  if ((X - Mx) * (X - Mx) + (Y - My) * (Y - My) < (R1 - R2) * (R1 - R2))
    Ellipse(hDC, Mx - R2, My + R2, Mx + R2, My - R2);
  else
  {
    A = (INT)sqrt((Mx - X) * (Mx - X) + (My - Y) * (My - Y));
    B = (R1 - R2) * (Mx - X) / A;
    C = (R1 - R2) * (My - Y) / A;

    Ellipse(hDC, X + B - R2, Y + C + R2, X + B + R2, Y + C - R2);
  }
} /* End of 'DrawEye' function */

/* END OF 'T02EYES.C' FILE */