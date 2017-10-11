#include <stdio.h>
#define  SIZE   10
 
int main()
{
       // declare and initialize an array named n with size SIZE...
       int n[SIZE] = {19, 3, 15, 7, 11, 9, 13, 5, 17, 1};
       int i, j;
       // display the table header...
       printf("%s%13s%17s\n","Element/index", "Value", "Histogram");
       // do the iteration...
       // the outer for loop, read row by row...
       for(i=0; i <SIZE; i++)
       {
              printf("%9d%15d       ", i, n[i]);
              // the inner for loop, for every row, read column by column and print the bar...
              for(j = 1; j<= n[i]; j++)
              // print the asterisk bar...repeat...
              printf("*");
              // go to new line for new row...repeats...
              printf("\n");
       }
       return   0;
}