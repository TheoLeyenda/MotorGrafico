
#include "Camera.h"
#include <glew.h>
#include <GLFW/glfw3.h>
#include "Material.h"
#include "AxisAlignedBoundingBox.h"

Camera::Camera(Renderer* _render, TypeProjectionCamera _typeProjectionCamera) : Entity(_render)
{
	_MVP.view = glm::mat4(1.0f);
	_MVP.projection = glm::mat4(1.0f);
	typeProjectionCamera = _typeProjectionCamera;
	typeCamera = FirstPerson;
	InmortalObject = true;
}

Camera::~Camera()
{
	if (_AABBOrthographic != NULL && _AABBPerspective != NULL)
	{
		delete _AABBOrthographic;
		delete _AABBPerspective;
		_AABBOrthographic = NULL;
		_AABBPerspective = NULL;
	}
}

void Camera::ChangeActualFrustrum()
{
	switch (typeProjectionCamera)
	{
	case Perspective:
		_actualFrustrumInUse = _AABBPerspective;
		cout << "CHANGED TO PERSPECTIVE" << endl;
		break;
	case Ortho:
		_actualFrustrumInUse = _AABBOrthographic;
		cout << "CHANGED TO ORTHOGRAPHIC" << endl;
		break;
	}
}

void Camera::SetEnableDrawAABB(bool value)
{
	if (axisAlignedBoundingBox != NULL)
		axisAlignedBoundingBox->SetEnableDraw(value);
}

void Camera::BindBuffer(){}

void Camera::Draw(bool & wireFrameActive)
{
	UseCamera(renderer->GetCurrentShaderUse(), internalData.localModel);
}
void Camera::UseCamera(Shader& shader, glm::mat4 trsCamera)
{
	unsigned int transformLoc = glGetUniformLocation(shader.getId(), "model");
	unsigned int projectionLoc = glGetUniformLocation(shader.getId(), "projection");
	unsigned int viewLoc = glGetUniformLocation(shader.getId(), "view");
	glUseProgram(shader.getId());
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trsCamera));
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(_MVP.projection));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(_MVP.view));

	switch (typeProjectionCamera)
	{
	case Perspective:
		if (_AABBPerspective != NULL)
		{
			_AABBPerspective->UpdateInternalDataBoundingBox(internalData, transform);
			_AABBPerspective->Draw(_AABBPerspective->GetEnableDraw());
		}
		break;
	case Ortho:
		if (_AABBOrthographic != NULL)
		{
			_AABBOrthographic->UpdateInternalDataBoundingBox(internalData, transform);
			_AABBOrthographic->Draw(_AABBOrthographic->GetEnableDraw());
		}
		break;
	}
}
void Camera::SetViewFirstPerson()
{
	_MVP.view = CalculateViewMatrix();
}

void Camera::SetViewThirdPerson()
{
	_MVP.view = glm::lookAt(transform.position, targetThirdPerson->transform.position + _front, _up);
	CalculateThirdPersonPositionCamera();
}

void Camera::CalculateThirdPersonPositionCamera()
{
	float theta = targetThirdPerson->transform.rotation.y;
	float posX = CalculateHorizontalDistanceOfTarget() * glm::sin(glm::radians(theta));
	float posY = targetThirdPerson->transform.position.y + CalculateVerticalDistanceOfTarget();
	float posZ = CalculateHorizontalDistanceOfTarget() * glm::cos(glm::radians(theta));

	float finalPosX = targetThirdPerson->transform.position.x - posX;
	float finalPosY = posY;
	float finalPosZ = targetThirdPerson->transform.position.z - posZ;

	_yaw = 180 - glm::radians(targetThirdPerson->transform.rotation.y);

	SetPosition(finalPosX, finalPosY, finalPosZ);
	
	float _calcDistanceZ = CalculateDistanceOfTarget() - initOffsetCameraThirdPersonZ;

	glm::vec3 vec = glm::vec3(initOffsetCameraThirdPersonX, initOffsetCameraThirdPersonY, targetThirdPerson->GetForward().z* _calcDistanceZ);
	glm::vec3 addVector = transform.position + vec;
	SetPosition(addVector);
	

	lastPositionTarget = targetThirdPerson->transform.position;

	UpdateCamera();
}


