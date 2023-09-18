#include <iostream>
using namespace std;
int f(int N, int M, int x, int y)
{
    return max(M * x, (N - 1 - M) * y);
}
int main()
{
    int N, x, y;
    int L, R, M;
    cin >> N >> x >> y;
    L = 0;
    R = N + 1;
    while (L != R)
    {
        M = L / 2 + R / 2;
        if ((f(N, M, x, y)) >= f(N, M + 1, x, y))
        {
            L = M + 1;
        }
        else
        {
            R = M;
        }
        //       cout << f(N, M, x, y) << endl;
    }
    cout << f(N, R, x, y) + min(x, y) << endl;

    // int min_ = f(N, 1, x, y);
    // for (int k = 0; k < N; k++)
    // {
    //     if (f(N, k, x, y) < min_)
    //         min_ = f(N, k, x, y);
    // }
    // cout << min_ + min(x, y) << endl;

    return 0;
}