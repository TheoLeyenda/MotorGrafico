#ifndef ANIMATION_H
#define ANIMATION_H

#include "PrivateClass/Export.h"
#include "Timer.h"
#include "Frame.h"
#include <vector>

using namespace std;

class ENGINE_API Animation
{
private:
	int _currentFrame;
	float _currentTime;
	float _length;
	vector<Frame> _totalFrames;
	vector<vector<Frame>> _animations;
	int _currentAnimation = 0;
public:
	Animation();
	~Animation();
	void Update(Time& time);
	void AddFrame(float u, float v, int width, int heigth,
		int spriteWidth, int spriteHeigth, float timeToAnim, int totalFrames, int countFilas);
	int GetCurrentFrame();
	vector<Frame>& GetAnimation();
	void SetCurrentAnimation(int currentAnimation) { _currentAnimation = currentAnimation; }
};

#endif