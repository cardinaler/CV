#include <iostream>
using namespace std;
int main()
{
    string s;
    getline(cin, s);
    int max_let = 0;
    int max_dig = 0;
    for (int c : s)
    {
        if (isdigit(c))
        {
            if (c > max_dig)
            {
                max_dig = c;
            }
        }
        else if (isupper(c))
        {
            if (c > max_let)
            {
                max_let = c;
            }
        }
        else
        {
            cout << -1 << endl;
            return 0;
        }
    }
    if (max_let)
    {
        cout << max_let - 65 + 10 + 1 << endl;
    }
    else if (max_dig)
    {
        if (max_dig == '0')
        {
            cout << 2 << endl;
        }
        else
        {
            cout << max_dig - 48 + 1 << endl;
        }
    }
    else
    {
        cout << -1 << endl;
    }

    return 0;
}