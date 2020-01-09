#include "Vector3.h"

double& Vector3::get_x()
{
	return x;
}

double& Vector3::get_y()
{
	return y;
}

double& Vector3::get_z()
{
	return z;
}

Vector3 Vector3::get_normal(Vector3 v1, Vector3 v2)
{
	return Vector3(v1.get_y() * v2.get_z() - v1.get_z() * v2.get_y(), v1.get_z() * v2.get_x() - v1.get_x() * v2.get_z(), v1.get_x() * v2.get_y() - v1.get_y() * v2.get_x());
}

double Vector3::get_len()
{
	return sqrt(x*x+y*y+z*z);
}

Vector3::Vector3(): x(0), y(0), z(0) {}
Vector3::Vector3(double x, double y, double z) : x(x), y(y), z(z) {}
istream& operator>> (istream& in, Vector3& vector3) {
	in >> vector3.x;
	in >> vector3.y;
	in >> vector3.z;
	return in;
}
ostream& operator<< (ostream& out, const Vector3& vector3) {
	out << vector3.x << " ";
	out << vector3.y << " ";
	out << vector3.z;
	return out;
}
Vector3 Vector3::operator*(double value) {
	return Vector3(x * value, y * value, z * value);
}

Vector3 Vector3::operator+(Vector3 other) {
	return Vector3(x + other.x, y + other.y, z + other.z);
}