
#include "SDL/include/SDL.h"
#include "p2Log.h"

#include "j1EntityManager.h"
#include "j1App.h"
#include "j1Textures.h"
#include "j1Input.h"
#include "j1Render.h"
#include "j1Collision.h"

j1EntityManager::j1EntityManager()
{
	actual_stage = Stage::STAGE_NONE;

	//Enemy states
	easy_enemy_config.hp = 20;
	easy_enemy_config.damage = 5;
	easy_enemy_config.speed = 5;

	medium_enemy_config.hp = 20;
	medium_enemy_config.damage = 5;
	medium_enemy_config.speed = 5;

	hard_enemy_config.hp = 20;
	hard_enemy_config.damage = 5;
	hard_enemy_config.speed = 5;

	//Turret animations
	basic_tower_animation.PushBack({0,0,50,50});

	//Animations pushbacks
	easy_enemy_animation.PushBack({0,0,170,98});
	medium_enemy_animation.PushBack({ 0,110,170,98 });
}



bool j1EntityManager::Start()
{
	//Load texutre
	entities_texture = App->tex->Load("textures/esketit.png");
	assert(entities_texture != nullptr, "Entities texture not loaded");

	for (int i = 0; i < MAX_ENEMIES; ++i)
	{
		enemies_list[i] = new Enemy();
		entities_list.add(enemies_list[i]);
	}

	for (int i = 0; i < MAX_TOWERS; ++i)
	{
		tower_list[i] = new Tower();
		entities_list.add(tower_list[i]);
		tower_list[i]->tower_type = TowerType::TOWER_NONE;
		tower_list[i]->animation = &basic_tower_animation;
		tower_list[i]->active = true;
		tower_list[i]->position = {50*i,500};
	}

	return true;
}

bool j1EntityManager::Update(float dt)
{
	//Draw all the entities
	p2List_item<Entity*>* item=nullptr;
	for (item = entities_list.start; item != nullptr; item = item->next)
	{
		if (item->data->active == true)
		{
			item->data->Update();
			item->data->Draw();
		}
	}

	for (int i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies_list[i]->active == true && enemies_list[i]->position.x < -App->render->camera.x)
			enemies_list[i]->Die();
	}

	return true;
}

bool j1EntityManager::CleanUp()
{
	return true;
}

bool j1EntityManager::SpawnEnemy(EnemyType enemy_type)
{
	int i = rand() % 2;

	iPoint new_position = { 500,0 };

	if (i == 0)
		new_position.y = 80;
	else if (i == 1)
		new_position.y = 175;

	Enemy* enemy = nullptr;
	for (int i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies_list[i]->active == false)
		{
			enemy = enemies_list[i];
			
			break;
		}
	}
	if (enemy != nullptr)
	{
		switch (enemy_type)
		{
		case EnemyType::ENEMY_EASY:
			enemy->animation = &easy_enemy_animation;

			enemy->health_points = easy_enemy_config.hp;
			enemy->speed = easy_enemy_config.speed;
			enemy->damage = easy_enemy_config.damage;

			enemy->position = new_position;

			enemy->active = true;

			break;

		case EnemyType::ENEMY_MEDIUM:
			enemy->animation = &medium_enemy_animation;

			enemy->health_points = medium_enemy_config.hp;
			enemy->speed = medium_enemy_config.speed;
			enemy->damage = medium_enemy_config.damage;

			enemy->position = new_position;

			enemy->active = true;
			break;

		case EnemyType::ENEMY_HARD:
			enemy->animation = &medium_enemy_animation;

			enemy->health_points = hard_enemy_config.hp;
			enemy->speed = hard_enemy_config.speed;
			enemy->damage = hard_enemy_config.damage;

			enemy->position = new_position;

			enemy->active = true;
			break;

		case EnemyType::ENEMY_NONE:
			break;
		}
	}
	enemy->collider->active = true;
	enemy->collider->SetPos(new_position.x, new_position.y);
	enemy = nullptr;
	return true;
}

bool j1EntityManager::CreateTower(TowerType tower_type)
{

	Tower* tower = nullptr;
	for (int i = 0; i < MAX_TOWERS; ++i)
	{
		if (tower_list[i]->active == false)
		{
			tower = tower_list[i];

			break;
		}
	}
	tower->tower_type = tower_type;
	switch (tower_type)
	{
	case TowerType::TOWER_BASIC:
		tower->attack_speed = 3000;
		break;
	case TowerType::TOWER_MEDIUM:
		tower->attack_speed = 3000;
		break;
	case TowerType::TOWER_PRO:
		tower->attack_speed = 3000;
		break;
	case TowerType::TOWER_NONE:
		break;
	}
	tower->active = true;
	tower = nullptr;
}

bool j1EntityManager::CleanEnemies()
{

	for (int i = 0; i < MAX_ENEMIES; ++i)
	{
		enemies_list[i]->Die();
	}

	return true;
}

bool j1EntityManager::CleanTowers()
{

	for (int i = 0; i < MAX_TOWERS; ++i)
	{
		tower_list[i]->active = false;
	}

	return true;
}