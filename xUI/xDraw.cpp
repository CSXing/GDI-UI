/********************************************************
Create: 2019.12.02
Editor: 2022-03-15
==============================
  Version: 1.0.2022
   Author: X!ng,cHEn 『宅』910955951
Copyright: 2019 - 2020(C)
==============================
Description:
      gl/GDI画图功能
********************************************************/
#include "zHAi_WF.h"

//===========================================================
bool getBitsTo32(HDC srcDC, HBITMAP srcBMP, BITMAPINFO *Info, unsigned char *retDatas, unsigned int *retSize, bool toFixRGB=false, BYTE fixR=0, BYTE fixG=0, BYTE fixB=0) 
{ 
    BITMAP bi;
    GetObject(srcBMP, sizeof(bi), &bi);
    
    unsigned int size = bi.bmHeight * bi.bmWidthBytes;
    unsigned char *bits = (unsigned char *)malloc(sizeof(unsigned char)*size);

    Info->bmiHeader.biSize          = sizeof(BITMAPINFOHEADER);
    Info->bmiHeader.biWidth         = bi.bmWidth;
    Info->bmiHeader.biHeight        = bi.bmHeight;
    Info->bmiHeader.biPlanes        = 1;
    Info->bmiHeader.biBitCount      = bi.bmBitsPixel;
    Info->bmiHeader.biCompression   = BI_RGB;
    Info->bmiHeader.biSizeImage     = size;
    Info->bmiHeader.biXPelsPerMeter = 0;
    Info->bmiHeader.biYPelsPerMeter = 0;
    Info->bmiHeader.biClrUsed       = 0;
    Info->bmiHeader.biClrImportant  = 0;
    
    int isGod = GetDIBits(srcDC, srcBMP, 0, bi.bmHeight, bits, Info, DIB_RGB_COLORS);
    if (!isGod){
        free(bits);
        return false;
    }

    //*retSize = bi.bmHeight * (bi.bmWidth+7)/8 * 32;
    //retDatas = (unsigned char *)malloc(sizeof(unsigned char)*(*retSize)+1);
    
    int iX, iY, iPos=0;
    if (bi.bmBitsPixel==16){
        WORD wPixel;
        for (iY=0; iY<bi.bmHeight; iY++)
        {
            for (iX=0; iX<bi.bmWidth; iX++)
            {
                iPos = iY * bi.bmWidthBytes + iX * 4;
                wPixel=*(WORD*)(bits+iY*bi.bmWidthBytes+iX*2);
                retDatas[iPos+0] = ((0x7C00 & wPixel) >> 10) << 3 ;  //R
                retDatas[iPos+1] = ((0x03E0 & wPixel) >> 5 ) << 3 ;  //G
                retDatas[iPos+2] = ((0x001F & wPixel) >> 0 ) << 3 ;  //B
                if (toFixRGB && retDatas[iPos+2]==fixR && retDatas[iPos+1]==fixG && retDatas[iPos+0]==fixB)
                    retDatas[iPos+3] = 0;
                else
                    retDatas[iPos+3] = 255;
            }
        }
    } else if (bi.bmBitsPixel==24){
        int wPixel;
        for (iY=0; iY<bi.bmHeight; iY++)
        {
            for (iX=0; iX<bi.bmWidth; iX++)
            {
                iPos = iY * bi.bmWidthBytes + iX * 4;
                wPixel = iY * bi.bmWidthBytes + iX * 3;
                retDatas[iPos+0] = bits[iPos+0];  //B
                retDatas[iPos+1] = bits[iPos+1];  //G
                retDatas[iPos+2] = bits[iPos+2];  //R
                if (toFixRGB && retDatas[iPos+2]==fixR && retDatas[iPos+1]==fixG && retDatas[iPos+0]==fixB)
                    retDatas[iPos+3] = 0;
                else
                    retDatas[iPos+3] = 255;
            }
        }
    } else if (bi.bmBitsPixel==32){
        //memcpy(&retDatas[0], &bits[0], size);
        for (iY=0; iY<bi.bmHeight; iY++)
        {
            for (iX=0; iX<bi.bmWidth; iX++)
            {
                iPos = iY * bi.bmWidthBytes + iX * 4;
                retDatas[iPos+0] = bits[iPos+0];  //B
                retDatas[iPos+1] = bits[iPos+1];  //G
                retDatas[iPos+2] = bits[iPos+2];  //R
                if (toFixRGB && retDatas[iPos+2]==fixR && retDatas[iPos+1]==fixG && retDatas[iPos+0]==fixB)
                    retDatas[iPos+3] = 0;
                else
                    retDatas[iPos+3] = 255;
            }
        }
    }
    Info->bmiHeader.biBitCount  = 32; 
    Info->bmiHeader.biSizeImage = (*retSize);
    __try {
        if (bits) free(bits);
    } __except (EXCEPTION_EXECUTE_HANDLER){};
    return true;
}


