/********************************************************
Create: 2019.12.02
Editor: 2022-03-15
==============================
  Version: 1.0.2022
   Author: X!ng,cHEn ��լ��910955951
Copyright: 2019 - 2020(C)
==============================
Description:
      ���ڱ��������ƹ���
********************************************************/
#include "zHAi_WF.h"

xWF_Form::xWF_Form(){
    this->Font(11, 500);

    /* �������� */
    this->_rcMain.l  = 0;
    this->_rcMain.t  = 0;

    this->_rcFrame.Set(5,5);

    sprintf_s(this->_caption, "��լ���Ի�ؼ�v1");
    this->_bTracking = 0;
    this->_mousefrist= 0;
    this->_mouse     = 0;

    /* ���ڰ�ť */
    this->_sysbtns  = xWF::SysBtns::Title | xWF::SysBtns::Icon | xWF::SysBtns::Close;
    /* ͼ�� */
    this->_hBgImage = 0;
    this->_hIcon    = 0;
    /* ���ھ�� */
    this->_hWnd   = 0;
    this->_hDC    = 0;
    this->_hBmpDC = 0;
    /* �¼��̳� */
    this->_funcClick_Close = 0;

    this->base = new xWF_Draw();
    this->Lock = new CLocks();
}
xWF_Form::~xWF_Form()
{
    delete this->base;
    delete this->Lock;
    //delete this->client;
    //delete this->myLock;
    if (this->_hBmpDC) DeleteObject(this->_hBmpDC);
    if (this->_hDC) DeleteDC(this->_hDC);
}

/* ����ͼ */
void xWF_Form::Background(HBITMAP Image)
{
    this->_hBgImage = Image;
}
/*===========================================================
            ����: Bind
            ����: hWnd=���ھ����width=��ȣ�height=�߶�
            ����: �󶨵����ھ��
  ===========================================================*/
void xWF_Form::Bind(HWND hWnd, int Width, int Height)
{
    if (Width<this->TitleBarHeight*8)   Width = this->TitleBarHeight*8;
    if (Height<this->TitleBarHeight+4) Height = this->TitleBarHeight+4;

    this->_hWnd  = hWnd;
    this->_rcMain.Set(Width, Height);

// ������ ====================================================================
    if (xWF::isEqual(this->_sysbtns, xWF::SysBtns::Title)){
        this->_rcTitle.Set(
            this->_rcFrame.w/2,
            this->_rcFrame.h/2,
            Width-this->_rcFrame.w*2, 26);
    }
// ϵͳ��ť =====================================================================
    int x = this->_rcMain.r - this->_rcFrame.w*2;
    //ͼ��
    if (xWF::isEqual(this->_sysbtns, xWF::SysBtns::Icon)){
        this->_rcIcon.Set( 
            (this->_rcTitle.b - 16)/2, 
            (this->_rcTitle.b - 16)/2,
            16, 16);
    }
    //�ر�
    if (xWF::isEqual(this->_sysbtns, xWF::SysBtns::Close)){
        this->_rcClose.Set(40, this->_rcTitle.h - 4);
        x -= this->_rcClose.w;
        this->_rcClose.l = x;
        this->_rcClose.Calc();
    } else {
        this->_rcClose.Set(-1, -1);
    }
    //���
    if (xWF::isEqual(this->_sysbtns, xWF::SysBtns::Max)){
        this->_rcMax.Set(30, this->_rcTitle.h - 4);
        x -= this->_rcMax.w;
        if (this->_rcClose.w!=0) x += 3;
        this->_rcMax.l = x;
        this->_rcMax.Calc();
    } else {
        this->_rcMax.Set(-1, -1);
        SetWindowLong(hWnd, GWL_STYLE, GetWindowLong(hWnd,GWL_STYLE) & ~WS_MAXIMIZEBOX );
        SetWindowLong(hWnd, GWL_STYLE, GetWindowLong(hWnd,GWL_STYLE) & ~WS_THICKFRAME );
    }
    //��С��
    if (xWF::isEqual(this->_sysbtns, xWF::SysBtns::Min)){
        this->_rcMin.Set(30, this->_rcTitle.h - 4);
        x -= this->_rcMin.w;
        if (this->_rcClose.w!=0 || this->_rcMax.w!=0) x += 3;
        this->_rcMin.l = x;
        this->_rcMin.Calc();
    } else {
        this->_rcMin.Set(-1, -1);
        SetWindowLong(hWnd, GWL_STYLE, GetWindowLong(hWnd,GWL_STYLE) & ~WS_MINIMIZEBOX );
    }
// �ͻ��� =====================================================================
    this->_rcClient.l = this->_rcFrame.r +1;
    this->_rcClient.t = this->_rcTitle.b +1;
    this->_rcClient.w = this->_rcMain.r - this->_rcClient.l*2+1;
    this->_rcClient.h = this->_rcMain.b - this->_rcClient.t - this->_rcFrame.h -1;
    this->_rcClient.Calc();
}

/*===========================================================
            ����: BindOnClick
            ����: Button=��ť��CallbackFunc=�ص�����ָ��
            ����: ���¼�_����
  ===========================================================*/
void xWF_Form::BindOnClick(int Button, tEvent_OnClick CallbackFunc)
{
    if (Button==xWF::SysBtns::Close){
        this->_funcClick_Close = CallbackFunc;
    }else if (Button==xWF::SysBtns::Icon){
        //this->_funcClick_Icon = CallbackFunc;
    }else if (Button==xWF::SysBtns::Max){
        //this->_funcClick_Max = CallbackFunc;
    }else if (Button==xWF::SysBtns::Min){
        //this->_funcClick_Min = CallbackFunc;
    }else if (Button==xWF::SysBtns::Title){
        //this->_funcClick_Title = CallbackFunc;
    }else if (Button==xWF::SysBtns::Resize){
        //this->_funcClick_Resize = CallbackFunc;
    }
}

/* ���ڰ�ť */
void xWF_Form::Button(bool btnMin, bool btnMax, bool btnClose)
{
    if (btnMin)
        this->_sysbtns |= xWF::SysBtns::Min;
    else
        this->_sysbtns &= ~xWF::SysBtns::Min;
    
    if (btnMax)
        this->_sysbtns |= xWF::SysBtns::Max;
    else
        this->_sysbtns &= ~xWF::SysBtns::Max;

    if (btnClose)
        this->_sysbtns |= xWF::SysBtns::Close;
    else
        this->_sysbtns &= ~xWF::SysBtns::Close;
}

/* ���� */
void xWF_Form::Font(int Size, int Bold, char *Name)
{
    this->_fontsize = Size;
    this->_fontbold = Bold;
    sprintf_s(this->_fontname, Name);
}

/* ͼ�� */
void xWF_Form::Icon(HICON Image)
{
    this->_hIcon = Image;
    this->_sysbtns |= xWF::SysBtns::Icon;
}

/* ���ڱ��� */
void xWF_Form::Title(char *Text)
{
    sprintf_s(this->_caption, "%s --��լ��", Text);
}
/*===========================================================
            ����: Refresh
            ����: bRunning=�Ƿ�����ı�
            ����: ˢ���ڴ��豸����
  ===========================================================*/
