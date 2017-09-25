#include "PCH.h"
#include "Game.h"

// Default constructor.
Game::Game(sf::RenderWindow* window) :
	m_window(*window),
	m_isRunning(true),
	m_string(""),
	m_screenSize({ 0, 0 }),
	m_screenCenter({ 0, 0 }),
	m_newLevelRequested(false)
{
	m_elapsed = m_clock.restart().asSeconds();

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
	m_player.SetContext(&m_context);
	m_player.AddComponent<C_ProjectileAttack>();
	m_player.AddComponent<C_PlayerTorch>();
	m_player.AddComponent<C_Inventory>();
	m_player.AddComponent<C_DistanceBasedCollision>();
	m_player.AddComponent<C_EndLevelTileCollision>();

	//m_context.m_enemies = &m_enemies;
	//m_context.m_items = &m_items;
	//m_context.m_projectiles = &m_projectiles;
	m_context.m_newObjects = &m_newObjects;
	m_context.m_objects = &m_objects;
	m_context.m_level = &m_level;
	m_context.m_window = &m_window;
	m_context.m_lightGrid = &m_lightGrid;
	m_context.m_player = &m_player;
	m_context.m_game = this;
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

	//Create object responsible for updating tourch sound.
	Object torchSound;
	//TODO: shouldn't need to remember to do this for objects!
	torchSound.SetContext(&m_context);
	torchSound.AddComponent<C_ClosestTorchSoundPosition>();
	m_objects.push_back(std::make_unique<Object>(torchSound));

	// Builds the light grid.
	ConstructLightGrid();

	// Define the game views.
	m_views[static_cast<int>(VIEW::MAIN)] = m_window.getDefaultView();
	m_views[static_cast<int>(VIEW::MAIN)].zoom(0.5f);
	m_views[static_cast<int>(VIEW::UI)] = m_window.getDefaultView();

	// Load all game sounds.
	int soundBufferId;

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
	int rowIndex(0), columnIndex(0), tileIndex(0);
	for (int i = 0; i < 15; i++)
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
		m_level.SetTile(columnIndex, rowIndex, TILE::FLOOR_ALT);
	}

	//TODO: create aim sprite as child object of player.
	int textureID = TextureManager::AddTexture("../resources/ui/spr_aim.png");
	
	//Object aim;
	auto aimSprite = m_aim.AddComponent<C_StaticSprite>();
	aimSprite->GetSprite().setTexture(TextureManager::GetTexture(textureID));
	aimSprite->GetSprite().setOrigin(sf::Vector2f(16.5f, 16.5f));
	aimSprite->GetSprite().setScale(2.f, 2.f);
	m_aim.AddComponent<C_CentreOnMousePosition>();

	Object aim;
	auto aimSprite2 = aim.AddComponent<C_StaticSprite>();
	aimSprite2->GetSprite().setTexture(TextureManager::GetTexture(textureID));
	aimSprite2->GetSprite().setOrigin(sf::Vector2f(16.5f, 16.5f));
	aimSprite2->GetSprite().setScale(2.f, 2.f);
	aim.AddComponent<C_CentreOnMousePosition>();
	m_objects.push_back(std::make_unique<Object>(aim));
	//aim.m_transform->SetParent(m_player.m_transform);
	//aim.m_transform->SetPosition(sf::Vector2f(1.f, 1.f));
	//m_objects.push_back(std::make_unique<Object>(aim));
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
	m_playerUiSprite->setTexture(TextureManager::GetTexture(m_playerUiTextureIDs[static_cast<int>(m_player.GetComponent<C_PlayerClass>()->Get())]));
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

void Game::RequestNewLevel()
{
	m_newLevelRequested = true;
}

// Generates a new level.
void Game::GenerateLevel()
{
	// Generate a new level.
	m_level.GenerateLevel();

	// Add a key to the level.
	SpawnItem(ITEM::KEY);
	assert(m_objects[0]->m_transform->m_owner != nullptr);

	// Populate the level with items.
//	PopulateLevel();

	assert(m_objects[0]->m_transform->m_owner != nullptr);

	// Moves the player to the start.
	m_player.m_transform->SetPosition(m_level.SpawnLocation());

	m_keyUiSprite->setColor(sf::Color(255, 255, 255, 60));
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
			ENEMY enemyType = static_cast<ENEMY>(std::rand() % static_cast<int>(ENEMY::COUNT));

			//TODO: do not spawn enemies outside of map!
			sf::Vector2f position = { -1.f, -1.f };

			sf::Vector2f spawnLocation;

			// Choose a random, unused spawn location.
			if ((position.x >= 0.f) || (position.y >= 0.f))
				spawnLocation = position;
			else
				spawnLocation = m_level.GetRandomSpawnLocation();

			// Create the enemy.
			std::unique_ptr<Object> enemy = EntityFactory::GetInstance()->Create(enemyType, &m_context);

			//TODO: do we need this check? should't it always return an enemy?
			if (enemy)
			{
				enemy->SetContext(&m_context);

				// Set spawn location.
				enemy->m_transform->SetPosition(spawnLocation);

				// Add to list of all enemies.
				//m_enemies.push_back(std::move(enemy));
			//	m_objects.push_back(std::move(enemy));
			}
		}
	}
}

// Returns the running state of the game.
bool Game::IsRunning()
{
	return m_isRunning;
}

