#include "zHAi_WF.h"


/* ==========================================================
            函数: Init
            参数: left=左，top=上，width=宽, height=高
            描述: 初始化
   ========================================================== */
xContainer::xContainer()
{
    memset(&this->_ctrls, 0, sizeof(struct xWF_tagCtrls));
    this->_last = &this->_ctrls;
}
xContainer::xContainer(xWF_pRect rc)
{
    this->_ctrls.rc = rc;
    this->_last = &this->_ctrls;
}

xContainer::~xContainer()
{
    xWF_pCtrls item, delItem;
    for(item = this->_last->next; item;)
    {
        delItem=item;
            item=item->next;
        delete delItem;
    }
}

/* ==========================================================
            过程: AddItem
            参数: controlid=控件类型Id, rc=左/上/宽/高, CallbackFunc=点击事件
            描述: 初始化
   ========================================================== */
//void xContainer::AddItem(xButton obj)  //0x01=按钮
//{
//    xWF_pCtrls item = this->_last->next = (xWF_pCtrls)malloc(sizeof(struct xWF_tagCtrls));
//    memset(item, 0, sizeof(struct xWF_tagCtrls));
//        item->type = controlid;
//        item->rc   = rc;
//    this->_last->next = item;
//}
//void xContainer::AddItem(xCheck  obj)  //0x02=复选框
//{
//
//}
//void xContainer::AddItem(xCombo  obj)  //0x03=组合框
//{
//
//}
//void xContainer::AddItem(xEdit   obj)  //0x04=编辑框
//{
//
//}
//void xContainer::AddItem(xGrid   obj)  //0x05=网格列表
//{
//
//}
void xContainer::AddItem(xLabel  obj)  //0x06=标签文本
{

}
//void xContainer::AddItem(xStatus obj)  //0x07=状态栏
//{
//
//}
//void xContainer::AddItem(xTree   obj)  //0x08=树形
//{
//
//}
//void xContainer::AddItem(BYTE controlid, xWF_pRect rc, tEvent_OnClick CallbackFunc=0)
//{
//    xWF_pCtrls item = this->_last->next = (xWF_pCtrls)malloc(sizeof(struct xWF_tagCtrls));
//    memset(item, 0, sizeof(struct xWF_tagCtrls));
//        item->type = controlid;
//        item->rc   = rc;
//    this->_last->next = item;
//}