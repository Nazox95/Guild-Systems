//Open common tables.h add
#include "length.h"
#include "service.h"
#include "item_length.h"
//find and replace 
typedef struct SPacketGuildLadder
{
	DWORD dwGuild;
	long lLadderPoint;
	long lWin;
	long lDraw;
	long lLoss;
#ifdef ENABLE_GUILD_WAR_SCORE
	long lWinNew[3];
	long lDrawNew[3];
	long lLossNew[3];
#endif
} TPacketGuildLadder;
