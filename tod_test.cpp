#include <iostream>
#include "tod.h"
#include "tod_test.h"

using namespace std;

bool check(Divider& div, int dividend)
{
    divres r = div(dividend);
    return dividend == r.quot * div.getDivisor() + r.rem;
}

void showEquation(Divider& div, long dividend)
{
    divres res = div(dividend);
    cout << dividend << " = " << res.quot << " * " << div.getDivisor() << " + " << res.rem << "; "
         << (check(div, dividend) ? "correct" : "incorrect")
         << endl;
}

void test(Divider& div, int dividends[], int nDiv)
{
    cout << endl << "Dividing by " << div.getDivisor() << ", shifting " << div.getShiftBits() << " bits" << endl;

    bool ok = true;
    
    if (dividends)
    {
        cout << "Performing on a custom set of dividends" << endl;

        for (int i = 0; i < nDiv; i++)
        {
            cout << "d = " << dividends[i] << endl;
            if (!check(div, (int)dividends[i])) cout << "!!! An error on " << dividends[i] << endl, ok = false;
        }
    }
    else
    {
        cout << "Performing on all `int`s" << endl;
        
        for (long d = INT_MIN; d <= INT_MAX; d++)
        {
            if ((d & 0xffffff) == 0) cout << "d = " << d << endl;
            if (!check(div, (int)d)) cout << "!!! An error on " << d << endl, ok = false;
        }
    }
    
    if (ok)
        cout << "Done! Test was successful!" << endl;
    else
        cout << "There\'s an error!" << endl;
}

void test(int divisor, int shiftBits, int dividends[], int nDiv)
{
    Divider div(divisor, shiftBits);

    test(div, dividends, nDiv);
}

int __attribute__((weak)) main()
{
    Divider div10(10, 32);
    cout << "factor = " << div10.getFactor() << ", " << "shiftBits = " << div10.getShiftBits() << endl;
    showEquation(div10, 546789097);

    Divider divM1(-1, 32);
    showEquation(divM1, INT_MIN);

    test(636, 32);

    Divider divC1(-78, 18);
    int divdC1[6] = {24654, 3572, -1375, 0, -56316309, 9326193};
    test(divC1, divdC1, 6);
}