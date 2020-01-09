#pragma once
#include "Vector3.h"

class Facet {
	Vector3 normal;
	Vector3 A, B, C;
public:
	void SetNormal(); 
	Facet();
	Facet(Vector3 A, Vector3 B, Vector3 C);
	friend istream& operator>> (istream& in, Facet& facet);
	friend ostream& operator<< (ostream& out, const Facet& facet);
};