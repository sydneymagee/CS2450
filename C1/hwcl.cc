#include <stdio.h>

void printRectangleWhile(int w, int h)
{
    int updateW = w;
    int updateH = h;
    
    if (w < 1 || h < 1)
    {
        return;
    }
    
    if (w == 1 || h == 1)
    {
        printf("+");
    }

    while (updateH > 0)
    {
        int row = w;
        if (updateH == h || updateH == 1)
        {
            while (row>0)
            {
                printf("+");
                row--;
            }
            printf("\n");
        }
        else
        {
            printf("+");
            int sub = w -2;
            while (sub > 0)
            {
                printf("-");
                sub--;
            }
            printf("+\n");
        }
        updateH--;
        updateW--;
    }
}
 
void printTriangleFor(int h)
{
    if (h < 1)
    {
        return;
    }
    if (h == 1)
    {
        printf("+");
    }

    int column = h - 1;

    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < h; j++)
        {
            printf(" ");
        }
        column--;
        for (int k = 0; k < i; k++)
        {
            printf("+");
        }
        printf("\n");
    }
    for (int v = 0; v < h; v++)
    {
        printf("+");
    }
    printf("\n");
}



