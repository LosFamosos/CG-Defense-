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

	uint attack_speed;

private:

	uint attack_timer;


	
};

#endif // ! __TOWER_H__


#pragma once
