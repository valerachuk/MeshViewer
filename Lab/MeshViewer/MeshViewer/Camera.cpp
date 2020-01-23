#include "Camera.h"

Camera::Camera() :
	eye(glm::vec3(0.0f, 1.0f, 0.0f)),
	target(0.0f),
	up(glm::vec3(0.0f, 1.0f, 0.0f)) { }

glm::mat4 Camera::calcViewMatrix() const
{
	return glm::lookAt(eye, target, up);
}

glm::vec3 Camera::calcForward() const
{
	return glm::normalize(target - eye);
}

glm::vec3 Camera::calcRight() const
{
	return glm::normalize(glm::cross(calcForward(), up));
}

float Camera::distanceFromEyeToTarget() const
{
	return glm::distance(eye, target);
}

const glm::vec3& Camera::getEye() const
{
	return eye;
}

const glm::vec3& Camera::getTarget() const
{
	return target;
}

const glm::vec3& Camera::getUp() const
{
	return up;
}

void Camera::setFrontView()
{
	float D = distanceFromEyeToTarget();
	setEyeTargetUp(target + glm::vec3(0.0f, 0.0f, 1.0f), target, glm::vec3(0.0f, 1.0f, 0.0f));
	setDistnceToTarget(D);
}

void Camera::setTopView()
{
	setFrontView();
	rotate(target, glm::vec3(1.0f, 0.0f, 0.0f), -90.0f);
}

void Camera::setRearView()
{
	setFrontView();
	rotate(target, glm::vec3(0.0f, 1.0f, 0.0f), 180.0f);
}

void Camera::setRightView()
{
	setFrontView();
	rotate(target, glm::vec3(0.0f, 1.0f, 0.0f), 90.0f);
}

void Camera::setLeftView()
{
	setFrontView();
	rotate(target, glm::vec3(0.0f, 1.0f, 0.0f), -90.0f);
}

void Camera::setBottomView()
{
	setFrontView();
	rotate(target, glm::vec3(1.0f, 0.0f, 0.0f), 90.0f);
}

void Camera::setIsoView()
{
	setFrontView();
	rotate(target, glm::vec3(0.0f, 1.0f, 0.0f), 45.0f);
	rotate(target, glm::vec3(0.0f, 0.0f, 1.0f), 45.0f);
	setEyeTargetUp(eye, target, glm::vec3(0.0f, 1.0f, 0.0f));
}

void Camera::zoom(float factor)
{
	setDistnceToTarget(distanceFromEyeToTarget() * factor);
}

void Camera::setDistnceToTarget(float D)
{
	eye = target - calcForward() * D;
}

void Camera::updateTarget(glm::vec3 newTarget)
{
	float D = distanceFromEyeToTarget();
	target = newTarget;
	setDistnceToTarget(D);
}

void Camera::transform(const glm::mat4& trf)
{
	eye = trf * glm::vec4(eye, 1.0f); //vec4 --> vec3
}

void Camera::rotate(glm::vec3 point, glm::vec3 axis, float angle)
{
	eye -= point;
	target -= point;

	transform(glm::rotate(glm::mat4(1.0f), glm::radians(angle), axis));
	updateUp();

	eye += point;
	target += point;
}

void Camera::setEyeTargetUp(glm::vec3 newEye, glm::vec3 newTarget, glm::vec3 newUp)
{
	eye = newEye;
	target = newTarget;
	glm::vec3 fwd = calcForward();
	up = glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::cross(fwd, newUp)) * glm::vec4(fwd, 1.0f); //vec4 --> vec3
}

void Camera::updateUp()
{
	glm::vec3 fwd = calcForward();
	up = glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::cross(fwd, up)) * glm::vec4(fwd, 1.0f); //vec4 --> vec3
}
