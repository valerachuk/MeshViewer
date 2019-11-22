#include <List>
#include <iostream>
#include <fstream>
#include <chrono>
#include "Solid.h"
#include "Sphere.h"
#include "Cube.h"
#include "Facet.h"

using namespace std;

int ReadWrite() {
	const string inFile = "input.stl";
	const string outFile = "output.stl";

	ifstream file(inFile);
	Solid v;
	auto t1 = chrono::high_resolution_clock::now();
	try
	{
		file >> v;
	}
	catch (const char* error)
	{
		cout << "Reading ERROR: " << error;
		return 1;
	}

	auto t2 = chrono::high_resolution_clock::now();
	file.close();
	//cout << "Solid name: " << v.getSolidName() << " Facet count: " << v.getFacetCnt() << endl << "Read time: " << chrono::duration_cast<chrono::milliseconds>(t2 - t1).count() << "ms\n";

	ofstream ofile(outFile);
	t1 = chrono::high_resolution_clock::now();
	ofile << v;
	t2 = chrono::high_resolution_clock::now();
	ofile.close();
	cout << "Write time: " << chrono::duration_cast<chrono::milliseconds>(t2 - t1).count() << "ms";
	return 0; 

}

int CreateSphere() {
	const string outFile = "output.stl";
	ofstream ofile(outFile);
	ofile << Sphere::GetSphere(10, 3, 3);
	ofile.close();
	return 0;
}

int CreateCube() {
	const string outFile = "output.stl";
	ofstream ofile(outFile);
	ofile << Cube::GetCube(100);
	ofile.close();
	return 0;
}

int main()
{
	//return ReadWrite();
	//return CreateSphere();
	//return CreateCube();
	try
	{
		Facet f = Facet(Vector3(), Vector3(), Vector3(27, 8, 94));
		std::cout << f;
	}
	catch (const std::exception& arg)
	{
		cout << arg.what();
	}
	return 0;
}
