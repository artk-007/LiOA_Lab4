// Lab4.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#define _CRT_SECURE_NO_WARNINGS
#define SIZE 5
#include <time.h>
#include <locale.h>
#include <iostream>
void rand_Zap(int* Matrix, int n) {
	srand(time(NULL));
	printf("G\n");
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++) {
			if (i == j) {
				Matrix[i * n + j] = 0;
			}
			if (i < j) {
				Matrix[i * n + j] = rand() % 2;
				Matrix[j * n + i] = Matrix[i * n + j];
			}
		}
}
void print_G(int* Matrix, int n) {
	printf("  ");
	for (int i = 0; i < n; i++)
		printf("%3d", i + 1);
	printf("\n\n");
	for (int i = 0; i < n; i++) {
		printf("%2d", i + 1);
		for (int j = 0; j < n; j++) {

			printf("%3d", Matrix[i * n + j]);
		}
		printf("\n");
	}
	printf("\n");


}
void DFS(int v,int* G, int n, int* num) {
	num[v] = 1;
	printf("%d\t",v+1);
	for (int i = 0; i < n; i++) {
		if (G[v * n + i] == 1 && num[i] == 0)
			DFS(i, G, n, &num[0]);
	}
}
int main()
{
	int G[SIZE][SIZE], num[SIZE], v;
	rand_Zap(&G[0][0], SIZE);
	print_G(&G[0][0], SIZE);
	for (int i = 0; i < SIZE; i++) {
		num[i] = 0;
	}
	scanf("%d", &v);
	v--;
	DFS(v, &G[0][0], SIZE, &num[0]);

}
