#ifndef __TOD__H__
#define __TOD__H__

struct divres
{
    int quot;
    int rem;
}

class Divider
{
public:
    Divider(int divisor, int bits) : divisor(divisor), bits(bits),
            factor((int)ceil((1ul << bits) * 1.0 / divisor)) { }

    divres operator()(int d)
    {
        divres res;
        res.quot = ((long)d * factor) >> bits;
        res.rem  = d - res.quot * divisor;
        while (res.rem < 0) res.quot--, res.rem+=divisor;
        return res;
    }

private:
    int divisor;
    int bits;
    int factor;
};





#endif // __TOD__H__