#ifndef __TOD__TEST__H__
#define __TOD__TEST__H__

bool check(Divider& div, int dividend);

void showEquation(Divider& div, long dividend);

void test(Divider& div, int dividends[] = nullptr, int nDiv = 0);

void test(int divisor, int shiftBits = 32, int dividends[] = nullptr, int nDiv = 0);

#endif // __TOD__TEST__H__