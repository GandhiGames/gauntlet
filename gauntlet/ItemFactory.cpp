#include "PCH.h"
#include "ItemFactory.h"

std::unique_ptr<Object> ItemFactory::CreateInstance(ITEM type)
{
	Object item;
	item.AddComponent<C_AnimatedSprite>();
	item.AddComponent<C_ItemType>();

	switch (type)
	{
	case ITEM::POTION:
	{
		std::string spriteFilePath;

		auto potionType = item.AddComponent<C_PotionType>();
		potionType->Set(static_cast<POTION>(std::rand() % static_cast<int>(POTION::COUNT)));

		item.AddComponent<C_PointsOnPickup>()->SetValue(std::rand() % 11 + 5);

		// Set stat modifiers, sprite file path, and item name.
		switch (potionType->Get())
		{
		case POTION::ATTACK:
			spriteFilePath = "../resources/loot/potions/spr_potion_attack.png";
			break;

		case POTION::DEFENSE:
			spriteFilePath = "../resources/loot/potions/spr_potion_defense.png";
			break;

		case POTION::STRENGTH:
			spriteFilePath = "../resources/loot/potions/spr_potion_strength.png";
			break;

		case POTION::DEXTERITY:
			spriteFilePath = "../resources/loot/potions/spr_potion_dexterity.png";
			break;

		case POTION::STAMINA:
			spriteFilePath = "../resources/loot/potions/spr_potion_stamina.png";
			break;
		}

		item.GetComponent<C_AnimatedSprite>()->SetSprite(TextureManager::GetTexture(TextureManager::AddTexture(spriteFilePath)), false, 8, 12);

		//TODO: move to component?
		item.GetComponent<C_ItemType>()->Set(ITEM::POTION);

		break;
	}
	case ITEM::GEM:
	{
		item.GetComponent<C_AnimatedSprite>()->SetSprite(TextureManager::GetTexture(TextureManager::AddTexture("../resources/loot/gem/spr_pickup_gem.png")), false, 8, 12);
		item.AddComponent<C_PointsOnPickup>()->SetValue(std::rand() % 100);
		item.GetComponent<C_ItemType>()->Set(ITEM::GEM);

		break;
	}
	case ITEM::GOLD:
	{
		int goldValue = std::rand() % 21 + 5;

		item.AddComponent<C_PointsOnPickup>()->SetValue(goldValue);

		// Choose a sprite based on the gold value.
		int textureID;

		if (goldValue < 9)
		{
			textureID = TextureManager::AddTexture("../resources/loot/gold/spr_pickup_gold_small.png");
		}
		else if (goldValue >= 16)
		{
			textureID = TextureManager::AddTexture("../resources/loot/gold/spr_pickup_gold_large.png");
		}
		else
		{
			textureID = TextureManager::AddTexture("../resources/loot/gold/spr_pickup_gold_medium.png");
		}

		// Set the sprite.
		item.GetComponent<C_AnimatedSprite>()->SetSprite(TextureManager::GetTexture(textureID), false, 8, 12);

		// Set the item type.
		item.GetComponent<C_ItemType>()->Set(ITEM::GOLD);

		break;
	}
	case ITEM::KEY:
	{
		int textureID = TextureManager::AddTexture("../resources/loot/key/spr_pickup_key.png");
		item.GetComponent<C_AnimatedSprite>()->SetSprite(TextureManager::GetTexture(textureID), false, 8, 12);

		auto title = item.AddComponent<C_Title>();
		title->Set("Key");

		item.GetComponent<C_ItemType>()->Set(ITEM::KEY);
		break;
	}
	case ITEM::HEART:
	{
		item.GetComponent<C_AnimatedSprite>()->SetSprite(TextureManager::GetTexture(TextureManager::AddTexture("../resources/loot/heart/spr_pickup_heart.png")), false, 8, 12);

		item.AddComponent<C_PointsOnPickup>()->SetValue(std::rand() % 11 + 10);

		item.GetComponent<C_ItemType>()->Set(ITEM::HEART);

		break;
	}
	}

	return std::make_unique<Object>(item);
}