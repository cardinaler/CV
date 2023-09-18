#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
int main()
{
    int K;
    char c;
    cin >> K;
    getchar();
    string s;
    for (int i = 0; i < K; ++i)
    {
        int j;
        getline(cin, s);
        s.insert(0, " ");
        j = s.rfind(' ');
        cout << s.substr(j + 1);
        s.erase(j);
        while (s != "")
        {
            j = s.rfind(' ');
            cout << s.substr(j);
            s.erase(j);
        }
        cout << endl;
    }
    return 0;
}