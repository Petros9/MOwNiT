#include <stdio.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_blas.h>
#include <gsl/gsl_matrix.h>
#include <stdlib.h>
#include <time.h>
#include <sys/times.h>
#include <fcntl.h>
#include <unistd.h>


double time_diff(clock_t first_clock, clock_t second_clock){
    double result = ((double)second_clock - first_clock) / sysconf (_SC_CLK_TCK);
    return result;
}

void print_time_diffrence(struct tms* begin, struct tms* end, FILE * raport, char* type, int size){
   char str[12];
   sprintf(str, "%d", size);  
   fprintf(raport, str);
   fprintf(raport,",");   
   char array[10];
   sprintf(array, "%f", time_diff(begin->tms_utime,end->tms_utime));
   fprintf(raport,array);
   fprintf(raport,",");
   fprintf(raport,type);
   fprintf(raport,"\n");
}

void vector_vector(int size){
    srand((unsigned int)times(NULL));
    gsl_vector* first = gsl_vector_alloc(size);
    gsl_vector* second = gsl_vector_alloc(size);

    for(int i = 0; i<size; i++)
    {
      gsl_vector_set (first, i, rand());
      gsl_vector_set (second, i, rand());      
    }
    double number;
    gsl_blas_ddot(first, second, &number);
}


void vector_matrix(int size)
{
    srand((unsigned int)times(NULL));
    int dim = rand()%10 +1;
    gsl_vector* vector_a = gsl_vector_alloc(size);
    gsl_matrix* matrix = gsl_matrix_alloc(size,size);
    gsl_vector* vector_b = gsl_vector_alloc(size);
    int random = rand()%10;
    for(int i = 0; i<size; i++)
    {
      gsl_vector_set (vector_a, i, random);
      gsl_vector_set (vector_b, i, random);
      for(int j = 0; j<size; j++)
      {
        gsl_matrix_set(matrix, j, i, random);
      }
      
    }
    int i = 0;
    double number;
    gsl_blas_dgemv(CblasNoTrans, 1.0, matrix, vector_a, 0.0, vector_b);
    /*
    lotkin_a = gsl_matrix_alloc(DIM, DIM);
    frank_a = gsl_matrix_alloc(DIM, DIM);
    x = gsl_vector_alloc(DIM);
    lotkin_b = gsl_vector_alloc(DIM);
 
    /* set x = [1 2 ... DIM] 
    for(i = 0; i < DIM; i++)
        gsl_vector_set(x, i, (double)i);
 
    /* set Lotkin matrix              
    /* a_ij = 1 (i = 1) or 1/(i+j-1) (i != 1) 
    for(i = 0; i < DIM; i++)
        gsl_matrix_set(lotkin_a, 0, i, 1.0);
    for(i = 1; i < DIM; i++)
        for(j = 0; j < DIM; j++)
            gsl_matrix_set(lotkin_a, i, j, 1.0 / (double)(i + j + 1));
 
 
    /* b = A * x 
    gsl_blas_dgemv(CblasNoTrans, 1.0, lotkin_a, x, 0.0, lotkin_b);*/
}
int main(void)
{
  
    FILE* raport = fopen("plik.txt","a+");
    struct tms *tms[140];
    int curent = 0;
    for (int i = 0; i < 140; i++){
        tms[i] = calloc(1, sizeof(struct tms *));
    }
    int current = 0; 
    /*
    for(int i = 5000000; i<10000000; i=i+1000000)
    {
      for(int j = 0; j<10; j++)
      { 
        times(tms[current]);
        vector_vector(i);
        times(tms[current+1]);
        print_time_diffrence(tms[current], tms[current+1], raport, "V",i);
        current = current+2;        
      }
    }
    */
      for(int i = 1000; i<6000; i=i+1000)
      {
          for(int j = 0; j<10; j++)
          {
            times(tms[current]);
            vector_matrix(i);
            times(tms[current+1]);
            print_time_diffrence(tms[current], tms[current+1], raport, "M",i);
            current +=2;
          }
    }
    fclose(raport);
}