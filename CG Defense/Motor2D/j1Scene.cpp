#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Textures.h"
#include "j1Audio.h"
#include "j1Render.h"
#include "j1Window.h"
#include "j1Map.h"
#include "j1Scene.h"
#include "j1Pathfinding.h"
#include "j1Gui.h"
#include "SDL_mixer/include/SDL_mixer.h"
#include "j1EntityManager.h"

#include "stdio.h"

//#pragma comment( lib, "SDL_mixer/libx86/SDL2_mixer.lib" )
j1Scene::j1Scene() : j1Module()
{
	name.create("scene");

	mainmenu = "Main_menu.tmx";

	current_base_health = { 0,0,1100,50 };
	left_base_health = { 0,0,1100,50 };

}

// Destructor
j1Scene::~j1Scene()
{}

// Called before render is available
bool j1Scene::Awake()
{
	LOG("Loading Scene");
	bool ret = true;
	
	return ret;
}

// Called before the first frame
bool j1Scene::Start()
{	
	fade_step = FadeStep::fade_none;
	fade_time = 1000;
	fade_rect.w = App->render->camera.w;
	fade_rect.h = App->render->camera.h;

	current_map = App->map;

	LoadLevel(mainmenu);

	current_time = SDL_GetTicks();
	enemy_spawn_frequency = 500;
	timer = 0;

	game_timer.Start();

	return true;
}

// Called each loop iteration
bool j1Scene::PreUpdate()
{
	
	fade_rect.x = -App->render->camera.x;
	fade_rect.y = -App->render->camera.y;

	return true;
}

// Called each loop iteration
bool j1Scene::Update(float dt)
{
	if (SceneLoaded) {
		SceneLoaded = false;
		PlayerExists = true;//no hace falta pero por si acaso
	}
	
	if (SDL_GetTicks() - timer > enemy_spawn_frequency)
	{
		App->entity_manager->SpawnEnemy(EnemyType::ENEMY_EASY);
		timer = SDL_GetTicks();

	}

	if (App->input->GetKey(SDL_SCANCODE_B) == KEY_DOWN)
		current_base_health.w -= 100;

	//Draw the map
	current_map->Draw();

	game_timer.Update();

	if (current_base_health.w <= 0)
		Restart();

	return true;
}

// Called each loop iteration
bool j1Scene::PostUpdate()
{
	bool ret = true;

	//Fade
	UpdateFade();

	//Draw base health
	App->render->DrawQuad(left_base_health,255,0,0,255);

	App->render->DrawQuad(current_base_health, 0, 255, 0, 255);

	if (App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;
	return ret;
}

// Called before quitting
bool j1Scene::CleanUp()
{

	LOG("Freeing scene");

	return true;
}

// Load Game State
bool j1Scene::Load(pugi::xml_node& data)
{

	FadeToBlack(data.attribute("level").as_string());

	return true;
}

// Save Game State
bool j1Scene::Save(pugi::xml_node& data)const 
{
	

	data.append_attribute("level") = "lmao";

	return true;
}

void j1Scene::LoadLevel(const char* level_to_load) {
	
			App->map->CleanUp();
			App->map->Load(level_to_load);

			int w, h;
			uchar* data = NULL;
			if (App->map->CreateWalkabilityMap(w, h, &data))
				App->pathfinding->SetMap(w, h, data);
			RELEASE_ARRAY(data);
	
}

void j1Scene::UpdateFade() 
{
	if (fade_step == FadeStep::fade_none)
		return;

	static uint phase_fade_time = fade_time/2;

	Uint32 now = SDL_GetTicks() - fade_start_time;
	float normalized = MIN(1.0f, (float)now / (float)fade_time);

	switch (fade_step)
	{
	case FadeStep::fade_to_black:
		if (now >= fade_time)
		{
			App->render->DrawQuad(fade_rect, 0, 0, 0, (Uint8)(normalized * 255.0f));
			LoadLevel(level_to_load.GetString());
			fade_start_time = SDL_GetTicks();
			fade_step = FadeStep::fade_from_black;

		}
		break;
	case FadeStep::fade_from_black:

		normalized = 1.0f - normalized;
		
		if (now > fade_time)
		{
			fade_step = FadeStep::fade_none;
		}
		break;
	}

	App->render->DrawQuad(fade_rect, 0, 0, 0, (Uint8)(normalized * 255.0f));

}

void j1Scene::Restart()
{
	App->entity_manager->CleanEnemies();
	game_timer.start_time = SDL_GetTicks();
	current_base_health.w = 1100;

}

void j1Scene::FadeToBlack(const char* leveltoload)
{
	if (fade_step == FadeStep::fade_none)
	{
		fade_start_time = SDL_GetTicks();
		fade_step = FadeStep::fade_to_black;
		level_to_load = leveltoload;
	}

}

void j1Scene::ButtonAction(UiButton* button)
{
	int i = 0;
}




//TIMER~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

bool GameTimer::Start()
{
	seconds_label = App->gui->AddLabel({ 500,60 }, "");
	minutes_label = App->gui->AddLabel({ 420,60 }, "");

	start_time = SDL_GetTicks();

	return true;
}

void GameTimer::Update()
{
	//TIMER
	current_time = SDL_GetTicks() - start_time;

	int minutes = current_time / 60000;

	sprintf_s(seconds_text, 10, "%.2d", (current_time - minutes * 60000) / 1000);
	seconds_label->text = seconds_text;

	sprintf_s(minutes_text, 10, "%.2d", minutes);
	minutes_label->text = minutes_text;

}

void GameTimer::ChangeState()
{
	minutes_label->active = !minutes_label->active;
	seconds_label->active = !seconds_label->active;
}