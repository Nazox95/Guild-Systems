//Open input_db.cpp find 
void CInputDB::GuildWar(const char* c_pData)
{
	const TPacketGuildWar* p = (TPacketGuildWar*)c_pData;

	sys_log(0, "InputDB::GuildWar %u %u state %d", p->dwGuildFrom, p->dwGuildTo, p->bWar);

	switch (p->bWar)
	{
		case GUILD_WAR_SEND_DECLARE:
		case GUILD_WAR_RECV_DECLARE:
//replace
#ifdef ENABLE_NEW_WAR_OPTIONS
			CGuildManager::Instance().DeclareWar(p->dwGuildFrom, p->dwGuildTo, p->bType, p->bRound, p->bPoints, p->bTime);
#else
			CGuildManager::Instance().DeclareWar(p->dwGuildFrom, p->dwGuildTo, p->bType);
#endif
			break;
