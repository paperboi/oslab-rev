#include<stdio.h>
#include<math.h>
#include<sys/types.h>
#include<unistd.h>

float determinant(float a[25][25], float k)
{
      float s = 1, det = 0, b[25][25];
      int i, j, m, n, c;
      
      if (k == 1)
         return (a[0][0]);

      else
      {
         det = 0;
         for (c = 0; c < k; c++)
         {
            m = 0;
            n = 0;
            for (i = 0;i < k; i++)
            {
                for (j = 0 ;j < k; j++)
                {
                    b[i][j] = 0;
                    if (i != 0 && j != c)
                    {
                       b[m][n] = a[i][j];
                       if (n < (k - 2))
                        n++;

                       else
                       {
                         n = 0;
                         m++;
                       }
                     }
                 }
             }
             
             det = det + s * (a[0][c] * determinant(b, k - 1));
             s = -1 * s;
           }

        }

        return (det);

}
    
void transpose(float num[25][25], float fac[25][25], float r)
{
      int i, j;
      float b[25][25], inverse[25][25], d;

      for (i = 0;i < r; i++)
         for (j = 0;j < r; j++)
             b[i][j] = fac[j][i];

      d = determinant(num, r);

      for (i = 0;i < r; i++)
         for (j = 0;j < r; j++)
            inverse[i][j] = b[i][j] / d;

       printf("\n\n\nThe inverse of matrix is : \n");


       for (i = 0;i < r; i++)
       {
         for (j = 0;j < r; j++)
             printf("\t%f", inverse[i][j]);
        printf("\n");

       }

}
     

void cofactor(float num[25][25], float f)
{
     float b[25][25], fac[25][25];
     int p, q, m, n, i, j;

     for (q = 0;q < f; q++)
     {
     	for (p = 0;p < f; p++)
        {
         m = 0;
         n = 0;
         for (i = 0;i < f; i++)
         {
           for (j = 0;j < f; j++)
           {
              if (i != q && j != p)
              {
                b[m][n] = num[i][j];
                if (n < (f - 2))
                 n++;

                else
                {
                   n = 0;
                   m++;
                }
               }
            }
          }

          fac[q][p] = pow(-1, q + p) * determinant(b, f - 1);
        }
      }

      transpose(num, fac, f);

}
  
    
int main()
{

      float a[25][25], k, d;
      int i, j;
      pid_t pid;
      
      
      
     
	      printf("Enter the order of the Matrix : ");
	      scanf("%f", &k);
	      printf("Enter the elements of %.0fX%.0f Matrix : \n", k, k);

	      for (i = 0;i < k; i++)
		 for (j = 0;j < k; j++)
		      scanf("%f", &a[i][j]);

      pid=vfork();
      
      if(pid==0)
      {
	      d = determinant(a, k);
	      exit(0);
      }

      else if(pid>0)
      {
	       wait(pid);
	       
	       if(d==0)
	        printf("Inverse can't be calculated\n");
	       else
	        cofactor(a, k);
	       	      
      }

}
