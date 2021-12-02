#include <stdio.h> 
#include "elapsed_time.h"
#include "000000.h"

#define min_n       10
#define max_n       57
#define n_sums      20
#define n_problems  (max_n - min_n + 1)

int Bf_Iter(int n, integer_t *p, integer_t desired_sum){

    int comb = 0;
    integer_t test_sum;

    for(comb;comb<(1<<n);comb++){
        test_sum =0;

        for(int bit=0; bit<n ;bit++){
            int mask = (1<<bit);
            if((comb & mask)!=0){test_sum += p[bit];}
        }   

        if(test_sum == desired_sum){break;}
    }

    return comb;
    
}


int Bf_recur(int n, integer_t *p, integer_t desired_sum,int i,int current_sum,int current_comb){
    if (p[i] == p[n-1]) {
        if (current_sum + 1 * p[i] == desired_sum){   
            //change combination here
            return current_comb;
        }
        return current_comb + 0 * p[i];
    }

    if (current_sum + 0 * p[i]  == desired_sum){
        return current_comb;
    }
/*     else if (current_sum + 1 * p[i]  == desired_sum){
        return current_comb * ;
    } */

}

int print_all_sums_recursive(unsigned int n,unsigned int m,integer_t *p,double sum,unsigned long mask,integer_t desired_sum)
{
    if(m == n)
    { // nothing more to do; print sum
        unsigned int i,j;
        if (sum == desired_sum){
            printf("\n %lu \n",mask);
            return mask;
            
        }
    }
    else
    {
        print_all_sums_recursive(n,m + 1u,p,sum ,mask ,desired_sum); // do not use a[m]
        print_all_sums_recursive(n,m + 1u,p,sum + p[m],mask | (1ul << m),desired_sum); // use a[m]
    }
}



char *Converter(int n,int x, char *sol){
    for(int bit=0; bit<n ;bit++){
        int mask = (1<<bit);   
        if((x & mask)!=0){ sol[bit]='1';}else{ sol[bit]='0';}
    }
    sol[n]='\0';

    return sol;
}

int main(void)
{           
    /* Setting up file */
    FILE *fp = NULL;
	
	remove("data.log");    
    /* Open for the first time the file provided as argument */
    fp = fopen("data.log", "a");


    
    printf("\n");
    printf("Program configuration:\n");
    printf("  min_n ....... %d\n",min_n);
    printf("  max_n ....... %d\n",max_n);
    printf("  n_sums ...... %d\n",n_sums);
    printf("  n_problems .. %d\n",n_problems);
    printf("  integer_t ... %d bits\n",8 * (int)sizeof(integer_t));
    printf("\n");
     

   // start looping for n's
   /*  for(int i = 0;i < 15;i++)
    {
        printf("--------------------------- \n");
        
        // get n
        int n = all_subset_sum_problems[i].n;  
        printf("n =  %i\n\n",n);
        // get p and sums
        integer_t *p = all_subset_sum_problems[i].p;    
        integer_t *sums = all_subset_sum_problems[i].sums;    

        //create space to store results
        char comb_bin[n+1];

        
        double dt = 0;   
        // loop for sums
        for(int j = 0;j < n_sums;j++)
        {   
            integer_t sum = all_subset_sum_problems[i].sums[j];

            // run function and take time 
            double tmp_dt = cpu_time();   
            int comb = Bf_Iter(n, p, sum);
            tmp_dt = cpu_time() - tmp_dt;
            dt += tmp_dt;

            // print results
            printf("%d,  %lld -> %s\n", j ,sum, Converter(n, comb, comb_bin));
        }

        // store times 
        fprintf(fp,"%i %f \n",n, dt);

    }   */

     for(int i = 0;i < 15;i++)
    {
        printf("--------------------------- \n");
 
        // get n
        int n = all_subset_sum_problems[i].n;    
        char comb_bin[n+1];
        printf("n =  %i\n\n",n);
        // get p and sums
        integer_t *p = all_subset_sum_problems[i].p;    
        integer_t *sums = all_subset_sum_problems[i].sums; 
        
        for(int j = 0;j < n_sums;j++){   
            integer_t sum = all_subset_sum_problems[i].sums[j];
            int combination = print_all_sums_recursive(n,0, p,0,0,sum);
            printf("\nsoma = %llu --- solution = %s ", sum ,Converter(n, combination, comb_bin));

        }

    } 
    return 0;

    
    
}
