#include "GameBase.h"
#include "EmptyObject.h"
#include "glew.h"
#include "GLFW/glfw3.h"

vector<Entity*> GameBase::entitysDebugInGame = vector<Entity*>();


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

	motorasoGui = new MotorasoGui(windows);
	
	rootScene = new EmptyObject(render);
	rootScene->SetName("Hierarchy Objects");

	textureMaterialForLight = new Material();
	textureMaterialForLight->SetAmbientMat(glm::vec3(0.5f, 0.5f, 0.5f));
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
	render->SetCurrentShaderUse("Falta Path de VertexShader", "Falta Path de FragmentShader");

#pragma region CREACION Y SETEO DE LUZ DEFAULT
	_lights.clear();
#pragma endregion
	//=====================================
#pragma region CREACION Y SETEO DE CAMARA DEFAULT

	camera->SetDataOrtho(0.0f, windows->GetSizeX(), 0.0f, windows->GetSizeY(), -100.0f, 10000.0f);
	camera->SetDataPerspective(90.0f, windows->GetSizeX(), windows->GetSizeY(), 100.1f, 10000.0f);
	camera->UseProjection();
	camera->SetPosition(300.0f, 100.0f, 200.0f);
	camera->InitCamera(camera->transform.position, glm::vec3(0.0f, 1.0f, 0.0f), -90, 0);
	camera->SetViewFirstPerson();
	camera->SetName("Camera");

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
		if (useDebugWindows)
		{
			//motorasoGui->Begin("Entity Hierarchy", 0, 4);
			motorasoGui->NewFrame();
			motorasoGui->TreeEntitys(rootScene);
			/*for (int i = 0; i < entitysDebugInGame.size(); i++) 
			{
			}*/
		}
		//---------------------//
		HandleCamera();
		//---------------------//
		HandleLight();
		//---------------------//
		UpdateGame(windows, render, input);
		//---------------------//
		if (useDebugWindows)
		{
			motorasoGui->Render();
			//motorasoGui->End();
		}
		//---------------------//	
		glfwPollEvents();
		//---------------------//
		render->EndDraw(windows);
	}
}

void GameBase::DestroyEngine()
{
	glfwTerminate();

	if (motorasoGui != NULL) {
		delete motorasoGui;
		motorasoGui = NULL;
	}
	if (input != NULL) {
		delete input;
		input = NULL;
	}
	if (windows != NULL) {
		delete windows;
		windows = NULL;
	}
	if (render != NULL) {
		delete render;
		render = NULL;
	}
	if (collisionManager != NULL) {
		delete collisionManager;
		collisionManager = NULL;
	}
	if (camera != NULL) {
		delete camera;
		camera = NULL;
	}
	if (textureMaterialDefault != NULL) {
		delete textureMaterialDefault;
		textureMaterialDefault = NULL;
	}
	if (textureMaterialForLight != NULL) {
		delete textureMaterialForLight;
		textureMaterialForLight = NULL;
	}

	while(_lights.size() > 0)
	{
		if (_lights[0] != NULL)
		{
			delete _lights[0];
		}
		_lights.erase(_lights.begin());
	}
}

void GameBase::AddObjectInDenugGame(Entity* entity)
{
	if (entity != NULL) 
	{
		for (int i = 0; i < entitysDebugInGame.size(); i++)
		{
			if (entitysDebugInGame[i] == entity)
			{
				return;
			}
		}
		entitysDebugInGame.push_back(entity);
		rootScene->AddChildren(entity);
	}
}

void GameBase::RemoveObjectInDebugGame(Entity* entity)
{
	int index = -1;
	for (int i = 0; i < entitysDebugInGame.size(); i++) 
	{
		if (entitysDebugInGame[i] == entity) 
		{
			entitysDebugInGame[i]->SetShowInDebug(false);
			index = i;
			i = elementsForVertexCount;
		}
	}
	if (index != -1) {
		entitysDebugInGame.erase(entitysDebugInGame.begin() + index);
		rootScene->RemoveChildren(entity, rootScene);
	}

}

void GameBase::DisableObjectInGame(Entity* entity)
{
	entity->SetIsAlive(false);
}

void GameBase::EnableObjectInGame(Entity * entity)
{
	entity->SetIsAlive(true);
}

