#pragma once
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

class Camera 
{
public:
	Camera();

	glm::mat4 calcViewMatrix() const;
	glm::vec3 calcForward() const;
	glm::vec3 calcRight() const;
	float distanceFromEyeToTarget() const;
	const glm::vec3& getEye() const;
	const glm::vec3& getTarget() const;
	const glm::vec3& getUp() const;
	
	void setFrontView();
	void setTopView();
	void setRearView();
	void setRightView();
	void setLeftView();
	void setBottomView();
	void setIsoView();

	void zoom(float factor);
	void setDistnceToTarget(float D);
	void updateTarget(glm::vec3 newTarget);
	void transform(const glm::mat4& trf);
	void rotate(glm::vec3 point, glm::vec3 axis, float angle);
	void setEyeTargetUp(glm::vec3 newEye, glm::vec3 newTarget, glm::vec3 newUp);
	void updateUp();

private:
	glm::vec3 eye;
	glm::vec3 target;
	glm::vec3 up;
};