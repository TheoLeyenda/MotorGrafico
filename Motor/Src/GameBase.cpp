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

	//PRUEBA DEL MATERIAL (SPECULAR)
	if (!initGLFW || windows == NULL)
		return INIT_ERROR;

	windows->CheckCreateWindows();
	windows->CreateContextWindows();
	render->GLEWInit();
	render->SetShader();


	light = new Light(render, Light::TypeLight::Directional);
	//light->SetColour(glm::vec3(1.0f, 1.0f, 1.0f));
	light->SetAmbient(glm::vec3(0.2f, 0.2f, 0.2f));
	light->SetDiffuse(glm::vec3(0.5f, 0.5f, 0.5f));
	light->SetSpecular(glm::vec3(1.5f, 1.5f, 1.5f));

	render->SetLighting(light);
	
	glEnable(GL_DEPTH_TEST);

	//SETEO LA DATA DE VISTA DE LA CAMARA
	camera->SetDataOrtho(0.0f, windows->GetSizeX(), 0.0f, windows->GetSizeY(), -100.0f, 1000.0f);
	camera->SetDataPerspective(90.0f, windows->GetSizeX(), windows->GetSizeY(), 0.1f, 1000.0f);
	camera->UseProjection();

	//SETEO POSICION DE LA CAMARA
	camera->SetPosition(300.0f, 100.0f, 200.0f);
	light->SetPosition(300.0f, 200.0f, 50.0f);
	light->SetScale(10.0f, 10.0f, 10.0f);

	//INICIALIZO LA CAMARA PARA PODER UTILIZARLA
	camera->InitCamera(camera->transform.position, glm::vec3(0.0f, 1.0f, 0.0f), -90, 0);
	
	render->SetView(camera);
	
	render->drawCamera(render->GetShaderColor(),camera->GetInternalData().model);

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
		//HandleCamera();
		//render->UseMaterial(currentMaterial);
		//HandleLight(camera);
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
	//if (matCube1 != NULL)
	//	delete matCube1;
	//if (matCube2 != NULL)
	//	delete matCube2;
	//if (matPyramid != NULL)
	//	delete matPyramid;
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
	if (light != NULL)
	{
		render->LightingInfluence(light,camera);
		light->Draw();
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