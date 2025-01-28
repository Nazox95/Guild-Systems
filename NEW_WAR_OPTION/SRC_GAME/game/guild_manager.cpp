void CGuildManager::RequestWarOver(DWORD dwGuild1, DWORD dwGuild2, DWORD dwGuildWinner, long lReward)
{
	CGuild* g1 = TouchGuild(dwGuild1);
	const CGuild* g2 = TouchGuild(dwGuild2);

	if (!g1 || !g2)
		return;

	if (g1->GetGuildWarState(g2->GetID()) != GUILD_WAR_ON_WAR)
	{
		sys_log(0, "RequestWarOver : both guild was not in war %u %u", dwGuild1, dwGuild2);
		RequestEndWar(dwGuild1, dwGuild2);
		return;
	}

	TPacketGuildWar p{};

	p.bWar = GUILD_WAR_OVER;
	// There is no reward even after the guild battle is over.
	//p.lWarPrice = lReward;
	p.lWarPrice = 0;
	p.bType = dwGuildWinner == 0 ? 1 : 0; // bType == 1 means draw for this packet.
#ifdef ENABLE_NEW_WAR_OPTIONS
	p.bRound = 0;
	p.bPoints = 0;
	p.bTime = 0;
#endif

	if (dwGuildWinner == 0)
	{
		p.dwGuildFrom = dwGuild1;
		p.dwGuildTo = dwGuild2;
	}
	else
	{
		p.dwGuildFrom = dwGuildWinner;
		p.dwGuildTo = dwGuildWinner == dwGuild1 ? dwGuild2 : dwGuild1;
	}

	db_clientdesc->DBPacket(HEADER_GD_GUILD_WAR, 0, &p, sizeof(p));
	sys_log(0, "RequestWarOver : winner %u loser %u draw %u betprice %d", p.dwGuildFrom, p.dwGuildTo, p.bType, p.lWarPrice);
}

//find and replace 
#ifdef ENABLE_NEW_WAR_OPTIONS
void CGuildManager::DeclareWar(DWORD guild_id1, DWORD guild_id2, BYTE bType, BYTE bRound, BYTE bPoints, BYTE bTime)
#else
void CGuildManager::DeclareWar(DWORD guild_id1, DWORD guild_id2, BYTE bType)
#endif
{
	if (guild_id1 == guild_id2)
		return;

	CGuild* g1 = FindGuild(guild_id1);
	CGuild* g2 = FindGuild(guild_id2);

	if (!g1 || !g2)
		return;

#ifdef ENABLE_NEW_WAR_OPTIONS
	if (g1->DeclareWar(guild_id2, bType, GUILD_WAR_SEND_DECLARE, bRound, bPoints, bTime) &&
		g2->DeclareWar(guild_id1, bType, GUILD_WAR_RECV_DECLARE, bRound, bPoints, bTime))
#else
	if (g1->DeclareWar(guild_id2, bType, GUILD_WAR_SEND_DECLARE) &&
		g2->DeclareWar(guild_id1, bType, GUILD_WAR_RECV_DECLARE))
#endif
	{
		// @warme005
		{
			char buf[256];
			snprintf(buf, sizeof(buf), "[LS;475;%s;%s]", TouchGuild(guild_id1)->GetName(), TouchGuild(guild_id2)->GetName());
			SendNotice(buf);
		}
	}
}
---------------------
