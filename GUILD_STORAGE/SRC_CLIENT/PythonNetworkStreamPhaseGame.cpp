//Open PythonNetworkStreamPhaseGame.cpp find 
void CPythonNetworkStream::__RefreshMallWindow()
{
	m_isRefreshMallWnd=true;
}
//add
#ifdef ENABLE_GUILDSTORAGE_SYSTEM
void CPythonNetworkStream::__RefreshGuildstorageWindow()
{
	m_isRefreshGuildstorageWnd = true;
}
#endif

//find
			case HEADER_GC_MALL_SET:
				ret = RecvMallItemSetPacket();
				break;

			case HEADER_GC_MALL_DEL:
				ret = RecvMallItemDelPacket();
				break;
#ifdef GUILD_WAR_COUNTER
			case HEDAER_GC_GUILD_WAR:
				ret = RecvGuildWarPacket();
				break;
#endif
//add
#ifdef ENABLE_GUILDSTORAGE_SYSTEM
			case HEADER_GC_GUILDSTORAGE_OPEN:
				ret = RecvGuildstorageOpenPacket();
				break;

			case HEADER_GC_GUILDSTORAGE_SET:
				ret = RecvGuildstorageItemSetPacket();
				break;

			case HEADER_GC_GUILDSTORAGE_DEL:
				ret = RecvGuildstorageItemDelPacket();
				break;
#endif

//find
	if (m_isRefreshGuildWndGradePage)
	{
		m_isRefreshGuildWndGradePage=false;
		PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "RefreshGuildGradePage", Py_BuildValue("()"));
		s_nextRefreshTime = curTime + 300;
	}	
//add
#ifdef ENABLE_GUILDSTORAGE_SYSTEM
	if (m_isRefreshGuildstorageWnd)
	{
		m_isRefreshGuildstorageWnd = false;
		PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "RefreshGuildstorage", Py_BuildValue("()"));
		s_nextRefreshTime = curTime + 300;
	}
#endif

//find
void CPythonNetworkStream::__InitializeGamePhase()
{
	__ServerTimeSync_Initialize();

	m_isRefreshStatus=false;
	m_isRefreshCharacterWnd=false;
	m_isRefreshEquipmentWnd=false;
	m_isRefreshInventoryWnd=false;
	m_isRefreshExchangeWnd=false;
	m_isRefreshSkillWnd=false;
	m_isRefreshSafeboxWnd=false;
	m_isRefreshMallWnd=false;
	m_isRefreshMessengerWnd=false;
	m_isRefreshGuildWndInfoPage=false;
	m_isRefreshGuildWndBoardPage=false;
	m_isRefreshGuildWndMemberPage=false;
	m_isRefreshGuildWndMemberPageGradeComboBox=false;
	m_isRefreshGuildWndSkillPage=false;
	m_isRefreshGuildWndGradePage=false;
//add
#ifdef ENABLE_GUILDSTORAGE_SYSTEM
	m_isRefreshGuildstorageWnd = false;
#endif

//find
		case GUILD_SUBHEADER_GC_INFO:
		{
			TPacketGCGuildInfo GuildInfo;
			if (!Recv(sizeof(GuildInfo), &GuildInfo))
				return false;

			CPythonGuild::Instance().EnableGuild();
			CPythonGuild::TGuildInfo & rGuildInfo = CPythonGuild::Instance().GetGuildInfoRef();
			strncpy(rGuildInfo.szGuildName, GuildInfo.name, GUILD_NAME_MAX_LEN);
			rGuildInfo.szGuildName[GUILD_NAME_MAX_LEN] = '\0';

			rGuildInfo.dwGuildID = GuildInfo.guild_id;
			rGuildInfo.dwMasterPID = GuildInfo.master_pid;
			rGuildInfo.dwGuildLevel = GuildInfo.level;
			rGuildInfo.dwCurrentExperience = GuildInfo.exp;
			rGuildInfo.dwCurrentMemberCount = GuildInfo.member_count;
			rGuildInfo.dwMaxMemberCount = GuildInfo.max_member_count;
			rGuildInfo.dwGuildMoney = GuildInfo.gold;
			rGuildInfo.bHasLand = GuildInfo.hasLand;
//add
#if defined(ENABLE_GUILDRENEWAL_SYSTEM) && defined(ENABLE_GUILDSTORAGE_SYSTEM)
			strncpy(rGuildInfo.goldCheckout, GuildInfo.goldCheckout, CHARACTER_NAME_MAX_LEN);
			rGuildInfo.goldCheckout[CHARACTER_NAME_MAX_LEN] = '\0';  // Asegura la terminación en cero

			strncpy(rGuildInfo.itemCheckout, GuildInfo.itemCheckout, CHARACTER_NAME_MAX_LEN);
			rGuildInfo.itemCheckout[CHARACTER_NAME_MAX_LEN] = '\0';
#endif
