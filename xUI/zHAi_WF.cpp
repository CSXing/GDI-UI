
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

    /* ���뷽ʽ */
    BYTE Align::Left     = 0;
    BYTE Align::Center   = DT_CENTER;
    BYTE Align::Right    = DT_RIGHT;
    BYTE Align::VCenter  = DT_VCENTER | DT_SINGLELINE | DT_WORDBREAK;

    /* ����� */
    BYTE Click::Double   = 0x10;    //0x10=˫��
    BYTE Click::Down     = 0x80;    //0x80=���� ~0x80=����
    BYTE Click::LBtn     = 0x01;    //0x01=�������
    BYTE Click::MBtn     = 0x02;    //0x02=�м�����
    BYTE Click::RBtn     = 0x04;    //0x04=�Ҽ�����
    BYTE Click::LBtnDb   = Click::LBtn | Click::Double; //0x11=���˫��
    BYTE Click::MBtnDb   = Click::MBtn | Click::Double; //0x12=�м�˫��
    BYTE Click::RBtnDb   = Click::RBtn | Click::Double; //0x14=�Ҽ�˫��
    
    BYTE Color::Background  = (1<<0);   //0x01=������ɫ
    BYTE Color::Font        = (1<<1);   //0x02=������ɫ
    BYTE Color::Frame       = (1<<2);   //0x04=�߿���ɫ
    BYTE Color::Gradient    = (1<<3);   //0x08=������ɫ
    BYTE Color::Transparent = (1<<4);   //0x10=͸����ɫ
    
    /* �ؼ����� */
    BYTE Control::Button    = 0x01; //0x01=��ť
    BYTE Control::Check     = 0x02; //0x02=��ѡ��
    BYTE Control::Combo     = 0x03; //0x03=��Ͽ�
    BYTE Control::Edit      = 0x04; //0x04=�༭��
    BYTE Control::Grid      = 0x05; //0x05=�����б�
    BYTE Control::Label     = 0x06; //0x06=��ǩ�ı�
    BYTE Control::Status    = 0x07; //0x07=״̬��
    BYTE Control::Tree      = 0x08; //0x08=����

    /* ϵͳ��ť */
    BYTE SysBtns::Icon   = (1<<0);
    BYTE SysBtns::Min    = (1<<1);
    BYTE SysBtns::Max    = (1<<2);
    BYTE SysBtns::Close  = (1<<3);
    BYTE SysBtns::Title  = (1<<4);
    BYTE SysBtns::Resize = (1<<5);
    
    /* ���λ��״̬ */
    USHORT MouseIn::None   = 0;        //���ڴ�����
    USHORT MouseIn::Icon   = (1<<0);   //��ͼ��
    USHORT MouseIn::Title  = (1<<1);   //�ڱ�����
    USHORT MouseIn::Min    = (1<<2);   //����С����ť
    USHORT MouseIn::Max    = (1<<3);   //����󻯰�ť
    USHORT MouseIn::Close  = (1<<4);   //�ڹرհ�ť
    USHORT MouseIn::Resize = (1<<5);   //�ڸı��Сλ��
    USHORT MouseIn::Client = (1<<9);   //�ڿͻ���
    
    BYTE Smooth::None    = 0;       //����
    BYTE Smooth::LTop    = (1<<0);  //0x01=����
    BYTE Smooth::RTop    = (1<<1);  //0x02=����
    BYTE Smooth::LBottom = (1<<2);  //0x04=����
    BYTE Smooth::RBottom = (1<<3);  //0x08=����
    BYTE Smooth::Size1   = (1<<4);  //0x10=��С1
    BYTE Smooth::Size2   = (1<<5);  //0x20=��С2
    BYTE Smooth::Size4   = (1<<6);  //0x40=��С4
    BYTE Smooth::Glow    = (1<<7);  //0x80=����
    BYTE Smooth::Top     = Smooth::LTop | Smooth::RTop;        //0x03=��
    BYTE Smooth::Left    = Smooth::LTop | Smooth::LBottom;     //0x05=��
    BYTE Smooth::Right   = Smooth::RTop | Smooth::RBottom;     //0x0A=��
    BYTE Smooth::Bottom  = Smooth::LBottom | Smooth::RBottom;  //0x0C=��
    BYTE Smooth::Full    = Smooth::LTop | Smooth::RTop | Smooth::LBottom | Smooth::RBottom;  //0x0F=ȫ
    
    BYTE Fill::Solid    = (1<<0); //0x01=��ɫ
    BYTE Fill::Gradient = (1<<3); //0x08=����ɫ
};