void xWF_Form::Refresh()
{
    this->Lock->Enter();
    HDC hWinDC = GetWindowDC(this->_hWnd);
    
    //if (this->hDC==0){
        this->_hDC = CreateCompatibleDC(hWinDC);
        this->_hBmpDC = CreateCompatibleBitmap(hWinDC, this->_rcMain.w, this->_rcMain.h);
        SelectObject(this->_hDC, this->_hBmpDC);
    //}
    
        this->base->Create(this->_rcMain.w, this->_rcMain.h, false, 0xFFFFFF);
        //this->client->Create(this->Form.Client.width - this->Form.Caption.height, this->Form.Client.height);
        this->DrawFroms();
        this->base->Alpha();
        this->base->Alpha(0, 0, this->_rcMain.r, this->_rcClient.t);
        this->base->Alpha(0, this->_rcClient.t, this->_rcClient.l, this->_rcClient.b);
        this->base->Alpha(0, this->_rcClient.b, this->_rcMain.r, this->_rcMain.b);
        this->base->Alpha(this->_rcClient.r, this->_rcClient.t, this->_rcMain.r, this->_rcClient.b);
        //this->base->Alpha(this->_rcClient.l, this->_rcClient.t, this->_rcClient.r, this->_rcClient.b, false);
        this->base->Refresh(hWinDC, this->_hDC, 0,0,0,0);

    RECT rect;
    GetWindowRect(this->_hWnd, &rect);
    // ͸������
    BLENDFUNCTION m_Blend;
        m_Blend.BlendOp             = 0;    // the only BlendOp defined in Windows 2000
        m_Blend.BlendFlags          = 0;    // nothing else is special ...
        m_Blend.AlphaFormat         = 1;    // ...
        m_Blend.SourceConstantAlpha = 255;  // AC_SRC_ALPHA
    POINT point={0, 0};
     SIZE size={this->_rcMain.w, this->_rcMain.h};
    UpdateLayeredWindow(this->_hWnd, hWinDC, NULL, &size, this->_hDC, &point, 0, &m_Blend, ULW_ALPHA);

    DeleteObject(this->_hBmpDC);
    DeleteDC(this->_hDC);
    ReleaseDC(this->_hWnd, hWinDC);
    this->Lock->Leave();
    //RedrawWindow(hWnd, NULL, NULL, RDW_UPDATENOW || RDW_INVALIDATE || RDW_INTERNALPAINT || RDW_ALLCHILDREN);
}

