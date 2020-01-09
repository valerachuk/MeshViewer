#include "Scene.h"

Scene::Scene(glm::vec3 indentVector) : 
	indentVector(indentVector), 
	currentSelection(-1), 
	meshCollection(std::vector<Mesh*>()) {}

Scene::~Scene()
{
	for (int i = 0; i < getMeshCount(); i++)
	{
		delete meshCollection[i];
	}
}

void Scene::addMesh(Mesh& mesh)
{
	mesh.setPosition(indentVector * (float)(getMeshCount()));
	meshCollection.push_back(&mesh);
}

void Scene::addMesh(Mesh* mesh)
{
	addMesh(*mesh);
}

Mesh& Scene::getCurrentSelection()
{
	return operator[](currentSelection);
}

int Scene::getCurrentSelectionId()
{
	return currentSelection;
}

void Scene::setSelectionId(int id)
{
	currentSelection = id;
}

int Scene::getMeshCount()
{
	return meshCollection.size();
}

Mesh& Scene::operator[](int i)
{
	return *meshCollection[i];
}
