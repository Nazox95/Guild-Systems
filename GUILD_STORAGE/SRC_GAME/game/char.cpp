//Open char.cpp find
void CHARACTER::Initialize()
{
	CEntity::Initialize(ENTITY_CHARACTER);

	m_bNoOpenedShop = true;

	m_bOpeningSafebox = false;
//add
#ifdef ENABLE_GUILDSTORAGE_SYSTEM
	m_bOpeningGuildstorage = false;
#endif

//find 
	m_pkChrStone = NULL;

	m_pkSafebox = NULL;
	m_iSafeboxSize = -1;
	m_iSafeboxLoadTime = 0;

	m_pkMall = NULL;
	m_iMallLoadTime = 0;
//add 
#ifdef ENABLE_GUILDSTORAGE_SYSTEM
	m_pkGuildstorage = nullptr;
	m_iGuildstorageLoadTime = 0;
#endif

//find
	// ARENA
	m_pArena = NULL;
	m_nPotionLimit = quest::CQuestManager::instance().GetEventFlag("arena_potion_limit_count");
	// END_ARENA

	//PREVENT_TRADE_WINDOW
	m_isOpenSafebox = 0;
//add
#ifdef ENABLE_GUILDSTORAGE_SYSTEM
	m_isOpenGuildstorage = 0;
#endif
	//END_PREVENT_TRADE_WINDOW

//find 
	if (m_pkSafebox)
	{
		M2_DELETE(m_pkSafebox);
		m_pkSafebox = NULL;
	}

	if (m_pkMall)
	{
		M2_DELETE(m_pkMall);
		m_pkMall = NULL;
	}
//add
#ifdef ENABLE_GUILDSTORAGE_SYSTEM
	if (m_pkGuildstorage)
	{
		M2_DELETE(m_pkGuildstorage);
		m_pkGuildstorage = nullptr;
	}
#endif

//find
void CHARACTER::Disconnect(const char * c_pszReason)
{
	assert(GetDesc() != NULL);

	sys_log(0, "DISCONNECT: %s (%s)", GetName(), c_pszReason ? c_pszReason : "unset" );

//add
#ifdef ENABLE_GUILDSTORAGE_SYSTEM
	if (GetGuild() && IsOpenGuildstorage())
	{
		GetGuild()->SetStorageState(false, 0);
	}
#endif

//find 
	if (!CHARACTER_MANAGER::instance().FlushDelayedSave(this))
	{
		SaveReal();
	}

	FlushDelayedSaveItem();

	SaveAffect();
	m_bIsLoadedAffect = false;

	m_bSkipSave = true; // ÀÌ ÀÌÈÄ¿¡´Â ´õÀÌ»ó ÀúÀåÇÏ¸é ¾ÈµÈ´Ù.

	quest::CQuestManager::instance().DisconnectPC(this);

	CloseSafebox();

	CloseMall();
//add
#ifdef ENABLE_GUILDSTORAGE_SYSTEM
	CloseGuildstorage();
#endif

//find (if you have offline shop of Great)
void CHARACTER::OnClick(LPCHARACTER pkChrCauser)
//in this function search and replace
				//PREVENT_TRADE_WINDOW
				if (pkChrCauser == this) // ÀÚ±â´Â °¡´É
				{
					if ((GetExchange() || IsOpenSafebox() || GetShopOwner()) || IsCubeOpen()
# ifdef ENABLE_GUILDSTORAGE_SYSTEM
					|| IsOpenGuildstorage()
# endif
						)
					{
						pkChrCauser->ChatPacket(CHAT_TYPE_INFO, "[LS;841]");
						return;
					}
				}
				else // ´Ù¸¥ »ç¶÷ÀÌ Å¬¸¯ÇßÀ»¶§
				{
					// Å¬¸¯ÇÑ »ç¶÷ÀÌ ±³È¯/Ã¢°í/°³ÀÎ»óÁ¡/»óÁ¡ÀÌ¿ëÁßÀÌ¶ó¸é ºÒ°¡
					if ((pkChrCauser->GetExchange() || pkChrCauser->IsOpenSafebox() || pkChrCauser->GetMyShop() || pkChrCauser->GetShopOwner()) || pkChrCauser->IsCubeOpen()
# ifdef ENABLE_GUILDSTORAGE_SYSTEM
					|| IsOpenGuildstorage()
# endif
					)
					{
						pkChrCauser->ChatPacket(CHAT_TYPE_INFO, "[LS;841]");
						return;
					}

					// Å¬¸¯ÇÑ ´ë»óÀÌ ±³È¯/Ã¢°í/»óÁ¡ÀÌ¿ëÁßÀÌ¶ó¸é ºÒ°¡
					//if ((GetExchange() || IsOpenSafebox() || GetShopOwner()))
					if ((GetExchange() || IsOpenSafebox() || IsCubeOpen())
# ifdef ENABLE_GUILDSTORAGE_SYSTEM
						|| IsOpenGuildstorage()
# endif

//If you use other offline shop add
# ifdef ENABLE_GUILDSTORAGE_SYSTEM
					|| IsOpenGuildstorage()
# endif
//in the functions like 
if ((pkChrCauser->GetExchange() || pkChrCauser->IsOpenSafebox() || pkChrCauser->GetMyShop()

//find
bool CHARACTER::WarpSet(long x, long y, long lPrivateMapIndex)
{
	if (!IsPC())
		return false;

	long lAddr;
	long lMapIndex;
	WORD wPort;

	if (!CMapLocation::instance().Get(x, y, lMapIndex, lAddr, wPort))
	{
		sys_err("cannot find map location index %d x %d y %d name %s", lMapIndex, x, y, GetName());
		return false;
	}
//add
#ifdef ENABLE_GUILDSTORAGE_SYSTEM
	if (GetGuild() && IsOpenGuildstorage())
		CloseGuildstorage();
#endif

// find 
void CHARACTER::SetSafeboxOpenPosition()
{
	m_posSafeboxOpen = GetXYZ();
}
//add
#ifdef ENABLE_GUILDSTORAGE_SYSTEM
float CHARACTER::GetDistanceFromGuildstorageOpen() const
{
	return DISTANCE_APPROX(GetX() - m_posGuildstorageOpen.x, GetY() - m_posGuildstorageOpen.y);
}

void CHARACTER::SetGuildstorageOpenPosition()
{
	m_posGuildstorageOpen = GetXYZ();
}
#endif

//find 
void CHARACTER::ChangeSafeboxSize(BYTE bSize)
{
	//if (!m_pkSafebox)
	//return;

	TPacketCGSafeboxSize p;

	p.bHeader = HEADER_GC_SAFEBOX_SIZE;
	p.bSize = bSize;

	GetDesc()->Packet(&p, sizeof(TPacketCGSafeboxSize));

	if (m_pkSafebox)
		m_pkSafebox->ChangeSize(bSize);

	m_iSafeboxSize = bSize;
}
//add
#ifdef ENABLE_GUILDSTORAGE_SYSTEM
void CHARACTER::ReqGuildstorageLoad()
{
	CGuild* pGuild = GetGuild();
	if (!pGuild) {
		ChatPacket(CHAT_TYPE_INFO, "[LS;2035]");
		return;// no guild ptr fix
	}

	if (pGuild->GetGuildstorage() == 0) {
		ChatPacket(CHAT_TYPE_INFO, "[LS;2036]");
		return;
	}

	if (GetExchange() || GetMyShop() || GetShopOwner() || IsOpenSafebox() || IsCubeOpen())
	{
		ChatPacket(CHAT_TYPE_INFO, "[LS;2037]");
		return;
	}

#	ifdef ENABLE_GUILDRENEWAL_SYSTEM
	const TGuildMember* m = pGuild->GetMember(GetPlayerID());
	if (!pGuild->HasGradeAuth(m->grade, GUILD_AUTH_BANK))
	{
		ChatPacket(CHAT_TYPE_INFO, "[LS;2038]");
		return;
	}
#	endif

	if (pGuild->IsStorageOpen())
	{
		LPCHARACTER pChar = CHARACTER_MANAGER::Instance().FindByPID(pGuild->GetStoragePid());
		if (pChar) {
			pChar->ChatPacket(7, "player %s want to open storage.", GetName());
			ChatPacket(CHAT_TYPE_INFO, "guild is already open by %s", pChar->GetName());
		}
		else
			ChatPacket(CHAT_TYPE_INFO, "guild is already open");
		return;
	}

	if (GetGuildstorage())
	{
		ChatPacket(CHAT_TYPE_INFO, "[LS;527]");
		return;
	}
	else if (GetDistanceFromGuildstorageOpen() > 1000)
	{
		ChatPacket(CHAT_TYPE_INFO, "[LS;529]");
		return;
	}
	else if (m_bOpeningGuildstorage)
	{
		sys_log(0, "Overlapped guildstorage load request from %s", GetName());
		return;
	}

	SetGuildstorageLoadTime();
	m_bOpeningGuildstorage = true;

	TSafeboxLoadPacket p;
	p.dwID = GetGuild() ? GetGuild()->GetID() : 0;
	strlcpy(p.szLogin, GetDesc()->GetAccountTable().login, sizeof(p.szLogin));
	strlcpy(p.szPassword, "000000", sizeof(p.szPassword));

	if (!p.dwID)
		return;

	db_clientdesc->DBPacket(HEADER_GD_GUILDSTORAGE_LOAD, GetDesc()->GetHandle(), &p, sizeof(p));
	pGuild->SetStorageState(true, GetPlayerID());
}

void CHARACTER::ChangeGuildstorageSize(BYTE bSize)
{
	TPacketGCGuildstorageOpen p{};

	p.bHeader = HEADER_GC_GUILDSTORAGE_OPEN;
	p.bSize = bSize;

	GetDesc()->Packet(&p, sizeof(TPacketGCGuildstorageOpen));

	if (m_pkGuildstorage)
		m_pkGuildstorage->ChangeSize(bSize);

	m_iSafeboxSize = bSize;
}
#endif

//find 
void CHARACTER::CloseMall()
{
	if (!m_pkMall)
		return;

	m_pkMall->Save();

	M2_DELETE(m_pkMall);
	m_pkMall = NULL;

	ChatPacket(CHAT_TYPE_COMMAND, "CloseMall");
}
//add
#ifdef ENABLE_GUILDSTORAGE_SYSTEM
CSafebox* CHARACTER::GetGuildstorage() const
{
	return m_pkGuildstorage;
}

//find 
int CHARACTER::GetSafeboxSize() const
{
	return m_iSafeboxSize;
}
//add
#ifdef ENABLE_GUILDSTORAGE_SYSTEM
void CHARACTER::QueryGuildstorageSize()
{
	if (m_iGuildstorageSize == -1)
	{
		DBManager::Instance().ReturnQuery(QID_GUILDSTORAGE_SIZE,
			GetPlayerID(),
			nullptr,
			"SELECT guildstorage FROM guild%s WHERE id = %u",
			get_table_postfix(),
			GetGuild()->GetID());
	}
}

void CHARACTER::SetGuildstorageSize(int iSize)
{
	sys_log(1, "SetGuildstorageSize: %s %d", GetName(), iSize);
	m_iGuildstorageSize = iSize;
	GetGuild()->SetGuildstorage(iSize / SAFEBOX_PAGE_SIZE);
	//DBManager::Instance().Query("UPDATE guild%s SET guildstorage = %d WHERE id = %u", get_table_postfix(), iSize / SAFEBOX_PAGE_SIZE, GetGuild()->GetID());
}

int CHARACTER::GetGuildstorageSize() const
{
	return m_iGuildstorageSize;
}
#endif

//find
	if (iPulse - GetSafeboxLoadTime() < PASSES_PER_SEC(limittime))
	{
		if (bSendMsg)
			ChatPacket(CHAT_TYPE_INFO, "[LS;850;%d]", limittime);

		if (test_server)
			ChatPacket(CHAT_TYPE_INFO, "[TestOnly]Pulse %d LoadTime %d PASS %d", iPulse, GetSafeboxLoadTime(), PASSES_PER_SEC(limittime));
		return true; 
	}
//add the new macro or replace (if u don't have, find something like this and add 'IsOpenGuildstorage()')
	//°Å·¡°ü·Ã Ã¢ Ã¼Å©
	if (bCheckShopOwner)
	{
		if (GetExchange() || GetMyShop() || GetShopOwner() || IsOpenSafebox() || IsCubeOpen()
# ifdef ENABLE_GUILDSTORAGE_SYSTEM
			|| IsOpenGuildstorage()
# endif
			)
		{
			if (bSendMsg)
				ChatPacket(CHAT_TYPE_INFO, "[LS;851]");

			return true;
		}
	}
	else
	{
		if (GetExchange() || GetMyShop() || IsOpenSafebox() || IsCubeOpen()
# ifdef ENABLE_GUILDSTORAGE_SYSTEM
			|| IsOpenGuildstorage()
# endif
			)
		{
			if (bSendMsg)
				ChatPacket(CHAT_TYPE_INFO, "[LS;851]");

			return true;
		}
	}

//find and replace 
bool CHARACTER::CanWarp() const
{
	const int iPulse = thecore_pulse();
	const int limit_time = PASSES_PER_SEC(g_nPortalLimitTime);

	if ((iPulse - GetSafeboxLoadTime()) < limit_time)
		return false;

#ifdef ENABLE_GUILDSTORAGE_SYSTEM
	if ((iPulse - GetGuildstorageLoadTime()) < limit_time)
		return false;
#endif

	if ((iPulse - GetExchangeTime()) < limit_time)
		return false;

	if ((iPulse - GetMyShopTime()) < limit_time)
		return false;

	if ((iPulse - GetRefineTime()) < limit_time)
		return false;

	if (GetExchange() || GetMyShop() || GetShopOwner() || IsOpenSafebox() || IsCubeOpen()
# ifdef ENABLE_GUILDSTORAGE_SYSTEM
			|| IsOpenGuildstorage()
# endif
		)
		return false;

	return true;
}

//If u have sort inventory from Mali find and replace 
	if (IsDead() || GetExchange() || GetMyShop() || GetShopOwner() || IsOpenSafebox() || IsCubeOpen()
# ifdef ENABLE_GUILDSTORAGE_SYSTEM
			|| IsOpenGuildstorage()
# endif
