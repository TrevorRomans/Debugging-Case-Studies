#include <iostream>
#include <vector>

using namespace std;

class QS
{
private:
    vector <int> v = {16};
    int list[16];
    int lSize;
public:
    QS()
    {
        QS(16); // NOTE: In this context, 0 is not a value to use as the default, since 0 is a valid index and will mess with the result
    }
    QS(int x)
    {
        for(int i = 0; i < 16; i++)
        {
            list[i] = x;
        }
        lSize = 1;
    }
    
    void checkOff(int x)
    {
        v.push_back(x);
//        list[lSize - 1] = x;
//        lSize++;
    }
    
    void setLeft(int &x, int size, int* p, int place)
    {
        bool checked = false;
        
        if (place != 0)
        {
            for(int i = 0; i < size; i++)
            {
                for(int j = 0; j <= place; j++)
                {
                    if (i == p[j]) // If the index is in the vector
                    {
                        checked = true;
                        break;
                    }
                    else
                    {
                        checked = false;
                    }
                    
                    if (j == place && checked == false) // If the index never appeared in the vector
                    {
                        x = i;
                        break;
                    }
                }
                if (checked == false)
                {
                    break;
                }
            }
        }
        else
        {
            x = 0;
        }
    }
    
    void setRight(int &x, int size, int left, int* p, int place) // MISTAKE FOUND: Do not just copy paste the setLeft function to here and add the z variable. This causes the program to search for the next value that is not placed, but what we really need it to do is find the next checked value and set the bound to the spot in front of it
    {
        int z = left + 1;
        
        bool checked = false;
        
        if (place != 0)
        {
            for(int i = z; i < size; i++) // Rather than going from front to back, it starts immediately after the left bound
            {
                for(int j = 0; j <= place; j++)
                {
                    if (i == p[j]) // If the index is in the vector
                    {
                        x = i-1;
                        checked = true;
                        break;
                    }
                    else
                    {
                        checked = false;
                    }
                }
                if (checked == true)
                {
                    break;
                }
            }
            if (checked == false)
            {
                x = size - 1;
            }
        }
        else
        {
            x = size - 1;
        }
    }
};
