#include <iostream>
using namespace std;
int main()
{
    string e = "2.7182818284590452353602875";
    int n;
    cin >> n;
    if (n == 0)
    {
        cout << 3;
    }
    else
    {
        if ((n < 25) && (e[n + 2] - '0' >= 5))
        {
            e[n + 1] = e[n + 1] + 1;
        }
        cout << e.substr(0, n + 2) << endl;
    }
    return 0;
}