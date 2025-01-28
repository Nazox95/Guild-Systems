//Open common- tables.h find and replace 
typedef struct SPacketGuildWar
{
	BYTE	bType;
	BYTE	bWar;
#ifdef ENABLE_NEW_WAR_OPTIONS
	BYTE	bRound;
	BYTE	bPoints;
	BYTE	bTime;
#endif
	DWORD	dwGuildFrom;
	DWORD	dwGuildTo;
	long	lWarPrice;
	long	lInitialScore;
} TPacketGuildWar;

//find and replace:
typedef struct SGuildReserve
{
	DWORD       dwID;
	DWORD       dwGuildFrom;
	DWORD       dwGuildTo;
	DWORD       dwTime;
	BYTE        bType;
#ifdef ENABLE_NEW_WAR_OPTIONS
	BYTE		bRound;
	BYTE		bPoints;
	BYTE		bTime;
#endif
	long        lWarPrice;
	long        lInitialScore;
	bool        bStarted;
	DWORD	dwBetFrom;
	DWORD	dwBetTo;
	long	lPowerFrom;
	long	lPowerTo;
	long	lHandicap;
} TGuildWarReserve;
