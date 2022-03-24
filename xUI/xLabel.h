#ifndef _xControl_Label_Head_
#define _xControl_Label_Head_
    
    class xLabel; //0x06=标签文本
    class xLabel
    {
    private:
        /* 文本 */
        int _length;
        char *_text;
        /* 坐标 */
        xWF_tagRect _rc;
        /* 画图对象 */
        xWF_Draw *_base;

        /* 事件继承 */
        tEvent_OnClick _funcClick;
        /* 事件反馈 */
        void onEvents(const int x, const int y,const int mouse);
    public:
        xLabel();
        ~xLabel();
        xLabel(const int x, const int y, const int width, const int height, const char* text);

        /* 设置坐标 */
        void Set(const int x, const int y);
        /* 设置画图对象 */
        void Set(xWF_Draw *draw);
        /* 设置文本 */
        void Set(const char* text);
        

        /* 绑定事件 */
        void BindOnClick(tEvent_OnClick CallbackFunc);
        
        /* 刷新 */
        void Refresh();
    };
#endif