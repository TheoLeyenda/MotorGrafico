#include "..\Motor\Src\GameBase.h"
#include "Game.h"

enum TypeDrawShape
{
	Tri,
	Quad,
	Spri,
	MultiplayObjects,
};

//---------------------//
//VALORES DE TESTEO
float speed = 0.05f;
float speedRotation = 0.05f;
float speedScale = 0.05f;

float r = 1.0f;
float g = 0.0f;
float b = 0.0f;
float a = 1.0f;
//---------------------//

TypeDrawShape typeDrawShape = TypeDrawShape::MultiplayObjects;
TypeColorShape typeColorShape = TypeColorShape::VertexColor;
TypeMaterial typeMaterialShape = TypeMaterial::Texture;

Game::Game():GameBase(){}

//---------------------//
Game::~Game(){}
//---------------------//

void Game::InitGame()
{
	//---------------------//
	if(typeDrawShape == TypeDrawShape::Tri)
	{

		spriteTri = new Sprite(GetRenderer(), "res/texturas/bokitaElMasGrandePapa.png");
		tri = new Shape(GetRenderer(), typeMaterialShape);
		tri->SetShape(TypeShape::TRIANGLE, typeColorShape);
		tri->GetRenderer()->SetVertexsAttribShape( typeMaterialShape );
	}
	else if(typeDrawShape == TypeDrawShape::Quad)
	{
		spriteQuad = new Sprite(GetRenderer(), "res/texturas/Facharda.jpg");
		quad = new Shape(GetRenderer(), typeMaterialShape);
		quad->SetShape(TypeShape::QUAD, typeColorShape);
		quad->GetRenderer()->SetVertexsAttribShape(typeMaterialShape);
	}
	else if (typeDrawShape == TypeDrawShape::Spri) 
	{
		//-------------
		player = new Sprite(GetRenderer(), "res/texturas/caminataPiola.png");
		//-------------
		_runLeft = new Animation();
		_runLeft->AddFrame(0.0f, 0.0f, (1536.0f / 6), 256.0f, 1536.0f, 256.0f, 1.0f, 6, 6);
		player->SetAnimation(_runLeft);
		//-------------
		player->GetRenderer()->SetAttribsSprite();
	}
	else if (typeDrawShape == TypeDrawShape::MultiplayObjects) 
	{
		spriteQuad = new Sprite(GetRenderer(), "res/texturas/Facharda.jpg");
		quad = new Shape(GetRenderer(), typeMaterialShape);
		quad->SetShape(TypeShape::QUAD, typeColorShape);
		quad->GetRenderer()->SetVertexsAttribShape(typeMaterialShape);

		//quad->SetPosition(0.5, 0.5f, 0.0f);
		quad->SetScale(0.5f, 0.5f, 0.5f);

		spriteTri = new Sprite(GetRenderer(), "res/texturas/bokitaElMasGrandePapa.png");
		tri = new Shape(GetRenderer(), typeMaterialShape);
		tri->SetShape(TypeShape::TRIANGLE, typeColorShape);
		tri->GetRenderer()->SetVertexsAttribShape(typeMaterialShape);

		tri->SetPosition(-0.5, 0.5f, 0.0f);
		tri->SetScale(0.5f, 0.5f, 0.5f);

		/*player = new Sprite(GetRenderer(), "res/texturas/caminataPiola.png");
		//-------------
		_runLeft = new Animation();
		_runLeft->AddFrame(0.0f, 0.0f, (1536.0f / 6), 256.0f, 1536.0f, 256.0f, 1.0f, 6, 6);
		player->SetAnimation(_runLeft);
		//-------------
		player->GetRenderer()->SetAttribsSprite();
		
		player->SetPosition(0.0f, -0.5f, 0.0f);
		player->SetScale(0.5f, 0.5f, 0.5f);*/

	}
	//---------------------//
}

