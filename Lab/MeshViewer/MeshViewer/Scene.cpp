#include "Scene.h"

Scene::Scene(const glm::vec3& indentDirection, const glm::vec3& defaultColor, const glm::vec3& selectionColor) :
	indentDirection(glm::normalize(indentDirection)),
	currentSelection(-1),
	defaultColor(defaultColor),
	selectionColor(selectionColor),
	meshCollection(std::vector<std::unique_ptr<Mesh>>()) {}

void Scene::addMesh(std::unique_ptr<Mesh> meshPtr)
{
	const float modelDistanceFactor = 1.5f;

	if (getMeshCount() > 0) {
		Mesh& lastMesh = operator[](getMeshCount() - 1);
		meshPtr->setPosition((lastMesh.getOuterRadius() + meshPtr->getOuterRadius()) * modelDistanceFactor * indentDirection + lastMesh.getWorldPosition());
	}
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

size_t Scene::getMeshCount() const
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
