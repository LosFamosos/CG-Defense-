#ifndef  __TOWER_H__
#define	 __TOWER_H__

#include "Entities.h"

class Tower :public Entity
{
public:

	Tower();

	bool Update() override;

	void Shoot();

public:

	TowerType tower_type;

	uint attack_speed=0;

private:

	uint attack_timer=0;


	
};

#endif // ! __TOWER_H__


#pragma once
