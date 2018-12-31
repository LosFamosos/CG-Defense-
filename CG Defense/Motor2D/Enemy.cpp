#include "Enemy.h"
#include "j1Collision.h"
#include "j1App.h"
#include "j1EntityManager.h"

Enemy::Enemy():Entity(EntityType::ENEMY)
{
	speed = 0;
	health_points = 0;
	damage = 0;
	active = false;
	enemy_type = EnemyType::ENEMY_NONE;

	collider = App->collision->AddCollider({ 0,0,50,50 },COLLIDER_ENEMY , this);
	collider->active = false;
}

bool Enemy::Update()
{
	if (active)
	{
		position.x -= speed;

		collider->SetPos(position.x, position.y);
	}
	return true;
}

void Enemy::Die()
{

	active = false;

	collider->active = false;

}