//Open Guild.cpp find and replace:
void CGuild::LoadGuildData(SQLMsg* pmsg)
{
	if (pmsg->Get()->uiNumRows == 0)
	{
		sys_err("Query failed: getting guild data %s", pmsg->stQuery.c_str());
		return;
	}

	MYSQL_ROW row = mysql_fetch_row(pmsg->Get()->pSQLResult);
	m_data.master_pid = strtoul(row[0], (char **)NULL, 10);
	m_data.level = (BYTE)strtoul(row[1], (char **)NULL, 10);
	m_data.exp = strtoul(row[2], (char **)NULL, 10);
	strlcpy(m_data.name, row[3], sizeof(m_data.name));

	m_data.skill_point = (BYTE) strtoul(row[4], (char **) NULL, 10);
	if (row[5])
		thecore_memcpy(m_data.abySkill, row[5], sizeof(BYTE) * GUILD_SKILL_COUNT);
	else
		memset(m_data.abySkill, 0, sizeof(BYTE) * GUILD_SKILL_COUNT);

	m_data.power = MAX(0, strtoul(row[6], (char **) NULL, 10));

	str_to_number(m_data.ladder_point, row[7]);

	if (m_data.ladder_point < 0)
		m_data.ladder_point = 0;

	str_to_number(m_data.win, row[8]);
	str_to_number(m_data.draw, row[9]);
	str_to_number(m_data.loss, row[10]);
	str_to_number(m_data.gold, row[11]);
#ifdef ENABLE_GUILD_WAR_SCORE
	for (int w = 0; w < 3; ++w)
		str_to_number(m_data.winTypes[w], row[12+w]);
	for (int d = 0; d < 3; ++d)
		str_to_number(m_data.drawTypes[d], row[15+d]);
	for (int l = 0; l < 3; ++l)
		str_to_number(m_data.lossType[l], row[18+l]);
#endif

	ComputeGuildPoints();
}

//Find and replace:
void CGuild::Load(DWORD guild_id)
{
	Initialize();

	m_data.guild_id = guild_id;

	DBManager::instance().FuncQuery(std::bind(&CGuild::LoadGuildData, this, std::placeholders::_1),
			"SELECT master, level, exp, name, skill_point, skill, sp, ladder_point, win, draw, loss, gold"
#ifdef ENABLE_GUILD_WAR_SCORE
			", wintype0, wintype1, wintype2, drawtype0, drawtype1, drawtype2, losstype0, losstype1, losstype2"
#endif
			" FROM guild%s WHERE id = %u", get_table_postfix(), m_data.guild_id);

//Find
void CGuild::SendGuildInfoPacket(LPCHARACTER ch)
{
	LPDESC d = ch->GetDesc();

	if (!d)
		return;

	TPacketGCGuild pack;
	pack.header = HEADER_GC_GUILD;
	pack.size = sizeof(TPacketGCGuild) + sizeof(TPacketGCGuildInfo);
	pack.subheader = GUILD_SUBHEADER_GC_INFO;
	[...]
	sys_log(0, "GMC guild_name %s", m_data.name);
	sys_log(0, "GMC master %d", m_data.master_pid);

	d->BufferedPacket(&pack, sizeof(TPacketGCGuild));
	d->Packet(&pack_sub, sizeof(TPacketGCGuildInfo));
//add
#ifdef ENABLE_GUILD_WAR_SCORE
	SetWarInfo();
#endif

//add in the end or before 
void CGuild::SetGuildDonateInfo()
//
#ifdef ENABLE_GUILD_WAR_SCORE
void CGuild::SetWarInfo()
{
	TPacketGCGuild p{};
	p.header = HEADER_GC_GUILD;
	p.size = sizeof(p) + sizeof(int);
	p.subheader = GUILD_SUBHEADER_GC_WAR_INFO;

	for (itertype(m_memberOnline) it = m_memberOnline.begin(); it != m_memberOnline.end(); ++it)
	{
		LPCHARACTER ch = *it;
		LPDESC d = ch->GetDesc();
		d->BufferedPacket(&p, sizeof(p));

		for (int i = 0; i < 3; ++i) {
			d->Packet(&m_data.winTypes[i], sizeof(int));
		}
		for (int i = 0; i < 3; ++i) {
			d->Packet(&m_data.lossType[i], sizeof(int));
		}
		for (int i = 0; i < 3; ++i) {
			d->Packet(&m_data.drawTypes[i], sizeof(int));
		}
		d->Packet(&m_data.ladder_point, sizeof(int));
		int rank = CGuildManager::Instance().GetRank(this);
		d->Packet(&rank, sizeof(int));
	}
}
#endif
