#include <iostream>
#include <omp.h>

long double getPiWithNLenth(const int n)
{
	long double sum = 0;

#pragma omp parallel for reduction(+ : sum)
	for (int i = 0; i < n; i++)
	{
		long double x = (i + 0.5) / n;
		sum += 4 / (1 + x * x);
	}

	return sum / n;
}

int main()
{
	int n;
	printf("N = ");
	scanf("%d", &n);

	double start = omp_get_wtime();
	auto pi = getPiWithNLenth(n);
	double end = omp_get_wtime();

	printf("PI = %.15Lf, elipsed time = %0.6lf\n", pi, end - start);
	return 0;
}