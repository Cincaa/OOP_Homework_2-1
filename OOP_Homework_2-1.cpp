#include"pch.h"
#include <iostream>
using namespace std;
class Vector {
private:
	int dim;
	int *a;
public:
	Vector();
	Vector(int dim, int *a);
	Vector(const Vector &obj);
	~Vector();
	friend istream& operator >>(istream &i, Vector &obj);
	friend ostream& operator <<(ostream &i, const Vector &obj);
	Vector& operator =(const Vector &obj);

};

Vector::Vector() {
	dim = 0;
	a = NULL;
}

Vector::Vector(int dim, int *a) {
	this->dim = dim;
	this->a = a;
	this->a = new int[dim];
}

Vector::Vector(const Vector &obj) {
	dim = obj.dim;
	this->a = new int[dim];
	a = obj.a;
}

Vector::~Vector() {
	delete a;
	dim = 0;
}

Vector& Vector :: operator=(const Vector &obj) {
	this->dim = obj.dim;
	delete[] a;
	a = new int[dim];
	for (int i = 0; i < dim; i++)
		a[i] = obj.a[i];

	return *this;
}

istream& operator >>(istream &i, Vector &obj) {
	if (obj.a != NULL)
		delete[] obj.a;
	cout << "Dimensiunea este:\n";
	i >> obj.dim;
	obj.a = new int[obj.dim];
	
	cout << "Elementele sunt:\n";
	for (int it = 0; it < obj.dim; it++)
		i >> obj.a[it];
	cout << '\n';
	return i;
}

ostream& operator <<(ostream &o, const Vector &obj) {
	o << "Dimensiunea este: " << obj.dim << endl;
	o << "Elementele sunt:\n";
	for (int i = 0; i < obj.dim; i++)
		o << obj.a[i] << ' ';
	o << "\n\n";

	return o;
}
//--------------------------------------------------UTILITIES--------------------------------------------------
int determinant(int matrix[10][10], int n) {
	int det = 0;
	int submatrix[10][10];
	if (n == 2)
		return ((matrix[0][0] * matrix[1][1]) - (matrix[1][0] * matrix[0][1]));
	else {
		for (int x = 0; x < n; x++) {
			int subi = 0;
			for (int i = 1; i < n; i++) {
				int subj = 0;
				for (int j = 0; j < n; j++) {
					if (j == x)
						continue;
					submatrix[subi][subj] = matrix[i][j];
					subj++;
				}
				subi++;
			}
			det = det + (pow(-1, x) * matrix[0][x] * determinant(submatrix, n - 1));
		}
	}
	return det;
}
//-------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------MATRICE-----------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------

class Matrice {
protected:
	int linii;
	int **m;
public:
	Matrice();
	Matrice(int linii);
	~Matrice();
	virtual bool is_tri()=0;
	virtual bool is_diag() = 0;

};

Matrice::Matrice() {
	cout << "Exist!\n";
}
Matrice::Matrice(int linii) {
	this->linii = linii;
	m = new int* [linii];

	
}
Matrice::~Matrice() {
	delete[] m;
}
class Matrice_oarecare :public Matrice {
private:
	int col;
public:
	Matrice_oarecare() {
		cout << "Exist\n";
	}
	Matrice_oarecare(int lin,int col);
	~Matrice_oarecare();
	bool is_tri();
	bool is_diag();
	friend istream& operator >>(istream &in, Matrice_oarecare &obj);
	friend ostream& operator <<(ostream &out, const Matrice_oarecare &obj);
	Matrice_oarecare& operator =( const Matrice_oarecare &obj) {
		this->col = obj.col;
		this->linii = obj.linii;
		this->m = new int*[obj.linii];
		for (int i = 0; i < obj.linii; i++)
			this->m[i] = new int[obj.col];
		for (int i = 0; i < obj.linii; i++)
			for (int j = 0; j < obj.col; j++)
				this->m[i][j] = obj.m[i][j];
		return *this;
	}
};

istream& operator >>(istream &in, Matrice_oarecare &obj) {
	cout << "Linii si coloane: ";
	int l, c;
	in >> l >> c;
	obj.linii = l;
	obj.col = c;
	obj.m = new int*[l];
	for (int i = 0; i < l; i++)
		obj.m[i] = new int[c];
	cout << "Elementele sunt:\n";
	for (int i = 0; i < l; i++)
		for (int j = 0; j < c; j++)
			in >> obj.m[i][j];

	return in;
}

