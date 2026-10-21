#include <iostream>
using namespace std;
int triangle(int row, int col)
{
    if (col == 0 || col == row)
    {
        return 1;
    }
    return triangle(row - 1, col - 1) + triangle(row - 1, col);
}
int main()
{
    int length;
    cout << "Enter the length of the triangle you want to generate: " << endl;
    cin >> length;
    for (int i = 0; i < length; i++)
    {
        for (int j = 0; j <= i; j++)
        {
            cout << triangle(i, j) << " ";
        }
        cout << endl;
    }
    cout << "Generated the triangle" << endl;
    return 0;
}