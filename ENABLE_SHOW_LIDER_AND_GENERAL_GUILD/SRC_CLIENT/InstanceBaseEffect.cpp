//Open InstanceBaseEffect.cpp find:
void CInstanceBase::AttachTextTail()
{
	[...]
//Replace:
#ifdef ENABLE_SHOW_LIDER_AND_GENERAL_GUILD
	CPythonTextTail::Instance().RegisterCharacterTextTail(m_dwGuildID, m_dwNewIsGuildName, dwVID, s_kD3DXClrTextTail, fTextTailHeight);
#else
	CPythonTextTail::Instance().RegisterCharacterTextTail(m_dwGuildID, dwVID, s_kD3DXClrTextTail, fTextTailHeight);
#endif
}
