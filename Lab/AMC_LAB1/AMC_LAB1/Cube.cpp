#include "Cube.h"

Solid Cube::GetCube(double L, Vector3 origin) {
	if (L <= 0)
		throw std::invalid_argument("L have to be > 0");

	Solid cube;

	Vector3 v1 = Vector3(1, -1, -1)*(L/2);
	Vector3 v2 = Vector3(1, 1, -1) * (L / 2);
	Vector3 v3 = Vector3(1, 1, 1) * (L / 2);
	Vector3 v4 = Vector3(1, -1, 1) * (L / 2);
	Vector3 v5 = Vector3(-1, 1, -1) * (L / 2);
	Vector3 v6 = Vector3(-1, -1, -1) * (L / 2);
	Vector3 v7 = Vector3(-1, -1, 1) * (L / 2);	
	Vector3 v8 = Vector3(-1, 1, 1) * (L / 2);

	cube.AddFacet(Facet(v1, v2, v3));
	cube.AddFacet(Facet( v3, v4, v1 ));

	cube.AddFacet(Facet( v3, v2, v5));
	cube.AddFacet(Facet(v5, v8, v3 ));

	cube.AddFacet(Facet( v7, v4, v3 ));
	cube.AddFacet(Facet( v7, v3, v8 ));

	cube.AddFacet(Facet( v2, v1, v6 ));
	cube.AddFacet(Facet(v2, v6, v5 ));

	cube.AddFacet(Facet(v4, v7, v6 ));
	cube.AddFacet(Facet(v4, v6, v1 ));

	cube.AddFacet(Facet(v6, v7, v8 ));
	cube.AddFacet(Facet(v6, v8, v5 ));

	return cube;
}