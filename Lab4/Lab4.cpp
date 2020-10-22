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
struct stack {
	int elem[SIZE];
	int top;
};
void init(struct stack* stk) {
	stk->top = 0;
}
void push(struct stack* stk, int a) {
	if (stk->top < SIZE) {
		stk->elem[stk->top] = a;
		stk->top++;
	}
	else
		printf("Стек полон, количество элементов: %d !\n", stk->top);
}
int pop(struct stack* stk) {
	int elem;
	if ((stk->top) > 0)
	{
		stk->top--;
		elem = stk->elem[stk->top];
		return elem;
	}
	else
	{
		printf("Стек пуст!\n");
		return 0;
	}
}
void DFSonStack(struct stack* stk, int v, int* G, int n, int* num) {
	int i=0;
	num[v] = 1;
	printf("%d\t", v + 1);
	push(stk, v);
	push(stk, v);
	while (stk->top != 0 ) {
		if (i == n) { v = pop(stk); }
		for (i = 0; i < n; i++) {
			if (G[v * n + i] == 1 && num[i] == 0) {
				num[i] = 1;
				printf("%d\t", i + 1);
				if(stk->top != SIZE)
				push(stk, i);
				v = i;
				break;
			}
		}
		
		
	}
}

typedef struct Node {
	int value;
	struct Node* next;
}Spisok;
Spisok* create_V(int name)
{
	// Выделение памяти под корень списка
	Spisok* tmp = (Spisok*)malloc(sizeof(Spisok));
	// Присваивание имя вершине
	tmp->value = name;
	// Присваивание указателю на следующий элемент значения NULL
	tmp->next = NULL;
	return(tmp);
}
void add_element_end(int data, Spisok* head)
{
	// Выделение памяти под корень списка
	Spisok* tmp = (Spisok*)malloc(sizeof(Spisok));
	// Присваивание значения узлу
	tmp->value = data;
	// Присваивание указателю на следующий элемент значения NULL
	tmp->next = NULL;
	// Присваивание новому указателю указателя head. 
	// Присваивание выполняется для того, чтобы не потерять указатель на «голову» списка
	Spisok* p = head;
	// Сдвиг указателя p в самый конец первоначального списка
	while (p->next != NULL)
		p = p->next;
	// Присваивание указателю p -> next значения указателя tmp (созданный новый узел)
	p->next = tmp;
}
void print(Spisok* head) {
	Spisok* v = head;
	if (v != NULL) {
		printf("%d:  ", v->value + 1);
		v = v->next;
	}
	while (v != NULL)
	{
		// Вывод значения узла
		printf("%d ", v->value + 1);
		// Сдвиг указателя к следующему узлу
		v = v->next;
	}
}
void graf_iz_matrix(int(&Matrix)[SIZE][SIZE],Spisok* G_S[SIZE]) {
	for (int i = 0; i < SIZE; i++) {
		Node* tmp = create_V(i);
		for (int j = 0; j < SIZE; j++) {
			if (Matrix[i][j] == 1)
				add_element_end(j, tmp);
		}
		G_S[i] = tmp;
	}
	for (int i = 0; i < SIZE; i++) {
		print(G_S[i]);
		printf("\n");
	}
	printf("\n");
}

void DFSsp(Spisok* (&P)[SIZE], int ver,int* num) {
	num[ver] = 1;
	printf("%d\t", ver + 1);
	Spisok* v = P[ver];
	v = v->next;
	while (v != NULL) {
		if (num[v->value] == 0) {
			DFSsp(P, v->value, &num[0]);
		}
		v = v->next;
	}
}

int main()
{
	setlocale(LC_ALL, "Rus");
	Spisok* G_S1[SIZE];
	struct stack* stk;
	stk = (struct stack*)malloc(sizeof(struct stack));
	init(stk);
	int G[SIZE][SIZE], num[SIZE], v,i=0;
	rand_Zap(&G[0][0], SIZE);
	print_G(&G[0][0], SIZE);
	/*_________________________________________________*/
	for (int i = 0; i < SIZE; i++) {
		num[i] = 0;
	}
	printf("	введите вершину для начала обхода\n");
	scanf("%d", &v);
	while ((v < 1) || (v > SIZE)) {
		printf("Ошибка!!! введите занаво\n");
		scanf("%d", &v);
	}
	printf("\n");
	v--;
	printf("	Результат с рекурсией\n");
	DFS(v, &G[0][0], SIZE, &num[0]);
	printf("\n\n");
	/*_________________________________________________*/
	for (int i = 0; i < SIZE; i++) {
		num[i] = 0;
	}
	printf("	введите вершину для начала обхода\n");
	 
	scanf("%d", &v);
	while ((v < 1) || (v > SIZE)) {
		printf("Ошибка!!! введите занаво\n");
		scanf("%d", &v);
	}
	printf("\n");
	v--;
	printf("	Результат без рекурсии\n");
	DFSonStack(stk, v, &G[0][0], SIZE, &num[0]);
	printf("\n\n");
	/*_________________________________________________*/
	printf("\n	представление графа в виде списка\n");
	graf_iz_matrix(G, G_S1);
	for (int i = 0; i < SIZE; i++) {
		num[i] = 0;
	}
	printf("	введите вершину для начала обхода\n");
	scanf("%d", &v);
	while ((v < 1) || (v > SIZE)) {
		printf("Ошибка!!! введите занаво\n");
		scanf("%d", &v);
	}
	printf("\n");
	v--;
	printf("	Результат обхода списков\n");
	DFSsp(G_S1,v, &num[0]);
}
