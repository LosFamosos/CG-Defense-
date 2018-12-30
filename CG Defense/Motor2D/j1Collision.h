#ifndef __j1Collision_H__
#define __j1Collision_H__

#define MAX_COLLIDERS 1000

#include "j1Module.h"
#include "SDL/include/SDL.h"
#include "p2Defs.h"
#include "p2Log.h"
#include "p2Point.h"
#include "j1Module.h"
#include "j1App.h"

class j1Entity;

enum COLLIDER_TYPE
{
	COLLIDER_NONE = -1,
	COLLIDER_BASE,
	COLLIDER_ENEMY,
	COLLIDER_TURRETSHOT,
	COLLIDER_MAX
};

struct Collider
{
	SDL_Rect rect;
	bool active;
	bool to_delete = false;
	COLLIDER_TYPE type;
	j1Module* callback = nullptr;

	Collider(SDL_Rect rect, COLLIDER_TYPE type, j1Module *callback = nullptr) :
		rect(rect), type(type), callback(callback) {}

	void SetPos(int x, int y)
	{
		rect.x = x;
		rect.y = y;
	}

	bool CheckCollision(const SDL_Rect& r) const;
};

class j1Collision : public j1Module
{
public:

	j1Collision();
	~j1Collision();

	bool PreUpdate() override;
	bool Update(float dt) override;
	bool CleanUp() override;

	Collider* AddCollider(SDL_Rect rect, COLLIDER_TYPE type, j1Module* callback = nullptr);
	Collider* AddEntCollider(SDL_Rect rect, COLLIDER_TYPE type, j1Entity* entity_callback = nullptr);
	void DebugDraw();



private:

	Collider * colliders[MAX_COLLIDERS];
	bool matrix[COLLIDER_MAX][COLLIDER_MAX];
	bool debug = false;
};

#endif