void xWF_Form::DrawFroms()
{
    int iX1, iY1, iX2, iY2;
    int i, k, fx, halfH;
    float Per;

    BYTE clrTx[3], clrBg[3], clrRed[3], clrSd[3], clrFra[3];
    BYTE tmpClr[3], tmpClrBG[3]; // 0=r, 1=g, 2=b 
    // �߿�
    clrFra[0] = 44; clrFra[1] = 105; clrFra[2] = 157;
    //clrFra[0] = 110; clrFra[1] = 110; clrFra[2] = 110; //��ɫ
    //clrFra[0] = 0; clrFra[1] = 120; clrFra[2] = 215; //��ɫ
    // ����ɫ
    clrBg[0] = 0xFF; clrBg[1] = 0xFF; clrBg[2] = 0xFF;
    // �ı�ɫ
    clrTx[0] = clrFra[0] & 0x0F;
    clrTx[1] = clrFra[1] & 0x0F;
    clrTx[2] = clrFra[2] & 0x0F;

    // ��ɫ
    clrRed[0] = 0xF6; clrRed[1] = 0x39; clrRed[2] = 0x1E;
    // ��ɫ
    //clrYel[0] = 0xFF; clrYel[1] = 0xAA; clrYel[2] = 0x00;
    // ��ɫ
    BYTE clrBul[3];
    clrBul[0] = 0x32; clrBul[1] = 0xC8; clrBul[2] = 0xFF;
    //this->base->gPercent(clrBul, clrFra, clrBg, 0.50f);

    this->base->gPercent(clrSd, clrFra, clrBg, 0.90f);
    this->base->gPercent(tmpClr, clrBg, clrSd, 0.80f);
    clrBg[0] = tmpClr[0]; clrBg[1] = tmpClr[1]; clrBg[2] = tmpClr[2];

    this->base->Color(xWF::Color::Transparent, clrFra[0], clrFra[1], clrFra[2], 0xFF);
    this->base->Color(xWF::Color::Transparent, clrRed[0], clrRed[1], clrRed[2], 0xFF);
    this->base->Color(xWF::Color::Transparent, clrBul[0], clrBul[1], clrBul[2], 0xFF);
    this->base->Color(xWF::Color::Transparent, clrBg[0], clrBg[1], clrBg[2], 0xFF);
    this->base->Color(xWF::Color::Transparent, clrTx[0], clrTx[1], clrTx[2], 0xFF);
    this->base->Color(xWF::Color::Transparent, clrSd[0], clrSd[1], clrSd[2], 0xB4);
//������ =======================================================================================================================================
if (IsIconic(this->_hWnd)){//��С��״̬
    this->DrawMinTitlebar(clrTx,clrFra,clrBg,clrSd);
} else {
    // ����
    for (i=0; i<this->_rcMain.h; i++){
        if (i<=this->_rcMain.h*0.5f){
            Per = (i/(this->_rcMain.h+0.1f))*0.8f+0.2f;
            this->base->gPercent(tmpClrBG, clrFra, clrBg, Per);
        } else {
            Per = (i/(this->_rcMain.h+0.1f))*1.0f-0.2f;
            this->base->gPercent(tmpClrBG, clrBg, clrFra, Per);
        }
        this->base->Color(xWF::Color::Frame, tmpClrBG[0],tmpClrBG[1],tmpClrBG[2], 0xB4);

        if (i<this->_rcClient.t){// top
            iX1=this->_rcClient.l-1;
            iX2=this->_rcClient.r+1;
            iY1=iY2=this->_rcMain.t+i;
            this->base->gdi_line(iX1, iY1, iX2, iY2);
        }
        if (i>this->_rcMain.b-this->_rcFrame.h){// bottom
            iX1=this->_rcClient.l-1;
            iX2=this->_rcClient.r+1;
            iY1=iY2=i;
            this->base->gdi_line(iX1, iY1, iX2, iY2);
        }
        
        iX1=this->_rcMain.l;
        if (i<3) {iX1+=3;}
        if (i>this->_rcMain.h-5) {iX1+=1;}
        if (i>this->_rcMain.h-3) {iX1+=1;}
        if (i>this->_rcMain.h-2) {iX1+=2;}
        iX2=this->_rcClient.l-1;
        iY1=iY2=this->_rcMain.t+i;
        this->base->gdi_line(iX1, iY1, iX2, iY2); // left
        
        iX1=this->_rcMain.l+this->_rcClient.r;
        iX2=this->_rcMain.r;
        if (i<3) {iX2-=3;}
        if (i>this->_rcMain.h-5) {iX2-=1;}
        if (i>this->_rcMain.h-3) {iX2-=1;}
        if (i>this->_rcMain.h-2) {iX2-=2;}
        iY1=iY2=this->_rcMain.t+i;
        this->base->gdi_line(iX1, iY1, iX2, iY2); // right
    }

    for (k=0; k<2; k++){
        if (k==0) {//��߿�
            tmpClrBG[0] = clrFra[0];
            tmpClrBG[1] = clrFra[1];
            tmpClrBG[2] = clrFra[2];
        } else { //�ڱ߿�
            tmpClrBG[0] = clrSd[0];
            tmpClrBG[1] = clrSd[1];
            tmpClrBG[2] = clrSd[2];
        }
        this->base->Color(xWF::Color::Frame, tmpClrBG[0],tmpClrBG[1],tmpClrBG[2]);

        iX1=this->_rcMain.l; iX2=this->_rcMain.r;
        iY1=this->_rcMain.t; iY2=this->_rcMain.b;

        this->base->gdi_line( iX1+k,   iY1+2+k, iX1+3+k, iY1-1+k );
        this->base->gdi_line( iX1+k,   iY1+3+k, iX1+4+k, iY1-1+k );
        this->base->gdi_line( iX2-1-k, iY1+2+k, iX2-4-k, iY1-1+k );
        this->base->gdi_line( iX2-1-k, iY1+3+k, iX2-5-k, iY1-1+k );
        this->base->gdi_line( iX1+4+k, iY1+k,   iX2-4-k, iY1+k   ); //��
        this->base->gdi_line( iX1+k,   iY1+4+k, iX1+k,   iY2-4-k ); //��
        this->base->gdi_line( iX1+1+k, iY2-4-k, iX1+1+k, iY2-2-k );
        this->base->gdi_line( iX1+2+k, iY2-2-k, iX1+4+k, iY2-2-k );
        this->base->gdi_line( iX2-2-k, iY2-4-k, iX2-2-k, iY2-2-k );
        this->base->gdi_line( iX2-4-k, iY2-2-k, iX2-2-k, iY2-2-k );
        this->base->gdi_line( iX1+4+k, iY2-1-k, iX2-4-k, iY2-1-k ); //��
        this->base->gdi_line( iX2-1-k, iY1+4+k, iX2-1-k, iY2-4-k ); //��
        
        iX1=this->_rcClient.l-1; iX2=this->_rcMain.r-this->_rcFrame.w-1;
        iY1=this->_rcClient.t-1; iY2=this->_rcMain.b-this->_rcFrame.h-1;
        
        this->base->gdi_line( iX1,   iY1-k, iX2+1, iY1-k ); //��
        this->base->gdi_line( iX1,   iY2+k, iX2+1, iY2+k ); //��
        this->base->gdi_line( iX1-k, iY1,   iX1-k, iY2+1 ); //��
        this->base->gdi_line( iX2+k, iY1,   iX2+k, iY2+1 ); //��
    }
    //ͼ��
    COLORREF Color;
    for (i=0; i<16; i++){
        for (k=0; k<16; k++){
            if (xWF::zHAi_Icon[i][k]!=0){
                if (xWF::zHAi_Icon[i][k]==1) {
                    Color = 0x0000FF;
                } else if (xWF::zHAi_Icon[i][k]==2) {
                    Color = 0x73DEFE;
                } else {
                    Color = 0x0000FF;
                }
                this->base->gdi_point(this->_rcIcon.l+k, this->_rcIcon.t+i, Color);
            }
        }
    }
    // ����������
    this->base->Font(this->_fontsize, this->_fontbold, this->_fontname);
    iX1 = this->_rcTitle.l + this->_rcIcon.r + 2;
    iY1 = this->_rcTitle.t;
    this->base->Color(xWF::Color::Font, clrTx[0],clrTx[1],clrTx[2]);
    this->base->gdi_text(iX1,   iY1+1, this->_caption, xWF::Align::VCenter, this->_rcTitle.w, this->_rcTitle.h-this->_rcTitle.t);
    this->base->gdi_text(iX1+1, iY1+1, this->_caption, xWF::Align::VCenter, this->_rcTitle.w, this->_rcTitle.h-this->_rcTitle.t);
    this->base->Color(xWF::Color::Font, clrBg[0],clrBg[1],clrBg[2]);
    this->base->gdi_text(iX1, iY1, this->_caption, xWF::Align::VCenter, this->_rcTitle.w, this->_rcTitle.h-this->_rcTitle.t);
//�رհ�ť =======================================================================================================================================
    if (xWF::isEqual(this->_sysbtns, xWF::SysBtns::Close)){
        this->base->gPercent(clrSd, clrRed, clrBg, 0.85f);
        iX1=this->_rcClose.l; iX2=this->_rcClose.r;
        iY1=this->_rcClose.t; iY2=this->_rcClose.b;
        // ���䱳��
        halfH=(_rcClose.h-2)/2;
        for (i=0; i<halfH; i++){
            //this->base->gPercent(tmpClrBG, clrBg, clrRed, (i+3.0f)/25.0f);
            this->base->gPercent(tmpClrBG, clrBg, clrRed, (i+1.0f)/halfH*0.5f);
            this->base->Color(xWF::Color::Frame, tmpClrBG[0],tmpClrBG[1],tmpClrBG[2], 0xB4);
            this->base->gdi_line(iX1+2, iY1+i, iX2-2, iY1+i);

            //this->base->gPercent(tmpClrBG, clrRed, clrBg, (i+3.0f)/20.0f);
            this->base->gPercent(tmpClrBG, clrRed, clrBg, (i+1.0f)/halfH*0.6f);
            this->base->Color(xWF::Color::Frame, tmpClrBG[0],tmpClrBG[1],tmpClrBG[2], 0xB4);
            this->base->gdi_line(iX1+2, iY1+i+halfH, iX2-2, iY1+i+halfH);
        }
        // �߿�
        this->base->Color(xWF::Color::Frame, clrFra[0],clrFra[1],clrFra[2]);
        this->base->gdi_line( iX1, iY1, iX2, iY1 ); //��
        //
        if (!xWF::isEqual(this->_sysbtns, xWF::SysBtns::Min) && !xWF::isEqual(this->_sysbtns, xWF::SysBtns::Max)) fx=1; else fx=0;

        for (k=0; k<=2; k++){
            if (k==0){//��߿�
                tmpClr[0] = clrSd[0];
                tmpClr[1] = clrSd[1];
                tmpClr[2] = clrSd[2];
            } else if (k==1){//�߿�
                tmpClr[0] = clrFra[0];
                tmpClr[1] = clrFra[1];
                tmpClr[2] = clrFra[2];
                if ( (this->_mouse==this->_mousefrist || this->_mousefrist==0) && this->_bMouseIn && xWF::isEqual(this->_mouse, xWF::MouseIn::Close) ){
                    tmpClr[0] = clrRed[0];
                    tmpClr[1] = clrRed[1];
                    tmpClr[2] = clrRed[2];
                }
            }else{//�ڱ߿�
                tmpClr[0] = clrSd[0];
                tmpClr[1] = clrSd[1];
                tmpClr[2] = clrSd[2];
                if ( (this->_mouse==this->_mousefrist || this->_mousefrist==0) && this->_bMouseIn && xWF::isEqual(this->_mouse, xWF::MouseIn::Close) ){
                    tmpClr[0] = clrBg[0];
                    tmpClr[1] = clrBg[1];
                    tmpClr[2] = clrBg[2];
                }
            }
            this->base->Color(xWF::Color::Frame, tmpClr[0],tmpClr[1],tmpClr[2]);
            this->base->gdi_line( iX1+k,   iY2-1-k, iX2-k-2, iY2-1-k ); //��
            this->base->gdi_line( iX1+k,   iY1+1,   iX1+k,   iY2-1-k ); //��
            this->base->gdi_line( iX2-1-k, iY1+1,   iX2-1-k, iY2-2-k ); //��
            this->base->gdi_line( iX2-k-3, iY2-1-k, iX2-1-k, iY2-3-k ); //��
            this->base->gdi_line( iX2-k-3, iY2-2-k, iX2-1-k, iY2-4-k ); //��
        }
        if ( (this->_mouse==this->_mousefrist || this->_mousefrist==0) && this->_bMouseIn && xWF::isEqual(this->_mouse, xWF::MouseIn::Close) ){
            tmpClrBG[0] = clrBg[0];
            tmpClrBG[1] = clrBg[1];
            tmpClrBG[2] = clrBg[2];
            tmpClr[0] = clrRed[0];
            tmpClr[1] = clrRed[1];
            tmpClr[2] = clrRed[2];
        } else {
            tmpClrBG[0] = clrSd[0];
            tmpClrBG[1] = clrSd[1];
            tmpClrBG[2] = clrSd[2];
            tmpClr[0] = clrFra[0];
            tmpClr[1] = clrFra[1];
            tmpClr[2] = clrFra[2];
        }
        iX1 += this->_rcClose.w/2 - 3;
        iY1 += this->_rcClose.h/2 - 4;
        //�رհ�ť-X ��ʼ
            this->base->Color(xWF::Color::Frame, tmpClr[0],tmpClr[1],tmpClr[2]);
            //����
            this->base->gdi_line( iX1 - 1, iY1 - 1, iX1 + 1, iY1 - 0 );
            this->base->gdi_line( iX1 - 2, iY1 + 0, iX1 + 2, iY1 + 4 );
            this->base->gdi_line( iX1 + 1, iY1 - 1, iX1 + 4, iY1 + 2 );
            //����
            this->base->gdi_line( iX1 - 1, iY1 + 8, iX1 + 1, iY1 + 8 );
            this->base->gdi_line( iX1 + 1, iY1 + 4, iX1 - 3, iY1 + 8 );
            this->base->gdi_line( iX1 + 3, iY1 + 6, iX1 + 0, iY1 + 9 );
            //����
            this->base->gdi_line( iX1 + 6, iY1 - 1, iX1 + 8, iY1 - 1 );
            this->base->gdi_line( iX1 + 5, iY1 - 1, iX1 + 2, iY1 + 2 );
            this->base->gdi_line( iX1 + 8, iY1 + 0, iX1 + 4, iY1 + 4 );
            //����
            this->base->gdi_line( iX1 + 7, iY1 + 8, iX1 + 5, iY1 + 8 );
            this->base->gdi_line( iX1 + 3, iY1 + 6, iX1 + 6, iY1 + 9 );
            this->base->gdi_line( iX1 + 5, iY1 + 4, iX1 + 9, iY1 + 8 );


            this->base->Color(xWF::Color::Frame, tmpClrBG[0],tmpClrBG[1],tmpClrBG[2]);
            //����
            this->base->gdi_line( iX1 - 1, iY1 + 0, iX1 + 3, iY1 + 4 );
            this->base->gdi_line( iX1 + 0, iY1 + 0, iX1 + 4, iY1 + 4 );
            this->base->gdi_line( iX1 + 1, iY1 + 0, iX1 + 5, iY1 + 4 );
            //����
            this->base->gdi_line( iX1 + 2, iY1 + 4, iX1 - 2, iY1 + 8 );
            this->base->gdi_line( iX1 + 3, iY1 + 4, iX1 - 1, iY1 + 8 );
            this->base->gdi_line( iX1 + 4, iY1 + 4, iX1 + 0, iY1 + 8 );
            //����
            this->base->gdi_line( iX1 + 5, iY1 + 0, iX1 + 2, iY1 + 3 );
            this->base->gdi_line( iX1 + 6, iY1 + 0, iX1 + 3, iY1 + 3 );
            this->base->gdi_line( iX1 + 7, iY1 + 0, iX1 + 3, iY1 + 4 );
            //����
            this->base->gdi_line( iX1 + 3, iY1 + 5, iX1 + 6, iY1 + 8 );
            this->base->gdi_line( iX1 + 4, iY1 + 5, iX1 + 7, iY1 + 8 );
            this->base->gdi_line( iX1 + 5, iY1 + 5, iX1 + 8, iY1 + 8 );
        //�رհ�ť-X ����
    }

//��󻯰�ť =======================================================================================================================================
    if (xWF::isEqual(this->_sysbtns, xWF::SysBtns::Max)){
        this->base->gPercent(clrSd, clrFra, clrBg, 0.85f);
        iX1=this->_rcMax.l; iX2=this->_rcMax.r;
        iY1=this->_rcMax.t; iY2=this->_rcMax.b;
        // ���䱳��
        halfH=(this->_rcMax.h-2)/2;
        for (i=0; i<halfH; i++){
            this->base->gPercent(tmpClrBG, clrBg, clrFra, (i+1.0f)/halfH*0.5f);
            this->base->Color(xWF::Color::Frame, tmpClrBG[0],tmpClrBG[1],tmpClrBG[2], 0xB4);
            this->base->gdi_line(iX1+2, iY1+i, iX2-2, iY1+i);
            
            this->base->gPercent(tmpClrBG, clrFra, clrBg, (i+1.0f)/halfH*0.6f);
            this->base->Color(xWF::Color::Frame, tmpClrBG[0],tmpClrBG[1],tmpClrBG[2], 0xB4);
            this->base->gdi_line(iX1+2, iY1+i+halfH, iX2-2, iY1+i+halfH);
        }
        // �߿�
        this->base->Color(xWF::Color::Frame, clrFra[0],clrFra[1],clrFra[2]);
        this->base->gdi_line( iX1, iY1, iX2, iY1 ); //��
        //
        if (!xWF::isEqual(this->_sysbtns, xWF::SysBtns::Min)) fx=1; else fx=0;

        for (k=0; k<=2; k++){
            if (k==0){//��߿�
                tmpClr[0] = clrSd[0];
                tmpClr[1] = clrSd[1];
                tmpClr[2] = clrSd[2];
            } else if (k==1){//�߿�
                tmpClr[0] = clrFra[0];
                tmpClr[1] = clrFra[1];
                tmpClr[2] = clrFra[2];
                if ( (this->_mouse==this->_mousefrist || this->_mousefrist==0) && this->_bMouseIn && xWF::isEqual(this->_mouse, xWF::MouseIn::Max) ){
                    tmpClr[0] = clrBul[0];
                    tmpClr[1] = clrBul[1];
                    tmpClr[2] = clrBul[2];
                }
            }else{//�ڱ߿�
                tmpClr[0] = clrSd[0];
                tmpClr[1] = clrSd[1];
                tmpClr[2] = clrSd[2];
                if ( (this->_mouse==this->_mousefrist || this->_mousefrist==0) && this->_bMouseIn && xWF::isEqual(this->_mouse, xWF::MouseIn::Max) ){
                    tmpClr[0] = clrBg[0];
                    tmpClr[1] = clrBg[1];
                    tmpClr[2] = clrBg[2];
                }
            }
            this->base->Color(xWF::Color::Frame, tmpClr[0],tmpClr[1],tmpClr[2]);
            this->base->gdi_line( iX1+k+fx*2, iY2-1-k, iX2-k,   iY2-1-k    ); //��
            this->base->gdi_line( iX1+k,      iY1+1,   iX1+k,   iY2-1-k-fx ); //��
            if (fx){
                this->base->gdi_line( iX1+k,   iY2-3-k, iX1+3+k, iY2-k   ); //��
                this->base->gdi_line( iX1+k+1, iY2-3-k, iX1+4+k, iY2-k   ); //��
            }
            if (k!=0){
                if (k==1 && this->_bMouseIn) {
                    if (xWF::isEqual(this->_mouse, xWF::MouseIn::Close)){
                        continue;
                    }
                }
                this->base->gdi_line( iX2-1-k, iY1+1,   iX2-1-k, iY2-1-k ); //��
            }
        }
        if ( (this->_mouse==this->_mousefrist || this->_mousefrist==0) && this->_bMouseIn && xWF::isEqual(this->_mouse, xWF::MouseIn::Max) ){
            tmpClrBG[0] = clrBg[0];
            tmpClrBG[1] = clrBg[1];
            tmpClrBG[2] = clrBg[2];
            tmpClr[0] = clrBul[0];
            tmpClr[1] = clrBul[1];
            tmpClr[2] = clrBul[2];
        } else {
            tmpClrBG[0] = clrSd[0];
            tmpClrBG[1] = clrSd[1];
            tmpClrBG[2] = clrSd[2];
            tmpClr[0] = clrFra[0];
            tmpClr[1] = clrFra[1];
            tmpClr[2] = clrFra[2];
        }
        i=(this->_rcMax.w/5);
        k=(this->_rcMax.h/5);
        iX1 += i-2;
        iY1 += k*2+2;
        this->base->Color(xWF::Color::Background, tmpClrBG[0],tmpClrBG[1],tmpClrBG[2]);
        this->base->gdi_fill(iX1, iY1, i*3, k*2);
        
        this->base->Color(xWF::Color::Frame, tmpClr[0],tmpClr[1],tmpClr[2]);
        this->base->gdi_box(iX1, iY1, i*3, k*2);
        
        this->base->gdi_box((int)(iX1+i/2), (int)(iY1-k/1.5), i*3, k*2);
    }
//��С����ť =======================================================================================================================================
    if (xWF::isEqual(this->_sysbtns, xWF::SysBtns::Min)){
        this->base->gPercent(clrSd, clrFra, clrBg, 0.85f);
        iX1=this->_rcMin.l; iX2=this->_rcMin.r;
        iY1=this->_rcMin.t; iY2=this->_rcMin.b;
        // ���䱳��
        halfH=(this->_rcMin.h-2)/2;
        for (i=0; i<halfH; i++){
            this->base->gPercent(tmpClrBG, clrBg, clrFra, (i+1.0f)/halfH*0.5f);
            this->base->Color(xWF::Color::Frame, tmpClrBG[0],tmpClrBG[1],tmpClrBG[2], 0xB4);
            this->base->gdi_line(iX1+2, iY1+i, iX2-2, iY1+i);

            this->base->gPercent(tmpClrBG, clrFra, clrBg, (i+1.0f)/halfH*0.6f);
            this->base->Color(xWF::Color::Frame, tmpClrBG[0],tmpClrBG[1],tmpClrBG[2], 0xB4);
            this->base->gdi_line(iX1+2, iY1+i+halfH, iX2-2, iY1+i+halfH);
        }
        // �߿�
        this->base->Color(xWF::Color::Frame, clrFra[0],clrFra[1],clrFra[2]);
        this->base->gdi_line( iX1, iY1, iX2, iY1 ); //��
        for (k=0; k<=2; k++){
            if (k==0){//��߿�
                tmpClr[0] = clrSd[0];
                tmpClr[1] = clrSd[1];
                tmpClr[2] = clrSd[2];
            } else if (k==1){//�߿�
                tmpClr[0] = clrFra[0];
                tmpClr[1] = clrFra[1];
                tmpClr[2] = clrFra[2];
                if ( (this->_mouse==this->_mousefrist || this->_mousefrist==0) && this->_bMouseIn && xWF::isEqual(this->_mouse, xWF::MouseIn::Min) ){
                    tmpClr[0] = clrBul[0];
                    tmpClr[1] = clrBul[1];
                    tmpClr[2] = clrBul[2];
                }
            }else{//�ڱ߿�
                tmpClr[0] = clrSd[0];
                tmpClr[1] = clrSd[1];
                tmpClr[2] = clrSd[2];
                if ( (this->_mouse==this->_mousefrist || this->_mousefrist==0) && this->_bMouseIn && xWF::isEqual(this->_mouse, xWF::MouseIn::Min) ){
                    tmpClr[0] = clrBg[0];
                    tmpClr[1] = clrBg[1];
                    tmpClr[2] = clrBg[2];
                }
            }
            this->base->Color(xWF::Color::Frame, tmpClr[0],tmpClr[1],tmpClr[2]);
            this->base->gdi_line( iX1+k+2, iY2-1-k, iX2-k,   iY2-1-k ); //��
            this->base->gdi_line( iX1+k,   iY1+1,   iX1+k,   iY2-2-k ); //��
            this->base->gdi_line( iX1+k,   iY2-3-k, iX1+3+k, iY2-k   ); //��
            this->base->gdi_line( iX1+k+1, iY2-3-k, iX1+4+k, iY2-k   ); //��
            
            if (k>=1){
                if (k==1 && this->_bMouseIn) {
                    if (xWF::isEqual(this->_mouse, xWF::MouseIn::Close) || xWF::isEqual(this->_mouse, xWF::MouseIn::Max)){
                        continue;
                    }
                }
                this->base->gdi_line( iX2-1-k, iY1+1,   iX2-1-k, iY2-1-k ); //��
            }
        }
        if ( (this->_mouse==this->_mousefrist || this->_mousefrist==0) && this->_bMouseIn && xWF::isEqual(this->_mouse, xWF::MouseIn::Min) ){
            tmpClrBG[0] = clrBg[0];
            tmpClrBG[1] = clrBg[1];
            tmpClrBG[2] = clrBg[2];
            tmpClr[0] = clrBul[0];
            tmpClr[1] = clrBul[1];
            tmpClr[2] = clrBul[2];
        } else {
            tmpClrBG[0] = clrSd[0];
            tmpClrBG[1] = clrSd[1];
            tmpClrBG[2] = clrSd[2];
            tmpClr[0] = clrFra[0];
            tmpClr[1] = clrFra[1];
            tmpClr[2] = clrFra[2];
        }
        i=(this->_rcMin.w/5);
        k=(this->_rcMin.h/5);
        iX1 += i;
        iY1 += (int)(k*2.5+2);
        this->base->Color(xWF::Color::Background, tmpClrBG[0],tmpClrBG[1],tmpClrBG[2]);
        this->base->gdi_fill(iX1, iY1, (int)(i*3), (int)(k*1.5));
        
        this->base->Color(xWF::Color::Frame, tmpClr[0],tmpClr[1],tmpClr[2]);
        this->base->gdi_box(iX1, iY1, (int)(i*3), (int)(k*1.5));
    }
    
    /* �ͻ��� */
        this->base->Color(xWF::Color::Background, clrBg[0],clrBg[1],clrBg[2]);
        this->base->gdi_fill(this->_rcClient.l, this->_rcClient.t, this->_rcClient.w, this->_rcClient.h);
        //this->client->gdi_Fill(0, 0, this->_rcClient.w, this->_rcClient.h);
        //����ͼƬ
        //this->client->gdi_Image(iX1, iY1, this->hImage[0], iImgW, iImgH);

    /* �ͻ����߿� */
        //this->client->setColor_Box(clrBg[0],clrBg[1],clrBg[2]);
        //this->client->gdi_Box(this->_rcClient.l, this->_rcClient.t, this->_rcClient.w, this->_rcClient.h);
        //this->client->CopyTo(this->base->gMemDC(), 0, this->_rcClient.t, 0, 0);
        
        this->base->Color(xWF::Color::Background, clrBg[0],clrBg[1],clrBg[2]);
        this->base->Color(xWF::Color::Gradient, clrBg[0],clrBg[1],clrBg[2]);
        this->base->Color(xWF::Color::Frame, clrBul[0],clrBul[1],clrBul[2]);
        this->base->gdi_box(this->_rcClient.l+5, this->_rcClient.t+5 ,100,22, xWF::Smooth::Glow);
        this->base->gdi_box(this->_rcClient.l+5, this->_rcClient.t+30,100,22, xWF::Smooth::Full | xWF::Smooth::Size1 | xWF::Smooth::Glow);
        this->base->gdi_box(this->_rcClient.l+5, this->_rcClient.t+55,100,22, xWF::Smooth::Full | xWF::Smooth::Size2 | xWF::Smooth::Glow);
        this->base->gdi_box(this->_rcClient.l+5, this->_rcClient.t+85,100,22, xWF::Smooth::Full | xWF::Smooth::Size4 | xWF::Smooth::Glow);
        
        this->base->gdi_box(this->_rcClient.l+115, this->_rcClient.t+5 ,100,22, xWF::Smooth::Glow);
        this->base->gdi_box(this->_rcClient.l+115, this->_rcClient.t+30,100,22, xWF::Smooth::Bottom | xWF::Smooth::Size1 | xWF::Smooth::Glow, xWF::Fill::Gradient);
        this->base->gdi_box(this->_rcClient.l+115, this->_rcClient.t+55,100,22, xWF::Smooth::Full | xWF::Smooth::Size2 | xWF::Smooth::Glow, xWF::Fill::Gradient);
        this->base->gdi_box(this->_rcClient.l+115, this->_rcClient.t+85,100,22, xWF::Smooth::LTop | xWF::Smooth::Size2 | xWF::Smooth::Glow, xWF::Fill::Gradient);
        this->base->gdi_box(this->_rcClient.l+115, this->_rcClient.t+85+30,100,22, xWF::Smooth::RTop | xWF::Smooth::Size2 | xWF::Smooth::Glow, xWF::Fill::Gradient);
        this->base->gdi_box(this->_rcClient.l+115, this->_rcClient.t+85+60,100,22, xWF::Smooth::RBottom | xWF::Smooth::Size2 | xWF::Smooth::Glow, xWF::Fill::Gradient);
        this->base->gdi_box(this->_rcClient.l+115, this->_rcClient.t+85+90,100,22, xWF::Smooth::LBottom | xWF::Smooth::Size2 | xWF::Smooth::Glow, xWF::Fill::Gradient);
        
        this->base->gdi_box(this->_rcClient.l+225, this->_rcClient.t+85+5,100,30, xWF::Smooth::Full | xWF::Smooth::Size4 | xWF::Smooth::Glow, xWF::Fill::Gradient);
        this->base->gdi_box(this->_rcClient.l+225, this->_rcClient.t+85+40,100,30, xWF::Smooth::Full | xWF::Smooth::Size4 | xWF::Smooth::Glow, xWF::Fill::Solid);
    }
}

