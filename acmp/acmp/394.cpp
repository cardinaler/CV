#include <iostream>
using namespace std;
int main()
{
    long long int n, m, M, N;
    cin >> n >> m;
    N = n;
    M = m;
    while (M = M % N)
        swap(N, M);
    N = m * n / N; // NOK
    cout << N / m;
    return 0;
}