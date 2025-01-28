//Open PythonNetworkStreamPhaseGame.cpp find
		case GUILD_SUBHEADER_GC_MONEY_CHANGE:
//add after function
#ifdef ENABLE_GUILD_WAR_SCORE
		case GUILD_SUBHEADER_GC_WAR_INFO:
		{
			DWORD winTypes[3];
			DWORD drawTypes[3];
			DWORD lossTypes[3];
			DWORD ladderPoints;
			int rank;

			for (int i = 0; i < 3; ++i)
			{
				if (!Recv(sizeof(winTypes[i]), &winTypes[i]))
					return false;
			}
			for (int i = 0; i < 3; ++i)
			{
				if (!Recv(sizeof(lossTypes[i]), &lossTypes[i]))
					return false;
			}
			for (int i = 0; i < 3; ++i)
			{
				if (!Recv(sizeof(drawTypes[i]), &drawTypes[i]))
					return false;
			}

			if (!Recv(sizeof(ladderPoints), &ladderPoints))
				return false;
			if (!Recv(sizeof(rank), &rank))
				return false;

			CPythonGuild::Instance().SetGuildWarInfo(winTypes, lossTypes, drawTypes, ladderPoints, rank);
			PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "RefreshGuildWarInfoPage", Py_BuildValue("()"));
			__RefreshGuildWindowInfoPage();
			//Tracef(" >> Guild Money Change : %d\n", dwMoney);
			break;
		}
#endif
