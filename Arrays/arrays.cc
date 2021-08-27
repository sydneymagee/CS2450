#include <stdio.h>


double findAbsolute(double arr[], double num)
{
    int i = 0;
    for (i=0; i < num; i++)
    {
        if(arr[i] < 0)
        {
            arr[i] = arr[i] * (-1);
        }
    }
    return arr[i];
}
double findCloseToZero(double arr[], int num)
{
    int i = 0;
    double close= arr[0];
    for(i = 0; i< num; i++)
    {
        if(arr[i] == 0)
        {
            close = arr[i];
        }
        if(arr[i] > 0 && arr[i] <= findAbsolute(arr, close))
        {
            close = arr[i];
        }
        if(arr[i] < 0 && arr[i] < findAbsolute(arr, close))
        {
            close = arr[i];
        }
    }
    return close;

}
double findFarFromZero(double arr[], int num)
{
    int i = 0;
    double large = arr[0];
    for(i = 0; i < num; i++)
    {
        if(arr[i] < 0)
        {
            large = arr[i] * (-1);
        }
        if(arr[i] > large)
        {
            large = arr[i];
        }
    }
    return large;
}   
int countDivisible(int arr[], int num, int divisor)
{
    int i = 0;
    int cntr = 0;
    for (i = 0; i < num; i ++)
    {
        if (arr[i] % divisor  == 0)
        {
            cntr++;
        }
    }
    return cntr;
}
int countWholeNumbers(double arr[], int num)
{
    int i = 0;
    int cntr = 0;
    for (i = 0; i < num; i++)
    {
        if (((int)arr[i] % 2) == 0.0)
        {
            cntr++;
        }
    }
    return cntr;

}
double sumFractions(double arr[], int num)
{
    double sum = 0;
    double newnum = 0.0;
    for (int i = 0; i < num; i++)
    {
        int number = (int)arr[i];
        newnum = arr[i] - number;
        sum += newnum;
    }
    return sum;
}
int countAbsoluteRangeValues(double arr[], int num, double value)
{ 
    double low = 0;
    double high = 0;
    int cntr = 0;
    for(int i = 0; i < num; i++)
    {
        if (arr[i] < 0)
        {
            low = arr[i] * (-1);
        }
        if (arr[i] == value)
        {
            return value;
        }
    }
}

