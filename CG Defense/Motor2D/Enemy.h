#ifndef __ENEMIES_H__
#define __ENEMIES_H__

#include "Entities.h"

struct Collider;

class Enemy :public Entity
{
public:

	Enemy();

	bool Update() override;

	void Die();

	void OnCollision(Collider* c1, Collider* c2)override;

public:

	

	uint speed;
	int health_points;
	uint damage;

	EnemyType enemy_type;

	Collider* collider=nullptr;
};


#endif // !__ENEMY_H__



#pragma once