/*===========================================================
            函数: Font
            参数: Size=大小，Bold=加粗，Name=字体名称
            描述: 设置字体
  ===========================================================*/
void xWF_Draw::Alpha(bool Clear) {
    this->_aRcCount = 0;
}
void xWF_Draw::Alpha(int left, int top, int right, int bottom, bool alpha) {
    this->aRc[this->_aRcCount].rc.Set(left, top, right-left-1, bottom-top-1);
    this->aRc[this->_aRcCount].alpha = alpha;
    this->_aRcCount++;
}
/*===========================================================
            函数: Font
            参数: Size=大小，Bold=加粗，Name=字体名称
            描述: 设置字体
  ===========================================================*/
void xWF_Draw::Font(int Size, int Bold, char *Name)
{
    this->_Size=Size;
    this->_Bold=Bold;
    sprintf_s(this->_Name, Name);
};
/*===========================================================
            函数: CopyTo
            参数: hDst=场景，x=横坐标，y=纵坐标，xSrc=来源开始横坐标，ySrc=来源开始纵坐标
            描述: 复制DC到场景
  ===========================================================*/
void xWF_Draw::CopyTo(HDC hDst,int x, int y, int xSrc, int ySrc)
{
    BitBlt(hDst, x, y, this->_width, this->_height, this->hMemDC, xSrc, ySrc, SRCCOPY);
}
/*===========================================================
            函数: gPercent
            参数: ret=返回值，_Fst=开始颜色，_End=结束颜色，_Per=占比
            描述: 计算两个颜色中间的值
  ===========================================================*/
void xWF_Draw::gPercent(BYTE *ret, BYTE *_FstRGB, BYTE *_EndRGB, float _Per){
    this->gPercent(ret, _FstRGB[0], _FstRGB[1], _FstRGB[2], _EndRGB[0], _EndRGB[1], _EndRGB[2], _Per);
};

void xWF_Draw::gPercent(BYTE *ret, BYTE _fR, BYTE _fG, BYTE _fB, BYTE _eR, BYTE _eG, BYTE _eB, float _Per){
    *(ret+0) = (BYTE)(_fR + (int)((int)_eR - (int)_fR) * _Per) & 0xFF,
    *(ret+1) = (BYTE)(_fG + (int)((int)_eG - (int)_fG) * _Per) & 0xFF,
    *(ret+2) = (BYTE)(_fB + (int)((int)_eB - (int)_fB) * _Per) & 0xFF;
};

// 设置画板颜色
/*===========================================================
            函数: Color
            参数: colorid 颜色索引, rgba=颜色值
            描述: 设置文本颜色
  ===========================================================*/
        //this->Color(xWF::Color::Font, 255, 204,   0, 255);//金色
        //this->Color(xWF::Color::Font, 180, 240,   0, 255);//绿色
        //this->Color(xWF::Color::Font, 120, 220, 220, 255);//蓝色
        //this->Color(xWF::Color::Font, 255, 180, 220, 255);//红色
        //this->Color(xWF::Color::Font,   0,   0,   0, 255);//黑色
void xWF_Draw::Color(BYTE colorid, DWORD rgb, BYTE a)
{
    BYTE r, g, b;
    r = (BYTE)((rgb & 0xFF0000)>>16);
    g = (BYTE)((rgb & 0x00FF00)>>8);
    b = (BYTE) (rgb & 0x0000FF);
    this->Color(colorid, r, g, b, a);
}
void xWF_Draw::Color(BYTE colorid, BYTE r, BYTE g, BYTE b, BYTE a)
{
    //0x01=背景颜色
    if (xWF::isEqual(colorid, xWF::Color::Background)){
        this->bgR=r; this->bgG=g; this->bgB=b; this->bgA=a;
    }
    //0x02=字体颜色
    if (xWF::isEqual(colorid, xWF::Color::Font)){
        this->txtR=r; this->txtG=g; this->txtB=b; this->txtA=a;  
    }
    //0x04=边框颜色
    if (xWF::isEqual(colorid, xWF::Color::Frame)){
        this->fraR=r; this->fraG=g; this->fraB=b; this->fraA=a;
    }
    //0x08=渐变颜色
    if (xWF::isEqual(colorid, xWF::Color::Gradient)){
        this->grdR=r; this->grdG=g; this->grdB=b; this->grdA=a;
    }
    //0x10=透明颜色
    if (a!=0xFF || xWF::isEqual(colorid, xWF::Color::Transparent)){
        if (this->_alpCount>=0xFF) return;
        int i, k, iCount=(int)(this->_alpCount/2+0.66666f);
        for (i=0; i<iCount; i++)
        {
            if (this->alpR[i]==r && this->alpG[i]==g && this->alpB[i]==b){
                this->alpA[i]= a;
                return;
            }
            k = this->_alpCount-i-1;
            if (this->alpR[k]==r && this->alpG[k]==g && this->alpB[k]==b){
                this->alpA[k] = a;
                return;
            }
        }
        this->alpR[this->_alpCount] = r;
        this->alpG[this->_alpCount] = g;
        this->alpB[this->_alpCount] = b;
        this->alpA[this->_alpCount] = a;
        this->_alpCount++;
    }
}
/*===========================================================
            函数: Created
            参数: width=宽度，height=高度，bStroked=是否描边，bgColor=背景色，alphaColor=透明色
            描述: 创建画布
            返回: 成功/失败
  ===========================================================*/
