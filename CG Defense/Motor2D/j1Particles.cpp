#include <math.h>
#include "j1App.h"
#include "j1Textures.h"
#include "j1Render.h"
#include "j1Collision.h"
#include "j1Particles.h"

#include "SDL/include/SDL_timer.h"

j1Particles::j1Particles()
{

	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
		active[i] = nullptr;

}

j1Particles::~j1Particles()
{}

// Load assets
bool j1Particles::Start()
{
	LOG("Loading particles");

	
	return true;
}

// Unload assets
bool j1Particles::CleanUp()
{
	LOG("Unloading particles");

	/*App->textures->Unload(enemy_explosion.texture);*/

	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (active[i] != nullptr)
		{
			delete active[i];
			active[i] = nullptr;
		}
	}

	return true;
}

// Update: draw background
bool j1Particles::Update(float dt)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* p = active[i];
		if (p == nullptr)
			continue;

		if (p->Update() == false)
		{
			delete p;
			active[i] = nullptr;
		}
		else if (SDL_GetTicks() >= p->born)
		{
			App->render->Blit(p->texture, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()));
			if (p->fx_played == false)
			{
				p->fx_played = true;
				// Play particle fx here
				//App->audio->PlaySoundEffect(p->sound);
			}
		}
	}

	return true;
}

void j1Particles::AddParticle(const Particle& particle, int x, int y, COLLIDER_TYPE collider_type, Uint32 delay, iPoint *position, iPoint velocity_)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (active[i] == nullptr)
		{
			Particle* p = new Particle(particle);
			p->updated_speed.x = 0;
			p->updated_speed.y = 0;
			p->updated_speed = velocity_;
			p->position_to_attach = position;
			p->born = SDL_GetTicks() + delay;
			p->position.x = x;
			p->position.y = y;
			p->texture = particle.texture;
			p->sound = particle.sound;
			if (collider_type != COLLIDER_NONE)
				p->collider = App->collision->AddCollider(p->anim.GetCurrentFrame(), collider_type, this);
			p->collider->active = true;
			active[i] = p;
			//active[i]->texture = particle.texture;
			break;
		}
	}
}

// TODO 5: Make so every time a particle hits a wall it triggers an explosion particle
void j1Particles::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		// Always destroy particles that collide
		if (active[i] != nullptr && active[i]->collider == c1)
		{
			if (active[i]->end_particle != nullptr)
			{
				AddParticle(*active[i]->end_particle, active[i]->position.x, active[i]->position.y);
			}
			delete active[i];
			active[i] = nullptr;
			break;
		}
	}


}

// -------------------------------------------------------------
// -------------------------------------------------------------

Particle::Particle()
{
	position.SetToZero();
	speed.SetToZero();
}

Particle::Particle(const Particle& p) :
	anim(p.anim), position(p.position), speed(p.speed), end_particle(p.end_particle),
	fx(p.fx), born(p.born), life(p.life), position_to_attach(p.position_to_attach), updated_speed(p.updated_speed)
{}

Particle::~Particle()
{
	if (collider != nullptr)
		collider->to_delete = true;
}

bool Particle::Update()
{
	bool ret = true;
	if (updated_speed.x != 0 || updated_speed.y != 0) speed = updated_speed;

	if (life > 0)
	{
		int time = ((int)SDL_GetTicks() - (int)born);
		if (time > (int)life)
			ret = false;
	}

	else
		if (anim.Finished())
			ret = false;
	if (SDL_GetTicks() >= born)
	{
		if (position_to_attach != nullptr)
			position = *position_to_attach;
		else
		{
			position.x += speed.x;
			position.y += speed.y;
		}

		if (collider != nullptr)
			collider->SetPos(position.x, position.y);
	}


	return ret;
}