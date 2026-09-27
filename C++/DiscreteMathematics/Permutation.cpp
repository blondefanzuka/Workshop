#include <iostream>
#include <vector>
#include <string>
using namespace std;
string permutation(int numberCount, long long k)
{
    vector<int> numbers;
    for (int i = 1; i <= numberCount; i++)
    {
        numbers.push_back(i);
    }
    string result;
    k--;
    long long factorial = 1;
    for (int i = 1; i < numberCount; i++)
    {
        factorial *= i;
    }
    for (int i = numberCount - 1; i >= 0; i--)
    {
        int index = k / factorial;
        result += to_string(numbers[index]);
        numbers.erase(numbers.begin() + index);
        k = k % factorial;
        if (i > 0)
        {
            factorial = factorial / i;
        }
    }
    return result;
}
int main()
{
    int numberCount;
    long long k;
    cout << "Enter the amount of numbers: " << endl;
    cin >> numberCount;
    cout << "Enter k: " << endl;
    cin >> k;
    cout << "The k-th permutation is: " << permutation(numberCount, k) << endl;
    return 0;
}