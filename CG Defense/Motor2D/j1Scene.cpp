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

#include "stdio.h"

//#pragma comment( lib, "SDL_mixer/libx86/SDL2_mixer.lib" )
j1Scene::j1Scene() : j1Module()
{
	name.create("scene");

	mainmenu = "Main_menu.tmx";
	level1 = "MAGIC_CAVES.tmx";
	level2 = "MAGIC_CAVES_2.tmx";

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
	
	if(App->input->GetKey(SDL_SCANCODE_F6) == KEY_DOWN)			//Save game
		App->LoadGame("save_game.xml");

	if (App->input->GetKey(SDL_SCANCODE_F5) == KEY_DOWN) 
	{		//Save game
		App->SaveGame("save_game.xml");
		game_saved = true;
	}

	if (App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN) 		//Load game
		FadeToBlack(level1);

	if (App->input->GetKey(SDL_SCANCODE_F2) == KEY_DOWN)		//Load game
		FadeToBlack(level2);
	
	if (App->input->GetKey(SDL_SCANCODE_F3) == KEY_DOWN)		//Load game
		FadeToBlack(current_level.GetString());


	//Draw the map
	current_map->Draw();

	return true;
}

// Called each loop iteration
bool j1Scene::PostUpdate()
{
	bool ret = true;

	//Fade
	UpdateFade();

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
	const char* level = current_level.GetString();

	data.append_attribute("level") = level;

	return true;
}

void j1Scene::LoadLevel(const char* level_to_load) {
	
	
	if (p2SString(level_to_load) != current_level)
	{
			App->map->CleanUp();
			App->map->Load(level_to_load);
			current_level = level_to_load;

			int w, h;
			uchar* data = NULL;
			if (App->map->CreateWalkabilityMap(w, h, &data))
				App->pathfinding->SetMap(w, h, data);
			RELEASE_ARRAY(data);

	}
	
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
	switch (button->function)
	{
	case ButtonFunction::LOAD_MAIN_MENU:

		FadeToBlack(mainmenu);
		break;

	case ButtonFunction::LOAD_LEVEL1:

		FadeToBlack(level1);
		break;

	case ButtonFunction::SAVE_GAME:
		App->SaveGame("save_game.xml");
		game_saved = true;
		break;

	case ButtonFunction::LOAD_GAME:
		App->LoadGame("save_game.xml");
		break;

	case ButtonFunction::OPEN_GITHUB:

		ShellExecuteA(NULL, "open", "https://github.com/DevelopmentBeasts/Aegis", NULL, NULL, SW_SHOWNORMAL);
		break;

	}
}