bool  xWF_Draw::Create(int width, int height, bool bStroked, COLORREF bgColor, COLORREF alphaColor)
{
    if (this->_width != width || this->_height != height){
        if (width<1)   width = 1;
        if (height<1) height = 1;
        if(this->hPrevBmp) DeleteObject(this->hPrevBmp);
        if(this->hBMP)     DeleteObject(this->hBMP);
        if(this->hMemDC)   DeleteDC(this->hMemDC);
        //if(this->hDC)      DeleteDC(this->hDC);
        this->hDC = 0;
    }
    if(this->hDC==0)
    {
        this->_Stroked = bStroked; //是否描边
        HDC srcDC = CreateDC("DISPLAY", NULL, NULL, NULL);
        this->hDC = srcDC;
        this->hMemDC = CreateCompatibleDC(this->hDC);

        this->_width = width;
        this->_height= height;
        
        this->hBMP = CreateCompatibleBitmap(srcDC, width, height);
        this->hPrevBmp = (HBITMAP)SelectObject(this->hMemDC, this->hBMP);

        this->_alpCount = 0;
        this->Color(xWF::Color::Transparent, alphaColor, 0);

        this->Color(xWF::Color::Background, bgColor);

        DeleteDC(srcDC);
    }

    this->Clear(); //Refresh
    return (this->hDC!=0);
}

/*===========================================================
            函数: isAlpha()
            描述: 检查颜色值是否是透明色
            返回: 透明度
  ===========================================================*/
unsigned char xWF_Draw::isAlpha(BYTE r, BYTE g, BYTE b, BYTE a)
{
    int iR=0, iG=0, iB=0;
    for (int iAlp=0; iAlp<this->_alpCount; iAlp++)
    {
        iR = abs(r-this->alpR[iAlp]);
        iG = abs(g-this->alpG[iAlp]);
        iB = abs(b-this->alpB[iAlp]);
        if ((r==this->alpR[iAlp] && g==this->alpG[iAlp] && b==this->alpB[iAlp]) ||
            (iR+iG+iB<=3)
        ){

            return this->alpA[iAlp];
            break;
        }
        iR = abs(r-this->alpR[this->_alpCount-iAlp-1]);
        iG = abs(g-this->alpG[this->_alpCount-iAlp-1]);
        iB = abs(b-this->alpB[this->_alpCount-iAlp-1]);
        if ((r==this->alpR[this->_alpCount-iAlp-1] && g==this->alpG[this->_alpCount-iAlp-1] && b==this->alpB[this->_alpCount-iAlp-1]) ||
            (iR+iG+iB<=3)
        ){
            return this->alpA[_alpCount-iAlp-1];
            break;
        }
    }
    //if (r == g && g== b){
    //    if (0x11<=r && r<=0xEF){
    //        return 0x168;
    //    }
    //}

    return a;
}
/*===========================================================
            过程: Refresh
            参数: width=宽度，height=高度，bStroked=是否描边，bgColor=背景色，alphaColor=透明色
            描述: 刷新画布到前端
  ===========================================================*/
