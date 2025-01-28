//Find the function:
typedef struct SPacketGuildExpUpdate

//Replace the function with this:
typedef struct SPacketGuildExpUpdate
{
	DWORD guild_id;
#if defined(ENABLE_EXTENDED_GUILD_LEVEL)
	DWORD amount; //Fix
#else
	int amount; //Original
#endif
} TPacketGuildExpUpdate;