void Game::UpdateGame(Windows *_window, Renderer *_render, Input *_input)
{
	//---------------------//
	if (typeDrawShape == TypeDrawShape::Tri) {
		tri->Draw(TypeShape::TRIANGLE, 3, _render->GetShader(), _window, tri->GetInternalData().model);
		TempInputs(_window, tri);
		if (typeColorShape == TypeMaterial::Texture) 
			spriteTri->BindSprite();
	}
	else if (typeDrawShape == TypeDrawShape::Quad) 
	{
		quad->Draw(TypeShape::QUAD, 4, _render->GetShader(), _window, quad->GetInternalData().model);
		TempInputs(_window, quad);
		if (typeColorShape == TypeMaterial::Texture)
			spriteQuad->BindSprite();
	}
	else if (typeDrawShape == TypeDrawShape::Spri)
	{
		TempInputs(_window, player);
		player->UpdateSprite(GetTimeClock());
		player->Draw(_window);
		player->BindSprite();
	}
	else if (typeDrawShape == TypeDrawShape::MultiplayObjects) 
	{


		quad->Draw(TypeShape::QUAD, 4, _render->GetShader(), _window, quad->GetInternalData().model);
		//TempInputs(_window, quad);
		if (typeColorShape == TypeMaterial::Texture)
			spriteQuad->BindSprite();

		tri->Draw(TypeShape::TRIANGLE, 3, _render->GetShader(), _window, tri->GetInternalData().model);
		TempInputs(_window, tri);
		if (typeColorShape == TypeMaterial::Texture)
			spriteTri->BindSprite();

		collisionManager->CheckParcialTrigger2D(tri, quad);

		/*TempInputs(_window, player);
		player->UpdateSprite(GetTimeClock());
		player->Draw(_window);
		player->BindSprite();*/
	}
	//---------------------//
}

void Game::DestroyGame()
{
	//---------------------//
	if (quad != NULL)
		delete quad;
	if (tri != NULL)
		delete tri;
	if (spriteTri != NULL)
		delete spriteTri;
	if (spriteQuad != NULL)
		delete spriteQuad;
	if (_runLeft != NULL)
		delete _runLeft;
	if (player != NULL)
		delete player;
	//---------------------//
}

