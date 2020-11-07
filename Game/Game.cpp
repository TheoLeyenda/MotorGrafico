#include "..\Motor\Src\GameBase.h"
#include "Game.h"

enum TypeDrawShape
{
	Tri,
	Quad,
	Spri,
	MultiplayObjects,
};
enum TypeCollisionCheck 
{
	Collision,
	Trigger,
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

TypeColorShape typeColorShape = TypeColorShape::SolidColor;
TypeMaterial typeMaterialShape = TypeMaterial::Texture;

Game::Game():GameBase(){}

//---------------------//
Game::~Game(){}
//---------------------//

void Game::InitGame()
{
	if(typeMaterialShape == TypeMaterial::Texture)
		shape2 = new Shape(render, TypeShape::TRIANGLE, "res/texturas/bokitaElMasGrandePapa.png");
	else
		shape2 = new Shape(render, TypeShape::TRIANGLE, typeColorShape);
	shape2->SetPosition(-0.7, 0.0f, 0.0f);
	shape2->SetScale(0.5f, 0.5f, 0.5f);

	if (typeMaterialShape == TypeMaterial::Texture) {
		player = new Sprite(GetRenderer(), "res/texturas/PlayerShit.png", true);
		//-------------
		_animations = new Animation();
		_animations->AddFrame(0.0f, 0.0f, (480 / 8), (240 / 4), 480, 240, 1.0f, 32, 8);
		_animations->SetCurrentAnimation(1);

		player->SetAnimation(_animations);
		//-------------
		player->GetRenderer()->SetAttribsSprite();

		player->SetPosition(0.0f, -0.5f, 0.0f);
		player->SetScale(0.5f, 0.5f, 0.5f);
		player->SetSizeCollider2D(glm::vec3(0.25f, 0.402f, 0.5f));
	}

	if (typeMaterialShape == TypeMaterial::Texture)
		shape1 = new Shape(render, TypeShape::QUAD, "res/texturas/Facharda.jpg");
	else
		shape1 = new Shape(render, TypeShape::QUAD, typeColorShape);
	shape1->SetPosition(0.7, 0.0f, 0.0f);
	shape1->SetScale(0.5f, 0.5f, 0.5f);

}

void Game::UpdateGame(Windows *_window, Renderer *_render, Input *_input)
{
	shape2->Draw(TypeShape::TRIANGLE,3, render->GetShader(), windows, shape2->GetInternalData().model);
	shape1->Draw(TypeShape::QUAD, 4, render->GetShader(), windows, shape1->GetInternalData().model);
	
	if (typeMaterialShape == TypeMaterial::Texture) 
	{
		player->UpdateSprite(GetTimeClock());
		player->Draw(_window);

		TempInputs(windows, player);
		collisionManager->CheckCollision2D(player, shape2, speed, player->GetBoxColliderSize2D(), shape2->GetBoxColliderSize2D());
		collisionManager->CheckCollision2D(player, shape1, speed, player->GetBoxColliderSize2D(), shape1->GetBoxColliderSize2D());
	}
	TempColorInput(windows, shape1);
	TempColorInput(windows, shape2);
	
}

void Game::DestroyGame()
{
	//---------------------//
	if (shape1 != NULL)
		delete shape1;
	if (shape2 != NULL)
		delete shape2;
	if (_animations != NULL)
		delete _animations;
	if (player != NULL)
		delete player;
	//---------------------//
}
void Game::TempColorInput(Windows* windows, Shape* shape) 
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
				shape->SetVertexsAttribShape(typeMaterialShape);
			}
			else if (shape->GetCurrentShape() == TypeShape::QUAD)
			{
				shape->SetShape(TypeShape::QUAD, typeColorShape);
				shape->SetVertexsAttribShape(typeMaterialShape);
			}
		}
		if (input->GetKey(KeyBoard::KEY_RIGHT))
		{
			typeColorShape = TypeColorShape::VertexColor;
			if (shape->GetCurrentShape() == TypeShape::TRIANGLE) {
				shape->SetShape(TypeShape::TRIANGLE, typeColorShape);
				shape->SetVertexsAttribShape(typeMaterialShape);
			}
			else if (shape->GetCurrentShape() == TypeShape::QUAD)
			{
				shape->SetShape(TypeShape::QUAD, typeColorShape);
				shape->SetVertexsAttribShape(typeMaterialShape);
			}
		}
	}

}
void Game::TempInputs(Windows* windows, Shape* shape)
{
	
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
		_animations->SetCurrentAnimation(0);
	}
	if (input->GetKey(KeyBoard::KEY_S))
	{
		sprite->SetPosition(sprite->transform.position.x, sprite->transform.position.y - speed, sprite->transform.position.z);
		player->SetCurrentAnimationIndex(3);
	}
	if (input->GetKey(KeyBoard::KEY_D))
	{
		sprite->SetPosition(sprite->transform.position.x + speed, sprite->transform.position.y, sprite->transform.position.z);
		_animations->SetCurrentAnimation(1);
	}
	if (input->GetKey(KeyBoard::KEY_A))
	{
		sprite->SetPosition(sprite->transform.position.x - speed, sprite->transform.position.y, sprite->transform.position.z);
		player->SetCurrentAnimationIndex(2);
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