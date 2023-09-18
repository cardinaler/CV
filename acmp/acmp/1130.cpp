#include <iostream>
#include <cmath>
using namespace std;
int main()
{
    unsigned long long int N;
    unsigned long long int R = N, L = 1, M;
    unsigned int S;
    cin >> N;
    int counter = 0;
    M = 1;
    while (M < N)
    {
        M = M * 2;
        counter++;
    }
    cout << counter << endl;
}