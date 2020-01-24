#include "Scene.h"

Scene::Scene(const glm::vec3& indentVector, const glm::vec3& defaultColor, const glm::vec3& selectionColor) :
	indentVector(indentVector), 
	currentSelection(-1),
	defaultColor(defaultColor),
	selectionColor(selectionColor),
	meshCollection(std::vector<std::unique_ptr<Mesh>>()) {}

void Scene::addMesh(std::unique_ptr<Mesh> meshPtr)
{
	meshPtr->setPosition(indentVector * (float)(getMeshCount()));
	meshCollection.push_back(std::move(meshPtr));
}

Mesh& Scene::getCurrentSelection()
{
	return *meshCollection[currentSelection];
}

int Scene::getCurrentSelectionId() const
{
	return currentSelection;
}

void Scene::setSelectionId(int id)
{
	if (id >= 0)
	{
		currentSelection = id;
	}
}

bool Scene::isSelected() const
{
	return currentSelection >= 0;
}

int Scene::getMeshCount() const
{
	return meshCollection.size();
}

const glm::vec3& Scene::getDefaultColor() const
{
	return defaultColor;
}

const glm::vec3& Scene::getSelectionColor() const
{
	return selectionColor;
}

Mesh& Scene::operator[](int i)
{
	return *meshCollection[i];
}
