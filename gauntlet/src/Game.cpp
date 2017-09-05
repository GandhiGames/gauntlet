#include "PCH.h"
#include "Game.h"

// Default constructor.
Game::Game(sf::RenderWindow* window) :
	m_window(*window),
	m_gameState(GAME_STATE::PLAYING),
	m_isRunning(true),
	m_string(""),
	m_screenSize({ 0, 0 }),
	m_screenCenter({ 0, 0 }),
	m_scoreTotal(0),
	m_goldTotal(0),
	m_playerPreviousTile(nullptr)
{
	// Enable VSync.
	m_window.setVerticalSyncEnabled(true);

	// Hide the mouse cursor.
	m_window.setMouseCursorVisible(false);

	// Calculate and store the center of the screen.
	m_screenCenter = { m_window.getSize().x / 2.f, m_window.getSize().y / 2.f };

	// Create the level object.
	m_level = Level(*window, &m_context);

	// Create the game font.
	m_font.loadFromFile("../resources/fonts/ADDSBP__.TTF");

	// Setup the main game music.
	int trackIndex = std::rand() % static_cast<int>(MUSIC_TRACK::COUNT) + 1;

	// Load the music track.
	m_music.openFromFile("../resources/music/msc_main_track_" + std::to_string(trackIndex) + ".wav");

	m_music.play();

	m_player.GetComponent<C_Tag>()->Set(PLAYER_TAG);
	m_player.AddComponent<C_ProjectileAttack>();
	m_player.SetContext(&m_context);

	m_context.m_enemies = &m_enemies;
	m_context.m_level = &m_level;
	m_context.m_items = &m_items;
	m_context.m_window = &m_window;
	m_context.m_lightGrid = &m_lightGrid;
}

// Initializes the game.
void Game::Initialize()
{
	// Get the screen size.
	m_screenSize = m_window.getSize();

	// Initialize the UI.
	LoadUI();

	// Generate a level.
	GenerateLevel();

	// Builds the light grid.
	ConstructLightGrid();

	// Define the game views.
	m_views[static_cast<int>(VIEW::MAIN)] = m_window.getDefaultView();
	m_views[static_cast<int>(VIEW::MAIN)].zoom(0.5f);
	m_views[static_cast<int>(VIEW::UI)] = m_window.getDefaultView();

	// Load all game sounds.
	int soundBufferId;

	// Load torch sound.
	soundBufferId = SoundBufferManager::AddSoundBuffer("../resources/sounds/snd_fire.wav");
	m_fireSound.setBuffer(SoundBufferManager::GetSoundBuffer(soundBufferId));
	m_fireSound.setLoop(true);
	m_fireSound.setAttenuation(5.f);
	m_fireSound.setMinDistance(80.f);
	m_fireSound.play();

	// Load gem pickup sound.
	soundBufferId = SoundBufferManager::AddSoundBuffer("../resources/sounds/snd_gem_pickup.wav");
	m_gemPickupSound.setBuffer(SoundBufferManager::GetSoundBuffer(soundBufferId));
	m_gemPickupSound.setRelativeToListener(true);

	// Load coin pickup sound.
	soundBufferId = SoundBufferManager::AddSoundBuffer("../resources/sounds/snd_coin_pickup.wav");
	m_coinPickupSound.setBuffer(SoundBufferManager::GetSoundBuffer(soundBufferId));
	m_coinPickupSound.setRelativeToListener(true);

	// Load key pickup sound.
	soundBufferId = SoundBufferManager::AddSoundBuffer("../resources/sounds/snd_key_pickup.wav");
	m_keyPickupSound.setBuffer(SoundBufferManager::GetSoundBuffer(soundBufferId));
	m_keyPickupSound.setRelativeToListener(true);

	// Add the new tile type to level.
	m_level.AddTile("../resources/tiles/spr_tile_floor_alt.png", TILE::FLOOR_ALT);

	// Change a selection of random tiles to the cracked tile sprite.
	SpawnRandomTiles(TILE::FLOOR_ALT, 15);

	//TODO: create aim sprite as child object of player.
	int textureID = TextureManager::AddTexture("../resources/ui/spr_aim.png");
	auto aimSprite = m_aim.AddComponent<C_StaticSprite>();
	aimSprite->GetSprite().setTexture(TextureManager::GetTexture(textureID));
	aimSprite->GetSprite().setOrigin(sf::Vector2f(16.5f, 16.5f));
	aimSprite->GetSprite().setScale(2.f, 2.f);
}

