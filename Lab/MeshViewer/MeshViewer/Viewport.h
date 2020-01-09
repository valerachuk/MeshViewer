#pragma once
#include <GL\glew.h>
#include "glm\glm.hpp"
#include "Camera.h"

class Viewport
{
public:
	Viewport();

	glm::mat4 calcProjectionMatrix() const;

	void setViewportSize(uint32_t inWidth, uint32_t inHeigth);
	void setFov(double inFov);
	void setZNear(double inZNear);
	void setZFar(double inZFar);
	void setParallelProjection(bool use);

	double getZNear() const;
	double getZFar() const;
	double getFov() const;
	double getWidth() const;
	double getHeight() const;
	bool isParalellProjection() const;

	double calcTargetPlaneWidth() const;
	double calcTargetPlaneHeigth() const;
	double calcAspectRatio() const;
	
	Camera& getCamera();
	const Camera& getCamera() const;

private:
	double zNear, zFar;
	double fov;
	double width, height;
	bool isParalellProj;
	Camera camera;
};