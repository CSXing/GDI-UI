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
#pragma once

#include <windows.h>
#include <stdio.h>
#include <stdint.h>
#include <Olectl.h>

namespace xWF
{
    static int zHAi_Icon[16][16] = {
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {0,1,2,2,2,2,2,2,2,2,2,2,2,2,2,1},
        {0,1,2,2,2,2,2,2,2,2,2,2,2,2,2,1},
        {0,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1},
        {0,1,2,2,1,1,1,1,1,1,1,1,1,2,2,1},
        {0,1,2,2,1,2,2,2,2,2,1,1,2,2,2,1},
        {0,1,2,2,2,1,1,1,1,1,1,2,2,2,2,1},
        {0,1,2,2,2,2,2,1,1,2,2,2,1,2,2,1},
        {0,1,2,1,1,1,1,1,1,1,1,1,1,2,2,1},
        {0,1,2,2,2,2,2,1,1,2,2,1,2,2,2,1},
        {0,1,2,2,2,2,2,1,1,2,2,1,2,2,2,1},
        {0,1,2,2,2,2,2,1,1,1,1,1,1,2,2,1},
        {0,1,2,2,2,2,2,2,2,2,2,2,2,2,2,1},
        {0,1,2,2,2,2,2,2,2,2,2,2,2,2,2,1},
        {0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
    };
    bool isEqual(BYTE Src, BYTE Des);
    bool isEqual(USHORT Src, USHORT Des);
    bool isEqual(UINT Src, UINT Des);
    bool isMouseDown(BYTE btn);
    /*=====================================================================*/
    class Align
    {
    public:
        static BYTE Left;
        static BYTE Center;
        static BYTE Right;
        static BYTE VCenter;
    };
    /*=====================================================================*/
    class Color //��ɫ
    {
    public:
        static BYTE Background; //0x01=������ɫ
        static BYTE Font;       //0x02=������ɫ
        static BYTE Frame;      //0x04=�߿���ɫ
        static BYTE Gradient;   //0x08=������ɫ
        static BYTE Transparent;//0x10=͸����ɫ
    };
    /*=====================================================================*/
    class Click //�����
    {
    public:
        static BYTE LBtn;   //�������
        static BYTE LBtnDb; //    ˫��
        static BYTE MBtn;   //�м�����
        static BYTE MBtnDb; //    ˫��
        static BYTE RBtn;   //�Ҽ�����
        static BYTE RBtnDb; //    ˫��
        static BYTE Double, Down;
    };
    /*=====================================================================*/
    class Control //�ؼ�����
    {
        static BYTE Button; //0x01=��ť
        static BYTE Check;  //0x02=��ѡ��
        static BYTE Combo;  //0x03=��Ͽ�
        static BYTE Edit;   //0x04=�༭��
        static BYTE Grid;   //0x05=�����б�
        static BYTE Label;  //0x06=��ǩ�ı�
        static BYTE Status; //0x07=״̬��
        static BYTE Tree;   //0x08=����
    };
    /*=====================================================================*/
    class SysBtns // ϵͳ��ť���������������±߿���С������󻯼��رգ�
    {
    public:
        static BYTE Icon;
        static BYTE Title;
        static BYTE Min;
        static BYTE Max;
        static BYTE Close;
        static BYTE Resize;
    };
    /*=====================================================================*/
    class MouseIn //���λ��
    {
    public:
        static USHORT None;    //���ڴ�����
        static USHORT Icon;    //��ͼ��
        static USHORT Title;   //�ڱ�����
        static USHORT Min;     //����С����ť
        static USHORT Max;     //����󻯰�ť
        static USHORT Close;   //�ڹرհ�ť
        static USHORT Resize;  //�ڸı��Сλ��
        static USHORT Client;  //�ڿͻ���
    };
    /*=====================================================================*/
    class Smooth //ƽ��
    {
    public:
        static BYTE None;       //����
        static BYTE LTop;       //0x01=����
        static BYTE RTop;       //0x02=����
        static BYTE LBottom;    //0x04=����
        static BYTE RBottom;    //0x08=����
        static BYTE Top;
        static BYTE Bottom;
        static BYTE Left;
        static BYTE Right;
        static BYTE Full;
        static BYTE Size1;      //0x10=��С1
        static BYTE Size2;      //0x20=��С2
        static BYTE Size4;      //0x40=��С4
        static BYTE Glow;       //0x80=����
    };
    /*=====================================================================*/
    class Fill //ƽ��
    {
    public:
        static BYTE Solid;      //0x01=��ɫ
        static BYTE Gradient;   //0x08=����ɫ
    };
};



/* ===============================================
    ��Դ���ʻ���
   =============================================== */
class CLocks;
class CLocks
{
public:
	//��ʼ���ٽ���
    CLocks()  { ::InitializeCriticalSection(&m_crit); }
    //�ͷ����ٽ���
    ~CLocks() { ::DeleteCriticalSection(&m_crit); }
	//�����ٽ���
	void Enter() { ::EnterCriticalSection(&m_crit); }
	//�뿪�ٽ���
	void Leave() { ::LeaveCriticalSection(&m_crit); }

private:
	//�ڲ��̻߳������
	CRITICAL_SECTION  m_crit;  //����һ���ٽ���
};
#pragma pack(1)
    /* ===============================================
        �����Сλ��
       =============================================== */
    typedef struct xWF_tagRect
    {
        int l, t, r, b, w, h;
        void Calc() {
            this->r = this->l + this->w;
            this->b = this->t + this->h;
        };
        void Set(int left, int top, int width, int height) {
            this->l = left;  this->t = top;
            this->w = width; this->h = height;
            this->Calc();
        };
        void Set(int width, int height) {
            this->Set(0, 0, width, height);
        };
        bool In(int x, int y){
            return (this->l<=x && x<=this->r && this->t<=y && y<=this->b);
        }
    } *xWF_pRect;
    /* ===============================================
        ͸������λ��
       =============================================== */
    typedef struct xWF_tagRect_Alpha
    {
        xWF_tagRect rc;
        bool alpha;
    } *xWF_pRect_Alpha;
    /* ===============================================
        �¼������ص�����
       =============================================== */
    typedef VOID (CALLBACK* tEvent_OnClick)();
    typedef VOID (CALLBACK* tEvent_OnMouse)(int x, int y, int mousedown);
    typedef VOID (CALLBACK* tEvent_OnKey)(int key, int down);
    
