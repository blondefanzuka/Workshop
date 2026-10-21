#include <iostream>
#include <stack>
using namespace std;
void moveBetweenPegs(stack<int>& firstPeg, stack<int>& secondPeg, char firstName, char secondName)
{
    if (firstPeg.empty())
    {
        int disk = secondPeg.top();
        secondPeg.pop();
        firstPeg.push(disk);

        cout << "Move disk " << disk << " from " << secondName << " to " << firstName << endl;
    }
    else if (secondPeg.empty())
    {
        int disk = firstPeg.top();
        firstPeg.pop();
        secondPeg.push(disk);

        cout << "Move disk " << disk << " from " << firstName << " to " << secondName << endl;
    }
    else if (firstPeg.top() < secondPeg.top())
    {
        int disk = firstPeg.top();
        firstPeg.pop();
        secondPeg.push(disk);

        cout << "Move disk " << disk << " from " << firstName << " to " << secondName << endl;
    }
    else
    {
        int disk = secondPeg.top();
        secondPeg.pop();
        firstPeg.push(disk);

        cout << "Move disk " << disk << " from " << secondName << " to " << firstName << endl;
    }
}
void hanoiTowersIterative(int n, char start, char temp, char final)
{
    if (n <= 0)
    {
        return;
    }
    stack<int> startPeg;
    stack<int> tempPeg;
    stack<int> finalPeg;
    for (int i = n; i >= 1; i--)
    {
        startPeg.push(i);
    }
    if (n % 2 == 0)
    {
        swap(temp, final);
    }
    int totalMoves = 1;
    for (int i = 1; i <= n; i++)
    {
        totalMoves *= 2;
    }
    totalMoves--;
    for (int move = 1; move <= totalMoves; move++)
    {
        if (move % 3 == 1)
        {
            moveBetweenPegs(startPeg, finalPeg, start, final);
        }
        else if (move % 3 == 2)
        {
            moveBetweenPegs(startPeg, tempPeg, start, temp);
        }
        else
        {
            moveBetweenPegs(tempPeg, finalPeg, temp, final);
        }
    }
}
int main()
{
    int diskCount;
    cout << "Enter the amount of disks you want on the tower: " << endl;
    cin >> diskCount;
    hanoiTowersIterative(diskCount, 'A', 'B', 'C');
    cout << "Done";
    return 0;
}