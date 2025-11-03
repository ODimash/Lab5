#include <iostream>
#include <omp.h>

long double getPiWithNLenth(const unsigned long n)
{
	long double sum = 0;

#pragma omp parallel for
	for (int i = 0; i < n; i++)
	{
		long double x = (i + 0.5) / n;
		long double v = 4 / (1 + x * x);
#pragma omp critical
		{
			sum += v;
		}
	}

	return sum / n;
}

int main()
{
	unsigned long n;
	printf("N = ");
	scanf("%ld", &n);

	double start = omp_get_wtime();
	auto pi = getPiWithNLenth(n);
	double end = omp_get_wtime();

	printf("PI = %.15Lf, elipsed time = %0.6lf\n", pi, end - start);
	return 0;
}