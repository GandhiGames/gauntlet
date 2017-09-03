#include "PCH.h"
#include "Player.h"

// Constructor.
Player::Player() :
m_manaDelta(0.f),
m_statPoints(0)
{
	AddComponent<C_AudioListener>();

	auto sprite = AddComponent<C_AnimatedSprite>();

	// Generate a random class.
	m_class = static_cast<PLAYER_CLASS>(std::rand() % static_cast<int>(PLAYER_CLASS::COUNT));
	std::string className;

	// Set class-specific variables.
	switch (m_class)
	{
	case PLAYER_CLASS::WARRIOR:
	{
		auto strength = GetComponent<C_Strength>();
		strength->SetValue(strength->GetValue() + std::rand() % 6 + 5);
		className = "warrior";
		break;
	}
	case PLAYER_CLASS::MAGE:
	{
		GetComponent<C_Defense>()->SetValue(std::rand() % 6 + 5);
		className = "mage";
		break;
	}
	case PLAYER_CLASS::ARCHER:
	{
		GetComponent<C_Dexterity>()->SetValue(std::rand() % 6 + 5);
		className = "archer";
		break;
	}
	case PLAYER_CLASS::THIEF:
	{
		GetComponent<C_Stamina>()->SetValue(std::rand() % 6 + 5);
		className = "thief";
		break;
	}
	}

	// Load textures.
	m_textureIDs[static_cast<int>(ANIMATION_STATE::WALK_UP)] = TextureManager::AddTexture("../resources/players/" + className + "/spr_" + className + "_walk_up.png");
	m_textureIDs[static_cast<int>(ANIMATION_STATE::WALK_DOWN)] = TextureManager::AddTexture("../resources/players/" + className + "/spr_" + className + "_walk_down.png");
	m_textureIDs[static_cast<int>(ANIMATION_STATE::WALK_RIGHT)] = TextureManager::AddTexture("../resources/players/" + className + "/spr_" + className + "_walk_right.png");
	m_textureIDs[static_cast<int>(ANIMATION_STATE::WALK_LEFT)] = TextureManager::AddTexture("../resources/players/" + className + "/spr_" + className + "_walk_left.png");
	m_textureIDs[static_cast<int>(ANIMATION_STATE::IDLE_UP)] = TextureManager::AddTexture("../resources/players/" + className + "/spr_" + className + "_idle_up.png");
	m_textureIDs[static_cast<int>(ANIMATION_STATE::IDLE_DOWN)] = TextureManager::AddTexture("../resources/players/" + className + "/spr_" + className + "_idle_down.png");
	m_textureIDs[static_cast<int>(ANIMATION_STATE::IDLE_RIGHT)] = TextureManager::AddTexture("../resources/players/" + className + "/spr_" + className + "_idle_right.png");
	m_textureIDs[static_cast<int>(ANIMATION_STATE::IDLE_LEFT)] = TextureManager::AddTexture("../resources/players/" + className + "/spr_" + className + "_idle_left.png");

	// Set initial sprite.
	sprite->SetSprite(TextureManager::GetTexture(m_textureIDs[static_cast<int>(ANIMATION_STATE::WALK_UP)]), false, 8, 12);
	m_currentTextureIndex = static_cast<int>(ANIMATION_STATE::WALK_UP);
	sprite->GetSprite().setOrigin(sf::Vector2f(13.f, 18.f));

	// Set random traits.
	SetRandomTraits();

	// Set fixed stats.
	GetComponent<C_Health>()->SetCurrent(100);
	GetComponent<C_Mana>()->SetCurrent(50);
	m_speed = 200;

	// Randomly distribute other stats.
	m_statPoints = 50;

	int attackBias = std::rand() % 101;
	int defenseBias = std::rand() % 101;
	int strengthBias = std::rand() % 101;
	int dexterityBias = std::rand() % 101;
	int staminaBias = std::rand() % 101;

	int total = attackBias + defenseBias + strengthBias + dexterityBias + staminaBias;

	auto attack = GetComponent<C_Attack>();
	attack->SetValue(attack->GetValue() + m_statPoints * (attackBias / total));
	
	auto defense = GetComponent<C_Defense>();
	defense->SetValue(defense->GetValue() + m_statPoints * (defenseBias / total));
	
	auto strength = GetComponent<C_Strength>();
	strength->SetValue(strength->GetValue() + m_statPoints * (strengthBias / total));

	auto dexterity = GetComponent<C_Dexterity>();
	dexterity->SetValue(dexterity->GetValue() + m_statPoints * (dexterityBias / total));

	auto stamina = GetComponent<C_Stamina>();
	stamina->SetValue(stamina->GetValue() + m_statPoints * (staminaBias / total));
}

