#ifndef _xControl_Container_Head_
#define _xControl_Container_Head_
    
    class xContainer; //聚合
    class xContainer
    {
    private:
        xWF_tagCtrls _ctrls;
        xWF_pCtrls _last;
    public:
        xContainer();
        ~xContainer();
        xContainer(xWF_pRect rc);
        
        //void AddItem(xButton obj);  //0x01=按钮
        //void AddItem(xCheck  obj);  //0x02=复选框
        //void AddItem(xCombo  obj);  //0x03=组合框
        //void AddItem(xEdit   obj);  //0x04=编辑框
        //void AddItem(xGrid   obj);  //0x05=网格列表
        void AddItem(xLabel  obj);  //0x06=标签文本
        //void AddItem(xStatus obj);  //0x07=状态栏
        //void AddItem(xTree   obj);  //0x08=树形
    };
#endif