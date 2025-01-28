//open GuildManager.cpp add
#include "stdafx.h"
#include "GuildManager.h"
#include "Main.h"
#include "ClientManager.h"
#include "QID.h"
#include "Config.h"
#include <math.h>
#include "../../common/service.h"

//Find and replace
void CGuildManager::ParseResult(SQLResult * pRes)
{
	MYSQL_ROW row;

	while ((row = mysql_fetch_row(pRes->pSQLResult)))
	{
		DWORD GID = strtoul(row[0], NULL, 10);

		TGuild & r_info = TouchGuild(GID);

		strlcpy(r_info.szName, row[1], sizeof(r_info.szName));
		str_to_number(r_info.ladder_point, row[2]);
		str_to_number(r_info.win, row[3]);
		str_to_number(r_info.draw, row[4]);
		str_to_number(r_info.loss, row[5]);
		str_to_number(r_info.gold, row[6]);
		str_to_number(r_info.level, row[7]);
#ifdef ENABLE_GUILD_WAR_SCORE
		for (int i = 0; i < 3; ++i) {
			str_to_number(r_info.winNew[i], row[i+8]);
		}
		for (int i = 0; i < 3; ++i) {
			str_to_number(r_info.drawNew[i], row[i + 11]);
		}
		for (int i = 0; i < 3; ++i) {
			str_to_number(r_info.lossNew[i], row[i + 14]);
		}
#endif

		sys_log(0, 
				"GuildWar: %-24s ladder %-5d win %-3d draw %-3d loss %-3d", 
				r_info.szName,
				r_info.ladder_point,
				r_info.win,
				r_info.draw,
				r_info.loss);
	}
}

//Find and replace:
void CGuildManager::Initialize()
{
	char szQuery[1024];
#ifdef ENABLE_GUILD_WAR_SCORE
	snprintf(szQuery, sizeof(szQuery), "SELECT id, name, ladder_point, win, draw, loss, gold, level, wintype0, wintype1, wintype2, drawtype0, drawtype1, drawtype2, losstype0, losstype1, losstype2 FROM guild%s", GetTablePostfix());
#else
	snprintf(szQuery, sizeof(szQuery), "SELECT id, name, ladder_point, win, draw, loss, gold, level FROM guild%s", GetTablePostfix());
#endif
	std::unique_ptr<SQLMsg> pmsg(CDBManager::instance().DirectQuery(szQuery));

	if (pmsg->Get()->uiNumRows)
		ParseResult(pmsg->Get());

	char str[128 + 1];

	if (!CConfig::instance().GetValue("POLY_POWER", str, sizeof(str)))
		*str = '\0';

	if (!polyPower.Analyze(str))
		sys_err("cannot set power poly: %s", str);
	else
		sys_log(0, "POWER_POLY: %s", str);

	if (!CConfig::instance().GetValue("POLY_HANDICAP", str, sizeof(str)))
		*str = '\0';

	if (!polyHandicap.Analyze(str))
		sys_err("cannot set handicap poly: %s", str);
	else
		sys_log(0, "HANDICAP_POLY: %s", str);

	QueryRanking();
}

//Find and replace:
void CGuildManager::Load(DWORD dwGuildID)
{
	char szQuery[1024];

#ifdef ENABLE_GUILD_WAR_SCORE
	snprintf(szQuery, sizeof(szQuery), "SELECT id, name, ladder_point, win, draw, loss, gold, level, wintype0, wintype1, wintype2, drawtype0, drawtype1, drawtype2, losstype0, losstype1, losstype2 FROM guild%s WHERE id=%u", GetTablePostfix(), dwGuildID);
#else
	snprintf(szQuery, sizeof(szQuery), "SELECT id, name, ladder_point, win, draw, loss, gold, level FROM guild%s WHERE id=%u", GetTablePostfix(), dwGuildID);
#endif
	std::unique_ptr<SQLMsg> pmsg(CDBManager::instance().DirectQuery(szQuery));

	if (pmsg->Get()->uiNumRows)
		ParseResult(pmsg->Get());
}