// Updates the player object.
void Player::Update(float timeDelta, Level& level)
{
	Object::Update(timeDelta);

	// Calculate movement speed based on the timeDelta since the last update.
	sf::Vector2f movementSpeed(0.f, 0.f);
	sf::Vector2f previousPosition = m_transform->GetPosition();

	// Calculate where the current movement will put us.
	ANIMATION_STATE animState = static_cast<ANIMATION_STATE>(m_currentTextureIndex);

	if (Input::IsKeyPressed(Input::KEY::KEY_LEFT))
	{
		// Set movement speed.
		movementSpeed.x = -m_speed * timeDelta;

		// Chose animation state.
		animState = ANIMATION_STATE::WALK_LEFT;
	}
	else if (Input::IsKeyPressed(Input::KEY::KEY_RIGHT))
	{
		// Set movement speed.
		movementSpeed.x = m_speed * timeDelta;

		// Chose animation state.
		animState = ANIMATION_STATE::WALK_RIGHT;
	}

	if (Input::IsKeyPressed(Input::KEY::KEY_UP))
	{
		// Set movement speed.
		movementSpeed.y = -m_speed * timeDelta;

		// Chose animation state.
		animState = ANIMATION_STATE::WALK_UP;
	}
	else if (Input::IsKeyPressed(Input::KEY::KEY_DOWN))
	{
		// Set movement speed.
		movementSpeed.y = m_speed * timeDelta;

		// Chose animation state.
		animState = ANIMATION_STATE::WALK_DOWN;
	}

	// Calculate horizontal movement.
	if (CausesCollision(sf::Vector2f(movementSpeed.x, 0.0f), level))
	{
		m_transform->SetX(previousPosition.x);
	}
	else
	{
		m_transform->SetX(m_transform->GetPosition().x + movementSpeed.x);
	}

	// Calculate horizontal movement.
	if (CausesCollision(sf::Vector2f(0.0f, movementSpeed.y), level))
	{
		m_transform->SetY(previousPosition.y);
	}
	else
	{
		m_transform->SetY(m_transform->GetPosition().y + movementSpeed.y);
	}


	//TODO: cache call to getcomponent.
	auto sprite = GetComponent<C_AnimatedSprite>();

	// Set the sprite.
	if (m_currentTextureIndex != static_cast<int>(animState))
	{
		m_currentTextureIndex = static_cast<int>(animState);
		sprite->GetSprite().setTexture(TextureManager::GetTexture(m_textureIDs[m_currentTextureIndex]));
	}

	// set animation speed
	if ((movementSpeed.x == 0) && (movementSpeed.y == 0))
	{
		// the character is still
		if (sprite->IsAnimated())
		{
			// Update sprite to idle version.
			// In our enum we have 4 walking sprites followed by 4 idle sprites.
			// Given this, we can simply add 4 to a walking sprite to get its idle counterpart.
			m_currentTextureIndex += 4;
			sprite->GetSprite().setTexture(TextureManager::GetTexture(m_textureIDs[m_currentTextureIndex]));

			// Stop movement animations.
			sprite->SetAnimated(false);
		}
	}
	else
	{
		// the character is moving
		if (!sprite->IsAnimated())
		{
			// Update sprite to walking version.
			m_currentTextureIndex -= 4;
			sprite->GetSprite().setTexture(TextureManager::GetTexture(m_textureIDs[m_currentTextureIndex]));

			// Start movement animations.
			sprite->SetAnimated(true);
		}
	}

	if ((m_manaDelta += timeDelta) > 0.20)
	{
		//TODO: cache call to getcomponent.
		auto mana = GetComponent<C_Mana>();

		int curMana = mana->GetCurrent();
		if (curMana < mana->GetMax())
		{
			mana->SetCurrent(curMana + 1);
		}

		m_manaDelta = 0.f;
	}
}

