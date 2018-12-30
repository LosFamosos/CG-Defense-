#ifndef __j1ENTITYMANAGER_H__
#define __j1ENTITYMANAGER_H__

#define MAX_ENEMIES 100 

#include "j1Module.h"
#include "p2List.h"
#include "Entities.h"
#include "Enemy.h"

enum class Stage {
	STAGE_1,
	STAGE_2,
	STAGE_3,
	STAGE_4,
	STAGE_NONE
};

class j1EntityManager :public j1Module
{
public:

	j1EntityManager();
	~j1EntityManager() {}

	bool Start();
	bool Update(float dt);
	bool CleanUp();

	p2List<Entity*>		entities_list;
	Enemy*				enemies_list[MAX_ENEMIES];

public:

	Stage actual_stage;

	//Textures for the enemies and the turrets
	SDL_Texture* entities_texture;

	//ENEMY Animations
	Animation easy_enemy_animation;
	Animation medium_enemy_animation;
	Animation hard_enemy_animation;

};


#endif //  __j1ENTITYMANAGER_H__
