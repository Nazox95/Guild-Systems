//Add
#include "service.h"

//Now Search this:
GUILD_MAX_LEVEL			= 20,

//Replace with this:
#if defined(ENABLE_GUILDRENEWAL_SYSTEM) && defined(ENABLE_EXTENDED_GUILD_LEVEL)
	GUILD_MAX_LEVEL			= 40,
	MAX_GUILD_DONATION_PER_DAY = 3,
#else
	GUILD_MAX_LEVEL			= 20,
#endif
