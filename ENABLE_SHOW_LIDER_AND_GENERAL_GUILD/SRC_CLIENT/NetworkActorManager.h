//Open NetworkActorManager.h and find:
struct SNetworkActorData
{
	std::string m_stName;
	
	CAffectFlagContainer	m_kAffectFlags;

	BYTE	m_bType;
	DWORD	m_dwVID;
	[...]
	DWORD	m_dwMountVnum;

	DWORD	m_dwGuildID;
//add
#ifdef ENABLE_SHOW_LIDER_AND_GENERAL_GUILD
	BYTE	m_dwNewIsGuildName;
#endif

//find:
struct SNetworkUpdateActorData
{
	DWORD m_dwVID;
	DWORD m_dwGuildID;
	[...]
	BYTE m_byPKMode;
	DWORD m_dwMountVnum;
//add
#ifdef ENABLE_SHOW_LIDER_AND_GENERAL_GUILD
	DWORD m_dwNewIsGuildName;
#endif
	DWORD m_dwStateFlags; // º»·¡ Create ¶§¸¸ ¾²ÀÌ´Â º¯¼öÀÓ
	CAffectFlagContainer m_kAffectFlags;

//find:
	SNetworkUpdateActorData()
	{
		m_dwGuildID=0;
		m_dwVID=0;
		[...]
		m_dwMountVnum=0;
//add
#ifdef ENABLE_SHOW_LIDER_AND_GENERAL_GUILD
		m_dwNewIsGuildName = 0;
#endif	
		m_dwStateFlags=0;
		m_kAffectFlags.Clear();
	}
};