void  xWF_Draw::Refresh(HDC hDst, HDC hDstMem
        , int x, int y, int xSrc, int ySrc
    )
{
    if (!this->bInitOk()) return;

    //BITMAP bi;
    struct {
        BITMAPINFOHEADER bih;
        RGBQUAD col[1];
    }bic;

    BITMAPINFO *binf = (BITMAPINFO *)&bic; //= new BITMAPINFO()
    //GetObject(this->hBMP, sizeof(bi), &bi);

    unsigned int size = this->_height * (this->_width+7)/8 * 32;
    unsigned char *lpBitmap = (unsigned char *)malloc(sizeof(unsigned char)*size);

    getBitsTo32(this->hMemDC, this->hBMP, binf, lpBitmap, &size, true, this->alpR[0],this->alpG[0],this->alpB[0]);
    int iX, iY, iPos, iCk;
    unsigned char srcR, srcG, srcB, srcA;
    bool isFinded = false;
    for (iY=0; iY<this->_height; iY++)
    {
        for (iX=0; iX<this->_width; iX++)
        {
            iPos = (iY * this->_width + iX) * 4;
            //ALPHA值按比例相乘
            srcB = lpBitmap[iPos+0];
            srcG = lpBitmap[iPos+1];
            srcR = lpBitmap[iPos+2];
            if (this->_aRcCount>0){
                isFinded = false;
                for (iCk=0; iCk<this->_aRcCount; iCk++) {
                    if (this->aRc[iCk].rc.In( iX, (this->_height-iY) )) {
                        if (this->aRc[iCk].alpha)
                            srcA = this->isAlpha(srcR, srcG, srcB, 0xFF);
                        else
                            srcA = lpBitmap[iPos+3];
                        isFinded = true;
                        break;
                    }
                }
            }
            if(!isFinded){
                srcA = lpBitmap[iPos+3];
            }
            //ALPHA值按比例相乘
            lpBitmap[iPos+0] = srcB * srcA / 255;
            lpBitmap[iPos+1] = srcG * srcA / 255;
            lpBitmap[iPos+2] = srcR * srcA / 255;
            lpBitmap[iPos+3] = srcA;
        }
    }
    if (this->_Stroked){
        unsigned char *bits=(unsigned char *)malloc(sizeof(unsigned char)*size);
        memcpy(&bits[0], &lpBitmap[0], size);
        for (iY=0; iY<this->_height; iY++)
        {
            for (iX=0; iX<this->_width; iX++)
            {
                iPos = (iY * this->_width + iX) * 4;
                if (bits[iPos+3]==0xFF){
                    iCk = -1;
                    if (iY>1){
                        iCk=((iY-1) * this->_width + iX) * 4;
                        if (bits[iCk+3]!=0xFF) {
                            lpBitmap[iCk+0]=lpBitmap[iCk+1]=lpBitmap[iCk+2]=0;
                            lpBitmap[iCk+3]=0xFF;
                        }
                    }
                    if (iY+1<this->_height){
                        iCk=((iY+1) * this->_width + iX) * 4;
                        if (bits[iCk+3]!=0xFF){
                            lpBitmap[iCk+0]=lpBitmap[iCk+1]=lpBitmap[iCk+2]=0;
                            lpBitmap[iCk+3]=0xFF;
                        }
                    }
                    if (iX>1){
                        iCk=(iY * this->_width + iX-1) * 4;
                        if (bits[iCk+3]!=0xFF){
                            lpBitmap[iCk+0]=lpBitmap[iCk+1]=lpBitmap[iCk+2]=0;
                            lpBitmap[iCk+3]=0xFF;
                        }
                    }
                    if (iX+1<this->_width){
                        iCk=(iY * this->_width + iX+1) * 4;
                        if (bits[iCk+3]!=0xFF){
                            lpBitmap[iCk+0]=lpBitmap[iCk+1]=lpBitmap[iCk+2]=0;
                            lpBitmap[iCk+3]=0xFF;
                        }
                    }
                }
            }
        }
        free(bits);
    }
    
    HBITMAP hBgImage = CreateDIBitmap(hDstMem, &binf->bmiHeader, CBM_INIT, lpBitmap, binf, DIB_RGB_COLORS);
    SelectObject(hDstMem, hBgImage);
    
    BitBlt(hDst, x, y, this->_width, this->_height, hDstMem, xSrc, ySrc, SRCCOPY);
    
    DeleteObject(hBgImage);
    
    free(lpBitmap);
    //GlobalFree(lpBitmap);
}
/*===========================================================
            过程: Clear
            描述: 清除画布
  ===========================================================*/
void  xWF_Draw::Clear()
{
    if (!this->bInitOk()) return;
    for(int y=0; y<_height; y++){
        this->gdi_line(0, y, this->_width, y, this->alpR[0], this->alpG[0], this->alpB[0]);
    }
    this->_alpCount = 2;
}

/*===========================================================
            过程: gdi_Box
            参数: x=横坐标, y=纵坐标, w=高度, h=高度, smooth=(低位0x0F=1上2下4左8右)平滑角度、(高位0x70)大小、(高位0x80)发光
                 fill=填充
            描述: 画方框，渐变/纯色背景
  ===========================================================*/
void xWF_Draw::gdi_box(int x, int y, int w, int h)
{
    this->gdi_box(x, y, w, h, 0);
}

