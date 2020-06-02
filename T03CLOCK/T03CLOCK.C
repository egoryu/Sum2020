/* Nikitin Egor, 02.06.2020 */

#include <windows.h>
#include <math.h>
#include <stdlib.h>

#define WND_CLASS_NAME "My window class"
#define PI 3.14159265358979323846

LRESULT CALLBACK WinFunc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam );
VOID DrawEye( HDC hDC, INT X, INT Y, INT R1, INT R2, INT Mx, INT My );
VOID DrawClockface( HDC hDC, INT X, INT Y, INT R, DOUBLE Angle1, DOUBLE Angle2, DOUBLE Angle3 );
VOID DrawPolygon( HDC hDC, INT xc, INT yc, INT len1, INT len2, INT len3, INT len4, DOUBLE alpha, COLORREF Color );
VOID FlipFullScreen( HWND hWnd );

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
  static HDC hMemDC, hMemDCImage, hMemDCSprit;
  static HBITMAP hBm, hBmImage, hBmAnd, hBmXor;
  static BITMAP bm, bm1;
  SYSTEMTIME st;
  DOUBLE Angle1, Angle2, Angle3;
  INT r, len;
  HFONT hFnt, hFntOld;
  CHAR Buf[102];
  RECT rc;
  static CHAR *WD[] =
  {
    "вс", "пн", "вт", "ср", "чт", "пт", "сб"
  };

  switch (Msg)
  {
  case WM_GETMINMAXINFO:
    ((MINMAXINFO *)lParam)->ptMaxTrackSize.y =
      GetSystemMetrics(SM_CYMAXTRACK) + GetSystemMetrics(SM_CYCAPTION) + 2 * GetSystemMetrics(SM_CYBORDER);
    return 0;
  case WM_CREATE:
    hDC = GetDC(hWnd);
    hBmImage = LoadImage(NULL, "clockface.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    hBmAnd = LoadImage(NULL, "pt_and.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    hBmXor = LoadImage(NULL, "pt_xor.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    hMemDC = CreateCompatibleDC(hDC);
    hMemDCSprit = CreateCompatibleDC(hDC);
    hMemDCImage = CreateCompatibleDC(hDC);
    ReleaseDC(hWnd, hDC);
    hBm = NULL;
    SelectObject(hMemDCImage, hBmImage);

    SetTimer(hWnd, 30, 102, NULL);
    return 0;
  case WM_TIMER:
    GetLocalTime(&st);
    Angle1 = (st.wSecond + st.wMilliseconds / 1000.0) * 2 * PI / 60.0;
    Angle2 = (st.wMinute + st.wSecond / 60.0) * 2 * PI / 60.0;
    Angle3 = (st.wHour % 12 + st.wMinute / 60.0) * 2 * PI / 12.0;

    SetDCBrushColor(hMemDC, RGB(0, 0, 200));
    SetDCPenColor(hMemDC, RGB(120, 60, 200));
    Rectangle(hMemDC, 0, 0, w, h);

    r = w < h ? w : h;
    GetObject(hBmImage, sizeof(BITMAP), &bm);
    //BitBlt(hMemDC, 0, 0, bm.bmWidth, bm.bmHeight, hMemDCImage, 0, 0, SRCCOPY)
    SetStretchBltMode(hMemDC, COLORONCOLOR);
    StretchBlt(hMemDC, w / 2 - r / 2, h / 2 - r / 2, r, r, hMemDCImage, 0, 0, bm.bmWidth, bm.bmHeight, SRCCOPY);
    DrawClockface(hMemDC, w / 2, h / 2, r / 2, Angle1, Angle2, Angle3);

    /* draw text */
    hFnt = CreateFont(r / 8, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
             RUSSIAN_CHARSET,
             OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY,
             FF_SWISS | VARIABLE_PITCH, "Consolas");
    hFntOld = SelectObject(hMemDC, hFnt);
    len = wsprintf(Buf, "%02i.%02i.%i\n(%s)",
            st.wDay, st.wMonth, st.wYear, WD[st.wDayOfWeek]);

    SetBkMode(hMemDC, TRANSPARENT);
    SetTextColor(hMemDC, RGB(120, 255, 50));
    rc.left = 0;
    rc.right = w;
    rc.top = 3 * h / 4;
    rc.bottom = h;
    DrawText(hMemDC, Buf, len, &rc, DT_VCENTER);

    SelectObject(hMemDC, hFntOld);
    DeleteObject(hFnt);

    /* Draw sprite */
    GetObject(hBmAnd, sizeof(BITMAP), &bm1);
    SelectObject(hMemDCSprit, hBmAnd);
    SetStretchBltMode(hMemDC, COLORONCOLOR);
    //BitBlt(hMemDC, x - bm1.bmWidth / 2, y - bm1.bmHeight / 2, bm1.bmWidth, bm1.bmHeight, hMemDCSprit, 0, 0, SRCAND);
    StretchBlt(hMemDC, x - bm1.bmWidth / 16, y - bm1.bmHeight / 16, bm1.bmWidth / 8, bm1.bmHeight / 8, hMemDCSprit, 0, 0, bm1.bmWidth, bm1.bmHeight, SRCAND);

    SelectObject(hMemDCSprit, hBmXor);
    //BitBlt(hMemDC, x - bm1.bmWidth / 2, y - bm1.bmHeight / 2, bm1.bmWidth, bm1.bmHeight, hMemDCSprit, 0, 0, SRCINVERT);
    StretchBlt(hMemDC, x - bm1.bmWidth / 16, y - bm1.bmHeight / 16, bm1.bmWidth / 8, bm1.bmHeight / 8, hMemDCSprit, 0, 0, bm1.bmWidth, bm1.bmHeight, SRCINVERT);

    InvalidateRect(hWnd, NULL, FALSE);
    return 0;
  case WM_SIZE:
    w = LOWORD(lParam);
    h = HIWORD(lParam);

    if (hBm != NULL)
      DeleteObject(hBm);
    hDC = GetDC(hWnd);
    hBm = CreateCompatibleBitmap(hDC, w, h);
    ReleaseDC(hWnd, hDC);
    SelectObject(hMemDC, hBm);

    SendMessage(hWnd, WM_TIMER, 0, 0);
    return 0;
  case WM_MOUSEMOVE:
    x = LOWORD(lParam);
    y = HIWORD(lParam);
  case WM_SYSKEYDOWN:
    if ((GetAsyncKeyState(VK_MENU) & 0x8000) != 0 && wParam == VK_RETURN)
      FlipFullScreen(hWnd);
    return 0;
  case WM_KEYDOWN:
    if (wParam == VK_ESCAPE)
      SendMessage(hWnd, WM_CLOSE, 0, 0);
    return 0;
  case WM_PAINT:
    hDC = BeginPaint(hWnd, &ps);
    BitBlt(hDC, 0, 0, w, h, hMemDC, 0, 0, SRCCOPY);
    EndPaint(hWnd, &ps);
    return 0;
  case WM_CLOSE:
    if (MessageBox(hWnd, "Are you sure?", "Close",
      MB_YESNO | MB_DEFBUTTON2 | MB_ICONQUESTION) == IDYES)
      DestroyWindow(hWnd);
    return 0;
  case WM_DESTROY:
    if (hBm != NULL)
      DeleteObject(hBm);
    DeleteDC(hMemDC);
    DeleteDC(hMemDCSprit);
    DeleteDC(hMemDCImage);
    DeleteObject(hBmImage);
    DeleteObject(hBmAnd);
    DeleteObject(hBmXor);
    PostMessage(hWnd, WM_QUIT, 0, 0);
    KillTimer(hWnd, 30);
    return 0;
  }
  return DefWindowProc(hWnd, Msg, wParam, lParam);
} /* End of 'WinFunc' function */

/* Draw Clockface function */
VOID DrawClockface( HDC hDC, INT X, INT Y, INT R, DOUBLE Angle1, DOUBLE Angle2, DOUBLE Angle3 )
{
  /* second hand */
  /*hPen = CreatePen(PS_SOLID, 4, RGB(120, 120, 120));
  hOldPen = SelectObject(hDC, hPen);

  MoveToEx(hDC, X, Y, NULL);
  LineTo(hDC, X + R * sin(Angle1), Y - R * cos(Angle1));

  SelectObject(hDC, hOldPen);
  DeleteObject(hPen); */
  DrawPolygon(hDC, X, Y, R / 15, 0.6 * R, R / 10, R / 10, Angle1, RGB(0, 230, 120));

  /* minut hand */
  DrawPolygon(hDC, X, Y, R / 10, 0.47 * R, R / 10, R / 10, Angle2, RGB(120, 230, 0));

  /* house hand */
  DrawPolygon(hDC, X, Y, R / 8, 0.3 * R, R / 10, R / 10, Angle3, RGB(120, 230, 120));

} /* End of 'DrawClockface' function */

/* Draw Clockhand function */
VOID DrawPolygon( HDC hDC, INT xc, INT yc, INT len1, INT len2, INT len3, INT len4, DOUBLE alpha, COLORREF Color )
{
  POINT pnts[7];
  POINT pnts1[sizeof(pnts) / sizeof(pnts[0])];
  INT i;

  pnts[0].x = len1, pnts[0].y = 0;
  pnts[1].x = -len1, pnts[1].y = 0;
  pnts[2].x = -len1, pnts[2].y = -len2;
  pnts[3].x = -len1 - len3, pnts[3].y = -len2;
  pnts[4].x = 0, pnts[4].y = -len2 - len4;
  pnts[5].x = len3 + len1, pnts[5].y = -len2;
  pnts[6].x = len1, pnts[6].y = -len2;
  for (i = 0; i < 7; i++)
  {
    pnts1[i].x = xc + pnts[i].x * cos(alpha) - pnts[i].y * sin(alpha);
    pnts1[i].y = yc + pnts[i].x * sin(alpha) + pnts[i].y * cos(alpha);
  }
  SelectObject(hDC, GetStockObject(DC_PEN));
  SelectObject(hDC, GetStockObject(DC_BRUSH));

  SetDCBrushColor(hDC, Color);
  SetDCPenColor(hDC, Color);
  Polygon(hDC, pnts1, 7);
} /* End of 'DrawPolygon' function */

/* Toggle window fullscreen mode function */
VOID FlipFullScreen( HWND hWnd )
{
  static BOOL IsFullScreen = FALSE;
  static RECT SaveRect;

  IsFullScreen = !IsFullScreen;
  if (!IsFullScreen)
  {
    HMONITOR hmon;
    MONITORINFO moninfo;
    RECT rc;

    /* Goto fullscreen mode */
    GetWindowRect(hWnd, &SaveRect);

    /* Get nearest monitor */
    hmon = MonitorFromWindow(hWnd, MONITOR_DEFAULTTONEAREST);

    /* Get monitor information */
    moninfo.cbSize = sizeof(moninfo);
    GetMonitorInfo(hmon, &moninfo);

    rc = moninfo.rcMonitor;
    AdjustWindowRect(&rc, GetWindowLong(hWnd, GWL_STYLE), FALSE);
    SetWindowPos(hWnd, HWND_TOP,
      rc.left, rc.top,
      rc.right - rc.left, rc.bottom - rc.top,
      SWP_NOOWNERZORDER);
  }
  else
  {
    /* Restore window size and position */
    SetWindowPos(hWnd, HWND_TOP,
      SaveRect.left, SaveRect.top,
      SaveRect.right - SaveRect.left, SaveRect.bottom - SaveRect.top,
      SWP_NOOWNERZORDER);
  }
} /* End of 'FlipFullScreen' function */

/* END OF 'T03CLOCK.C' FILE */