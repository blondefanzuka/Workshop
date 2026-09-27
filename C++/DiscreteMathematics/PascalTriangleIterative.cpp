#include <iostream>
using namespace std;
int main()
{
    int length, value;
    cout << "Enter the length of the triangle you want to generate: " << endl;
    cin >> length;
    for (int row = 0; row < length; row++)
    {
        value = 1;
        for (int col = 0; col <= row; col++)
        {
            cout << value << " ";
            value = value * (row - col) / (col + 1);
        }
        cout << endl;
    }
    cout << "Generated the triangle" << endl;
    return 0;
}
