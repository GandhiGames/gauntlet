//-------------------------------------------------------------------------------------
// Enemy.h
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Written by Dale Green. Copyright (c) Packt Publishing. All rights reserved.
//-------------------------------------------------------------------------------------
#ifndef ENEMY_H
#define ENEMY_H

#include "Entity.h"
#include "Level.h"

class Enemy : public Entity
{
public:
	/**
	 * Default constructor.
	 */
	Enemy();

private:
	std::shared_ptr<C_Pathfinding> m_pathFinding;


};
#endif