// Constructs the grid of sprites that are used to draw the game light system.
void Game::ConstructLightGrid()
{
	// Load the light tile texture and store a reference.
	int textureID = TextureManager::AddTexture("../resources/spr_light_grid.png");
	sf::Texture& lightTexture = TextureManager::GetTexture(textureID);

	// Calculate the number of tiles in the grid. Each light tile is 25px square.
	sf::IntRect levelArea;

	// Define the bounds of the level.
	levelArea.left = static_cast<int>(m_level.GetPosition().x);
	levelArea.top = static_cast<int>(m_level.GetPosition().y);
	levelArea.width = m_level.GetSize().x * m_level.GetTileSize();
	levelArea.height = m_level.GetSize().y * m_level.GetTileSize();

	int width, height, lightTotal;

	width = levelArea.width / 25;
	height = levelArea.height / 25;

	lightTotal = width * height;

	// Create all tiles.
	for (int i = 0; i < lightTotal; i++)
	{
		// Create the tile.
		sf::Sprite lightSprite;

		// Set sprite texture.
		lightSprite.setTexture(lightTexture);

		// Set the position of the tile.
		int xPos = levelArea.left + ((i % width) * 25);
		int yPos = levelArea.top + ((i / width) * 25);

		lightSprite.setPosition(static_cast<float>(xPos), static_cast<float>(yPos));

		// Add the sprite to our light vector.
		m_lightGrid.push_back(lightSprite);
	}
}

