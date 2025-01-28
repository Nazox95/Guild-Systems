//Open PythonGuild.h find 
		typedef struct SGulidInfo
		{
			DWORD dwGuildID;
			char szGuildName[GUILD_NAME_MAX_LEN+1];
			DWORD dwMasterPID;
			DWORD dwGuildLevel;
			DWORD dwCurrentExperience;
			DWORD dwCurrentMemberCount;
			DWORD dwMaxMemberCount;
			DWORD dwGuildMoney;
			BOOL bHasLand;
//add
#ifdef ENABLE_GUILD_WAR_SCORE
			DWORD winTypes[3];
			DWORD lossTypes[3];
			DWORD drawTypes[3];
			DWORD ladderPoints;
			DWORD rank;
#endif

//find 
		DWORD GetGuildID();
		BOOL HasGuildLand();

		void StartGuildWar(DWORD dwEnemyGuildID);
		void EndGuildWar(DWORD dwEnemyGuildID);
		DWORD GetEnemyGuildID(DWORD dwIndex);
		BOOL IsDoingGuildWar();
//add
#ifdef ENABLE_GUILD_WAR_SCORE
		void SetGuildWarInfo(DWORD* winType, DWORD* lossType, DWORD* drawType, DWORD ladderPoints, DWORD rank)
		{
			for (int i = 0; i < 3; ++i) {
				m_GuildInfo.winTypes[i] = winType[i];
				m_GuildInfo.lossTypes[i] = lossType[i];
				m_GuildInfo.drawTypes[i] = drawType[i];
			}

			m_GuildInfo.ladderPoints = ladderPoints;
			m_GuildInfo.rank = rank;
		}
#endif
