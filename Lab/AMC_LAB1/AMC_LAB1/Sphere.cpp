#include "Sphere.h"

Vector3 Sphere::GetVertex(double R, double Th, double Ph) {
	return Vector3(R * sin(Th) * cos(Ph), R * sin(Th) * sin(Ph), R * cos(Th));
}

Solid Sphere::GetSphere(double radius, double rings, double slices, Vector3 origin) {
	if (rings <= 2 || slices <= 1)
		throw std::invalid_argument("slices<=2 || rings <=1");
	Solid sphere = Solid("My_Sphere");
	
	for (int i = 0; i < rings; i++)
	{
		double Th = M_PI / rings * i;
		double ThNext = M_PI / rings * (i + 1.);

		for (int j = 0; j < slices; j++)
		{
			double Ph = 2 * M_PI / slices * j;
			double PhNext = 2 * M_PI / slices * (j + 1.);
			Vector3 V1 = GetVertex(radius, Th, Ph)+origin;
			Vector3 V2 = GetVertex(radius, ThNext, Ph) + origin;
			Vector3 V3 = GetVertex(radius, ThNext, PhNext) + origin;
			Vector3 V4 = GetVertex(radius, Th, PhNext) + origin;
			if (i < rings - 1)
				sphere.AddFacet(Facet( V1, V2, V3 ));
			if (i > 0)
				sphere.AddFacet(Facet( V3, V4, V1 ));
		}
	}
	return sphere;
}