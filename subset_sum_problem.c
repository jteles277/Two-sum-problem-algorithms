//
// AED, November 2021
//
// Solution of the first practical assignement (subset sum problem)
//
// Place your student numbers and names here
//

#if __STDC_VERSION__ < 199901L
# error "This code must must be compiled in c99 mode or later (-std=c99)" // to handle the unsigned long long data type
#endif
#ifndef STUDENT_H_FILE
# define STUDENT_H_FILE "000000.h"
#endif


//
// include files
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "elapsed_time.h"
#include STUDENT_H_FILE

//Sorts

  void swap(integer_t *a, integer_t *b) {
    integer_t temp = *a;
    *a = *b;
    *b = temp;
  }

  //Bubble Sort
    void bubbleSort(integer_t arr[], int n)
    {
        // used just for the graphs and to show how effective heapSort is

      int i, j;
      int swapped;
      for (i = 0; i < n-1; i++)
      {
        swapped = 0;
        for (j = 0; j < n-i-1; j++)
        {
            if (arr[j] > arr[j+1]) 
            {
              swap(&arr[j], &arr[j+1]);
              swapped = 1;
            }
        }
    
        if (swapped == 0)
            break;
      }
    }
  //

  //Heap Sort
    void heapify(integer_t arr[], int n, int i) {
        // Find largest among root, left child and right child
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;
      
        if (left < n && arr[left] > arr[largest])
          largest = left;
      
        if (right < n && arr[right] > arr[largest])
          largest = right;
      
        // Swap and continue heapifying if root is not largest
        if (largest != i) {
          swap(&arr[i], &arr[largest]);
          heapify(arr, n, largest);
        }
    }
      

    void heapSort(integer_t arr[], int n) {
        // Build max heap
        for (int i = n / 2 - 1; i >= 0; i--)
          heapify(arr, n, i);
      
        // Heap sort
        for (int i = n - 1; i >= 0; i--) {
          swap(&arr[0], &arr[i]);
      
          // Heapify root element to get highest element at root again
          heapify(arr, i, 0);
        }
    }
  //
// 