void xWF_Form::DrawMinTitlebar(BYTE *clrTx, BYTE *clrFra, BYTE *clrBg, BYTE *clrSd)
{
    int iX1, iY1, iX2, iY2;
    int i, k, iFraW=this->_rcFrame.w;
    float Per;
    BYTE tmpClrBG[3];

    // ����
    for (i=1; i<this->_rcMain.h; i++){
            Per = (i/(this->_rcMain.h*5+0.1f))*0.8f+0.2f;
            this->base->gPercent(tmpClrBG, clrFra, clrBg, Per);
        this->base->Color(xWF::Color::Frame, tmpClrBG[0],tmpClrBG[1],tmpClrBG[2], 0xB4);
        
        k = this->_rcMain.b-this->_rcFrame.h;
        if (i<=k){// top
            iX1=this->_rcMain.l+1;
            iX2=this->_rcMain.r-1;
            iY1=iY2=this->_rcMain.t+i;
            this->base->gdi_line(iX1, iY1, iX2, iY2);
        } else { // bottom
            iX1=this->_rcMain.l+1+(i-k);
            iX2=this->_rcMain.r-1-(i-k);
            iY1=iY2=i;
            this->base->gdi_line(iX1, iY1, iX2, iY2);
        }
    }

    for (k=0; k<2; k++){
        if (k==0) {//��߿�
            tmpClrBG[0] = clrFra[0];
            tmpClrBG[1] = clrFra[1];
            tmpClrBG[2] = clrFra[2];
        } else { //�ڱ߿�
            tmpClrBG[0] = clrSd[0];
            tmpClrBG[1] = clrSd[1];
            tmpClrBG[2] = clrSd[2];
        }
        this->base->Color(xWF::Color::Frame, tmpClrBG[0],tmpClrBG[1],tmpClrBG[2]);

        iX1=this->_rcMain.l; iX2=this->_rcMain.r;
        iY1=this->_rcMain.t; iY2=this->_rcMain.b;

        this->base->gdi_line( iX1+k,   iY1+2+k, iX1+3+k, iY1-1+k );
        this->base->gdi_line( iX1+k,   iY1+3+k, iX1+4+k, iY1-1+k );
        this->base->gdi_line( iX2-1-k, iY1+2+k, iX2-4-k, iY1-1+k );
        this->base->gdi_line( iX2-1-k, iY1+3+k, iX2-5-k, iY1-1+k );
        this->base->gdi_line( iX1+4+k, iY1+k,   iX2-4-k, iY1+k   ); //��
        this->base->gdi_line( iX1+k,   iY1+4+k, iX1+k,   iY2-4-k ); //��
        this->base->gdi_line( iX1+1+k, iY2-4-k, iX1+1+k, iY2-2-k );
        this->base->gdi_line( iX1+2+k, iY2-2-k, iX1+4+k, iY2-2-k );
        this->base->gdi_line( iX2-2-k, iY2-4-k, iX2-2-k, iY2-2-k );
        this->base->gdi_line( iX2-4-k, iY2-2-k, iX2-2-k, iY2-2-k );
        this->base->gdi_line( iX1+4+k, iY2-1-k, iX2-4-k, iY2-1-k ); //��
        this->base->gdi_line( iX2-1-k, iY1+4+k, iX2-1-k, iY2-4-k ); //��
    }
    //ͼ��
    COLORREF Color;
    for (int i=0; i<16; i++){
        for (int k=0; k<16; k++){
            if (xWF::zHAi_Icon[i][k]!=0){
                if (xWF::zHAi_Icon[i][k]==1) {
                    Color = 0x0000FF;
                } else if (xWF::zHAi_Icon[i][k]==2) {
                    Color = 0x73DEFE;
                } else {
                    Color = 0x0000FF;
                }
                this->base->gdi_point(this->_rcIcon.l+k, this->_rcIcon.t+i-iFraW/2, Color);
            }
        }
    }
    // ����������
    this->base->Font(this->_fontsize, this->_fontbold, this->_fontname);
    iX1 = this->_rcTitle.l + this->_rcIcon.r + 2;
    iY1 = 0;
    this->base->Color(xWF::Color::Font, clrTx[0],clrTx[1],clrTx[2]);
    this->base->gdi_text(iX1,   iY1+1, this->_caption, xWF::Align::VCenter, this->_rcTitle.w, this->_rcMain.h);
    this->base->gdi_text(iX1+1, iY1+1, this->_caption, xWF::Align::VCenter, this->_rcTitle.w, this->_rcMain.h);
    this->base->Color(xWF::Color::Font, clrSd[0],clrSd[1],clrSd[2]);
    this->base->gdi_text(iX1, iY1, this->_caption, xWF::Align::VCenter, this->_rcTitle.w, this->_rcMain.h);
}
/*===========================================================
            ����: CallbackDialog
            ����: hDlg=���ھ����uMsg=��Ϣ���ͣ�wParam=�¼�ֵ��lParam=�¼�ֵ
            ����: ���λ��
            ����: ���ڻص��¼�
  ===========================================================*/
