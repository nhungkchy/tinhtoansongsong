#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>
#include <unistd.h>
#define MAX 100000;

// double LiToDouble(LARGE_INTEGER x)
// {
// 	double result = ((double)x.HighPart) * 4.294967296E9 + (double)((x).LowPart);
// 	return result;
// }

double GetTime()
{
	// LARGE_INTEGER lpFrequency, lpPerfomanceCount;
	// QueryPerformanceFrequency(&lpFrequency);
	// QueryPerformanceCounter(&lpPerfomanceCount);
	// return LiToDouble(lpPerfomanceCount) / LiToDouble(lpFrequency);
	struct timespec now;
  	clock_gettime(CLOCK_MONOTONIC, &now);
  	return now.tv_sec + now.tv_nsec / 1000000000.0;
}

void InputMatrix(double** Matrix, int RowCount, int ColCount)
{
	srand(unsigned(clock()));
	for (int i=0; i<RowCount; i++)
	{
		for (int j=0; j<ColCount; j++)
		{
			Matrix[i][j] = rand() % MAX;
		}
	}
}

void PrintMatrix(double** Matrix, int RowCount, int ColCount)
{
	printf("\nMatrix size is: %dx%d", RowCount, ColCount);
	printf("\nMatrix: \n");
	for (int i=0; i<RowCount; i++)
	{
		for(int j=0; j<ColCount; j++)
		{
			printf("%7.4lf\t", Matrix[i][j]);
		}
		printf("\n");
	}
}

void Paralell_MinForEachRow(double** Matrix, double* MinInEachRow, int RowCount, int ColCount)
{
    int i, j;
	for (i=0; i<RowCount; i++)
	{
		double min = Matrix[i][0];
		for (j=0; j<ColCount; j++)
		{
			if (Matrix[i][j] < min)
			{
				min = Matrix[i][j];
			}
		}
		MinInEachRow[i] = min;
	}
}

void PrintMinInEachRow(double* MinInEachRow, int RowCount)
{
	printf("\nMin in each row: \n");
	for (int i=0; i<RowCount; i++)
	{
		printf("%7.4lf\n", MinInEachRow[i]);
	}
}

void MaxOfMinInEachRow(double* MinInEachRow, int RowCount)
{
	double max = MinInEachRow[0];
	for (int i=0; i<RowCount; i++)
	{
		if (MinInEachRow[i] > max)
		{
			max = MinInEachRow[i];
		}
	}
	printf("\nMax of min in each row: %7.4lf\n", max);
}

int main()
{
	int RowCount, ColCount, NumThreads;
	double** Matrix = NULL;
	double* MinInEachRow = NULL;
	// double Duration;
	double Start, Duration, Finish;
	do {
		printf("\nInput the row:  ");
		scanf("%d", &RowCount);
		if (RowCount <= 0)
			printf("\nInput the row must be greater than 0!\n");
	} while (RowCount <= 0);
	
	do {
		printf("\nInput the column:  ");
		scanf("%d", &ColCount);
		if (ColCount <= 0)
			printf("\nInput the column must be greater than 0!\n");
	} while (ColCount <= 0);

	Matrix = (double **)malloc(RowCount * sizeof(int *));
	for (int i =0; i<RowCount; i++)
	{
		Matrix[i] = (double *)malloc(ColCount * sizeof(int *));
	}
	MinInEachRow = (double *)malloc(RowCount * sizeof(int *));

    InputMatrix(Matrix, RowCount, ColCount);
	//PrintMatrix(Matrix, RowCount, ColCount);
	Start = GetTime();
	Paralell_MinForEachRow(Matrix, MinInEachRow, RowCount, ColCount);
	MaxOfMinInEachRow(MinInEachRow, RowCount);
	Finish = GetTime();
	Duration = Finish - Start;

	printf("\nTime of execution: %lf\n", Duration);
    
	return 0;
}