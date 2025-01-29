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
#if defined(ENABLE_GUILDRENEWAL_SYSTEM) && defined(ENABLE_GUILDSTORAGE_SYSTEM)
			char goldCheckout[CHARACTER_NAME_MAX_LEN + 1];
			char itemCheckout[CHARACTER_NAME_MAX_LEN + 1];
#endif
#ifdef ENABLE_GUILD_WAR_SCORE
			DWORD winTypes[3];
			DWORD lossTypes[3];
			DWORD drawTypes[3];
			DWORD ladderPoints;
			DWORD rank;
#endif
#ifdef ENABLE_GUILD_LAND_INFO
			DWORD mindex;
			DWORD guildAltar;
			DWORD guildAlchemist;
			DWORD guildBlacksmith;
			DWORD storage_lv;
#endif
#ifdef ENABLE_GUILDBANK_LOG
			DWORD pLogCount;
#endif
#ifdef ENABLE_GUILD_DONATE_ATTENDANCE
			//BYTE bMedals;
			BYTE bDonateCount;
#endif
		} TGuildInfo;
