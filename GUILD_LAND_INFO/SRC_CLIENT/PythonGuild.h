//open PythonGuild.h find:
		typedef struct SGulidInfo
		{
			DWORD dwGuildID;
			char szGuildName[GUILD_NAME_MAX_LEN+1];
			DWORD dwMasterPID;
			DWORD dwGuildLevel;
			DWORD dwCurrentExperience;
			DWORD dwCurrentMemberCount;
			[,,,,]
//add
#ifdef ENABLE_GUILD_LAND_INFO
			DWORD mindex;
			DWORD guildAltar;
			DWORD guildAlchemist;
			DWORD guildBlacksmith;
			DWORD storage_lv;
#endif
//Now find:
public:
	CPythonGuild();
	virtual ~CPythonGuild();

	void Destroy();

	void EnableGuild():
	[...]
//add
#ifdef ENABLE_GUILD_LAND_INFO
		void SetGuildLandInfo(DWORD mindex, DWORD guildAltar, DWORD guildAlchemist, DWORD guildBlacksmith, DWORD storage_lv)
		{
			m_GuildInfo.mindex = mindex;
			m_GuildInfo.guildAltar = guildAltar;
			m_GuildInfo.guildAlchemist = guildAlchemist;
			m_GuildInfo.guildBlacksmith = guildBlacksmith;
			m_GuildInfo.storage_lv = storage_lv;
		}
#endif
