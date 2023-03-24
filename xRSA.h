#ifndef xRSA_H
#define xRSA_H
//#include <string>
//#include <iostream>
//#include <ctime>
#include <sys/timeb.h>

using std::cout;
using std::endl;

int ������[258] = {
    0x0002,0x0003,0x0005,0x0007,0x000B,0x000D,0x0011,0x0013,0x0017,0x001D,
    0x001F,0x0025,0x0029,0x002B,0x002F,0x0035,0x003B,0x003D,0x0043,0x0047,
    0x0049,0x004F,0x0053,0x0059,0x0061,0x0065,0x0067,0x006B,0x006D,0x0071,
    0x007F,0x0083,0x008B,0x0095,0x0097,0x009D,0x00A3,0x00A7,0x00AD,0x00B5,
    0x00C1,0x00C5,0x00C7,0x00D3,0x00DF,0x00E5,0x00E9,0x00F1,0x00FB, //49
    0x7FED,0x5551,0x332F,0x2485,0x1741,0x13AF,0x0F0D,0x0D79,0x0B1B,0x08CB,
    0x0841,0x06DF,0x063D,0x05F3,0x0565,0x04CF,0x0455,0x042D,0x03D1,0x0397,
    0x0377,0x033D,0x0313,0x02DD,0x02A1,0x0287,0x0277,0x025F,0x0259,0x0241,
    0x01FD,0x01F3,0x01D3,0x01B7,0x01B1,0x0199,0x0191,0x0185,0x0175,0x0167,
    0x0151,0x014B,0x013D,0x0133,0x0125,0x011B,0x0119,0x010F,0x0101, //98

    0x1069,0x2065,0x3067,0x5083,0x6079,0x7075,0x8077,0x906D,0xA099,0xB087,
    0x112D,0x215B,0x3127,0x5117,0x612D,0x7159,0x812F,0x913D,0xA11B,0xB11D,
    0x12B5,0x22A3,0x32A7,0x52C3,0x62DD,0x72C7,0x82DF,0x92C3,0xA2BB,0xB2C7,
    0x1307,0x2303,0x3307,0x5315,0x6305,0x7303,0x830B,0x9301,0xA301,0xB303,
    0x137B,0x2363,0x337F,0x5399,0x637F,0x739F,0x8365,0x93A7,0xA3A5,0xB39B,
    0x153D,0x2597,0x3577,0x5563,0x658D,0x758B,0x85A3,0x955D,0xA585,0xB579,
    0x1693,0x2683,0x36BB,0x568D,0x66CD,0x76B7,0x86C3,0x96FB,0xA6DF,0xB6B1,
    0x1709,0x2717,0x3701,0x5701,0x6703,0x7703,0x8717,0x970D,0xA70F,0xB705,
    0x183B,0x281F,0x3853,0x582B,0x6839,0x7853,0x8837,0x982F,0xA837,0xB827,
    0x19B5,0x299B,0x3995,0x59D1,0x69B5,0x79AB,0x89B9,0x99AF,0xA9C1,0xB999,
    0x1A87,0x2A8B,0x3AA5,0x5A95,0x6AC9,0x7A7D,0x8AC1,0x9AC3,0xAA95,0xBA7F,
    0x1B25,0x2B31,0x3B1B,0x5B19,0x6B11,0x7B19,0x8B0D,0x9B27,0xAB07,0xBB27,
    0x1C81,0x2C77,0x3C85,0x5C6F,0x6C65,0x7C93,0x8C81,0x9C9D,0xAC7F,0xBC99,
    0x1D35,0x2D61,0x3D1F,0x5D19,0x6D2B,0x7D33,0x8D29,0x9D3D,0xAD5F,0xBD35,
    0x1E3D,0x2E33,0x3E33,0x5E31,0x6E7B,0x7E6B,0x8E79,0x9E53,0xAE8B,0xBE6F,
    0x1FFF,0x2FF5,0x3FFD,0x5FFB,0x6FFD,0x7FED,0x8FF9,0x9FF5,0xAFFD,0xBFF3,
};

