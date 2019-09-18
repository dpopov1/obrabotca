#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "sortirovka.h"

typedef struct {
	char* mas;
	int size;
} element;

int get_m(bool l)
{
	FILE* f;
	if (l)
		f = fopen("out.txt", "r");
	else
		f = fopen("data.txt", "r");
	char ddd = 0;
	int m_ = 0;
	int yyy = 0;
	while (ddd != '\n') {
		char tt = ddd;
		if (fscanf(f, "%c", &ddd) != 1)
		{
			m_++;
			break;
		}
		yyy++;
		if (ddd == ' '&&yyy != 0)
		{
			if (tt != ' ')
				m_++;
		}
		else {
			if (ddd == '\n'&& tt != ' ')
				m_++;
		}
	}
	fclose(f);
	return m_;
}

int get_n(int m, bool l)
{
	FILE* f;
	if (l)
		f = fopen("out.txt", "r");
	else
		f = fopen("data.txt", "r");
	int uu = 0;
	double p;
	while ((fscanf(f, "%lf", &p)) == 1)
		uu++;
	fclose(f);
	return uu / m;
}

element get_element(FILE* f)//////vihod
{
	char r;
	char* a;
	char* b = new char;
	int i = 0;
	for (i; fscanf(f, "%c", &r) == 1; i++)
	{
		if (i == 0 && (r == ' ' || r == '\n'))
			i--;
		else {
			if (i != 0 && (r == ' ' || r == '\n'))
				break;
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
	}
	element h;
	h.size = i;
	h.mas = b;
	return h;
}

int* get_max(element** data, int m, int n)
{
	int* max = new int[m];
	for (int i = 0; i < m; i++)
		max[i] = data[i][0].size;
	for (int i = 0; i < m; i++)
		for (int j = 1; j < n; j++)
			if (data[i][j].size > max[i])
				max[i] = data[i][j].size;
	return max;
}

void sort_(element** data, int m, int n)
{
	int* max = get_max(data, m, n);
	for(int i =0;i<m;i++)
		for (int j = 0; j < n; j++)
			if (data[i][j].size < max[i])
			{
				char* a = new char[max[i]];
				for (int k = 0; k < data[i][j].size; k++)
					a[k] = data[i][j].mas[k];
				for (int k = data[i][j].size; k < max[i]; k++)
					a[k] = ' ';
				delete[] data[i][j].mas;
				data[i][j].mas = a;
				data[i][j].size = max[i];
			}
	delete[] max;
}

void perevod_v_double(int m_, int n_, bool l)
{
	if (!l) {
		FILE* ffile = fopen("data.txt", "r");
		double** data_ = new double*[m_];
		for (int i = 0; i < m_; i++)
			data_[i] = new double[n_];
		for (int i = 0; i < n_; i++)
			for (int j = 0; j < m_; j++)
				fscanf(ffile, "%lf", &data_[j][i]);
		fclose(ffile);
		FILE* file = fopen("data.txt", "w");
		for (int j = 0; j < n_; j++)
			for (int i = 0; i < m_; i++)
			{
				fprintf(file, "%lf", data_[i][j]);
				if (i != m_ - 1)
					fprintf(file, " ");
				if (i == m_ - 1)
					if (j != n_ - 1)
						fprintf(file, "\n");
			}
		for (int i = 0; i < m_; i++)
			delete[] data_[i];
		delete[] data_;
		fclose(file);
	}
}

void fprint(element** data, int m, int n, bool l)
{
	FILE* f;
	if (l)
		f = fopen("out.txt", "w");
	else
		f = fopen("data.txt", "w");
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			for (int k = 0; k < data[j][i].size; k++)
				fprintf(f, "%c", data[j][i].mas[k]);
			if (j != m - 1)
				fprintf(f, " ");
		}
		if (i != n - 1)
			fprintf(f, "\n");
	}
	fclose(f);
}

element** get_data(int m, int n, bool l)
{
	FILE* f;
	if (l)
		f = fopen("out.txt", "r");
	else
		f = fopen("data.txt", "r");
	element** data = new element*[m];
	for (int i = 0; i < m; i++)
		data[i] = new element[n];
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			data[j][i] = get_element(f);
	fclose(f);
	return data;
}

void viravnivanie(bool l)
{
	int n, m;
	m = get_m(l);
	n = get_n(m, l);
	perevod_v_double(m, n, l);
	element** data = get_data(m,n,l);
	sort_(data, m, n);
	fprint(data, m, n,l);
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
			delete[] data[i][j].mas;
		delete[] data[i];
	}
	delete[] data;
}