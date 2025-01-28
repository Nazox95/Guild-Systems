//Open PythonNetworkStreamPhaseGame.cpp find :
bool CPythonNetworkStream::SendPointResetPacket()
{
	PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "StartPointReset", Py_BuildValue("()"));
	return true;
}

//add before:
#ifdef ENABLE_GUILDBANK_LOG
void CPythonNetworkStream::GuildBankInfoOpen()
{
	PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "OpenGuildBankInfo", Py_BuildValue("()"));
}

bool CPythonNetworkStream::SendGuildBankInfoOpen()
{
	TPacketCGGuild GuildPacket{};
	GuildPacket.byHeader = HEADER_CG_GUILD;
	GuildPacket.bySubHeader = GUILD_SUBHEADER_CG_REFRESH;
	if (!Send(sizeof(GuildPacket), &GuildPacket))
		return false;

	PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "GuildBankLogInfoRefresh", Py_BuildValue("()"));
	//Tracef(" SendGuildLogRefreshPacket\n");

	return SendSequence();
}
#endif

//Now find:
bool CPythonNetworkStream::RecvGuild()
{
//add in the end with the others 'CASE':
#ifdef ENABLE_GUILDBANK_LOG
		case GUILD_SUBHEADER_GC_BANK_DELETE:
		{
			CPythonGuild::Instance().ClearBankLog();
			//TraceError("Clear bank log recv");
			break;
		}

		case GUILD_SUBHEADER_GC_BANK_INFO:
		{
			char szName[24];
			char szItemName[24];
			int itemAction;
			int itemCount;
			int datatype;
			//if (!Recv(sizeof(index), &index))
			//	return false;

			if (!Recv(sizeof(szName), &szName))
				return false;

			if (!Recv(sizeof(szItemName), &szItemName))
				return false;

			if (!Recv(sizeof(itemAction), &itemAction))
				return false;

			if (!Recv(sizeof(itemCount), &itemCount))
				return false;

			if (!Recv(sizeof(datatype), &datatype))
				return false;

			CPythonGuild::Instance().SetGuildBankLogs(szName, szItemName, itemAction, itemCount, datatype);
			PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "GuildBankLogInfoRefresh", Py_BuildValue("()"));
			CPythonGuild::Instance().IncreaseBankLog();

			__RefreshGuildWindowInfoPage();
			//TraceError("GUILD_SUBHEADER_GC_BANK_INFO received %s\n", szItemName);
			break;
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
#ifdef ENABLE_GUILDBANK_LOG
		case GUILD_SUBHEADER_GC_BANK_DELETE:
		{
			CPythonGuild::Instance().ClearBankLog();
			//TraceError("Clear bank log recv");
			break;
		}

		case GUILD_SUBHEADER_GC_BANK_INFO:
		{
			char szName[24];
			char szItemName[24];
			int itemAction;
			int itemCount;
			int datatype;
			//if (!Recv(sizeof(index), &index))
			//	return false;

			if (!Recv(sizeof(szName), &szName))
				return false;

			if (!Recv(sizeof(szItemName), &szItemName))
				return false;

			if (!Recv(sizeof(itemAction), &itemAction))
				return false;

			if (!Recv(sizeof(itemCount), &itemCount))
				return false;

			if (!Recv(sizeof(datatype), &datatype))
				return false;

			CPythonGuild::Instance().SetGuildBankLogs(szName, szItemName, itemAction, itemCount, datatype);
			PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "GuildBankLogInfoRefresh", Py_BuildValue("()"));
			CPythonGuild::Instance().IncreaseBankLog();

			__RefreshGuildWindowInfoPage();
			//TraceError("GUILD_SUBHEADER_GC_BANK_INFO received %s\n", szItemName);
			break;
		}
#endif
[...]
