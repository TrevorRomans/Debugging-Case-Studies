// RAW QUICKSORT, REQUIRES SIMPLIFICATION
// Created by Trevor Romans

#include <iostream>
#include <algorithm>
#include <vector>
#include "Sorter.cpp"

using namespace std;

//void trade(int &x, int &y);
void disp(int x[], int size);
bool isSorted(int x[], int size);
//bool complete(int x[]);
//int* trade(int x[], int i, int &hold);
int* sort(QS q, int& boundLeft, int& boundRight, int& hold, int size);


int main() // NOTE TO SELF: Try creating a second array as a global variable that gets changed in place of x and then set x equal to it at the end of the loop
{
    QS q;
    int boundLeft = 0;
    int boundRight = 15;
    int hold = 0;
    int size = 16;
    bool status = false;
    int loop = 0;
//    int A = 3;
//    int B = 9;
    
    int x[16] = {10,15,6,14,4,13,8,1,2,7,11,5,16,12,9,3};
    disp(x, size);
    while(status == false && loop < 16)
    {
        int* p;
//        if (loop == 4)
//        {
//            p = sort(q, A, B, hold, size);
//        }
//        else
//        {
            p = sort(q, boundLeft, boundRight, hold, size);
//        }
        for(int i = 0; i < size; i++)
        {
            x[i] = p[i];
        }
        disp(x, 16);
        status = isSorted(x, size);
        loop++;
    }
    
    cout << "Done!" << endl;
    disp(x, 16);
    
    return 0;
}

//void trade(int &x, int &y)
//{
//    int tmp = x;
//    x = y;
//    y = tmp;
//}

void disp(int x[], int size)
{
    for(int i = 0; i < size; i++)
    {
        cout << x[i] << ", ";
    }
    cout << endl;
}

bool isSorted(int x[], int size)
{
    bool proper = true;
    for(int i = 0; i < size - 1; i++)
    {
        if (x[i] > x[i + 1])
        {
            proper = false;
            break;
        }
        else
        {
            proper = true;
        }
    }
    
    if (proper == true)
    {
        return true;
    }
    else
    {
        return false;
    }
}

//bool complete(int x[])
//{
//    if (x[0]<x[1] && x[1]<x[2] && x[2]<x[3] && x[3]<x[4] && x[4]<x[5] && x[5]<x[6] && x[6]<x[7] && x[7]<x[8] && x[8]<x[9] && x[9]<x[10] && x[10]<x[11] && x[11]<x[12] && x[12]<x[13] && x[13]<x[14] && x[14]<x[15])
//    {
//        return true;
//    }
//    else
//    {
//        return false;
//    }
//}

int* trade(int x[], int i, int &hold)
{
    static int tmp[16];
    int a = x[i];
    for(int v = 0; v < 16; v++)
    {
        tmp[v] = 0;
    }
    
    for(int j = 0; j < 16; j++)
    {
        if (j == i)
        {
            tmp[j] = hold;
        }
        else
        {
            tmp[j] = x[j];
        }
    }
    
    hold = a;
    return tmp;
}

int* sort(QS q, int& boundLeft, int& boundRight, int& hold, int size)
{
    static int a[16] = {10,15,6,14,4,13,8,1,2,7,11,5,16,12,9,3};
    static int index[16] = {16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16}; // GAME CHANGER: The issue that took the longest to fix was that it would run 3 times in a row (maybe 4) and then it would stop changing. After much puzzling and searching, I determined the cause. The vector was not getting updated. The size was always the same, and even after initializing it with a starting number to make the size 1, the boundaries for the sort would always be the same since it was always using the same vector. The fix was to create this array that would be in charge of tracking the completed indexes.
    static int place = 0;
    int* ref;
    ref = &index[0];
    
    q.setLeft(boundLeft, size, ref, place);
    q.setRight(boundRight, size, boundLeft, ref, place);
    swap(a[boundLeft], hold);
    
    while(boundLeft < boundRight) // PROBLEM FOUND: when checking a number directly next to two values that are already marked off, the two bounds will be equal
    {
        if (boundLeft == boundRight)
        {
            boundRight--;
        }
        else
        {
            if (a[boundLeft] == 0) // Checking that the right side is bigger than hold
            {
                if (a[boundRight] < hold)
                {
                    swap(a[boundLeft], a[boundRight]); // Found in the algorithm header, swap can switch two values in an array
                }
                else
                {
                    boundRight--;
                }
            }
            else if (a[boundRight] == 0) // Must be else if, because if the first part runs, the right bound will then be zero, so this makes sure that only one runs at a time
            {
                if (a[boundLeft] > hold)
                {
                    swap(a[boundLeft], a[boundRight]);
                }
                else
                {
                    boundLeft++;
                }
            }
        }
    }
    
    q.checkOff(boundLeft);
    index[place] = boundLeft;
    place++;
    swap(a[boundLeft], hold);
    
    return a;
}