class x������
{
public:
    x������() {
        this->_��˽��_���� = 9;
        this->_�˻�_���� = (this->_��˽��_����-1) / 2;
        this->_��Կ_�˻�_xAx = this->_˽Կ_�˻�_xAx = 0;
        this->_��Կ�� = this->_˽Կ�� = 0;
    }
    //��ʼ����Կ��
    x������(unsigned short *keys, unsigned int size) {
        this->_��Կ�� = this->_˽Կ�� = 0;
        if (size%2==0) { //��һ����Կ
            this->_��˽��_���� = size / 2;
        } else { //�ǵ�����Կ
            this->_��˽��_���� = size;
        }
        this->_�˻�_���� = (this->_��˽��_����-1) / 2;
        unsigned short _���� = sizeof(unsigned short)*this->_��˽��_����+1;
        this->_��Կ_�˻�_xAx = (unsigned short*)malloc(_����);
        this->_˽Կ_�˻�_xAx = (unsigned short*)malloc(_����);
        memcpy(&this->_��Կ_�˻�_xAx[0], &keys[0], _����);
        if (size%2==0) { //��һ����Կ
            memcpy(&this->_˽Կ_�˻�_xAx[0], &keys[this->_��˽��_����], _����);
        } else {
            memcpy(&this->_˽Կ_�˻�_xAx[0], &keys[0], _����);
        }
    }
    ~x������() {
        this->_�ͷ��ڴ�();
    }
    unsigned int ����(const char *����, unsigned int ���ĳ���, char *����) {
        if (���� == 0) { return 0; }
        bool isSEQ = true;
        int k=0, iK=0;
        unsigned int i = 0, j = 0, iPer = 0, iCount=0, id = 0, iNum = 0, iN = 0;
        unsigned char ucOne=0, ucFix=0;
        while (i < ���ĳ���)
        {
            iPer = (iCount%2)*2; iCount++;
            ucOne = (unsigned char)����[i++];
            if ((ucOne & 0x80) || ucFix==1) {
                iNum = ucOne;
                if (ucFix==0)
                    ucFix=1;
                else
                    ucFix=0;
            } else {
                iNum = ucOne;
                iNum += (unsigned char)����[i++] * 0x100;
            }
            if (isSEQ) {
	            k++; if(k>=this->_��˽��_����) { k-=iPer; isSEQ=false; }
	        } else {
	            k--; if(k<0) { k=0; isSEQ=true; }
	        }
            iK = k+1-iPer;
            if(iK<0){
                iK=0;
            } else if(iK>=this->_��˽��_����){
                iK=this->_��˽��_����-1;
            } else if(iK==this->_�˻�_����){
                if (iPer==0) {
                    iK++;
                } else {
                    iK--;
                }
            }
            iN = PowMod(iNum, this->_��Կ_�˻�_xAx[iK], this->_��Կ_�˻�_xAx[this->_�˻�_����]);
            ����[id++] = (unsigned char)( iN & 0xFF);
            ����[id++] = (unsigned char)((iN & 0xFF00) / 0x100);
        }
        return id;
    }