// Loads and prepares all UI assets.
void Game::LoadUI()
{
	// Initialize the player ui texture and sprite.
	m_playerUiTextureIDs[static_cast<int>(PLAYER_CLASS::WARRIOR)] = TextureManager::AddTexture("../resources/ui/spr_warrior_ui.png");
	m_playerUiTextureIDs[static_cast<int>(PLAYER_CLASS::MAGE)] = TextureManager::AddTexture("../resources/ui/spr_mage_ui.png");
	m_playerUiTextureIDs[static_cast<int>(PLAYER_CLASS::ARCHER)] = TextureManager::AddTexture("../resources/ui/spr_archer_ui.png");
	m_playerUiTextureIDs[static_cast<int>(PLAYER_CLASS::THIEF)] = TextureManager::AddTexture("../resources/ui/spr_thief_ui.png");

	// Bar outlines.
	sf::Texture& barOutlineTexture = TextureManager::GetTexture(TextureManager::AddTexture("../resources/ui/spr_bar_outline.png"));
	sf::Vector2f barOutlineTextureOrigin = { barOutlineTexture.getSize().x / 2.f, barOutlineTexture.getSize().y / 2.f };

	m_healthBarOutlineSprite = std::make_shared<sf::Sprite>();
	m_healthBarOutlineSprite->setTexture(barOutlineTexture);
	m_healthBarOutlineSprite->setPosition(sf::Vector2f(205.f, 35.f));
	m_healthBarOutlineSprite->setOrigin(sf::Vector2f(barOutlineTextureOrigin.x, barOutlineTextureOrigin.y));
	m_uiSprites.push_back(m_healthBarOutlineSprite);

	m_manaBarOutlineSprite = std::make_shared<sf::Sprite>();
	m_manaBarOutlineSprite->setTexture(barOutlineTexture);
	m_manaBarOutlineSprite->setPosition(sf::Vector2f(205.f, 55.f));
	m_manaBarOutlineSprite->setOrigin(sf::Vector2f(barOutlineTextureOrigin.x, barOutlineTextureOrigin.y));
	m_uiSprites.push_back(m_manaBarOutlineSprite);

	//Bars.
	sf::Texture& healthBarTexture = TextureManager::GetTexture(TextureManager::AddTexture("../resources/ui/spr_health_bar.png"));
	sf::Vector2f barTextureOrigin = { healthBarTexture.getSize().x / 2.f, healthBarTexture.getSize().y / 2.f };

	m_healthBarSprite = std::make_shared<sf::Sprite>();
	m_healthBarSprite->setTexture(healthBarTexture);
	m_healthBarSprite->setPosition(sf::Vector2f(205.f, 35.f));
	m_healthBarSprite->setOrigin(sf::Vector2f(barTextureOrigin.x, barTextureOrigin.y));

	m_manaBarSprite = std::make_shared<sf::Sprite>();
	m_manaBarSprite->setTexture(TextureManager::GetTexture(TextureManager::AddTexture("../resources/ui/spr_mana_bar.png")));
	m_manaBarSprite->setPosition(sf::Vector2f(205.f, 55.f));
	m_manaBarSprite->setOrigin(sf::Vector2f(barTextureOrigin.x, barTextureOrigin.y));

	m_playerUiSprite = std::make_shared<sf::Sprite>();
	m_playerUiSprite->setTexture(TextureManager::GetTexture(m_playerUiTextureIDs[static_cast<int>(m_player.GetClass())]));
	m_playerUiSprite->setPosition(sf::Vector2f(45.f, 45.f));
	m_playerUiSprite->setOrigin(sf::Vector2f(30.f, 30.f));
	m_uiSprites.push_back(m_playerUiSprite);

	// Initialize the coin and gem ui sprites.
	m_gemUiSprite = std::make_shared<sf::Sprite>();
	m_gemUiSprite->setTexture(TextureManager::GetTexture(TextureManager::AddTexture("../resources/ui/spr_gem_ui.png")));
	m_gemUiSprite->setPosition(sf::Vector2f(m_screenCenter.x - 260.f, 50.f));
	m_gemUiSprite->setOrigin(sf::Vector2f(42.f, 36.f));
	m_uiSprites.push_back(m_gemUiSprite);

	m_coinUiSprite = std::make_shared<sf::Sprite>();
	m_coinUiSprite->setTexture(TextureManager::GetTexture(TextureManager::AddTexture("../resources/ui/spr_coin_ui.png")));
	m_coinUiSprite->setPosition(sf::Vector2f(m_screenCenter.x + 60.f, 50.f));
	m_coinUiSprite->setOrigin(sf::Vector2f(48.f, 24.f));
	m_uiSprites.push_back(m_coinUiSprite);

	// Key pickup sprite.
	m_keyUiSprite = std::make_shared<sf::Sprite>();
	m_keyUiSprite->setTexture(TextureManager::GetTexture(TextureManager::AddTexture("../resources/ui/spr_key_ui.png")));
	m_keyUiSprite->setPosition(sf::Vector2f(m_screenSize.x - 120.f, m_screenSize.y - 70.f));
	m_keyUiSprite->setOrigin(sf::Vector2f(90.f, 45.f));
	m_keyUiSprite->setColor(sf::Color(255, 255, 255, 60));
	m_uiSprites.push_back(m_keyUiSprite);

	// Load stats.
	m_attackStatTextureIDs[0] = TextureManager::AddTexture("../resources/ui/spr_attack_ui.png");
	m_attackStatTextureIDs[1] = TextureManager::AddTexture("../resources/ui/spr_attack_ui_alt.png");

	m_attackStatSprite = std::make_shared<sf::Sprite>();
	m_attackStatSprite->setTexture(TextureManager::GetTexture(m_attackStatTextureIDs[0]));
	m_attackStatSprite->setOrigin(sf::Vector2f(16.f, 16.f));
	m_attackStatSprite->setPosition(sf::Vector2f(m_screenCenter.x - 270.f, m_screenSize.y - 30.f));
	m_uiSprites.push_back(m_attackStatSprite);

	m_defenseStatTextureIDs[0] = TextureManager::AddTexture("../resources/ui/spr_defense_ui.png");
	m_defenseStatTextureIDs[1] = TextureManager::AddTexture("../resources/ui/spr_defense_ui_alt.png");

	m_defenseStatSprite = std::make_shared<sf::Sprite>();
	m_defenseStatSprite->setTexture(TextureManager::GetTexture(m_defenseStatTextureIDs[0]));
	m_defenseStatSprite->setOrigin(sf::Vector2f(16.f, 16.f));
	m_defenseStatSprite->setPosition(sf::Vector2f(m_screenCenter.x - 150.f, m_screenSize.y - 30.f));
	m_uiSprites.push_back(m_defenseStatSprite);

	m_strengthStatTextureIDs[0] = TextureManager::AddTexture("../resources/ui/spr_strength_ui.png");
	m_strengthStatTextureIDs[1] = TextureManager::AddTexture("../resources/ui/spr_strength_ui_alt.png");

	m_strengthStatSprite = std::make_shared<sf::Sprite>();
	m_strengthStatSprite->setTexture(TextureManager::GetTexture(m_strengthStatTextureIDs[0]));
	m_strengthStatSprite->setOrigin(sf::Vector2f(22.f, 12.f));
	m_strengthStatSprite->setPosition(sf::Vector2f(m_screenCenter.x - 30.f, m_screenSize.y - 30.f));
	m_uiSprites.push_back(m_strengthStatSprite);

	m_dexterityStatTextureIDs[0] = TextureManager::AddTexture("../resources/ui/spr_dexterity_ui.png");
	m_dexterityStatTextureIDs[1] = TextureManager::AddTexture("../resources/ui/spr_dexterity_ui_alt.png");

	m_dexterityStatSprite = std::make_shared<sf::Sprite>();
	m_dexterityStatSprite->setTexture(TextureManager::GetTexture(m_dexterityStatTextureIDs[0]));
	m_dexterityStatSprite->setOrigin(sf::Vector2f(16.f, 16.f));
	m_dexterityStatSprite->setPosition(sf::Vector2f(m_screenCenter.x + 90.f, m_screenSize.y - 30.f));
	m_uiSprites.push_back(m_dexterityStatSprite);

	m_staminaStatTextureIDs[0] = TextureManager::AddTexture("../resources/ui/spr_stamina_ui.png");
	m_staminaStatTextureIDs[1] = TextureManager::AddTexture("../resources/ui/spr_stamina_ui_alt.png");

	m_staminaStatSprite = std::make_shared<sf::Sprite>();
	m_staminaStatSprite->setTexture(TextureManager::GetTexture(m_staminaStatTextureIDs[0]));
	m_staminaStatSprite->setOrigin(sf::Vector2f(16.f, 16.f));
	m_staminaStatSprite->setPosition(sf::Vector2f(m_screenCenter.x + 210.f, m_screenSize.y - 30.f));
	m_uiSprites.push_back(m_staminaStatSprite);

	// Set player traits
	int traitCount = m_player.GetTraitCount();

	for (int i = 0; i < traitCount; ++i)
	{
		switch (m_player.GetTraits()[i])
		{
		case PLAYER_TRAIT::ATTACK:
			m_attackStatSprite->setTexture(TextureManager::GetTexture(m_attackStatTextureIDs[1]));
			m_attackStatSprite->setScale(sf::Vector2f(1.2f, 1.2f));
			break;

		case PLAYER_TRAIT::DEFENSE:
			m_defenseStatSprite->setTexture(TextureManager::GetTexture(m_defenseStatTextureIDs[1]));
			m_defenseStatSprite->setScale(sf::Vector2f(1.2f, 1.2f));
			break;

		case PLAYER_TRAIT::STRENGTH:
			m_strengthStatSprite->setTexture(TextureManager::GetTexture(m_strengthStatTextureIDs[1]));
			m_strengthStatSprite->setScale(sf::Vector2f(1.2f, 1.2f));
			break;

		case PLAYER_TRAIT::DEXTERITY:
			m_dexterityStatSprite->setTexture(TextureManager::GetTexture(m_dexterityStatTextureIDs[1]));
			m_dexterityStatSprite->setScale(sf::Vector2f(1.2f, 1.2f));
			break;

		case PLAYER_TRAIT::STAMINA:
			m_staminaStatSprite->setTexture(TextureManager::GetTexture(m_staminaStatTextureIDs[1]));
			m_staminaStatSprite->setScale(sf::Vector2f(1.2f, 1.2f));
			break;
		}
	}
}

