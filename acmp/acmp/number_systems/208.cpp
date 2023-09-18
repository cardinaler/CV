#include <iostream>
#include <algorithm>
#include <string>
using namespace std;
void shr(string &s)
{
    int l = s.length() - 1;
    char tmp;
    tmp = s[0];
    s[0] = s[l];
    for (int i = 1; i < l + 1; i++)
    {
        swap(s[i], tmp);
    }
}
int main()
{
    int N;
    cin >> N;
    string s = "";
    do
    {
        s = char(N % 2 + '0') + s;
        N /= 2;
    } while (N);
    for (int i = 0; s[i] == '0'; --i)
    {
        s.erase(i, 1);
    }
    string max = s;
    for (int i = s.length(); i > 0; --i)
    {
        shr(s);
        if (s > max)
        {
            max = s;
        }
    }
    for (char c : max)
    {
        N = 2 * N + (c - '0');
    }
    cout << N << endl;

    return 0;
}