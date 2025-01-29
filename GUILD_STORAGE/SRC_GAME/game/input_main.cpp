/Open input_main.cpp find on 
	switch (pinfo->sub_header)
	{
		case EXCHANGE_SUBHEADER_CG_START:	// arg1 == vid of target character
			if (!ch->GetExchange())
		[...]
					if (to_ch->IsPC())
					{
						if (quest::CQuestManager::instance().GiveItemToPC(ch->GetPlayerID(), to_ch))
						{
							sys_log(0, "Exchange canceled by quest %s %s", ch->GetName(), to_ch->GetName());
							return;
						}
					}

//add
					if (ch->GetMyShop() || ch->IsOpenSafebox() || ch->GetShopOwner() || ch->IsCubeOpen()
#ifdef ENABLE_GUILDSTORAGE_SYSTEM
						|| ch->IsOpenGuildstorage()
#endif
						)
					{
						ch->ChatPacket(CHAT_TYPE_INFO, "[LS;664]");
						return;
					}

					ch->ExchangeStart(to_ch);
				}
			}
			break;		
//find and replace 
#ifdef ENABLE_GUILDSTORAGE_SYSTEM
void CInputMain::SafeboxCheckin(LPCHARACTER ch, const char* c_pData, int bMall)
#else
void CInputMain::SafeboxCheckin(LPCHARACTER ch, const char* c_pData)
#endif
{
	if (quest::CQuestManager::instance().GetPCForce(ch->GetPlayerID())->IsRunning() == true)
		return;

	TPacketCGSafeboxCheckin * p = (TPacketCGSafeboxCheckin *) c_pData;

	if (!ch->CanHandleItem())
		return;

#ifdef ENABLE_GUILDSTORAGE_SYSTEM
	CSafebox* pkSafebox = bMall == 2 ? ch->GetGuildstorage() : ch->GetSafebox();
#else
	CSafebox* pkSafebox = ch->GetSafebox();
#endif
	LPITEM pkItem = ch->GetItem(p->ItemPos);

//in the same function find and replace
	pkItem->RemoveFromCharacter();
	if (!pkItem->IsDragonSoul())
		ch->SyncQuickslot(QUICKSLOT_TYPE_ITEM, p->ItemPos.cell, 255);
	pkSafebox->Add(p->bSafePos, pkItem);
	
	char szHint[128];
	snprintf(szHint, sizeof(szHint), "%s %u", pkItem->GetName(), pkItem->GetCount());
	LogManager::instance().ItemLog(ch, pkItem, "SAFEBOX PUT", szHint);
#if defined(ENABLE_GUILDRENEWAL_SYSTEM) && defined(ENABLE_GUILDSTORAGE_SYSTEM)
	if (bMall == 2)
		LogManager::Instance().GuildLog(ch, ch->GetGuild()->GetID(), pkItem->GetOriginalVnum(), pkItem->GetName(), GUILD_ITEM_TYPE_IN, pkItem->GetCount(), 0);
#endif
}

