#include "sglazivanie.h"
#include <iostream>
using namespace std;

double min(double* a, int n)
{
	double min_ = a[0];
	for (int i = 0; i < n; i++)
		if (a[i] < min_)
			min_ = a[i];
	return min_;
}

double max(double* a, int n)
{
	double max_ = a[0];
	for (int i = 0; i < n; i++)
		if (a[i] > max_)
			max_ = a[i];
	return max_;
}

double dlina_razb(double* a, int n, int N_razb)
{
	return (max(a, n) - min(a, n))/N_razb;
}

double glob_center(double*a, int n)
{
	double p=0;
	for (int i = 0; i < n; i++)
		p +=a[i];
	return p / n;
}

int kolvo_mas_cm(int n, double dl_razb, double** data, int k)
{
	int p = 0;
	int nmcm = 0;
	for (int i = 0; i < n; i++)
	{
		int o = p;
		double yy = fabs(data[k][i] - data[k][p]);
		if (fabs(data[k][i] - data[k][p]) > dl_razb)
		{
			p = i;
			nmcm++;
			if (o == p)
				p++;
		}
	}
	nmcm++;
	return nmcm;
}

int* kolvo_v_mas_CM(int nmcm, double** data, int k, int n, int dl_razb)
{
	int* NmasCM = new int [nmcm];
	int p = 0;
	int j = 0;
	for (int i = 0; i < nmcm; i++)
		for (j; j<n; j++)
		{
			int o = p;
			if (fabs(data[k][j] - data[k][p]) > dl_razb)
			{
				p = j;
				if (o == p)
					p++;
				NmasCM[i] = p - o;
				break;
			}
			else {
				if (i == nmcm - 1)
					NmasCM[i] = j-o+1;
			}
		}
	return NmasCM;
}

double* glavnCM(int* NmasCM, int nmcm, double** data, int k)
{
	double** tochki = new double*[nmcm];
	for (int i = 0; i < nmcm; i++)
		tochki[i] = new double[NmasCM[i]];
	int p = 0;
	for(int i = 0; i<nmcm;i++)
		for (int j = 0; j < NmasCM[i]; j++)
		{
			tochki[i][j] = data[k][p];
			p++;
		}
	double* CMgl = new double[nmcm];
	for(int i =0; i<nmcm; i++)
	CMgl[i] = glob_center(tochki[i], NmasCM[i]);
	for (int i = 0; i < nmcm; i++)
		delete[] tochki[i];
	delete[] tochki;
	return CMgl;
}

int polozenie(int x, int y, int* NmasCM)
{
	int p = 0;
	for (int i = 0; i < x; i++)
		p += NmasCM[i];
	return p + y;
}


double* pobochCM(double** data, int y, int* NmasCM, int nmcm) {
	
	double** pobochca = new double*[nmcm];
	for (int i = 0; i < nmcm; i++)
		pobochca[i] = new double [NmasCM[i]];
	for (int i = 0; i < nmcm; i++)
		for (int j = 0; j < NmasCM[i]; j++)
			pobochca[i][j] = data[y][polozenie(i, j, NmasCM)];
	double* CMpobochca = new double [nmcm];
	for (int i = 0; i < nmcm; i++)
		CMpobochca[i] = glob_center(pobochca[i], NmasCM[i]);
	for (int i = 0; i < nmcm; i++)
		delete[] pobochca[i];
	delete[] pobochca;
	return CMpobochca;
}



void MCM::in_nmcm(const int a)
{
	nmcm = a;
}

double** centr(MD dat, int N_razb, int &a) {
	int k = 0;
	int n = dat.n();
	int m = dat.m();
	double** data=dat.data();
	double dl_razb = dlina_razb(data[k], n, N_razb);
	int nmcm = kolvo_mas_cm(n, dl_razb, data, k);
	int* NmasCM = kolvo_v_mas_CM(nmcm, data, k, n, dl_razb);
	double* glCM = glavnCM(NmasCM, nmcm, data, k);
	double** center = new double*[m];
	center[0] = glCM;
	for (int i = 1; i < m; i++)
		center[i] = pobochCM(data, i, NmasCM, nmcm);
	delete[] NmasCM;
	for(int i =0;i<m;i++)
	delete[] data[i];
	delete[] data;
	a=nmcm;
	return center;
}

void MCM:: obrabotca(MD a)
{
	int nmcm__;
	mcm = centr(a, razb_, nmcm__);
	nmcm = nmcm__;
}

void MCM:: razb()
{
	cout << "vvedite kol-vo razbienii po x, vvedite 0, esli ne xotite delat razbienia" << endl;
	cin >> razb_;
}

double** MCM::get_mcm() const
{
	return mcm;
}

int MCM::get_nmcm() const
{
	return nmcm;
}

int MCM::get_razb() const
{
	return razb_;
}