// Generates a new level.
void Game::GenerateLevel()
{
	// Generate a new level.
	m_level.GenerateLevel();

	// Add a key to the level.
	SpawnItem(ITEM::KEY);

	// Populate the level with items.
	PopulateLevel();

	// Moves the player to the start.
	m_player.m_transform->SetPosition(m_level.SpawnLocation());
}

// Populate the level with items.
void Game::PopulateLevel()
{
	// Spawn items.
	for (int i = 0; i < MAX_ITEM_SPAWN_COUNT; i++)
	{
		if (std::rand() % 2)
		{
			SpawnItem(static_cast<ITEM>(std::rand() % 2));
		}
	}

	// Spawn enemies.
	for (int i = 0; i < MAX_ENEMY_SPAWN_COUNT; i++)
	{
		if (std::rand() % 2)
		{
			SpawnEnemy(static_cast<ENEMY>(std::rand() % static_cast<int>(ENEMY::COUNT)));
		}
	}
}

// Returns the running state of the game.
bool Game::IsRunning()
{
	return m_isRunning;
}

// Main game loop.
void Game::Run()
{
	float currentTime = m_timestepClock.restart().asSeconds();
	float timeDelta = 0.f;

	// Loop until there is a quite message from the window or the user pressed escape.
	while (m_isRunning)
	{
		// Check if the game was closed.
		sf::Event event;
		if (m_window.pollEvent(event))
		{
			if ((event.type == sf::Event::Closed) || (Input::IsKeyPressed(Input::KEY::KEY_ESC)))
			{
				m_window.close();
				return;
			}
		}

		float newTime = m_timestepClock.getElapsedTime().asSeconds();
		float frameTime = std::max(0.f, newTime - currentTime);
		currentTime = newTime;

		// Update all items in the level.
		Update(frameTime);

		// Draw all items in the level.
		Draw(frameTime);
	}

	// Shut the game down.
	m_window.close();
}

