//Open PythonCharacterManager.cpp and find:
void CPythonCharacterManager::RefreshAllGuildMark()
{
	[...]
//replace:
#ifdef ENABLE_SHOW_LIDER_AND_GENERAL_GUILD
		pInstance->ChangeGuild(pInstance->GetGuildID(), pInstance->GetNewIsGuildName());
#else
		pInstance->ChangeGuild(pInstance->GetGuildID();
#endif
		pInstance->RefreshTextTail();
	}
}
