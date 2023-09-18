#include <iostream>
using namespace std;
int main()
{
    int n, k;
    unsigned long long int multi = 1, sum = 0;
    cin >> n >> k;
    do
    {
        multi *= (n % k);
        sum += (n % k);
        n /= k;
    } while (n);
    cout << signed(multi - sum) << endl;
    return 0;
}