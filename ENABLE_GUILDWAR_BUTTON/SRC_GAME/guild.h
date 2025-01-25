//Open guild.h find:
		void		SendLogoutPacket(LPCHARACTER ch, DWORD pid);
		void		SendGuildInfoPacket(LPCHARACTER ch);
		void		SendGuildDataUpdateToAllMember(SQLMsg* pmsg);
//add
#ifdef ENABLE_GUILDWAR_BUTTON
		void		SendAllMembersButtonState(bool show);
#endif
