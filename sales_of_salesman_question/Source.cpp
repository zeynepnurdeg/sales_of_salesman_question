#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define NUM_OF_DAYS 5

void readFromFile(FILE* inp, int** arr, int salesman) {
	int r = 0, c = 0, num;
	while (r != salesman && fscanf(inp, "%d", &num) != EOF)
	{
		arr[r][c] = num;
		c++;
		if (c == NUM_OF_DAYS) {
			r++;
			c = 0;
		}
	}
}

void displaySalesInfo(int** arr, int salesman) {
	int r, c;
	printf("\n      Weekly Sales Report\n");
	printf("*******************************\n");
	printf("         M    T    W    T    F\n");
	for (r = 0; r < salesman; r++) {
		printf("S-0%d: ", r + 1);
		for (c = 0; c < NUM_OF_DAYS; c++)
			printf("%5d", *(*(arr + r) + c));
		printf("\n");
	}
}

double findAvg(int** arr, int salesman) {
	double sum = 0;
	int r, c;
	for (r = 0; r < salesman; r++)
		for (c = 0; c < NUM_OF_DAYS; c++)
			sum += *(*(arr + r) + c);
	return (sum / (salesman * NUM_OF_DAYS));
}

void findSalesmanAvg(int** arr, int salesman, double avg) {
	double avgByPerson = 0;
	printf("Salesman info on whose sale amount is above avg: \n");
	for (int r = 0; r < salesman; r++) {
		for (int c = 0; c < NUM_OF_DAYS; c++)
			avgByPerson += *(*(arr + r) + c);
		avgByPerson = avgByPerson / NUM_OF_DAYS;
		if (avgByPerson > avg)
			printf("Salesman No: %d, Avg: %.2f TL\n", r + 1, avgByPerson);
		avgByPerson = 0;
	}
}

void findMaxSale(int** arr, int salesman) {
	int rMax, cMax, r, c, max = 10;
	for (r = 0; r < salesman; r++) {
		for (c = 0; c < NUM_OF_DAYS; c++)
			if (*(*(arr + r) + c) > max) {
				max = *(*(arr + r) + c);
				rMax = r;
				cMax = c;
			}
	}
	printf("\nThe salesman %d has the max sales amount, %d TL, on ", rMax + 1, max);
	switch (cMax) {
	case 0:
		printf("MONDAY\n"); break;
	case 1:
		printf("TUESDAY\n"); break;
	case 2:
		printf("WEDNESDAY\n"); break;
	case 3:
		printf("THURSDAY\n"); break;
	case 4:
		printf("FRIDAY\n"); break;
	}
}

int main(void)
{
	FILE* inp;
	inp = fopen("sales.txt", "r");
	if (inp == NULL)
		printf("Error");
	else {
		int n;
		do {
			printf("Enter the number of salesman: ");
			scanf("%d", &n);
		} while (n < 3 || n > 10);

		int** arr = (int**)malloc(n * sizeof(int*));
		for (int i = 0; i < n; i++) {
			arr[i] = (int*)malloc(NUM_OF_DAYS * sizeof(int));
		}

		readFromFile(inp, arr, n);
		displaySalesInfo(arr, n);
		double avg = findAvg(arr, n);
		printf("\nThe weekly sale average of the restaurant: %.2f TL\n", avg);
		printf("\n");
		findSalesmanAvg(arr, n, avg);
		findMaxSale(arr, n);

		fclose(inp);
		for (int i = 0; i < n; i++)
			free(arr[i]);
		free(arr);
	}
	return 0;
}