    /* ===============================================
        �����Сλ��
       =============================================== */
    typedef struct xWF_tagCtrls
    {
        BYTE type;                  //����
        tEvent_OnClick funcClick;   //�¼�-����
        tEvent_OnClick funcKey;     //�¼�-����
        xWF_pRect rc;               //����λ��
        struct xWF_tagCtrls *next;  //��һ��
    } *xWF_pCtrls;
#pragma pack()
    
#define SetMinmize(hWnd) SendMessage(hWnd, WM_SYSCOMMAND, SC_MINIMIZE, 0) //��С��
#define SetRestore(hWnd) SendMessage(hWnd, WM_SYSCOMMAND, SC_RESTORE,  0) //��ԭ
#define SetMaxmize(hWnd) SendMessage(hWnd, WM_SYSCOMMAND, SC_MAXIMIZE, 0) //���
#define SetLBtnUP(hWnd, x,y) SendMessage(hWnd, WM_LBUTTONUP, 0, MAKELPARAM(x,y))
    
#include "xDraw.h"      //������ͼ��
//#include "xButton.h"    //0x01=��ť
//#include "xCheck.h"     //0x02=��ѡ��
//#include "xCombo.h"     //0x03=��Ͽ�
//#include "xEdit.h"      //0x04=�༭��
//#include "xGrid.h"      //0x05=�����б�
#include "xLabel.h"     //0x06=��ǩ�ı�
//#include "xStatus.h"    //0x07=״̬��
//#include "xTree.h"      //0x08=����
#include "xContainer.h" //�ؼ�������
#include "xWinForm.h"   //������