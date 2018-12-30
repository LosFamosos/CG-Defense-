#ifndef  __TOWER_H__
#define	 __TOWER_H__

#include "Entities.h"

class Tower :public Entity
{
public:

	Tower();

	bool Update();

private:

	void Shoot() {}

private:

	uint attack_speed;
};

#endif // ! __TOWER_H__


#pragma once
