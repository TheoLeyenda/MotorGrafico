
#include "Camera.h"

Camera::Camera(Renderer* _render, TypeProjectionCamera _typeProjectionCamera) : Entity(_render)
{
	typeProjectionCamera = _typeProjectionCamera;
}

Camera::~Camera(){}

void Camera::InitCamera(glm::vec3 pos, glm::vec3 up, float yaw, float pitch) {
	SetPosition(pos.x, pos.y, pos.z);
	_worldUp = up;
	_yaw = yaw;
	_pitch = pitch;
	_front = glm::vec3(0.0f, 0.0f, -1.0f);
	UpdateCamera();
}
glm::mat4 Camera::CalculateViewMatrix() {
	return glm::lookAt(transform.position, transform.position + _front, _up);
}
void Camera::UpdateCamera() {
	_front.x = cos(glm::radians(_yaw)) * cos(glm::radians(_pitch));
	_front.y = sin(glm::radians(_pitch));
	_front.z = sin(glm::radians(_yaw)) * cos(glm::radians(_pitch));
	_front = glm::normalize(_front);

	_right = glm::normalize(glm::cross(_front, _worldUp));
	_up = glm::normalize(glm::cross(_right, _front));
}
void Camera::SetPitch(float p) {
	_pitch = p;
	UpdateCamera();
}
void Camera::SetYaw(float y) {
	_yaw = y;
	UpdateCamera();
}
float Camera::GetPitch() {
	return _pitch;
}
float Camera::GetYaw() {
	return _yaw;
}

void Camera::SetDataPerspective(float FOV, float sizeScreenX, float sizeScreenY, float near, float front)
{
	projectionDataPerspective.FOV = FOV;
	projectionDataPerspective.aspect = sizeScreenX / sizeScreenY;
	projectionDataPerspective.near = near;
	projectionDataPerspective.front = front;
}

void Camera::SetDataOrtho(float left, float right, float bottom, float top, float near, float front)
{
	projectionDataOrtho.left = left;
	projectionDataOrtho.right = right;
	projectionDataOrtho.bottom = bottom;
	projectionDataOrtho.top = top;
	projectionDataOrtho.near = near;
	projectionDataOrtho.front = front;
}

void Camera::ChangePerspective(TypeProjectionCamera _typeProjectionCamera)
{
	typeProjectionCamera = _typeProjectionCamera;
	UseProjection();
}

void Camera::UseProjection()
{
	switch (typeProjectionCamera)
	{
	case Perspective:
		renderer->SetProjectionPerspective(
			projectionDataPerspective.FOV,
			projectionDataPerspective.aspect,
			projectionDataPerspective.near,
			projectionDataPerspective.front
		);
		break;
	case Ortho:
		renderer->SetProjectionOrtho(
			projectionDataOrtho.left,
			projectionDataOrtho.right,
			projectionDataOrtho.bottom,
			projectionDataOrtho.top,
			projectionDataOrtho.near,
			projectionDataOrtho.front
		);
		break;
	}
}

void Camera::RotateCameraX(float speed)
{
	_pitch = _pitch + speed;
	UpdateCamera();
}

void Camera::RotateCameraY(float speed)
{
	_yaw = _yaw + speed;
	UpdateCamera();
}

void Camera::RotateCameraZ(float speed)
{
	//PEDIR AYUDA PARA REALIZAR LA ROTACION EN Z
}
