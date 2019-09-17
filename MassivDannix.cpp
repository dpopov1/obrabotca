#define _CRT_SECURE_NO_WARNINGS
#include "sglazivanie.h"
#include <iostream>

using namespace std;
void MD:: zapolnenie()
{
	cout << "vvedite colvo massivov dannix" << endl;
	cin >> m_;
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