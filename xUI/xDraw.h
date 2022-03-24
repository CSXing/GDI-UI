#ifndef _xWinForm_BaseDraw_Head_
#define _xWinForm_BaseDraw_Head_

    /*=====================================================================*/
    class xWF_Draw;
    class xWF_Draw
    {
    protected: //�ڲ�����
        HDC hMemDC, hDC;
        HBITMAP hBMP, hPrevBmp;
        int _width, _height, _alpCount;

        HDC hMemDC_RC;
        HBITMAP hBMP_RC, hPrevBMP_RC;
        HFONT hFont_RC, hPrevFont_RC;
    private:
        bool _Stroked; //���
        char _Name[32];
        int _Size, _Bold;

        BYTE  txtR,  txtG,  txtB,  txtA
            , grdR,  grdG,  grdB,  grdA
            , fraR,  fraG,  fraB,  fraA
            , bgR,   bgG,   bgB,   bgA
            , alpR[256], alpG[256], alpB[256], alpA[256]
        ;
        xWF_tagRect_Alpha aRc[10];
        int _aRcCount;
    public:
        xWF_Draw() {
            this->hDC = this->hMemDC = this->hMemDC_RC = 0;
            this->hBMP = this->hPrevBmp = this->hBMP_RC = this->hPrevBMP_RC = 0;
            this->_alpCount= 0;
            this->_aRcCount= 0;
            this->_width   = 800;
            this->_height  = 600;
            this->_Stroked = false;
            this->_Size    = 0;
        }
        ~xWF_Draw() {
            if(this->hPrevBMP_RC) DeleteObject(this->hPrevBMP_RC);
            if(this->hBMP_RC)     DeleteObject(this->hBMP_RC);
            if(this->hMemDC_RC)   DeleteDC(this->hMemDC_RC);

            if(this->hPrevBmp) DeleteObject(this->hPrevBmp);
            if(this->hBMP)     DeleteObject(this->hBMP);
            if(this->hMemDC)   DeleteDC(this->hMemDC);
        }
        void Alpha(bool Clear=true);
        void Alpha(int x, int y, int w, int h, bool alpha=true);
        bool bInitOk(){
            if( !this->hDC)     return false;
            if( !this->hMemDC ) return false;
            if( !this->hBMP )   return false;
            return true;
        };
        HDC gMemDC() { return this->hMemDC; };
        // ��Χ
        int Height() { return this->_height; };
        int Width()  { return this->_width;  };
        // �ж���ɫֵ�Ƿ���͸��ɫ
        unsigned char isAlpha(BYTE r, BYTE g, BYTE b, BYTE a);
        // �����ڴ滭��
        bool Create(int width=1024, int height=768, bool bStroked=false, COLORREF bgColor=0, COLORREF alphaColor=0x030201);
        void Clear();
        void Refresh(HDC hDst, HDC hDstMem,int x=0, int y=0, int xSrc=0, int ySrc=0);
        void CopyTo(HDC hDst,int x=0, int y=0, int xSrc=0, int ySrc=0);
        // ����ͼƬ
        IPicture *LoadImage(char *arrImage, int sizeImage);

        //����������ɫ�м��ֵ
        void gPercent(BYTE *ret, BYTE *_FstRGB, BYTE *_EndRGB, float _Per=1.0f);
        void gPercent(BYTE *ret, BYTE _fR, BYTE _fG, BYTE _fB,
                                 BYTE _eR, BYTE _eG, BYTE _eB, float _Per=1.0f);
        // ��������
        void Font(int Size=10, int Bold=FW_BOLD, char *Name="MS Sans Serif");

        // ���û�����ɫ
        void Color(BYTE colorid, DWORD rgb, BYTE a=0xFF);
        void Color(BYTE colorid, BYTE r, BYTE g, BYTE b, BYTE a=0xFF);
        // ��ͼ��
        void gdi_icon(int x, int y, HICON hIcon, int cxWidth, int cyHeight);
        void gdi_image(int x, int y, HBITMAP hImage, int cxWidth, int cyHeight);
        // ������
        void gdi_box(int x, int y, int w, int h);
        void gdi_box(int x, int y, int w, int h, BYTE smooth, BYTE fill=0);
        // ����� ��ɫ
        void gdi_fill(int x, int y, int w, int h, BYTE fill=1);
        // ������
        void gdi_line(int X1, int Y1, int X2, int Y2, int lineWidth=1);
        void gdi_line(int X1, int Y1, int X2, int Y2, BYTE r, BYTE g, BYTE b, int lineWidth=1);
        // ���ı�
        int  gdi_text(int x, int y, char *str, int Align=0, int w=0, int h=0, bool bFill=false);
        // ����
        long gdi_point(int x, int y, int *rgb);
        long gdi_point(int x, int y, BYTE *rgb);
        long gdi_point(int x, int y, DWORD Color);

        void gdi_getTextRCBegin();
        bool gdi_getTextRC(char * str, int *w, int *h);
        void gdi_getTextRCEnd();
    };
#endif

bool getBitsTo32(HDC srcDC, HBITMAP srcBMP, BITMAPINFO *Info, unsigned char *retDatas, unsigned int *retSize);