//find and replace
#ifdef ENABLE_GUILDSTORAGE_SYSTEM
void CInputMain::SafeboxCheckout(LPCHARACTER ch, const char* c_pData, int bMall)
#else
void CInputMain::SafeboxCheckout(LPCHARACTER ch, const char* c_pData, bool bMall)
#endif
{
	TPacketCGSafeboxCheckout * p = (TPacketCGSafeboxCheckout *) c_pData;

	if (!ch->CanHandleItem())
		return;

	CSafebox * pkSafebox;

#ifdef ENABLE_GUILDSTORAGE_SYSTEM
	pkSafebox = bMall == 2 ? ch->GetGuildstorage() : (bMall == 1 ? ch->GetMall() : ch->GetSafebox());
#else
	if (bMall)
		pkSafebox = ch->GetMall();
	else
		pkSafebox = ch->GetSafebox();
#endif
//in the same function find and replace
		pkSafebox->Remove(p->bSafePos);
		pkItem->AddToCharacter(ch, DestPos);
		ITEM_MANAGER::instance().FlushDelayedSave(pkItem);
#if defined(ENABLE_GUILDRENEWAL_SYSTEM) && defined(ENABLE_GUILDSTORAGE_SYSTEM)
		if (bMall == 2)
		{
			CGuild* pGuild = ch->GetGuild();
			if (pGuild)
			{
				pGuild->SetLastCheckout(ch->GetName(), GS_ITEM);
				pGuild->SetLastCheckoutP2P(ch->GetName(), GS_ITEM);
				pGuild->SendGuildInfoPacket(ch);
				TPacketGGGuild p1{};
				TPacketGGGuildChat p2{};

				p1.bHeader = HEADER_GG_GUILD;
				p1.bSubHeader = GUILD_SUBHEADER_GG_REFRESH;
				p1.dwGuild = pGuild->GetID();
				strlcpy(p2.szText, "none", sizeof(p2.szText));

				P2P_MANAGER::Instance().Send(&p1, sizeof(TPacketGGGuild));
				P2P_MANAGER::Instance().Send(&p2, sizeof(TPacketGGGuildChat));
			}
		}
#endif
//find and replace
		pkSafebox->Remove(p->bSafePos);
		if (bMall)
		{
			if (NULL == pkItem->GetProto())
			{
				sys_err ("pkItem->GetProto() == NULL (id : %d)",pkItem->GetID());
				return ;
			}
			// 100% È®·ü·Î ¼Ó¼ºÀÌ ºÙ¾î¾ß ÇÏ´Âµ¥ ¾È ºÙ¾îÀÖ´Ù¸é »õ·Î ºÙÈù´Ù. ...............
			if (100 == pkItem->GetProto()->bAlterToMagicItemPct && 0 == pkItem->GetAttributeCount())
			{
				pkItem->AlterToMagicItem();
			}
		}
		pkItem->AddToCharacter(ch, p->ItemPos);
		ITEM_MANAGER::instance().FlushDelayedSave(pkItem);
#if defined(ENABLE_GUILDRENEWAL_SYSTEM) && defined(ENABLE_GUILDSTORAGE_SYSTEM)
		if (bMall == 2)
		{
			CGuild* pGuild = ch->GetGuild();
			if (pGuild)
			{
				pGuild->SetLastCheckout(ch->GetName(), GS_ITEM);
				pGuild->SetLastCheckoutP2P(ch->GetName(), GS_ITEM);
				pGuild->SendGuildInfoPacket(ch);
				TPacketGGGuild p1{};
				TPacketGGGuildChat p2{};

				p1.bHeader = HEADER_GG_GUILD;
				p1.bSubHeader = GUILD_SUBHEADER_GG_REFRESH;
				p1.dwGuild = pGuild->GetID();
				strlcpy(p2.szText, "none", sizeof(p2.szText));

				P2P_MANAGER::Instance().Send(&p1, sizeof(TPacketGGGuild));
				P2P_MANAGER::Instance().Send(&p2, sizeof(TPacketGGGuildChat));
			}
		}
#endif
	}
//find and replace
	DWORD dwID = pkItem->GetID();
	db_clientdesc->DBPacketHeader(HEADER_GD_ITEM_FLUSH, 0, sizeof(DWORD));
	db_clientdesc->Packet(&dwID, sizeof(DWORD));

	char szHint[128];
	snprintf(szHint, sizeof(szHint), "%s %u", pkItem->GetName(), pkItem->GetCount());
	if (bMall)
		LogManager::instance().ItemLog(ch, pkItem, "MALL GET", szHint);
	else
		LogManager::instance().ItemLog(ch, pkItem, "SAFEBOX GET", szHint);
