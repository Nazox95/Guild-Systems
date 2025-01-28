//Open guild.cpp find
void CGuild::SendGuildInfoPacket(LPCHARACTER ch)
{
	[...]
	sys_log(0, "GMC guild_name %s", m_data.name);
	sys_log(0, "GMC master %d", m_data.master_pid);

	d->BufferedPacket(&pack, sizeof(TPacketGCGuild));
	d->Packet(&pack_sub, sizeof(TPacketGCGuildInfo));
//add
#ifdef ENABLE_GUILDBANK_LOG
	SetBankInfo();
#endif
}

//before
bool CGuild::HasLand()
//add
#ifdef ENABLE_GUILDBANK_LOG
void CGuild::SetBankInfo()
{
	for (itertype(m_memberOnline) it = m_memberOnline.begin(); it != m_memberOnline.end(); ++it)
	{
		LPCHARACTER ch = *it;
		LPDESC d = ch->GetDesc();

		TPacketGCGuild p_del{};
		p_del.header = HEADER_GC_GUILD;
		p_del.size = sizeof(p_del);
		p_del.subheader = GUILD_SUBHEADER_GC_BANK_DELETE;
		d->Packet(&p_del, sizeof(p_del));

		auto pkMsg(DBManager::Instance().DirectQuery("SELECT chrname,itemname,iteminout,itemcount,datatype FROM log.guildstorage WHERE guild_id = %d ORDER by time DESC", GetID()));

		MYSQL_ROW row = nullptr;
		while ((row = mysql_fetch_row(pkMsg->Get()->pSQLResult)))
		{
			char szName[24];
			strlcpy(szName, row[0], sizeof(szName));
			char szItemName[24];
			strlcpy(szItemName, row[1], sizeof(szItemName));

			int action = atoi(row[2]);
			int count = atoi(row[3]);
			int datatype = atoi(row[4]);

			TPacketGCGuild p{};
			p.header = HEADER_GC_GUILD;
			p.size = sizeof(p) + sizeof(szName) + sizeof(szItemName) + sizeof(action) + sizeof(count) + sizeof(datatype);
			p.subheader = GUILD_SUBHEADER_GC_BANK_INFO;

			TEMP_BUFFER buf;
			buf.write(&p, sizeof(p));
			buf.write(szName, sizeof(szName));
			buf.write(szItemName, sizeof(szItemName));
			buf.write(&action, sizeof(action));
			buf.write(&count, sizeof(count));
			buf.write(&datatype, sizeof(datatype));

			d->Packet(buf.read_peek(), buf.size());
		}
	}
}
#endif
