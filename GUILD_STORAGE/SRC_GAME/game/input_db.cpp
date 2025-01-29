//Open input_db.cpp find 
	for (int i = 0; i < QUICKSLOT_MAX_NUM; ++i)
		ch->SetQuickslot(i, pTab->quickslot[i]);

	ch->PointsPacket();
	ch->SkillLevelPacket();

	sys_log(0, "InputDB: player_load %s %dx%dx%d LEVEL %d MOV_SPEED %d JOB %d ATG %d DFG %d GMLv %d",
			pTab->name, 
			ch->GetX(), ch->GetY(), ch->GetZ(),
			ch->GetLevel(),
			ch->GetPoint(POINT_MOV_SPEED),
			ch->GetJob(),
			ch->GetPoint(POINT_ATT_GRADE),
			ch->GetPoint(POINT_DEF_GRADE),
			ch->GetGMLevel());

	ch->QuerySafeboxSize();
//add
#ifdef ENABLE_GUILDSTORAGE_SYSTEM
	if (ch->GetGuild())
		ch->QueryGuildstorageSize();	//if core-crash, then delete [useless, just offical Code]
#endif

//find 
void CInputDB::SafeboxChangeSize(LPDESC d, const char * c_pData)
{
	if (!d)
		return;

	BYTE bSize = *(BYTE *) c_pData;

	if (!d->GetCharacter())
		return;

	d->GetCharacter()->ChangeSafeboxSize(bSize);
}
//add
#ifdef ENABLE_GUILDSTORAGE_SYSTEM
void CInputDB::GuildstorageChangeSize(LPDESC d, const char* c_pData)
{
	if (!d)
		return;

	BYTE bSize = *(BYTE*)c_pData;

	if (!d->GetCharacter())
		return;

	d->GetCharacter()->ChangeGuildstorageSize(bSize);
}
#endif

//find 
void CInputDB::MallLoad(LPDESC d, const char * c_pData)
{
	if (!d)
		return;

	TSafeboxTable * p = (TSafeboxTable *) c_pData;

	if (d->GetAccountTable().id != p->dwID)
	{
		sys_err("safebox has different id %u != %u", d->GetAccountTable().id, p->dwID);
		return;
	}

	if (!d->GetCharacter())
		return;

	d->GetCharacter()->LoadMall(p->wItemCount, (TPlayerItem *) (c_pData + sizeof(TSafeboxTable)));
}
//add
#ifdef ENABLE_GUILDSTORAGE_SYSTEM
void CInputDB::GuildstorageLoad(LPDESC d, const char* c_pData)
{
	if (!d)
		return;

	TSafeboxTable* p = (TSafeboxTable*)c_pData;

	//BYTE bSize = 1;

	LPCHARACTER ch = d->GetCharacter();
	if(!ch)
	{
		sys_err("no ch ptr");
		return;
	}

	DWORD gID = (ch->GetGuild() ? ch->GetGuild()->GetID() : 0);
	if (gID != p->dwID)
	{
		sys_err("Guildsafebox has different id %u != %u", gID, p->dwID);
		return;
	}

	//PREVENT_TRADE_WINDOW


	if (ch->GetExchange() || ch->IsCubeOpen() || ch->GetShopOwner() || ch->GetMyShop())
	{
		d->GetCharacter()->ChatPacket(CHAT_TYPE_INFO, "[LS;773]");
		d->GetCharacter()->CancelSafeboxLoad();
		return;
	}
	//END_PREVENT_TRADE_WINDOW

	BYTE bSize = ch->GetGuild()->GetGuildstorage();

	if (!d->GetCharacter())
		return;

	d->GetCharacter()->LoadGuildstorage(bSize * SAFEBOX_PAGE_SIZE, p->wItemCount, (TPlayerItem*)(c_pData + sizeof(TSafeboxTable)));
}
#endif

//find 
	case HEADER_DG_SAFEBOX_LOAD:
		SafeboxLoad(DESC_MANAGER::instance().FindByHandle(m_dwHandle), c_pData);
		break;

	case HEADER_DG_SAFEBOX_CHANGE_SIZE:
		SafeboxChangeSize(DESC_MANAGER::instance().FindByHandle(m_dwHandle), c_pData);
		break;
//add
#ifdef ENABLE_GUILDSTORAGE_SYSTEM
	case HEADER_DG_GUILDSTORAGE_CHANGE_SIZE:
		GuildstorageChangeSize(DESC_MANAGER::Instance().FindByHandle(m_dwHandle), c_pData);
		break;
#endif
//find 
	case HEADER_DG_SAFEBOX_CHANGE_PASSWORD_ANSWER:
		SafeboxChangePasswordAnswer(DESC_MANAGER::instance().FindByHandle(m_dwHandle), c_pData);
		break;

	case HEADER_DG_MALL_LOAD:
		MallLoad(DESC_MANAGER::instance().FindByHandle(m_dwHandle), c_pData);
		break;
//add
#ifdef ENABLE_GUILDSTORAGE_SYSTEM
		case HEADER_DG_GUILDSTORAGE_LOAD:
			GuildstorageLoad(DESC_MANAGER::Instance().FindByHandle(m_dwHandle), c_pData);
			break;
#endif