LRESULT CALLBACK xWF_Form::CallbackDialog( HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam )
{ 
    RECT rcF;
    int x, y;
    BYTE down;
    switch ( uMsg )
    {
    case WM_CREATE:
    case WM_INITDIALOG:
        {
            this->ScreenWidth    = GetSystemMetrics(SM_CXFULLSCREEN);
            this->ScreenHeight   = GetSystemMetrics(SM_CYFULLSCREEN);
            this->TitleBarHeight = GetSystemMetrics(SM_CYCAPTION);  //�������߶�
            //SystemParametersInfo(SPI_GETWORKAREA, 0, &rcF, 0);      //�������߶�
            //this->TaskBar  = rcF.right-rcF.left; //���������
            //this->TaskBar = rcF.bottom-rcF.top; //�������߶�

            GetWindowRect(hDlg,&rcF);
                x = rcF.right-rcF.left;
                y = rcF.bottom-rcF.top;

            this->_hWnd = hDlg;
            this->_bMouseIn = FALSE;
            this->Bind(this->_hWnd, x, y);
            this->Refresh();
            break;
        }
        
    case WM_DESTROY:
        {
            break;
        }
    case WM_SIZE: //�ı��С
        {
            GetClientRect(hDlg,&rcF);
                x = rcF.right-rcF.left;
                y = rcF.bottom-rcF.top;

            if (IsZoomed(hDlg)) {//���״̬
                y = this->ScreenHeight;
                y += this->TitleBarHeight;
            }
            this->Bind(hDlg, x, y);
                //sprintf_s(this->_caption, "���ڴ�С��%d,%d --��լ��", x, y);
            this->Refresh();
            break;
        }
    case WM_MOUSELEAVE:
        {
            this->_bTracking = FALSE;
            this->_bMouseIn  = FALSE;
            this->Refresh();
            break;
        }
    case WM_MOUSEHOVER:
        {
            this->_bTracking = TRUE;
            this->_bMouseIn  = TRUE;
            break;
        }
    case WM_MOUSEWHEEL: //��������Ϣ
        {
            break;
        }
    //case WM_NCMOUSEMOVE:
    case WM_MOUSEMOVE: //��꾭��
        {
            if (!this->_bTracking)
            {
                TRACKMOUSEEVENT tme;
                tme.cbSize = sizeof(tme);
                tme.hwndTrack = hDlg;
                tme.dwFlags = TME_LEAVE | TME_HOVER;
                tme.dwHoverTime = 1;
                this->_bTracking = TrackMouseEvent(&tme);
            }
            this->_bMouseIn = TRUE;
            x = LOWORD(lParam);
            y = HIWORD(lParam);

            if ((wParam & MK_LBUTTON) == MK_LBUTTON){
                down = xWF::Click::LBtn | xWF::Click::Down;
                sprintf_s(this->_caption, "������£�%d,%d --��լ��", x, y);
            }else if ((wParam & MK_MBUTTON) == MK_MBUTTON){
                down = xWF::Click::MBtn | xWF::Click::Down;
            }else if ((wParam & MK_RBUTTON) == MK_RBUTTON){
                down = xWF::Click::RBtn | xWF::Click::Down;
            }else{
                down = 0;
            }

            this->onEvents(x, y, down);
            
            break;
        }
    case WM_LBUTTONDOWN: //����������
    //case WM_MBUTTONDOWN:
    //case WM_RBUTTONDOWN:
        {
            SetCapture(hDlg);
            x = LOWORD(lParam);
            y = HIWORD(lParam);
            
            if (uMsg==WM_LBUTTONDOWN){
                down = xWF::Click::LBtn | xWF::Click::Down;
                sprintf_s(this->_caption, "������£�%d,%d --��լ��", x, y);
            }else if (uMsg==WM_MBUTTONDOWN){
                down = xWF::Click::MBtn | xWF::Click::Down;
            }else if (uMsg==WM_RBUTTONDOWN){
                down = xWF::Click::RBtn | xWF::Click::Down;
            }else{
                down = 0;
            }

            this->onEvents(x, y, down);
            
            break;
        }
    case WM_LBUTTONUP: //����������
    //case WM_RBUTTONUP:
    //case WM_MBUTTONUP:
        {
            x = LOWORD(lParam);
            y = HIWORD(lParam);
            
            if (uMsg==WM_LBUTTONUP){
                down = xWF::Click::LBtn;
                sprintf_s(this->_caption, "�������%d,%d --��լ��", x, y);
            }else if (uMsg==WM_MBUTTONUP){
                down = xWF::Click::MBtn;
            }else if (uMsg==WM_RBUTTONUP){
                down = xWF::Click::RBtn;
            }else{
                down = 0;
            }

            this->onEvents(x, y, down);

            this->_mousefrist = 0;
            ReleaseCapture();
            break;
        }
    //case WM_NCLBUTTONDBLCLK:
    case WM_LBUTTONDBLCLK: //������˫��
        {
            x = LOWORD(lParam);
            y = HIWORD(lParam);

            this->onEvents(x, y, xWF::Click::LBtnDb);

            this->_mousefrist = 0;
            break;
        }
    case WM_PAINT:
        {
            this->Refresh();
            break;
        }
    }
    return FALSE;
}

