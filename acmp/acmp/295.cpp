#include <iostream>
#include <string>
using namespace std;
int main()
{
    string s, w, tmp;
    char c;
    int dif;
    int l1, l2;
    int min_d;
    cin >> s;
    cin >> w;
    c = w[0];
    l1 = s.length();
    l2 = w.length();
    min_d = 100;
    for (int i = 0; i < l1 - l2 + 1; ++i)
    {
        dif = s[i] - c;
        tmp = s;
        for (int j = 0; tmp[j]; ++j)
        {
            tmp[j] = (tmp[j] - dif) % int('Z');
        }
        if (tmp.find(w) != -1)
        {
            if (dif < min_d)
                min_d = dif;
        }
    }
    if (min_d != 100)
    {
        for (int j = 0; s[j]; ++j)
        {
            s[j] = s[j] - min_d;
        }
        cout << s;
    }
    else
    {
        cout << "IMPOSSIBLE";
    }
    cout << endl;

    return 0;
}