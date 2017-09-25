//-------------------------------------------------------------------------------------
// Game.h
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Written by Dale Green. Copyright (c) Packt Publishing. All rights reserved.
//-------------------------------------------------------------------------------------
#ifndef GAME_H
#define GAME_H

#include "EntityFactory.h"
#include "ItemFactory.h"
#include "Player.h"
#include "Level.h"
#include "Humanoid.h"
#include "SharedContext.h"

static float const FPS = 60.0;						// Constant for fixed time - step loop. We'll lock it at 60fps.
static float const MS_PER_STEP = 1.0f / FPS;		// Roughly (0.017) @ 60fps.
static int const MAX_ITEM_SPAWN_COUNT = 50;			// The maximum number of items that can be spawned each room.
static int const MAX_ENEMY_SPAWN_COUNT = 5;		// The maximum number of enemies that can be spawned each room.

class Game
{
public:
	/**
	 * Constructor.
	 * @param window A pointer to the main render window.
	 */
	Game(sf::RenderWindow* window);

	/**
	 * Initializes the game object by initializing all objects the main game uses.
	 * @return True if the game was initialized successfully.
	 */
	void Initialize();

	/**
	 * Returns true if the game is currently running.
	 * @return True if the game is running.
	 */
	bool IsRunning();


	void Update();
	void Draw();
	void LateUpdate();

	void RequestNewLevel();

private:

	//TODO: move to Util class
	/**
	* Calculates the distance between two points
	* @param position1 The position of the first point.
	* @param position2 The position of the second item.
	* @return The distance between the two points.
	*/
	float DistanceBetweenPoints(const sf::Vector2f& position1, const sf::Vector2f& position2)
	{
		return (abs(sqrt(((position1.x - position2.x) * (position1.x - position2.x)) + ((position1.y - position2.y) * (position1.y - position2.y)))));
	}

	/**
	 * Populates the current game room with items and enemies.
	 */
	void PopulateLevel();

	/**
	 * Loads all sprites needed for the UI.
	 */
	void LoadUI();

	/**
	 * Generates a new level.
	 */
	void GenerateLevel();



	/**
	 * Draws text at a given location on the screen.
	 * @param text The string you wish to draw.
	 * @param position The top-left position of the string.
	 * @param size (Optional) The font-size to use. Default value is 10.
	 */
	void DrawString(std::string text, sf::Vector2f position, unsigned int size = 10);


	void SpawnItem(ITEM itemType, sf::Vector2f position = { -1.f, -1.f });

	/**
	 * Constructs the grid of sprites that are used to draw the game light system.
	 */
	void ConstructLightGrid();

private:

	SharedContext m_context;

	/**
	 * The main application window.
	 */
	sf::RenderWindow& m_window;

	/**
	 * An array of the different views the game needs.
	 */
	sf::View m_views[static_cast<int>(VIEW::COUNT)];

	/**
	 * The default font to be used when drawing text.
	 */
	sf::Font m_font;

	std::vector<std::unique_ptr<Object>> m_newObjects;
	std::vector<std::unique_ptr<Object>> m_objects;

	/**
	 * A bool that tracks the running state of the game. It's used in the main loop.
	 */
	bool m_isRunning;

	/**
	 * The main level object. All data and functionally regarding the level lives in this class/object.
	 */
	Level m_level;

	/**
	 * The main player object. Only one instance of this object should be created at any one time.
	 */
	Player m_player;

	/**
	 * String stream used by the DrawText() function.
	 */
	std::ostringstream m_stringStream;

	/**
	 * String used by the DrawText() function.
	 */
	std::string m_string;

	/**
	 * Text used by the DrawText() function.
	 */
	sf::Text m_text;

	/**
	 * A vector containing all sprites that make up the lighting grid.
	 */
	std::vector<sf::Sprite> m_lightGrid;

	/**
	 * The size of the screen and window.
	 */
	sf::Vector2u m_screenSize;

	/**
	* The center of the screen.
	*/
	sf::Vector2f m_screenCenter;

	/**
	 * An array of texture for the player in the UI.
	 */
	int m_playerUiTextureIDs[static_cast<int>(PLAYER_CLASS::COUNT)];

	/**
	 * The sprite that shows the player class in the UI.
	 */
	std::shared_ptr<sf::Sprite> m_playerUiSprite;

	/**
	 * The sprite used to show how many coins the player has.
	 */
	std::shared_ptr<sf::Sprite> m_coinUiSprite;

	/**
	* The sprite used to show how much score the player has.
	*/
	std::shared_ptr<sf::Sprite> m_gemUiSprite;

	/**
	 * Key ui sprite.
	 */
	std::shared_ptr<sf::Sprite> m_keyUiSprite;

	/**
	 * The sprite for the players attack stat.
	 */
	std::shared_ptr<sf::Sprite> m_attackStatSprite;

	/**
	 * The texture IDs for the attack stat textures.
	 */
	int m_attackStatTextureIDs[2];

	/**
	* The sprite for the players defense stat.
	*/
	std::shared_ptr<sf::Sprite> m_defenseStatSprite;

	/**
	* The texture IDs for the defense stat textures.
	*/
	int m_defenseStatTextureIDs[2];

	/**
	* The sprite for the players strength stat.
	*/
	std::shared_ptr<sf::Sprite> m_strengthStatSprite;

	/**
	* The texture IDs for the strength stat textures.
	*/
	int m_strengthStatTextureIDs[2];

	/**
	* The sprite for the players dexterity stat.
	*/
	std::shared_ptr<sf::Sprite> m_dexterityStatSprite;

	/**
	* The texture IDs for the dexterity stat textures.
	*/
	int m_dexterityStatTextureIDs[2];

	/**
	* The sprite for the players stamina stat.
	*/
	std::shared_ptr<sf::Sprite> m_staminaStatSprite;

	/**
	* The texture IDs for the stamina stat textures.
	*/
	int m_staminaStatTextureIDs[2];

	/**
	 * Sprite for the health bar.
	 */
	std::shared_ptr<sf::Sprite> m_healthBarSprite;

	/**
	* Sprite for the health bar outline.
	*/
	std::shared_ptr<sf::Sprite> m_healthBarOutlineSprite;

	/**
	 * Sprite for the mana bar.
	 */
	std::shared_ptr<sf::Sprite> m_manaBarSprite;

	/**
	* Sprite for the mana bar outline.
	*/
	std::shared_ptr<sf::Sprite> m_manaBarOutlineSprite;

	/**
	 * A vector of all ui sprites.
	 */
	std::vector<std::shared_ptr<sf::Sprite>> m_uiSprites;

	/**
	 * Gem pickup sound.
	 */
	sf::Sound m_gemPickupSound;

	/**
	 * Coin pickup sound.
	 */
	sf::Sound m_coinPickupSound;

	/**
	* Key collect sound.
	*/
	sf::Sound m_keyPickupSound;

	/**
	 * The main music.
	 */
	sf::Music m_music;

	Object m_aim;

	sf::Clock m_clock;
	float m_elapsed;

	bool m_newLevelRequested;

};
#endif