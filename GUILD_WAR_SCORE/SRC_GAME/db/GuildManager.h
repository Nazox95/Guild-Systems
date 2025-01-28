//Open GuildManager.h add
// vim:ts=8 sw=4
#ifndef __INC_GUILD_MANAGER_H
#define __INC_GUILD_MANAGER_H

#include "Peer.h"
#include <queue>
#include <utility>
#include "../../libsql/libsql.h"
#include "../../libpoly/Poly.h"
#include "../../common/service.h"
//Find and replace:
typedef struct SGuild
{
#ifdef ENABLE_GUILD_WAR_SCORE
	SGuild() : ladder_point(0), win(0), draw(0), loss(0), gold(0), level(0), winNew{ 0, 0, 0 }, drawNew{ 0, 0, 0 }, lossNew{ 0, 0, 0 }
#else
	SGuild() : ladder_point(0), win(0), draw(0), loss(0), gold(0), level(0)
#endif
	{
		memset(szName, 0, sizeof(szName));
	}

	char szName[GUILD_NAME_MAX_LEN+1];
	int	ladder_point;
	int	win;
	int	draw;
	int	loss;
	int	gold;
	int	level;
#ifdef ENABLE_GUILD_WAR_SCORE
	int winNew[3];
	int drawNew[3];
	int lossNew[3];
#endif
} TGuild;

//find 
   private:
	void ParseResult(SQLResult * pRes);

	void RemoveWar(DWORD GID1, DWORD GID2);	// erase war from m_WarMap and set end on priority queue

	void WarEnd(DWORD GID1, DWORD GID2, bool bDraw = false);

	int GetLadderPoint(DWORD GID);
//add
#ifdef ENABLE_GUILD_WAR_SCORE
	int GetGuildWarType(int GID);
#endif
