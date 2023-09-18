#include <iostream>
using namespace std;
int main()
{
    string keyboard = "qwertyuiopasdfghjklzxcvbnm";
    char key;
    cin >> key;
    cout << keyboard[(keyboard.find(key) + 1) % keyboard.length()] << endl;
}