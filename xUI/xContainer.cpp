#include "zHAi_WF.h"


/* ==========================================================
            ����: Init
            ����: left=��top=�ϣ�width=��, height=��
            ����: ��ʼ��
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
            ����: AddItem
            ����: controlid=�ؼ�����Id, rc=��/��/��/��, CallbackFunc=����¼�
            ����: ��ʼ��
   ========================================================== */
//void xContainer::AddItem(xButton obj)  //0x01=��ť
//{
//    xWF_pCtrls item = this->_last->next = (xWF_pCtrls)malloc(sizeof(struct xWF_tagCtrls));
//    memset(item, 0, sizeof(struct xWF_tagCtrls));
//        item->type = controlid;
//        item->rc   = rc;
//    this->_last->next = item;
//}
//void xContainer::AddItem(xCheck  obj)  //0x02=��ѡ��
//{
//
//}
//void xContainer::AddItem(xCombo  obj)  //0x03=��Ͽ�
//{
//
//}
//void xContainer::AddItem(xEdit   obj)  //0x04=�༭��
//{
//
//}
//void xContainer::AddItem(xGrid   obj)  //0x05=�����б�
//{
//
//}
void xContainer::AddItem(xLabel  obj)  //0x06=��ǩ�ı�
{

}
//void xContainer::AddItem(xStatus obj)  //0x07=״̬��
//{
//
//}
//void xContainer::AddItem(xTree   obj)  //0x08=����
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