//add before
void CGuildManager::GuildWarWin(DWORD GID)
//
#ifdef ENABLE_GUILD_WAR_SCORE
int CGuildManager::GetGuildWarType(int GID)
{
	char Query[1024];
	snprintf(Query, sizeof(Query), "SELECT type FROM player.guild_war_reservation WHERE guild1 = %d or guild2 = %d", GID, GID);
	auto pmsg(CDBManager::Instance().DirectQuery(Query));

	if (pmsg->Get()->uiNumRows == 0)
		return 0;

	MYSQL_ROW row = mysql_fetch_row(pmsg->Get()->pSQLResult);
	int warType = 0;

	if (row[0] == 0)
		str_to_number(warType, 0);
	else
		str_to_number(warType, row[0]);

	sys_log(0, "GetGuildWarType: %d", warType);
	return warType;
}
#endif

//Now find and replace (GuildWarWin ; GuildWarLose and GuildWarDraw)
void CGuildManager::GuildWarWin(DWORD GID)
{
	itertype(m_map_kGuild) it = m_map_kGuild.find(GID);

	if (it == m_map_kGuild.end())
		return;

	++it->second.win;
#ifdef ENABLE_GUILD_WAR_SCORE
	char winType[1024];
	int _type = GetGuildWarType(GID);
	++it->second.winNew[_type];
	snprintf(winType, sizeof(winType), "wintype%d", _type);
#endif

	char buf[1024];
#ifdef ENABLE_GUILD_WAR_SCORE
	snprintf(buf, sizeof(buf), "UPDATE guild%s SET win=%d, wintype%d = %d WHERE id=%u", GetTablePostfix(), it->second.win, _type, it->second.winNew[_type], GID);
#else
	snprintf(buf, sizeof(buf), "UPDATE guild%s SET win=%d WHERE id=%u", GetTablePostfix(), it->second.win, GID);
#endif
	CDBManager::instance().AsyncQuery(buf);
}

void CGuildManager::GuildWarLose(DWORD GID)
{
	itertype(m_map_kGuild) it = m_map_kGuild.find(GID);

	if (it == m_map_kGuild.end())
		return;

	++it->second.loss;
#ifdef ENABLE_GUILD_WAR_SCORE
	char lossType[1024];
	int _type = GetGuildWarType(GID);
	++it->second.lossNew[_type];
	snprintf(lossType, sizeof(lossType), "losstype%d", _type);
#endif

	char buf[1024];
#ifdef ENABLE_GUILD_WAR_SCORE
	snprintf(buf, sizeof(buf), "UPDATE guild%s SET loss=%d, losstype%d = %d WHERE id=%u", GetTablePostfix(), it->second.loss, _type, it->second.lossNew[_type], GID);
#else
	snprintf(buf, sizeof(buf), "UPDATE guild%s SET loss=%d WHERE id=%u", GetTablePostfix(), it->second.loss, GID);
#endif
	CDBManager::instance().AsyncQuery(buf);
}

void CGuildManager::GuildWarDraw(DWORD GID)
{
	itertype(m_map_kGuild) it = m_map_kGuild.find(GID);

	if (it == m_map_kGuild.end())
		return;

	++it->second.draw;
#ifdef ENABLE_GUILD_WAR_SCORE
	char drawType[1024];
	int _type = GetGuildWarType(GID);
	++it->second.drawNew[_type];
	snprintf(drawType, sizeof(drawType), "drawtype%d", _type);
#endif

	char buf[1024];
#ifdef ENABLE_GUILD_WAR_SCORE
	snprintf(buf, sizeof(buf), "UPDATE guild%s SET draw=%d, drawtype%d = %d WHERE id=%u", GetTablePostfix(), it->second.draw, _type, it->second.drawNew[_type], GID);
#else
	snprintf(buf, sizeof(buf), "UPDATE guild%s SET draw=%d WHERE id=%u", GetTablePostfix(), it->second.draw, GID);
#endif
	CDBManager::instance().AsyncQuery(buf);
}

//Find:
void CGuildManager::ChangeLadderPoint(DWORD GID, int change)
[...]
	sys_log(0, "GuildManager::ChangeLadderPoint %u %d", GID, r.ladder_point);
	sys_log(0, "%s", buf);

	// Packet º¸³»±â
	TPacketGuildLadder p;

	p.dwGuild = GID;
	p.lLadderPoint = r.ladder_point;
	p.lWin = r.win;
	p.lDraw = r.draw;
	p.lLoss = r.loss;
//add
#ifdef ENABLE_GUILD_WAR_SCORE
	for (int i = 0; i < 3; ++i)
	{
		p.lWinNew[i] = r.winNew[i];
		p.lDrawNew[i] = r.drawNew[i];
		p.lLossNew[i] = r.lossNew[i];
	}
#endif
