#include <iostream>
using namespace std;
int main()
{
    unsigned int N_10, M_10;
    string s1, s2;
    cin >> s1 >> s2;
    N_10 = 0;
    for (char c : s1)
    {
        N_10 = 3 * N_10 + c - '0';
    }
    M_10 = 0;
    for (char c : s2)
    {
        M_10 = 3 * M_10 + c - '0';
    }
    cout << (long long)(M_10 + N_10) << endl;
    return 0;
}