#ifndef _xControl_Container_Head_
#define _xControl_Container_Head_
    
    class xContainer; //�ۺ�
    class xContainer
    {
    private:
        xWF_tagCtrls _ctrls;
        xWF_pCtrls _last;
    public:
        xContainer();
        ~xContainer();
        xContainer(xWF_pRect rc);
        
        //void AddItem(xButton obj);  //0x01=��ť
        //void AddItem(xCheck  obj);  //0x02=��ѡ��
        //void AddItem(xCombo  obj);  //0x03=��Ͽ�
        //void AddItem(xEdit   obj);  //0x04=�༭��
        //void AddItem(xGrid   obj);  //0x05=�����б�
        void AddItem(xLabel  obj);  //0x06=��ǩ�ı�
        //void AddItem(xStatus obj);  //0x07=״̬��
        //void AddItem(xTree   obj);  //0x08=����
    };
#endif