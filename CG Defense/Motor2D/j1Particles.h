#ifndef __MODULEPARTICLES_H__
#define __MODULEPARTICLES_H__

#include "j1Module.h"
#include "Animation.h"
#include "p2Point.h"
#include "j1Collision.h"
#include "j1Audio.h"

#define MAX_ACTIVE_PARTICLES 350

struct SDL_Texture;
struct Collider;

struct Particle
{
	Collider* collider = nullptr;
	Animation anim;
	uint fx = 0;
	iPoint position;
	iPoint speed;
	Uint32 born = 0;
	Uint32 life = 0;
	bool fx_played = false;
	SDL_Texture* texture = nullptr;
	Mix_Chunk* sound = nullptr;
	Particle* end_particle = nullptr;
	iPoint * position_to_attach = nullptr;
	iPoint updated_speed;



	Particle();
	Particle(const Particle& p);
	~Particle();
	bool Update();
};


class j1Particles : public j1Module
{
public:
	j1Particles();
	~j1Particles();

	bool Start();
	bool Update(float dt);
	bool CleanUp();
	void OnCollision(Collider* c1, Collider* c2);

	void AddParticle(const Particle& particle, int x, int y, COLLIDER_TYPE collider_type = COLLIDER_NONE, Uint32 delay = 0, iPoint *position = nullptr, iPoint velocity_ = { 0,0 });

private:

	Particle* active[MAX_ACTIVE_PARTICLES];

public:
	

};

#endif // __MODULEPARTICLES_H__
