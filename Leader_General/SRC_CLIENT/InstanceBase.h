class CInstanceBase
{	
	public:
		struct SCreateData
		{
			BYTE	m_bType;
			DWORD	m_dwStateFlags;
			[...]
			DWORD	m_dwHair;
			DWORD	m_dwMountVnum;
//add
#ifdef ENABLE_SHOW_LIDER_AND_GENERAL_GUILD
			BYTE	m_dwNewIsGuildName;
#endif
		[...]


//Find and replace:

#ifdef ENABLE_SHOW_LIDER_AND_GENERAL_GUILD
		void					ChangeGuild(DWORD dwGuildID, DWORD dwNewIsGuildName);
#else
		void					ChangeGuild(DWORD dwGuildID);
#endif

//Find:
		DWORD					GetGuildID();
//Add
#ifdef ENABLE_SHOW_LIDER_AND_GENERAL_GUILD
		BYTE					GetNewIsGuildName();
#endif	

//Find:

	protected:
		BOOL m_isTextTail;		

		// Instance Data
		std::string				m_stName;

		DWORD					m_awPart[CRaceData::PART_MAX_NUM];

		DWORD					m_dwLevel;
		DWORD					m_dwEmpireID;
		DWORD					m_dwGuildID;
//Add
#ifdef ENABLE_SHOW_LIDER_AND_GENERAL_GUILD
		BYTE					m_dwNewIsGuildName;
#endif
