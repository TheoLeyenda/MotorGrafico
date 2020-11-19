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

bool enableVertexTexture = false;
//---------------------//

TypeColorShape typeColorShape = TypeColorShape::SolidColor;

Game::Game():GameBase(){}

//---------------------//
Game::~Game(){}
//---------------------//

void Game::InitGame()
{
	shape2 = new Shape(render, TypeShape::TRIANGLE, "res/texturas/Facharda.jpg");
	//shape2 = new Shape(render, TypeShape::TRIANGLE, typeColorShape);
	shape2->SetPosition(-0.7, 0.0f, 0.0f);
	shape2->SetScale(0.5f, 0.5f, 0.5f);

	player = new Sprite(GetRenderer(), "res/texturas/PlayerShit.png", true);
	//-------------
	_animations = new Animation();
	
	float durationAnim = 0.75f;

	// ANIMACION CAMINATA HACIA ARRIBA
	_animations->AddFrame((480 - 60 * 8), 0.0f, 60, 60, 480, 240, durationAnim);
	_animations->AddFrame((480 - 60 * 7), 0.0f, 60, 60, 480, 240, durationAnim);
	_animations->AddFrame((480 - 60 * 6), 0.0f, 60, 60, 480, 240, durationAnim);
	_animations->AddFrame((480 - 60 * 5), 0.0f, 60, 60, 480, 240, durationAnim);
	_animations->AddFrame((480 - 60 * 4), 0.0f, 60, 60, 480, 240, durationAnim);
	_animations->AddFrame((480 - 60 * 3), 0.0f, 60, 60, 480, 240, durationAnim);
	_animations->AddFrame((480 - 60 * 2), 0.0f, 60, 60, 480, 240, durationAnim);
	_animations->AddFrame((480 - 60 * 1), 0.0f, 60, 60, 480, 240, durationAnim);
	_animations->AddAnimation();

	// ANIMACION CAMINATA HACIA DERECHA
	_animations->AddFrame((480 - 60 * 8), 60, 60, 60, 480, 240, durationAnim);
	_animations->AddFrame((480 - 60 * 7), 60, 60, 60, 480, 240, durationAnim);
	_animations->AddFrame((480 - 60 * 6), 60, 60, 60, 480, 240, durationAnim);
	_animations->AddFrame((480 - 60 * 5), 60, 60, 60, 480, 240, durationAnim);
	_animations->AddFrame((480 - 60 * 4), 60, 60, 60, 480, 240, durationAnim);
	_animations->AddFrame((480 - 60 * 3), 60, 60, 60, 480, 240, durationAnim);
	_animations->AddFrame((480 - 60 * 2), 60, 60, 60, 480, 240, durationAnim);
	_animations->AddFrame((480 - 60 * 1), 60, 60, 60, 480, 240, durationAnim);
	_animations->AddAnimation();

	// ANIMACION CAMINATA HACIA IZQUIERDA
	_animations->AddFrame((480 - 60 * 8), 120, 60, 60, 480, 240, durationAnim);
	_animations->AddFrame((480 - 60 * 7), 120, 60, 60, 480, 240, durationAnim);
	_animations->AddFrame((480 - 60 * 6), 120, 60, 60, 480, 240, durationAnim);
	_animations->AddFrame((480 - 60 * 5), 120, 60, 60, 480, 240, durationAnim);
	_animations->AddFrame((480 - 60 * 4), 120, 60, 60, 480, 240, durationAnim);
	_animations->AddFrame((480 - 60 * 3), 120, 60, 60, 480, 240, durationAnim);
	_animations->AddFrame((480 - 60 * 2), 120, 60, 60, 480, 240, durationAnim);
	_animations->AddFrame((480 - 60 * 1), 120, 60, 60, 480, 240, durationAnim);
	_animations->AddAnimation();

	// ANIMACION CAMINATA HACIA ABAJO
	_animations->AddFrame((480 - 60 * 8), 180, 60, 60, 480, 240, durationAnim);
	_animations->AddFrame((480 - 60 * 7), 180, 60, 60, 480, 240, durationAnim);
	_animations->AddFrame((480 - 60 * 6), 180, 60, 60, 480, 240, durationAnim);
	_animations->AddFrame((480 - 60 * 5), 180, 60, 60, 480, 240, durationAnim);
	_animations->AddFrame((480 - 60 * 4), 180, 60, 60, 480, 240, durationAnim);
	_animations->AddFrame((480 - 60 * 3), 180, 60, 60, 480, 240, durationAnim);
	_animations->AddFrame((480 - 60 * 2), 180, 60, 60, 480, 240, durationAnim);
	_animations->AddFrame((480 - 60 * 1), 180, 60, 60, 480, 240, durationAnim);
	_animations->AddAnimation();

	player->SetAnimation(_animations);

	
	//-------------
	player->GetRenderer()->SetAttribsSprite();

	player->SetPosition(-0.6f, -0.5f, 0.0f);
	player->SetScale(0.5f, 0.5f, 0.5f);
	player->SetSizeCollider2D(glm::vec3(0.25f, 0.402f, 0.5f));

	player2 = new Sprite(GetRenderer(), "res/texturas/PlayerShit.png", true);
	//-------------
	_animations2 = new Animation();
	_animations2->AddFrame(0.0f, 0.0f, (480 / 8), (240 / 4), 480, 240, durationAnim, 32, 8);
	_animations2->SetCurrentAnimation(1);

	player2->SetAnimation(_animations2);
	//-------------
	player2->GetRenderer()->SetAttribsSprite();

	player2->SetPosition(0.6f, -0.5f, 0.0f);
	player2->SetScale(0.5f, 0.5f, 0.5f);
	player2->SetSizeCollider2D(glm::vec3(0.25f, 0.402f, 0.5f));

	//shape1 = new Shape(render, TypeShape::QUAD, "res/texturas/Facharda.jpg");
	shape1 = new Shape(render, TypeShape::QUAD, typeColorShape);
	shape1->SetPosition(0.7, 0.0f, 0.0f);
	shape1->SetScale(0.5f, 0.5f, 0.5f);

	bokita = new Sprite(GetRenderer(), "res/texturas/bokitaElMasGrandePapa.png", false);
	bokita->GetRenderer()->SetAttribsSprite();
	bokita->SetScale(2.0f, 3.0f, 2.0f);

	//int scaledTextureX = bokita->transform.scale.x + 100;
	//int scaledTextureY = bokita->transform.scale.y + 100;
	//bokita->SetTextureCoordinates(0.0f + scaledTextureX, 1.0f + scaledTextureY,
	//							  1.0f + scaledTextureX, 1.0f + scaledTextureY,
	//							  1.0f + scaledTextureX, 0.0f + scaledTextureY,
	//							  0.0f + scaledTextureX, 0.0f + scaledTextureY);
}

