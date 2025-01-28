//Open common->length.h add after
enum EGuildWarState
//
#if defined(ENABLE_GUILDRENEWAL_SYSTEM) || defined(ENABLE_GUILDBANK_LOG)
enum EGuildLogInOut
{
	GUILD_GOLD_TYPE_IN = 0,						// Depositar
	GUILD_GOLD_TYPE_OUT = 1,					// Retirar
	GUILD_GOLD_TYPE_OBJECT_CREATE = 5,			// Construcción
	GUILD_GOLD_TYPE_DRAGON_SP_RECOVER = 6,		// SP
	GUILD_GOLD_TYPE_BUY_GUILD_LAND = 7,			// Tierras
	GUILD_GOLD_TYPE_CHANGE_SMELTER = 8,			// Hornos
	GUILD_GOLD_TYPE_UPGRADE_ALTEROFPOWER = 9,	// Altar
	GUILD_GOLD_TYPE_UPGRADE_GUILDBANK = 10,		// Aknacén
};
