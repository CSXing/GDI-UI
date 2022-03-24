#include "zHAi_WF.h"

/* ==========================================================
            函数: Init
            参数: left=左，top=上，width=宽, height=高
            描述: 初始化
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
            过程: Set
            参数: xy=坐标, draw=画图对象, text=文本
            描述: 设置坐标、设置画图对象、设置文本
   ========================================================== */
/* 设置坐标 */
void xLabel::Set(const int x, const int y)
{
    this->_rc.l = x; this->_rc.t = y;
}
/* 设置画图对象 */
void xLabel::Set(xWF_Draw *draw)
{
    this->_base = draw;
}
/* 设置文本 */
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
            过程: BindOnClick
            参数: CallbackFunc=回调函数指针
            描述: 绑定事件_单击
  ===========================================================*/
void xLabel::BindOnClick(tEvent_OnClick CallbackFunc)
{
    this->_funcClick = CallbackFunc;
}