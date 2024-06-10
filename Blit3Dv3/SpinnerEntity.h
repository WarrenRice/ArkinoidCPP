#pragma once

#include "Entity.h"

//Spinners are just obstacles to bounce the balls off.

class SpinnerEntity : public Entity
{
public:
	float rotationSpeed;

	SpinnerEntity();
	void Update(float seconds);
};

SpinnerEntity * MakeSpinner(float xpos, float ypos, Sprite *sprite);