#include "Viewport.h"

Viewport::Viewport() : 
	width(1), 
	height(1), 
	fov(60), 
	zNear(0.1), 
	zFar(500), 
	isParalellProj(false),
	camera(Camera()) {}

glm::mat4 Viewport::calcProjectionMatrix() const
{
	if (isParalellProj)
	{
		double halfWidth = calcTargetPlaneWidth()/2;
		double halfHeight = calcTargetPlaneHeigth()/2;
		return glm::ortho(-halfWidth, halfWidth, -halfHeight, halfHeight, zNear, zFar);
	}

	return glm::perspective(glm::radians(fov), calcAspectRatio(), zNear, zFar);
}

void Viewport::setViewportSize(uint32_t inWidth, uint32_t inHeigth)
{
	width = inWidth;
	height = inHeigth;
}

void Viewport::setFov(double inFov)
{
	fov = inFov;
}

void Viewport::setZNear(double inZNear)
{
	zNear = inZNear;
}

void Viewport::setZFar(double inZFar)
{
	zFar = inZFar;
}

void Viewport::setParallelProjection(bool use)
{
	isParalellProj = use;
}

double Viewport::getZNear() const
{
	return zNear;
}

double Viewport::getZFar() const
{
	return zFar;
}

double Viewport::getFov() const
{
	return fov;
}

double Viewport::getWidth() const
{
	return width;
}

double Viewport::getHeight() const
{
	return height;
}

bool Viewport::isParalellProjection() const
{
	return isParalellProj;
}

double Viewport::calcTargetPlaneWidth() const
{
	return calcTargetPlaneHeigth() * calcAspectRatio();
}

double Viewport::calcTargetPlaneHeigth() const
{
	return 2.0 * camera.distanceFromEyeToTarget() * glm::tan(glm::radians(fov / 2.0));
}

double Viewport::calcAspectRatio() const
{
	return width/height;
}

Camera& Viewport::getCamera()
{
	return camera;
}

const Camera& Viewport::getCamera() const
{
	return camera;
}
