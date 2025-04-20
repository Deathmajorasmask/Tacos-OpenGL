#pragma once

enum movementsAnimations {
	NONE,
	UPANDDOWN,
	ROTATE360
};

class AnimationsSystemLevels
{
private:
	float positionMove;
	float rotateMove;
	bool ctrlAnimMove;
	bool ctrlAnimRotate;
	float maxPosition;
	float minPosition;
public:
	AnimationsSystemLevels();
	~AnimationsSystemLevels();

	void setAnimation(float _maxPosition, float _minPosition);
	void setAnimationBucle(int animType);
	float getPosition();
	float getRotation();
};