#include <iostream>
#include <omp.h>

int main()
{

	int N;
	printf("N = ");
	scanf("%d", &N);

	long sum = 0;

	double start = omp_get_wtime();
#pragma omp parallel for
	for (int i = 1; i <= N; i++)
	{
#pragma omp atomic
		sum += i;
	}
	double end = omp_get_wtime();

	printf("Sum = %ld, elipsed time = %.6lf\n", sum, end - start);

	return 0;
}