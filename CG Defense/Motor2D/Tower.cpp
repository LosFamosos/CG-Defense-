#include "Tower.h"
#include "j1Collision.h"
#include "j1App.h"
#include "j1EntityManager.h"

Tower::Tower():Entity(EntityType::TOWER)
{

	tower_type = TowerType::TOWER_NONE;


	active = false;

}

bool Tower::Update()
{

	return true;
}

void Tower::Shoot()
{
	switch (tower_type)
	{
	case TowerType::TOWER_BASIC:
		break;
	case TowerType::TOWER_MEDIUM:
		break;
	case TowerType::TOWER_PRO:
		break;
	case TowerType::TOWER_NONE:
		break;
	default:
		break;
	}
}