#if defined(ENABLE_GUILDRENEWAL_SYSTEM) && defined(ENABLE_GUILDSTORAGE_SYSTEM)
	if (bMall == 2)
		LogManager::Instance().GuildLog(ch, ch->GetGuild()->GetID(), pkItem->GetOriginalVnum(), pkItem->GetName(), GUILD_ITEM_TYPE_OUT, pkItem->GetCount(), 0);
#endif
}
//find
void CInputMain::SafeboxItemMove(LPCHARACTER ch, const char * data)
{
	struct command_item_move * pinfo = (struct command_item_move *) data;

	if (!ch->CanHandleItem())
		return;
//replace
#ifdef ENABLE_GUILDSTORAGE_SYSTEM
	if (pinfo->count == 0)
	{
		if (!ch->GetSafebox())
			return;

		ch->GetSafebox()->MoveItem(pinfo->Cell.cell, pinfo->CellTo.cell, pinfo->count);
	}
	else if (pinfo->count == 2)
	{
		if (!ch->GetGuildstorage())
			return;

		ch->GetGuildstorage()->MoveItem(pinfo->Cell.cell, pinfo->CellTo.cell, 0);
	}
#else
	if (!ch->GetSafebox())
		return;

	ch->GetSafebox()->MoveItem(static_cast<BYTE>(pinfo->Cell.cell), static_cast<BYTE>(pinfo->CellTo.cell), pinfo->count);
#endif
}

//find and replace (GUILD_SUBHEADER_CG_DEPOSIT_MONEY ; and WITHDRAM_MONEY) if u don't want replace only add function
	switch (SubHeader)
	{
		case GUILD_SUBHEADER_CG_DEPOSIT_MONEY:	//Einzahlen
			{
#ifndef ENABLE_GUILDRENEWAL_SYSTEM
				return SubPacketLen;
#endif
				const int gold = MIN(*reinterpret_cast<const int*>(c_pData), __deposit_limit());

				if (gold < 0)
				{
					ch->ChatPacket(CHAT_TYPE_INFO, "[LS;686]");
					return SubPacketLen;
				}

				if (ch->GetGold() < gold)
				{
					ch->ChatPacket(CHAT_TYPE_INFO, "[LS;687]");
					return SubPacketLen;
				}

#ifdef ENABLE_GUILDSTORAGE_SYSTEM
				if (gold > GOLD_MAX - 1) {	//Can't Put more than 2kkk into Guildstorage from your Pocket
					ch->ChatPacket(CHAT_TYPE_INFO, "[LS;2039]");
					return SubPacketLen;
				}

				if ((gold + pGuild->GetGuildMoney()) > (GOLD_MAX - 1)) {
					int gold_add = (GOLD_MAX - 1) - pGuild->GetGuildMoney();
					ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("GUILDSTORAGE_TOOK_INSTEAD %d"), gold_add);
					pGuild->RequestDepositMoney(ch, gold_add);
				}
				else
					pGuild->RequestDepositMoney(ch, gold);
#else
				pGuild->RequestDepositMoney(ch, gold);
#endif
			}
			return SubPacketLen;

		case GUILD_SUBHEADER_CG_WITHDRAW_MONEY:	//Auszahlen
			{
#ifndef ENABLE_GUILDRENEWAL_SYSTEM
				return SubPacketLen;
				const int gold = MIN(*reinterpret_cast<const int*>(c_pData), 500000);
#else
				const int gold = MIN(*reinterpret_cast<const int*>(c_pData), __deposit_limit());
#endif

				if (gold < 0) {
					ch->ChatPacket(CHAT_TYPE_INFO, "[LS;686]");
					return SubPacketLen;
				}

#ifdef ENABLE_GUILDSTORAGE_SYSTEM
				if (gold > GOLD_MAX) {
					ch->ChatPacket(CHAT_TYPE_INFO, "[LS;2040]");
					return SubPacketLen;
				}
				if (gold > pGuild->GetGuildMoney()) {	//Can't put out more than Money in Guildbank
					ch->ChatPacket(CHAT_TYPE_INFO, "[LS;2041]");
					return SubPacketLen;
				}

				if ((gold + ch->GetGold()) > (GOLD_MAX - 1)) {
					int gold_add = (GOLD_MAX - 1) - ch->GetGold();
					ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("GUILDSTORAGE_TOOK_INSTEAD %d"), gold_add);
					pGuild->RequestWithdrawMoney(ch, gold_add);
				}
				else
					pGuild->RequestWithdrawMoney(ch, gold);
