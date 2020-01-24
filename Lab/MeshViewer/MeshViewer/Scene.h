#pragma once
#include <vector>
#include <memory>
#include <glm\glm.hpp>
#include "Mesh.h"

class Scene
{
public:
	Scene(const glm::vec3& indentDirection, const glm::vec3& defaultColor = glm::vec3(1), const glm::vec3& selectionColor = glm::vec3(0.7f, 1.0f, 0.7f));

	void addMesh(std::unique_ptr<Mesh>);
	
	void setSelectionId(int id);
	bool isSelected() const;
	Mesh& getCurrentSelection();
	int getCurrentSelectionId() const;

	int getMeshCount() const;

	const glm::vec3& getDefaultColor() const;
	const glm::vec3& getSelectionColor() const;

	Mesh& operator[](int);

private:
	std::vector<std::unique_ptr<Mesh>> meshCollection;

	int currentSelection;
	glm::vec3 indentDirection;

	glm::vec3 defaultColor;
	glm::vec3 selectionColor;
};