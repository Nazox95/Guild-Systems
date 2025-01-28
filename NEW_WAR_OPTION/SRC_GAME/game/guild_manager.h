//Open guild_manager.h find
		void		RequestWarOver(DWORD dwGuild1, DWORD dwGuild2, DWORD dwGuildWinner, long lReward);
//replace
#ifdef ENABLE_NEW_WAR_OPTIONS
		void		DeclareWar(DWORD guild_id1, DWORD guild_id2, BYTE bType, BYTE bRound, BYTE bPoints, BYTE bTime);
#else
		void		DeclareWar(DWORD guild_id1, DWORD guild_id2, BYTE bType);
#endif
