#include "GameBase.h"

#include "glew.h"
#include "GLFW/glfw3.h"

GameBase::GameBase() {}
GameBase::~GameBase() {}

int GameBase::InitEngine()
{
	bool initGLFW = glfwInit();

	windows = new Windows(1080, 680, "MOTORASO");
	render = new Renderer();
	input = new Input(windows->GetWindowsPtr());
	camera = new Camera(render, TypeProjectionCamera::Ortho);
	collisionManager = new CollisionManager();

	textureMaterialForLight = new Material();
	textureMaterialForLight->SetAmbientMat(glm::vec3(1.1f, 1.1f, 1.1f));
	textureMaterialForLight->SetDiffuseMat(glm::vec3(0.0f, 0.0f, 0.0f));
	textureMaterialForLight->SetSpecularMat(glm::vec3(0.5f, 0.5f, 0.5f));
	textureMaterialForLight->SetNewShininess(1.0f, 128.0f);

	textureMaterialDefault = new Material();
	textureMaterialDefault->SetAmbientMat(glm::vec3(0.0f, 0.0f, 0.0f));
	textureMaterialDefault->SetDiffuseMat(glm::vec3(0.0f, 0.0f, 0.0f));
	textureMaterialDefault->SetSpecularMat(glm::vec3(0.0f, 0.0f, 0.0f));
	textureMaterialDefault->SetNewShininess(0.25f, 128.0f);

	//PRUEBA DEL MATERIAL (SPECULAR)
	if (!initGLFW || windows == NULL)
		return INIT_ERROR;

	windows->CheckCreateWindows();
	windows->CreateContextWindows();
	render->GLEWInit();
	render->SetShader();

#pragma region CREACION Y SETEO DE LUZ DEFAULT
	_lights.clear();

	//light = new Light(render, Light::TypeLight::Directional);
	//
	//light->SetAmbient(glm::vec3(0.2f, 0.2f, 0.2f));
	//light->SetDiffuse(glm::vec3(0.5f, 0.5f, 0.5f));
	//light->SetSpecular(glm::vec3(1.5f, 1.5f, 1.5f));
	//render->SetLighting(light);
	//light->SetPosition(350.0f, 200.0f, 300.0f);
	//light->SetScale(10.0f, 10.0f, 10.0f);

#pragma endregion
	//=====================================
#pragma region CREACION Y SETEO DE CAMARA DEFAULT

	camera->SetDataOrtho(0.0f, windows->GetSizeX(), 0.0f, windows->GetSizeY(), -100.0f, 10000.0f);
	camera->SetDataPerspective(90.0f, windows->GetSizeX(), windows->GetSizeY(), 100.1f, 10000.0f);
	camera->UseProjection();
	camera->SetPosition(300.0f, 100.0f, 200.0f);
	camera->InitCamera(camera->transform.position, glm::vec3(0.0f, 1.0f, 0.0f), -90, 0);
	render->SetView(camera);

#pragma endregion

	glEnable(GL_DEPTH_TEST);

	return 0;
}

void GameBase::UpdateEngine()
{
	while (!windows->CheckGLFWwindowShouldClose())
	{
		render->BeignDraw();
		//---------------------//
		timeClock.tick();
		//---------------------//
		HandleCamera();
		//---------------------//
		HandleLight(camera);
		//---------------------//
		UpdateGame(windows, render, input);
		//---------------------//	
		glfwPollEvents();
		//---------------------//
		render->EndDraw(windows);
	}
}

void GameBase::DestroyEngine()
{
	glfwTerminate();

	if (input != NULL)
		delete input;
	if (windows != NULL)
		delete windows;
	if (render != NULL)
		delete render;
	if (collisionManager != NULL)
		delete collisionManager;
	if (camera != NULL)
		delete camera;
	if (light != NULL)
		delete light;
	if (textureMaterialDefault != NULL)
		delete textureMaterialDefault;
	if (textureMaterialForLight != NULL)
		delete textureMaterialForLight;

	while(_lights.size() > 0)
	{
		if (_lights[0] != NULL)
		{
			delete _lights[0];
		}
		_lights.erase(_lights.begin());
	}
}

