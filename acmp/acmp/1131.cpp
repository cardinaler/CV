#include <iostream>
#include <cmath>
using namespace std;
int a, b, c, d;
double f(double x)
{
    return a * x * x * x + b * x * x + c * x + d;
}

int main()
{
    double L, R, M = 0;
    double e = 0.000001;
    cin >> a >> b >> c >> d;
    if (a < 0)
    {
        a = -1 * a;
        b = -1 * b;
        c = -1 * c;
        d = -1 * d;
    }
    if (a > 0)
    {
        R = 1;
        L = -1;
        while (!(f(R) > 0))
        {
            R = R + 1;
        }
        while (!(f(L) < 0))
        {
            L = L - 1;
        }
        while (fabs(f(M)) > e)
        {
            M = L / 2 + R / 2;
            if (f(M) < 0)
            {
                L = M;
            }
            else
            {
                R = M;
            }
        }
    }
    cout << M << endl;
}