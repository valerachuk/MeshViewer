#pragma once
#include <vector>
#include <memory>
#include <glm\glm.hpp>
#include "Mesh.h"

class Scene
{
public:
	Scene(glm::vec3 spawnDirection);

	void addMesh(std::unique_ptr<Mesh>);
	
	void setSelectionId(int id);
	Mesh& getCurrentSelection();
	int getCurrentSelectionId() const;
	bool isSelected() const;
	int getMeshCount() const;

	Mesh& operator[](int i);

private:
	std::vector<std::unique_ptr<Mesh>> meshCollection;
	int currentSelection;
	glm::vec3 indentVector;

};