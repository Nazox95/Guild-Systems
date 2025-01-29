//Open PythonTextTail.h and replace:
#ifdef ENABLE_SHOW_LIDER_AND_GENERAL_GUILD
		void RegisterCharacterTextTail(DWORD dwGuildID, BYTE m_dwNewIsGuildName, DWORD dwVirtualID, const D3DXCOLOR& c_rColor, float fAddHeight = 10.0f);
#else
		void RegisterCharacterTextTail(DWORD dwGuildID, DWORD dwVirtualID, const D3DXCOLOR& c_rColor, float fAddHeight = 10.0f);
#endif
