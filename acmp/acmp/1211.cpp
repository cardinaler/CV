#include <iostream>
using namespace std;

int main()
{
    unsigned long long int A, K, B, M, X, R, L, aver;
    cin >> A >> K >> B >> M >> X;
    long double a;
    cin >> a;
    cout << a;
    L = 1;
    R = X;
    while (L < R)
    {
        aver = (L + R) / 2;
        if (aver * (A - A / K) + aver * (B - B / M) < X)
        {
            L = aver + 1;
        }
        else
        {
            R = aver;
        }
    }
    cout << L << endl;
}