    unsigned int ����(const char *����, unsigned int ���ĳ���, char *����) {
        if (���� == 0) { return 0; }
        bool isSEQ = true;
        int k=0, iK=0;
        unsigned int i = 0, j = 0, iPer = 0, iCount=0, id = 0, iNum = 0, iN = 0;
        unsigned char ucOne=0, ucFix=0;
        while (id < ���ĳ���)
        {
            iN = (unsigned char)����[id];
            iN+= (unsigned char)����[id+1] * 0x100;
            id+=2;
            iPer = (iCount%2)*2; iCount++;
            if (isSEQ) {
	            k++; if(k>=this->_��˽��_����) { k-=iPer; isSEQ=false; }
	        } else {
	            k--; if(k<0) { k=0; isSEQ=true; }
	        }
            iK = k+1-iPer;
            if(iK<0){
                iK=0;
            } else if(iK>=this->_��˽��_����){
                iK=this->_��˽��_����-1;
            } else if(iK==this->_�˻�_����){
                if (iPer==0) {
                    iK++;
                } else {
                    iK--;
                }
            }
            iNum = PowMod(iN, this->_˽Կ_�˻�_xAx[iK], this->_˽Կ_�˻�_xAx[this->_�˻�_����]);
            ucOne = (unsigned char)(iNum & 0xFF);
            if ((ucOne & 0x80) || ucFix==1) {
                ����[i++] = ucOne;
                if (ucFix==0)
                    ucFix=1;
                else
                    ucFix=0;
            } else {
                ����[i++] = ucOne;
                ����[i++] = (unsigned char)((iNum & 0xFF00)/ 0x100);
            }
        }
        return i;
    }

    void ��ת��Կ() {
        unsigned short id = 0, _��˽��=0;
        for (id=0; id<this->_��˽��_����; id++)
        {
            _��˽�� = this->_��Կ_�˻�_xAx[id];
            this->_��Կ_�˻�_xAx[id] = this->_˽Կ_�˻�_xAx[id];
            this->_˽Կ_�˻�_xAx[id] = _��˽��;
        }
    }
    /**
        ������������Կ
        ��������Կ�汾����Χ0-0xFF
        ����������˽Կ�͹�Կ
    */
    void ������Կ(const unsigned char ��Կ�汾=0)
    {
        const unsigned char _pqMax=98;
        unsigned char pid = this->Rand(_pqMax/2) & 0xFF;
        if (1<=��Կ�汾) pid = ��Կ�汾 % (_pqMax/2) & 0xFF;
        unsigned char qid = pid + _pqMax/2; //(this->Rand(_pqMax/2)+_pqMax/2) & 0xFF;
        unsigned short p = ������[pid], q = ������[qid];
        unsigned int id = 0, _��Կ = 0, _˽Կ = 0, _�˻� = p * q;
        //while(_�˻�>0xFFFF || _�˻�<0xA000 || p==q) { qid = this->Rand(_pqMax/2)+_pqMax/2; q = ������[qid]; _�˻� = p * q; }
        //�ͷ��ڴ�
        this->_�ͷ��ڴ�();
        //���ݰ汾������Կ��
        this->_��˽��_���� = 256;
        this->_�˻�_���� = (this->_��˽��_����-1) / 2;
        unsigned short _���� = sizeof(unsigned short)*this->_��˽��_����+1;
        this->_��Կ_�˻�_xAx = (unsigned short*)malloc(_����);
        this->_˽Կ_�˻�_xAx = (unsigned short*)malloc(_����);
        memset(this->_��Կ_�˻�_xAx, 0, _����);
        memset(this->_˽Կ_�˻�_xAx, 0, _����);
        //������Կ
        for (int i=0; i<this->_��˽��_����; i++)
        {
            _��Կ = this->����(this->Rand(0xEFFE) + 0x1001);
            _˽Կ = reverseMod(_��Կ, (p - 1)*(q - 1));
            while (this->_��Կ�Ѵ���(_��Կ,_˽Կ)) {
	            _��Կ = this->����(this->Rand(0xEFFE) + 0x1001);
	            _˽Կ = reverseMod(_��Կ, (p - 1)*(q - 1));
            }
            if (i%2==0) {
                this->_��Կ_�˻�_xAx[id] = _��Կ;
                this->_˽Կ_�˻�_xAx[id] = _˽Կ;
            } else {
                this->_��Կ_�˻�_xAx[id] = _˽Կ;
                this->_˽Կ_�˻�_xAx[id] = _��Կ;
            }
            id++;
        }
        this->_��Կ_�˻�_xAx[this->_�˻�_����] = this->_˽Կ_�˻�_xAx[this->_�˻�_����] = _�˻�;
    }
    
