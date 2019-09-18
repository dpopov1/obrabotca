#define _CRT_SECURE_NO_WARNINGS
#include "sglazivanie.h"
#include <iostream>

void MSD:: out() const
{
	FILE* file = fopen("out.txt", "w");
	double** a = mcm.get_mcm();
	int nmcm = mcm.get_nmcm();
	for (int j = 0; j < nmcm; j++)
		for (int i = 0; i < md.m(); i++)
		{
			fprintf(file, "%lf", a[i][j]);
			if (i != md.m() - 1)
				fprintf(file, " ");
			if (i == md.m() - 1)
				if(j!=nmcm-1)
				fprintf(file, "\n");
		}
	for (int i = 0; i < md.m(); i++)
		delete[] a[i];
	delete[] a;
	fclose(file);
}

bool MSD::construction()
{
	mcm.razb();
	if (mcm.get_razb() == 0)
		return 0;
	md.zapolnenie();
	mcm.obrabotca(md);
	return 1;
}

void sglazivanie()
{
	MSD a;
	if(a.construction())
	a.out();
}