float Camera::CalculateVerticalDistanceOfTarget() 
{
	return CalculateDistanceOfTarget() * glm::sin(glm::radians(_pitch));
}

float Camera::CalculateDistanceOfTarget()
{
	return glm::distance(transform.position, targetThirdPerson->transform.position);
}

float Camera::CalculateHorizontalDistanceOfTarget()
{
	return CalculateDistanceOfTarget() * glm::cos(glm::radians(_pitch));
}

void Camera::SetProjectionPerspective(float FOV, float aspect, float near, float front)
{
	//                                      FOV          Aspect  near   front
	_MVP.projection = glm::perspective(glm::radians(FOV), aspect, near, front);
}

void Camera::SetProjectionOrtho(float left, float right, float bottom, float top, float near, float front)
{
	_MVP.projection = glm::ortho(left, right, bottom, top, near, front);
}

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
	CheckIsModel();
	_front.x = cos(glm::radians(_yaw)) * cos(glm::radians(_pitch));
	_front.y = sin(glm::radians(_pitch));
	_front.z = sin(glm::radians(_yaw)) * cos(glm::radians(_pitch));
	_front = glm::normalize(_front);

	_right = glm::normalize(glm::cross(_front, _worldUp));
	_up = glm::normalize(glm::cross(_right, _front));

	//CheckIsModel();
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

string Camera::GetClassName()
{
	return "Camera";
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
	ChangeActualFrustrum();
	UseProjection();
}

