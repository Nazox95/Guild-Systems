// after this function add
void CGuild::SkillLevelUp(DWORD dwVnum)
{
  [...]
}
#ifdef ENABLE_SKILL_FORGOT_BOOK
bool CGuild::SkillLevelDown(DWORD dwVnum)
{
	DWORD dwRealVnum = dwVnum - GUILD_SKILL_START;

	if (dwRealVnum >= GUILD_SKILL_COUNT)
		return false;

	if (m_data.abySkill[dwRealVnum] == 0)
		return false;

	m_data.abySkill[dwRealVnum]--; // this reduce level of skill.

	m_data.skill_point++; // This give 1 point to add in skill guild board page.
	ComputeGuildPoints();
	SaveSkill();
	SendDBSkillUpdate(0);

	std::for_each(m_memberOnline.begin(), m_memberOnline.end(), std::bind(&CGuild::SendSkillInfoPacket, this, std::placeholders::_1));

	sys_log(0, "Guild SkillDown: %s %d level %d type %u", GetName(), dwVnum, m_data.abySkill[dwRealVnum], CSkillManager::instance().Get(dwVnum)->dwType);

	return true;
}
#endif
