#pragma once
#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

class Vector3 {
	double x, y, z;
public:
	double& get_x();
	double& get_y();
	double& get_z();
	static Vector3 get_normal(Vector3, Vector3);
	double get_len();
	Vector3();
	Vector3(double, double, double);
	Vector3 operator+(Vector3 other);
	Vector3 operator*(double value);
	friend istream& operator>> (istream& in, Vector3& vector3);
	friend ostream& operator<< (ostream& out, const Vector3& vector3);
};