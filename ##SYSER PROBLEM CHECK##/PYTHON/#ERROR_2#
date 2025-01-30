//If you have problem like:
mysql_query error: Field 'wintype0' doesn't have a default value
query: INSERT INTO guild(name, master, sp, level, exp, skill_point, skill, token) VALUES('Admins', 1, 1000, 1, 0, 0, '\0\0\0\0\0\0\0\0\0\0\0\0', 7403490252059772119)

//This  problem is because you have wrong values in row, the problems is from guild.cpp;

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
	str_to_number(m_data.gold, row[11]); <--GOLD
#ifdef ENABLE_GUILD_WAR_SCORE
	for (int w = 0; w < 3; ++w)
		str_to_number(m_data.winTypes[w], row[12+w]); <--12,13 & 14
	for (int d = 0; d < 3; ++d)
		str_to_number(m_data.drawTypes[d], row[15+d]); <--15,16 & 17
	for (int l = 0; l < 3; ++l)
		str_to_number(m_data.lossType[l], row[18+l]); <--18,19 & 20
#endif
#ifdef ENABLE_GUILDSTORAGE_SYSTEM
	str_to_number(m_data.guildstorage, row[21]);
	strlcpy(m_data.lastGold, row[22], sizeof(m_data.lastGold));
	strlcpy(m_data.lastItem, row[23], sizeof(m_data.lastItem));
	str_to_number(m_data.guildstoragestate, row[24]);
	str_to_number(m_data.guildstoragewho, row[25]);
#endif

	ComputeGuildPoints();
}

//So you need have the same values in mysql/guild.cpp and check position, from here, btw you here need have this:

void CGuild::Load(DWORD guild_id)
{
	Initialize();

	m_data.guild_id = guild_id;

	DBManager::instance().FuncQuery(std::bind(&CGuild::LoadGuildData, this, std::placeholders::_1),
			"SELECT master, level, exp, name, skill_point, skill, sp, ladder_point, win, draw, loss, gold"
#ifdef ENABLE_GUILD_WAR_SCORE
			", wintype0, wintype1, wintype2, drawtype0, drawtype1, drawtype2, losstype0, losstype1, losstype2"
#endif
#ifdef ENABLE_GUILDSTORAGE_SYSTEM
			", guildstorage, lastGold, lastItem, guildstoragestate, guildstoragewho"
#endif
			" FROM guild%s WHERE id = %u", get_table_postfix(), m_data.guild_id);

	sys_log(0, "GUILD: loading guild id %12s %u", m_data.name, guild_id);

	DBManager::instance().FuncQuery(std::bind(&CGuild::LoadGuildGradeData, this, std::placeholders::_1), 
			"SELECT grade, name, auth+0 FROM guild_grade%s WHERE guild_id = %u", get_table_postfix(), m_data.guild_id);

	DBManager::instance().FuncQuery(std::bind(&CGuild::LoadGuildMemberData, this, std::placeholders::_1), 
			"SELECT pid, grade, is_general, offer,"
#ifdef ENABLE_GUILD_DONATE_ATTENDANCE
			"UNIX_TIMESTAMP(join_date), donate_limit, UNIX_TIMESTAMP(last_donation), daily_donate_count, UNIX_TIMESTAMP(last_daily_donate), "
#endif
			" level, job, name FROM guild_member%s, player%s WHERE guild_id = %u and pid = id", get_table_postfix(), get_table_postfix(), guild_id);
}

and mysql check this photo (you need have in the same position of your [row]):
https://i.postimg.cc/xThCQ51m/1.png