// Updates the game.
void Game::Update(float timeDelta)
{
	// Check what state the game is in.
	switch (m_gameState)
	{
	case GAME_STATE::MAIN_MENU:
		// Main menu code ...
		break;

	case GAME_STATE::PLAYING:
	{
		//TODO: cache get component call.
		sf::Vector2i mousePos = sf::Mouse::getPosition();

		m_aim.m_transform->SetPosition((float)mousePos.x, (float)mousePos.y);

		// First check if the player is at the exit. If so there's no need to update anything.
		Tile& playerTile = *m_level.GetTile(m_player.m_transform->GetPosition());

		if (playerTile.type == TILE::WALL_DOOR_UNLOCKED)
		{
			// Clear all current items.
			m_items.clear();

			// Clear all current enemies.
			m_enemies.clear();

			// Generate a new room.
			GenerateLevel();

			// Set the key as not collected.
			m_keyUiSprite->setColor(sf::Color(255, 255, 255, 60));
		}
		else
		{
			// Update the player.
			m_player.Update(timeDelta, m_level);
			m_aim.Update(timeDelta);

			// Store the player position as it's used many times.
			sf::Vector2f playerPosition = m_player.m_transform->GetPosition();



			// Update all items.
			UpdateItems(playerPosition, timeDelta);

			// Update level light.
			UpdateLight(playerPosition, timeDelta);

			// Update all enemies.
			UpdateEnemies(playerPosition, timeDelta);

			// Find which torch is nearest the player.
			auto torches = m_level.GetTorches();

			// If there are torches.
			if (!torches->empty())
			{
				// Store the first torch as the current closest.
				std::shared_ptr<Object> nearestTorch = torches->front();
				float lowestDistanceToPlayer = DistanceBetweenPoints(playerPosition, nearestTorch->m_transform->GetPosition());

				for (std::shared_ptr<Object> torch : *torches)
				{
					// Get the distance to the player.
					float distanceToPlayer = DistanceBetweenPoints(playerPosition, torch->m_transform->GetPosition());
					if (distanceToPlayer < lowestDistanceToPlayer)
					{
						lowestDistanceToPlayer = distanceToPlayer;
						nearestTorch = torch;
					}
				}

				m_fireSound.setPosition(nearestTorch->m_transform->GetPosition().x, nearestTorch->m_transform->GetPosition().y, 0.0f);
			}

			// Check if the player has moved grid square.
			Tile* playerCurrentTile = m_level.GetTile(playerPosition);

			if (m_playerPreviousTile != playerCurrentTile)
			{
				// Store the new tile.
				m_playerPreviousTile = playerCurrentTile;

				// Update path finding for all enemies if within range of the player.
				for (const auto& enemy : m_enemies)
				{
					if (DistanceBetweenPoints(enemy->m_transform->GetPosition(), playerPosition) < 300.f)
					{
						enemy->GetComponent<C_Pathfinding>()->Calculate(m_level, playerPosition);
					}
				}
			}


			// Venter the view.
			m_views[static_cast<int>(VIEW::MAIN)].setCenter(playerPosition);
		}
	}
	break;

	case GAME_STATE::GAME_OVER:
		// Game over code
		break;
	}
}

//TODO: fix fixed player light outline.
void Game::UpdateLight(sf::Vector2f playerPosition, float timeDelta)
{
	m_level.Update(timeDelta);

	for (sf::Sprite& sprite : m_lightGrid)
	{
		float tileAlpha = 255.f;
		float distance = 0.f;				// The distance between player and tile.

											// Calculate distance between tile and player.
		distance = DistanceBetweenPoints(sprite.getPosition(), playerPosition);

		// Calculate tile transparency.
		if (distance < 200.f)
		{
			tileAlpha = 0.f;
		}
		else if (distance < 250.f)
		{
			tileAlpha = (51.f * (distance - 200.f)) / 10.f;
		}

		if (tileAlpha != 255.f)
		{
			sprite.setColor(sf::Color(255, 255, 255, static_cast<sf::Uint8>(tileAlpha)));
		}
	}


}

