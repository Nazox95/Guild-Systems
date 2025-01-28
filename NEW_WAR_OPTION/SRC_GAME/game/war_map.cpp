//Open war_map.cpp find and replace 
void CWarMap::SendWarPacket(LPDESC d)
{
	TPacketGCGuild pack{};
	TPacketGCGuildWar pack2{};

	pack.header		= HEADER_GC_GUILD;
	pack.subheader	= GUILD_SUBHEADER_GC_WAR;
	pack.size		= sizeof(pack) + sizeof(pack2);

	pack2.dwGuildSelf	= m_TeamData[0].dwID;
	pack2.dwGuildOpp	= m_TeamData[1].dwID;
	pack2.bType		= CGuildManager::Instance().TouchGuild(m_TeamData[0].dwID)->GetGuildWarType(m_TeamData[1].dwID);
	pack2.bWarState	= CGuildManager::Instance().TouchGuild(m_TeamData[0].dwID)->GetGuildWarState(m_TeamData[1].dwID);
#ifdef ENABLE_NEW_WAR_OPTIONS
	pack2.bRound = CGuildManager::Instance().TouchGuild(m_TeamData[0].dwID)->GetGuildWarSettingRound(m_TeamData[1].dwID);
	pack2.bPoints = CGuildManager::Instance().TouchGuild(m_TeamData[0].dwID)->GetGuildWarSettingPoints(m_TeamData[1].dwID);
	pack2.dwTime = CGuildManager::Instance().TouchGuild(m_TeamData[0].dwID)->GetGuildWarSettingTime(m_TeamData[1].dwID);
#endif

	d->BufferedPacket(&pack, sizeof(pack));
	d->Packet(&pack2, sizeof(pack2));
}

//Find and replace 
bool CWarMap::CheckScore()
{
	if (m_bEnded)
		return true;

	// 30ÃÊ ÀÌÈÄ ºÎÅÍ È®ÀÎÇÑ´Ù.
	if (get_dword_time() - m_dwStartTime < 30000)
		return false;

	// Á¡¼ö°¡ °°À¸¸é Ã¼Å©ÇÏÁö ¾Ê´Â´Ù.
	if (m_TeamData[0].iScore == m_TeamData[1].iScore)
		return false;

#ifdef ENABLE_NEW_WAR_OPTIONS
	int bPoints = CGuildManager::Instance().TouchGuild(m_TeamData[0].dwID)->GetGuildWarSettingPoints(m_TeamData[1].dwID);
	int bRound = CGuildManager::Instance().TouchGuild(m_TeamData[0].dwID)->GetGuildWarSettingRound(m_TeamData[1].dwID);

	int points, round;

	if (bPoints == 1)
		points = 30;
	else if (bPoints == 2)
		points = 50;
	else if (bPoints == 3)
		points = 100;

	if (bRound == 1)
		round = 1;
	else if (bRound == 2)
		round = 3;
	else if (bRound == 3)
		round = 5;

	int iEndScore;
	if (m_WarInfo.lMapIndex == 110)	//arena
		iEndScore = points;
	else if (m_WarInfo.lMapIndex == 111)	//flag
		iEndScore = round;
	else
		iEndScore = m_WarInfo.iEndScore;
#else
	int iEndScore = m_WarInfo.iEndScore;
#endif

	if (test_server)
		iEndScore /= 10;

	DWORD dwWinner;
	DWORD dwLoser;

	if (m_TeamData[0].iScore >= iEndScore)
	{
		dwWinner = m_TeamData[0].dwID;
		dwLoser = m_TeamData[1].dwID;
	}
	else if (m_TeamData[1].iScore >= iEndScore)
	{
		dwWinner = m_TeamData[1].dwID;
		dwLoser = m_TeamData[0].dwID;
	}
	else
		return false;

	int iRewardGold = 0;

	if (dwWinner == m_TeamData[0].dwID)
		iRewardGold = GetRewardGold(0);
	else if (dwWinner == m_TeamData[1].dwID)
		iRewardGold = GetRewardGold(1);

	sys_log(0, "WarMap::CheckScore end score %d guild1 %u score guild2 %d %u score %d winner %u reward %d",
			iEndScore,
			m_TeamData[0].dwID,
			m_TeamData[0].iScore,
			m_TeamData[1].dwID,
			m_TeamData[1].iScore,
			dwWinner,
			iRewardGold);

	CGuildManager::Instance().RequestWarOver(dwWinner, dwLoser, dwWinner, iRewardGold);
	return true;
}
