#pragma once

#include "Entity.h"

enum class BrickColour { YELLOW, ORANGE, RED, PURPLE, BLUE};

//externed sprites
extern Sprite *redBrickSprite;
extern Sprite *yellowBrickSprite;
extern Sprite *orangeBrickSprite;
extern Sprite *purpleBrickSprite;
extern Sprite* blueBrickSprite;

class BrickEntity : public Entity
{
public:
	BrickColour colour;
	float x, y;
	BrickEntity()
	{
		typeID = ENTITYBRICK;
		colour = BrickColour::RED;
	}

	bool HandleCollision();
};

BrickEntity * MakeBrick(BrickColour type, float xpos, float ypos);