// Spawns a given object type at a random location within the map. Has the option to explicitly set a spawn location.
void Game::SpawnItem(ITEM itemType, sf::Vector2f position)
{
	int objectIndex = 0;

	// Choose a random, unused spawn location.
	sf::Vector2f spawnLocation;

	if ((position.x >= 0.f) || (position.y >= 0.f))
	{
		spawnLocation = position;
	}
	else
	{
		spawnLocation = m_context.m_level->GetRandomSpawnLocation();
	}

	std::unique_ptr<Object> item = ItemFactory::CreateInstance(itemType);
	item->SetContext(&m_context);

	// Set the item position.
	item->m_transform->SetPosition(spawnLocation);

	//TODO: shared context should have reference to list of all items, this should be added to it.
	m_items.push_back(std::move(item));
}

//TODO: add to global object list
void Game::UpdateItems(sf::Vector2f playerPosition, float timeDelta)
{
	// Update all items.
	auto itemIterator = m_items.begin();
	while (itemIterator != m_items.end())
	{
		// Get the item from the iterator.
		Object& item = **itemIterator;

		item.Update(timeDelta);

		if (DistanceBetweenPoints(item.m_transform->GetPosition(), playerPosition) < 40.f)
		{
			//TODO: convert to ActionOnPickUp Components
			switch (item.GetComponent<C_ItemType>()->Get())
			{
			case ITEM::GOLD:
			{
				auto points = item.GetComponent<C_PointsOnPickup>();

				if (points)
				{
					int goldValue = points->GetValue();

					// Add to the gold total.
					m_goldTotal += goldValue;

				}


				// Play gold collect sound effect.
				PlaySound(m_coinPickupSound);
				break;
			}
			case ITEM::GEM:
			{
				auto points = item.GetComponent<C_PointsOnPickup>();

				if (points)
				{
					m_scoreTotal += points->GetValue();
				}

				// Play the gem pickup sound
				PlaySound(m_gemPickupSound);

				break;
			}
			case ITEM::KEY:
			{
				// Unlock the door.
				m_level.UnlockDoor();

				// Play key collect sound.
				PlaySound(m_keyPickupSound);

				// Set the key as collected.
				m_keyUiSprite->setColor(sf::Color::White);

				break;
			}
			case ITEM::POTION:
			{
				switch (item.GetComponent<C_PotionType>()->Get())
				{
				case POTION::ATTACK:
				{
					auto attack = m_player.GetComponent<C_Attack>();
					attack->SetValue(attack->GetValue() + item.GetComponent<C_PointsOnPickup>()->GetValue());
					break;
				}
				case POTION::DEFENSE:
				{
					auto defense = m_player.GetComponent<C_Defense>();
					defense->SetValue(defense->GetValue() + item.GetComponent<C_PointsOnPickup>()->GetValue());
					break;
				}
				case POTION::STRENGTH:
				{
					auto strength = m_player.GetComponent<C_Strength>();
					strength->SetValue(strength->GetValue() + item.GetComponent<C_PointsOnPickup>()->GetValue());
					break;
				}
				case POTION::DEXTERITY:
				{
					auto dexterity = m_player.GetComponent<C_Dexterity>();
					dexterity->SetValue(dexterity->GetValue() + item.GetComponent<C_PointsOnPickup>()->GetValue());
					break;
				}
				case POTION::STAMINA:
				{
					auto stamina = m_player.GetComponent<C_Stamina>();
					stamina->SetValue(stamina->GetValue() + item.GetComponent<C_PointsOnPickup>()->GetValue());
					break;
				}
				}

				break;
			}
			case ITEM::HEART:
			{
				auto heart = item.GetComponent<C_PointsOnPickup>();

				auto health = m_player.GetComponent<C_Health>();
				health->SetCurrent(health->GetCurrent() + heart->GetValue());
				break;
			}
			}

			// Finally, delete the object.
			itemIterator = m_items.erase(itemIterator);
		}
		else
		{
			// Increment iterator.
			++itemIterator;
		}
	}
}

