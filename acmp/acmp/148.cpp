#include <iostream>
using namespace std;
int main()
{
    int A, B;
    cin >> A >> B;
    while (B = B % A)
        swap(A, B);
    cout << A << endl;
    return 0;
}