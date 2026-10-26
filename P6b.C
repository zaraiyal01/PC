#include <stdio.h>
#include <mpi.h>
#define SIZE 100000

int main(int argc, char *argv[]) 
{
    int rank, data[SIZE], recv[SIZE];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    for (int i = 0; i < SIZE; i++) 
        data[i] = rank;

    if (rank == 0) 
    {
        MPI_Send(data, SIZE, MPI_INT, 1, 0, MPI_COMM_WORLD);
        printf("Process 0 sent: %d\n", data[0]);
        MPI_Recv(recv, SIZE, MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Process 0 received: %d\n", recv[0]);
    } 
    else if (rank == 1) 
    {
        MPI_Recv(recv, SIZE, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Process 1 received: %d\n", recv[0]);
        MPI_Send(data, SIZE, MPI_INT, 0, 0, MPI_COMM_WORLD);
        printf("Process 1 sent: %d\n", data[0]);
    }
    MPI_Finalize();
    return 0;
}
