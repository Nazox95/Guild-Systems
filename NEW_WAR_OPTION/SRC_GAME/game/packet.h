//Open packet.h find and replace
typedef struct packet_guild_war
{
	DWORD	dwGuildSelf;
	DWORD	dwGuildOpp;
	BYTE	bType;
	BYTE 	bWarState;
#ifdef ENABLE_NEW_WAR_OPTIONS
	BYTE	bRound;
	BYTE	bPoints;
	DWORD	dwTime;
#endif
} TPacketGCGuildWar;