void GameBase::AddLight(Light::TypeLight typeLight, int id)
{
	for (int i = 0; i < _lights.size(); i++)
	{
		if (_lights[i] != NULL)
		{
			if (_lights[i]->GetMyId() == id)
			{
				std::cout << "La luz[" <<i <<"] del vector ya pose el identificador: "<< id << std::endl;
				return;
			}
		}
	}
	Light* newLight = new Light(render, typeLight);
	newLight->SetAmbient(glm::vec3(0.2f, 0.2f, 0.2f));
	newLight->SetDiffuse(glm::vec3(0.5f, 0.5f, 0.5f));
	newLight->SetSpecular(glm::vec3(1.5f, 1.5f, 1.5f));
	newLight->SetIdLight(id);
	newLight->SetPosition(350.0f, 200.0f, 300.0f);
	newLight->SetScale(10.0f, 10.0f, 10.0f);
	render->SetLighting(newLight);
	
	_lights.push_back(newLight);
}

void GameBase::RemoveLight(int id)
{
	for (int i = 0; i < _lights.size(); i++)
	{
		if (_lights[i] != NULL)
		{
			if (_lights[i]->GetMyId() == id) {
				delete _lights[i];
				_lights.erase(_lights.begin() + i);
				i = _lights.size();
			}
		}
	}
}

void GameBase::SetLightPosition(int id, glm::vec3 position)
{
	for (int i = 0; i < _lights.size(); i++)
	{
		if (_lights[i] != NULL)
		{
			if (_lights[i]->GetMyId() == id)
			{
				_lights[i]->SetPosition(position.x, position.y, position.z);
			}
		}
	}
}

void GameBase::SetTypeLightDefault(int id, Light::TypeLight setType)
{
	for (int i = 0; i < _lights.size(); i++)
	{
		if (_lights[i] != NULL)
		{
			if (_lights[i]->GetMyId() == id)
			{
				_lights[i]->SetTypeLightDefault(setType);
			}
		}
	}
}

void GameBase::SetTypeLightCustom(int id, glm::vec3 direction)
{
	for (int i = 0; i < _lights.size(); i++)
	{
		if (_lights[i] != NULL)
		{
			if (_lights[i]->GetMyId() == id)
			{
				_lights[i]->SetDirectionalLightCustom(direction);
			}
		}
	}
}

void GameBase::SetTypeLightCustom(int id, float linearVal, float quadraticVal, float cutOffValue)
{
	for (int i = 0; i < _lights.size(); i++)
	{
		if (_lights[i] != NULL)
		{
			if (_lights[i]->GetMyId() == id)
			{
				_lights[i]->SetPointLightCustom(linearVal, quadraticVal, cutOffValue);
			}
		}
	}
}

void GameBase::SetTypeLightCustom(int id, float linearVal, float quadraticVal, float cutOffValue, float outerCutOffValue)
{
	for (int i = 0; i < _lights.size(); i++)
	{
		if (_lights[i] != NULL)
		{
			if (_lights[i]->GetMyId() == id)
			{
				_lights[i]->SetSpotLightCustom(linearVal, quadraticVal, cutOffValue, outerCutOffValue);
			}
		}
	}
}

void GameBase::HandleCamera()
{
	render->SetView(camera);
	render->drawCamera(render->GetShaderColor(), camera->GetInternalData().model);

	//HACER UN FRAGMENT SHADER QUE CONTENGA EL COLOR Y LA TEXTURA.

	//render->drawCamera(render->GetShaderTexture(), camera->GetInternalData().model);
}

void GameBase::HandleLight(Camera* camera)
{
	for (int i = 0; i < _lights.size(); i++)
	{
		if (_lights[i] != NULL)
		{
			render->LightingInfluence(_lights[i], camera);
			_lights[i]->Draw();
		}
	}
	/*
	if (light != NULL)
	{

		render->LightingInfluence(light,camera);
		light->Draw();
	}
	*/
}

Time& GameBase::GetTimeClock()
{
	return timeClock;
}

Windows * GameBase::GetWindows()
{
	return windows;
}

Renderer * GameBase::GetRenderer()
{
	return render;
}

Input * GameBase::GetInput()
{
	return input;
}