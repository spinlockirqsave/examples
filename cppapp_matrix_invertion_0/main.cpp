/* 
 * File:   main.cpp
 * Author: http://hullooo.blogspot.com/2011/02/matrix-inversion-by-gauss-jordan.html
 *
 * Created on November 24, 2013, 2:21 AM
 */

#include<stdio.h>
#include<math.h>

#define maximum 10
#define minvalue 0.0005

int main()
{
 float augmentedmatrix[maximum][2*maximum] ;  
                                                                /* 2D array declared to store augmented matrix */
 float temporary, r ;
 int i, j, k, dimension, temp;                                  /* declaring counter variables for loops */


 printf("\n INVERSE OF NON-SINGULAR MATRIX BY GAUSS-JORDAN"
                  " ELIMINATION  METHOD");

 printf("\n Enter the dimension of the matrix to be provided as input : \n");
 scanf("%d",&dimension);

 /*   storing augmented matrix as a matrix of dimension
      (dimension)x(2*dimension) in 2D array  */

 printf("\n Enter a non-singular %dx%d matrix : \n",dimension,dimension);
 for(i=0; i<dimension; i++)
  for(j=0; j<dimension; j++)
            scanf("%f",&augmentedmatrix[i][j]) ;

 /* augmenting with identity matrix of similar dimensions */

 for(i=0;i<dimension; i++)
  for(j=dimension; j<2*dimension; j++)
      if(i==j%dimension)
         augmentedmatrix[i][j]=1;
      else
         augmentedmatrix[i][j]=0;

 /* using gauss-jordan elimination */

 for(j=0; j<dimension; j++)
 {
  temp=j;

 /* finding maximum jth column element in last (dimension-j) rows */

  for(i=j+1; i<dimension; i++)
if(augmentedmatrix[i][j]>augmentedmatrix[temp][j])
                        temp=i;

  if(fabs(augmentedmatrix[temp][j])<minvalue)
             {
                printf("\n Elements are too small to deal with !!!");
                return -1;
             }

 /* swapping row which has maximum jth column element */

  if(temp!=j)
            for(k=0; k<2*dimension; k++)
            {
            temporary=augmentedmatrix[j][k] ;
            augmentedmatrix[j][k]=augmentedmatrix[temp][k] ;
            augmentedmatrix[temp][k]=temporary ;
            }

/* performing row operations to form required identity matrix out of the input matrix */

  for(i=0; i<dimension; i++)
            if(i!=j)
            {
            r=augmentedmatrix[i][j];
            for(k=0; k<2*dimension; k++)
              augmentedmatrix[i][k]-=(augmentedmatrix[j][k]/augmentedmatrix[j][j])*r ;
            }
            else
            {
            r=augmentedmatrix[i][j];
            for(k=0; k<2*dimension; k++)
              augmentedmatrix[i][k]/=r ;
            }

 }
          
 /* Display augmented matrix */

 printf("\n After Gauss-Jordan elimination, augmented matrix is : \n\n") ;

 for(i=0; i<dimension; i++)
 {
  for(j=0; j<2*dimension; j++)
            printf("  %4.2f",augmentedmatrix[i][j]) ;
  printf("\n");
 }


 /* displaying inverse of the non-singular matrix */

 printf("\n\n\n The inverse of the entered non-singular matrix is : \n\n");

 for(i=0; i<dimension; i++)
 {
  for(j=dimension; j<2*dimension; j++)
            printf("  %.5f",augmentedmatrix[i][j]);
  printf("\n");
 }

 }

