#include <iostream>
using namespace std;

unsigned long long int f(unsigned long long int d, unsigned long long int w, unsigned long long int h, unsigned long long int a, unsigned long long int b)
{
    return max((w / (b + 2 * d)) * (h / (a + 2 * d)), (h / (b + 2 * d)) * (w / (a + 2 * d)));
}
int main()
{
    unsigned long long int R, L, M, w, h, d, n, a, b;
    cin >> n >> a >> b >> w >> h;
    L = 1;
    R = min(h - max(a, b), w - max(a, b)) / 2 + 3;
    while (L < R)
    {
        M = (L + R) / 2;
        if (f(M, w, h, a, b) < n)
        {
            R = M;
        }
        else
        {
            L = M + 1;
        }
    }
    cout << L - 1 << endl;
    return 0;
}