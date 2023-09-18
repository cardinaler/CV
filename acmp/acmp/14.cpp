#include <iostream>
using namespace std;
int main()
{
    int A, B, a, b;
    cin >> A >> B;
    a = A;
    b = B;
    while (B = B % A)
        swap(A, B);
    cout << a * b / A << endl;
    return 0;
}