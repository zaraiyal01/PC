#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) 
{
    int rank, size, data;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size < 2) 
    {
        if (rank == 0) printf("Run with at least 2 processes.\n");
        MPI_Finalize();
        return 0;
    }

    if (rank == 0) 
    {
        for (int i = 1; i < size; i++) 
        {
            data = 100 + i;
            MPI_Send(&data, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
            printf("Process 0 sent %d to Process %d\n", data, i);
        }
    } 
    else 
    {
        MPI_Recv(&data, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Process %d received %d from Process 0\n", rank, data);
    }
    MPI_Finalize();
    return 0;
}
