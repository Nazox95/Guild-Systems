//Open guild.cpp find and replace
CGuild::CGuild(TGuildCreateParameter & cp)
{
	Initialize();
	m_general_count = 0;
	m_iMemberCountBonus = 0;
	strlcpy(m_data.name, cp.name, sizeof(m_data.name));
	m_data.master_pid = cp.master->GetPlayerID();
#ifdef ENABLE_GUILD_REQUEST
	m_data.empire = cp.master->GetEmpire();
#endif
	strlcpy(m_data.grade_array[0].grade_name, "[LS;927]", sizeof(m_data.grade_array[0].grade_name));
#ifdef ENABLE_GUILDRENEWAL_SYSTEM
	m_data.grade_array[0].auth_flag = GUILD_AUTH_ADD_MEMBER | GUILD_AUTH_REMOVE_MEMBER | GUILD_AUTH_NOTICE | GUILD_AUTH_USE_SKILL | GUILD_AUTH_WAR | GUILD_AUTH_BANK;
#else
	m_data.grade_array[0].auth_flag = GUILD_AUTH_ADD_MEMBER | GUILD_AUTH_REMOVE_MEMBER | GUILD_AUTH_NOTICE | GUILD_AUTH_USE_SKILL;
#endif

#ifdef ENABLE_COLEADER_WAR_PRIVILEGES
	strlcpy(m_data.grade_array[1].grade_name, "[LS;2020]", sizeof(m_data.grade_array[1].grade_name));
	for (int i = GUILD_COLEADER_GRADE; i < GUILD_GRADE_COUNT; ++i)
#else
	for (int i = GUILD_LEADER_GRADE; i < GUILD_GRADE_COUNT; ++i)
#endif
	{
		strlcpy(m_data.grade_array[i].grade_name, "[LS;928]", sizeof(m_data.grade_array[i].grade_name));
		m_data.grade_array[i].auth_flag = 0;
	}
