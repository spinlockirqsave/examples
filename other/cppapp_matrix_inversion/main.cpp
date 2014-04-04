/* 
 * File:   main.cpp
 * Author: root
 *
 * Created on November 24, 2013, 1:17 AM
 */

//
// An example of the matrix txt file is shown below:
/*    
1,2,3,
4,6,5,
3,7,8,
*/
//
#include<string>
#include<cstdlib>
#include<fstream>
#include<vector>
#include<iostream>

// Compiled with Code::Blocks 10.05 over Windows 7

#include<stdio.h>
#define MAX 10

int lcm(int x,int y);

int main()
{
    int i,j,k,r,c,a[MAX][MAX],b[MAX][MAX],det=1,l,d1,d2;
    printf("\nEnter the number of Rows of the Matrix: ");
    scanf("%d",&r);
    printf("\nEnter the number of Columns of the Matrix: ");
    scanf("%d",&c);
    if(r==c)
    {
       printf("\nEnter the Elements of the Matrix:\n");
       for(i=0;i<r;i++)
       {
          for(j=0;j<c;j++)
          {
             scanf("%d",&a[i][j]);
          }
       }
       for(i=0;i<r-1;i++)
       {
           for(j=i+1;j<r;j++)
           {
             l=lcm(a[i][i],a[j][i]);
             if(l!=0&&(a[i][i]!=0&&a[j][i]!=0))
             {
               l=(a[i][i]*a[j][i])/l;
               d1=l/a[i][i];
               d2=l/a[j][i];
               a[j][i]=0;
               for(k=i+1;k<r;k++)
               {
                 a[j][k]=(d2*a[j][k])-(d1*a[i][k]);
               }
             }
           }
        }
        printf("\nThe given Matrix after Gauss Elimination is:\n");
        for(i=0;i<r;i++)
        {
          for(j=0;j<c;j++)
          {
             printf("%d\t",a[i][j]);
          }
          printf("\n");
        }
        for(i=r-1;i>0;i--)
        {
           for(j=i-1;j>=0;j--)
           {
             l=lcm(a[i][i],a[j][i]);
             if(l!=0&&(a[i][i]!=0&&a[j][i]!=0))
             {
               l=(a[i][i]*a[j][i])/l;
               d1=l/a[i][i];
               d2=l/a[j][i];
               for(k=0;k<=r;k++)
               {
                 a[j][k]=(d2*a[j][k])-(d1*a[i][k]);
               }
             }
           }
        }
        printf("\nThe given Matrix after Gauss Jordan Elimination is:\n");
        for(i=0;i<r;i++)
        {
          for(j=0;j<c;j++)
          {
             printf("%d\t",a[i][j]);
          }
          printf("\n");
        }
     }
     else
     {
        printf("\nThis is not a Square Matrix!!!\n");
     }
     return 0;
}

int lcm(int x,int y)
{
    int t;
    while (y != 0)
    {
      t=y;
      y=x%y;
      x=t;
    }
    return x;
}