    /**
        ��������Կ
        ������
        ��������ȡ��Կ����
            ��Կ:(7BEF 70B7 2C41 B9AD 6F1F 7193 FCEF 8605 8DD9 70B7 6DCD 6FFB 19B5)
            ˽Կ:(0B0F AF27 56D1 1CA5 73FF 6C9B FCEF 3C0D 2479 AF27 2525 1B83 E5CD)
    */
    const char *��Կ() {
        if (this->_��Կ�� == 0 && this->_˽Կ�� == 0) {
            this->_��Կ�� = (char*)malloc(sizeof(char)*this->_��˽��_����*4+1);
            memset(&this->_��Կ��[0], 0, sizeof(char)*this->_��˽��_����*4+1);

            this->_˽Կ�� = (char*)malloc(sizeof(char)*this->_��˽��_����*4+1);
            memset(&this->_˽Կ��[0], 0, sizeof(char)*this->_��˽��_����*4+1);

            char _One[5]={0}, _Two[5]={0};
            for (int i=0; i<this->_��˽��_����; i++)
            {
                sprintf(_One, "%04X", this->_��Կ_�˻�_xAx[i]); strcat(this->_��Կ��, _One);
                sprintf(_Two, "%04X", this->_˽Կ_�˻�_xAx[i]); strcat(this->_˽Կ��, _Two);
            }
        }
        //cout << "��Կ:" << "(" << this->_��Կ�� << ")" << endl;
        //cout << "˽Կ:" << "(" << this->_˽Կ�� << ")" << endl;
        return &this->_��Կ��[0];
    }
    /**
        ��������Կ
        ������[uchar*]��Կ
            ��Կ:(7BEF70B72C41B9AD6F1F7193FCEF86058DD970B76DCD6FFB19B5)
            ˽Կ:(0B0FAF2756D11CA573FF6C9BFCEF3C0D2479AF2725251B83E5CD)
        ��������ʼ����Կ��
    */
    void ��Կ(const char *_in��Կ) {
        unsigned int i = 0, id = 0, ��С = strlen(_in��Կ);
        char _One[5];
        unsigned int _out��С = ��С/4;
        unsigned short *_out��Կ = (unsigned short*)malloc(sizeof(unsigned short)*_out��С+1);
        memset(&_out��Կ[0], 0, sizeof(unsigned short)*_out��С+1);
        for (i=0; i<��С; i+=4)
        {
            memcpy(&_One[0], &_in��Կ[i], 4); _One[4]=0;
            _out��Կ[id++] = strtol(_One, 0, 16);
        }
        this->��Կ(_out��Կ, _out��С);
        free(_out��Կ);
    }
    /**
        ������������Կ
        ������[uint]��Կ {xxxx,y,xxxx}
             [uint]��С������������
        ��������ʼ����Կ��
    */
    void ��Կ(unsigned short *_in��Կ, unsigned int _in��С) {
        this->_�ͷ��ڴ�();
        this->_��˽��_���� = _in��С;
        this->_�˻�_���� = (this->_��˽��_����-1) / 2;
        this->_��Կ_�˻�_xAx = (unsigned short*)malloc(sizeof(unsigned short)*this->_��˽��_����);
        this->_˽Կ_�˻�_xAx = (unsigned short*)malloc(sizeof(unsigned short)*this->_��˽��_����);
        memcpy(&this->_��Կ_�˻�_xAx[0], &_in��Կ[0], sizeof(unsigned short)*this->_��˽��_����);
        memcpy(&this->_˽Կ_�˻�_xAx[0], &_in��Կ[0], sizeof(unsigned short)*this->_��˽��_����);
    }
    
