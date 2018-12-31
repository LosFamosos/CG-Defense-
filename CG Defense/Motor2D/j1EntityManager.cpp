
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

	//Enemy states
	easy_enemy_config.hp = 20;
	easy_enemy_config.damage = 5;
	easy_enemy_config.speed = 6;

	medium_enemy_config.hp = 70;
	medium_enemy_config.damage = 15;
	medium_enemy_config.speed =5;

	hard_enemy_config.hp = 140;
	hard_enemy_config.damage = 30;
	hard_enemy_config.speed = 4;

	//Turret animations
	basic_tower_animation.PushBack({0,0,43,47});
	medium_tower_animation.PushBack({ 49,0,43,47 });
	pro_tower_animation.PushBack({ 96,0,43,47 });

	//Animations pushbacks
	easy_enemy_animation.PushBack({0,47,33,22});
	easy_enemy_animation.PushBack({ 36,47,33,22 });
	easy_enemy_animation.PushBack({ 75,47,33,22 });
	easy_enemy_animation.PushBack({ 111,47,33,22 });
	easy_enemy_animation.loop = true;
	easy_enemy_animation.speed = 0.3f;

	medium_enemy_animation.PushBack({ 0,83,33,22 });
	medium_enemy_animation.PushBack({ 36,83,33,22 });
	medium_enemy_animation.PushBack({ 75,83,33,22 });
	medium_enemy_animation.PushBack({ 111,83,33,22 });
	medium_enemy_animation.loop = true;
	medium_enemy_animation.speed = 0.3f;

	hard_enemy_animation.PushBack({ 0,119,33,22 });
	hard_enemy_animation.PushBack({ 36,119,33,22 });
	hard_enemy_animation.PushBack({ 75,119,33,22 });
	hard_enemy_animation.PushBack({ 111,119,33,22 });
	hard_enemy_animation.loop = true;
	hard_enemy_animation.speed = 0.3f;

}



bool j1EntityManager::Start()
{
	//Load texutre
	entities_texture = App->tex->Load("textures/Turrets&Enemies.png");
	assert(entities_texture != nullptr, "Entities texture not loaded");

	particles_texture = App->tex->Load("gui/atlas.png");

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
		tower_list[i]->position = {80*i,270};
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
	App->tex->UnLoad(entities_texture);
	App->tex->UnLoad(particles_texture);

	return true;
}

bool j1EntityManager::SpawnEnemy(EnemyType enemy_type)
{
	int i = rand() % 2;

	iPoint new_position = { 960,0 };

	if (i == 0)
		new_position.y = 170;
	else if (i == 1)
		new_position.y = 390;

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
			enemy->animation = easy_enemy_animation;

			enemy->health_points = easy_enemy_config.hp;
			enemy->speed = easy_enemy_config.speed;
			enemy->damage = easy_enemy_config.damage;

			enemy->position = new_position;

			enemy->active = true;

			break;

		case EnemyType::ENEMY_MEDIUM:
			enemy->animation = medium_enemy_animation;

			enemy->health_points = medium_enemy_config.hp;
			enemy->speed = medium_enemy_config.speed;
			enemy->damage = medium_enemy_config.damage;

			enemy->position = new_position;

			enemy->active = true;
			break;

		case EnemyType::ENEMY_HARD:
			enemy->animation =hard_enemy_animation;

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
	if (tower != nullptr)
	{
		tower->tower_type = tower_type;
		switch (tower_type)
		{
		case TowerType::TOWER_BASIC:
			tower->tower_type = TowerType::TOWER_BASIC;
			tower->attack_speed = 200;
			tower->animation = basic_tower_animation;
			break;
		case TowerType::TOWER_MEDIUM:
			tower->tower_type = TowerType::TOWER_MEDIUM;
			tower->attack_speed =1000;
			tower->animation = medium_tower_animation;
			break;
		case TowerType::TOWER_PRO:
			tower->tower_type = TowerType::TOWER_PRO;
			tower->attack_speed = 1500;
			tower->animation = pro_tower_animation;
			break;
		case TowerType::TOWER_NONE:
			break;
		}
		tower->active = true;
		tower = nullptr;
	}
	return true;
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