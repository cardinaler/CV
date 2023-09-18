#include <iostream>
using namespace std;
int main()
{
    int m;
    cin >> m;
    string s = "";
    do
    {
        s = char(m % 2 + '0') + s;
        m /= 2;
    } while (m);
    // m = 0
    for (int i = s.length() - 1; i >= 0; --i)
    {
        m = m * 2 + s[i] - '0';
    }
    cout << m << endl;
    return 0;
}