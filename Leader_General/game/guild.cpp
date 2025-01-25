//Open guild.cpp and find:
DWORD CGuild::GetMemberPID(const std::string& strName)
{
	[...]
}
//Add after, this:
#ifdef ENABLE_SHOW_LIDER_AND_GENERAL_GUILD
BYTE CGuild::NewIsGuildGeneral(DWORD pid)
{
	for ( TGuildMemberContainer::iterator iter = m_member.begin(); iter != m_member.end(); iter++ )
	{
		if ( iter->first == pid )
			return iter->second.is_general;
	}
	return 0;
}

bool CGuild::IsCoLeader(DWORD pid)
{
	for ( TGuildMemberContainer::iterator iter = m_member.begin(); iter != m_member.end(); iter++ )
	{
		if ( iter->first == pid )
			if (iter->second.grade == GUILD_COLEADER_GRADE)
				return true;
			else
				return false;
	}

	return false;
}
#endif