void Camera::SetFrustrumCulling()
{
	_AABBOrthographic = new AxisAlignedBoundingBox(renderer);
	_AABBPerspective = new AxisAlignedBoundingBox(renderer);
		
	_AABBOrthographic->AttachEntity(internalData, transform);
	_AABBPerspective->AttachEntity(internalData, transform);

	float nearDist = ((transform.position.z + projectionDataPerspective.near) / (projectionDataPerspective.FOV / projectionDataPerspective.aspect));
	float farDist = ((transform.position.z + projectionDataPerspective.front) / (projectionDataPerspective.FOV / projectionDataPerspective.aspect));

	float nearZ = (transform.position.z + projectionDataPerspective.near);
	float farZ = (transform.position.z + projectionDataPerspective.front);

	vector<glm::vec3> _dataXYZOrtho;
	vector<glm::vec3> _dataXYZPerspective;

	float nearMinX = transform.position.x * (-nearDist);
	float nearMaxX = transform.position.x * (nearDist);
	float nearMinY = transform.position.y * (-nearDist);
	float nearMaxY = transform.position.y * (nearDist);
	
	float farMinX = transform.position.x * (-(farDist));
	float farMaxX = transform.position.x * ( (farDist));
	float farMinY = transform.position.y * (-(farDist));
	float farMaxY = transform.position.y * ( (farDist));

	#pragma region ORTHOGRAPHIC VIEW 
	//--------------------------------------------------------------------
	//0
	_dataXYZOrtho.push_back(glm::vec3(projectionDataOrtho.left , projectionDataOrtho.top, projectionDataOrtho.front));
	//1
	_dataXYZOrtho.push_back(glm::vec3(projectionDataOrtho.left , projectionDataOrtho.bottom,projectionDataOrtho.front));
	//2
	_dataXYZOrtho.push_back(glm::vec3(projectionDataOrtho.right, projectionDataOrtho.bottom,projectionDataOrtho.front));
	//3
	_dataXYZOrtho.push_back(glm::vec3(projectionDataOrtho.right, projectionDataOrtho.top,projectionDataOrtho.front));
	
	//4
	_dataXYZOrtho.push_back(glm::vec3(projectionDataOrtho.left , projectionDataOrtho.top, projectionDataOrtho.near));
	//5
	_dataXYZOrtho.push_back(glm::vec3(projectionDataOrtho.left , projectionDataOrtho.bottom, projectionDataOrtho.near));
	//6
	_dataXYZOrtho.push_back(glm::vec3(projectionDataOrtho.right, projectionDataOrtho.bottom, projectionDataOrtho.near));
	//7
	_dataXYZOrtho.push_back(glm::vec3(projectionDataOrtho.right, projectionDataOrtho.top, projectionDataOrtho.near));

	_AABBOrthographic->SetVerticesColliders(_AABBOrthographic->GenerateAxisAlignedBoundingBoxPos(_dataXYZOrtho),
		_AABBOrthographic->GenerateAxisAlignedBoundingBoxCol());

	cout << "DATA ORTOGRAPHIC FRUSTRUM" << endl;
	for (int i = 0; i < _dataXYZOrtho.size(); i++)
	{
		cout << i << "_[" << _dataXYZOrtho[i].x << "][" << _dataXYZOrtho[i].y << "][" << _dataXYZOrtho[i].z << "]." << endl;
	}
	//-
	//--------------------------------------------------------------------
	#pragma endregion

	#pragma region PERSPECTIVE VIEW
	//0
	_dataXYZPerspective.push_back(glm::vec3(nearMinX, nearMaxY, farZ));
	//1
	_dataXYZPerspective.push_back(glm::vec3(nearMinX, nearMinY, farZ));
	//2
	_dataXYZPerspective.push_back(glm::vec3(nearMaxX, nearMinY, farZ));
	//3
	_dataXYZPerspective.push_back(glm::vec3(nearMaxX, nearMaxY, farZ));
	
	//4
	_dataXYZPerspective.push_back(glm::vec3(farMinX, farMaxY, nearZ));
	//5
	_dataXYZPerspective.push_back(glm::vec3(farMinX, farMinY, nearZ));
	//6
	_dataXYZPerspective.push_back(glm::vec3(farMaxX, farMinY, nearZ));
	//7
	_dataXYZPerspective.push_back(glm::vec3(farMaxX, farMaxY, nearZ));

	cout << "DATA PERSPECTIVE FRUSTRUM" << endl;
	for (int i = 0; i < _dataXYZPerspective.size(); i++)
	{
		cout << i << "_[" << _dataXYZPerspective[i].x << "][" << _dataXYZPerspective[i].y << "][" << _dataXYZPerspective[i].z << "]." << endl;
	}

	_AABBPerspective->SetVerticesColliders(_AABBPerspective->GenerateAABBFrustrumPerspective(_dataXYZPerspective),
		_AABBPerspective->GenerateAxisAlignedBoundingBoxCol());
	#pragma endregion
}

void Camera::UseProjection()
{
	switch (typeProjectionCamera)
	{
	case Perspective:
		SetProjectionPerspective(
			projectionDataPerspective.FOV,
			projectionDataPerspective.aspect,
			projectionDataPerspective.near,
			projectionDataPerspective.front
		);
		break;
	case Ortho:
		SetProjectionOrtho(
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

glm::mat4 Camera::getViewMat()
{
	return _MVP.view;
}
glm::mat4 Camera::getProjMat()
{
	return _MVP.projection;
}

void Camera::SetRotationY(float rotY)
{
	_yaw = rotY;
	UpdateCamera();
	Entity::SetRotationY(rotY);
}

void Camera::SetRotationX(float rotX)
{
	_pitch = rotX;
	UpdateCamera();
	Entity::SetRotationX(rotX);
}

void Camera::RotateCameraX(float speed)
{
	_pitch = _pitch + speed;
	UpdateCamera();
	Entity::SetRotationX(_pitch);
}

void Camera::RotateCameraY(float speed)
{
	_yaw = _yaw + speed;
	UpdateCamera();
	Entity::SetRotationY(_yaw);
}

void Camera::RotateCameraZ(float speed)
{
	//PEDIR AYUDA PARA REALIZAR LA ROTACION EN Z
}
