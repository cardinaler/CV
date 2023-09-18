#include <iostream>
#include <cmath>
using namespace std;
int main()
{
    unsigned long long int a1, a2, a3, a4, S;
    unsigned long long int L, R, m;
    cin >> a1 >> a2 >> a3 >> a4;
    S = min(a1, a2) + min(a3, a4);
    // cout << min(a1, a2) << endl;
    L = 0;
    R = (int)sqrt(S) + 1;
    while (R != L)
    {
        m = L / 2 + R / 2;
        //     cout << m << endl;
        if (m * m < S)
        {
            L = m + 1;
        }
        else
        {
            R = m;
        }
    }
    if (R * R > S)
        cout << R - 1;
    else
        cout << R;
}