#ifndef __Entity__H__
#define __Entity__H__

#include "p2Point.h"
#include "Animation.h"

class j1EntityManager;
struct SDL_Texture;
struct SDL_Rect;
struct Collider;

enum class EntityType {
	TOWER,
	ENEMY,
	NONE
};

enum class EnemyType {
	ENEMY_EASY,
	ENEMY_MEDIUM,
	ENEMY_HARD,
	ENEMY_NONE
};

enum class TowerType {
	TOWER_BASIC,
	TOWER_MEDIUM,
	TOWER_PRO,
	TOWER_NONE
};

class Entity
{
public:

	Entity(EntityType type);

	//Print the entity
	void Draw();

	virtual bool Update() { return true; }

	//Delete dynamic memory etc
	bool CleanUp();

	void OnCollision(Collider* c1, Collider* c2){}

public:

	//If an entity is not active, basically it doesn't exist
	bool active=false;

	//Position of the entity
	iPoint position;

	//Animation we want to draw
	Animation animation;

protected:

	EntityType entity_type = EntityType::NONE;


	//Texutre
	SDL_Texture* texture=nullptr;
};





#endif // !__Entity__H__
