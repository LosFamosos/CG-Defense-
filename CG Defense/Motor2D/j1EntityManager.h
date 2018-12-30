#ifndef __j1ENTITYMANAGER_H__
#define __j1ENTITYMANAGER_H__

#define MAX_ENEMIES 100 

#include "j1Module.h"
#include "p2List.h"
#include "Entities.h"
#include "Enemy.h"
#include "Animation.h"

enum class Stage {
	STAGE_1,
	STAGE_2,
	STAGE_3,
	STAGE_4,
	STAGE_NONE
};

struct EnemyConfig {
	uint speed;
	uint damage;
	uint hp;
};

class j1EntityManager :public j1Module
{
public:

	j1EntityManager();
	~j1EntityManager() {}

	bool Start();
	bool Update(float dt);
	bool CleanUp();

	bool SpawnEnemy(EnemyType enemy_type);

	p2List<Entity*>		entities_list;
	Enemy*				enemies_list[MAX_ENEMIES];

public:
	//Enemy configurations
	EnemyConfig easy_enemy_config;
	EnemyConfig medium_enemy_config;
	EnemyConfig hard_enemy_config;


	Stage actual_stage;

	//Textures for the enemies and the turrets
	SDL_Texture* entities_texture;

	//ENEMY Animations
	Animation easy_enemy_animation;
	Animation medium_enemy_animation;
	Animation hard_enemy_animation;

};


#endif //  __j1ENTITYMANAGER_H__
