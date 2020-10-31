#include "Animation.h"
#include <iostream>



Animation::Animation()
{
	_currentTime = 0;
	_currentFrame = 0;
	_length = 1000;
}

Animation::~Animation(){}

void Animation::Update(Timer & timer)
{
	float deltaTime = timer.GetGlobalTime()/ _length;
	_currentTime += deltaTime * _length;
	
	while (_currentTime > _length){
		_currentTime -= _length;
	}

	//std::cout << "CurrenTime anim: "<<_currentTime << std::endl;

	float frameLength = _length / _frames.size();
	_currentFrame = static_cast<int>(_currentTime / frameLength);
}

void Animation::AddFrame(float u, float v, int width, int heigth, int spriteWidth, int spriteHeigth, int timeToAnim)
{
	_length = timeToAnim * 1000;

	Frame frame;

	//--------
	frame.frameCoords[0].U = (u / spriteWidth);
	frame.frameCoords[0].V = (v / spriteHeigth);
	//--------
	frame.frameCoords[1].U = ((u + width) / spriteWidth);
	frame.frameCoords[1].V = (v / spriteHeigth);
	//--------
	frame.frameCoords[2].U = (u / spriteWidth);
	frame.frameCoords[2].V = ((v + heigth)/ spriteHeigth);
	//--------
	frame.frameCoords[3].U = ((u + width ) / spriteWidth);
	frame.frameCoords[3].V = ((v + heigth) / spriteHeigth);
	//--------

	_frames.push_back(frame);
}

void Animation::AddFrame(float u, float v, int width, int heigth, int spriteWidth, int spriteHeigth, int timeToAnim, int frames)
{
	_length = timeToAnim * 1000;

	float index = 0;
	Frame frame;
	for (int i = 0; i < frames; i++){
		//--------
		frame.frameCoords[0].U = ((u + index) / spriteWidth);
		frame.frameCoords[0].V = (v / spriteHeigth);
		//--------
		cout << frame.frameCoords[0].U << endl;
		cout << frame.frameCoords[0].V << endl;

		frame.frameCoords[1].U = (((u + index) + width) / spriteWidth);
		frame.frameCoords[1].V = (v / spriteHeigth);

		cout << frame.frameCoords[1].U << endl;
		cout << frame.frameCoords[1].V << endl;
		//--------
		frame.frameCoords[2].U = ((u + index) / spriteWidth);
		frame.frameCoords[2].V = ((v + heigth) / spriteHeigth);

		cout << frame.frameCoords[2].U << endl;
		cout << frame.frameCoords[2].V << endl;
		//--------
		frame.frameCoords[3].U = (((u + index) + width) / spriteWidth);
		frame.frameCoords[3].V = ((v + heigth) / spriteHeigth);

		cout << frame.frameCoords[3].U << endl;
		cout << frame.frameCoords[3].V << endl;
		//--------
		_frames.push_back(frame);
		index += width;
	}

}

int Animation::GetCurrentFrame()
{
	return _currentFrame;
}

vector<Frame>& Animation::GetFrames()
{
	return _frames;
}
