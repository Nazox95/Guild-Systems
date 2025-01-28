//open guild_manager.h add before:

template <typename Func> void CGuildManager::for_each_war(Func & f)
{
	for (itertype(m_GuildWar) it = m_GuildWar.begin(); it != m_GuildWar.end(); ++it)
	{
		f(it->first, it->second);
	}
}
//
#ifdef ENABLE_GUILD_DONATE_ATTENDANCE
	public:
		TGuildMap GetGuilds() { return m_mapGuild; }
#endif
};
