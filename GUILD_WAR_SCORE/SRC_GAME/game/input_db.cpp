//Open input_db.cpp find and replace:
void CInputDB::GuildLadder(const char* c_pData)
{
	TPacketGuildLadder* p = (TPacketGuildLadder*)c_pData;
	sys_log(0, "Recv GuildLadder %u %d / w %d d %d l %d", p->dwGuild, p->lLadderPoint, p->lWin, p->lDraw, p->lLoss);
	CGuild* g = CGuildManager::Instance().TouchGuild(p->dwGuild);
	if (g)
	{
		g->SetLadderPoint(p->lLadderPoint);
		g->SetWarData(p->lWin, p->lDraw, p->lLoss);
#ifdef ENABLE_GUILD_WAR_SCORE
		g->SetNewWarData(p->lWinNew, p->lDrawNew, p->lLossNew);
#endif
#ifdef ENABLE_GUILD_REQUEST
		CGuildManager::Instance().SortGuildCache();
#endif
	}
}