/*===========================================================
            ����: onEvents
            ����: x=�����꣬y=�����꣬mouse=�������0=�޵����1=���������2=���˫����4=�Ҽ�������8=�Ҽ�˫����
            ����: ���λ��
            ����: ��Ӧ�����ͣ/����
  ===========================================================*/
void xWF_Form::onEvents(int x, int y, BYTE mouseclick)
{
    this->Lock->Enter();
    if (!this->_bMouseIn){
        //xWF::Align.Left
        //sprintf_s(Caption, "x:%d, y:%d, down:%d\n", x, y, down);
        this->_mouse = xWF::MouseIn::None;
    } else {
        if ( xWF::isEqual(this->_sysbtns, xWF::SysBtns::Icon) && (this->_rcIcon.l<=x && x<=this->_rcIcon.r) && (this->_rcIcon.t<=y && y<=this->_rcIcon.b) ){
            this->_mouse = xWF::MouseIn::Icon;

        }else if ( xWF::isEqual(this->_sysbtns, xWF::SysBtns::Min) && (this->_rcMin.l<=x && x<=this->_rcMin.r) && (this->_rcMin.t<=y && y<=this->_rcMin.b) ){
            this->_mouse = xWF::MouseIn::Min;
            
        }else if ( xWF::isEqual(this->_sysbtns, xWF::SysBtns::Max) && (this->_rcMax.l<=x && x<=this->_rcMax.r) && (this->_rcMax.t<=y && y<=this->_rcMax.b) ){
            this->_mouse = xWF::MouseIn::Max;

        }else if ( xWF::isEqual(this->_sysbtns, xWF::SysBtns::Close) && (this->_rcClose.l<=x && x<=this->_rcClose.r) && (this->_rcClose.t<=y && y<=this->_rcClose.b) ){
            this->_mouse = xWF::MouseIn::Close;

        }else if ( (this->_rcTitle.l<=x && x<=this->_rcTitle.r) && (this->_rcTitle.t<=y && y<=this->_rcTitle.b) ){
            this->_mouse = xWF::MouseIn::Title;

        }else if ( (this->_rcClient.l<=x && x<=this->_rcClient.r) && (this->_rcClient.t<=y && y<=this->_rcClient.b) ){
            this->_mouse = xWF::MouseIn::Client;

        }else if (( x<=this->_rcFrame.r && y<=this->_rcFrame.b) ||
                  ( this->_rcMain.w-this->_rcFrame.w<=x && y<=this->_rcFrame.b) ||
                  ( x<=this->_rcFrame.r && y>=this->_rcMain.h-this->_rcFrame.b) ||
                  ( this->_rcMain.w-this->_rcFrame.w<=x && y>=this->_rcMain.h-this->_rcFrame.b)
                ){
            this->_mouse = xWF::MouseIn::Resize;
        }else{
            this->_mouse = xWF::MouseIn::None;
        }
        if (xWF::isEqual(mouseclick, xWF::Click::Down)) {
            if (this->_mousefrist==0) this->_mousefrist = this->_mouse;
        }
        //sprintf_s(Caption, "x:%d, y:%d, down:%d, MouseIn:%d \n", x, y, down, posMouses);

        if ( this->_mouse==this->_mousefrist ){
            //����
            if (xWF::isEqual(mouseclick, xWF::Click::LBtn) ) {
                //�ر�
                if( xWF::isEqual(this->_mouse, xWF::MouseIn::Close) && !xWF::isMouseDown(mouseclick) ){
                    if (this->_funcClick_Close)
                        this->_funcClick_Close();
                //��С��
                } else if( xWF::isEqual(this->_mouse, xWF::MouseIn::Min) && !xWF::isMouseDown(mouseclick) ){
                    if (!IsIconic(this->_hWnd)) {//������С��״̬
                        ReleaseCapture();
                        SetMinmize(this->_hWnd); //��С��
                        SetLBtnUP(this->_hWnd, x, y);
                        {
                            RECT rect;
                            GetWindowRect(this->_hWnd,&rect);
                                int w = rect.right-rect.left;
                                int h = rect.bottom-rect.top;
                                int x = (this->ScreenWidth - w);
                                int y = (this->ScreenHeight + this->TitleBarHeight - h);
                            //�ƶ�λ��
                            SetWindowPos(this->_hWnd, 0, x, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
                        }
                    }
                //���
                } else if( xWF::isEqual(this->_mouse, xWF::MouseIn::Max) && !xWF::isMouseDown(mouseclick) ){
                    ReleaseCapture();
                    if (IsZoomed(this->_hWnd)) //���״̬
                        SetRestore(this->_hWnd); //��ԭ
                    else
                        SetMaxmize(this->_hWnd); //���
                    SetLBtnUP(this->_hWnd, x, y);
                //�ͻ���
                } else if( xWF::isEqual(this->_mouse, xWF::MouseIn::Client) ){
                    if( !xWF::isMouseDown(mouseclick) ) ReleaseCapture();

                    //SetLBtnUP(this->_hWnd, x, y);
                //�ƶ�������
                } else if( xWF::isEqual(this->_mouse, xWF::MouseIn::Title) && xWF::isMouseDown(mouseclick) ){
                    ReleaseCapture();
                    this->_mousefrist = 0;
                    PostMessage(this->_hWnd, WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM(x,y));
                    SetLBtnUP(this->_hWnd, x, y);
                }
            }
        }
        //˫��
        if (xWF::isEqual(mouseclick, xWF::Click::LBtnDb)) {
            //ReleaseCapture();
            if( xWF::isEqual(this->_mouse, xWF::MouseIn::Title) ){
                if( xWF::isEqual(this->_sysbtns, xWF::SysBtns::Max) ){
                    if (IsZoomed(this->_hWnd)) {//���״̬
                        SetRestore(this->_hWnd); //��ԭ
                    } else {
                        if (!IsIconic(this->_hWnd)) {//������С��״̬
                            SetMaxmize(this->_hWnd); //���
                        } else {
                            SetRestore(this->_hWnd); //��ԭ
                        }
                    }
                }
            } else if( xWF::isEqual(this->_mouse, xWF::MouseIn::Icon) ){
                if (this->_funcClick_Close) this->_funcClick_Close();
            }
        }
    }
    this->Lock->Leave();
    this->Refresh();
}
