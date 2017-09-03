#include "PCH.h"
#include "EntityFactory.h"

EntityFactory* EntityFactory::m_instance = 0;

EntityFactory* EntityFactory::GetInstance()
{
	if (!m_instance)
	{
		//TODO: does this resource need to be freed?
		m_instance = new EntityFactory();
	}

	return m_instance;
}

EntityFactory::EntityFactory()
{
	//TODO: remove these lines from factory. Create resource manager and components can request audio resources.
	int soundBufferId = SoundBufferManager::AddSoundBuffer("../resources/sounds/snd_player_hit.wav");
	m_playerHitSound.setBuffer(SoundBufferManager::GetSoundBuffer(soundBufferId));
	m_playerHitSound.setRelativeToListener(true);
}

std::unique_ptr<Entity> EntityFactory::Create(ENEMY type, SharedContext* context)
{
	switch (type)
	{
	case ENEMY::SLIME:
	{
		Entity instance;

		instance.GetComponent<C_Tag>()->Set(ENEMY_TAG);
		instance.AddComponent<C_AnimatedSprite>();
		instance.AddComponent<C_SpawnItemsOnDeath>();
		instance.AddComponent<C_PlaySoundOnDeath>();
		instance.AddComponent<C_Pathfinding>();
		instance.GetComponent<C_Health>()->SetCurrent(std::rand() % 41 + 80);
		instance.GetComponent<C_Attack>()->SetValue(std::rand() % 5 + 6);
		instance.GetComponent<C_Defense>()->SetValue(std::rand() % 5 + 6);
		instance.GetComponent<C_Strength>()->SetValue(std::rand() % 5 + 6);
		instance.GetComponent<C_Dexterity>()->SetValue(std::rand() % 5 + 6);
		instance.GetComponent<C_Stamina>()->SetValue(std::rand() % 5 + 6);

		auto dmg = instance.AddComponent<C_CollisionDamage>();
		dmg->SetDamageAmount(10);
		dmg->SetTargetTag(PLAYER_TAG);
		dmg->SetSoundOnHit(&m_playerHitSound);

		// Load textures.
		instance.m_textureIDs[static_cast<int>(ANIMATION_STATE::WALK_UP)] = TextureManager::AddTexture("../resources/enemies/slime/spr_slime_walk_up.png");
		instance.m_textureIDs[static_cast<int>(ANIMATION_STATE::WALK_DOWN)] = TextureManager::AddTexture("../resources/enemies/slime/spr_slime_walk_down.png");
		instance.m_textureIDs[static_cast<int>(ANIMATION_STATE::WALK_RIGHT)] = TextureManager::AddTexture("../resources/enemies/slime/spr_slime_walk_right.png");
		instance.m_textureIDs[static_cast<int>(ANIMATION_STATE::WALK_LEFT)] = TextureManager::AddTexture("../resources/enemies/slime/spr_slime_walk_left.png");
		instance.m_textureIDs[static_cast<int>(ANIMATION_STATE::IDLE_UP)] = TextureManager::AddTexture("../resources/enemies/slime/spr_slime_idle_up.png");
		instance.m_textureIDs[static_cast<int>(ANIMATION_STATE::IDLE_DOWN)] = TextureManager::AddTexture("../resources/enemies/slime/spr_slime_idle_down.png");
		instance.m_textureIDs[static_cast<int>(ANIMATION_STATE::IDLE_RIGHT)] = TextureManager::AddTexture("../resources/enemies/slime/spr_slime_idle_right.png");
		instance.m_textureIDs[static_cast<int>(ANIMATION_STATE::IDLE_LEFT)] = TextureManager::AddTexture("../resources/enemies/slime/spr_slime_idle_left.png");

		auto sprite = instance.GetComponent<C_AnimatedSprite>();
		// Set initial sprite.
		sprite->SetSprite(TextureManager::GetTexture(instance.m_textureIDs[static_cast<int>(ANIMATION_STATE::WALK_DOWN)]), false, 8, 12);

		// Choose the random sprite color and set it.
		int r, g, b, a;

		r = rand() % 256;
		g = rand() % 256;
		b = rand() % 256;
		a = rand() % 156 + 100;
		sf::Color color(r, g, b, 255);

		sprite->GetSprite().setColor(color);

		// Generate a random scale between 0.5 and 1.5 and set it.
		float scale;
		scale = (rand() % 11 + 5) / 10.f;

		sprite->GetSprite().setScale(sf::Vector2f(scale, scale));
		
		return std::make_unique<Entity>(instance);
	}
	case ENEMY::HUMANOID:
	{
		Humanoid instance;

		instance.GetComponent<C_Tag>()->Set(ENEMY_TAG);
		instance.AddComponent<C_AnimatedSprite>();
		instance.AddComponent<C_SpawnItemsOnDeath>();
		instance.AddComponent<C_PlaySoundOnDeath>();
		instance.AddComponent<C_Pathfinding>();
		instance.GetComponent<C_Health>()->SetCurrent(std::rand() % 41 + 80);
		instance.GetComponent<C_Attack>()->SetValue(std::rand() % 5 + 6);
		instance.GetComponent<C_Defense>()->SetValue(std::rand() % 5 + 6);
		instance.GetComponent<C_Strength>()->SetValue(std::rand() % 5 + 6);
		instance.GetComponent<C_Dexterity>()->SetValue(std::rand() % 5 + 6);
		instance.GetComponent<C_Stamina>()->SetValue(std::rand() % 5 + 6);

		auto dmg = instance.AddComponent<C_CollisionDamage>();
		dmg->SetDamageAmount(10);
		dmg->SetTargetTag(PLAYER_TAG);
		dmg->SetSoundOnHit(&m_playerHitSound);

		// Generate a humanoid type. (Skeleton or Goblin)
		HUMANOID humanoidType = static_cast<HUMANOID>(rand() % static_cast<int>(HUMANOID::COUNT));
		std::string enemyName;

		// Set enemy specific variables.
		switch (humanoidType)
		{
		case HUMANOID::GOBLIN:
			enemyName = "goblin";
			break;

		case HUMANOID::SKELETON:
			enemyName = "skeleton";
			break;
		}

		// Load textures.
		instance.m_textureIDs[static_cast<int>(ANIMATION_STATE::WALK_UP)] = TextureManager::AddTexture("../resources/enemies/" + enemyName + "/spr_" + enemyName + "_walk_up.png");
		instance.m_textureIDs[static_cast<int>(ANIMATION_STATE::WALK_DOWN)] = TextureManager::AddTexture("../resources/enemies/" + enemyName + "/spr_" + enemyName + "_walk_down.png");
		instance.m_textureIDs[static_cast<int>(ANIMATION_STATE::WALK_RIGHT)] = TextureManager::AddTexture("../resources/enemies/" + enemyName + "/spr_" + enemyName + "_walk_right.png");
		instance.m_textureIDs[static_cast<int>(ANIMATION_STATE::WALK_LEFT)] = TextureManager::AddTexture("../resources/enemies/" + enemyName + "/spr_" + enemyName + "_walk_left.png");
		instance.m_textureIDs[static_cast<int>(ANIMATION_STATE::IDLE_UP)] = TextureManager::AddTexture("../resources/enemies/" + enemyName + "/spr_" + enemyName + "_idle_up.png");
		instance.m_textureIDs[static_cast<int>(ANIMATION_STATE::IDLE_DOWN)] = TextureManager::AddTexture("../resources/enemies/" + enemyName + "/spr_" + enemyName + "_idle_down.png");
		instance.m_textureIDs[static_cast<int>(ANIMATION_STATE::IDLE_RIGHT)] = TextureManager::AddTexture("../resources/enemies/" + enemyName + "/spr_" + enemyName + "_idle_right.png");
		instance.m_textureIDs[static_cast<int>(ANIMATION_STATE::IDLE_LEFT)] = TextureManager::AddTexture("../resources/enemies/" + enemyName + "/spr_" + enemyName + "_idle_left.png");

		// Set initial sprite.
		instance.GetComponent<C_AnimatedSprite>()->SetSprite(TextureManager::GetTexture(instance.m_textureIDs[static_cast<int>(ANIMATION_STATE::WALK_UP)]), false, 8, 12);

		// Copy textures.
		for (int i = 0; i < static_cast<int>(ANIMATION_STATE::COUNT); i++)
		{
			instance.m_textures[i] = TextureManager::GetTexture(instance.m_textureIDs[i]);
		}

		// Generate armor.
		// Create arrays of textures for our armor, and the final versions.
		const int textureCount = static_cast<int>(ANIMATION_STATE::COUNT);
		sf::RenderTexture armorTextures[textureCount];
		sf::RenderTexture finalTextures[textureCount];
		sf::Image renderImage;

		// Setup all render textures.
		for (int i = 0; i < static_cast<int>(ANIMATION_STATE::COUNT); i++)
		{
			sf::Vector2u textureSize = instance.m_textures[i].getSize();

			armorTextures[i].create(textureSize.x, textureSize.y);
			finalTextures[i].create(textureSize.x, textureSize.y);
		}

		// Create variables to determine what armor be created.
		int hasHelmet(0), hasTorso(0), hasLegs(0);

		hasHelmet = rand() % 5;
		hasTorso = rand() % 5;
		hasLegs = rand() % 5;

		// Spawn helmet.
		if (hasHelmet == 0)
		{
			// Load the default helmet textures.
			int defaultHelmetTextureIDs[static_cast<int>(ANIMATION_STATE::COUNT)];

			defaultHelmetTextureIDs[static_cast<int>(ANIMATION_STATE::WALK_UP)] = TextureManager::AddTexture("../resources/armor/helmet/spr_helmet_walk_front.png");
			defaultHelmetTextureIDs[static_cast<int>(ANIMATION_STATE::WALK_DOWN)] = TextureManager::AddTexture("../resources/armor/helmet/spr_helmet_walk_front.png");
			defaultHelmetTextureIDs[static_cast<int>(ANIMATION_STATE::WALK_RIGHT)] = TextureManager::AddTexture("../resources/armor/helmet/spr_helmet_walk_side.png");
			defaultHelmetTextureIDs[static_cast<int>(ANIMATION_STATE::WALK_LEFT)] = TextureManager::AddTexture("../resources/armor/helmet/spr_helmet_walk_side.png");
			defaultHelmetTextureIDs[static_cast<int>(ANIMATION_STATE::IDLE_UP)] = TextureManager::AddTexture("../resources/armor/helmet/spr_helmet_idle_front.png");
			defaultHelmetTextureIDs[static_cast<int>(ANIMATION_STATE::IDLE_DOWN)] = TextureManager::AddTexture("../resources/armor/helmet/spr_helmet_idle_front.png");
			defaultHelmetTextureIDs[static_cast<int>(ANIMATION_STATE::IDLE_RIGHT)] = TextureManager::AddTexture("../resources/armor/helmet/spr_helmet_idle_side.png");
			defaultHelmetTextureIDs[static_cast<int>(ANIMATION_STATE::IDLE_LEFT)] = TextureManager::AddTexture("../resources/armor/helmet/spr_helmet_idle_side.png");

			// Generate random number to determine tier.
			sf::Color tierColor;
			int tierValue = rand() % 100 + 1;

			// Select which tier armor should be created.
			if (tierValue < 51)
			{
				tierColor = sf::Color(110, 55, 28, 255);	// Bronze.
			}
			else if (tierValue < 86)
			{
				tierColor = sf::Color(209, 208, 201, 255);	// Silver.
			}
			else
			{
				tierColor = sf::Color(229, 192, 21, 255);	// Gold.
			}

			// Render helmet to armor texture.
			for (int i = 0; i < static_cast<int>(ANIMATION_STATE::COUNT); i++)
			{
				// Load the default helmet texture and set its color.
				sf::Sprite tempSprite;
				tempSprite.setTexture(TextureManager::GetTexture(defaultHelmetTextureIDs[i]));
				tempSprite.setColor(tierColor);

				// Flip the texture vertically.
				sf::Vector2u size = armorTextures[i].getTexture().getSize();
				tempSprite.setTextureRect(sf::IntRect(0, size.y, size.x, -static_cast<int>(size.y)));

				// Draw the texture.
				armorTextures[i].draw(tempSprite);
			}
		}

		// Spawn torso.
		if (hasTorso == 0)
		{
			// Load the default torso textures.
			int defaultTorsoTextureIDs[static_cast<int>(ANIMATION_STATE::COUNT)];

			defaultTorsoTextureIDs[static_cast<int>(ANIMATION_STATE::WALK_UP)] = TextureManager::AddTexture("../resources/armor/torso/spr_torso_walk_front.png");
			defaultTorsoTextureIDs[static_cast<int>(ANIMATION_STATE::WALK_DOWN)] = TextureManager::AddTexture("../resources/armor/torso/spr_torso_walk_front.png");
			defaultTorsoTextureIDs[static_cast<int>(ANIMATION_STATE::WALK_RIGHT)] = TextureManager::AddTexture("../resources/armor/torso/spr_torso_walk_side.png");
			defaultTorsoTextureIDs[static_cast<int>(ANIMATION_STATE::WALK_LEFT)] = TextureManager::AddTexture("../resources/armor/torso/spr_torso_walk_side.png");
			defaultTorsoTextureIDs[static_cast<int>(ANIMATION_STATE::IDLE_UP)] = TextureManager::AddTexture("../resources/armor/torso/spr_torso_idle_front.png");
			defaultTorsoTextureIDs[static_cast<int>(ANIMATION_STATE::IDLE_DOWN)] = TextureManager::AddTexture("../resources/armor/torso/spr_torso_idle_front.png");
			defaultTorsoTextureIDs[static_cast<int>(ANIMATION_STATE::IDLE_RIGHT)] = TextureManager::AddTexture("../resources/armor/torso/spr_torso_idle_side.png");
			defaultTorsoTextureIDs[static_cast<int>(ANIMATION_STATE::IDLE_LEFT)] = TextureManager::AddTexture("../resources/armor/torso/spr_torso_idle_side.png");

			// Generate random number to determine tier.
			sf::Color tierColor;
			int tierValue = rand() % 100 + 1;

			// Select which tier armor should we created.
			if (tierValue < 51)
			{
				tierColor = sf::Color(110, 55, 28, 255);	// Bronze.
			}
			else if (tierValue < 86)
			{
				tierColor = sf::Color(209, 208, 201, 255);	// Silver.
			}
			else
			{
				tierColor = sf::Color(229, 192, 21, 255);	// Gold.
			}

			// Render torso to armor texture.
			for (int i = 0; i < static_cast<int>(ANIMATION_STATE::COUNT); i++)
			{
				sf::Sprite tempSprite;
				tempSprite.setTexture(TextureManager::GetTexture(defaultTorsoTextureIDs[i]));
				tempSprite.setColor(tierColor);

				// Flip the texture vertically.
				sf::Vector2u size = armorTextures[i].getTexture().getSize();
				tempSprite.setTextureRect(sf::IntRect(0, size.y, size.x, -static_cast<int>(size.y)));

				// Draw the texture.
				armorTextures[i].draw(tempSprite);
			}
		}

		// Spawn legs.
		if (hasLegs == 0)
		{
			// Load the default legs textures.
			int defaultLegsTextureIDs[static_cast<int>(ANIMATION_STATE::COUNT)];

			defaultLegsTextureIDs[static_cast<int>(ANIMATION_STATE::WALK_UP)] = TextureManager::AddTexture("../resources/armor/legs/spr_legs_walk_front.png");
			defaultLegsTextureIDs[static_cast<int>(ANIMATION_STATE::WALK_DOWN)] = TextureManager::AddTexture("../resources/armor/legs/spr_legs_walk_front.png");
			defaultLegsTextureIDs[static_cast<int>(ANIMATION_STATE::WALK_RIGHT)] = TextureManager::AddTexture("../resources/armor/legs/spr_legs_walk_side.png");
			defaultLegsTextureIDs[static_cast<int>(ANIMATION_STATE::WALK_LEFT)] = TextureManager::AddTexture("../resources/armor/legs/spr_legs_walk_side.png");
			defaultLegsTextureIDs[static_cast<int>(ANIMATION_STATE::IDLE_UP)] = TextureManager::AddTexture("../resources/armor/legs/spr_legs_idle_front.png");
			defaultLegsTextureIDs[static_cast<int>(ANIMATION_STATE::IDLE_DOWN)] = TextureManager::AddTexture("../resources/armor/legs/spr_legs_idle_front.png");
			defaultLegsTextureIDs[static_cast<int>(ANIMATION_STATE::IDLE_RIGHT)] = TextureManager::AddTexture("../resources/armor/legs/spr_legs_idle_side.png");
			defaultLegsTextureIDs[static_cast<int>(ANIMATION_STATE::IDLE_LEFT)] = TextureManager::AddTexture("../resources/armor/legs/spr_legs_idle_side.png");

			// Generate random number to determine tier.
			sf::Color tierColor;
			int tierValue = rand() % 100 + 1;

			// Select which tier armor should we created.
			if (tierValue < 51)
			{
				tierColor = sf::Color(110, 55, 28, 255);	// Bronze.
			}
			else if (tierValue < 86)
			{
				tierColor = sf::Color(209, 208, 201, 255);	// Silver.
			}
			else
			{
				tierColor = sf::Color(229, 192, 21, 255);	// Gold.
			}

			// Render legs to armor texture.
			for (int i = 0; i < static_cast<int>(ANIMATION_STATE::COUNT); i++)
			{
				sf::Sprite tempSprite;
				tempSprite.setTexture(TextureManager::GetTexture(defaultLegsTextureIDs[i]));
				tempSprite.setColor(tierColor);

				// Flip the texture vertically.
				sf::Vector2u size = armorTextures[i].getTexture().getSize();
				tempSprite.setTextureRect(sf::IntRect(0, size.y, size.x, -static_cast<int>(size.y)));

				// Draw the texture.
				armorTextures[i].draw(tempSprite);
			}
		}

		// Create the final textures.
		for (int i = 0; i < static_cast<int>(ANIMATION_STATE::COUNT); i++)
		{
			sf::Sprite baseSprite, armorSprite;

			// Draw the default texture.
			baseSprite.setTexture(instance.m_textures[i]);
			finalTextures[i].draw(baseSprite);

			// Draw armor on top.
			armorSprite.setTexture(armorTextures[i].getTexture());
			finalTextures[i].draw(armorSprite);

			// Flip the texture vertically.
			sf::Image img = finalTextures[i].getTexture().copyToImage();
			img.flipVertically();

			// Store the resulting texture.
			instance.m_textures[i].loadFromImage(img);
		}

		return std::make_unique<Humanoid>(instance);

		break;
	}
	case ENEMY::COUNT: default:
	{
		return nullptr;
	}
	}
}
