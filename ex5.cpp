#include <iostream>
#include <omp.h>

int *initArrayWithRandomValues(int size);
void sort(int *array, int size);

int main()
{

	int size, *array;
	printf("Enter array size: ");
	scanf("%d", &size);

	array = initArrayWithRandomValues(size);
	double start = omp_get_wtime();
	sort(array, size);
	double end = omp_get_wtime();

	for (int i = 0; i < size; i++)
		printf("%d\n", array[i]);

	printf("elipsed time: %.6lf\n", end - start);
	return 0;
}

int *initArrayWithRandomValues(int size)
{
	int *array = new int[size];
	srand(time(nullptr));
	for (int i = 0; i < size; i++)
	{
		array[i] = rand() % 10000;
	}
	return array;
}

void sort(int *array, int size)
{
	for (int i = size; i > 0; i--)
	{
#pragma omp parallel for
		for (int j = 0; j < i; j++)
		{
			if (array[j] > array[j + 1])
			// #pragma omp critical
			{
				int buf = array[j];
				array[j] = array[j + 1];
				array[j + 1] = buf;
			}
		}
	}
}