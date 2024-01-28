#include <stdio.h>
#include<stdlib.h>
#include <omp.h>
#define MAX_DIM (1000)
double matA[MAX_DIM][MAX_DIM];
double matB[MAX_DIM][MAX_DIM];
double C[MAX_DIM][MAX_DIM];
double vectA[MAX_DIM];
double notesA[3][3] = {{1,2,3}, {4,5,6}, {7,8,9}};
double notesB[3][3] = {{9,8,7}, {6,5,4}, {3,2,1}};
double notesX[3] = {11,7,13};
int thread_count=4;
int debug=0;
FILE *fp;
void  matrix_print (int nr, int nc, double A[][MAX_DIM]);
void mmult(int n, double A[][MAX_DIM], double B[][MAX_DIM]);
void vmult(int n, double A[][MAX_DIM], double x[MAX_DIM]);
void vector_print (int nr, double x[MAX_DIM]);
int main(int argc, char** argv)
{
    fp = fopen("results.txt", "w");
    
    int n;
    int row_idx, col_jdx, count=0;;
    if(argc<2)
    {
        printf("Usage: ./omp_matrix_mult <N>\n");
        return 1;
    }
    else
    {
        sscanf(argv[1], "%i", &n);
    }
    if(n == 3) //if n = 3 we will use the provided example from the hand out
    {

        printf("Using %d x %d example from Assignment 5 write up\n", n, n);
        for(row_idx = 0; row_idx < n; row_idx++)
        {
            for(col_jdx = 0; col_jdx < n; col_jdx++)
            {
                matA[row_idx][col_jdx] = notesA[row_idx][col_jdx];
                matB[row_idx][col_jdx] = notesB[row_idx][col_jdx];
            }
            vectA[row_idx] = notesX[row_idx];
        }
    }
    else
    {
        for(row_idx = 0; row_idx < n; row_idx++)
        {
            for(col_jdx = 0; col_jdx < n; col_jdx++)
            {
                matA[row_idx][col_jdx] = count++;
                matB[row_idx][col_jdx] = count++;
            }
            vectA[row_idx] = count;
        }
    }
    if(n<1000)
    {
        debug=1;
    }
    if(debug)
    {
        printf("A\n");
        fprintf(fp,"A\n");
        matrix_print(n, n, matA);
        printf("B\n");
        fprintf(fp,"B\n");
        matrix_print(n, n, matB);
        printf("VectA\n");
        fprintf(fp,"VectA\n");
        vector_print(n, vectA);
    }
        printf("\n");
        mmult(n, matA, matB);
        printf("A x VectA");
        fprintf(fp,"\nA x VectA");
        vmult(n, matA, vectA);
    
} //main---------------------------

void  matrix_print (int nr, int nc, double A[][MAX_DIM])
{

    int row_idx, col_jdx;
  
    for (row_idx = 0; row_idx < nr; row_idx++) 
    {
     	for (col_jdx = 0; col_jdx < nc; col_jdx++) 
        {
	    	printf ("%9.4f ", A[row_idx][col_jdx]);
            fprintf(fp, "%9.4f ", A[row_idx][col_jdx]);
	    }
        fprintf(fp,"\n");
	    printf("\n"); // Insert a new line at end of each row
    }
}
void mmult(int n, double A[][MAX_DIM], double B[][MAX_DIM])
{
    int row_idx, col_jdx, coeff_idx;
    // double temp;

    // for all rows - this loop speeds-up well with OpenMP
#pragma omp parallel for num_threads(thread_count) private(row_idx, col_jdx, coeff_idx) shared(n)
    for (row_idx=0; row_idx < n; ++row_idx)
    {
        for (col_jdx=0; col_jdx < n; ++col_jdx)
        {

            for(coeff_idx=0; coeff_idx < n; ++coeff_idx)
            {
                C[row_idx][col_jdx] += A[row_idx][coeff_idx] * B[coeff_idx][col_jdx];
            }
        }
    }
    if(debug)
    {
        printf("[A x B = C]");
        printf("\nComputed C is:\n");
        printf("C \n"); /*matrix_print(n, n, C);*/ printf("\n");
        fprintf(fp,"[A x B = C]");
        fprintf(fp,"\nComputed C is:\n");
        fprintf(fp,"C \n"); matrix_print(n, n, C); printf("\n");
    }
}
void vmult(int n, double A[][MAX_DIM], double x[MAX_DIM])
{
    int row_idx, col_jdx;
    double rhs[n], temp;

    // for all rows - this loop speeds up well with OpenMP
#pragma omp parallel for num_threads(thread_count) private(row_idx, col_jdx) shared(n)
    for (row_idx=0; row_idx < n; ++row_idx)
    {
        rhs[row_idx] = 0.0; temp=0.0;

        // sum up row's column coefficient x solution vector element
        // as we would do for any matrix * vector operation which yields a vector,
        // which should be the RHS
        for (col_jdx=0; col_jdx < n; ++col_jdx)
        {
            temp += A[row_idx][col_jdx] * x[col_jdx];
        }
        rhs[row_idx]=temp;
    }

    if(debug)
    {
        // Computed RHS
        printf("\nComputed RHS is:\n");
        fprintf(fp,"\nComputed RHS is:\n");
        vector_print(n, rhs);
    }
}
void  vector_print (int nr, double x[MAX_DIM])
{
    int row_idx;
  
    for (row_idx = 0; row_idx < nr; row_idx++) 
    {
    	printf ("%9.4f  \n", x[row_idx]);
    	fprintf (fp,"%9.4f  \n", x[row_idx]);
    }

    printf("\n");  // Insert a new line at the end
}