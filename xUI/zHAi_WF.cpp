
#include "zHAi_WF.h"

namespace xWF
{
    bool isEqual(BYTE Src, BYTE Des){
        return isEqual((UINT)Src, (UINT)Des);
    };
    bool isEqual(USHORT Src, USHORT Des){
        return isEqual((UINT)Src, (UINT)Des);
    };
    bool isEqual(UINT Src, UINT Des){
        if ((Src & Des)==Des) return true;
        return false;
    };

    bool isMouseDown(BYTE btn){
        if ((btn & Click::Down)==Click::Down)
            return true;
        else
            return false;
    };

    /* 对齐方式 */
    BYTE Align::Left     = 0;
    BYTE Align::Center   = DT_CENTER;
    BYTE Align::Right    = DT_RIGHT;
    BYTE Align::VCenter  = DT_VCENTER | DT_SINGLELINE | DT_WORDBREAK;

    /* 鼠标点击 */
    BYTE Click::Double   = 0x10;    //0x10=双击
    BYTE Click::Down     = 0x80;    //0x80=按下 ~0x80=弹起
    BYTE Click::LBtn     = 0x01;    //0x01=左键单击
    BYTE Click::MBtn     = 0x02;    //0x02=中键单击
    BYTE Click::RBtn     = 0x04;    //0x04=右键单击
    BYTE Click::LBtnDb   = Click::LBtn | Click::Double; //0x11=左键双击
    BYTE Click::MBtnDb   = Click::MBtn | Click::Double; //0x12=中键双击
    BYTE Click::RBtnDb   = Click::RBtn | Click::Double; //0x14=右键双击
    
    BYTE Color::Background  = (1<<0);   //0x01=背景颜色
    BYTE Color::Font        = (1<<1);   //0x02=字体颜色
    BYTE Color::Frame       = (1<<2);   //0x04=边框颜色
    BYTE Color::Gradient    = (1<<3);   //0x08=渐变颜色
    BYTE Color::Transparent = (1<<4);   //0x10=透明颜色
    
    /* 控件类型 */
    BYTE Control::Button    = 0x01; //0x01=按钮
    BYTE Control::Check     = 0x02; //0x02=复选框
    BYTE Control::Combo     = 0x03; //0x03=组合框
    BYTE Control::Edit      = 0x04; //0x04=编辑框
    BYTE Control::Grid      = 0x05; //0x05=网格列表
    BYTE Control::Label     = 0x06; //0x06=标签文本
    BYTE Control::Status    = 0x07; //0x07=状态栏
    BYTE Control::Tree      = 0x08; //0x08=树形

    /* 系统按钮 */
    BYTE SysBtns::Icon   = (1<<0);
    BYTE SysBtns::Min    = (1<<1);
    BYTE SysBtns::Max    = (1<<2);
    BYTE SysBtns::Close  = (1<<3);
    BYTE SysBtns::Title  = (1<<4);
    BYTE SysBtns::Resize = (1<<5);
    
    /* 鼠标位置状态 */
    USHORT MouseIn::None   = 0;        //不在窗口上
    USHORT MouseIn::Icon   = (1<<0);   //在图标
    USHORT MouseIn::Title  = (1<<1);   //在标题栏
    USHORT MouseIn::Min    = (1<<2);   //在最小化按钮
    USHORT MouseIn::Max    = (1<<3);   //在最大化按钮
    USHORT MouseIn::Close  = (1<<4);   //在关闭按钮
    USHORT MouseIn::Resize = (1<<5);   //在改变大小位置
    USHORT MouseIn::Client = (1<<9);   //在客户区
    
    BYTE Smooth::None    = 0;       //方框
    BYTE Smooth::LTop    = (1<<0);  //0x01=左上
    BYTE Smooth::RTop    = (1<<1);  //0x02=右上
    BYTE Smooth::LBottom = (1<<2);  //0x04=左下
    BYTE Smooth::RBottom = (1<<3);  //0x08=右下
    BYTE Smooth::Size1   = (1<<4);  //0x10=大小1
    BYTE Smooth::Size2   = (1<<5);  //0x20=大小2
    BYTE Smooth::Size4   = (1<<6);  //0x40=大小4
    BYTE Smooth::Glow    = (1<<7);  //0x80=发光
    BYTE Smooth::Top     = Smooth::LTop | Smooth::RTop;        //0x03=上
    BYTE Smooth::Left    = Smooth::LTop | Smooth::LBottom;     //0x05=左
    BYTE Smooth::Right   = Smooth::RTop | Smooth::RBottom;     //0x0A=左
    BYTE Smooth::Bottom  = Smooth::LBottom | Smooth::RBottom;  //0x0C=下
    BYTE Smooth::Full    = Smooth::LTop | Smooth::RTop | Smooth::LBottom | Smooth::RBottom;  //0x0F=全
    
    BYTE Fill::Solid    = (1<<0); //0x01=纯色
    BYTE Fill::Gradient = (1<<3); //0x08=渐变色
};