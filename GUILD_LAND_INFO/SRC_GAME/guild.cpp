//Open guild.cpp find:
void CGuild::SendGuildInfoPacket(LPCHARACTER ch)
{
	LPDESC d = ch->GetDesc();

	if (!d)
		return;
		[...]
	pack_sub.level	= m_data.level;
	strlcpy(pack_sub.name, m_data.name, sizeof(pack_sub.name));
	pack_sub.gold	= m_data.gold;
	pack_sub.has_land	= HasLand();

	sys_log(0, "GMC guild_name %s", m_data.name);
	sys_log(0, "GMC master %d", m_data.master_pid);

	d->BufferedPacket(&pack, sizeof(TPacketGCGuild));
	d->Packet(&pack_sub, sizeof(TPacketGCGuildInfo));
//add
#ifdef ENABLE_GUILD_LAND_INFO
	SetGuildLandInfo();
#endif

//Find:
#ifndef ENABLE_USE_MONEY_FROM_GUILD
void CGuild::RecvWithdrawMoneyGive(int iChangeGold)
{
	LPCHARACTER ch = GetMasterCharacter();

	if (ch) {
		ch->PointChange(POINT_GOLD, iChangeGold);
		sys_log(0, "GUILD: WITHDRAW %s:%u player %s[%u] gold %d", GetName(), GetID(), ch->GetName(), ch->GetPlayerID(), iChangeGold);
	}

	TPacketGDGuildMoneyWithdrawGiveReply p;
	p.dwGuild = GetID();
	p.iChangeGold = iChangeGold;
	p.bGiveSuccess = ch ? 1 : 0;
	db_clientdesc->DBPacket(HEADER_GD_GUILD_WITHDRAW_MONEY_GIVE_REPLY, 0, &p, sizeof(p));
}
#endif

//add after:
#ifdef ENABLE_GUILD_LAND_INFO
int CGuild::GetGuildLandIndex()
{
	auto pMsg(DBManager::Instance().DirectQuery("SELECT map_index FROM player.land WHERE guild_id = %d", GetID()));
	if (pMsg->Get()->uiNumRows == 0)
		return 0;

	MYSQL_ROW row = mysql_fetch_row(pMsg->Get()->pSQLResult);
	int maxIndex = 0;

	if (row[0] == 0)
		str_to_number(maxIndex, 0);
	else
		str_to_number(maxIndex, row[0]);

	sys_log(0, "GetGuildLandIndex: %u", maxIndex);
	return maxIndex;
}

int CGuild::GetGuildLandID()
{
	auto pMsg(DBManager::Instance().DirectQuery("SELECT id FROM player.land WHERE guild_id = %d", GetID()));
	if (pMsg->Get()->uiNumRows == 0)
		return 0;

	MYSQL_ROW row = mysql_fetch_row(pMsg->Get()->pSQLResult);
	int LandID = 0;

	if (row[0] == 0)
		str_to_number(LandID, 0);
	else
		str_to_number(LandID, row[0]);

	sys_log(0, "GetGuildLandID: %u", LandID);
	return LandID;
}

void CGuild::SetGuildLandInfo()
{
	TPacketGCGuild p{};
	p.header = HEADER_GC_GUILD;
	p.size = sizeof(p) + sizeof(int);
	p.subheader = GUILD_SUBHEADER_GC_LAND_INFO;

	std::vector<int> landAltars = { 14061, 14062, 14063 };
	std::vector<int> Alchemists = { 14043, 14045, 14046, 14047, 14048, 14049, 14050, 14051, 14052, 14053, 14054, 14055, 14074, 14075, 14076, 14077, 14078, 14079 };
	std::vector<int> Blacksmiths = { 14013, 14014, 14015 };
	
	auto pkMsg(DBManager::Instance().DirectQuery("SELECT vnum FROM player.object WHERE land_id = %d", GetGuildLandID()));

	MYSQL_ROW row = NULL;
	int guildAltar = 0;
	int guildAlchemist = 0;
	int guildBlacksmith = 0;
	while ((row = mysql_fetch_row(pkMsg->Get()->pSQLResult)))
	{
		int vnum = atoi(row[0]);

		std::vector<int>::iterator it = std::find(landAltars.begin(), landAltars.end(), vnum);
		if (it != landAltars.end())  {
			int pos = std::distance(landAltars.begin(), it);
			guildAltar=pos+1;
		}

		it = std::find(Alchemists.begin(), Alchemists.end(), vnum);
		if (it != Alchemists.end())  {
			int pos = std::distance(Alchemists.begin(), it);
			guildAlchemist=pos+1;
		}

		it = std::find(Blacksmiths.begin(), Blacksmiths.end(), vnum);
		if (it != Blacksmiths.end())  {
			int pos = std::distance(Blacksmiths.begin(), it);
			guildBlacksmith=pos+1;
		}
	}

	int index = GetGuildLandIndex();

	for (itertype(m_memberOnline) it = m_memberOnline.begin(); it != m_memberOnline.end(); ++it) {
		LPCHARACTER ch = *it;
		LPDESC d = ch->GetDesc();
		d->BufferedPacket(&p, sizeof(p));
		d->Packet(&index, sizeof(int));				//Baseinfo
		d->Packet(&guildAltar, sizeof(int));		//Nivel de Altar
		d->Packet(&guildAlchemist, sizeof(int));	//Alquimistas
		d->Packet(&guildBlacksmith, sizeof(int));	//Herreros de Gremio
		d->Packet(&m_data.guildstorage, sizeof(int));//Nivel de Almacén.
	}
}
#endif
