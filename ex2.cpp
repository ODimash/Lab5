#include <iostream>
#include <omp.h>

static int **multiplyMatrix(int **a, int **b, int matrixSize);
static int **createMatrix(int matrixSize);
static void displayMatrix(int **matrix, int size);

int main()
{
	int matrixSize, **a, **b;

	printf("Enter the matrix size: ");
	scanf("%d", &matrixSize);

	a = createMatrix(matrixSize);
	b = createMatrix(matrixSize);

	printf("Enter elements of matrix A:\n");
	for (int i = 0; i < matrixSize; i++)
		for (int j = 0; j < matrixSize; j++)
			scanf("%d", &a[i][j]);

	printf("Enter elements of matrix B:\n");
	for (int i = 0; i < matrixSize; i++)
		for (int j = 0; j < matrixSize; j++)
			scanf("%d", &b[i][j]);

	double start = omp_get_wtime();
	int **c = multiplyMatrix(a, b, matrixSize);
	double end = omp_get_wtime();

	printf("Result matrix:\n");
	displayMatrix(c, matrixSize);

	printf("Execution time: %.6f seconds\n", end - start);

	return 0;
}

int **createMatrix(int matrixSize)
{
	int **c = new int *[matrixSize];
	for (int i = 0; i < matrixSize; i++)
		c[i] = new int[matrixSize];
	return c;
}

int **multiplyMatrix(int **a, int **b, int matrixSize)
{
	int **c = createMatrix(matrixSize);

#pragma omp parallel for
	for (int it = 0; it < matrixSize * matrixSize; it++)
	{
		int i = it / matrixSize;
		int j = it % matrixSize;

		int sum = 0;
		for (int k = 0; k < matrixSize; k++)
		{
			{
				sum += a[i][k] * b[k][j];
			}
		}
		c[i][j] = sum;
	}

	return c;
}

void displayMatrix(int **matrix, int size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
			printf("%d ", matrix[i][j]);
		printf("\n");
	}
}
