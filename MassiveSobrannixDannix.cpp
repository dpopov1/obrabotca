#define _CRT_SECURE_NO_WARNINGS//
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
			fprintf(file, "%lf ", a[i][j]);
			if (i == md.m() - 1)
				fprintf(file, "\n");
		}
	fclose(file);
}

void MSD::construction()
{
	md.zapolnenie();
	mcm.razb();
	mcm.obrabotca(md);
}