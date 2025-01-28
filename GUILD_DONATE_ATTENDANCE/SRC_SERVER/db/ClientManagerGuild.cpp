//Open ClientManagerGuild.cpp
//add
#include "../../common/service.h"

//Find the function and replace:
void CClientManager::GuildAddMember(CPeer* peer, TPacketGDGuildAddMember * p)
{
	CGuildManager::instance().TouchGuild(p->dwGuild);
	sys_log(0, "GuildAddMember %u %u", p->dwGuild, p->dwPID);

	char szQuery[512];

	snprintf(szQuery, sizeof(szQuery), 
			"INSERT INTO guild_member%s VALUES(%u, %u, %d, 0, 0"
#ifdef ENABLE_GUILD_DONATE_ATTENDANCE
		", now(), 0, now(), 0, now()"
#endif
		")", GetTablePostfix(), p->dwPID, p->dwGuild, p->bGrade);

	std::unique_ptr<SQLMsg> pmsg_insert(CDBManager::instance().DirectQuery(szQuery));

	snprintf(szQuery, sizeof(szQuery), 
			"SELECT pid, grade, is_general, offer,"
#ifdef ENABLE_GUILD_DONATE_ATTENDANCE
			"UNIX_TIMESTAMP(join_date), donate_limit, UNIX_TIMESTAMP(last_donation), daily_donate_count, UNIX_TIMESTAMP(last_daily_donate), "
#endif
			" level, job, name FROM guild_member%s, player%s WHERE guild_id = %u and pid = id and pid = %u", GetTablePostfix(), GetTablePostfix(), p->dwGuild, p->dwPID);

	std::unique_ptr<SQLMsg> pmsg(CDBManager::instance().DirectQuery(szQuery));

	if (pmsg->Get()->uiNumRows == 0)
	{
		sys_err("Query failed when getting guild member data %s", pmsg->stQuery.c_str());
		return;
	}

	MYSQL_ROW row = mysql_fetch_row(pmsg->Get()->pSQLResult);

	if (!row[0] || !row[1])
		return;

	TPacketDGGuildMember dg;

	dg.dwGuild = p->dwGuild;
	str_to_number(dg.dwPID, row[0]);
	str_to_number(dg.bGrade, row[1]);
	str_to_number(dg.isGeneral, row[2]);
	str_to_number(dg.dwOffer, row[3]);
#ifdef ENABLE_GUILD_DONATE_ATTENDANCE
	str_to_number(dg.dwJoinDate, row[4]);
	str_to_number(dg.bDonateLimit, row[5]);
	str_to_number(dg.dwLastDonation, row[6]);
	str_to_number(dg.bDailyDonateCount, row[7]);
	str_to_number(dg.dwLastDailyDonate, row[8]);
	str_to_number(dg.bLevel, row[9]);
	str_to_number(dg.bJob, row[10]);
	strlcpy(dg.szName, row[11], sizeof(dg.szName));
#else
	str_to_number(dg.bLevel, row[4]);
	str_to_number(dg.bJob, row[5]);
	strlcpy(dg.szName, row[6], sizeof(dg.szName));
#endif
	ForwardPacket(HEADER_DG_GUILD_ADD_MEMBER, &dg, sizeof(TPacketDGGuildMember));
}
