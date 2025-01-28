//Open PythonGuild.cpp and find:
void CPythonGuild::__Initialize()
{
	ZeroMemory(&m_GuildInfo, sizeof(m_GuildInfo));
	ZeroMemory(&m_GuildSkillData, sizeof(m_GuildSkillData));
	ZeroMemory(&m_adwEnemyGuildID, ENEMY_GUILD_SLOT_MAX_COUNT*sizeof(DWORD));
	m_GradeDataMap.clear();
	m_GuildMemberDataVector.clear();
	m_dwMemberLevelSummary = 0;
	m_dwMemberLevelAverage = 0;
	m_bGuildEnable = FALSE;
	m_GuildNameMap.clear();
//add
#ifdef ENABLE_GUILDBANK_LOG
	m_GuildInfo.pLogCount = 0;
#endif
}
//Add before
void initguild()
//
#ifdef ENABLE_GUILDBANK_LOG
PyObject* guildGetGuildBankInfoSize(PyObject* poSelf, PyObject* poArgs)
{
	CPythonGuild::TGuildInfo& rGuildInfo = CPythonGuild::Instance().GetGuildInfoRef();
	return Py_BuildValue("i", rGuildInfo.pLogCount);
}

PyObject* guildGetGuildBankInfoData(PyObject* poSelf, PyObject* poArgs)
{
	int index = 0;
	if (!PyTuple_GetInteger(poArgs, 0, &index))
		return Py_BuildException();

	if (index >= CPythonGuild::Instance().GetLogs().size())
		index = 0;

	return Py_BuildValue("ssiii", CPythonGuild::Instance().GetLogs()[index].szName, CPythonGuild::Instance().GetLogs()[index].szItemName, CPythonGuild::Instance().GetLogs()[index].itemAction, CPythonGuild::Instance().GetLogs()[index].itemCount, CPythonGuild::Instance().GetLogs()[index].datatype);
}
#endif