Light * GameBase::GetLight(int id)
{
	for (int i = 0; i < _lights.size(); i++) 
	{
		if (_lights[i]->GetMyId() == id) 
		{
			return _lights[i];
		}
	}
	return NULL;
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
	Light* newLight = new Light(render, typeLight, camera);
	if(typeLight == Light::Directional)
		newLight->SetAmbient(glm::vec3(0.5f, 0.5f, 0.5f));
	else
		newLight->SetAmbient(glm::vec3(0.2f, 0.2f, 0.2f));
	
	newLight->SetDiffuse(glm::vec3(0.2f, 0.2f, 0.2f));
	newLight->SetSpecular(glm::vec3(1.5f, 1.5f, 1.5f));
	
	newLight->SetIdLight(id);
	
	newLight->SetPosition(350.0f, 200.0f, 300.0f);
	newLight->SetScale(10.0f, 10.0f, 10.0f);
	
	stringstream ss;
	ss << id;
	string index = ss.str();

	switch (newLight->GetTypeLight())	
	{
	case Light::TypeLight::Directional:
		render->SetLighting(newLight, Light::nr_of_directional_light - 1);
		
		newLight->SetName("Directional Light " + index);
		break;
	case Light::TypeLight::Point:
		render->SetLighting(newLight, Light::nr_of_point_light - 1);
		newLight->SetName("Point Light " + index);
		break;
	case Light::TypeLight::Spot:
		render->SetLighting(newLight, Light::nr_of_spot_light - 1);
		newLight->SetName("Spot Light " + index);
		break;
	}
	cout << "Count pointLight: " << Light::nr_of_point_light << endl;
	cout << "Count directionalLight: " << Light::nr_of_directional_light << endl;
	cout << "Count spotLight: " << Light::nr_of_spot_light << endl;
	
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
				_lights[i]->SetPosition(_lights[i]->transform.position.x + position.x,
					_lights[i]->transform.position.y + position.y, _lights[i]->transform.position.z + position.z);

				i = _lights.size();
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
				system("cls");
				cout << "Count pointLight: " << Light::nr_of_point_light << endl;
				cout << "Count directionalLight: " << Light::nr_of_directional_light << endl;
				cout << "Count spotLight: " << Light::nr_of_spot_light << endl;
			}
		}
	}
}

void GameBase::SetSettingsLightCustom(int id, glm::vec3 direction)
{
	for (int i = 0; i < _lights.size(); i++)
	{
		if (_lights[i] != NULL)
		{
			if (_lights[i]->GetMyId() == id && _lights[i]->GetTypeLight() == Light::TypeLight::Directional)
			{
				_lights[i]->SetDirectionalLightCustom(direction);
			}
		}
	}
}

void GameBase::SetSettingsLightCustom(int id, float linearVal, float quadraticVal, float cutOffValue)
{
	for (int i = 0; i < _lights.size(); i++)
	{
		if (_lights[i] != NULL)
		{
			if (_lights[i]->GetMyId() == id && _lights[i]->GetTypeLight() == Light::TypeLight::Point)
			{
				_lights[i]->SetPointLightCustom(linearVal, quadraticVal, cutOffValue);
			}
		}
	}
}

void GameBase::SetSettingsLightCustom(int id, float linearVal, float quadraticVal, float cutOffValue, float outerCutOffValue)
{
	for (int i = 0; i < _lights.size(); i++)
	{
		if (_lights[i] != NULL)
		{
			if (_lights[i]->GetMyId() == id && _lights[i]->GetTypeLight() == Light::TypeLight::Spot)
			{
				_lights[i]->SetSpotLightCustom(linearVal, quadraticVal, cutOffValue, outerCutOffValue);
			}
		}
	}
}

void GameBase::ChangeColorLight(int id, glm::vec3 color)
{
	for (int i = 0; i < _lights.size(); i++)
	{
		if (_lights[i] != NULL)
		{
			if (_lights[i]->GetMyId() == id)
			{
				_lights[i]->SetColour(color);
			}
		}
	}
}

void GameBase::GetMyLightsID()
{
	for (int i = 0; i < _lights.size(); i++)
	{
		if (_lights[i] != NULL)
		{
			cout << "Light " << i << " in list-> ID : " << _lights[i]->GetMyId() << endl;
			switch (_lights[i]->GetTypeLight())		
			{
			case Light::TypeLight::Directional:
				cout << "TypeLight -> Directional light"<< endl;
				break;
			case Light::TypeLight::Point:
				cout << "TypeLight -> Point light" << endl;
				break;
			case Light::TypeLight::Spot:
				cout << "TypeLight -> Spot light" << endl;
				break;
			}
		}
	}
}

void GameBase::HandleCamera()
{
	switch (camera->GetTypeCamera())
	{
	case TypeCamera::FirstPerson:
		camera->SetViewFirstPerson();
		break;
	case TypeCamera::ThirdPerson:
		camera->SetViewThirdPerson();
		break;
	}

	camera->UseCamera(render->GetCurrentShaderUse(), camera->GetInternalData().localModel);
}

void GameBase::HandleLight()
{
	for (int i = 0; i < _lights.size(); i++)
	{
		if (_lights[i] != NULL)
		{
			_lights[i]->Draw(motorasoGui->GetIfWireFrameIsActive());
		}
	}
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