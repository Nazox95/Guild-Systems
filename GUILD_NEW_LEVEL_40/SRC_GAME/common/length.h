//Add
#include "service.h"

//Now Search this:
GUILD_MAX_LEVEL			= 20,

//Replace with this:
#if defined(ENABLE_EXTENDED_GUILD_LEVEL)
	GUILD_MAX_LEVEL			= 40, //Lv 40 for guilds
#else
	GUILD_MAX_LEVEL			= 20, //Original Level
#endif
