#include "Sprite.h"
#include "glew.h"

//============================================
Sprite::Sprite(Renderer *_renderer, Material* _material, const char* filePath):Entity2D(_renderer, _material)
{
	renderer = _renderer;
	material = _material;
	textureImporter.GenerateTexture(filePath, 1, texture, data, width, height, nrChannels);

	InitTextureVertexCoord();
}
//============================================
Sprite::Sprite(Renderer * _renderer, const char* filePath):Entity2D(_renderer)
{
	renderer = _renderer;
	textureImporter.GenerateTexture(filePath, 1, texture, data, width, height, nrChannels);

	InitTextureVertexCoord();
}
//============================================
void Sprite::Draw(Windows* refWindow)
{
	if (renderer != NULL) 
	{
		renderer->BeignDraw();

		renderer->DrawSprite(GL_QUADS, 4, _vbo, renderer->GetShader(), internalData.model);

		renderer->EndDraw(refWindow);
	}
}
//============================================
void Sprite::UpdateSprite(Timer & timer)
{
	if (!animation)
		return;

	animation->Update(timer);

	_currentFrame = animation->GetCurrentFrame();
	if (_currentFrame != _previusFrame) {
		SetTextureCoordinates(animation->GetFrames()[_currentFrame].frameCoords[0].U, animation->GetFrames()[_currentFrame].frameCoords[0].V,
							  animation->GetFrames()[_currentFrame].frameCoords[1].U, animation->GetFrames()[_currentFrame].frameCoords[1].V,
							  animation->GetFrames()[_currentFrame].frameCoords[2].U, animation->GetFrames()[_currentFrame].frameCoords[2].V,
							  animation->GetFrames()[_currentFrame].frameCoords[3].U, animation->GetFrames()[_currentFrame].frameCoords[3].V);
		_previusFrame = _currentFrame;
	}
}
//============================================
void Sprite::SetCurrentTexture(const char* filePath)
{
}
//============================================
void Sprite::SetAnimation(Animation * _animation)
{
	_animation = animation;
	_previusFrame = std::numeric_limits<unsigned int>::max_digits10;
}
//============================================
void Sprite::InitTextureVertexCoord()
{
	textureVertexCoord[0].x = -0.5f;
	textureVertexCoord[1].x = 0.5f;
	textureVertexCoord[2].x = -0.5f;
	textureVertexCoord[3].x = 0.5f;

	textureVertexCoord[0].y = 0.5f;
	textureVertexCoord[1].y = 0.5f;
	textureVertexCoord[2].y = -0.5f;
	textureVertexCoord[3].y = -0.5f;

	textureVertexCoord[0].z = 0.0f;
	textureVertexCoord[1].z = 0.0f;
	textureVertexCoord[2].z = 0.0f;
	textureVertexCoord[3].z = 0.0f;

	textureVertexCoord[0].u = 0.0f;
	textureVertexCoord[1].u = 1.0f;
	textureVertexCoord[2].u = 0.0f;
	textureVertexCoord[3].u = 1.0f;

	textureVertexCoord[0].v = 0.0f;
	textureVertexCoord[1].v = 0.0f;
	textureVertexCoord[2].v = 1.0f;
	textureVertexCoord[3].v = 1.0f;

	glGenBuffers(1, &_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(textureVertexCoord), textureVertexCoord, GL_STATIC_DRAW);
}
//============================================
void Sprite::SetTextureCoordinates(float u0, float v0, float u1, float v1, float u2, float v2, float u3, float v3)
{
	textureVertexCoord[0].u = u0;
	textureVertexCoord[1].u = u1;
	textureVertexCoord[2].u = u2;
	textureVertexCoord[3].u = u3;

	textureVertexCoord[0].v = u0;
	textureVertexCoord[1].v = u1;
	textureVertexCoord[2].v = u2;
	textureVertexCoord[3].v = u3;
}
//============================================
Sprite::~Sprite() {
	glDeleteTextures(1, &texture);
}
//============================================
int Sprite::getWidth()
{
	return width;
}
//============================================
int Sprite::getHeigth()
{
	return height;
}
//============================================
int Sprite::getNrChannels()
{
	return nrChannels;
}
//============================================
void Sprite::BindSprite()
{
	textureImporter.BindTexture(texture);
}
//============================================