#ifndef __Entity__H__
#define __Entity__H__

#include "p2Point.h"

class j1EntityManager;
struct SDL_Texture;
struct SDL_Rect;
class Animation;

enum class EntityType {
	TOWER,
	ENEMY,
	NONE
};

enum EnemyType {
	ENEMY_EASY,
	ENEMY_MEDIUM,
	ENEMY_HARD,
	ENEMY_NONE
};

class Entity
{
public:

	Entity(EntityType type);

	//Print the entity
	void Draw();

	bool Update() { return true; }

	//Delete dynamic memory etc
	bool CleanUp();

public:

	//If an entity is not active, basically it doesn't exist
	bool active=false;

	//Position of the entity
	iPoint position;

protected:

	EntityType entity_type = EntityType::NONE;

	//Animation we want to draw
	Animation* animation= nullptr;

	//Texutre
	SDL_Texture* texture=nullptr;
};





#endif // !__Entity__H__
