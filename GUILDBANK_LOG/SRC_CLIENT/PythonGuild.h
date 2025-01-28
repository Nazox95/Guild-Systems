//Open PythonGuild.h and find:
class CPythonGuild : public CSingleton<CPythonGuild>
{
	public:
		enum
		{
			GUILD_SKILL_MAX_NUM = 12,
			ENEMY_GUILD_SLOT_MAX_COUNT = 6,
		};
//add
#ifdef ENABLE_GUILDBANK_LOG
		typedef struct SGuildBank
		{
			char szName[24];
			char szItemName[24];
			int itemAction;
			int itemCount;
			int datatype;
		} BankLog;
#endif

//Now find:
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
#ifdef ENABLE_GUILDBANK_LOG
			DWORD pLogCount;
#endif

//Now before:
protected:
	void __CalculateLevelAverage();
	[...]
//add
#ifdef ENABLE_GUILDBANK_LOG
		void IncreaseBankLog()
		{
			++m_GuildInfo.pLogCount;
		}

		void ClearBankLog()
		{
			log.clear();
			m_GuildInfo.pLogCount = 0;
		}

		void SetGuildBankLogs(const char* name, const char* itemName, int itemAction, int itemCount, int datatype)
		{
			const int index = m_GuildInfo.pLogCount;
			if (index == 0 || index <= 0)
			{
				log.clear();
			}
			BankLog entry;
			entry.datatype = datatype;
			entry.itemCount = itemCount;
			entry.itemAction = itemAction;

			strncpy(entry.szName, name, sizeof(entry.szName));
			strncpy(entry.szItemName, itemName, sizeof(entry.szItemName));
			//m_GuildInfo.log.emplace(std::pair<int, BankLog>(index, entry));
			log[index] = entry;
		}
		std::map<int, BankLog> GetLogs()
		{
			return log;
		}
private:
	std::map<int, BankLog> log;
	//BankLog log[1024];
#endif
