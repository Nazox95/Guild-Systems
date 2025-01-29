//Open ClientManager.cpp find and replace
#ifdef ENABLE_GUILDSTORAGE_SYSTEM
void CClientManager::QUERY_SAFEBOX_LOAD(CPeer* pkPeer, DWORD dwHandle, const TSafeboxLoadPacket* packet, int bMall)
#else
void CClientManager::QUERY_SAFEBOX_LOAD(CPeer* pkPeer, DWORD dwHandle, const TSafeboxLoadPacket* packet, bool bMall)
#endif
{
	ClientHandleInfo * pi = new ClientHandleInfo(dwHandle);
	strlcpy(pi->safebox_password, packet->szPassword, sizeof(pi->safebox_password));
	pi->account_id = packet->dwID;
	pi->account_index = 0;
#ifdef ENABLE_GUILDSTORAGE_SYSTEM
	pi->ip[0] = bMall == 2 ? 2 : (bMall == 1 ? 1 : 0);
#else
	pi->ip[0] = bMall ? 1 : 0;
#endif
	strlcpy(pi->login, packet->szLogin, sizeof(pi->login));

	char szQuery[QUERY_MAX_LEN];
	snprintf(szQuery, sizeof(szQuery),
#if defined(__BL_SAFEBOX_MONEY__)
			"SELECT account_id, size, password, gold FROM safebox%s WHERE account_id=%u",
#else
			"SELECT account_id, size, password FROM safebox%s WHERE account_id=%u",
#endif
			GetTablePostfix(), packet->dwID);
	
	if (g_log)
#ifdef ENABLE_GUILDSTORAGE_SYSTEM
		sys_log(0, "HEADER_GD_SAFEBOX_LOAD (handle: %d account.id %u is_mall %d)", dwHandle, packet->dwID, bMall==1 ? 1 : (bMall == 2 ? 2: 0));
#else
		sys_log(0, "HEADER_GD_SAFEBOX_LOAD (handle: %d account.id %u is_mall %d)", dwHandle, packet->dwID, bMall ? 1 : 0);
#endif

	CDBManager::instance().ReturnQuery(szQuery, QID_SAFEBOX_LOAD, pkPeer->GetHandle(), pi);
}

//in this function 
void CClientManager::RESULT_SAFEBOX_LOAD(CPeer * pkPeer, SQLMsg * msg)
//find
		char szQuery[512];
		snprintf(szQuery, sizeof(szQuery), 
				"SELECT id, window+0, pos, count, vnum, socket0, socket1, socket2, "
				"attrtype0, attrvalue0, "
				"attrtype1, attrvalue1, "
				"attrtype2, attrvalue2, "
				"attrtype3, attrvalue3, "
				"attrtype4, attrvalue4, "
				"attrtype5, attrvalue5, "
				"attrtype6, attrvalue6 "
				"FROM item%s WHERE owner_id=%d AND window='%s'",
				GetTablePostfix(), pi->account_id,
				pi->ip[0] == 0 ? "SAFEBOX" : "MALL"
		);

		pi->account_index = 1;

		CDBManager::instance().ReturnQuery(szQuery, QID_SAFEBOX_LOAD, pkPeer->GetHandle(), pi);
	}
//replace like this:
				"FROM item%s WHERE owner_id=%d AND window='%s'",
				GetTablePostfix(), pi->account_id,
#ifdef ENABLE_GUILDSTORAGE_SYSTEM
				pi->ip[0] == 0 ? "SAFEBOX" : (pi->ip[0] == 2 ? "GUILDBANK" : "MALL")
#else
				pi->ip[0] == 0 ? "SAFEBOX" : "MALL"
#endif
		);

		pi->account_index = 1;

		CDBManager::instance().ReturnQuery(szQuery, QID_SAFEBOX_LOAD, pkPeer->GetHandle(), pi);
	}

