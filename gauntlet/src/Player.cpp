#include "PCH.h"
#include "Player.h"

// Constructor.
Player::Player() 
{
	AddComponent<C_Health>();
	AddComponent<C_Defense>();
	AddComponent<C_Strength>();
	AddComponent<C_Dexterity>();
	AddComponent<C_Stamina>();
	AddComponent<C_Attack>();
	AddComponent<C_Mana>();

	AddComponent<C_AudioListener>();

	AddComponent<C_Movement>();
	AddComponent<C_KeyboardController>();

	auto sprite = AddComponent<C_AnimatedSprite>();

	auto plyrClass = AddComponent<C_PlayerClass>();
	// Generate a random class.
	auto setClass = static_cast<PLAYER_CLASS>(std::rand() % static_cast<int>(PLAYER_CLASS::COUNT));

	plyrClass->Set(setClass);

	std::string className;

	// Set class-specific variables.
	switch (setClass)
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

	std::array<int, static_cast<int>(ANIMATION_STATE::COUNT)> textureIDs;
	textureIDs[static_cast<int>(ANIMATION_STATE::WALK_UP)] = TextureManager::AddTexture("../resources/players/" + className + "/spr_" + className + "_walk_up.png");
	textureIDs[static_cast<int>(ANIMATION_STATE::WALK_DOWN)] = TextureManager::AddTexture("../resources/players/" + className + "/spr_" + className + "_walk_down.png");
	textureIDs[static_cast<int>(ANIMATION_STATE::WALK_RIGHT)] = TextureManager::AddTexture("../resources/players/" + className + "/spr_" + className + "_walk_right.png");
	textureIDs[static_cast<int>(ANIMATION_STATE::WALK_LEFT)] = TextureManager::AddTexture("../resources/players/" + className + "/spr_" + className + "_walk_left.png");
	textureIDs[static_cast<int>(ANIMATION_STATE::IDLE_UP)] = TextureManager::AddTexture("../resources/players/" + className + "/spr_" + className + "_idle_up.png");
	textureIDs[static_cast<int>(ANIMATION_STATE::IDLE_DOWN)] = TextureManager::AddTexture("../resources/players/" + className + "/spr_" + className + "_idle_down.png");
	textureIDs[static_cast<int>(ANIMATION_STATE::IDLE_RIGHT)] = TextureManager::AddTexture("../resources/players/" + className + "/spr_" + className + "_idle_right.png");
	textureIDs[static_cast<int>(ANIMATION_STATE::IDLE_LEFT)] = TextureManager::AddTexture("../resources/players/" + className + "/spr_" + className + "_idle_left.png");

	auto anim = AddComponent<C_DirectionalAnimation>();
	anim->SetTextures(textureIDs);

	// Set initial sprite.
	sprite->SetSprite(TextureManager::GetTexture(textureIDs[static_cast<int>(ANIMATION_STATE::WALK_UP)]), false, 8, 12);
	//m_currentTextureIndex = static_cast<int>(ANIMATION_STATE::WALK_UP);
	sprite->GetSprite().setOrigin(sf::Vector2f(13.f, 18.f));

	// Set random traits.
	SetRandomTraits();

	// Set fixed stats.
	GetComponent<C_Health>()->SetCurrent(100);
	GetComponent<C_Mana>()->SetCurrent(50);

	// Randomly distribute other stats.
	int statPoints = 50;

	int attackBias = std::rand() % 101;
	int defenseBias = std::rand() % 101;
	int strengthBias = std::rand() % 101;
	int dexterityBias = std::rand() % 101;
	int staminaBias = std::rand() % 101;

	int total = attackBias + defenseBias + strengthBias + dexterityBias + staminaBias;

	auto attack = GetComponent<C_Attack>();
	attack->SetValue(attack->GetValue() + statPoints * (attackBias / total));
	
	auto defense = GetComponent<C_Defense>();
	defense->SetValue(defense->GetValue() + statPoints * (defenseBias / total));
	
	auto strength = GetComponent<C_Strength>();
	strength->SetValue(strength->GetValue() + statPoints * (strengthBias / total));

	auto dexterity = GetComponent<C_Dexterity>();
	dexterity->SetValue(dexterity->GetValue() + statPoints * (dexterityBias / total));

	auto stamina = GetComponent<C_Stamina>();
	stamina->SetValue(stamina->GetValue() + statPoints * (staminaBias / total));
}

// Updates the player object.
void Player::Update(float timeDelta, Level& level)
{
	Object::Update(timeDelta);
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