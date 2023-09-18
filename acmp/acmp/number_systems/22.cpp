#include <iostream>
using namespace std;
int main()
{
    unsigned long long int n;
    int counter = 0;
    cin >> n;
    while (n)
    {
        if (n % 2 == 1)
        {
            ++counter;
        }
        n /= 2;
    }
    cout << counter << endl;
}