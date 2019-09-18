#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "sortirovka.h"

char* get_mas(int &i, bool l)
{
	FILE* f;
	if (l)
		f = fopen("out.txt", "r");
	else
		f = fopen("data.txt", "r");
	char r;
	char* a;
	char* b = new char;
	i = 0;
	for (i; fscanf(f, "%c", &r) == 1; i++)
	{
		a = new char[i + 1];
		for (int j = 0; j < i; j++)
			a[j] = b[j];
		a[i] = r;
		delete[] b;
		b = new char[i + 1];
		for (int j = 0; j <= i; j++)
			b[j] = a[j];
		delete[] a;
	}
	fclose(f);
	return b;
}

void sort_tz(char* a, char bilo, char stalo, int n)
{
	for (int i = 0; i < n; i++)
		if (a[i] == bilo)
			a[i] = stalo;
}

void fprint(char* a, int n, bool l)
{
	FILE* f;
	if (l)
		f = fopen("out.txt", "w");
	else
		f = fopen("data.txt", "w");
	for (int i = 0; i < n; i++)
		fprintf(f, "%c", a[i]);
	fclose(f);
}

void points(char b, char c, bool l)
{
	int a;
	char* t = get_mas(a,l);
	sort_tz(t,b,c, a);
	fprint(t, a, l);
	delete[] t;
}