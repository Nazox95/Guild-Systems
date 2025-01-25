//Open guild.cpp find:
void CGuild::SendGuildDataUpdateToAllMember(SQLMsg* pmsg)
{
	TGuildMemberOnlineContainer::iterator iter = m_memberOnline.begin();

	for (; iter != m_memberOnline.end(); iter++ )
	{
		SendGuildInfoPacket(*iter);
		SendAllGradePacket(*iter);
	}
}
//add
#ifdef ENABLE_GUILDWAR_BUTTON
void CGuild::SendAllMembersButtonState(bool show)
{
	TGuildMemberOnlineContainer::iterator itOnline = m_memberOnline.begin();

	while (itOnline != m_memberOnline.end())
	{
		LPDESC d = (*(itOnline++))->GetDesc();

		if (!d || !d->GetCharacter())
			continue;

		d->GetCharacter()->SendWarTeleportButton(show);
	}
}
#endif
