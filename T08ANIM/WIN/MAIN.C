/* FILE NAME: MAIN.C
 * PROGRAMMER: EN5
 * DATE: 06.06.2020
 * PURPOSE: 3D animation project.
 */
#include <time.h>

#include "../def.h"
#include "../anim/rnd/rnd.h"

/* My window class */
#define WND_CLASS_NAME "My window class"

LRESULT CALLBACK WinFunc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam );

/* The main program function.
 * ARGUMENTS:
 *   - handle of application instance:
 *       HINSTANCE hInstance;
 *   - dummy handle of previous application instance (not used):
 *       HINSTANCE hPrevInstance;
 *   - command line string:
 *       CHAR *CmdLine;
 *   - show window command parameter (see SW_***):
 *       INT CmdShow;
 * RETURNS:
 *   (INT) Error level for operation system (0 for success).
 */
INT WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, CHAR *CmdLine, INT CmdShow )
{
  HWND hWnd;
  MSG msg;
  WNDCLASS wc;

  wc.style = CS_VREDRAW | CS_HREDRAW;
  wc.cbClsExtra = 0;
  wc.cbWndExtra = 0;
  wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
  wc.hCursor = LoadIcon(NULL, IDI_HAND);
  wc.hIcon = LoadIcon(NULL, IDI_ASTERISK);
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

  while (TRUE)
  if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
  {
    if (msg.message == WM_QUIT)
      break;
    DispatchMessage(&msg);
  }
  else
    SendMessage(hWnd, WM_TIMER, 30, 0);

  return 0;
} /* End of 'WinMain' function */

/* Main window message handle function.
 * ARGUMENTS:
 *   - window handle:
 *       HWND hWnd;
 *   - dummy handle of previous application instance (not used):
 *       HINSTANCE hPrevInstance;
 *   - command line string:
 *       CHAR *CmdLine;
 *   - show window command parameter (see SW_***):
 *       INT CmdShow;
 * RETURNS:
 *   (INT) DefWindowProc(hWnd, Msg, wParam, lParam).
 */
LRESULT CALLBACK WinFunc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam )
{
  HDC hDC;
  PAINTSTRUCT ps;
  static en5PRIM Pr;

  switch (Msg)
  {
  case WM_GETMINMAXINFO:
    ((MINMAXINFO *)lParam)->ptMaxTrackSize.y =
      GetSystemMetrics(SM_CYMAXTRACK) + GetSystemMetrics(SM_CYCAPTION) + 2 * GetSystemMetrics(SM_CYBORDER);
    return 0;
  case WM_CREATE:
    EN5_RndInit(hWnd);
    EN5_RndPrimCreateSphere(&Pr, VecSet(1, 1, 0), 2, 30, 30);

    SetTimer(hWnd, 30, 1, NULL);
    return 0;
  case WM_TIMER:
    EN5_RndStart();
    EN5_RndPrimDraw(&Pr, MatrRotateY(30 * clock() / 1000.0));
    EN5_RndEnd();
    hDC = GetDC(hWnd);
    EN5_RndCopyFrame(hDC);

    InvalidateRect(hWnd, NULL, FALSE);
    return 0;
  case WM_ERASEBKGND:
    return 1;
  case WM_SIZE:
    EN5_RndResize(LOWORD(lParam), HIWORD(lParam));

    SendMessage(hWnd, WM_TIMER, 0, 0);
    return 0;
  case WM_KEYDOWN:
    if (wParam == VK_ESCAPE)
      SendMessage(hWnd, WM_CLOSE, 0, 0);
    return 0;
  case WM_PAINT:
    hDC = BeginPaint(hWnd, &ps);
    EN5_RndCopyFrame(hDC);
    EndPaint(hWnd, &ps);
    return 0;
  case WM_CLOSE:
    if (MessageBox(hWnd, "Are you sure?", "Close",
      MB_YESNO | MB_DEFBUTTON2 | MB_ICONQUESTION) == IDYES)
      DestroyWindow(hWnd);
    return 0;
  case WM_DESTROY:
    EN5_RndPrimFree(&Pr);
    EN5_RndClose();
    KillTimer(hWnd, 30);
    PostMessage(hWnd, WM_QUIT, 0, 0);
    return 0;
  }
  return DefWindowProc(hWnd, Msg, wParam, lParam);
} /* End of 'WinFunc' function */

/* END OF 'MAIN.C' FILE */