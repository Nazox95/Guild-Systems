//Open guild.h find
enum
{
	GUILD_AUTH_ADD_MEMBER	= (1 << 0),
	GUILD_AUTH_REMOVE_MEMBER	= (1 << 1),
	GUILD_AUTH_NOTICE		= (1 << 2),
	GUILD_AUTH_USE_SKILL	= (1 << 3),
//add
#ifdef ENABLE_GUILDRENEWAL_SYSTEM
	GUILD_AUTH_WAR = (1 << 4),
	GUILD_AUTH_BANK = (1 << 5),
#endif
};
