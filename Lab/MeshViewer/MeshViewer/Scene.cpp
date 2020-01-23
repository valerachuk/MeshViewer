#include "Scene.h"

Scene::Scene(glm::vec3 indentVector) : 
	indentVector(indentVector), 
	currentSelection(-1), 
	meshCollection(std::vector<std::unique_ptr<Mesh>>()) {}

void Scene::addMesh(std::unique_ptr<Mesh> meshPtr)
{
	meshPtr->setPosition(indentVector * (float)(getMeshCount()));
	meshCollection.push_back(std::move(meshPtr));
}

Mesh& Scene::getCurrentSelection()
{
	return operator[](currentSelection);
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

Mesh& Scene::operator[](int i)
{
	return *meshCollection[i];
}