    unsigned short ����(const unsigned short _in��ʼֵ, const unsigned char _in����=10) {
    	for (int i=0; i<_in����; i++)
        {
        	if (this->�Ƿ�����(_in��ʼֵ+i)) return _in��ʼֵ+i;
        }
        return 0;
    }
    //�ж��Ƿ�������
    bool �Ƿ�����(const unsigned short _inֵ){
	    if (_inֵ == 2 || _inֵ == 3) return true;
        if (_inֵ <= 1 || (_inֵ % 6 != 1 && _inֵ % 6 != 5)) return false;

	    unsigned short i, halfNum = (int)sqrt((double)_inֵ);
	    for (i = 5; i <= halfNum; i += 6)
		    if (_inֵ % i == 0 || _inֵ % (i + 2) == 0)
			    return false;
	    return true;
    }
private:
    char *_��Կ��, *_˽Կ��;
    unsigned short *_��Կ_�˻�_xAx, *_˽Կ_�˻�_xAx, _��˽��_����, _�˻�_����;

    //unsigned int _�˻�; //n=p*q
    //unsigned int _˽Կ; //a���ڦ�(n)��ģ��Ԫ��
    //unsigned int _��Կ;

    void _�ͷ��ڴ�() {
        if (this->_��Կ_�˻�_xAx) { free(this->_��Կ_�˻�_xAx); this->_��Կ_�˻�_xAx=0; }
        if (this->_˽Կ_�˻�_xAx) { free(this->_˽Կ_�˻�_xAx); this->_˽Կ_�˻�_xAx=0; }
        if (this->_��Կ��) { free(this->_��Կ��); this->_��Կ��=0; }
        if (this->_˽Կ��) { free(this->_˽Կ��); this->_˽Կ��=0; }
    }
    
    bool _��Կ�Ѵ���(unsigned short _��Կ, unsigned short _˽Կ) {
    	int seqId=0, revId = this->_��˽��_����-1, halfCount = this->_��˽��_����/2+1;
        for (int seqId=0; seqId<halfCount; seqId++)
        {
            if (this->_��Կ_�˻�_xAx[seqId] == _��Կ || this->_˽Կ_�˻�_xAx[seqId] == _˽Կ) {
                return true;
            }
            if (this->_��Կ_�˻�_xAx[revId-seqId] == _��Կ || this->_˽Կ_�˻�_xAx[revId-seqId] == _˽Կ) {
                return true;
            }
        }
        return false;
    }
    //ģ�����㣬����ֵ x=a*b mod n
    //ģ�����㣬����ֵ x=base^pow mod n
    unsigned int PowMod(unsigned int _inֵ, unsigned int _in��Կ, unsigned int _in�˻�)
    {
        if (_in��Կ == 1)
            return _inֵ % _in�˻�;
        else
            return (PowMod(_inֵ, _in��Կ / 2, _in�˻�)*PowMod(_inֵ, _in��Կ - _in��Կ / 2, _in�˻�)) % _in�˻�;
    }
    //����d=gcd(a,b);�Ͷ�Ӧ�ڵ�ʽax+by=d�е�x,y
    int extend_gcd(int one, int two, int &x, int &y) {
        if (one == 0 && two == 0) return -1;//�����Լ��
        if (two == 0) {
            x = 1; y = 0; return one;
        }
        int d = extend_gcd(two, one%two, y, x);
        y -= one / two * x;
        return d;
    }
    //ax = 1(mod n) ��X
    int reverseMod(int one, int two) {
        int x, y;
        int d = extend_gcd(one, two, x, y);
        if (d == 1)
            return (x%two + two) % two;
        else return -1;
    }
    
    unsigned int time_stamp;
    /* ================================
        ����: Rand
        ����: [in]seeds=������,���ֵ
        ����: ���������������
       ================================ */
    unsigned int Rand(const unsigned int seeds)
    {
        if (seeds == 0) return seeds;
        struct timeb timeSeed;
        ftime(&timeSeed);
        unsigned int _timestamp = ((timeSeed.time & 0xFFFFFFFFUL) * 0x10000UL + timeSeed.millitm) & 0xFFFFFFFFUL;
        if (_timestamp - time_stamp > 100) {
            time_stamp = _timestamp;
            srand(time_stamp); // milli time
        }
        unsigned int _randVal = rand();
        return _randVal % seeds;
    }
};
#endif