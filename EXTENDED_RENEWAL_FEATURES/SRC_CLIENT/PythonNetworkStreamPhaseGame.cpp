//Open PythonNetorkStreamPhaseGame.cpp find:
bool CPythonNetworkStream::SendGuildRemoveMemberPacket(DWORD dwPID)
//After this function add:
#if defined(ENABLE_GUILDRENEWAL_SYSTEM) && defined(ENABLE_EXTENDED_RENEWAL_FEATURES)
bool CPythonNetworkStream::SendGuildVoteChangeMaster(DWORD dwPID)
{
	TPacketCGGuild GuildPacket{};
	GuildPacket.byHeader = HEADER_CG_GUILD;
	GuildPacket.bySubHeader = GUILD_SUBHEADER_CG_CHANGE_GUILDMASTER;
	if (!Send(sizeof(GuildPacket), &GuildPacket))
		return false;
	if (!Send(sizeof(dwPID), &dwPID))
		return false;

	Tracef(" SendGuildVoteChangeMaster %d\n", dwPID);
	return SendSequence();
}

bool CPythonNetworkStream::SendGuildVoteLandAbndon(int iVID)
{
	TPacketCGGuild GuildPacket{};
	GuildPacket.byHeader = HEADER_CG_GUILD;
	GuildPacket.bySubHeader = GUILD_SUBHEADER_CG_DELETE_LAND;
	if (!Send(sizeof(GuildPacket), &GuildPacket))
		return false;
	if (!Send(sizeof(iVID), &iVID))
		return false;

	Tracef(" SendGuildVoteLandAbndon %d\n", iVID);
	return SendSequence();
}
#endif