//Algorithms

  // Brute Force Iterative Algorithm 
    int Bf_Iter(int n, integer_t *p, integer_t desired_sum){

      int comb = 0;
      integer_t test_sum;

      for(comb;comb<(1<<n);comb++){   // changes the combination
        
        test_sum =0;

        for(int bit=0; bit<n ;bit++){
          
          int mask = (1<<bit);
          if((comb & mask)!=0){test_sum += p[bit];}   
        }   

        if(test_sum == desired_sum){break;} // tests if the sum is equal to the desired sum 
      }

      return comb;
        
    }
  //

  // Brute Force Recursive Algorithm  
    int Bf_recur( unsigned int n,unsigned int m,integer_t *p,double sum, int comb,integer_t desired_sum){
        
      if(m == n){ // if is in last step of recursion
        
        if (sum == desired_sum){
          return comb;    // return combination different from 0 if found
                
        }
        else return 0;      // else returns 0
      }

        
      int result = Bf_recur(n,m + 1u,p,sum , comb ,desired_sum);  
      if (result == 0){         // if combination is 0 it means we must take another path          
    
        return Bf_recur(n,m + 1u,p,sum + p[m] ,comb+ pow(2,m),desired_sum);      
      }   

      return result;
    }
  //

  // Smart Brute Force Recursive Algorithm  
    integer_t Bf_recur_smart( unsigned int n,int m,integer_t *p,integer_t sum, integer_t comb,integer_t desired_sum)
    {  // this function run trougth the array from bigger to smaller and if the current_sum is bigger then the desired_sum we exit, saving lots of time

      if (sum == desired_sum){    // found the solucion so we return the combination
        return comb;
      }

      if(sum > desired_sum){ // if current sum > desired_sum this branch does not contain the solucion
        return 0;
      }

      if(m == -1) {               // if we reached the end of the array
        return 0 ;
      }

      integer_t power = (1ull);
      integer_t result = Bf_recur_smart(n,m-1,p,sum + p[m], comb + (power<<m),desired_sum);  
        
      if (result == 0)  {             // if combination is 0 it means we must take another path         
        return Bf_recur_smart(n,m-1,p,sum  ,comb,desired_sum);      
      }   
      return result;
    }
  //
  
  // Meet in the middle Algorithm
    //Create Array(x[]) composed by all the possible sums of a given Array(a[])
      void calcsubarray(integer_t a[], integer_t x[], int n, int c){

        integer_t s;
        for (int i=0; i<(1<<n); i++)
        {
          s = 0;
          for (int j=0; j<n; j++){
            if (i & (1<<j)){
              s += a[j+c];
            }    
          }

          if(s >= 0){
            x[i] = s;  
          }
        }
      } 
    //Algorithm itself
      int mitm(int n, integer_t *p, integer_t desired_sum){
    
        // Get sub-arrays sizes
        int size_X = 1<<(n/2);
        int size_Y = 1<<(n-n/2);
        
        // Allocate space for them
        integer_t *X = malloc(size_X*sizeof(integer_t));
        integer_t *Y = malloc(size_Y*sizeof(integer_t)); 

        // Create the sub arrays
        calcsubarray(p, X, n/2, 0);
        calcsubarray(p, Y, n-n/2, n/2);
        
        // Sort them
        heapSort(X, size_X);
        heapSort(Y, size_Y);
        
        /* Go through the array X from start to end, and through Y form end to start, testing if we get the desired sum from putting them together */
        int i= 0;
        int j= size_Y - 1;
        while(i< size_X && j >= 0){

          integer_t s = X[i]+Y[j]; 
          if(s == desired_sum ){ 
        
            free(X);    //freeing the space of the arrays
            free(Y);
            return 1;   // return 1 if its found
          }else if(s < desired_sum){
            i++;
          }else{
            j--;
          } 
        }

        // return 0 if is not found
        return 0;
      }
    //
  //

  // Faster Meet in the middle Algorithm (The difference being in the fact that this one sort the arrays while creating them)

    //Create a Sorted Array(x[]) composed by all the possible sums of a given Array(a[])
      void faster_calcsubarray(integer_t a[], integer_t x[], int n, int c){

        for (int i=0; i<n; i++)
        {

          integer_t i1 = (1<<n)-(1<<i);
          integer_t j1 = i1;
          integer_t k1 = (1<<n)-(2<<i);

          while(i1 < (1<<n)){

            if(x[i1] <= x[j1] + a[i+c]){
              x[k1++] = x[i1++];
            }else{
              x[k1++] = x[j1++] + a[i+c];   
            }
          }
          while(j1 < (1<<n)){
            x[j1++] += a[i+c];
          }
        }

      } 
    //Algorithm itself
      int faster_mitm(int n, integer_t *p, integer_t desired_sum){
      
        // Get sub-arrays sizes
        int size_X = 1<<(n/2);
        int size_Y = 1<<(n-n/2);
          
        // Allocate space for them
        integer_t *X = malloc(size_X*sizeof(integer_t));
        integer_t *Y = malloc(size_Y*sizeof(integer_t)); 

        for(int i=0;i<size_X;i++){
          X[i]=0;
        }  
        for(int i=0;i<size_Y;i++){
          Y[i]=0;
        } 
              
        // Create the sub arrays and Sort them
        faster_calcsubarray(p, X, n/2, 0);
        faster_calcsubarray(p, Y, n-n/2, n/2); 
          
        /* Go through the array X from start to end, and through Y form end to start, testing if we get the desired sum from putting them together */
        int i= 0;
        int j= size_Y - 1;
        while(i< size_X && j >= 0){
          integer_t s = X[i]+Y[j];
              
          if(s == desired_sum){ 
                  
            free(X);    //freeing the space of the arrays
            free(Y);                 
            return 1;   // return 1 if its found
          }else if(s < desired_sum){
            i++;
          }else{
            j--;
          }  
        }

        // return 0 if is not found
        return 0;
      }
    //
  //

//

//Converter (converts a decimal number to binary, used to get the commbinations)
  char *Converter(int n,integer_t x, char *sol){
    for(int bit=0; bit<n ;bit++){
        integer_t mask = (1ull<<bit);   
        if((x & mask)!=0){ sol[bit]='1';}else{ sol[bit]='0';}
    }
    sol[n]='\0';

    return sol;
  }
//


//
// main program
//

