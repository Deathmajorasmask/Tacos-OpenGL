#include "AnimationsSystemLevels.h"

AnimationsSystemLevels::AnimationsSystemLevels() {
	positionMove = 0.0f;
	rotateMove = 0.0f;
	ctrlAnimMove = true;
	ctrlAnimRotate = true;
	maxPosition = 0.0f;
	minPosition = 0.0f;
};

AnimationsSystemLevels::~AnimationsSystemLevels() {

};

void AnimationsSystemLevels::setAnimation(float _maxPosition, float _minPosition) {
	maxPosition = _maxPosition;
	minPosition = _minPosition;
}

void AnimationsSystemLevels::setAnimationBucle(int animType) {
	switch (animType)
	{
	case 1:
		if (ctrlAnimMove) {
			positionMove += 0.05f;
			if (positionMove >= maxPosition) {
				ctrlAnimMove = false;
			}
		}
		else {
			positionMove -= 0.05f;
			if (positionMove <= minPosition) {
				ctrlAnimMove = true;
			}
		}
		break;
	case 2:
			if (rotateMove >= 360) {
				rotateMove = 0.0f;
			}
			else {
				rotateMove += 0.5f;
			}
		break;
	default:
		break;
	}
}

float AnimationsSystemLevels::getPosition() {
	return positionMove;
}

float AnimationsSystemLevels::getRotation() {
	return rotateMove;
}