// Updates all enemies in the level.
void Game::UpdateEnemies(sf::Vector2f playerPosition, float timeDelta)
{
	// Store player tile.
	Tile* playerTile = m_level.GetTile(m_player.m_transform->GetPosition());

	//TODO: change to for each loop? this may crash as enemies are removed from list during iteration
	auto enemyIterator = m_enemies.begin();
	while (enemyIterator != m_enemies.end())
	{
		Entity& enemy = **enemyIterator;

		enemy.Update(timeDelta);
		++enemyIterator;
	}
}


// Calculates the distance between two given points.
float Game::DistanceBetweenPoints(sf::Vector2f position1, sf::Vector2f position2)
{
	return (abs(sqrt(((position1.x - position2.x) * (position1.x - position2.x)) + ((position1.y - position2.y) * (position1.y - position2.y)))));
}

// Draw the given string at the given position.
void Game::DrawString(std::string text, sf::Vector2f position, unsigned int size)
{
	// Clear the old data.
	m_stringStream.str(std::string());
	m_string.clear();

	m_stringStream << text;
	m_string = m_stringStream.str();

	m_text.setString(m_string);
	m_text.setFont(m_font);
	m_text.setCharacterSize(size);
	m_text.setPosition(position.x - (m_text.getLocalBounds().width / 2.f), position.y - (m_text.getLocalBounds().height / 2.f));

	m_window.draw(m_text);
}



// Spawns a given number of enemies in the level.
void Game::SpawnEnemy(ENEMY enemyType, sf::Vector2f position)
{
	// Spawn location of enemy(s).
	sf::Vector2f spawnLocation;

	// Choose a random, unused spawn location.
	if ((position.x >= 0.f) || (position.y >= 0.f))
		spawnLocation = position;
	else
		spawnLocation = m_level.GetRandomSpawnLocation();

	// Create the enemy.
	std::unique_ptr<Entity> enemy = EntityFactory::GetInstance()->Create(enemyType, &m_context);

	//TODO: do we need this check? should't it always return an enemy?
	if (enemy)
	{
		enemy->SetContext(&m_context);

		// Set spawn location.
		enemy->m_transform->SetPosition(spawnLocation);

		// Add to list of all enemies.
		m_enemies.push_back(std::move(enemy));
	}
}

// Spawns a given number of a given tile randomly in the level.
void Game::SpawnRandomTiles(TILE tileType, int count)
{
	// Declare the variables we need.
	int rowIndex(0), columnIndex(0), tileIndex(0);

	// Loop the number of tiles we need.
	for (int i = 0; i < count; i++)
	{
		// Declare the variables we need.
		int columnIndex(0), rowIndex(0);

		// Loop until we select a floor tile.
		while (!m_level.IsFloor(columnIndex, rowIndex))
		{
			// Generate a random index for the row and column
			columnIndex = std::rand() % GRID_WIDTH;
			rowIndex = std::rand() % GRID_HEIGHT;
		}

		// Now we change the selected tile.
		m_level.SetTile(columnIndex, rowIndex, tileType);
	}
}

//TODO: this should not be in game class: move to components.
void Game::PlaySound(sf::Sound& sound, sf::Vector2f position)
{
	// Generate and set a random pitch.
	float pitch = (std::rand() % 11 + 95) / 100.f;
	sound.setPitch(pitch);

	// Set the position of the sound.
	sound.setPosition(position.x, position.y, 0.f);

	// Play the sound.
	sound.play();
}

