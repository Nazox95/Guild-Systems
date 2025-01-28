//Open GuildManager.cpp find and replace
namespace
{
	struct FSendPeerWar
	{
#ifdef ENABLE_NEW_WAR_OPTIONS
		FSendPeerWar(BYTE bType, BYTE bRound, BYTE bPoints, BYTE bTime, BYTE bWar, DWORD GID1, DWORD GID2)
#else
		FSendPeerWar(BYTE bType, BYTE bWar, DWORD GID1, DWORD GID2)
#endif
		{
			if (number(0, 1))
				std::swap(GID1, GID2);

			memset(&p, 0, sizeof(TPacketGuildWar));

			p.bWar = bWar;
			p.bType = bType;
#ifdef ENABLE_NEW_WAR_OPTIONS
			p.bRound = bRound;
			p.bPoints = bPoints;
			p.bTime = bTime;
#endif
			p.dwGuildFrom = GID1;
			p.dwGuildTo = GID2;
		}

		void operator() (CPeer* peer)
		{
			if (peer->GetChannel() == 0)
				return;

			peer->EncodeHeader(HEADER_DG_GUILD_WAR, 0, sizeof(TPacketGuildWar));
			peer->Encode(&p, sizeof(TPacketGuildWar));
		}

		TPacketGuildWar p;
	};

//Find and replace
void CGuildManager::Update()
{
	ProcessReserveWar(); // ¿¹¾à ÀüÀï Ã³¸®

	time_t now = CClientManager::instance().GetCurrentTime();

	if (!m_pqOnWar.empty())
	{
		// UNKNOWN_GUILD_MANAGE_UPDATE_LOG
		/*
		   sys_log(0, "GuildManager::Update size %d now %d top %d, %s(%u) vs %s(%u)", 
		   m_WarMap.size(),
		   now,
		   m_pqOnWar.top().first,
		   m_map_kGuild[m_pqOnWar.top().second->GID[0]].szName,
		   m_pqOnWar.top().second->GID[0],
		   m_map_kGuild[m_pqOnWar.top().second->GID[1]].szName,
		   m_pqOnWar.top().second->GID[1]);
		   */
		// END_OF_UNKNOWN_GUILD_MANAGE_UPDATE_LOG

		while (!m_pqOnWar.empty() && (m_pqOnWar.top().first <= now || (m_pqOnWar.top().second && m_pqOnWar.top().second->bEnd)))
		{
			TGuildWarPQElement * e = m_pqOnWar.top().second;

			m_pqOnWar.pop();

			if (e)
			{
				if (!e->bEnd)
					WarEnd(e->GID[0], e->GID[1], false); 

				delete e;
			}
		}
	}

	// GUILD_SKILL_COOLTIME_BUG_FIX
	while (!m_pqSkill.empty() && m_pqSkill.top().first <= now)
	{
		const TGuildSkillUsed& s = m_pqSkill.top().second;
		CClientManager::instance().SendGuildSkillUsable(s.GID, s.dwSkillVnum, true);
		m_pqSkill.pop();
	}
	// END_OF_GUILD_SKILL_COOLTIME_BUG_FIX

	while (!m_pqWaitStart.empty() && m_pqWaitStart.top().first <= now)
	{
		const TGuildWaitStartInfo& ws = m_pqWaitStart.top().second;
		m_pqWaitStart.pop();

#ifdef ENABLE_NEW_WAR_OPTIONS
		StartWar(ws.bType, ws.GID[0], ws.GID[1], ws.bRound, ws.bPoints, ws.bTime, ws.pkReserve); // insert new element to m_WarMap and m_pqOnWar
#else
		StartWar(ws.bType, ws.GID[0], ws.GID[1], ws.pkReserve); // insert new element to m_WarMap and m_pqOnWar
#endif

		if (ws.lInitialScore)
		{
			UpdateScore(ws.GID[0], ws.GID[1], ws.lInitialScore, 0);
			UpdateScore(ws.GID[1], ws.GID[0], ws.lInitialScore, 0);
		}

		TPacketGuildWar p{};

		p.bType		= ws.bType;
		p.bWar		= GUILD_WAR_ON_WAR;
#ifdef ENABLE_NEW_WAR_OPTIONS
		p.bRound	= ws.bRound;
		p.bPoints	= ws.bPoints;
		p.bTime		= ws.bTime;
#endif
		p.dwGuildFrom	= ws.GID[0];
		p.dwGuildTo	= ws.GID[1];

		CClientManager::Instance().ForwardPacket(HEADER_DG_GUILD_WAR, &p, sizeof(p));
		sys_log(0, "GuildWar: GUILD sending start of wait start war %d %d", ws.GID[0], ws.GID[1]);
	}
}

//find and replace 
void CGuildManager::OnSetup(CPeer* peer)
{
	for_all(m_WarMap, it_cont)
		for_all(it_cont->second, it)
	{
		const DWORD g1 = it_cont->first;
		const DWORD g2 = it->first;
		const TGuildWarPQElement* p = it->second.pElement;

		if (!p || p->bEnd)
			continue;

#ifdef ENABLE_NEW_WAR_OPTIONS
		FSendPeerWar(p->bType, p->bRound, p->bPoints, p->bTime, GUILD_WAR_ON_WAR, g1, g2) (peer);
#else
		FSendPeerWar(p->bType, GUILD_WAR_ON_WAR, g1, g2) (peer);
#endif
		FSendGuildWarScore(p->GID[0], p->GID[1], p->iScore[0], p->iBetScore[0]);
		FSendGuildWarScore(p->GID[1], p->GID[0], p->iScore[1], p->iBetScore[1]);
	}

	for_all(m_DeclareMap, it)
	{
#ifdef ENABLE_NEW_WAR_OPTIONS
		FSendPeerWar(it->bType, it->bRound, it->bPoints, it->bTime, GUILD_WAR_SEND_DECLARE, it->dwGuildID[0], it->dwGuildID[1]) (peer);
#else
		FSendPeerWar(it->bType, GUILD_WAR_SEND_DECLARE, it->dwGuildID[0], it->dwGuildID[1]) (peer);
#endif
	}

	for_all(m_map_kWarReserve, it)
	{
		it->second->OnSetup(peer);
	}
}

//Find and replace 

void CGuildManager::WarEnd(DWORD GID1, DWORD GID2, bool bForceDraw)
{
	if (GID1 > GID2)
		std::swap(GID2, GID1);

	sys_log(0, "GuildWar: WarEnd %d %d", GID1, GID2);

	const auto itWarMap = m_WarMap[GID1].find(GID2);

	if (itWarMap == m_WarMap[GID1].end())
	{
		sys_err("GuildWar: war not exist or already ended. [1]");
		return;
	}

	const TGuildWarInfo gwi = itWarMap->second;
	const TGuildWarPQElement* pData = gwi.pElement;

	if (!pData || pData->bEnd)
	{
		sys_err("GuildWar: war not exist or already ended. [2]");
		return;
	}

	DWORD win_guild = pData->GID[0];
	DWORD lose_guild = pData->GID[1];

	bool bDraw = false;

	if (!bForceDraw) // If it is not a forced draw, the score is checked.
	{
		if (pData->iScore[0] > pData->iScore[1])
		{
			win_guild = pData->GID[0];
			lose_guild = pData->GID[1];
		}
		else if (pData->iScore[1] > pData->iScore[0])
		{
			win_guild = pData->GID[1];
			lose_guild = pData->GID[0];
		}
		else
			bDraw = true;
	}
	else // In case of forced draw, unconditional draw
		bDraw = true;

	if (bDraw)
		ProcessDraw(win_guild, lose_guild);
	else
		ProcessWinLose(win_guild, lose_guild);

	// Since the DB server may end itself by itself, a separate packet must be sent.
#ifdef ENABLE_NEW_WAR_OPTIONS
	CClientManager::Instance().for_each_peer(FSendPeerWar(0, 0, 0, 0, GUILD_WAR_END, GID1, GID2));
#else
	CClientManager::Instance().for_each_peer(FSendPeerWar(0, GUILD_WAR_END, GID1, GID2));
#endif

	RemoveWar(GID1, GID2);
}

//Find and replace
#ifdef ENABLE_NEW_WAR_OPTIONS
void CGuildManager::StartWar(BYTE bType, DWORD GID1, DWORD GID2, BYTE bRound, BYTE bPoints, BYTE bTime, CGuildWarReserve* pkReserve)
#else
void CGuildManager::StartWar(BYTE bType, DWORD GID1, DWORD GID2, CGuildWarReserve * pkReserve)
#endif
{
	sys_log(0, "GuildWar: StartWar(%d,%d,%d)", bType, GID1, GID2);

	if (GID1 > GID2)
		std::swap(GID1, GID2);

	TGuildWarInfo& gw = m_WarMap[GID1][GID2]; // map insert

#ifdef ENABLE_NEW_WAR_OPTIONS
	int wtime;
	if (bTime == 1)
		wtime = 600;	//10min
	else if (bTime == 2)
		wtime = 1800;	//30min
	else if (bTime == 3)
		wtime = 3600;	//1h
	else
		wtime = 123;
		//wtime = GUILD_WAR_DURATION;

	gw.tEndTime = CClientManager::Instance().GetCurrentTime() + wtime;
	gw.pElement = new TGuildWarPQElement(bType, bRound, bPoints, bTime, GID1, GID2);
#else
	if (bType == GUILD_WAR_TYPE_FIELD)
		gw.tEndTime = CClientManager::Instance().GetCurrentTime() + GUILD_WAR_DURATION;
	else
		gw.tEndTime = CClientManager::Instance().GetCurrentTime() + 172800;

	gw.pElement = new TGuildWarPQElement(bType, GID1, GID2);
#endif
	gw.pkReserve = pkReserve;

	m_pqOnWar.push(std::make_pair(gw.tEndTime, gw.pElement));
}

//Find and replace (AddDeclare and RemoveDeclare)
#ifdef ENABLE_NEW_WAR_OPTIONS
void CGuildManager::AddDeclare(BYTE bType, DWORD guild_from, DWORD guild_to, BYTE bRound, BYTE bPoints, BYTE bTime)
#else
void CGuildManager::AddDeclare(BYTE bType, DWORD guild_from, DWORD guild_to)
#endif
{
#ifdef ENABLE_NEW_WAR_OPTIONS
	const TGuildDeclareInfo di(bType, bRound, bPoints, bTime, guild_from, guild_to);
#else
	const TGuildDeclareInfo di(bType, guild_from, guild_to);
#endif

	if (m_DeclareMap.find(di) == m_DeclareMap.end())
		m_DeclareMap.insert(di);

	sys_log(0, "GuildWar: AddDeclare(Type:%d,from:%d,to:%d)", bType, guild_from, guild_to);
}

void CGuildManager::RemoveDeclare(DWORD guild_from, DWORD guild_to)
{
#ifdef ENABLE_NEW_WAR_OPTIONS
	__typeof(m_DeclareMap.begin()) it = m_DeclareMap.find(TGuildDeclareInfo(0, 0, 0, 0, guild_from, guild_to));
#else
	__typeof(m_DeclareMap.begin()) it = m_DeclareMap.find(TGuildDeclareInfo(0, guild_from, guild_to));
#endif

	if (it != m_DeclareMap.end())
		m_DeclareMap.erase(it);

#ifdef ENABLE_NEW_WAR_OPTIONS
	it = m_DeclareMap.find(TGuildDeclareInfo(0, 0, 0, 0, guild_to, guild_from));
#else
	it = m_DeclareMap.find(TGuildDeclareInfo(0, guild_to, guild_from));
#endif

	if (it != m_DeclareMap.end())
		m_DeclareMap.erase(it);

	sys_log(0, "GuildWar: RemoveDeclare(from:%d,to:%d)", guild_from, guild_to);
}

//Find and replace 
bool CGuildManager::WaitStart(TPacketGuildWar* p)
{
	if (!p)
		return false;

	if (p->lWarPrice > 0)
	{
		if (!TakeBetPrice(p->dwGuildFrom, p->dwGuildTo, p->lWarPrice))
			return false;
	}

	const DWORD dwCurTime = CClientManager::Instance().GetCurrentTime();

#ifdef ENABLE_NEW_WAR_OPTIONS
	TGuildWaitStartInfo info(p->bType, p->bRound, p->bPoints, p->bTime, p->dwGuildFrom, p->dwGuildTo, p->lWarPrice, p->lInitialScore, nullptr);
#else
	TGuildWaitStartInfo info(p->bType, p->dwGuildFrom, p->dwGuildTo, p->lWarPrice, p->lInitialScore, nullptr);
#endif
	m_pqWaitStart.push(std::make_pair(dwCurTime + GetGuildWarWaitStartDuration(), info));

	sys_log(0,
		"GuildWar: WaitStart g1 %d g2 %d price %d start at %u",
		p->dwGuildFrom,
		p->dwGuildTo,
		p->lWarPrice,
		dwCurTime + GetGuildWarWaitStartDuration());

	return true;
}

//Find and replace
void CGuildManager::BootReserveWar()
{
	const char* c_apszQuery[2] =
	{
#ifdef ENABLE_NEW_WAR_OPTIONS
		"SELECT id, guild1, guild2, UNIX_TIMESTAMP(time), type, round, points, xtime, warprice, initscore, bet_from, bet_to, power1, power2, handicap FROM guild_war_reservation WHERE started=1 AND winner=-1",
		"SELECT id, guild1, guild2, UNIX_TIMESTAMP(time), type, round, points, xtime, warprice, initscore, bet_from, bet_to, power1, power2, handicap FROM guild_war_reservation WHERE started=0"
#else
		"SELECT id, guild1, guild2, UNIX_TIMESTAMP(time), type, warprice, initscore, bet_from, bet_to, power1, power2, handicap FROM guild_war_reservation WHERE started=1 AND winner=-1",
		"SELECT id, guild1, guild2, UNIX_TIMESTAMP(time), type, warprice, initscore, bet_from, bet_to, power1, power2, handicap FROM guild_war_reservation WHERE started=0"
#endif
	};

	for (int i = 0; i < 2; ++i)
	{
		auto pmsg(CDBManager::Instance().DirectQuery(c_apszQuery[i]));

		if (pmsg->Get()->uiNumRows == 0)
			continue;

		MYSQL_ROW row;

		while ((row = mysql_fetch_row(pmsg->Get()->pSQLResult)))
		{
			int col = 0;

			TGuildWarReserve t;

			str_to_number(t.dwID, row[col++]);
			str_to_number(t.dwGuildFrom, row[col++]);
			str_to_number(t.dwGuildTo, row[col++]);
			str_to_number(t.dwTime, row[col++]);
			str_to_number(t.bType, row[col++]);
#ifdef ENABLE_NEW_WAR_OPTIONS
			str_to_number(t.bRound, row[col++]);
			str_to_number(t.bPoints, row[col++]);
			str_to_number(t.bTime, row[col++]);
#endif
			str_to_number(t.lWarPrice, row[col++]);
			str_to_number(t.lInitialScore, row[col++]);
			str_to_number(t.dwBetFrom, row[col++]);
			str_to_number(t.dwBetTo, row[col++]);
			str_to_number(t.lPowerFrom, row[col++]);
			str_to_number(t.lPowerTo, row[col++]);
			str_to_number(t.lHandicap, row[col++]);
			t.bStarted = 0;

			CGuildWarReserve* pkReserve = new CGuildWarReserve(t);

			char buf[512];
			snprintf(buf, sizeof(buf), "GuildWar: BootReserveWar : step %d id %u GID1 %u GID2 %u", i, t.dwID, t.dwGuildFrom, t.dwGuildTo);
			// If i == 0, the DB bounced during the guild battle, so it is treated as a draw.
			// Alternatively, the remaining reservation guild battles with less than 5 minutes remaining will be treated as a draw. (They return their bets)
			//if (i == 0 || (int) t.dwTime - CClientManager::Instance().GetCurrentTime() < 60 * 5)
			if (i == 0 || (int)t.dwTime - CClientManager::Instance().GetCurrentTime() < 0)
			{
				if (i == 0)
					sys_log(0, "%s : DB was shutdowned while war is being.", buf);
				else
					sys_log(0, "%s : left time lower than 5 minutes, will be canceled", buf);

				pkReserve->Draw();
				delete pkReserve;
			}
			else
			{
				sys_log(0, "%s : OK", buf);
				m_map_kWarReserve.insert(std::make_pair(t.dwID, pkReserve));
			}
		}
	}
}

//Find and replace
bool CGuildManager::ReserveWar(TPacketGuildWar* p)
{
	if (!p)
		return false;

	DWORD GID1 = p->dwGuildFrom;
	DWORD GID2 = p->dwGuildTo;

	if (GID1 > GID2)
		std::swap(GID1, GID2);

	if (p->lWarPrice > 0)
		if (!TakeBetPrice(GID1, GID2, p->lWarPrice))
			return false;

	TGuildWarReserve t;
	memset(&t, 0, sizeof(TGuildWarReserve));

	t.dwGuildFrom = GID1;
	t.dwGuildTo = GID2;
	t.dwTime = CClientManager::Instance().GetCurrentTime() + GetGuildWarReserveSeconds();
	t.bType = p->bType;
#ifdef ENABLE_NEW_WAR_OPTIONS
	t.bRound = p->bRound;
	t.bPoints = p->bPoints;
	t.bTime = p->bTime;
#endif
	t.lWarPrice = p->lWarPrice;
	t.lInitialScore = p->lInitialScore;

	int lvp = 0, rkp = 0, alv = 0, mc = 0;

	// calculate power
	TGuild& k1 = TouchGuild(GID1);

	lvp = c_aiScoreByLevel[MIN(GUILD_MAX_LEVEL, k1.level)];
	rkp = c_aiScoreByRanking[GetRanking(GID1)];
	alv = GetAverageGuildMemberLevel(GID1);
	mc = GetGuildMemberCount(GID1);

	polyPower.SetVar("lvp", lvp);
	polyPower.SetVar("rkp", rkp);
	polyPower.SetVar("alv", alv);
	polyPower.SetVar("mc", mc);

	t.lPowerFrom = (long)polyPower.Eval();
	sys_log(0, "GuildWar: %u lvp %d rkp %d alv %d mc %d power %d", GID1, lvp, rkp, alv, mc, t.lPowerFrom);

	// calculate power
	const TGuild& k2 = TouchGuild(GID2);

	lvp = c_aiScoreByLevel[MIN(GUILD_MAX_LEVEL, k2.level)];
	rkp = c_aiScoreByRanking[GetRanking(GID2)];
	alv = GetAverageGuildMemberLevel(GID2);
	mc = GetGuildMemberCount(GID2);

	polyPower.SetVar("lvp", lvp);
	polyPower.SetVar("rkp", rkp);
	polyPower.SetVar("alv", alv);
	polyPower.SetVar("mc", mc);

	t.lPowerTo = (long)polyPower.Eval();
	sys_log(0, "GuildWar: %u lvp %d rkp %d alv %d mc %d power %d", GID2, lvp, rkp, alv, mc, t.lPowerTo);

	// calculate handicap
	if (t.lPowerTo > t.lPowerFrom)
	{
		polyHandicap.SetVar("pA", t.lPowerTo);
		polyHandicap.SetVar("pB", t.lPowerFrom);
	}
	else
	{
		polyHandicap.SetVar("pA", t.lPowerFrom);
		polyHandicap.SetVar("pB", t.lPowerTo);
	}

	t.lHandicap = (long)polyHandicap.Eval();
	sys_log(0, "GuildWar: handicap %d", t.lHandicap);

	// Queries
	char szQuery[512];

#ifdef ENABLE_NEW_WAR_OPTIONS
	snprintf(szQuery, sizeof(szQuery),
		"INSERT INTO guild_war_reservation (guild1, guild2, time, type, round, points, xtime, warprice, initscore, power1, power2, handicap) "
		"VALUES(%u, %u, DATE_ADD(NOW(), INTERVAL 180 SECOND), %u, %u, %u, %u, %ld, %ld, %ld, %ld, %ld)",
		GID1, GID2, p->bType, p->bRound, p->bPoints, p->bTime, p->lWarPrice, p->lInitialScore, t.lPowerFrom, t.lPowerTo, t.lHandicap);
#else
	snprintf(szQuery, sizeof(szQuery),
		"INSERT INTO guild_war_reservation (guild1, guild2, time, type, warprice, initscore, power1, power2, handicap) "
		"VALUES(%u, %u, DATE_ADD(NOW(), INTERVAL 180 SECOND), %u, %ld, %ld, %ld, %ld, %ld)",
		GID1, GID2, p->bType, p->lWarPrice, p->lInitialScore, t.lPowerFrom, t.lPowerTo, t.lHandicap);
#endif

	auto pmsg(CDBManager::Instance().DirectQuery(szQuery));

	if (pmsg->Get()->uiAffectedRows == 0 || pmsg->Get()->uiInsertID == 0 || pmsg->Get()->uiAffectedRows == (DWORD)-1)
	{
		sys_err("GuildWar: Cannot insert row");
		return false;
	}

	t.dwID = static_cast<DWORD>(pmsg->Get()->uiInsertID);

	m_map_kWarReserve.insert(std::make_pair(t.dwID, new CGuildWarReserve(t)));

	CClientManager::Instance().ForwardPacket(HEADER_DG_GUILD_WAR_RESERVE_ADD, &t, sizeof(TGuildWarReserve));
	return true;
}

//Find and replace
void CGuildManager::ProcessReserveWar()
{
	const DWORD dwCurTime = CClientManager::Instance().GetCurrentTime();

	auto it = m_map_kWarReserve.begin();

	while (it != m_map_kWarReserve.end())
	{
		const auto it2 = it++;

		CGuildWarReserve* pk = it2->second;
		if (!pk)
			return;

		TGuildWarReserve& r = pk->GetDataRef();

		if (!r.bStarted && r.dwTime - 1800 <= dwCurTime) // notify 30 minutes in advance.
		{
			const int iMin = static_cast<int>(ceil(static_cast<int>(r.dwTime - dwCurTime) / 60.0));

			/*
			// Nyx: The text that show in GameForge is in CGuildManager::WaitStartWar from guild_manager.cpp (in game_src)
			const TGuild& r_1 = m_map_kGuild[r.dwGuildFrom];
			const TGuild& r_2 = m_map_kGuild[r.dwGuildTo];
			*/

			sys_log(0, "GuildWar: started GID1 %u GID2 %u %d time %d min %d", r.dwGuildFrom, r.dwGuildTo, r.bStarted, dwCurTime - r.dwTime, iMin);

			if (iMin <= 0)
			{
				char szQuery[128];
				snprintf(szQuery, sizeof(szQuery), "UPDATE guild_war_reservation SET started=1 WHERE id=%u", r.dwID);
				CDBManager::Instance().AsyncQuery(szQuery);

				CClientManager::Instance().ForwardPacket(HEADER_DG_GUILD_WAR_RESERVE_DEL, &r.dwID, sizeof(DWORD));

				r.bStarted = true;

#ifdef ENABLE_NEW_WAR_OPTIONS
				TGuildWaitStartInfo info(r.bType, r.bRound, r.bPoints, r.bTime, r.dwGuildFrom, r.dwGuildTo, r.lWarPrice, r.lInitialScore, pk);
#else
				TGuildWaitStartInfo info(r.bType, r.dwGuildFrom, r.dwGuildTo, r.lWarPrice, r.lInitialScore, pk);
#endif
				m_pqWaitStart.push(std::make_pair(dwCurTime + GetGuildWarWaitStartDuration(), info));

				TPacketGuildWar pck{};

				pck.bType = r.bType;
#ifdef ENABLE_NEW_WAR_OPTIONS
				pck.bRound = r.bRound;
				pck.bPoints = r.bPoints;
				pck.bTime = r.bTime;
#endif
				pck.bWar = GUILD_WAR_WAIT_START;
				pck.dwGuildFrom = r.dwGuildFrom;
				pck.dwGuildTo = r.dwGuildTo;
				pck.lWarPrice = r.lWarPrice;
				pck.lInitialScore = r.lInitialScore;

				CClientManager::Instance().ForwardPacket(HEADER_DG_GUILD_WAR, &pck, sizeof(TPacketGuildWar));
				//m_map_kWarReserve.erase(it2);
			}
			/*
			// Nyx: The text that show in GameForge is in CGuildManager::WaitStartWar from guild_manager.cpp (in game_src)
			else
			{
				if (iMin != pk->GetLastNoticeMin())
				{
					pk->SetLastNoticeMin(iMin);
					CClientManager::Instance().SendNotice("The war between %s and %s will start after %d minutes!", r_1.szName, r_2.szName, iMin);
				}
			}
			*/
		}
	}
}

//find and replace
void CGuildWarReserve::OnSetup(CPeer* peer)
{
	if (!peer)
		return;

	if (m_data.bStarted) // Don't send what has already started.
		return;

#ifdef ENABLE_NEW_WAR_OPTIONS
	FSendPeerWar(m_data.bType, m_data.bRound, m_data.bPoints, m_data.bTime, GUILD_WAR_RESERVE, m_data.dwGuildFrom, m_data.dwGuildTo) (peer);
#else
	FSendPeerWar(m_data.bType, GUILD_WAR_RESERVE, m_data.dwGuildFrom, m_data.dwGuildTo) (peer);
#endif

	peer->EncodeHeader(HEADER_DG_GUILD_WAR_RESERVE_ADD, 0, sizeof(TGuildWarReserve));
	peer->Encode(&m_data, sizeof(TGuildWarReserve));

	TPacketGDGuildWarBet pckBet{};
	pckBet.dwWarID = m_data.dwID;

	auto it = mapBet.begin();

	while (it != mapBet.end())
	{
		strlcpy(pckBet.szLogin, it->first.c_str(), sizeof(pckBet.szLogin));
		pckBet.dwGuild = it->second.first;
		pckBet.dwGold = it->second.second;

		peer->EncodeHeader(HEADER_DG_GUILD_WAR_BET, 0, sizeof(TPacketGDGuildWarBet));
		peer->Encode(&pckBet, sizeof(TPacketGDGuildWarBet));

		++it;
	}
}
