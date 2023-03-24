#ifndef xRSA_H
#define xRSA_H
//#include <string>
//#include <iostream>
//#include <ctime>
#include <sys/timeb.h>

using std::cout;
using std::endl;

int 素数表[258] = {
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

class x加密类
{
public:
    x加密类() {
        this->_公私积_总数 = 9;
        this->_乘积_索引 = (this->_公私积_总数-1) / 2;
        this->_公钥_乘积_xAx = this->_私钥_乘积_xAx = 0;
        this->_公钥串 = this->_私钥串 = 0;
    }
    //初始化密钥对
    x加密类(unsigned short *keys, unsigned int size) {
        this->_公钥串 = this->_私钥串 = 0;
        if (size%2==0) { //是一对密钥
            this->_公私积_总数 = size / 2;
        } else { //是单个密钥
            this->_公私积_总数 = size;
        }
        this->_乘积_索引 = (this->_公私积_总数-1) / 2;
        unsigned short _总数 = sizeof(unsigned short)*this->_公私积_总数+1;
        this->_公钥_乘积_xAx = (unsigned short*)malloc(_总数);
        this->_私钥_乘积_xAx = (unsigned short*)malloc(_总数);
        memcpy(&this->_公钥_乘积_xAx[0], &keys[0], _总数);
        if (size%2==0) { //是一对密钥
            memcpy(&this->_私钥_乘积_xAx[0], &keys[this->_公私积_总数], _总数);
        } else {
            memcpy(&this->_私钥_乘积_xAx[0], &keys[0], _总数);
        }
    }
    ~x加密类() {
        this->_释放内存();
    }
    unsigned int 加密(const char *明文, unsigned int 明文长度, char *密文) {
        if (密文 == 0) { return 0; }
        bool isSEQ = true;
        int k=0, iK=0;
        unsigned int i = 0, j = 0, iPer = 0, iCount=0, id = 0, iNum = 0, iN = 0;
        unsigned char ucOne=0, ucFix=0;
        while (i < 明文长度)
        {
            iPer = (iCount%2)*2; iCount++;
            ucOne = (unsigned char)明文[i++];
            if ((ucOne & 0x80) || ucFix==1) {
                iNum = ucOne;
                if (ucFix==0)
                    ucFix=1;
                else
                    ucFix=0;
            } else {
                iNum = ucOne;
                iNum += (unsigned char)明文[i++] * 0x100;
            }
            if (isSEQ) {
	            k++; if(k>=this->_公私积_总数) { k-=iPer; isSEQ=false; }
	        } else {
	            k--; if(k<0) { k=0; isSEQ=true; }
	        }
            iK = k+1-iPer;
            if(iK<0){
                iK=0;
            } else if(iK>=this->_公私积_总数){
                iK=this->_公私积_总数-1;
            } else if(iK==this->_乘积_索引){
                if (iPer==0) {
                    iK++;
                } else {
                    iK--;
                }
            }
            iN = PowMod(iNum, this->_公钥_乘积_xAx[iK], this->_公钥_乘积_xAx[this->_乘积_索引]);
            密文[id++] = (unsigned char)( iN & 0xFF);
            密文[id++] = (unsigned char)((iN & 0xFF00) / 0x100);
        }
        return id;
    }

    unsigned int 解密(const char *密文, unsigned int 密文长度, char *明文) {
        if (明文 == 0) { return 0; }
        bool isSEQ = true;
        int k=0, iK=0;
        unsigned int i = 0, j = 0, iPer = 0, iCount=0, id = 0, iNum = 0, iN = 0;
        unsigned char ucOne=0, ucFix=0;
        while (id < 密文长度)
        {
            iN = (unsigned char)密文[id];
            iN+= (unsigned char)密文[id+1] * 0x100;
            id+=2;
            iPer = (iCount%2)*2; iCount++;
            if (isSEQ) {
	            k++; if(k>=this->_公私积_总数) { k-=iPer; isSEQ=false; }
	        } else {
	            k--; if(k<0) { k=0; isSEQ=true; }
	        }
            iK = k+1-iPer;
            if(iK<0){
                iK=0;
            } else if(iK>=this->_公私积_总数){
                iK=this->_公私积_总数-1;
            } else if(iK==this->_乘积_索引){
                if (iPer==0) {
                    iK++;
                } else {
                    iK--;
                }
            }
            iNum = PowMod(iN, this->_私钥_乘积_xAx[iK], this->_私钥_乘积_xAx[this->_乘积_索引]);
            ucOne = (unsigned char)(iNum & 0xFF);
            if ((ucOne & 0x80) || ucFix==1) {
                明文[i++] = ucOne;
                if (ucFix==0)
                    ucFix=1;
                else
                    ucFix=0;
            } else {
                明文[i++] = ucOne;
                明文[i++] = (unsigned char)((iNum & 0xFF00)/ 0x100);
            }
        }
        return i;
    }

    void 反转密钥() {
        unsigned short id = 0, _公私积=0;
        for (id=0; id<this->_公私积_总数; id++)
        {
            _公私积 = this->_公钥_乘积_xAx[id];
            this->_公钥_乘积_xAx[id] = this->_私钥_乘积_xAx[id];
            this->_私钥_乘积_xAx[id] = _公私积;
        }
    }
    /**
        方法：生成密钥
        参数：密钥版本，范围0-0xFF
        描述：产生私钥和公钥
    */
    void 生成密钥(const unsigned char 密钥版本=0)
    {
        const unsigned char _pqMax=98;
        unsigned char pid = this->Rand(_pqMax/2) & 0xFF;
        if (1<=密钥版本) pid = 密钥版本 % (_pqMax/2) & 0xFF;
        unsigned char qid = pid + _pqMax/2; //(this->Rand(_pqMax/2)+_pqMax/2) & 0xFF;
        unsigned short p = 素数表[pid], q = 素数表[qid];
        unsigned int id = 0, _公钥 = 0, _私钥 = 0, _乘积 = p * q;
        //while(_乘积>0xFFFF || _乘积<0xA000 || p==q) { qid = this->Rand(_pqMax/2)+_pqMax/2; q = 素数表[qid]; _乘积 = p * q; }
        //释放内存
        this->_释放内存();
        //根据版本生成密钥对
        this->_公私积_总数 = 256;
        this->_乘积_索引 = (this->_公私积_总数-1) / 2;
        unsigned short _总数 = sizeof(unsigned short)*this->_公私积_总数+1;
        this->_公钥_乘积_xAx = (unsigned short*)malloc(_总数);
        this->_私钥_乘积_xAx = (unsigned short*)malloc(_总数);
        memset(this->_公钥_乘积_xAx, 0, _总数);
        memset(this->_私钥_乘积_xAx, 0, _总数);
        //生产密钥
        for (int i=0; i<this->_公私积_总数; i++)
        {
            _公钥 = this->素数(this->Rand(0xEFFE) + 0x1001);
            _私钥 = reverseMod(_公钥, (p - 1)*(q - 1));
            while (this->_密钥已存在(_公钥,_私钥)) {
	            _公钥 = this->素数(this->Rand(0xEFFE) + 0x1001);
	            _私钥 = reverseMod(_公钥, (p - 1)*(q - 1));
            }
            if (i%2==0) {
                this->_公钥_乘积_xAx[id] = _公钥;
                this->_私钥_乘积_xAx[id] = _私钥;
            } else {
                this->_公钥_乘积_xAx[id] = _私钥;
                this->_私钥_乘积_xAx[id] = _公钥;
            }
            id++;
        }
        this->_公钥_乘积_xAx[this->_乘积_索引] = this->_私钥_乘积_xAx[this->_乘积_索引] = _乘积;
    }
    
    /**
        方法：密钥
        参数：
        描述：获取公钥数据
            公钥:(7BEF 70B7 2C41 B9AD 6F1F 7193 FCEF 8605 8DD9 70B7 6DCD 6FFB 19B5)
            私钥:(0B0F AF27 56D1 1CA5 73FF 6C9B FCEF 3C0D 2479 AF27 2525 1B83 E5CD)
    */
    const char *密钥() {
        if (this->_公钥串 == 0 && this->_私钥串 == 0) {
            this->_公钥串 = (char*)malloc(sizeof(char)*this->_公私积_总数*4+1);
            memset(&this->_公钥串[0], 0, sizeof(char)*this->_公私积_总数*4+1);

            this->_私钥串 = (char*)malloc(sizeof(char)*this->_公私积_总数*4+1);
            memset(&this->_私钥串[0], 0, sizeof(char)*this->_公私积_总数*4+1);

            char _One[5]={0}, _Two[5]={0};
            for (int i=0; i<this->_公私积_总数; i++)
            {
                sprintf(_One, "%04X", this->_公钥_乘积_xAx[i]); strcat(this->_公钥串, _One);
                sprintf(_Two, "%04X", this->_私钥_乘积_xAx[i]); strcat(this->_私钥串, _Two);
            }
        }
        //cout << "公钥:" << "(" << this->_公钥串 << ")" << endl;
        //cout << "私钥:" << "(" << this->_私钥串 << ")" << endl;
        return &this->_公钥串[0];
    }
    /**
        方法：密钥
        参数：[uchar*]密钥
            公钥:(7BEF70B72C41B9AD6F1F7193FCEF86058DD970B76DCD6FFB19B5)
            私钥:(0B0FAF2756D11CA573FF6C9BFCEF3C0D2479AF2725251B83E5CD)
        描述：初始化密钥对
    */
    void 密钥(const char *_in密钥) {
        unsigned int i = 0, id = 0, 大小 = strlen(_in密钥);
        char _One[5];
        unsigned int _out大小 = 大小/4;
        unsigned short *_out密钥 = (unsigned short*)malloc(sizeof(unsigned short)*_out大小+1);
        memset(&_out密钥[0], 0, sizeof(unsigned short)*_out大小+1);
        for (i=0; i<大小; i+=4)
        {
            memcpy(&_One[0], &_in密钥[i], 4); _One[4]=0;
            _out密钥[id++] = strtol(_One, 0, 16);
        }
        this->密钥(_out密钥, _out大小);
        free(_out密钥);
    }
    /**
        方法：设置密钥
        参数：[uint]密钥 {xxxx,y,xxxx}
             [uint]大小，必须是奇数
        描述：初始化密钥对
    */
    void 密钥(unsigned short *_in密钥, unsigned int _in大小) {
        this->_释放内存();
        this->_公私积_总数 = _in大小;
        this->_乘积_索引 = (this->_公私积_总数-1) / 2;
        this->_公钥_乘积_xAx = (unsigned short*)malloc(sizeof(unsigned short)*this->_公私积_总数);
        this->_私钥_乘积_xAx = (unsigned short*)malloc(sizeof(unsigned short)*this->_公私积_总数);
        memcpy(&this->_公钥_乘积_xAx[0], &_in密钥[0], sizeof(unsigned short)*this->_公私积_总数);
        memcpy(&this->_私钥_乘积_xAx[0], &_in密钥[0], sizeof(unsigned short)*this->_公私积_总数);
    }
    
    unsigned short 素数(const unsigned short _in起始值, const unsigned char _in个数=10) {
    	for (int i=0; i<_in个数; i++)
        {
        	if (this->是否素数(_in起始值+i)) return _in起始值+i;
        }
        return 0;
    }
    //判断是否是素数
    bool 是否素数(const unsigned short _in值){
	    if (_in值 == 2 || _in值 == 3) return true;
        if (_in值 <= 1 || (_in值 % 6 != 1 && _in值 % 6 != 5)) return false;

	    unsigned short i, halfNum = (int)sqrt((double)_in值);
	    for (i = 5; i <= halfNum; i += 6)
		    if (_in值 % i == 0 || _in值 % (i + 2) == 0)
			    return false;
	    return true;
    }
private:
    char *_公钥串, *_私钥串;
    unsigned short *_公钥_乘积_xAx, *_私钥_乘积_xAx, _公私积_总数, _乘积_索引;

    //unsigned int _乘积; //n=p*q
    //unsigned int _私钥; //a对于φ(n)的模反元素
    //unsigned int _公钥;

    void _释放内存() {
        if (this->_公钥_乘积_xAx) { free(this->_公钥_乘积_xAx); this->_公钥_乘积_xAx=0; }
        if (this->_私钥_乘积_xAx) { free(this->_私钥_乘积_xAx); this->_私钥_乘积_xAx=0; }
        if (this->_公钥串) { free(this->_公钥串); this->_公钥串=0; }
        if (this->_私钥串) { free(this->_私钥串); this->_私钥串=0; }
    }
    
    bool _密钥已存在(unsigned short _公钥, unsigned short _私钥) {
    	int seqId=0, revId = this->_公私积_总数-1, halfCount = this->_公私积_总数/2+1;
        for (int seqId=0; seqId<halfCount; seqId++)
        {
            if (this->_公钥_乘积_xAx[seqId] == _公钥 || this->_私钥_乘积_xAx[seqId] == _私钥) {
                return true;
            }
            if (this->_公钥_乘积_xAx[revId-seqId] == _公钥 || this->_私钥_乘积_xAx[revId-seqId] == _私钥) {
                return true;
            }
        }
        return false;
    }
    //模乘运算，返回值 x=a*b mod n
    //模幂运算，返回值 x=base^pow mod n
    unsigned int PowMod(unsigned int _in值, unsigned int _in密钥, unsigned int _in乘积)
    {
        if (_in密钥 == 1)
            return _in值 % _in乘积;
        else
            return (PowMod(_in值, _in密钥 / 2, _in乘积)*PowMod(_in值, _in密钥 - _in密钥 / 2, _in乘积)) % _in乘积;
    }
    //返回d=gcd(a,b);和对应于等式ax+by=d中的x,y
    int extend_gcd(int one, int two, int &x, int &y) {
        if (one == 0 && two == 0) return -1;//无最大公约数
        if (two == 0) {
            x = 1; y = 0; return one;
        }
        int d = extend_gcd(two, one%two, y, x);
        y -= one / two * x;
        return d;
    }
    //ax = 1(mod n) 求X
    int reverseMod(int one, int two) {
        int x, y;
        int d = extend_gcd(one, two, x, y);
        if (d == 1)
            return (x%two + two) % two;
        else return -1;
    }
    
    unsigned int time_stamp;
    /* ================================
        函数: Rand
        参数: [in]seeds=种子数,最大值
        描述: 随机产生整型数字
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