ostream& operator <<(ostream &out, const Matrice_oarecare &obj) {
	for (int i = 0; i < obj.linii; i++) {
		for (int j = 0; j < obj.col; j++)
			out << obj.m[i][j] << ' ';
		out << "\n";
	}
	return out;
}
bool Matrice_oarecare::is_tri() {
	if(linii!=col)
		return false;
	else {
		int ok_inf = 0, ok_sup = 0;
		for (int i = 0; i < linii; i++)
			for (int j = 0; j < col; j++) {
				if (i > j && m[i][j] != 0)
					ok_inf = 1;
				if (i < j && m[i][j] != 0)
					ok_sup = 1;
			}
		if (ok_inf == 1 && ok_sup == 1)
			return false;
		return true;
	}
}
bool Matrice_oarecare::is_diag() {
	if (linii != col)
		return false;
	else {
		int ok_inf = 0, ok_sup = 0;
		for (int i = 0; i < linii; i++)
			for (int j = 0; j < col; j++) {
				if (i > j && m[i][j] != 0)
					ok_inf = 1;
				if (i < j && m[i][j] != 0)
					ok_sup = 1;
			}
		if (ok_inf == 0 && ok_sup == 0)
			return true;
		return false;
	}
}
Matrice_oarecare::Matrice_oarecare(int lin, int col) : Matrice(col) {
	this->col = col;
	for (int i = 0; i< lin; i++)
		m[i] = new int[col];
 }

Matrice_oarecare::~Matrice_oarecare() {
	for (int i = 0; i < linii; i++)
		delete[] m[i];
}
class Matrice_patratica :public Matrice {
public:
	Matrice_patratica();
	Matrice_patratica(int dim);
	bool is_tri();
	bool is_diag();
	friend istream& operator >>(istream &in, Matrice_patratica &obj);
	friend ostream& operator <<(ostream &out, const Matrice_patratica &obj);
	Matrice_patratica& operator =(const Matrice_patratica &obj);
	int det();
};

int Matrice_patratica::det() {
	int mat[10][10];
	for (int i = 0; i < linii; i++)
		for (int j = 0; j < linii; j++)
			mat[i][j] = m[i][j];
	return determinant(mat, linii);
}
Matrice_patratica& Matrice_patratica:: operator =(const Matrice_patratica &obj) {
	this->linii = obj.linii;
	this->m = new int*[obj.linii];
	for (int i = 0; i < obj.linii; i++)
		this->m[i] = new int[obj.linii];
	for (int i = 0; i < obj.linii; i++)
		for (int j = 0; j < obj.linii; j++)
			this->m[i][j] = obj.m[i][j];
	return *this;
}
istream& operator >>(istream &in, Matrice_patratica &obj) {
	cout << "Dimensiunea: ";
	int n;
	in >> n;
	obj.linii = n;
	obj.m = new int*[n];
	for (int i = 0; i < n; i++)
		obj.m[i] = new int[n];
	cout << "Elementele sunt:\n";
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			in >> obj.m[i][j];

	return in;
}

ostream& operator <<(ostream &out, const Matrice_patratica &obj) {
	for (int i = 0; i < obj.linii; i++) {
		for (int j = 0; j < obj.linii; j++)
			out << obj.m[i][j] << ' ';
		out << "\n";
	}
	return out;
}
Matrice_patratica::Matrice_patratica():Matrice() {

}

Matrice_patratica::Matrice_patratica(int dim):Matrice(dim) {
	for (int i = 0; i <= dim; i++)
		this->m[i] = new int[dim];
}

bool Matrice_patratica::is_tri() {
		int ok_inf = 0, ok_sup = 0;
		for (int i = 0; i < linii; i++)
			for (int j = 0; j < linii; j++) {
				if (i > j && m[i][j] != 0)
					ok_inf = 1;
				if (i < j && m[i][j] != 0)
					ok_sup = 1;
			}
		if (ok_inf == 1 || ok_sup == 1)
			return false;
		return true;
	
}
bool Matrice_patratica::is_diag() {
	int ok_inf = 0, ok_sup = 0;
	for (int i = 0; i < linii; i++)
		for (int j = 0; j < linii; j++) {
			if (i > j && m[i][j] != 0)
				ok_inf = 1;
			if (i < j && m[i][j] != 0)
				ok_sup = 1;
		}
	if (ok_inf == 0 && ok_sup == 0)
		return true;
	return false;
}
int main()
{
	/*Vector v;
	cin >> v;
	cout << v;
	Vector w(v);
	cout << w;
	
	Matrice_oarecare A(2,2);
	Matrice_oarecare B;
	cin >> A;
	cout << A;
	*/
	//cin >> B;
	//cout << B;
	//B = A;
	//cout << B;
	//cout << A.is_tri();
	//cout << '\n' << A.is_diag();
	Matrice_patratica C,D;
	cin >> C;
	//D = C;
	cout << C.det();
	//cout << '\n' << D.is_diag();
	return 0;
}
