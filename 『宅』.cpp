#include "『宅』.h"

HANDLE hMutexExe;
char exeTitle[256]="『宅』CStrike注入器[v15]";

unsigned int __stdcall Refresh   (void* pArguments);

HICON hMainIco=NULL;
HWND  hWnd=NULL;
xWF_Form  *Face=NULL;
LRESULT CALLBACK LoaderDialog( HWND hDlg, UINT Msg, WPARAM wParam, LPARAM lParam );

//NOTIFYICONDATA trayIcon;
//#define WM_TRAY ( WM_USER+617 )
//==================================================================================
//void ShowTrayInfo(const char * Info)
//{
//    pubLock.Enter();
//    trayIcon.dwInfoFlags = NIIF_INFO;
//    sprintf( trayIcon.szInfo, Info);
//    Shell_NotifyIcon(NIM_MODIFY, &trayIcon);
//    pubLock.Leave();
//}
//void ShowTrayWarning(const char * Info)
//{
//    pubLock.Enter();
//    trayIcon.dwInfoFlags = NIIF_WARNING;
//    sprintf( trayIcon.szInfo, Info);
//    Shell_NotifyIcon(NIM_MODIFY, &trayIcon);
//    pubLock.Leave();
//}
//void ShowTrayError(const char * Msg)
//{
//    pubLock.Enter();
//    trayIcon.dwInfoFlags = NIIF_ERROR;
//    sprintf( trayIcon.szInfo, Msg);
//    Shell_NotifyIcon(NIM_MODIFY, &trayIcon);
//    pubLock.Leave();
//}

VOID CALLBACK AppClose()
{
    zHAi_Quit(0);
}

//==================================================================================
//==================================================================================
INT WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, INT nShowCmd )
{
    hMainIco = LoadIcon(hInstance, MAKEINTRESOURCE(IDR_MAINFRAME));

    /* 『宅』标题内容 */
    Face=new xWF_Form();
    Face->Title("登录");
    Face->Button(true,true,true);
    Face->Icon((HICON)LoadImage(hInstance, MAKEINTRESOURCE(IDR_MAINFRAME), IMAGE_ICON, 16, 16, LR_DEFAULTCOLOR));
    //Face->Background((HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(IDB_BITMAP), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION));
    Face->BindOnClick(xWF::SysBtns::Close, &AppClose);

    //// inintialize tray icon
    //trayIcon.cbSize   = sizeof( NOTIFYICONDATA );
    //trayIcon.uCallbackMessage = WM_TRAY;
    //trayIcon.uFlags      = NIF_MESSAGE | NIF_ICON | NIF_TIP | NIF_INFO;
    //trayIcon.dwInfoFlags = NIIF_INFO;
    //trayIcon.uID         = 1;
    //trayIcon.uTimeout    = 10;
    //trayIcon.hIcon       = Face->hIcon;
    ///* 『宅』v5.x */
    //sprintf( trayIcon.szInfoTitle, XorStr<0x7E, 11, 0x560B3349>("\xDF\xC5\x55\x2D\x23\x38\xF2\xB0\xA8\xFF"+0x560B3349).s);
    ///* 欢迎使用『宅』辅助工具
    //   购买请联系企鹅: 910955951。 */
    //sprintf( trayIcon.szTip,
    //    XorStr<0x67, 52, 0x4FB1A1D1>("\xDC\xDE\xBA\xC7\xA1\xD5\xBE\xAD\xCE\xCA\xA4\xDE\xD2\xCF\xCD\xDE\xA1\x82\xC0\xDE\xC5\xA3\x70\x74\xC6\x3A\x43\x70\x44\x6F\x44\x2C\x48\x3D\x4F\x79\x3D\x60\xB7\xAE\xB6\xA1\xA1\xAB\xA6\xA1\xAC\xA3\xA6\x39\x3A"+0x4FB1A1D1).s
    //);

    // 创建主窗口
    DialogBox( hInstance, MAKEINTRESOURCE(IDD_DIALOG), NULL, (DLGPROC)LoaderDialog );
    
    return TRUE;
}

//==================================================================================
BOOL m_bTracking = FALSE;
LRESULT CALLBACK LoaderDialog( HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam )
{ 
    int iX_Screen, iY_Screen, iH_Title, x, y, h, w;
    RECT rect, ClientRect;
    PAINTSTRUCT ps;

    switch ( uMsg )
    {
    case WM_CREATE:
    case WM_INITDIALOG:
        {
            if (hWnd==NULL) {
                hWnd = hDlg;
                //trayIcon.hWnd = hDlg;
                //Shell_NotifyIcon( NIM_ADD, &trayIcon );
            }

            SetClassLong(hDlg,GCL_HICON,(LONG)hMainIco);
            SetWindowText(hDlg, exeTitle);
            iX_Screen = GetSystemMetrics(SM_CXFULLSCREEN);
            iY_Screen = GetSystemMetrics(SM_CYFULLSCREEN);
            iH_Title  = GetSystemMetrics(SM_CYCAPTION);
            
            GetWindowRect(hDlg,&rect);
                w = rect.right-rect.left;
                h = rect.bottom-rect.top;
                x = (iX_Screen - w-3);
                y = (iY_Screen + iH_Title - h);

                x = (iX_Screen - w)/2;
                y = (iY_Screen - h)/2 - iH_Title;
            //GetClientRect( hDlg, &ClientRect );

            //移动位置
            SetWindowPos(hDlg, NULL, x, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

            //HANDLE hThread3 = (HANDLE)_beginthreadex(NULL, NULL, &Refresh, NULL, NULL, NULL);
            //HANDLE hThread3 = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)Refresh, NULL, NULL, NULL);
            //CloseHandle(hThread3);
            break;
        }
        
    case WM_DESTROY:
        {
            delete Face;
            return FALSE;
            break;
        }
    }
    return Face->CallbackDialog(hDlg, uMsg, wParam, lParam);
}

/* ===============================================
                退出进程处理程序
=============================================== */
void zHAi_Quit(float flSleep)
{
    if (flSleep>0.0f) {
        int iRunNo=flSleep*75;
        while (iRunNo>0){
            Face->Refresh();
            iRunNo--;
            Sleep(10);
        }
    }
    while (true) {
        HANDLE hself = GetCurrentProcess();
        TerminateProcess(hself, 0);
        ExitProcess(0);
        exit(0);
        Sleep(50);
    }
    int iOver=(int)(0.00001f*0.00009f);
    iOver = (int)(987654*0.0000001) / iOver;
}
/* ===============================================
                刷新界面处理程序
=============================================== */
unsigned int __stdcall Refresh(void* pArguments)
{
    while(true){
        Face->Refresh();
        Sleep(100);
    }
    return 0;
}