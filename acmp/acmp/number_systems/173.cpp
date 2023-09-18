#include <iostream>
using namespace std;
bool ispalindrom(const string &s)
{
    int f = 0;
    int l = s.length() - 1;
    while (f < l)
    {
        if (s[f] != s[l])
        {
            return false;
        }
        f++;
        l--;
    }
    return true;
}
int counter = 0;
int main()
{
    string s;
    string answer = "";
    int N;
    cin >> N;
    int num;

    for (int k = 2; k <= 36; ++k)
    {
        s = "";
        num = N;
        do
        {
            s = s + char(num % k + '0');
            num /= k;
        } while (num);
        if (ispalindrom(s))
        {
            counter++;
            answer = answer + to_string(k) + ' ';
        }
    }
    if (counter == 0)
    {
        cout << "none" << endl;
    }
    else if (counter == 1)
    {
        cout << "unique" << endl;
    }
    else
    {
        cout << "multiple" << endl;
    }
    cout << answer << endl;
    return 0;
}