void xWF_Draw::gdi_box(int x, int y, int w, int h, BYTE smooth, BYTE fill)
{
    int i=0, id=0, iMax, iFst=0, k=0;
    BYTE clrSd[4][3]={0,0,0,0,0,0}, fix[4]={0,0,0,0}, max = (smooth & 0x70)>>4, glow = (smooth & 0x80);
    BYTE clrBg[3];

    if(max!=0) {
        if ((smooth & 1)==1) fix[0]=max; //0=左上
        if ((smooth & 2)==2) fix[1]=max; //1=右上
        if ((smooth & 4)==4) fix[2]=max; //2=左下
        if ((smooth & 8)==8) fix[3]=max; //3=右下
    }
    LPPOINT p=(LPPOINT)malloc(18*sizeof(POINT));
    memset(p, 0, 18*sizeof(POINT));

    iFst = 0;
    clrBg[0] = this->bgR; clrBg[1] = this->bgG; clrBg[2] = this->bgB;
    clrSd[iFst][0] = this->fraR;
    clrSd[iFst][1] = this->fraG;
    clrSd[iFst][2] = this->fraB;

    this->gPercent(clrSd[iFst+1], clrSd[iFst], clrBg, 0.70f);
    this->gPercent(clrSd[iFst+2], clrSd[iFst], clrBg, 0.30f);
    this->gPercent(clrSd[iFst+3], clrSd[iFst], clrBg, 0.95f);

    // 填充背景
    if (fill) {
        if ((fill & xWF::Fill::Gradient)==xWF::Fill::Gradient) { //0x08=渐变色
            clrSd[iFst+1][0]= this->grdR; clrSd[iFst+1][1] = this->grdG; clrSd[iFst+1][2] = this->grdB;
        }
        this->gdi_fill(x+2, y+2, w-3, h-3, fill);
    }

    POINT Point; HPEN hPen; HGDIOBJ hPenOld;
    iFst = 0;
    if (glow) iFst=-1;
    //id=3; clrSd[id][0] = 0xff;clrSd[id][1] = 0;clrSd[id][2] = 0;

    for (i=iFst; i<2; i++) {
        if (glow && i==iFst) k=1; else k=0;
        id = -1;
        id++; p[id].x=x+i+fix[0]+k;       p[id].y=y+i;
        id++; p[id].x=x+w-1-i-fix[1]-k;   p[id].y=p[id-1].y; //边框-上
        if ((smooth & 2)==2 && max==4){ //1=右上
            p[id].x-=k;
            id++; p[id].x=p[id-1].x+1+k*2;  p[id].y=p[id-1].y+1;
            id++; p[id].x=p[id-1].x+2;      p[id].y=p[id-1].y+1+k;
        }
        id++; p[id].x=x+w-1-i;  p[id].y=y+i+fix[1]+k;
        if (max!=0 || k!=0){ id++; p[id].x=p[id-1].x;   p[id].y=y+h-1-i-fix[3]-k; } //边框-右
        if ((smooth & 8)==8 && max==4){ //3=右下
            p[id].y-=k;
            id++; p[id].x=p[id-1].x-1;      p[id].y=p[id-1].y+2+k;
            id++; p[id].x=p[id-1].x-1-k;    p[id].y=p[id-1].y+1+k;
        }
        id++; p[id].x=x+w-1-i-fix[3]-k;     p[id].y=y+h-1-i;
        if (max!=0 || k!=0){ id++; p[id].x=x+i+fix[2]+k;  p[id].y=p[id-1].y; } //边框-下
        if ((smooth & 4)==4 && max==4){ //2=左下
            if (k) {
                id++; p[id].x=p[id-1].x-3;   p[id].y=p[id-1].y-2;
            } else {
                id++; p[id].x=p[id-1].x-2;  p[id].y=p[id-1].y-1;
                id++; p[id].x=p[id-1].x-1;  p[id].y=p[id-1].y-2;
            }
        }
        id++; p[id].x=x+i;      p[id].y=y+h-1-i-fix[2]-k;
        if (max!=0 || k!=0){ id++; p[id].x=p[id-1].x;   p[id].y=y+i+fix[0]+k; } //边框-左
        if ((smooth & 1)==1 && max==4){ //0=左上
            if (k) {
                id++; p[id].x=p[id-1].x+2;  p[id].y=p[id-1].y-3;
                id++; p[id].x=p[0].x;       p[id].y=p[0].y;
            } else {
                id++; p[id].x=p[id-1].x+1;  p[id].y=p[id-1].y-1;
                id++; p[id].x=p[id-1].x+1;  p[id].y=p[id-1].y-2;
                id++; p[id].x=p[0].x+1;     p[id].y=p[0].y;
            }
        } else {
            id++; p[id].x=p[0].x;   p[id].y=p[0].y;
        }
        iMax = id+1;
        id = i<0? 3: i;
        hPen = CreatePen(0, 1, RGB(clrSd[id][0], clrSd[id][1], clrSd[id][2]));
        hPenOld = SelectObject(this->hMemDC, hPen);
        id = 0;
        MoveToEx(this->hMemDC, p[id].x, p[id].y, &Point);
        for (id=1; id<iMax; id++){
            LineTo(this->hMemDC, p[id].x, p[id].y);
        }
        SelectObject(this->hMemDC, hPenOld);
        DeleteObject(hPen);
    }

    if (max>0) {
        id = -1;
        if ((smooth & 1)==1) { //0=左上
            id++; p[id].x=x+max;        p[id].y=y+1;
            if (max>1) {id++; p[id].x=p[id-1].x-max/2;  p[id].y=p[id-1].y+1;}
            if (max>2) {id++; p[id].x=p[id-1].x-1;      p[id].y=p[id-1].y+2;}
        }
        if ((smooth & 2)==2) { //1=右上
            id++; p[id].x=x+w-1-max;    p[id].y=y+1;
            if (max>1) {id++; p[id].x=p[id-1].x+max/2;  p[id].y=p[id-1].y+1;}
            if (max>2) {id++; p[id].x=p[id-1].x+1;      p[id].y=p[id-1].y+2;}
        }
        if ((smooth & 4)==4) { //2=左下
            id++; p[id].x=x+max;        p[id].y=y+h-1-1;
            if (max>1) {id++; p[id].x=p[id-1].x-max/2;  p[id].y=p[id-1].y-1;}
            if (max>2) {id++; p[id].x=p[id-1].x-1;      p[id].y=p[id-1].y-2;}
        }
        if ((smooth & 8)==8) { //3=右下
            id++; p[id].x=x+w-1-max;    p[id].y=y+h-1-1;
            if (max>1) {id++; p[id].x=p[id-1].x+max/2;  p[id].y=p[id-1].y-1;}
            if (max>2) {id++; p[id].x=p[id-1].x+1;      p[id].y=p[id-1].y-2;}
        }
        iMax = id+1;
        for (id=0; id<iMax; id++){
            this->gdi_point(p[id].x, p[id].y, clrSd[2]);
        }
    }

    delete[] p;
}

