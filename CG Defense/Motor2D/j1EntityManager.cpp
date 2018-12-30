#include "j1EntityManager.h"
#include "j1App.h"
#include "j1Textures.h"

j1EntityManager::j1EntityManager()
{
	actual_stage = Stage::STAGE_NONE;
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

	return true;
}

bool j1EntityManager::CleanUp()
{
	return true;
}