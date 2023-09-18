#include <iostream>
using namespace std;
int main()
{
    int i, j;
    cin >> i >> j;
    while (j = j % i)
        swap(i, j);
    // i NOD
    // cout << i << endl;
    unsigned long long int F[i + 1];
    F[0] = 0;
    F[1] = 1;
    for (int k = 2; k < i + 1; ++k)
    {
        F[k] = F[k - 1] + F[k - 2];
        F[k] = F[k] % 1000000000;
    }
    cout << F[i];
}