// Updates the game.
void Game::Update()
{
	// Check if the game was closed.
	sf::Event event;
	if (m_window.pollEvent(event))
	{
		if ((event.type == sf::Event::Closed) || (Input::IsKeyPressed(Input::KEY::KEY_ESC)))
		{
			m_isRunning = false;
			m_window.close();
			return;
		}
	}

	// Update the player.
	m_player.Update(m_elapsed, m_level);
	m_aim.Update(m_elapsed);

	for (const auto& obj : m_objects)
	{
		obj->Update(m_elapsed);
	}

	// Update level light.
	//TODO: fix fixed player light outline.
	m_level.Update(m_elapsed);

	sf::Vector2f playerPosition = m_player.m_transform->GetPosition();

	// Center the view.
	m_views[static_cast<int>(VIEW::MAIN)].setCenter(playerPosition);
}

//TODO: implement off-screen culling
void Game::Draw()
{
	// Clear the screen.
	m_window.clear(sf::Color(3, 3, 3, 225));		// Grey

		// Set the main game view.
	m_window.setView(m_views[static_cast<int>(VIEW::MAIN)]);

	// Draw the level.
	m_level.Draw(m_window, m_elapsed);

	//std::sort(m_objects.begin(), m_objects.end(),
		//[](Object const& a, Object const& b) { return a.get < b.v; });

	for (const auto& obj : m_objects)
	{
		obj->Draw(m_window, m_elapsed);
	}

	m_player.Draw(m_window, m_elapsed);

	// Draw level light.
	for (const sf::Sprite& sprite : m_lightGrid)
	{
		m_window.draw(sprite);
	}

	// Switch to UI view.
	m_window.setView(m_views[static_cast<int>(VIEW::UI)]);

	m_aim.Draw(m_window, m_elapsed);

	// Draw player stats.
	//TODO: cache components.
	DrawString(std::to_string(m_player.GetComponent<C_Attack>()->GetValue()), sf::Vector2f(m_screenCenter.x - 210.f, m_screenSize.y - 30.f), 25);
	DrawString(std::to_string(m_player.GetComponent<C_Defense>()->GetValue()), sf::Vector2f(m_screenCenter.x - 90.f, m_screenSize.y - 30.f), 25);
	DrawString(std::to_string(m_player.GetComponent<C_Strength>()->GetValue()), sf::Vector2f(m_screenCenter.x + 30.f, m_screenSize.y - 30.f), 25);
	DrawString(std::to_string(m_player.GetComponent<C_Dexterity>()->GetValue()), sf::Vector2f(m_screenCenter.x + 150.f, m_screenSize.y - 30.f), 25);
	DrawString(std::to_string(m_player.GetComponent<C_Dexterity>()->GetValue()), sf::Vector2f(m_screenCenter.x + 270.f, m_screenSize.y - 30.f), 25);

	// Draw player score.
	std::string scoreString;

	int scoreTotal = m_player.GetComponent<C_Inventory>()->m_score;

	//TODO: convert to string format
	if (scoreTotal > 99999)
	{
		scoreString = std::to_string(scoreTotal);
	}
	else if (scoreTotal > 9999)
	{
		scoreString = "0" + std::to_string(scoreTotal);
	}
	else if (scoreTotal > 999)
	{
		scoreString = "00" + std::to_string(scoreTotal);
	}
	else if (scoreTotal > 99)
	{
		scoreString = "000" + std::to_string(scoreTotal);
	}
	else if (scoreTotal > 9)
	{
		scoreString = "0000" + std::to_string(scoreTotal);
	}
	else
	{
		scoreString = "00000" + std::to_string(scoreTotal);
	}

	DrawString(scoreString, sf::Vector2f(m_screenCenter.x - 120.f, 40.f), 40);

	// Draw gold total.
	std::string goldString;
	int goldTotal = m_player.GetComponent<C_Inventory>()->m_gold;

	if (goldTotal > 99999)
	{
		goldString = std::to_string(goldTotal);
	}
	else if (goldTotal > 9999)
	{
		goldString = "0" + std::to_string(goldTotal);
	}
	else if (goldTotal > 999)
	{
		goldString = "00" + std::to_string(goldTotal);
	}
	else if (goldTotal > 99)
	{
		goldString = "000" + std::to_string(goldTotal);
	}
	else if (goldTotal > 9)
	{
		goldString = "0000" + std::to_string(goldTotal);
	}
	else
	{
		goldString = "00000" + std::to_string(goldTotal);
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


	// Present the back-buffer to the screen.
	m_window.display();
}

void Game::LateUpdate()
{
	m_aim.LateUpdate(m_elapsed);
	m_player.LateUpdate(m_elapsed);

	for (const auto& obj : m_objects)
	{
		obj->LateUpdate(m_elapsed);
	}

	auto objIterator = m_objects.begin();
	while (objIterator != m_objects.end())
	{
		auto obj = **objIterator;

		bool remove = obj.IsQueuedForRemoval();

		if (remove)
		{
			objIterator = m_objects.erase(objIterator);
		}
		else
		{
			++objIterator;
		}
	}


	// Move newly created objects to global list.
	for (auto& obj : m_newObjects)
	{
		m_objects.push_back(std::move(obj));
	}
	m_newObjects.clear();


	if (m_newLevelRequested)
	{
		m_newLevelRequested = false;
		GenerateLevel();
	}

	m_elapsed = m_clock.restart().asSeconds();
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
	item->m_transform->SetPosition(spawnLocation);

	//TODO: shouldn't need to do anything extra to object retrieved from factory?
	if (itemType == ITEM::KEY)
	{
		Object keyTitle;
		keyTitle.SetContext(&m_context);
		auto title = keyTitle.AddComponent<C_Title>();
		title->Set("Key");
		keyTitle.m_transform->SetParent(item->m_transform);
		keyTitle.m_transform->SetPosition(sf::Vector2f(0.f, 0.f));

		auto newObj = std::make_unique<Object>(keyTitle);
		m_objects.push_back(std::move(newObj));

		m_objects.push_back(std::move(item));
	}


}