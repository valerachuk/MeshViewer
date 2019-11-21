#pragma once
#include "Facet.h"
#include <vector>

class Solid {
	std::string name;
	int facetcnt;
	std::vector<Facet> facets;
public:
	void AddFacet(Facet);
	int getFacetCnt() const;
	std::string getSolidName() const;
	Solid();
	Solid(std::string);
	friend istream& operator>> (istream& in, Solid& solid);
	friend ostream& operator<< (ostream& out, const Solid& solid);
};