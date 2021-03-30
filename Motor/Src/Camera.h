#ifndef CAMERA_H
#define CAMERA_H

#include "Entity.h"


class ENGINE_API Camera : public Entity
{
private:
	glm::vec3 _front;
	glm::vec3 _up;
	glm::vec3 _right;
	glm::vec3 _worldUp;

	float _yaw;
	float _pitch;

public:
	Camera(Renderer* _render);
	~Camera();
	void InitCamera(glm::vec3 pos, glm::vec3 up, float yaw, float pitch);
	glm::mat4 CalculateViewMatrix();
	void UpdateCamera();
	void SetPitch(float p);
	void SetYaw(float y);
	float GetPitch();
	float GetYaw();

	void RotateCameraX(float speed);
	void RotateCameraY(float speed);
	void RotateCameraZ(float speed);
};
#endif