#include <iostream>
using namespace std;

int main()
{
    long long int L_x, R_x, L_y, R_y;
    long long int m_x, m_y;
    int shift_x, shift_y;
    L_x = L_y = -1000 * 1000 - 1;
    R_x = R_y = 1000 * 1000 + 1;
    m_x = L_x / 2 + R_x / 2;
    m_y = L_y / 2 + R_y / 2;
    do
    {
        cout << m_x << " " << m_y << endl;
        cin >> shift_x >> shift_y;
        if (shift_y < 0)
        {
            L_y--;
            R_y = m_y - 1;
        }
        else if (shift_y > 0)
        {
            R_y++;
            L_y = m_y + 1;
        }
        if (shift_x < 0)
        {
            L_x--;
            R_x = m_x - 1;
        }
        else if (shift_x > 0)
        {
            R_x++;
            L_x = m_x + 1;
        }
        if (shift_x != 0)
        {
            m_x = L_x / 2 + R_x / 2;
        }
        if (shift_y != 0)
        {
            m_y = L_y / 2 + R_y / 2;
        }
    } while (shift_x != 0 || shift_y != 0);
    return 0;
}