/*===========================================================
            过程: gdi_Fill
            参数: x=横坐标，y=纵坐标，w=高度，h=高度
            描述: 填充区域
  ===========================================================*/
void xWF_Draw::gdi_fill(int x, int y, int w, int h, BYTE fill)
{
    int xPos=0, yPos=0, half;
    BYTE clrGrd[3], clrFra[3], tmpClrBG[3];
    clrGrd[0] = this->grdR; clrGrd[1] = this->grdG; clrGrd[2] = this->grdB;
    clrFra[0] = this->fraR; clrFra[1] = this->fraG; clrFra[2] = this->fraB;
    if (h<=w){
        if ((fill & xWF::Fill::Gradient) == xWF::Fill::Gradient) { //0x08=渐变色
            // 渐变背景
            half=h/2;
            for (yPos=0; yPos<half; yPos++){
                this->gPercent(tmpClrBG, clrGrd, clrFra, (yPos+1.0f)/half*0.5f);
                this->gdi_line(x, y+yPos, x+w-1, y+yPos, tmpClrBG[0], tmpClrBG[1], tmpClrBG[2]);

                this->gPercent(tmpClrBG, clrFra, clrGrd, (yPos+1.0f)/half*0.6f);
                this->gdi_line(x, y+yPos+half, x+w-1, y+yPos+half, tmpClrBG[0], tmpClrBG[1], tmpClrBG[2]);
            }
        } else { //0x01=纯色
            for(yPos=0; yPos<h; yPos++){
                this->gdi_line(x, y+yPos, x+w-1, y+yPos, this->bgR, this->bgG, this->bgB);
            }
        }
    } else {
        if ((fill & xWF::Fill::Gradient) == xWF::Fill::Gradient) { //0x08=渐变色
            // 渐变背景
            half=w/2;
            for (xPos=0; xPos<w; xPos++){
                this->gPercent(tmpClrBG, clrGrd, clrFra, (xPos+1.0f)/half*0.5f);
                this->gdi_line(x+xPos, y, x+xPos, y+h-1, tmpClrBG[0], tmpClrBG[1], tmpClrBG[2]);

                this->gPercent(tmpClrBG, clrFra, clrGrd, (xPos+1.0f)/half*0.6f);
                this->gdi_line(x+xPos+half, y, x+xPos+half, y+h-1, tmpClrBG[0], tmpClrBG[1], tmpClrBG[2]);
            }
        } else { //0x01=纯色
            for(xPos=0; xPos<w; xPos++){
                this->gdi_line(x+xPos, y, x+xPos, y+h-1, this->bgR, this->bgG, this->bgB);
            }
        }
    }
}

