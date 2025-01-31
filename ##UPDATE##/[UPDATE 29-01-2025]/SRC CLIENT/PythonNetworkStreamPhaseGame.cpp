//Open PythonNetworkStreamPhaseGame.cpp find and replace
		case GUILD_SUBHEADER_GC_WAR:
		{
			TPacketGCGuildWar kGuildWar;
			if (!Recv(sizeof(kGuildWar), &kGuildWar))
				return false;

			switch (kGuildWar.bWarState)
			{
				case GUILD_WAR_SEND_DECLARE:
					Tracef(" >> GUILD_SUBHEADER_GC_WAR : GUILD_WAR_SEND_DECLARE\n");
					PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], 
						"BINARY_GuildWar_OnSendDeclare", 
						Py_BuildValue("(i)", kGuildWar.dwGuildOpp)
					);
					break;
				case GUILD_WAR_RECV_DECLARE:
					Tracef(" >> GUILD_SUBHEADER_GC_WAR : GUILD_WAR_RECV_DECLARE\n");
					PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], 
						"BINARY_GuildWar_OnRecvDeclare", 
#if defined(ENABLE_GUILDRENEWAL_SYSTEM) && defined(ENABLE_NEW_WAR_OPTIONS)
						Py_BuildValue("(iiiii)", kGuildWar.dwGuildOpp, kGuildWar.bType, kGuildWar.bRound, kGuildWar.bPoints, kGuildWar.dwTime));
#else
						Py_BuildValue("(ii)", kGuildWar.dwGuildOpp, kGuildWar.bType));
#endif
					break;
				case GUILD_WAR_ON_WAR:
					Tracef(" >> GUILD_SUBHEADER_GC_WAR : GUILD_WAR_ON_WAR : %d, %d\n", kGuildWar.dwGuildSelf, kGuildWar.dwGuildOpp);
					PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], 
						"BINARY_GuildWar_OnStart", 
						Py_BuildValue("(ii)", kGuildWar.dwGuildSelf, kGuildWar.dwGuildOpp)
					);
					CPythonGuild::Instance().StartGuildWar(kGuildWar.dwGuildOpp);
					break;
				case GUILD_WAR_END:
					Tracef(" >> GUILD_SUBHEADER_GC_WAR : GUILD_WAR_END\n");
					PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], 
						"BINARY_GuildWar_OnEnd", 
						Py_BuildValue("(ii)", kGuildWar.dwGuildSelf, kGuildWar.dwGuildOpp)
					);
					CPythonGuild::Instance().EndGuildWar(kGuildWar.dwGuildOpp);
					break;
			}
			break;
		}

//find and replace
		case GUILD_SUBHEADER_GC_WAR_POINT:
		{
			TPacketGuildWarPoint GuildWarPoint;
			if (!Recv(sizeof(GuildWarPoint), &GuildWarPoint))
				return false;

			PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME],
				"BINARY_GuildWar_OnRecvPoint",
#if defined(ENABLE_GUILDRENEWAL_SYSTEM)
				Py_BuildValue("(iii)", GuildWarPoint.dwGainGuildID, GuildWarPoint.dwOpponentGuildID, GuildWarPoint.lPoint)); // Enviar tres argumentos
#else
				Py_BuildValue("(iiii)", GuildWarPoint.dwGainGuildID, GuildWarPoint.dwOpponentGuildID, GuildWarPoint.lPoint, 0)); // Enviar cuatro argumentos
#endif
			break;
		}
		case GUILD_SUBHEADER_GC_MONEY_CHANGE:
		{
			DWORD dwMoney;
			if (!Recv(sizeof(dwMoney), &dwMoney))
				return false;

			CPythonGuild::Instance().SetGuildMoney(dwMoney);

			__RefreshGuildWindowInfoPage();
#ifdef ENABLE_GUILDRENEWAL_SYSTEM
			PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "RefreshGuildBaseInfoPageBankGold", Py_BuildValue("()"));
#endif
			Tracef(" >> Guild Money Change : %d\n", dwMoney);
			break;
		}
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
