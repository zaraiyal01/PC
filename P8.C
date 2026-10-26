#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int rank, size, data[] = {1, 2, 3, 4}, local, result[4];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    MPI_Scatter(data, 1, MPI_INT, &local, 1, MPI_INT, 0, MPI_COMM_WORLD);

    printf("Process %d received %d\n", rank, local);
    local *= local;

    MPI_Gather(&local, 1, MPI_INT, result, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0) 
    {
        printf("Result: ");
        for (int i = 0; i < size; i++)
            printf("%d ", result[i]);
        printf("\n");
    }

    MPI_Finalize();
    return 0;
}
