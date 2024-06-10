#include "SpinnerEntity.h"

#include "CollisionMask.h"

extern b2World *world;

SpinnerEntity::SpinnerEntity()
{
	typeID = ENTITYSPINNER;
	rotationSpeed = -90.f;
}

void SpinnerEntity::Update(float seconds)
{
	//rotate the spinner 
	/*float angle = body->GetAngle();
	angle += seconds * deg2rad(rotationSpeed);
	position = body->GetPosition();
	body->SetTransform(position, angle);*/

	body->SetAngularVelocity(deg2rad(rotationSpeed));
}

SpinnerEntity * MakeSpinner(float xpos, float ypos, Sprite *sprite)
{
	//make a spinner entity
	SpinnerEntity *spinnerEntity = new SpinnerEntity();

	// Define the spinner body. 
	//We set its position and call the body factory.
	b2BodyDef spinnerBodyDef;
	spinnerBodyDef.type = b2_kinematicBody; //make it a ki nematic body i.e. one moved by us
	spinnerBodyDef.position.Set(xpos/PTM_RATIO, ypos/PTM_RATIO); //set its position in the world

	//make the userdata point back to this entity
	spinnerBodyDef.userData.pointer = reinterpret_cast<uintptr_t>(spinnerEntity);

	spinnerEntity->body = world->CreateBody(&spinnerBodyDef); //create the body and add it to the world

	// Define a polygon shape for our body.

	//The hsape has 9 vertices, but Box2D only allows a max of 8.
	//To get around this, we will make two fixtures, each with half of the shape.
	
	//center of the body, calculated from the sprite.
	//If we use these pre-calculated offsets when setting the vertice positions
	//it will make it easy to get the numbers we want from the paint program coordinates.
	float cx = 57.f / PTM_RATIO;
	float cy = 50.f / PTM_RATIO;

	const int32 count = 5; //how many vertices in the first shape
	const int32 count2 = 6; //how many vertices in the second shape

	b2Vec2 vertices[count]; //array1 to hold the vertices
	b2Vec2 vertices2[count2]; //array2 to hold the vertices
	// This defines a the vertices of the shape in CCW order.
	vertices[0].Set(28.f / PTM_RATIO - cx, 0.f / PTM_RATIO  - cy);
	vertices[1].Set(14.f / PTM_RATIO  - cx, 24.f / PTM_RATIO - cy);
	vertices[2].Set(14.f / PTM_RATIO  - cx, 74.f / PTM_RATIO - cy);
	vertices[3].Set(28.f / PTM_RATIO - cx, 99.f / PTM_RATIO - cy);
	vertices[4].Set(56.f / PTM_RATIO - cx, 99.f / PTM_RATIO - cy);
	
	vertices2[0].Set(56.f / PTM_RATIO - cx, 99.f / PTM_RATIO - cy);
	vertices2[1].Set(99.f / PTM_RATIO - cx, 74.f / PTM_RATIO - cy);
	vertices2[2].Set(112.f / PTM_RATIO - cx, 50.f / PTM_RATIO - cy);
	vertices2[3].Set(99.f / PTM_RATIO - cx, 25.f / PTM_RATIO - cy);
	vertices2[4].Set(57.f / PTM_RATIO - cx, 0.f / PTM_RATIO - cy);
	vertices2[5].Set(28.f / PTM_RATIO - cx, 0.f / PTM_RATIO - cy);


	b2PolygonShape polygonShape;
	polygonShape.Set(vertices, count); //applies the vertices to the polygon shape

	//create the fixture definition - we don't need to save this
	b2FixtureDef fixtureDef;

	//collison masking
	fixtureDef.filter.categoryBits = CMASK_SPINNER;  //this is a spinner
	fixtureDef.filter.maskBits = CMASK_BALL;//it collides wth balls

	// Define the dynamic body fixture.
	fixtureDef.shape = &polygonShape;

	//doesn't matter for kinematic objects...
	fixtureDef.density = 1.0f;

	// Override the default friction.
	fixtureDef.friction = 0.0f;

	//restitution makes us bounce; use 0 for no bounce, 1 for perfect bounce
	fixtureDef.restitution = 0.0;

	// Add the shape to the body. 
	spinnerEntity->body->CreateFixture(&fixtureDef);

	//make second shape
	polygonShape.Set(vertices2, count2); //applies the vertices to the polygon shape
	// Define the dynamic body fixture.
	//fixtureDef.shape = &polygonShape;
	
	// Add the second shape to the body. 
	spinnerEntity->body->CreateFixture(&fixtureDef);

	//add a sprite to the entity
	spinnerEntity->sprite = sprite;
	
	return spinnerEntity;
}