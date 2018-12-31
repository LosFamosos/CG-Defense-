#include "Tower.h"
#include "j1Collision.h"
#include "j1App.h"
#include "j1EntityManager.h"
#include "j1Input.h"

Tower::Tower():Entity(EntityType::TOWER)
{

	tower_type = TowerType::TOWER_NONE;

	active = false;

	basic_shot.anim.PushBack({ 115,144, 12,12 });
	basic_shot.life = 1000;
	basic_shot.texture = App->entity_manager->particles_texture;

	medium_shot.anim.PushBack({115,159,7,7});
	medium_shot.life = 1500;
	medium_shot.texture= App->entity_manager->particles_texture;


	pro_shot.anim.PushBack({115,166,9,9});
	pro_shot.life = 1500;
	pro_shot.texture = App->entity_manager->particles_texture;
}

bool Tower::Update()
{
	if (SDL_GetTicks() - attack_timer > attack_speed)
	{
		Shoot();
		attack_timer = SDL_GetTicks();
	}

	return true;
}

void Tower::Shoot()
{
	switch (tower_type)
	{
	case TowerType::TOWER_BASIC:

		App->particles->AddParticle(basic_shot, position.x + 16, position.y + 16, COLLIDER_TURRETSHOT, 0, nullptr, {0,5});
		App->particles->AddParticle(basic_shot, position.x + 16, position.y + 16, COLLIDER_TURRETSHOT, 0, nullptr, { 0,-5 });
		break;
	case TowerType::TOWER_MEDIUM:

		App->particles->AddParticle(medium_shot, position.x + 16, position.y + 16, COLLIDER_TURRETSHOT, 0, nullptr, {3,3 });
		App->particles->AddParticle(medium_shot, position.x + 16, position.y + 16, COLLIDER_TURRETSHOT, 100, nullptr, { 3,3 });
		App->particles->AddParticle(medium_shot, position.x + 16, position.y + 16, COLLIDER_TURRETSHOT, 200, nullptr, { 3,3 });
		App->particles->AddParticle(medium_shot, position.x + 16, position.y + 16, COLLIDER_TURRETSHOT, 300, nullptr, { 3,3 });
		App->particles->AddParticle(medium_shot, position.x + 16, position.y + 16, COLLIDER_TURRETSHOT, 400, nullptr, { 3,3 });
		App->particles->AddParticle(medium_shot, position.x + 16, position.y + 16, COLLIDER_TURRETSHOT, 500, nullptr, { 3,3 });

		App->particles->AddParticle(medium_shot, position.x + 16, position.y + 16, COLLIDER_TURRETSHOT, 0, nullptr, { 3,-3 });
		App->particles->AddParticle(medium_shot, position.x + 16, position.y + 16, COLLIDER_TURRETSHOT, 100, nullptr, { 3,-3 });
		App->particles->AddParticle(medium_shot, position.x + 16, position.y + 16, COLLIDER_TURRETSHOT, 200, nullptr, { 3,-3 });
		App->particles->AddParticle(medium_shot, position.x + 16, position.y + 16, COLLIDER_TURRETSHOT, 300, nullptr, { 3,-3 });
		App->particles->AddParticle(medium_shot, position.x + 16, position.y + 16, COLLIDER_TURRETSHOT, 400, nullptr, { 3,-3 });
		App->particles->AddParticle(medium_shot, position.x + 16, position.y + 16, COLLIDER_TURRETSHOT, 500, nullptr, { 3,-3 });
		break;
	case TowerType::TOWER_PRO:

		App->particles->AddParticle(pro_shot, position.x + 16, position.y + 16, COLLIDER_TURRETSHOT, 0, nullptr, { 3,-3 });
		App->particles->AddParticle(pro_shot, position.x + 16, position.y + 16, COLLIDER_TURRETSHOT, 50, nullptr, { 3,-3 });
		App->particles->AddParticle(pro_shot, position.x + 16, position.y + 16, COLLIDER_TURRETSHOT, 100, nullptr, { 3,-3 });

		App->particles->AddParticle(pro_shot, position.x + 16, position.y + 16, COLLIDER_TURRETSHOT, 0, nullptr, { 3,3 });
		App->particles->AddParticle(pro_shot, position.x + 16, position.y + 16, COLLIDER_TURRETSHOT, 50, nullptr, { 3,3 });
		App->particles->AddParticle(pro_shot, position.x + 16, position.y + 16, COLLIDER_TURRETSHOT, 100, nullptr, { 3,3 });

		App->particles->AddParticle(pro_shot, position.x + 16, position.y + 16, COLLIDER_TURRETSHOT, 0, nullptr, { -3,3 });
		App->particles->AddParticle(pro_shot, position.x + 16, position.y + 16, COLLIDER_TURRETSHOT, 50, nullptr, { -3,3 });
		App->particles->AddParticle(pro_shot, position.x + 16, position.y + 16, COLLIDER_TURRETSHOT, 100, nullptr, { -3,3 });

		App->particles->AddParticle(pro_shot, position.x + 16, position.y + 16, COLLIDER_TURRETSHOT, 0, nullptr, { 0,-3 });
		App->particles->AddParticle(pro_shot, position.x + 16, position.y + 16, COLLIDER_TURRETSHOT, 50, nullptr, { 0,-3 });
		App->particles->AddParticle(pro_shot, position.x + 16, position.y + 16, COLLIDER_TURRETSHOT, 100, nullptr, { 0,-3 });

		App->particles->AddParticle(pro_shot, position.x + 16, position.y + 16, COLLIDER_TURRETSHOT, 0, nullptr, { 0,3 });
		App->particles->AddParticle(pro_shot, position.x + 16, position.y + 16, COLLIDER_TURRETSHOT, 50, nullptr, { 0,3 });
		App->particles->AddParticle(pro_shot, position.x + 16, position.y + 16, COLLIDER_TURRETSHOT, 100, nullptr, { 0,3 });



		App->particles->AddParticle(pro_shot, position.x + 16, position.y + 16, COLLIDER_TURRETSHOT, 0, nullptr, { -3,-3 });
		App->particles->AddParticle(pro_shot, position.x + 16, position.y + 16, COLLIDER_TURRETSHOT, 50, nullptr, { -3,-3 });
		App->particles->AddParticle(pro_shot, position.x + 16, position.y + 16, COLLIDER_TURRETSHOT, 100, nullptr, { -3,-3 });


		break;
	case TowerType::TOWER_NONE:
		break;
	default:
		break;
	}
}