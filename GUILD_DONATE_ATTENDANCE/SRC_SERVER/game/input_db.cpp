//Open input_db.cpp find and replace:
void CInputDB::GuildChangeMemberData(const char* c_pData)
{
	sys_log(0, "Recv GuildChangeMemberData");
	TPacketGuildChangeMemberData * p = (TPacketGuildChangeMemberData *) c_pData;
	CGuild * g = CGuildManager::instance().TouchGuild(p->guild_id);

	if (g)
		g->ChangeMemberData(p->pid, p->offer, p->level, p->grade
#ifdef ENABLE_GUILD_DONATE_ATTENDANCE
			, p->join_date, p->donate_limit, p->last_donation, p->daily_donate_count, p->last_daily_donate
#endif
		);
}
