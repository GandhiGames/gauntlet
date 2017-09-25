#include "PCH.h"
#include "C_Pathfinding.h"
#include "Level.h"
#include "Object.h"


C_Pathfinding::C_Pathfinding(Object* owner) : Component(owner, true),
m_currentTarget({ 0.f, 0.f }),
m_speed(0),
m_prevTargetTile(nullptr)
{
	m_speed = rand() % 51 + 150;
}


C_Pathfinding::~C_Pathfinding()
{
}

void C_Pathfinding::LoadDependencies(Object* owner)
{
	m_movement = owner->GetComponent<C_Movement>();
	m_transform = owner->GetComponent<C_Transform>();
}

void C_Pathfinding::Update(float deltaTime, Object* owner)
{
	SharedContext* context = owner->GetContext();
	const sf::Vector2f& playerPos = context->m_player->m_transform->GetPosition();
	Level* level = context->m_level;

	Tile*curTile = level->GetTile(playerPos);

	if (curTile != m_prevTargetTile)
	{
		m_prevTargetTile = curTile;

		if (DistanceBetweenPoints(playerPos, owner->m_transform->GetPosition()) < 300.0f)
		{
			Calculate(context->m_level, playerPos);
		}
	}



	sf::Vector2f* targetLocation = GetNextPosition();

	// Move towards current target location.
	if (targetLocation)
	{
		sf::Vector2f velocity = sf::Vector2f(targetLocation->x - m_transform->GetPosition().x,
			targetLocation->y - m_transform->GetPosition().y);

		if (abs(velocity.x) < 10.f && abs(velocity.y) < 10.f) // Reached target.
		{
			RemoveFirst();
		}
		else
		{
			float length = sqrt(velocity.x * velocity.x + velocity.y * velocity.y);
			velocity.x /= length;
			velocity.y /= length;

			m_movement->SetVelocity((velocity * (float)m_speed * deltaTime));
		}
	}
	else
	{
		m_movement->SetVelocity(sf::Vector2f(0.f, 0.f));
	}
}

void C_Pathfinding::Calculate(Level* level, const sf::Vector2f& target)
{
	// Create all variables.
	std::vector<Tile*> openList;
	std::vector<Tile*> closedList;
	std::vector<Tile*> pathList;
	std::vector<Tile*>::iterator position;
	Tile* currentNode;

	// Reset all nodes.
	level->ResetNodes();

	// Store the start and goal nodes.
	Tile* startNode = level->GetTile(m_transform->GetPosition());
	Tile* goalNode = level->GetTile(target);

	// Check we have a valid path to find. If not we can just end the function as there's no path to find.
	if (startNode == goalNode)
	{
		// Clear the vector of target positions.
		m_targetPositions.clear();

		// Exit the function.
		return;
	}

	// Pre-compute our H cost (estimated cost to goal) for each node.
	for (int i = 0; i < level->GetSize().x; i++)
	{
		for (int j = 0; j < level->GetSize().y; j++)
		{
			int rowOffset, heightOffset;
			Tile* node = level->GetTile(i, j);

			heightOffset = abs(node->rowIndex - goalNode->rowIndex);
			rowOffset = abs(node->columnIndex - goalNode->columnIndex);

			node->H = heightOffset + rowOffset;
		}
	}

	// Add the start node to the open list.
	openList.push_back(startNode);

	// While we have values to check in the open list.
	while (!openList.empty())
	{
		// Find the node in the open list with the lowest F value and mark it as current.
		int lowestF = INT_MAX;

		for (Tile* tile : openList)
		{
			if (tile->F < lowestF)
			{
				lowestF = tile->F;
				currentNode = tile;
			}
		}

		// Remove the current node from the open list and add it to the closed list.
		position = std::find(openList.begin(), openList.end(), currentNode);
		if (position != openList.end())
			openList.erase(position);

		closedList.push_back(currentNode);

		// Find all valid adjacent nodes.
		std::vector<Tile*> adjacentTiles;
		Tile* node;

		// Top.
		node = level->GetTile(currentNode->columnIndex, currentNode->rowIndex - 1);
		if ((node != nullptr) && (level->IsFloor(*node)))
		{
			adjacentTiles.push_back(level->GetTile(currentNode->columnIndex, currentNode->rowIndex - 1));
		}

		// Right.
		node = level->GetTile(currentNode->columnIndex + 1, currentNode->rowIndex);
		if ((node != nullptr) && (level->IsFloor(*node)))
		{
			adjacentTiles.push_back(level->GetTile(currentNode->columnIndex + 1, currentNode->rowIndex));
		}

		// Bottom.
		node = level->GetTile(currentNode->columnIndex, currentNode->rowIndex + 1);
		if ((node != nullptr) && (level->IsFloor(*node)))
		{
			adjacentTiles.push_back(level->GetTile(currentNode->columnIndex, currentNode->rowIndex + 1));
		}

		// Left.
		node = level->GetTile(currentNode->columnIndex - 1, currentNode->rowIndex);
		if ((node != nullptr) && (level->IsFloor(*node)))
		{
			adjacentTiles.push_back(level->GetTile(currentNode->columnIndex - 1, currentNode->rowIndex));
		}

		// For all adjacent nodes.
		for (Tile* node : adjacentTiles)
		{
			// If the node is our goal node.
			if (node == goalNode)
			{
				// Parent the goal node to current.
				node->parentNode = currentNode;

				// Store the current path.
				while (node->parentNode != nullptr)
				{
					pathList.push_back(node);
					node = node->parentNode;
				}

				// Empty the open list and break out of our for loop.
				openList.clear();
				break;
			}
			else
			{
				// If the node is not in the closed list.
				position = std::find(closedList.begin(), closedList.end(), node);
				if (position == closedList.end())
				{
					// If the node is not in the open list.
					position = std::find(openList.begin(), openList.end(), node);
					if (position == openList.end())
					{
						// Add the node to the open list.
						openList.push_back(node);

						// Set the parent of the node to the current node.
						node->parentNode = currentNode;

						// Calculate G (total movement cost so far) cost.
						node->G = currentNode->G + 10;

						// Calculate the F (total movement cost + heuristic) cost.
						node->F = node->G + node->H;
					}
					else
					{
						// Check if this path is quicker that the other.
						int tempG = currentNode->G + 10;

						// Check if tempG is faster than the other. I.e, whether it's faster to go A->C->B that A->C.
						if (tempG < node->G)
						{
							// Re-parent node to this one.
							node->parentNode = currentNode;
						}
					}
				}
			}
		}
	}

	// Clear the vector of target positions.
	m_targetPositions.clear();

	// Store the node locations as the enemies target locations.
	for (Tile* tile : pathList)
	{
		m_targetPositions.push_back(level->GetActualTileLocation(tile->columnIndex, tile->rowIndex));
	}

	// Reverse the target position as we read them from goal to origin and we need them the other way around.
	std::reverse(m_targetPositions.begin(), m_targetPositions.end());
}

sf::Vector2f* C_Pathfinding::GetNextPosition()
{
	if (!m_targetPositions.empty())
	{
		return &m_targetPositions.front();
	}

	return nullptr;
}


void C_Pathfinding::RemoveFirst()
{
	if (!m_targetPositions.empty())
	{
		m_targetPositions.erase(m_targetPositions.begin());
	}
}
