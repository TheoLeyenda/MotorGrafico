#ifndef CAMERA_H
#define CAMERA_H

#include "Entity.h"

static enum TypeProjectionCamera
{
	Perspective,
	Ortho,
};

static struct ProjectionDataOrtho
{
	float left;
	float right;
	float bottom;
	float top;
	float near;
	float front;
};

struct ProjectionDataPerspective
{
public:
	float FOV;
	float aspect;
	float near;
	float front;
};

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

	TypeProjectionCamera typeProjectionCamera;
	ProjectionDataPerspective projectionDataPerspective;
	ProjectionDataOrtho projectionDataOrtho;
	Camera(Renderer* _render, TypeProjectionCamera _typeProjectionCamera);
	~Camera();
	void InitCamera(glm::vec3 pos, glm::vec3 up, float yaw, float pitch);
	glm::mat4 CalculateViewMatrix();
	void UpdateCamera();
	void SetPitch(float p);
	void SetYaw(float y);
	float GetPitch();
	float GetYaw();

	void SetDataPerspective(float FOV, float sizeScreenX, float sizeScreenY, float near, float front);

	void SetDataOrtho(float left, float right, float bottom, float top, float near, float front);

	void ChangePerspective(TypeProjectionCamera _typeProjectionCamera);

	void UseProjection();

	void RotateCameraX(float speed);
	void RotateCameraY(float speed);
	void RotateCameraZ(float speed);
};
#endif