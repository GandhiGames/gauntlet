#include "PCH.h"
#include "C_EndLevelTileCollision.h"
#include "Level.h"
#include "Game.h"

C_EndLevelTileCollision::C_EndLevelTileCollision(Object* owner) : Component(owner, true)
{
}


C_EndLevelTileCollision::~C_EndLevelTileCollision()
{
}

void C_EndLevelTileCollision::Update(float timeDelta, Object* owner)
{
	SharedContext* context = owner->GetContext();

	Tile* playerTile = context->m_level->GetTile(context->m_player->m_transform->GetPosition());
	
	if (playerTile->type == TILE::WALL_DOOR_UNLOCKED)
	{
		for (const auto& obj : *context->m_objects)
		{
			obj->Destroy();
		}
		
		context->m_game->RequestNewLevel();
	}
}