/*===========================================================
            过程: gdi_Icon
            参数: x=横坐标，y=纵坐标，hIcon=图标句柄，cxWidth=宽度，cyHeight=高度
            描述: 画图标
  ===========================================================*/
void xWF_Draw::gdi_icon(int x, int y, HICON hIcon, int cxWidth, int cyHeight){
    DrawIconEx(this->hMemDC, x, y, hIcon, cxWidth, cyHeight, 0, 0, DI_NORMAL );
}
/*===========================================================
            过程: gdi_Image
            参数: x=横坐标，y=纵坐标，hImage=图像句柄，cxWidth=宽度，cyHeight=高度
            描述: 画图像
  ===========================================================*/
void xWF_Draw::gdi_image(int x, int y, HBITMAP hImage, int cxWidth, int cyHeight){
    HDC _tmpDC = CreateCompatibleDC(this->hMemDC);
        SelectObject(_tmpDC, hImage);
        BitBlt(this->hMemDC, x, y, cxWidth, cyHeight, _tmpDC, 0, 0, SRCCOPY);
        //StretchBlt(base->hDC, Rect.left, Rect.top, iBoxSize, iBoxSize, _hDC, 0, 0, iBoxSize, iBoxSize, SRCCOPY);
    DeleteDC(_tmpDC);
}
/*===========================================================
            过程: gdi_line
            参数: X1,Y1=开始坐标点，X2,Y2=结束坐标点，lineWidth=线条宽度
            描述: 画线条
  ===========================================================*/
void xWF_Draw::gdi_line(int X1, int Y1, int X2, int Y2, int lineWidth)
{
    this->gdi_line(X1, Y1, X2, Y2, this->fraR, this->fraG, this->fraB, lineWidth);
}
void xWF_Draw::gdi_line(int X1, int Y1, int X2, int Y2, BYTE r, BYTE g, BYTE b, int lineWidth)
{
    if (!this->bInitOk()) return;

    POINT Point; HPEN hPen; HGDIOBJ hPenOld;
    const COLORREF Color=RGB(r, g, b);
    hPen = CreatePen(0, lineWidth, Color);
    hPenOld = SelectObject(this->hMemDC, hPen);
    MoveToEx(this->hMemDC, X1, Y1, &Point);
    LineTo(this->hMemDC, X2, Y2);
    SelectObject(this->hMemDC, hPenOld);
    DeleteObject(hPen);
}
/*===========================================================
            函数: gdi_Point
            参数: x=横坐标，y=纵坐标，Color=rgba颜色
            返回: 成功/失败
            描述: 画点
  ===========================================================*/
long xWF_Draw::gdi_point(int x, int y, BYTE *clrRGB){
    DWORD Color = clrRGB[0] + clrRGB[1]*0x100 + clrRGB[2]*0x10000;
    return SetPixel(this->hMemDC, x, y, Color);
}
long xWF_Draw::gdi_point(int x, int y, int *clrRGB){
    DWORD Color = clrRGB[0] + clrRGB[1]*0x100 + clrRGB[2]*0x10000;
    return SetPixel(this->hMemDC, x, y, Color);
}
long xWF_Draw::gdi_point(int x, int y, DWORD Color){
    return SetPixel(this->hMemDC, x, y, Color);
}
/*===========================================================
            函数: gdi_text
            参数: x=横坐标，y=纵坐标，str=字符串，Align=对齐方式，w=宽度，h=高度, bFill=是否填充背景
            返回: 宽度
            描述: 画文本
  ===========================================================*/
int xWF_Draw::gdi_text(int x, int y, char *str, int Align, int w, int h, bool bFill)
{
    if (!this->bInitOk()) return 0;
    // 根据字体属性创建字体对象
    LOGFONT lf;

    memset(&lf, 0, sizeof(lf));
    lf.lfHeight        = -MulDiv(this->_Size, GetDeviceCaps(GetDC(0), LOGPIXELSY), 72); //字体高度
    lf.lfCharSet       = DEFAULT_CHARSET | ANSI_CHARSET; //字符集
    lf.lfWeight        = this->_Bold;                    //粗体, 取值: 0/700/1000
    lf.lfOutPrecision  = OUT_STROKE_PRECIS;              //输出精度
    lf.lfClipPrecision = CLIP_CHARACTER_PRECIS;          //剪裁精度

    //lf.lfEscapement    = Escap*10; //旋转角度 90
    //lfItalic     //斜体
    //lfUnderline  //下划线
    //lfStrikeOut  //删除线
    lstrcpy(lf.lfFaceName, this->_Name);                 //字体名称

    HFONT hFont = CreateFontIndirect(&lf);
    //GlobalFree(&lf);

        HFONT hPrevFont = (HFONT)SelectObject(this->hMemDC, hFont);
        SIZE size; int len = strlen(str);
        GetTextExtentPoint32(this->hMemDC, str, len, &size);

            RECT Rect;
            Rect.left = x; Rect.right  = x+(w==0 ? size.cx+4 : w);
            Rect.top  = y; Rect.bottom = y+(h==0 ? size.cy+4 : h);
            
            SetBkColor(this->hMemDC, 0);
            SetTextColor(this->hMemDC, RGB(this->txtR, this->txtG, this->txtB));
            SetBkMode(this->hMemDC, TRANSPARENT);

            if (bFill){
                for (int yPos=Rect.top+1; yPos<Rect.bottom; yPos++){
                    this->gdi_line(Rect.left, yPos, Rect.right, yPos, this->bgR, this->bgG, this->bgB);
                }
            }
            Rect.left+=2; Rect.right -=2;
            Rect.top +=2; Rect.bottom-=2;
            const UINT format = DT_END_ELLIPSIS | DT_VCENTER | Align; //DT_CENTER | DT_SINGLELINE | DT_WORDBREAK
            DrawText(hMemDC, str, -1, &Rect, format);
            
            SelectObject(this->hMemDC, hPrevFont);
        DeleteObject(hPrevFont);
    DeleteObject(hFont);
    return size.cy;
}

