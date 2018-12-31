#include "Tower.h"
#include "j1Collision.h"
#include "j1App.h"
#include "j1EntityManager.h"

Tower::Tower():Entity(EntityType::TOWER)
{
	active = false;

}

bool Tower::Update()
{

	return true;
}

void Tower::Shoot()
{

}