//Open Guild.cpp find:
CGuild::CGuild(TGuildCreateParameter & cp)
{
	Initialize();
	m_general_count = 0;
	m_iMemberCountBonus = 0;
	strlcpy(m_data.name, cp.name, sizeof(m_data.name));
	m_data.master_pid = cp.master->GetPlayerID();
	[...]
//replace:
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

//Find:
void CGuild::ChangeMemberGrade(DWORD pid, BYTE grade)
{
	if (grade == 1)
		return;

//Add after:
#ifdef ENABLE_COLEADER_WAR_PRIVILEGES
	if (grade == 2) {
		char Query[1024];
		snprintf(Query, sizeof(Query), "SELECT COUNT(*) FROM guild_member WHERE guild_id=%d and grade=2", GetID());
		auto pmsg(DBManager::Instance().DirectQuery(Query));

		int count = 0;

		if (pmsg->Get()->uiNumRows == 0) {
			count = 0;
			sys_err("not found query");
		}
		else {
			MYSQL_ROW row = mysql_fetch_row(pmsg->Get()->pSQLResult);
			count = atoi(row[0]);
		}

		LPCHARACTER ch = GetMasterCharacter();
		if (count == 1) {
			ch->ChatPacket(CHAT_TYPE_INFO, "[LS;2030]");
			return;
		}
	}
#endif

//Find:
LPCHARACTER CGuild::GetMasterCharacter()
{ 
	return CHARACTER_MANAGER::instance().FindByPID(GetMasterPID()); 
}

//Add after:

#ifdef ENABLE_COLEADER_WAR_PRIVILEGES
bool CGuild::IsOnlineLeader()
{
	for (const auto& pkChr : m_memberOnline)
	{
		const auto& rkMember = GetMember(pkChr->GetPlayerID());
		if (rkMember && rkMember->grade == GUILD_LEADER_GRADE)
			return true;
	}

	for (const auto& dwPID : m_memberP2POnline)
	{
		const auto& rkMember = GetMember(dwPID);
		if (rkMember && rkMember->grade == GUILD_LEADER_GRADE)
			return true;
	}

	return false;
}
#endif
