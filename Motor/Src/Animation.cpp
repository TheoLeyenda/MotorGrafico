#include "Animation.h"
#include <iostream>



Animation::Animation()
{
	_currentTime = 0;
	_currentFrame = 0;
	_length = 200;
}

Animation::~Animation(){}

void Animation::Update(Time & timer)
{
	_currentTime = (timer.deltaTime() * _length);
	
	while (_currentTime >= _length){
		_currentTime -= _length;
	}

	std::cout << "CurrenTime time anim: "<<_currentTime << std::endl;

	float frameLength = _length / _frames.size();
	_currentFrame = static_cast<int>(_currentTime / frameLength);
}

/*
float textureVertex[] = {
	//    x     y     z     u     v
	   -0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
		0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
		0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
	   -0.5f, -0.5f, 0.0f, 0.0f, 0.0f
};
*/
void Animation::AddFrame(float u, float v, int width, int heigth, int spriteWidth, int spriteHeigth, int timeToAnim, int totalFrames, int countFramesForFilas)
{
	_length = timeToAnim * 200;

	float index_X = 0;
	float index_Y = 0;
	Frame frame;
	for (int i = 0; i < totalFrames; i++){
		//--------
		frame.frameCoords[0].U = ((u + index_X) / spriteWidth);
		frame.frameCoords[0].V = ((heigth + index_Y) / spriteHeigth);
		//--------
		cout << frame.frameCoords[0].U << endl;
		cout << frame.frameCoords[0].V << endl;

		frame.frameCoords[1].U = (((u + index_X) + width) / spriteWidth);
		frame.frameCoords[1].V = ((heigth + index_Y) / spriteHeigth);

		cout << frame.frameCoords[1].U << endl;
		cout << frame.frameCoords[1].V << endl;
		//--------
		frame.frameCoords[2].U = (((u + index_X) + width) / spriteWidth);
		frame.frameCoords[2].V = ((v + index_Y) / spriteHeigth);

		cout << frame.frameCoords[2].U << endl;
		cout << frame.frameCoords[2].V << endl;
		//--------
		frame.frameCoords[3].U = ((u + index_X) / spriteWidth);
		frame.frameCoords[3].V = ((v + index_Y) / spriteHeigth);

		cout << frame.frameCoords[3].U << endl;
		cout << frame.frameCoords[3].V << endl;
		//--------
		_frames.push_back(frame);
		index_X += width;

		if (i > 0) {
			if (i % countFramesForFilas == 0)
				index_Y += heigth;
		}
		cout << "-------------------------------------------------" << endl;
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
