#ifndef __j1SCENE_H__
#define __j1SCENE_H__

#define MIN( a, b ) ( ((a) < (b)) ? (a) : (b) )
#define MAX( a, b ) ( ((a) > (b)) ? (a) : (b) )

#include "j1Module.h"
#include "p2Point.h"
#include "SDL/include/SDL.h"

struct SDL_Texture;
class j1Map;

class UiWindow;
class UiDragBar;
class UiLabel;
class UiImage;

enum class FadeStep {
	fade_none,
	fade_to_black,
	fade_from_black
};

class j1Scene : public j1Module
{
public:

	j1Scene();

	// Destructor
	virtual ~j1Scene();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	// Load / Save
	bool Load(pugi::xml_node&);
	bool Save(pugi::xml_node&)const;

	//Call this function in order to start a fade to load a level
	void FadeToBlack(const char* leveltoload);

	//Called when we want the change the level -> PRIVATE
	void LoadLevel(const char* level_to_load);

	void ButtonAction(UiButton* button);

private:
	
	//Usually does nothing, unless we call the function FadeToBlack()
	//Draws the fade 
	void UpdateFade();

public:

	const char*	mainmenu;
	const char* level1 ;		//Level 1
	const char*	level2 ;		//Level 2

	////Pointer to the current map
	j1Map* current_map=nullptr;

	float playerinitx;
	float playerinity;

	float screeninitx;
	float screeninity;

	pugi::xml_document doc;

	bool SceneLoaded = false;
	bool PlayerExists = false;
	bool findplayer = false;

	//Turns true if we save the game
	bool game_saved=false;

	p2SString current_level;

private:

	//Fade
	uint		fade_time;				//Time for each phase of the fade
	uint		fade_start_time;		//Time at which we start the fade
	SDL_Rect	fade_rect ;				//Square
	FadeStep	fade_step;				//Fading vs unfading
	p2SString	level_to_load;			//Level we want to load
	iPoint	load_position;

};


#endif // __j1SCENE_H__