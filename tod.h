#ifndef __TOD__H__
#define __TOD__H__

/*
 *  tod.h
 *
 *  An optimised divider
 *  
 *  Conceptualised on 2024-08-05 on ideas provided by Thomas Hoehenleitner (github.com/rokath)
 *  Implemented in the following weeks by Lazar Radosavljevic (github.com/lazar-rad)
 */

#include <climits>
#include <cmath>            

struct divres
{
    int quot;
    int rem;
};

class Divider
{
public:
    Divider(int divisor, int shiftBits = 32) :
        divisor_abs(divisor >= 0 ? divisor : -divisor),
        divisor_pos(divisor > 0),
        shiftBits  (shiftBits > 32 ? 32 : (shiftBits < 1 ? 1 : shiftBits)),
        factor     (divisor_abs != 0 ? (int)ceil((1ul << shiftBits) * 1.0 / divisor_abs) : 0)
    { }

    inline divres operator()(int dividend)
    {
        if (divisor_abs == 0)
            return { dividend >= 0 ? INT_MAX : INT_MIN, 0 };

        if (divisor_abs == 1 && !divisor_pos && dividend == INT_MIN)
            return { INT_MAX, -1 };

        bool dividend_pos = dividend >= 0;
        long dividend_abs = dividend_pos ? dividend : -dividend;
        long quot = (dividend_abs * factor) >> shiftBits;
        long rem  =  dividend_abs - quot * divisor_abs;
        while (rem < 0)
        {
            quot--;
            rem += divisor_abs;
        }

        return { (int)((dividend_pos == divisor_pos) ? quot : -quot),
                 (int)( dividend_pos ? rem : -rem)
               };
    }

    inline int getShiftBits() { return shiftBits; }

    inline int getFactor() { return (int)factor; }

    inline int getDivisor() { return (int)(divisor_pos ? divisor_abs : -divisor_abs); }

private:
    long divisor_abs;
    bool divisor_pos;
    int shiftBits;
    long factor;
};

#endif // __TOD__H__