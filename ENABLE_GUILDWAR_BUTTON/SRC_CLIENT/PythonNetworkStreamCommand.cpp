//open PythonNetworkStreamCommand.cpp find and add like this:
	// CUEBE_END
	else if (!strcmpi(szCmd, "ObserverCount"))
	{
		if (2 != TokenVector.size())
		{
			TraceError("CPythonNetworkStream::ServerCommand(c_szCommand=%s) - Strange Parameter Count : %s", c_szCommand);
			return;
		}

		UINT uObserverCount= atoi(TokenVector[1].c_str());				

		PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], 
			"BINARY_BettingGuildWar_UpdateObserverCount", 
			Py_BuildValue("(i)", uObserverCount)
		);
	}
	else if (!strcmpi(szCmd, "ObserverMode"))
	{		
		if (2 != TokenVector.size())
		{
			TraceError("CPythonNetworkStream::ServerCommand(c_szCommand=%s) - Strange Parameter Count : %s", c_szCommand);
			return;
		}

		UINT uMode= atoi(TokenVector[1].c_str());
		
		IAbstractPlayer& rkPlayer=IAbstractPlayer::GetSingleton();
		rkPlayer.SetObserverMode(uMode ? true : false);

		PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME],
			"BINARY_BettingGuildWar_SetObserverMode",
#ifdef ENABLE_GUILDWAR_BUTTON
			Py_BuildValue("(ii)", uMode, uMode));
#else
			Py_BuildValue("(i)", uMode));
#endif
	}
	else if (!strcmpi(szCmd, "ObserverTeamInfo"))
	{		
	}
