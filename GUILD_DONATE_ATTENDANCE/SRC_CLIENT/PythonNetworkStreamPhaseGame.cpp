bool CPythonNetworkStream::SendPointResetPacket()
{
	PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "StartPointReset", Py_BuildValue("()"));
	return true;
}

//add before:
#ifdef ENABLE_GUILD_DONATE_ATTENDANCE
void CPythonNetworkStream::GuildDonateInfoOpen()
{
	PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "GuildDonateInfoRefresh", Py_BuildValue("()"));
}
#endif

//Now find :
bool CPythonNetworkStream::SendGuildOfferPacket(DWORD dwExperience)
{
	TPacketCGGuild GuildPacket;
	GuildPacket.byHeader = HEADER_CG_GUILD;
	GuildPacket.bySubHeader = GUILD_SUBHEADER_CG_OFFER;
	if (!Send(sizeof(GuildPacket), &GuildPacket))
		return false;
	if (!Send(sizeof(dwExperience), &dwExperience))
		return false;

	Tracef(" SendGuildOfferPacket %d\n", dwExperience);
	return SendSequence();
}

//Replace:
bool CPythonNetworkStream::SendGuildOfferPacket(DWORD dwExperience)
{
	TPacketCGGuild GuildPacket;
	GuildPacket.byHeader = HEADER_CG_GUILD;
	GuildPacket.bySubHeader = GUILD_SUBHEADER_CG_OFFER;
	if (!Send(sizeof(GuildPacket), &GuildPacket))
		return false;
	if (!Send(sizeof(dwExperience), &dwExperience))
		return false;

#ifdef ENABLE_GUILD_DONATE_ATTENDANCE
		PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "GuildDonateInfoRefresh", Py_BuildValue("()"));
#endif

	Tracef(" SendGuildOfferPacket %d\n", dwExperience);
	return SendSequence();
}

//Now find:
bool CPythonNetworkStream::RecvGuild()
{
//add in the end with the others 'CASE':
#ifdef ENABLE_GUILD_DONATE_ATTENDANCE
		case GUILD_SUBHEADER_GC_DONATE:
		{
		//	int medals;
			//if (!Recv(sizeof(medals), &medals))
				//return false;

			int count;
			if (!Recv(sizeof(count), &count))
				return false;

//			CPythonGuild::Instance().SetGuildDonateInfo(medals);
			CPythonGuild::Instance().SetGuilDonateCount(count);
			PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "GuildDonateInfoRefresh", Py_BuildValue("()"));
		}
#endif

//Ex:
[...]
		case GUILD_SUBHEADER_GC_GUILD_WAR_END_LIST:
		{
			DWORD dwSrcGuildID;
			DWORD dwDstGuildID;

			int iPacketSize = int(GuildPacket.size) - sizeof(GuildPacket);
			int nItemSize = sizeof(dwSrcGuildID) + sizeof(dwDstGuildID);

			assert(iPacketSize%nItemSize==0 && "GUILD_SUBHEADER_GC_GUILD_WAR_END_LIST");

			for (; iPacketSize > 0;)
			{
				
				if (!Recv(sizeof(dwSrcGuildID), &dwSrcGuildID))
					return false;
				
				if (!Recv(sizeof(dwDstGuildID), &dwDstGuildID))
					return false;

				Tracef(" >> GulidWarEndList [%d vs %d]\n", dwSrcGuildID, dwDstGuildID);
				CInstanceBase::RemoveGVGKey(dwSrcGuildID, dwDstGuildID);
				CPythonCharacterManager::Instance().ChangeGVG(dwSrcGuildID, dwDstGuildID);
				iPacketSize -= nItemSize;
			}
			break;
		}
#ifdef ENABLE_GUILD_DONATE_ATTENDANCE
		case GUILD_SUBHEADER_GC_DONATE:
		{
		//	int medals;
			//if (!Recv(sizeof(medals), &medals))
				//return false;

			int count;
			if (!Recv(sizeof(count), &count))
				return false;

//			CPythonGuild::Instance().SetGuildDonateInfo(medals);
			CPythonGuild::Instance().SetGuilDonateCount(count);
			PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "GuildDonateInfoRefresh", Py_BuildValue("()"));
		}
#endif