void Game::TempInputs(Windows* windows, Shape* shape)
{
	//---------------------//
	if (typeMaterialShape == TypeMaterial::Color) {
		if (input->GetKey(KeyBoard::KEY_ENTER))
		{
			r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
			g = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
			b = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
			shape->SetSolidColor(r, g, b);
		}
		if (input->GetKey(KeyBoard::KEY_LEFT))
		{
			typeColorShape = TypeColorShape::SolidColor;
			if (shape->GetCurrentShape() == TypeShape::TRIANGLE) {
				shape->SetShape(TypeShape::TRIANGLE, typeColorShape);
				shape->GetRenderer()->SetVertexsAttribShape(typeMaterialShape);
			}
			else if (shape->GetCurrentShape() == TypeShape::QUAD)
			{
				shape->SetShape(TypeShape::QUAD, typeColorShape);
				shape->GetRenderer()->SetVertexsAttribShape(typeMaterialShape);
			}
		}
		if (input->GetKey(KeyBoard::KEY_RIGHT))
		{
			typeColorShape = TypeColorShape::VertexColor;
			if (shape->GetCurrentShape() == TypeShape::TRIANGLE) {
				shape->SetShape(TypeShape::TRIANGLE, typeColorShape);
				shape->GetRenderer()->SetVertexsAttribShape(typeMaterialShape);
			}
			else if (shape->GetCurrentShape() == TypeShape::QUAD)
			{
				shape->SetShape(TypeShape::QUAD, typeColorShape);
				shape->GetRenderer()->SetVertexsAttribShape(typeMaterialShape);
			}
		}
	}
	//INPUT DE MOVIMIENTO
	if (input->GetKey(KeyBoard::KEY_W))
	{
		shape->SetPosition(shape->transform.position.x, shape->transform.position.y + speed , shape->transform.position.z);
	}
	if (input->GetKey(KeyBoard::KEY_S))
	{
		shape->SetPosition(shape->transform.position.x, shape->transform.position.y - speed, shape->transform.position.z);
	}
	if (input->GetKey(KeyBoard::KEY_D))
	{
		shape->SetPosition(shape->transform.position.x + speed, shape->transform.position.y, shape->transform.position.z);
	}
	if (input->GetKey(KeyBoard::KEY_A))
	{
		shape->SetPosition(shape->transform.position.x - speed, shape->transform.position.y, shape->transform.position.z);
	}
	//-------------------//

	//INPUT DE ROTACION
	if (input->GetKey(KeyBoard::KEY_KP_4))
	{
		shape->SetRotationZ(shape->transform.rotation.z + speedRotation);
	}
	if (input->GetKey(KeyBoard::KEY_KP_6))
	{
		shape->SetRotationZ(shape->transform.rotation.z - speedRotation);
	}

	if (input->GetKey(KeyBoard::KEY_KP_1))
	{
		shape->SetRotationY(shape->transform.rotation.y + speedRotation);
	}
	if (input->GetKey(KeyBoard::KEY_KP_3))
	{
		shape->SetRotationY(shape->transform.rotation.y - speedRotation);
	}

	if (input->GetKey(KeyBoard::KEY_KP_7))
	{
		shape->SetRotationX(shape->transform.rotation.x + speedRotation);
	}
	if (input->GetKey(KeyBoard::KEY_KP_9))
	{
		shape->SetRotationX(shape->transform.rotation.x - speedRotation);
	}
	//------------------//

	//INPUT DE ESCALA
	if (input->GetKey(KeyBoard::KEY_KP_8))
	{
		shape->SetScale(shape->transform.scale.x + speedScale, shape->transform.scale.y + speedScale, shape->transform.scale.z + speedScale);
	}
	if (input->GetKey(KeyBoard::KEY_KP_2))
	{
		shape->SetScale(shape->transform.scale.x - speedScale, shape->transform.scale.y - speedScale, shape->transform.scale.z - speedScale);
	}
}
void Game::TempInputs(Windows* windows, Sprite* sprite)
{
	
	//INPUT DE MOVIMIENTO
	if (input->GetKey(KeyBoard::KEY_W))
	{
		sprite->SetPosition(sprite->transform.position.x, sprite->transform.position.y + speed, sprite->transform.position.z);
	}
	if (input->GetKey(KeyBoard::KEY_S))
	{
		sprite->SetPosition(sprite->transform.position.x, sprite->transform.position.y - speed, sprite->transform.position.z);
	}
	if (input->GetKey(KeyBoard::KEY_D))
	{
		sprite->SetPosition(sprite->transform.position.x + speed, sprite->transform.position.y, sprite->transform.position.z);
	}
	if (input->GetKey(KeyBoard::KEY_A))
	{
		sprite->SetPosition(sprite->transform.position.x - speed, sprite->transform.position.y, sprite->transform.position.z);
	}
	//-------------------//

	//INPUT DE ROTACION
	if (input->GetKey(KeyBoard::KEY_KP_4))
	{
		sprite->SetRotationZ(sprite->transform.rotation.z + speedRotation);
	}
	if (input->GetKey(KeyBoard::KEY_KP_6))
	{
		sprite->SetRotationZ(sprite->transform.rotation.z - speedRotation);
	}

	if (input->GetKey(KeyBoard::KEY_KP_1))
	{
		sprite->SetRotationY(sprite->transform.rotation.y + speedRotation);
	}
	if (input->GetKey(KeyBoard::KEY_KP_3))
	{
		sprite->SetRotationY(sprite->transform.rotation.y - speedRotation);
	}

	if (input->GetKey(KeyBoard::KEY_KP_7))
	{
		sprite->SetRotationX(sprite->transform.rotation.x + speedRotation);
	}
	if (input->GetKey(KeyBoard::KEY_KP_9))
	{
		sprite->SetRotationX(sprite->transform.rotation.x - speedRotation);
	}
	//------------------//

	//INPUT DE ESCALA
	if (input->GetKey(KeyBoard::KEY_KP_8))
	{
		sprite->SetScale(sprite->transform.scale.x + speedScale, sprite->transform.scale.y + speedScale, sprite->transform.scale.z + speedScale);
	}
	if (input->GetKey(KeyBoard::KEY_KP_2))
	{
		sprite->SetScale(sprite->transform.scale.x - speedScale, sprite->transform.scale.y - speedScale, sprite->transform.scale.z - speedScale);
	}
}