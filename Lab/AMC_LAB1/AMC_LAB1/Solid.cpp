#include "Solid.h"
Solid::Solid() : name("NullName"){}

Solid::Solid(std::string name) : name(name){}

std::string Solid::getSolidName() const {
	return name;
}

void Solid::AddFacet(Facet other) {
	facets.push_back(other);
}

istream& operator>> (istream& in, Solid& solid) {
	std::string skip;
	in >> skip;
	if (skip != "solid")
		throw std::invalid_argument("solid keyword is missing");
	
	in >> solid.name;

	for (;;)
	{
		in >> skip;
		if (skip == "endsolid" || in.eof())
			return in;
		if (skip != "facet")
			throw std::invalid_argument("facet keyword is missing");

		Facet toPush;
		in >> toPush;
		solid.AddFacet(toPush);
	}

	return in;
}


ostream& operator<< (ostream& out, const Solid& solid) {
	out << "solid " << solid.name << "\n";
	
	for (auto i = solid.facets.begin(); i != solid.facets.end(); i++)
	{
		out << *i;
	}
	
	out << "endsolid " << solid.getSolidName();
	return out;
}