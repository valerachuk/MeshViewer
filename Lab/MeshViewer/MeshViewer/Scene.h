#pragma once
#include <vector>
#include <glm\glm.hpp>
#include "Mesh.h"

class Scene
{
public:
	Scene(glm::vec3 spawnDirection);
	~Scene();

	void addMesh(Mesh&);
	void addMesh(Mesh*);
	
	void setSelectionId(int id);

	Mesh& getCurrentSelection();
	int getCurrentSelectionId();
	int getMeshCount();

	Mesh& operator[](int i);

private:
	std::vector<Mesh*> meshCollection;
	int currentSelection;
	glm::vec3 indentVector;
};