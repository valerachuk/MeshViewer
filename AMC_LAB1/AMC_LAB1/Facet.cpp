#include "Facet.h"

Facet::Facet(){}
Facet::Facet(Vector3 A, Vector3 B, Vector3 C): A(A), B(B), C(C) {
	SetNormal();
}

void Facet::SetNormal()
{
	Vector3 v1 = B + A*(-1);
	Vector3 v2 = C + A*(-1);
	normal = Vector3::get_normal(v1, v2);
	normal = normal * (1 / normal.get_len());
}

istream& operator>> (istream& in, Facet& facet) {
	std::string skip;
	in >> skip;
	if (skip != "normal")
		throw "normal keyword is missing";

	in >> facet.normal;
	
	in >> skip;
	if (skip != "outer")
		throw "outer keyword is missing";
	in >> skip;
	if (skip != "loop")
		throw "loop keyword is missing";

	Vector3* points[3]{&facet.A, &facet.B, &facet.C};
	for (int i = 0; i < 3; i++)
	{
		in >> skip;
		if (skip != "vertex")
			throw "vertex keyword is missing";
		in >> *(points[i]);
	}
	in >> skip;
	if (skip != "endloop")
		throw "endloop keyword is missing";
	
	in >> skip;
	if (skip != "endfacet")
		throw "endfacet keyword is missing";
	return in;
}
ostream& operator<< (ostream& out, const Facet& facet) {
	out << "\tfacet normal " << facet.normal << "\n\t\touter loop";
	Vector3 points[3]{ facet.A, facet.B, facet.C };
	for (int i = 0; i < 3; i++)
		out << "\n\t\t\tvertex " << points[i];

	out << "\n\t\tendloop\n\tendfacet\n";

	return out;
}
