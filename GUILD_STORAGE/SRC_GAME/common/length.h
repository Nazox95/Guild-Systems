//Open length.h find 
enum EWindows
{
	RESERVED_WINDOW,
	INVENTORY,
	EQUIPMENT,
	SAFEBOX,
	MALL,
	DRAGON_SOUL_INVENTORY,
	BELT_INVENTORY,
//add
#ifdef ENABLE_GUILDSTORAGE_SYSTEM
	GUILDBANK,
#endif
#ifdef __AUCTION__
	AUCTION,
#endif
	GROUND
};

//find
	bool IsValidItemPosition() const
	{
		switch (window_type)
		{
		case RESERVED_WINDOW:
			return false;
		case INVENTORY:
		case EQUIPMENT:
		case BELT_INVENTORY:
			return cell < INVENTORY_AND_EQUIP_SLOT_MAX;
		case DRAGON_SOUL_INVENTORY:
			return cell < (DRAGON_SOUL_INVENTORY_MAX_NUM);
		case SAFEBOX:
		case MALL:
//add
#ifdef ENABLE_GUILDSTORAGE_SYSTEM
		case GUILDBANK:
#endif
			return false;
		default:
			return false;
		}
		return false;
	}