//in the same function find
			if (!bEscape)
			{
				std::vector<std::pair<DWORD, DWORD> > vec_dwFinishedAwardID;

				__typeof(pSet->begin()) it = pSet->begin();

				char szQuery[512];

				while (it != pSet->end())
				{
					TItemAward * pItemAward = *(it++);
					const DWORD& dwItemVnum = pItemAward->dwVnum;

					if (pItemAward->bTaken)
						continue;

					if (pi->ip[0] == 0 && pItemAward->bMall)
						continue;

					if (pi->ip[0] == 1 && !pItemAward->bMall)
						continue;
//add
#ifdef ENABLE_GUILDSTORAGE_SYSTEM
					if (pi->ip[0] == 2 && pItemAward->bMall)
						continue;
#endif

//The same function find
						snprintf(szQuery, sizeof(szQuery), 
								"INSERT INTO item%s (id, owner_id, window, pos, vnum, count, socket0, socket1, socket2) "
								"VALUES(%u, %u, '%s', %d, %u, %u, %u, %u, %u)",
								GetTablePostfix(),
								GainItemID(),
								pi->account_id,
//replace
#ifdef ENABLE_GUILDSTORAGE_SYSTEM
								pi->ip[0] == 0 ? "SAFEBOX" : (pi->ip[0] == 2 ? "GUILDBANK" : "MALL"),
#else
								pi->ip[0] == 0 ? "SAFEBOX" : "MALL",
#endif
								iPos,
								pItemAward->dwVnum, pItemAward->dwCount, pItemAward->dwSocket0, pItemAward->dwSocket1, dwSocket2);
					}

					std::unique_ptr<SQLMsg> pmsg(CDBManager::instance().DirectQuery(szQuery));
					SQLResult * pRes = pmsg->Get();
					sys_log(0, "SAFEBOX Query : [%s]", szQuery);

					if (pRes->uiAffectedRows == 0 || pRes->uiInsertID == 0 || pRes->uiAffectedRows == (DWORD)-1)
						break;

					item.id = pmsg->Get()->uiInsertID;
//replace					
#ifdef ENABLE_GUILDSTORAGE_SYSTEM
					item.window = pi->ip[0] == 0 ? SAFEBOX : (pi->ip[0] == 2 ? GUILDBANK : MALL);
#else
					item.window = pi->ip[0] == 0 ? SAFEBOX : MALL,
#endif
					item.pos = iPos;
					item.count = pItemAward->dwCount;
					item.vnum = pItemAward->dwVnum;
					item.alSockets[0] = pItemAward->dwSocket0;
					item.alSockets[1] = pItemAward->dwSocket1;
					item.alSockets[2] = dwSocket2;

//Below find
				for (DWORD i = 0; i < vec_dwFinishedAwardID.size(); ++i)
					ItemAwardManager::instance().Taken(vec_dwFinishedAwardID[i].first, vec_dwFinishedAwardID[i].second);
			}
		}

		pi->pSafebox->wItemCount = s_items.size();

//replace
#ifdef ENABLE_GUILDSTORAGE_SYSTEM
		pkPeer->EncodeHeader(pi->ip[0] == 0 ? HEADER_DG_SAFEBOX_LOAD : (pi->ip[0] == 2 ? HEADER_DG_GUILDSTORAGE_LOAD : HEADER_DG_MALL_LOAD), dwHandle, sizeof(TSafeboxTable) + sizeof(TPlayerItem) * s_items.size());
#else
		pkPeer->EncodeHeader(pi->ip[0] == 0 ? HEADER_DG_SAFEBOX_LOAD : HEADER_DG_MALL_LOAD, dwHandle, sizeof(TSafeboxTable) + sizeof(TPlayerItem) * s_items.size());
#endif

		pkPeer->Encode(pi->pSafebox, sizeof(TSafeboxTable));

		if (!s_items.empty())
			pkPeer->Encode(&s_items[0], sizeof(TPlayerItem) * s_items.size());

		delete pi;
	}
}

