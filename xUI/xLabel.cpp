#include "zHAi_WF.h"

/* ==========================================================
            ����: Init
            ����: left=��top=�ϣ�width=��, height=��
            ����: ��ʼ��
   ========================================================== */
xLabel::xLabel()
{
    this->_length = 0;
    this->_text   = 0;
    memset(&this->_rc, 0, sizeof(struct xWF_tagCtrls));
}
xLabel::xLabel(const int x, const int y, const int width, const int height, const char* text)
{
    this->_rc.Set(x, y, width, height);
    this->Set(text);
}

xLabel::~xLabel()
{
    if (this->_length) free(this->_text);
    if (this->_base) delete this->_base;
}

/* ==========================================================
            ����: Set
            ����: xy=����, draw=��ͼ����, text=�ı�
            ����: �������ꡢ���û�ͼ���������ı�
   ========================================================== */
/* �������� */
void xLabel::Set(const int x, const int y)
{
    this->_rc.l = x; this->_rc.t = y;
}
/* ���û�ͼ���� */
void xLabel::Set(xWF_Draw *draw)
{
    this->_base = draw;
}
/* �����ı� */
void xLabel::Set(const char* text)
{
    int len = strlen(text);
    if (this->_length <len ) {
        if (this->_length) free(this->_text);
        this->_length = len;
        this->_text   = (char*)malloc(sizeof(char) * len+1);
        memset(this->_text, 0, len+1);
    }
    memcpy(this->_text, text, len);
}

/*===========================================================
            ����: BindOnClick
            ����: CallbackFunc=�ص�����ָ��
            ����: ���¼�_����
  ===========================================================*/
void xLabel::BindOnClick(tEvent_OnClick CallbackFunc)
{
    this->_funcClick = CallbackFunc;
}