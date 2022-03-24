#ifndef _xControl_Label_Head_
#define _xControl_Label_Head_
    
    class xLabel; //0x06=��ǩ�ı�
    class xLabel
    {
    private:
        /* �ı� */
        int _length;
        char *_text;
        /* ���� */
        xWF_tagRect _rc;
        /* ��ͼ���� */
        xWF_Draw *_base;

        /* �¼��̳� */
        tEvent_OnClick _funcClick;
        /* �¼����� */
        void onEvents(const int x, const int y,const int mouse);
    public:
        xLabel();
        ~xLabel();
        xLabel(const int x, const int y, const int width, const int height, const char* text);

        /* �������� */
        void Set(const int x, const int y);
        /* ���û�ͼ���� */
        void Set(xWF_Draw *draw);
        /* �����ı� */
        void Set(const char* text);
        

        /* ���¼� */
        void BindOnClick(tEvent_OnClick CallbackFunc);
        
        /* ˢ�� */
        void Refresh();
    };
#endif