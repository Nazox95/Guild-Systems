//Open PythonNetworkStreamPhaseGame.cpp find and replace 
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
