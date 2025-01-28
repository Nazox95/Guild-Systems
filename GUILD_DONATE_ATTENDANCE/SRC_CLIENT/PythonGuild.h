//Open PythonGuild.h and find:
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
//add :
#ifdef ENABLE_GUILD_DONATE_ATTENDANCE
			//BYTE bMedals;
			BYTE bDonateCount;
#endif

//Now find this:
	protected:
		void __CalculateLevelAverage();
		void __SortMember();
		BOOL __IsGradeData(BYTE byGradeNumber);

		void __Initialize();
//Add before (if you don't have this, add in the end before };)
#ifdef ENABLE_GUILD_DONATE_ATTENDANCE
	public:
//		void SetGuildDonateInfo(int medals) { m_GuildInfo.bMedals = medals; }
		void SetGuilDonateCount(int count) { m_GuildInfo.bDonateCount = count; }
#endif
