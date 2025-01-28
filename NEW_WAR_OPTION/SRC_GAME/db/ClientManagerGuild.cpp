//open ClientManagerGuild.cpp add
#include "stdafx.h"
#include "ClientManager.h"
#include "Main.h"
#include "Config.h"
#include "DBManager.h"
#include "QID.h"
#include "GuildManager.h"
#include "../../common/service.h"

//Find and replace 
void CClientManager::GuildWar(CPeer* peer, TPacketGuildWar* p)
{
	switch (p->bWar)
	{
		case GUILD_WAR_SEND_DECLARE:
			sys_log(0, "GuildWar: GUILD_WAR_SEND_DECLARE type(%s) guild(%d - %d)",  __GetWarType(p->bType), p->dwGuildFrom, p->dwGuildTo);
#ifdef ENABLE_NEW_WAR_OPTIONS
			CGuildManager::Instance().AddDeclare(p->bType, p->dwGuildFrom, p->dwGuildTo, p->bRound, p->bPoints, p->bTime);
#else
			CGuildManager::Instance().AddDeclare(p->bType, p->dwGuildFrom, p->dwGuildTo);
#endif
			break;

		case GUILD_WAR_REFUSE:
			sys_log(0, "GuildWar: GUILD_WAR_REFUSE type(%s) guild(%d - %d)", __GetWarType(p->bType), p->dwGuildFrom, p->dwGuildTo);
			CGuildManager::Instance().RemoveDeclare(p->dwGuildFrom, p->dwGuildTo);
			break;
			/*
			   case GUILD_WAR_WAIT_START:
			   CGuildManager::Instance().RemoveDeclare(p->dwGuildFrom, p->dwGuildTo);

			   if (!CGuildManager::Instance().WaitStart(p))
			   p->bWar = GUILD_WAR_CANCEL;

			   break;
			   */

		case GUILD_WAR_WAIT_START:
			sys_log(0, "GuildWar: GUILD_WAR_WAIT_START type(%s) guild(%d - %d)", __GetWarType(p->bType), p->dwGuildFrom, p->dwGuildTo);
		case GUILD_WAR_RESERVE:	// ±æµåÀü ¿¹¾à
			if (p->bWar != GUILD_WAR_WAIT_START)
				sys_log(0, "GuildWar: GUILD_WAR_RESERVE type(%s) guild(%d - %d)", __GetWarType(p->bType), p->dwGuildFrom, p->dwGuildTo);
			CGuildManager::Instance().RemoveDeclare(p->dwGuildFrom, p->dwGuildTo);

			if (!CGuildManager::Instance().ReserveWar(p))
				p->bWar = GUILD_WAR_CANCEL;
			else
				p->bWar = GUILD_WAR_RESERVE;

			break;

		case GUILD_WAR_ON_WAR:		// ±æµåÀüÀ» ½ÃÀÛ ½ÃÅ²´Ù. (ÇÊµåÀüÀº ¹Ù·Î ½ÃÀÛ µÊ)
			sys_log(0, "GuildWar: GUILD_WAR_ON_WAR type(%s) guild(%d - %d)", __GetWarType(p->bType), p->dwGuildFrom, p->dwGuildTo);
			CGuildManager::Instance().RemoveDeclare(p->dwGuildFrom, p->dwGuildTo);
#ifdef ENABLE_NEW_WAR_OPTIONS
			CGuildManager::Instance().StartWar(p->bType, p->dwGuildFrom, p->dwGuildTo, p->bRound, p->bPoints, p->bTime);
#else
			CGuildManager::Instance().StartWar(p->bType, p->dwGuildFrom, p->dwGuildTo);
#endif
			break;

		case GUILD_WAR_OVER:		// ±æµåÀü Á¤»ó Á¾·á
			sys_log(0, "GuildWar: GUILD_WAR_OVER type(%s) guild(%d - %d)", __GetWarType(p->bType), p->dwGuildFrom, p->dwGuildTo);
			CGuildManager::Instance().RecvWarOver(p->dwGuildFrom, p->dwGuildTo, p->bType, p->lWarPrice);
			break;

		case GUILD_WAR_END:		// ±æµåÀü ºñÁ¤»ó Á¾·á
			sys_log(0, "GuildWar: GUILD_WAR_END type(%s) guild(%d - %d)", __GetWarType(p->bType), p->dwGuildFrom, p->dwGuildTo);
			CGuildManager::Instance().RecvWarEnd(p->dwGuildFrom, p->dwGuildTo);
			return; // NOTE: RecvWarEnd¿¡¼­ ÆÐÅ¶À» º¸³»¹Ç·Î µû·Î ºê·ÎµåÄ³½ºÆÃ ÇÏÁö ¾Ê´Â´Ù.

		case GUILD_WAR_CANCEL :
			sys_log(0, "GuildWar: GUILD_WAR_CANCEL type(%s) guild(%d - %d)", __GetWarType(p->bType), p->dwGuildFrom, p->dwGuildTo);
			CGuildManager::Instance().CancelWar(p->dwGuildFrom, p->dwGuildTo);
			break;
	}

	ForwardPacket(HEADER_DG_GUILD_WAR, p, sizeof(TPacketGuildWar));
}
