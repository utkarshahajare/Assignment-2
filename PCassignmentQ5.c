/*
Write an MPI program to compute the product of two vectors i.e.,

V^T*V

. Input: Size of the vector. Output: Scalar value (Print only once).
*/
#include <mpi.h>
#include <stdio.h>
#include <time.h>



int main(int argc, char** argv) {
    // Initialize the MPI environment
    
    
    MPI_Init(&argc, &argv);
//printf("%d,%c",argc,** argv);


    // Get the number of processes
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // Get the rank of the process
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    // Get the name of the processor
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int name_len;
    MPI_Get_processor_name(processor_name, &name_len);
    
    clock_t start, end;
     double cpu_time_used;
    
    start = clock();
    
    int n=atoi(argv[1]);
    int elements=n/world_size;
    int data[elements],i,j;
	
           
           int start1=(n/world_size)*world_rank;
		  // int end1=(n/world_size)*(world_rank+1);
		   int local_sum;
		   
		   //initialzing array
		   
		   for( j=0;j<elements;j++)
	{
	data[j]=start1;//can call randomno function here,but keeping index value for validation check of result
	start1++;
	}
	
	
		   
		   for( i=0;i<elements;i++)
		   {
				local_sum +=data[i]*data[i];//inner product
		   }
 printf("local_sum %d, rank %d out of %d processors ",
           local_sum, world_rank, world_size);
		   
		   int total_sum;
		   
		   end = clock();
     cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
     
     printf("Time:%f secs\n",cpu_time_used);
		   
		   MPI_Reduce(&local_sum,&total_sum,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);
		   
		   if(world_rank==0)
		   {
				printf("total_sum %d\n",total_sum);
		   }
		   
	 	   
    // Finalize the MPI environment.
    MPI_Finalize();
}