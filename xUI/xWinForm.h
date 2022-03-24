#ifndef _xWF_Forms_Main_Head_
#define _xWF_Forms_Main_Head_
    /*=====================================================================*/
    class xWF_Form;
    class xWF_Form
    {
    private:
        /* ���ھ�� */
        HWND    _hWnd;
        HDC     _hDC; 
        HBITMAP _hBmpDC;
        int ScreenWidth, ScreenHeight, TitleBarHeight;
        /* �������� */
        xWF_tagRect
            _rcMain,  /* �������� */
            _rcFrame, /* �߿� */
            _rcTitle, /* ������ */
            _rcIcon,  /* ͼ�� */
            _rcMin,   /* ��С����ť */
            _rcMax,   /* ��󻯰�ť */
            _rcClose, /* �رհ�ť */
            _rcClient;/* �ͻ��� */
        /* ���ڰ�ť */
        BYTE _sysbtns;
        /* ���λ�� */
        USHORT _mousefrist, _mouse;
        /* ͼ�� */
        HICON _hIcon;
        /* ����ͼ */
        HBITMAP _hBgImage;
        /* ���� */
        char _caption[999];
        /* ���� */
        char _fontname[256];
         int _fontsize, _fontbold;
        /* ��ͼ���� */
        xWF_Draw *base;
        /* �¼��̳� */
        tEvent_OnClick 
            _funcClick_Close
            ;
        BOOL _bTracking,
            /* ����ڴ����� */
            _bMouseIn;

        CLocks *Lock;

        /* �������� */
        void DrawFroms();
        /* ��С�������� */
        void DrawMinTitlebar(BYTE *clrTx, BYTE *clrFra, BYTE *clrBg, BYTE *clrSd);
        /* �¼����� */
        void onEvents(int x, int y,BYTE mouse);
    public:
        xWF_Form();
        ~xWF_Form();
        
        /* ����ͼ */
        void Background(HBITMAP Image);
        /* �󶨵����� */
        void Bind(HWND hWnd, int Width, int Height);
        /* ���¼� */
        void BindOnClick(int Button, tEvent_OnClick CallbackFunc);
        void BindOnMouse(int Button, tEvent_OnMouse CallbackFunc);
        /* ���ڰ�ť */
        void Button(bool btnMin, bool btnMax, bool btnClose);

        /* ���� */
        void Font(int Size=10, int Bold=FW_NORMAL, char *Name="MS Sans Serif");
        /* ͼ�� */
        void Icon(HICON Image);
        /* ���ڱ��� */
        void Title(char *Text);
        
        /* ˢ�� */
        void Refresh();
    public:
        LRESULT CALLBACK CallbackDialog( HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam );
    };
#endif