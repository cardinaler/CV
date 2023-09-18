#include <iostream>
using namespace std;
typedef signed int sint;
int main()
{
    string s; // C7-D5 keke
    string letters = "ABCDEFGH";
    string numbers = "12345678";
    cin >> s;
    if ((s.length() != 5) || (s[2] != '-') || ((sint)letters.find(s[0]) == -1) || ((sint)letters.find(s[3]) == -1) || ((sint)numbers.find(s[1]) == -1) || ((sint)numbers.find(s[4]) == -1))
    {
        cout << "ERROR" << endl;
        //   cout << (s.length() != 5) << (s[2] != '-') << ((sint)letters.find(s[0]) == -1) << ((sint)letters.find(s[3]) == -1) << ((sint)numbers.find(s[1]) == -1) << ((sint)numbers.find(s[4] == -1)) << endl;
    }
    else
    {
        if (abs(s[3] - s[0]) == 1 && abs(s[4] - s[1]) == 2 || abs(s[3] - s[0]) == 2 && abs(s[4] - s[1]) == 1)
        {
            cout << "YES" << endl;
        }
        else
        {
            cout << "NO" << endl;
        }
    }
    return 0;
}