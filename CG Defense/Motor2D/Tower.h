#ifndef  __TOWER_H__
#define	 __TOWER_H__

#include "Entities.h"
#include "j1Particles.h"

class Tower :public Entity
{
public:

	Tower();

	bool Update() override;

	void Shoot();

public:

	Particle basic_shot;
	Particle medium_shot;
	Particle pro_shot;

	TowerType tower_type;

	uint attack_speed=0;
	uint attack_timer = 0;

	


	
};

#endif // ! __TOWER_H__


#pragma once
