#include "Enemy.h"

Enemy::Enemy():Entity(EntityType::ENEMY)
{
	speed = 0;
	health_points = 0;
	damage = 0;
	active = false;
	enemy_type = EnemyType::ENEMY_NONE;
}

bool Enemy::Update()
{

	position.x -= speed;

	return true;
}
