#define _CRT_SECURE_NO_WARNINGS
#include "sglazivanie.h"
#include <iostream>


void MD:: zapolnenie()
{
	FILE* file_ = fopen("data.txt", "r");
	char ddd = 0;
	m_ = 0;
	int yyy = 0;
	while (ddd != '\n') {
		char tt = ddd;
		if (fscanf(file_, "%c", &ddd) != 1)
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

	fclose(file_);
	FILE* file = fopen("data.txt", "r");
	int uu = 0;
	double p;
	while ((fscanf(file, "%lf", &p)) == 1)
		uu++;
	fclose(file);
	FILE* ffile = fopen("data.txt", "r");
	n_ = uu / m_;
	data_ = new double* [m_];
	for (int i = 0; i < m_; i++)
		data_[i] = new double [n_];
	for (int i = 0; i < n_; i++)
		for (int j = 0; j < m_; j++)
			fscanf(ffile, "%lf", &data_[j][i]);
	fclose(ffile);
}

double** MD::data() const 
{
	return data_;
}

int MD::m() const
{
	return m_;
}

int MD::n() const
{
	return n_;
}