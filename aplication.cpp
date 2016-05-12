#include<iostream>
#include<math.h>
#include<fstream>

#define M_PI           3.14159265358979323846  /* pi */

using namespace std;
double x_beg, x_end, x_step, precision;

void chose_enter();
void keyboard();
void read_file(double&, double&, double&, double&);
void calculation(double, double, double, double);
double factorial(int);
double** cos_pow_3 (double, double, double, double);
void output(double**, int);
double val_cur_val(double, char, double, double, int);
double** check_function(double, double, double);
void write_to_file(double**, int);

int main() {
	chose_enter();
	system("pause");
	return 0;
}

void chose_enter() {
	char number;
	cout << "If you want write value at kayboard, enter 1." << endl << "If you want taken from the file, enter 2." << endl;
	cin >> number;
	switch (number){
	case '1': keyboard(); break;
	case '2': read_file(x_beg, x_end, x_step, precision); break;
		default: cout << "Your input data is incorrect!"; 
		break;
	}
}

void keyboard() {
	cout << "Enter X(begin): "; cin >> x_beg;
	cout << "Enter X(end): "; cin >> x_end;
	cout << "Enter step of x: "; cin >> x_step;
	cout << "Enter precision: "; cin >> precision;
	calculation(x_beg, x_end, x_step, precision);
	
}

void read_file(double& x_beg, double& x_end, double& x_step, double& precision) {
	ifstream input("input_file.txt");

	input >> x_beg; cout << "X(begin): " << x_beg << endl;
	input >> x_end; cout << "X(end): " << x_end << endl;
	input >> x_step; cout << "Step of x: " << x_step << endl;
	input >> precision; cout << "Precision: " << precision << endl;
	input.close();
	calculation(x_beg, x_end, x_step, precision);
}

void calculation(double, double, double, double) {
	double** result = cos_pow_3(x_beg, x_end, x_step, precision);
	write_to_file(result, (int)((x_end - x_beg) / x_step) + 1);
	double** check_res = check_function(x_beg, x_end, x_step);
	output(result, (int)((x_end - x_beg) / x_step) + 1);					//include last point
	output(check_res, (int)((x_end - x_beg) / x_step) + 1);
}

double** cos_pow_3 (double x_beg, double x_end, double x_step, double precision) {
	double **result = new double*[(int)((x_end - x_beg) / x_step) + 1];
	for (int i = 0; i < (int)((x_end - x_beg) / x_step) + 1; ++i)
		result[i] = new double[2];
	for (int i = 0; x_beg <= x_end ; x_beg += x_step, ++i) {
		result[i][0] = x_beg;
		result[i][1] = INT32_MAX;
		char sign = 1;
		//cout << "Counting for x = " << x_beg << endl;
		result[i][1] = val_cur_val(x_beg, sign, precision, result[i][1], 0);
		result[i][1] = pow(result[i][1], 3);
		cout << endl;
	}
	return result;
}

double factorial(int n) {
	if (n == 0) return 1;
	return n * (factorial(n - 1));
}

void output(double** arr, int lines) {
	cout << "Massive of elements is: \n";
	for (int i = 0; i < lines; i++)
	{
		for (int j = 0; j < 2; ++j)
		{
			cout << arr[i][j] << "\t ";
		}
		cout << endl;
	}
}

double val_cur_val(double x, char sign, double precision, double cur_val, int i) {
	if (fabs(cur_val) <= precision) 
		return 0;
	long double y_val = (pow(x, 2 * i)) / factorial(2 * i);
	//cout << sign * y_val << " with i = " << i << "| ";
	return y_val * sign + val_cur_val(x, sign * (-1), precision, y_val, i + 1 );

}

double** check_function(double b, double e, double s) {
	double **result = new double*[(int)((e - b) / s) + 1];
	for (int i = 0; i < (int)((e - b) / s) + 1; ++i)
		result[i] = new double[2];
	for (int i = 0; b <= e; b += s, ++i) {
		result[i][0] = b;
		result[i][1] = pow(cos(b),3);
	}
	return result;
}

void write_to_file(double** mas, int lines) {
	ofstream fout;
	fout.open("result.txt");
	fout << "Massive of elements is: \n";
	for (int i = 0; i < lines; i++)
	{
		for (int j = 0; j < 2; ++j)
		{
			fout << mas[i][2] << "\t ";
		}
		fout << endl;
	}
	fout.close();
}