#else
				pGuild->RequestWithdrawMoney(ch, gold);
#endif
			}
			return SubPacketLen;
//Fix for kick member find and replace
		case GUILD_SUBHEADER_CG_ADD_MEMBER:
			{
				const DWORD vid = *reinterpret_cast<const DWORD*>(c_pData);
				LPCHARACTER newmember = CHARACTER_MANAGER::instance().Find(vid);

				// if (!newmember)
				if (!newmember || !newmember->IsPC()) // Fix
				{
					ch->ChatPacket(CHAT_TYPE_INFO, "[LS;688]");
					return SubPacketLen;
				}

//find
		case HEADER_CG_TARGET:
			Target(ch, c_pData);
			break;

		case HEADER_CG_WARP:
			Warp(ch, c_pData);
			break;
//replace
		case HEADER_CG_SAFEBOX_CHECKIN:
#ifdef ENABLE_GUILDSTORAGE_SYSTEM
			SafeboxCheckin(ch, c_pData, 0);
#else
			SafeboxCheckin(ch, c_pData);
#endif
			break;
//add
#ifdef ENABLE_GUILDSTORAGE_SYSTEM
		case HEADER_CG_GUILDSTORAGE_CHECKIN:
			SafeboxCheckin(ch, c_pData, 2);
			break;
#endif
//replace
		case HEADER_CG_SAFEBOX_CHECKOUT:
#ifdef ENABLE_GUILDSTORAGE_SYSTEM
			SafeboxCheckout(ch, c_pData, 0);
#else
			SafeboxCheckout(ch, c_pData, false);
#endif
			break;
//find and replace 
		case HEADER_CG_MALL_CHECKOUT:
#ifdef ENABLE_GUILDSTORAGE_SYSTEM
			SafeboxCheckout(ch, c_pData, 1);
#else
			SafeboxCheckout(ch, c_pData, true);
#endif
			break;
//add
#ifdef ENABLE_GUILDSTORAGE_SYSTEM
		case HEADER_CG_GUILDSTORAGE_CHECKOUT:
			SafeboxCheckout(ch, c_pData, 2);
			break;
#endif
--------------
--------------
--------------
//Open input_p2p.cpp find 
int CInputP2P::Guild(LPDESC d, const char* c_pData, size_t uiBytes)
{
	TPacketGGGuild * p = (TPacketGGGuild *) c_pData;
	uiBytes -= sizeof(TPacketGGGuild);
	c_pData += sizeof(TPacketGGGuild);

	CGuild * g = CGuildManager::instance().FindGuild(p->dwGuild);

	switch (p->bSubHeader)
	{
//add
#if defined(ENABLE_GUILDRENEWAL_SYSTEM) && defined(ENABLE_GUILDSTORAGE_SYSTEM)
		case GUILD_SUBHEADER_GG_REFRESH:
			{
				if (uiBytes < sizeof(TPacketGGGuildChat))
					return -1;

				if (g)
					g->RefreshP2P(g);

				return sizeof(TPacketGGGuildChat);
			}

		case GUILD_SUBHEADER_GG_REFRESH1:
			{
				if (uiBytes < sizeof(TPacketGGGuildChat))
					return -1;

				TPacketGGGuildChat * p2 = (TPacketGGGuildChat *) c_pData;

				if (g)
					g->SetLastCheckoutP2P(p2->szText, p2->dwGuild);

				return sizeof(TPacketGGGuildChat);
			}
#endif
