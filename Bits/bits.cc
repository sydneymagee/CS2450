#include <stdio.h>


int getMask(int start, int end, int binary)
{
    int mask = 0;
    int x  = 1;
    if (binary != 1 && binary != 0)
    {
        return 0;
    }
    if (start < 0 || start > 31 || end < 0 || end > 31)
    {
        return 0;
    }
    if (start > end)
    {
        return 0;
    }
    for (int i = 0; i < 32; i++)
    {
        if(i >= start && i <= end)
        {
            mask = mask | x;
        }    
        x = x << 1;    
    }
    if (binary == 0)
    {
        mask = ~mask;
    }
    return mask;
}
int getSubInt(int start, int end, int value)
{
    int mask = getMask(start, end, 1);
    unsigned int returnVal = value & mask;
    returnVal = returnVal >> start;
    return returnVal;
}
void printDashHex(int value)
{
    int mask = 0xF0000000;
    int arr[8];
    for (int i = 0; i < 8; i++)
    {
        arr[i] = (unsigned)(value & mask) >> 28;
        value = value << 4;
    }
    for (int i = 0; i < 15; i++)
    {
        if(i % 2 == 0)
        {
            printf("%X", arr[i/2]);
        }
        else
        {
            printf("-");
        }
    }
    printf("\n");
}


