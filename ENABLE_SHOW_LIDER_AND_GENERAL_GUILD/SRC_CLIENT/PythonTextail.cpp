//Open PythonTextTail.cpp find and replace:
#ifdef ENABLE_SHOW_LIDER_AND_GENERAL_GUILD
void CPythonTextTail::RegisterCharacterTextTail(DWORD dwGuildID, BYTE dwNewIsGuildName, DWORD dwVirtualID, const D3DXCOLOR& c_rColor, float fAddHeight)
#else
void CPythonTextTail::RegisterCharacterTextTail(DWORD dwGuildID, DWORD dwVirtualID, const D3DXCOLOR& c_rColor, float fAddHeight)
#endif

//In the same function find:
		std::string strGuildName;
		if (!CPythonGuild::Instance().GetGuildName(dwGuildID, &strGuildName))
			strGuildName = "Noname";
//add
#ifdef ENABLE_SHOW_LIDER_AND_GENERAL_GUILD
		if (dwNewIsGuildName == 3)
			strGuildName.insert(0, ENABLE_SHOW_LIDER_AND_GENERAL_GUILD_VALUE1);
		else if (dwNewIsGuildName == 2)
			strGuildName.insert(0, ENABLE_SHOW_LIDER_AND_GENERAL_GUILD_VALUE2);
#endif
