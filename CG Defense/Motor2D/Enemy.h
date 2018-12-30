#ifndef __ENEMIES_H__
#define __ENEMIES_H__

#include "Entities.h"

class Enemy :public Entity
{
public:

	Enemy();

	bool Update();

protected:

	uint speed;
	uint health_points;
	uint damage;

	EnemyType enemy_type;
};


#endif // !__ENEMY_H__



#pragma once