//Find
void CClientManager::RESULT_SAFEBOX_CHANGE_SIZE(CPeer * pkPeer, SQLMsg * msg)
//add after
#ifdef ENABLE_GUILDSTORAGE_SYSTEM
void CClientManager::QUERY_GUILDSTORAGE_CHANGE_SIZE(CPeer* pkPeer, DWORD dwHandle, TGuildstorageChangeSizePacket* p)
{
	ClientHandleInfo* pi = new ClientHandleInfo(dwHandle);
	pi->account_index = p->bSize;

	char szQuery[QUERY_MAX_LEN];

	if (p->bSize == 1)
		snprintf(szQuery, sizeof(szQuery), "INSERT INTO guild%s (id, guildstorage) VALUES(%u, %u)", GetTablePostfix(), p->dwID, p->bSize);
	else
		snprintf(szQuery, sizeof(szQuery), "UPDATE guild%s SET guildstorage=%u WHERE id=%u", GetTablePostfix(), p->bSize, p->dwID);

	CDBManager::Instance().ReturnQuery(szQuery, QID_GUILDSTORAGE_CHANGE_SIZE, pkPeer->GetHandle(), pi);
}

void CClientManager::RESULT_GUILDSTORAGE_CHANGE_SIZE(CPeer* pkPeer, SQLMsg* msg)
{
	CQueryInfo* qi = (CQueryInfo*)msg->pvUserData;
	ClientHandleInfo* p = (ClientHandleInfo*)qi->pvData;
	DWORD dwHandle = p->dwHandle;
	BYTE bSize = p->account_index;

	delete p;

	if (msg->Get()->uiNumRows > 0)
	{
		pkPeer->EncodeHeader(HEADER_DG_GUILDSTORAGE_CHANGE_SIZE, dwHandle, sizeof(BYTE));
		pkPeer->EncodeBYTE(bSize);
	}
}
#endif

//find
void CClientManager::QUERY_ITEM_SAVE(CPeer * pkPeer, const char * c_pData)
{
	TPlayerItem * p = (TPlayerItem *) c_pData;

	// Ã¢°í¸é Ä³½¬ÇÏÁö ¾Ê°í, Ä³½¬¿¡ ÀÖ´ø °Íµµ »©¹ö·Á¾ß ÇÑ´Ù.
	// auctionÀº ÀÌ ·çÆ®¸¦ Å¸Áö ¾Ê¾Æ¾ß ÇÑ´Ù. EnrollInAuctionÀ» Å¸¾ßÇÑ´Ù.
//replace
	if (p->window == SAFEBOX || p->window == MALL
#ifdef ENABLE_GUILDSTORAGE_SYSTEM
		|| p->window == GUILDBANK
#endif
		)
	{

//Find 
			case HEADER_GD_SAFEBOX_CHANGE_SIZE:
				QUERY_SAFEBOX_CHANGE_SIZE(peer, dwHandle, (TSafeboxChangeSizePacket *) data);
				break;
//add
#ifdef ENABLE_GUILDSTORAGE_SYSTEM
			case HEADER_GD_GUILDSTORAGE_CHANGE_SIZE:
				QUERY_GUILDSTORAGE_CHANGE_SIZE(peer, dwHandle, (TGuildstorageChangeSizePacket*)data);
				break;
#endif

//Find 
			case HEADER_GD_MALL_LOAD:
				QUERY_SAFEBOX_LOAD(peer, dwHandle, (TSafeboxLoadPacket *) data, 1);
				break;
//add
#ifdef ENABLE_GUILDSTORAGE_SYSTEM
			case HEADER_GD_GUILDSTORAGE_LOAD:
				QUERY_SAFEBOX_LOAD(peer, dwHandle, (TSafeboxLoadPacket*)data, 2);
				break;
#endif

//Find 
		case QID_SAFEBOX_CHANGE_SIZE:
			sys_log(0, "QUERY_RESULT: HEADER_GD_SAFEBOX_CHANGE_SIZE");
			RESULT_SAFEBOX_CHANGE_SIZE(peer, msg);
			break;
//add
#ifdef ENABLE_GUILDSTORAGE_SYSTEM
		case QID_GUILDSTORAGE_CHANGE_SIZE:
			sys_log(0, "QUERY_RESULT: HEADER_GD_GUILDSTORAGE_CHANGE_SIZE");
			RESULT_GUILDSTORAGE_CHANGE_SIZE(peer, msg);
			break;
#endif
