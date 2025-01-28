//Open guild_war.cpp find and replace
#ifdef ENABLE_NEW_WAR_OPTIONS
void CGuild::GuildWarPacket(DWORD dwOppGID, BYTE bWarType, BYTE bWarState, BYTE bRound, BYTE bPoints, BYTE bTime)
#else
void CGuild::GuildWarPacket(DWORD dwOppGID, BYTE bWarType, BYTE bWarState)
#endif
{
	TPacketGCGuild pack{};
	TPacketGCGuildWar pack2{};

	pack.header		= HEADER_GC_GUILD;
	pack.subheader	= GUILD_SUBHEADER_GC_WAR;
	pack.size		= sizeof(pack) + sizeof(pack2);
	pack2.dwGuildSelf	= GetID();
	pack2.dwGuildOpp	= dwOppGID;
	pack2.bWarState	= bWarState;
	pack2.bType		= bWarType;
#ifdef ENABLE_NEW_WAR_OPTIONS
	pack2.bRound	= bRound;
	pack2.bPoints	= bPoints;
	pack2.dwTime	= bTime;
#endif

//find and replace 
void CGuild::SendEnemyGuild(LPCHARACTER ch)
{
	LPDESC d = ch->GetDesc();

	if (!d)
		return;

	TPacketGCGuild pack{};
	TPacketGCGuildWar pack2{};
	pack.header = HEADER_GC_GUILD;
	pack.subheader = GUILD_SUBHEADER_GC_WAR;
	pack.size = sizeof(pack) + sizeof(pack2);
	pack2.dwGuildSelf = GetID();

	TPacketGCGuild p{};
	p.header = HEADER_GC_GUILD;
	p.subheader = GUILD_SUBHEADER_GC_WAR_SCORE;
	p.size = sizeof(p) + sizeof(DWORD) + sizeof(DWORD) + sizeof(long);

	for (auto it : m_EnemyGuild)
	{
		ch->SendGuildName( it.first );

		pack2.dwGuildOpp = it.first;
		pack2.bType = it.second.type;
		pack2.bWarState = it.second.state;
#ifdef ENABLE_NEW_WAR_OPTIONS
		pack2.bRound = it.second.round;
		pack2.bPoints = it.second.points;
		pack2.dwTime = it.second.time;
#endif

		d->BufferedPacket(&pack, sizeof(pack));
		d->Packet(&pack2, sizeof(pack2));

		if (it.second.state == GUILD_WAR_ON_WAR)
		{
			long lScore = GetWarScoreAgainstTo(pack2.dwGuildOpp);

			d->BufferedPacket(&p, sizeof(p));
			d->BufferedPacket(&pack2.dwGuildSelf, sizeof(DWORD));
			d->BufferedPacket(&pack2.dwGuildOpp, sizeof(DWORD));
			d->Packet(&lScore, sizeof(long));

			lScore = CGuildManager::Instance().TouchGuild(pack2.dwGuildOpp)->GetWarScoreAgainstTo(pack2.dwGuildSelf);

			d->BufferedPacket(&p, sizeof(p));
			d->BufferedPacket(&pack2.dwGuildOpp, sizeof(DWORD));
			d->BufferedPacket(&pack2.dwGuildSelf, sizeof(DWORD));
			d->Packet(&lScore, sizeof(long));
		}
	}
}

//Find 
DWORD CGuild::GetGuildWarpMapIndex(DWORD dwOppGID)
//add before
#ifdef ENABLE_NEW_WAR_OPTIONS
int CGuild::GetGuildWarSettingRound(DWORD dwOppGID)
{
	itertype(m_EnemyGuild) git = m_EnemyGuild.find(dwOppGID);

	if (git == m_EnemyGuild.end())
		return 1;

	return git->second.round;
}

int CGuild::GetGuildWarSettingPoints(DWORD dwOppGID)
{
	itertype(m_EnemyGuild) git = m_EnemyGuild.find(dwOppGID);

	if (git == m_EnemyGuild.end())
		return 1;

	return git->second.points;
}

int CGuild::GetGuildWarSettingTime(DWORD dwOppGID)
{
	itertype(m_EnemyGuild) git = m_EnemyGuild.find(dwOppGID);

	if (git == m_EnemyGuild.end())
		return 1;

	return git->second.time;
}
#endif

//Find and replace
#ifdef ENABLE_NEW_WAR_OPTIONS
void CGuild::RequestDeclareWar(DWORD dwOppGID, BYTE type, BYTE flag, BYTE round, BYTE points, DWORD time)
#else
void CGuild::RequestDeclareWar(DWORD dwOppGID, BYTE type)
#endif
{
	if (dwOppGID == GetID())
	{
		sys_log(0, "GuildWar.DeclareWar.DECLARE_WAR_SELF id(%d -> %d), type(%d)", GetID(), dwOppGID, type);
		return;
	}

	if (type >= GUILD_WAR_TYPE_MAX_NUM)
	{
		sys_log(0, "GuildWar.DeclareWar.UNKNOWN_WAR_TYPE id(%d -> %d), type(%d)", GetID(), dwOppGID, type);
		return;
	}

	itertype(m_EnemyGuild) it = m_EnemyGuild.find(dwOppGID);
	if (it == m_EnemyGuild.end())
	{
		if (!GuildWar_IsWarMap(type))
		{
			sys_err("GuildWar.DeclareWar.NOT_EXIST_MAP id(%d -> %d), type(%d), map(%d)",
					GetID(), dwOppGID, type, GuildWar_GetTypeMapIndex(type));

			map_allow_log();
			NotifyGuildMaster("[LS;669]");
			return;
		}

		// ÆÐÅ¶ º¸³»±â to another server
		TPacketGuildWar p;
		p.bType = type;
		p.bWar = GUILD_WAR_SEND_DECLARE;
#ifdef ENABLE_NEW_WAR_OPTIONS
		p.bRound = round;
		p.bPoints = points;
		p.bTime = time;
#endif
		p.dwGuildFrom = GetID();
		p.dwGuildTo = dwOppGID;
		db_clientdesc->DBPacket(HEADER_GD_GUILD_WAR, 0, &p, sizeof(p));
		sys_log(0, "GuildWar.DeclareWar id(%d -> %d), type(%d)", GetID(), dwOppGID, type);
		return;
	}

	switch (it->second.state)
	{
		case GUILD_WAR_RECV_DECLARE:
			{
				const BYTE saved_type = it->second.type;
#ifdef ENABLE_NEW_WAR_OPTIONS
				const BYTE saved_round = it->second.round;
				const BYTE saved_points = it->second.points;
				const BYTE saved_time = it->second.time;
#endif

				if (saved_type == GUILD_WAR_TYPE_FIELD)
				{
					TPacketGuildWar p;
					p.bType = saved_type;
					p.bWar = GUILD_WAR_ON_WAR;
#ifdef ENABLE_NEW_WAR_OPTIONS
					p.bRound = saved_round;
					p.bPoints = saved_points;
					p.bTime = saved_time;
#endif
					p.dwGuildFrom = GetID();
					p.dwGuildTo = dwOppGID;
					db_clientdesc->DBPacket(HEADER_GD_GUILD_WAR, 0, &p, sizeof(p));
					sys_log(0, "GuildWar.AcceptWar id(%d -> %d), type(%d)", GetID(), dwOppGID, saved_type);
					return;
				}

				if (!GuildWar_IsWarMap(saved_type))
				{
					sys_err("GuildWar.AcceptWar.NOT_EXIST_MAP id(%d -> %d), type(%d), map(%d)",
							GetID(), dwOppGID, type, GuildWar_GetTypeMapIndex(type));

					map_allow_log();
					NotifyGuildMaster("[LS;669]");
					return;
				}

				const TGuildWarInfo& guildWarInfo = GuildWar_GetTypeInfo(saved_type);

				TPacketGuildWar p;
				p.bType = saved_type;
				p.bWar = GUILD_WAR_WAIT_START;
#ifdef ENABLE_NEW_WAR_OPTIONS
				p.bRound = saved_round;
				p.bPoints = saved_points;
				p.bTime = saved_time;
#endif
				p.dwGuildFrom = GetID();
				p.dwGuildTo = dwOppGID;
				p.lWarPrice = guildWarInfo.iWarPrice;
				p.lInitialScore = guildWarInfo.iInitialScore;

				if (test_server)
					p.lInitialScore /= 10;

				db_clientdesc->DBPacket(HEADER_GD_GUILD_WAR, 0, &p, sizeof(p));

				sys_log(0, "GuildWar.WaitStartSendToDB id(%d vs %d), type(%d), bet(%d), map_index(%d)",
						GetID(), dwOppGID, saved_type, guildWarInfo.iWarPrice, guildWarInfo.lMapIndex);

			}
			break;
		case GUILD_WAR_SEND_DECLARE:
			{
				NotifyGuildMaster("[LS;780]");
			}
			break;
		default:
			sys_err("GuildWar.DeclareWar.UNKNOWN_STATE[%d]: id(%d vs %d), type(%d), guild(%s:%u)",
					it->second.state, GetID(), dwOppGID, type, GetName(), GetID());
			break;
	}
}

//Find and replace 
#ifdef ENABLE_NEW_WAR_OPTIONS
bool CGuild::DeclareWar(DWORD dwOppGID, BYTE type, BYTE state, BYTE round, BYTE points, BYTE time)
#else
bool CGuild::DeclareWar(DWORD dwOppGID, BYTE type, BYTE state)
#endif
{
	if (m_EnemyGuild.find(dwOppGID) != m_EnemyGuild.end())
		return false;

	TGuildWar gw(type);
	gw.state = state;
#ifdef ENABLE_NEW_WAR_OPTIONS
	gw.round = round;
	gw.points = points;
	gw.time = time;
#endif

	m_EnemyGuild.insert(std::make_pair(dwOppGID, gw));

#ifdef ENABLE_NEW_WAR_OPTIONS
	GuildWarPacket(dwOppGID, type, state, round, points, time);
#else
	GuildWarPacket(dwOppGID, type, state);
#endif
	return true;
}

//Find and replace
void CGuild::StartWar(DWORD dwOppGID)
{
	itertype(m_EnemyGuild) it = m_EnemyGuild.find(dwOppGID);

	if (it == m_EnemyGuild.end())
		return;

	TGuildWar & gw(it->second);

	if (gw.state == GUILD_WAR_ON_WAR)
		return;

	gw.state = GUILD_WAR_ON_WAR;
	gw.war_start_time = get_global_time();

#ifdef ENABLE_NEW_WAR_OPTIONS
	GuildWarPacket(dwOppGID, gw.type, GUILD_WAR_ON_WAR, gw.round, gw.points, gw.time);
#else
	GuildWarPacket(dwOppGID, gw.type, GUILD_WAR_ON_WAR);
#endif

	if (gw.type != GUILD_WAR_TYPE_FIELD)
		GuildWarEntryAsk(dwOppGID);
}

//Find and replace 
void CGuild::RefuseWar(DWORD dwOppGID)
{
	if (dwOppGID == GetID())
		return;

	itertype(m_EnemyGuild) it = m_EnemyGuild.find(dwOppGID);

	if (it != m_EnemyGuild.end() && (it->second.state == GUILD_WAR_SEND_DECLARE || it->second.state == GUILD_WAR_RECV_DECLARE))
	{
		BYTE type = it->second.type;
#ifdef ENABLE_NEW_WAR_OPTIONS
		BYTE round = it->second.round;
		BYTE point = it->second.points;
		BYTE time = it->second.time;
#endif
		m_EnemyGuild.erase(dwOppGID);

#ifdef ENABLE_NEW_WAR_OPTIONS
		GuildWarPacket(dwOppGID, type, GUILD_WAR_END, round, point, time);
#else
		GuildWarPacket(dwOppGID, type, GUILD_WAR_END);
#endif
	}
}

//Find and replace
void CGuild::EndWar(DWORD dwOppGID)
{
	if (dwOppGID == GetID())
		return;

	itertype(m_EnemyGuild) it = m_EnemyGuild.find(dwOppGID);

	if (it != m_EnemyGuild.end())
	{
		CWarMap * pMap = CWarMapManager::Instance().Find(it->second.map_index);

		if (pMap)
			pMap->SetEnded();

#ifdef ENABLE_NEW_WAR_OPTIONS
		GuildWarPacket(dwOppGID, it->second.type, GUILD_WAR_END, it->second.round, it->second.points, it->second.time);
#else
		GuildWarPacket(dwOppGID, it->second.type, GUILD_WAR_END);
#endif
		m_EnemyGuild.erase(it);

		if (!UnderAnyWar())
		{
			for (itertype(m_memberOnline) it = m_memberOnline.begin(); it != m_memberOnline.end(); ++it)
			{
				LPCHARACTER ch = *it;
				ch->RemoveAffect(GUILD_SKILL_BLOOD);
				ch->RemoveAffect(GUILD_SKILL_BLESS);
				ch->RemoveAffect(GUILD_SKILL_SEONGHWI);
				ch->RemoveAffect(GUILD_SKILL_ACCEL);
				ch->RemoveAffect(GUILD_SKILL_BUNNO);
				ch->RemoveAffect(GUILD_SKILL_JUMUN);

				ch->RemoveBadAffect();
			}
		}
	}
#ifdef ENABLE_NEW_WAR_OPTIONS
	for_each(m_memberOnline.begin(), m_memberOnline.end(), std::bind(&CGuild::SendSkillInfoPacket, this, std::placeholders::_1));
#endif
}
