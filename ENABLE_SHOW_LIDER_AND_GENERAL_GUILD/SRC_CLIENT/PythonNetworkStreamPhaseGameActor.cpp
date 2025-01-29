//Open PythonNetworkStreamPhaseGameActor.cpp and find:
bool CPythonNetworkStream::RecvCharacterAppendPacket()
{
	[...]
	kNetActorData.m_dwWeapon = 0;/*chrAddPacket.awPart[CHR_EQUIPPART_WEAPON]*/;
	kNetActorData.m_dwHair = 0;/*chrAddPacket.awPart[CHR_EQUIPPART_HAIR]*/;
	kNetActorData.m_dwMountVnum = 0;/*chrAddPacket.dwMountVnum*/;
//add
#ifdef ENABLE_SHOW_LIDER_AND_GENERAL_GUILD
	kNetActorData.m_dwNewIsGuildName = 0;
#endif
}

//find:
bool CPythonNetworkStream::RecvCharacterAdditionalInfo()
{
	[...]
		kNetActorData.m_dwHair = chrInfoPacket.awPart[CHR_EQUIPPART_HAIR];
		kNetActorData.m_dwMountVnum = chrInfoPacket.dwMountVnum;
//add
#ifdef ENABLE_SHOW_LIDER_AND_GENERAL_GUILD
		kNetActorData.m_dwNewIsGuildName = chrInfoPacket.dwNewIsGuildName;
#endif
}

//Find: (optional)
bool CPythonNetworkStream::RecvCharacterAppendPacketNew()
{
	[...]
	kNetActorData.m_dwVID = chrAddPacket.dwVID;
	kNetActorData.m_dwMountVnum = chrAddPacket.dwMountVnum;
//If you have this line, comment or remove:
//	kNetActorData.m_dwNewIsGuildName = chrAddPacket.dwNewIsGuildName;
	kNetActorData.m_fRot = chrAddPacket.angle;
}

//Find:
bool CPythonNetworkStream::RecvCharacterUpdatePacket()
{
	[...]

	kNetUpdateActorData.m_dwStateFlags = chrUpdatePacket.bStateFlag;
	kNetUpdateActorData.m_dwMountVnum = chrUpdatePacket.dwMountVnum;
//add
#ifdef ENABLE_SHOW_LIDER_AND_GENERAL_GUILD
	kNetUpdateActorData.m_dwNewIsGuildName = chrUpdatePacket.dwNewIsGuildName;
#endif
	__RecvCharacterUpdatePacket(&kNetUpdateActorData);

	return true;
}
