/********************************************************
Create: 2019.12.02
Editor: 2022-03-15
==============================
  Version: 1.0.2022
   Author: X!ng,cHEn 『宅』910955951
Copyright: 2019 - 2020(C)
==============================
Description:
      窗口标题栏绘制功能
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
    class Color //颜色
    {
    public:
        static BYTE Background; //0x01=背景颜色
        static BYTE Font;       //0x02=字体颜色
        static BYTE Frame;      //0x04=边框颜色
        static BYTE Gradient;   //0x08=渐变颜色
        static BYTE Transparent;//0x10=透明颜色
    };
    /*=====================================================================*/
    class Click //鼠标点击
    {
    public:
        static BYTE LBtn;   //左键单击
        static BYTE LBtnDb; //    双击
        static BYTE MBtn;   //中键单击
        static BYTE MBtnDb; //    双击
        static BYTE RBtn;   //右键单击
        static BYTE RBtnDb; //    双击
        static BYTE Double, Down;
    };
    /*=====================================================================*/
    class Control //控件类型
    {
        static BYTE Button; //0x01=按钮
        static BYTE Check;  //0x02=复选框
        static BYTE Combo;  //0x03=组合框
        static BYTE Edit;   //0x04=编辑框
        static BYTE Grid;   //0x05=网格列表
        static BYTE Label;  //0x06=标签文本
        static BYTE Status; //0x07=状态栏
        static BYTE Tree;   //0x08=树形
    };
    /*=====================================================================*/
    class SysBtns // 系统按钮（标题栏、左右下边框、最小化、最大化及关闭）
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
    class MouseIn //鼠标位置
    {
    public:
        static USHORT None;    //不在窗口上
        static USHORT Icon;    //在图标
        static USHORT Title;   //在标题栏
        static USHORT Min;     //在最小化按钮
        static USHORT Max;     //在最大化按钮
        static USHORT Close;   //在关闭按钮
        static USHORT Resize;  //在改变大小位置
        static USHORT Client;  //在客户区
    };
    /*=====================================================================*/
    class Smooth //平滑
    {
    public:
        static BYTE None;       //方框
        static BYTE LTop;       //0x01=左上
        static BYTE RTop;       //0x02=右上
        static BYTE LBottom;    //0x04=左下
        static BYTE RBottom;    //0x08=右下
        static BYTE Top;
        static BYTE Bottom;
        static BYTE Left;
        static BYTE Right;
        static BYTE Full;
        static BYTE Size1;      //0x10=大小1
        static BYTE Size2;      //0x20=大小2
        static BYTE Size4;      //0x40=大小4
        static BYTE Glow;       //0x80=发光
    };
    /*=====================================================================*/
    class Fill //平滑
    {
    public:
        static BYTE Solid;      //0x01=纯色
        static BYTE Gradient;   //0x08=渐变色
    };
};



/* ===============================================
    资源访问互斥
   =============================================== */
class CLocks;
class CLocks
{
public:
	//初始化临界区
    CLocks()  { ::InitializeCriticalSection(&m_crit); }
    //释放里临界区
    ~CLocks() { ::DeleteCriticalSection(&m_crit); }
	//进人临界区
	void Enter() { ::EnterCriticalSection(&m_crit); }
	//离开临界区
	void Leave() { ::LeaveCriticalSection(&m_crit); }

private:
	//内部线程互斥对象
	CRITICAL_SECTION  m_crit;  //设置一个临界区
};
#pragma pack(1)
    /* ===============================================
        矩阵大小位置
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
        透明矩阵位置
       =============================================== */
    typedef struct xWF_tagRect_Alpha
    {
        xWF_tagRect rc;
        bool alpha;
    } *xWF_pRect_Alpha;
    /* ===============================================
        事件触发回调函数
       =============================================== */
    typedef VOID (CALLBACK* tEvent_OnClick)();
    typedef VOID (CALLBACK* tEvent_OnMouse)(int x, int y, int mousedown);
    typedef VOID (CALLBACK* tEvent_OnKey)(int key, int down);
    
    /* ===============================================
        矩阵大小位置
       =============================================== */
    typedef struct xWF_tagCtrls
    {
        BYTE type;                  //类型
        tEvent_OnClick funcClick;   //事件-单击
        tEvent_OnClick funcKey;     //事件-按键
        xWF_pRect rc;               //坐标位置
        struct xWF_tagCtrls *next;  //下一个
    } *xWF_pCtrls;
#pragma pack()
    
#define SetMinmize(hWnd) SendMessage(hWnd, WM_SYSCOMMAND, SC_MINIMIZE, 0) //最小化
#define SetRestore(hWnd) SendMessage(hWnd, WM_SYSCOMMAND, SC_RESTORE,  0) //还原
#define SetMaxmize(hWnd) SendMessage(hWnd, WM_SYSCOMMAND, SC_MAXIMIZE, 0) //最大化
#define SetLBtnUP(hWnd, x,y) SendMessage(hWnd, WM_LBUTTONUP, 0, MAKELPARAM(x,y))
    
#include "xDraw.h"      //基础画图类
//#include "xButton.h"    //0x01=按钮
//#include "xCheck.h"     //0x02=复选框
//#include "xCombo.h"     //0x03=组合框
//#include "xEdit.h"      //0x04=编辑框
//#include "xGrid.h"      //0x05=网格列表
#include "xLabel.h"     //0x06=标签文本
//#include "xStatus.h"    //0x07=状态栏
//#include "xTree.h"      //0x08=树形
#include "xContainer.h" //控件集合类
#include "xWinForm.h"   //窗口类