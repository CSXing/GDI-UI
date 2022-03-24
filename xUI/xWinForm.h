#ifndef _xWF_Forms_Main_Head_
#define _xWF_Forms_Main_Head_
    /*=====================================================================*/
    class xWF_Form;
    class xWF_Form
    {
    private:
        /* 窗口句柄 */
        HWND    _hWnd;
        HDC     _hDC; 
        HBITMAP _hBmpDC;
        int ScreenWidth, ScreenHeight, TitleBarHeight;
        /* 窗口坐标 */
        xWF_tagRect
            _rcMain,  /* 窗口整体 */
            _rcFrame, /* 边框 */
            _rcTitle, /* 标题栏 */
            _rcIcon,  /* 图标 */
            _rcMin,   /* 最小化按钮 */
            _rcMax,   /* 最大化按钮 */
            _rcClose, /* 关闭按钮 */
            _rcClient;/* 客户区 */
        /* 窗口按钮 */
        BYTE _sysbtns;
        /* 鼠标位置 */
        USHORT _mousefrist, _mouse;
        /* 图标 */
        HICON _hIcon;
        /* 背景图 */
        HBITMAP _hBgImage;
        /* 标题 */
        char _caption[999];
        /* 字体 */
        char _fontname[256];
         int _fontsize, _fontbold;
        /* 画图对象 */
        xWF_Draw *base;
        /* 事件继承 */
        tEvent_OnClick 
            _funcClick_Close
            ;
        BOOL _bTracking,
            /* 鼠标在窗口上 */
            _bMouseIn;

        CLocks *Lock;

        /* 窗口整体 */
        void DrawFroms();
        /* 最小化标题栏 */
        void DrawMinTitlebar(BYTE *clrTx, BYTE *clrFra, BYTE *clrBg, BYTE *clrSd);
        /* 事件反馈 */
        void onEvents(int x, int y,BYTE mouse);
    public:
        xWF_Form();
        ~xWF_Form();
        
        /* 背景图 */
        void Background(HBITMAP Image);
        /* 绑定到场景 */
        void Bind(HWND hWnd, int Width, int Height);
        /* 绑定事件 */
        void BindOnClick(int Button, tEvent_OnClick CallbackFunc);
        void BindOnMouse(int Button, tEvent_OnMouse CallbackFunc);
        /* 窗口按钮 */
        void Button(bool btnMin, bool btnMax, bool btnClose);

        /* 字体 */
        void Font(int Size=10, int Bold=FW_NORMAL, char *Name="MS Sans Serif");
        /* 图标 */
        void Icon(HICON Image);
        /* 窗口标题 */
        void Title(char *Text);
        
        /* 刷新 */
        void Refresh();
    public:
        LRESULT CALLBACK CallbackDialog( HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam );
    };
#endif