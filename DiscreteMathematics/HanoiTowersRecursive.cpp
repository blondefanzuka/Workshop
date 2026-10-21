#include <iostream>
using namespace std;
void hanoiTowers(int n, char start, char temp, char final)
{
    if (n <= 0) {
        return;
    }
    if (n == 1) {
        cout << "Move disk 1 from " << start << " to " << final << endl;
        return;
    }
    hanoiTowers(n - 1, start, final, temp);
    cout << "Move disk " << n << " from " << start << " to " << final << endl;
    hanoiTowers(n - 1, temp, start, final);
}
int main()
{
    int diskCount;
    cout << "Enter the amount of disks you want on the tower: " << endl;
    cin >> diskCount;
    hanoiTowers(diskCount, 'A', 'B', 'C');
    cout << "Done";
    return 0;
}
