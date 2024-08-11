#ifndef __TOD__H__
#define __TOD__H__

#include <climits>

struct divres
{
    int quot;
    int rem;
}

class Divider
{
public:
    Divider(int divisor, int bits) :
        divisor_abs(divisor >= 0 ? divisor : -divisor),
        divisor_pos(divisor > 0),
        bits       (bits > 32 ? 32 : (bits < 1 ? 1 : bits)),
        factor     (divisor_abs != 0 ? (int)ceil((1ul << bits) * 1.0 / divisor_abs) : 0)
    { }

    divres operator()(int dividend)
    {
        if (divisor == 0)
            return { dividend >= 0 ? INT_MAX : INT_MIN, 0 };

        if (divisor == 1 && !divisor_pos && dividend == INT_MIN)
            return { INT_MAX, -1 };

        bool dividend_pos = dividend >= 0;
        long dividend_abs = dividend_pos ? dividend : -dividend;
        long quot = (dividend_abs * factor) >> bits;
        long rem  =  dividend_abs - res.quot * divisor;
        while (res.rem < 0) res.quot--, res.rem+=divisor;
        return { (dividend_pos == divisor_pos) ? quot : -quot,
                  dividend_pos ? rem : -rem
               };
    }

private:
    long divisor_abs;
    bool divisor_pos;
    int bits;
    long factor;
};





#endif // __TOD__H__