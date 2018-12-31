
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

	for (int i = 0; i < MAX_ENEMIES; ++i)
	{
		enemies_list[i] = new Enemy();
		entities_list.add(enemies_list[i]);
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

//test
	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
		SpawnEnemy(EnemyType::ENEMY_EASY);

	if (App->input->GetKey(SDL_SCANCODE_J) == KEY_DOWN)
		SpawnEnemy(EnemyType::ENEMY_MEDIUM);


	if (App->input->GetKey(SDL_SCANCODE_M) == KEY_DOWN)
		CleanEnemies();

	return true;
}

bool j1EntityManager::CleanUp()
{
	return true;
}

bool j1EntityManager::SpawnEnemy(EnemyType enemy_type)
{
	iPoint new_position = { 500,rand()%2 * 50 };

	Enemy* enemy = nullptr;
	for (int i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies_list[i]->active == false)
		{
			enemy = enemies_list[i];
			
			LOG("%d", i);
			break;
		}
	}
	if (enemy != nullptr)
	{
		switch (enemy_type)
		{
		case ENEMY_EASY:
			enemy->animation = &easy_enemy_animation;

			enemy->health_points = easy_enemy_config.hp;
			enemy->speed = easy_enemy_config.speed;
			enemy->damage = easy_enemy_config.damage;

			enemy->position = new_position;

			enemy->active = true;

			break;

		case ENEMY_MEDIUM:
			enemy->animation = &medium_enemy_animation;

			enemy->health_points = medium_enemy_config.hp;
			enemy->speed = medium_enemy_config.speed;
			enemy->damage = medium_enemy_config.damage;

			enemy->position = new_position;

			enemy->active = true;
			break;

		case ENEMY_HARD:
			enemy->animation = &medium_enemy_animation;

			enemy->health_points = hard_enemy_config.hp;
			enemy->speed = hard_enemy_config.speed;
			enemy->damage = hard_enemy_config.damage;

			enemy->position = new_position;

			enemy->active = true;
			break;

		case ENEMY_NONE:
			break;
		}
	}
	enemy->collider->active = true;
	enemy->collider->SetPos(new_position.x, new_position.y);
	enemy = nullptr;
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