void Game::UpdateGame(Windows *_window, Renderer *_render, Input *_input)
{
	timeClock.FPS();

	bokita->Draw();

	shape2->Draw(TypeShape::TRIANGLE,3);
	shape1->Draw(TypeShape::QUAD, 4);
	

	player->UpdateSprite(GetTimeClock());
	player->Draw();

	player2->UpdateSprite(GetTimeClock());
	player2->Draw();

	TempInputsPlayer1(windows, player);
	TempInputsPlayer2(windows, player2);
	
	collisionManager->CheckCollision2D(player, shape2, speed, player->GetBoxColliderSize2D(), shape2->GetBoxColliderSize2D());
	collisionManager->CheckCollision2D(player, shape1, speed, player->GetBoxColliderSize2D(), shape1->GetBoxColliderSize2D());

	collisionManager->CheckCollision2D(player2, shape2, speed, player2->GetBoxColliderSize2D(), shape2->GetBoxColliderSize2D());
	collisionManager->CheckCollision2D(player2, shape1, speed, player2->GetBoxColliderSize2D(), shape1->GetBoxColliderSize2D());

	collisionManager->CheckCollision2D(player, player2, speed, player->GetBoxColliderSize2D(), player2->GetBoxColliderSize2D());
	collisionManager->CheckCollision2D(player2, player, speed, player2->GetBoxColliderSize2D(), player->GetBoxColliderSize2D());

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
	if (_animations2 != NULL)
		delete _animations2;
	if (player != NULL)
		delete player;
	if (player2 != NULL)
		delete player2;
	if (bokita != NULL)
		delete bokita;
	//---------------------//
}
void Game::TempColorInput(Windows* windows, Shape* shape)
{
	//---------------------//
		if (input->GetKey(KeyBoard::KEY_ENTER))
		{
			r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
			g = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
			b = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
			shape->SetSolidColor(r, g, b);
		}

		if (input->GetKey(KeyBoard::KEY_KP_0))
		{
			typeColorShape = TypeColorShape::SolidColor;
			if (shape->GetCurrentShape() == TypeShape::TRIANGLE) {
				shape->SetShape(TypeShape::TRIANGLE, typeColorShape);
				shape->SetVertexsAttribShape(TypeMaterial::Color);
			}
			else if (shape->GetCurrentShape() == TypeShape::QUAD)
			{
				shape->SetShape(TypeShape::QUAD, typeColorShape);
				shape->SetVertexsAttribShape(TypeMaterial::Color);
			}
		}
		if (input->GetKey(KeyBoard::KEY_KP_ENTER))
		{
			typeColorShape = TypeColorShape::VertexColor;
			if (shape->GetCurrentShape() == TypeShape::TRIANGLE) {
				shape->SetShape(TypeShape::TRIANGLE, typeColorShape);
				shape->SetVertexsAttribShape(TypeMaterial::Color);
			}
			else if (shape->GetCurrentShape() == TypeShape::QUAD)
			{
				shape->SetShape(TypeShape::QUAD, typeColorShape);
				shape->SetVertexsAttribShape(TypeMaterial::Color);
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
void Game::TempInputsPlayer1(Windows* windows, Sprite* sprite)
{
	
	//INPUT DE MOVIMIENTO
	if (input->GetKey(KeyBoard::KEY_W))
	{
		sprite->SetPosition(sprite->transform.position.x, sprite->transform.position.y + speed, sprite->transform.position.z);
		player->SetCurrentAnimationIndex(0);
	}
	if (input->GetKey(KeyBoard::KEY_S))
	{
		sprite->SetPosition(sprite->transform.position.x, sprite->transform.position.y - speed, sprite->transform.position.z);
		player->SetCurrentAnimationIndex(3);
	}
	if (input->GetKey(KeyBoard::KEY_D))
	{
		sprite->SetPosition(sprite->transform.position.x + speed, sprite->transform.position.y, sprite->transform.position.z);
		player->SetCurrentAnimationIndex(1);
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

void Game::TempInputsPlayer2(Windows * windows, Sprite * sprite)
{
	//INPUT DE MOVIMIENTO
	if (input->GetKey(KeyBoard::KEY_UP))
	{
		sprite->SetPosition(sprite->transform.position.x, sprite->transform.position.y + speed, sprite->transform.position.z);
		player2->SetCurrentAnimationIndex(0);
	}
	if (input->GetKey(KeyBoard::KEY_DOWN))
	{
		sprite->SetPosition(sprite->transform.position.x, sprite->transform.position.y - speed, sprite->transform.position.z);
		player2->SetCurrentAnimationIndex(3);
	}
	if (input->GetKey(KeyBoard::KEY_RIGHT))
	{
		sprite->SetPosition(sprite->transform.position.x + speed, sprite->transform.position.y, sprite->transform.position.z);
		player2->SetCurrentAnimationIndex(1);
	}
	if (input->GetKey(KeyBoard::KEY_LEFT))
	{
		sprite->SetPosition(sprite->transform.position.x - speed, sprite->transform.position.y, sprite->transform.position.z);
		player2->SetCurrentAnimationIndex(2);
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
