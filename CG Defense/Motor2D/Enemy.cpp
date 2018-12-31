#include "Enemy.h"
#include "j1Collision.h"
#include "j1App.h"
#include "j1EntityManager.h"
#include "j1Render.h"
#include "j1Scene.h"

Enemy::Enemy():Entity(EntityType::ENEMY)
{
	speed = 0;
	health_points = 0;
	damage = 0;
	active = false;
	enemy_type = EnemyType::ENEMY_NONE;

	collider = App->collision->AddCollider({ 0,0,33,22 },COLLIDER_ENEMY , this);
	collider->active = false;

	

}

bool Enemy::Update()
{
	if (active)
	{
		position.x -= speed;

		collider->SetPos(position.x, position.y);

		if (health_points <= 0)
			Die();

		else if (position.x < -App->render->camera.x)
		{
			Die();
			App->scene->current_base_health.w -= health_points;
		}
	}

	
	return true;
}

void Enemy::Die()
{

	active = false;

	collider->active = false;

}

void Enemy::OnCollision(Collider* c1, Collider* c2)
{
  	health_points -= 5;
}