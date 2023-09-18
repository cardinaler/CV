#include <iostream>
using namespace std;
int main()
{
    string flowers[3] = {"GCV", "VGC", "CVG"};
    int K;
    cin >> K;
    cout << flowers[K % 3] << endl;
}