/*===========================================================
            函数: gdi_textRC
            参数: x=横坐标，y=纵坐标，str=字符串，Align=对齐方式，w=高度，h=高度, bFill=是否填充背景
            返回: 宽度
            描述: 画文本
  ===========================================================*/
void xWF_Draw::gdi_getTextRCBegin()
{
    if (!hMemDC_RC){
        HDC srcDC = CreateDC("DISPLAY", NULL, NULL, NULL);
        this->hMemDC_RC = CreateCompatibleDC(srcDC);

        this->hBMP_RC = CreateCompatibleBitmap(srcDC, this->_width, this->_height);
        this->hPrevBMP_RC = (HBITMAP)SelectObject(this->hMemDC_RC, this->hBMP_RC);

        DeleteDC(srcDC);
    }
    // 根据字体属性创建字体对象
    LOGFONT lf;
    
    memset(&lf, 0, sizeof(lf));
    lf.lfHeight        = -MulDiv(this->_Size, GetDeviceCaps(GetDC(0), LOGPIXELSY), 72); //字体高度
    lf.lfCharSet       = DEFAULT_CHARSET | ANSI_CHARSET; //字符集
    lf.lfWeight        = this->_Bold;                    //粗体, 取值: 0/700/1000
    lf.lfOutPrecision  = OUT_STROKE_PRECIS;              //输出精度
    lf.lfClipPrecision = CLIP_CHARACTER_PRECIS;          //剪裁精度

    //lf.lfEscapement    = Escap*10; //旋转角度 90
    //lfItalic     //斜体
    //lfUnderline  //下划线
    //lfStrikeOut  //删除线
    lstrcpy(lf.lfFaceName, this->_Name);                 //字体名称
    this->hFont_RC = CreateFontIndirect(&lf);
    //GlobalFree(&lf);

    this->hPrevFont_RC = (HFONT)SelectObject(this->hMemDC_RC, this->hFont_RC);
}
bool xWF_Draw::gdi_getTextRC(char * str, int *w, int *h)
{
    SIZE size; int len = strlen(str);
    BOOL ret=GetTextExtentPoint32(this->hMemDC_RC, str, len, &size);
    if (*w<size.cx) *w=size.cx+4; 
    if (*h<size.cy) *h=size.cy+4;

    return (ret!=FALSE);
}
void xWF_Draw::gdi_getTextRCEnd()
{
    SelectObject(this->hMemDC_RC, this->hPrevFont_RC);
    if(this->hPrevFont_RC) DeleteObject(this->hPrevFont_RC);
    if(this->hFont_RC)     DeleteObject(this->hFont_RC);
}
/*===========================================================
            函数: LoadImage
            参数: arrImage  字节数组
                 sizeImage 数组大小
            返回: IPicture对象
            描述: 加载图片
  ===========================================================*/
IPicture *xWF_Draw::LoadImage(char *arrData, int arrSize)
{
    IPicture *pPic;
    IStream  *pStm;
    LPVOID   lpMem = NULL;
    HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, arrSize);
    if (hMem != 0) {
        lpMem = GlobalLock(hMem);
        if (lpMem != 0) {
            CopyMemory(lpMem, &arrData[0], arrSize);
            GlobalUnlock(hMem);
            if (CreateStreamOnHGlobal(hMem, TRUE, &pStm) == 0) {
                OleLoadPicture(pStm, arrSize, 0, IID_IPicture, (LPVOID *)&pPic);
                return pPic;
            }
        }
    }
	return 0;
}