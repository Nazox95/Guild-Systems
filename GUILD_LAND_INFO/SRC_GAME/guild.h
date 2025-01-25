//Open guild.h find:
		int			GetGuildMoney() const noexcept { return m_data.gold; }
		void		SetGuildMoney(int gold) { m_data.gold = gold; }
//add
#ifdef ENABLE_GUILD_LAND_INFO
		int			GetGuildLandIndex();
		int			GetGuildLandID();
		void		SetGuildLandInfo();
#endif
