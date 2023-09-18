#include <iostream>
using namespace std;
int main()
{
    char c;
    unsigned int L = 1;
    unsigned int x;
    unsigned int R = 1000000000;
    do
    {
        x = L / 2 + R / 2;
        cout << x << endl;
        fflush(stdout);

        cin >> c;
        if (c == '>')
        {
            L = x + 1;
        }
        else
            R = x;

    } while (c != '=');

    return 0;
}