// Returns the player's class.
PLAYER_CLASS Player::GetClass() const
{
	return m_class;
}

// Chooses random traits for the character.
void Player::SetRandomTraits()
{
	// Generate the traits.
	for (int i = 0; i < PLAYER_TRAIT_COUNT; ++i)
		m_traits[i] = static_cast<PLAYER_TRAIT>(std::rand() % static_cast<int>(PLAYER_TRAIT::COUNT));

	//TODO: refractor into template method
	for (PLAYER_TRAIT trait : m_traits)
	{
		switch (trait)
		{
		case PLAYER_TRAIT::ATTACK: default:
		{
			auto attack = GetComponent<C_Attack>();
			attack->SetValue(attack->GetValue() + std::rand() % 6 + 5);
			break;
		}
		case PLAYER_TRAIT::DEFENSE:
		{
			auto attack = GetComponent<C_Defense>();
			attack->SetValue(attack->GetValue() + std::rand() % 6 + 5);
			break;
		}
		case PLAYER_TRAIT::STRENGTH:
		{
			auto strength = GetComponent<C_Defense>();
			strength->SetValue(strength->GetValue() + std::rand() % 6 + 5);
			break;
		}
		case PLAYER_TRAIT::DEXTERITY:
		{
			auto dexterity = GetComponent<C_Dexterity>();
			dexterity->SetValue(dexterity->GetValue() + std::rand() % 6 + 5);
			break;
		}
		case PLAYER_TRAIT::STAMINA:
		{
			auto stamina = GetComponent<C_Stamina>();
			stamina->SetValue(stamina->GetValue() + std::rand() % 6 + 5);
			break;
		}
		}
	}
}

// Return the players traits.
PLAYER_TRAIT* Player::GetTraits()
{
	return &m_traits[0];
}

// Returns the number of traits the player has.
int Player::GetTraitCount() const
{
	return PLAYER_TRAIT_COUNT;
}

// Checks is the given movement will result in a collision.
bool Player::CausesCollision(sf::Vector2f movement, Level& level)
{
	// Get the tiles that the four corners other player are overlapping with.
	Tile* overlappingTiles[4];
	sf::Vector2f newPosition = m_transform->GetPosition() + movement;

	// Top left.
	overlappingTiles[0] = level.GetTile(sf::Vector2f(newPosition.x - 14.f, newPosition.y - 14.f));

	// Top right.
	overlappingTiles[1] = level.GetTile(sf::Vector2f(newPosition.x + 14.f, newPosition.y - 14.f));

	// Bottom left.
	overlappingTiles[2] = level.GetTile(sf::Vector2f(newPosition.x - 14.f, newPosition.y + 14.f));

	// Bottom right.
	overlappingTiles[3] = level.GetTile(sf::Vector2f(newPosition.x + 14.f, newPosition.y + 14.f));

	// If any of the overlapping tiles are solid there was a collision.
	for (int i = 0; i < 4; i++)
	{
		if (level.IsSolid(overlappingTiles[i]->columnIndex, overlappingTiles[i]->rowIndex))
			return true;
	}

	// If we've not returned yet no collisions were found.
	return false;
}
