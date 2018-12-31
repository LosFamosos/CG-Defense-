#ifndef __j1ENTITYMANAGER_H__
#define __j1ENTITYMANAGER_H__

#define MAX_ENEMIES 100 
#define MAX_TOWERS 8

#include "j1Module.h"
#include "p2List.h"
#include "Entities.h"
#include "Enemy.h"
#include "Animation.h"
#include "Tower.h"

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
	bool CreateTower(TowerType tower_type);

	bool CleanEnemies();
	bool CleanTowers();

	
public:

	//Esketit
	p2List<Entity*>		entities_list;
	Enemy*				enemies_list[MAX_ENEMIES];
	Tower*				tower_list[MAX_TOWERS];


	//Enemy configurations
	EnemyConfig easy_enemy_config;
	EnemyConfig medium_enemy_config;
	EnemyConfig hard_enemy_config;

	//Textures for the enemies and the turrets
	SDL_Texture* entities_texture;
	SDL_Texture* particles_texture;

	//TOWERS animations
	Animation basic_tower_animation;
	Animation medium_tower_animation;
	Animation pro_tower_animation;


	//ENEMY Animations
	Animation easy_enemy_animation;
	Animation medium_enemy_animation;
	Animation hard_enemy_animation;

};


#endif //  __j1ENTITYMANAGER_H__
