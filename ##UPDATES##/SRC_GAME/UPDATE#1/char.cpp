//[UPDATE 30/01/2025]
//Open char.cpp and add before:
bool CHARACTER::BuildUpdatePartyPacket(TPacketGCPartyUpdate & out)
{
  [...]
}

//add
#ifdef ENABLE_GUILDSTORAGE_SYSTEM
CSafebox* CHARACTER::GetGuildstorage() const
{
	return m_pkGuildstorage;
}

void CHARACTER::LoadGuildstorage(int iSize, int iItemCount, TPlayerItem* pItems)
{
	bool bLoaded = false;

	//PREVENT_TRADE_WINDOW
	SetOpenGuildstorage(true);
	//END_PREVENT_TRADE_WINDOW

	if (m_pkGuildstorage)
		bLoaded = true;

	if (!m_pkGuildstorage)
		m_pkGuildstorage = M2_NEW CSafebox(this, iSize, 0);
	else
		m_pkGuildstorage->ChangeSize(iSize);

	m_iGuildstorageSize = iSize;

	m_pkGuildstorage->SetWindowMode(GUILDBANK);

	TPacketGCGuildstorageOpen p{};

	p.bHeader = HEADER_GC_GUILDSTORAGE_OPEN;
	p.bSize = iSize;

	GetDesc()->Packet(&p, sizeof(TPacketGCGuildstorageOpen));

	if (!bLoaded)
	{
		for (int i = 0; i < iItemCount; ++i, ++pItems)
		{
			if (!m_pkGuildstorage->IsValidPosition(pItems->pos))
				continue;

			LPITEM item = ITEM_MANAGER::Instance().CreateItem(pItems->vnum, pItems->count, pItems->id);

			if (!item)
			{
				sys_err("cannot create item vnum %d id %u (name: %s)", pItems->vnum, pItems->id, GetName());
				continue;
			}

			item->SetSkipSave(true);
			item->SetSockets(pItems->alSockets);
			item->SetAttributes(pItems->aAttr);

			if (!m_pkGuildstorage->Add(pItems->pos, item))
				M2_DESTROY_ITEM(item);
			else
				item->SetSkipSave(false);
		}
	}
}

void CHARACTER::CloseGuildstorage()
{
	if (!m_pkGuildstorage)
		return;

	//PREVENT_TRADE_WINDOW
	SetOpenGuildstorage(false);
	GetGuild()->SetStorageState(false, 0);
	//END_PREVENT_TRADE_WINDOW

	m_pkGuildstorage->Save();

	M2_DELETE(m_pkGuildstorage);
	m_pkGuildstorage = nullptr;

	ChatPacket(CHAT_TYPE_COMMAND, "CloseGuildstorage");

	SetGuildstorageLoadTime();
	m_bOpeningGuildstorage = false;

	Save();
}
#endif