//TODO: implement off-screen culling
void Game::Draw(float timeDelta)
{
	// Clear the screen.
	m_window.clear(sf::Color(3, 3, 3, 225));		// Grey

	// Check what state the game is in.
	switch (m_gameState)
	{
	case GAME_STATE::MAIN_MENU:
		// Draw main menu ...
		break;

	case GAME_STATE::PLAYING:
	{
		// Set the main game view.
		m_window.setView(m_views[static_cast<int>(VIEW::MAIN)]);

		// Draw the level.
		m_level.Draw(m_window, timeDelta);

		//TODO: create drawable component. 
		//TODO: create getcomponents that returns list of all components that match type. Use this to return all drawable.
		for (const auto& item : m_items)
		{
			item->Draw(m_window, timeDelta);
		}

		//TODO: Make this unneseccary by having components have a virtual draw method and sprite inherit it.
		// then have one loop through all game objects and call draw on the object::draw.
		for (const auto& enemy : m_enemies)
		{
			enemy->Draw(m_window, timeDelta);
		}

		m_player.Draw(m_window, timeDelta);

		// Draw level light.
		for (const sf::Sprite& sprite : m_lightGrid)
		{
			m_window.draw(sprite);
		}

		// Switch to UI view.
		m_window.setView(m_views[static_cast<int>(VIEW::UI)]);

		// TODO: cache getcomponent.
		m_aim.GetComponent<C_StaticSprite>()->Draw(m_window, timeDelta);

		// Draw player stats.
		//TODO: cache components.
		DrawString(std::to_string(m_player.GetComponent<C_Attack>()->GetValue()), sf::Vector2f(m_screenCenter.x - 210.f, m_screenSize.y - 30.f), 25);
		DrawString(std::to_string(m_player.GetComponent<C_Defense>()->GetValue()), sf::Vector2f(m_screenCenter.x - 90.f, m_screenSize.y - 30.f), 25);
		DrawString(std::to_string(m_player.GetComponent<C_Strength>()->GetValue()), sf::Vector2f(m_screenCenter.x + 30.f, m_screenSize.y - 30.f), 25);
		DrawString(std::to_string(m_player.GetComponent<C_Dexterity>()->GetValue()), sf::Vector2f(m_screenCenter.x + 150.f, m_screenSize.y - 30.f), 25);
		DrawString(std::to_string(m_player.GetComponent<C_Dexterity>()->GetValue()), sf::Vector2f(m_screenCenter.x + 270.f, m_screenSize.y - 30.f), 25);

		// Draw player score.
		std::string scoreString;

		//TODO: convert to string format
		if (m_scoreTotal > 99999)
		{
			scoreString = std::to_string(m_scoreTotal);
		}
		else if (m_scoreTotal > 9999)
		{
			scoreString = "0" + std::to_string(m_scoreTotal);
		}
		else if (m_scoreTotal > 999)
		{
			scoreString = "00" + std::to_string(m_scoreTotal);
		}
		else if (m_scoreTotal > 99)
		{
			scoreString = "000" + std::to_string(m_scoreTotal);
		}
		else if (m_scoreTotal > 9)
		{
			scoreString = "0000" + std::to_string(m_scoreTotal);
		}
		else
		{
			scoreString = "00000" + std::to_string(m_scoreTotal);
		}

		DrawString(scoreString, sf::Vector2f(m_screenCenter.x - 120.f, 40.f), 40);

		// Draw gold total.
		std::string goldString;

		if (m_goldTotal > 99999)
		{
			goldString = std::to_string(m_goldTotal);
		}
		else if (m_goldTotal > 9999)
		{
			goldString = "0" + std::to_string(m_goldTotal);
		}
		else if (m_goldTotal > 999)
		{
			goldString = "00" + std::to_string(m_goldTotal);
		}
		else if (m_goldTotal > 99)
		{
			goldString = "000" + std::to_string(m_goldTotal);
		}
		else if (m_goldTotal > 9)
		{
			goldString = "0000" + std::to_string(m_goldTotal);
		}
		else
		{
			goldString = "00000" + std::to_string(m_goldTotal);
		}

		DrawString(goldString, sf::Vector2f(m_screenCenter.x + 220.f, 40.f), 40);

		// Draw rest of the UI.
		for (const auto& sprite : m_uiSprites)
		{
			m_window.draw(*sprite);
		}

		// Draw the current room and floor.
		DrawString("Floor " + std::to_string(m_level.GetFloorNumber()), sf::Vector2f(70.f, m_screenSize.y - 65.f), 25);
		DrawString("Room " + std::to_string(m_level.GetRoomNumber()), sf::Vector2f(70.f, m_screenSize.y - 30.f), 25);

		// Draw health and mana bars.
		//TODO: if going to use in future then cache.
		auto health = m_player.GetComponent<C_Health>();
		m_healthBarSprite->setTextureRect(sf::IntRect(0, 0, (int)(213.f / health->GetMax()) * health->GetCurrent(), 8));
		m_window.draw(*m_healthBarSprite);

		//TODO: cache getcomponent.
		auto mana = m_player.GetComponent<C_Mana>();
		m_manaBarSprite->setTextureRect(sf::IntRect(0, 0, (int)(213.f / mana->GetMax()) * mana->GetCurrent(), 8));
		m_window.draw(*m_manaBarSprite);
	}
	break;

	case GAME_STATE::GAME_OVER:
		// Draw game over screen ...
		break;
	}

	// Present the back-buffer to the screen.
	m_window.display();
}