int main(void)
{
  fprintf(stderr,"Program configuration:\n");
  fprintf(stderr,"  min_n ....... %d\n",min_n);
  fprintf(stderr,"  max_n ....... %d\n",max_n);
  fprintf(stderr,"  n_sums ...... %d\n",n_sums);
  fprintf(stderr,"  n_problems .. %d\n",n_problems);
  fprintf(stderr,"  integer_t ... %d bits\n",8 * (int)sizeof(integer_t));
  
 
  /* Setting up file */
  FILE *fp_1 = NULL;
  FILE *fp_2 = NULL;
  FILE *fp_3 = NULL;
  FILE *fp_4 = NULL;
  FILE *fp_5 = NULL;
  FILE *fp_6 = NULL;
  FILE *fp_7 = NULL;
  FILE *fp_8 = NULL;
  FILE *fp_9 = NULL;
  FILE *fp_10 = NULL;
  fp_1 = fopen("data_1.log", "a");
  fp_2 = fopen("data_1_max.log", "a");
  fp_3 = fopen("data_2.log", "a");
  fp_4 = fopen("data_2_max.log", "a");
  fp_5 = fopen("data_3.log", "a");
  fp_6 = fopen("data_3_max.log", "a");
  fp_7 = fopen("data_4.log", "a");
  fp_8 = fopen("data_4_max.log", "a");
  fp_9 = fopen("data_5.log", "a");
  fp_10 = fopen("data_5_max.log", "a");
    
 

  // Loop for n's
  for(int i = 0;i < n_problems;i++){
  
    printf("--------------------------- \n");
                
    // get n and p
    int n = all_subset_sum_problems[i].n;  
    printf("n =  %i\n\n",n);
    integer_t *p = all_subset_sum_problems[i].p;     

    // Set up to get the combinations 
    char comb_bin[n+1];

    // Setting up time variables    
    double dt_bf_i = 0;  
    double dt_bf_i_max = 0;  
    double dt_bf_r = 0;
    double dt_bf_r_max = 0;
    double dt_bf_i_s = 0;
    double dt_bf_i_s_max = 0;
    double dt_mitm = 0;     
    double dt_mitm_max = 0;
    double dt_f_mitm = 0;     
    double dt_f_mitm_max = 0;

    // Loop for sum's
    for(int j = 0;j < n_sums;j++){
           
      integer_t sum = all_subset_sum_problems[i].sums[j];
      double tmp_dt;

        
        // Iterative
        tmp_dt = cpu_time();   
        int comb = Bf_Iter(n, p, sum);
        tmp_dt = cpu_time() - tmp_dt;
        if(tmp_dt > dt_bf_i_max){
          dt_bf_i_max = tmp_dt;
        }
        dt_bf_i += tmp_dt;


        // Recursive
        tmp_dt = cpu_time();   
        int comb_rec= Bf_recur(n,0, p,0,0,sum);
        tmp_dt = cpu_time() - tmp_dt;        
        if(tmp_dt > dt_bf_r_max){
          dt_bf_r_max = tmp_dt;
        }
        dt_bf_r += tmp_dt;


        // Recursive Smart
        tmp_dt = cpu_time();   
        integer_t comb_smart= Bf_recur_smart(n,n-1, p,0,0,sum);
        tmp_dt = cpu_time() - tmp_dt;
        if(tmp_dt > dt_bf_i_s_max){
          dt_bf_i_s_max = tmp_dt;
        }
        dt_bf_i_s += tmp_dt;
            
            
        // Meet in the middle
        tmp_dt = cpu_time();   
        int x= mitm(n, p, sum);
        tmp_dt = cpu_time() - tmp_dt;
        if(tmp_dt > dt_mitm_max){
          dt_mitm_max = tmp_dt;
        }
        dt_mitm += tmp_dt;

            
        // Fast Meet in the middle
        tmp_dt = cpu_time();   
        int y= faster_mitm(n, p, sum);
        tmp_dt = cpu_time() - tmp_dt;
        if(tmp_dt > dt_f_mitm_max){
          dt_f_mitm_max = tmp_dt;
        }
        dt_f_mitm += tmp_dt;


 
        // print results
        printf("-------------------------------------------------\n");
        printf("Brute force                   %d,  %lld || %i -> %s  \n", j ,sum,comb,   Converter(n, comb, comb_bin));
        printf("Brute force recursiva         %d,  %lld || %i -> %s  \n", j ,sum,comb_rec,   Converter(n, comb_rec, comb_bin));
        printf("Brute force recur smart       %d,  %lld || %lld -> %s  \n", j ,sum,comb_smart,   Converter(n, comb_smart, comb_bin));  
        printf("Meet in the middle            %d,  %lld || %i  \n", j ,sum, x);
        printf("Faster meet in the middle     %d,  %lld || %i  \n", j ,sum, y);
            
      }

      // store times (commented beacause we already took the data needed)
      /*
      fprintf(fp_1,"%i %f \n",n, dt_bf_i/20);
      fprintf(fp_2,"%i %f \n",n, dt_bf_i_max);
      fprintf(fp_3,"%i %f \n",n, dt_bf_r/20);
      fprintf(fp_4,"%i %f \n",n, dt_bf_r_max);
      fprintf(fp_5,"%i %f \n",n, dt_bf_i_s/20);
      fprintf(fp_6,"%i %f \n",n, dt_bf_i_s_max);
      fprintf(fp_7,"%i %f \n",n, dt_mitm/20);
      fprintf(fp_8,"%i %f \n",n, dt_mitm_max);
      fprintf(fp_9,"%i %f \n",n, dt_f_mitm/20);
      fprintf(fp_10,"%i %f \n",n, dt_f_mitm_max);
      */

    }     


   
  return 0;
}