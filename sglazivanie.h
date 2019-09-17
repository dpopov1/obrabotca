#pragma once

class MD;
class MCM {
public:
	void obrabotca(MD);
	void razb();
	double** get_mcm() const;
	void in_nmcm(const int);
	int get_nmcm() const;
private:
	double** mcm;
	int razb_; 
	int nmcm;
};

class MD {
public:
	void zapolnenie();
	double** data() const;
	int m() const;
	int n() const;
private:
	int nmcm;
	double **data_;
	int m_, n_;
};

class MSD {
public:
	void construction();
	void out() const;
private:
	MD md;
	MCM mcm;
};