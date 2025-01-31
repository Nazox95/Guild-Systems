//Open guild_war.cpp find and replace
void CGuild::GuildWarEntryAccept(DWORD dwOppGID, LPCHARACTER ch)
{
	itertype(m_EnemyGuild) git = m_EnemyGuild.find(dwOppGID);

	if (git == m_EnemyGuild.end())
		return;

	TGuildWar & gw(git->second);

	if (gw.type == GUILD_WAR_TYPE_FIELD)
		return;

	if (gw.state != GUILD_WAR_ON_WAR)
	{
		ch->ChatPacket(CHAT_TYPE_INFO, "[LS;891]");
		return;
	}

#ifdef ENABLE_GUILDRENEWAL_SYSTEM
	if (!HasGradeAuth(GetMember(ch->GetPlayerID())->grade, GUILD_AUTH_WAR))
	{
		ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("guild_war_permit"));
		return;
	}
#endif

	if (!gw.map_index)
		return;

	PIXEL_POSITION pos;

	if (!CWarMapManager::instance().GetStartPosition(gw.map_index, GetID() < dwOppGID ? 0 : 1, pos))
		return;

	quest::PC * pPC = quest::CQuestManager::instance().GetPC(ch->GetPlayerID());
	pPC->SetFlag("war.is_war_member", 1);

	ch->SaveExitLocation();
	ch->WarpSet(pos.x, pos.y, gw.map_index);
}
