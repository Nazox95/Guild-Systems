//Open cmd_general.cpp find:
ACMD(do_war)
{
	//³» ±æµå Á¤º¸¸¦ ¾ò¾î¿À°í
	CGuild * g = ch->GetGuild();

	if (!g)
		return;
[...]
//find this:
	DWORD gm_pid = g->GetMasterPID();

	//¸¶½ºÅÍÀÎÁö Ã¼Å©(±æÀüÀº ±æµåÀå¸¸ÀÌ °¡´É)
	if (gm_pid != ch->GetPlayerID())
	{
		ch->ChatPacket(CHAT_TYPE_INFO, "[LS;534]");
		return;
	}
//replace:
#ifdef ENABLE_COLEADER_WAR_PRIVILEGES
	DWORD leader_pid = g->GetMasterPID();
	DWORD cl_grades = g->GetMember(ch->GetPlayerID())->grade;
	bool bIsLeaderOnline = g->IsOnlineLeader();

	if (bIsLeaderOnline) {
		if ((leader_pid != ch->GetPlayerID()) && !(cl_grades <= 2)) {
			ch->ChatPacket(CHAT_TYPE_INFO, "[LS;534]");
			return;
		}
		else {
			if (cl_grades == 2) {
				ch->ChatPacket(CHAT_TYPE_INFO, "[LS;2028]");
				return;
			}
		}
	}
	else {
		if ((leader_pid != ch->GetPlayerID()) && !(cl_grades <= 2)) {
			ch->ChatPacket(CHAT_TYPE_INFO, "[LS;534]");
			return;
		}
		else {
			if (cl_grades == 2)
				ch->ChatPacket(CHAT_TYPE_INFO,  "[LS;2029]");
		}
	}
#else
	//±æµåÀÇ ¸¶½ºÅÍ ¾ÆÀÌµð¸¦ ¾ò¾î¿ÂµÚ
	DWORD gm_pid = g->GetMasterPID();

	//¸¶½ºÅÍÀÎÁö Ã¼Å©(±æÀüÀº ±æµåÀå¸¸ÀÌ °¡´É)
	if (gm_pid != ch->GetPlayerID())
	{
		ch->ChatPacket(CHAT_TYPE_INFO, "[LS;534]");
		return;
	}
#endif

//find:
	if (!g->CanStartWar(type))
	{
		// ±æµåÀüÀ» ÇÒ ¼ö ÀÖ´Â Á¶°ÇÀ» ¸¸Á·ÇÏÁö¾Ê´Â´Ù.
		if (g->GetLadderPoint() == 0)
		{
			[.-..]
		else
		{
			sys_log(0, "GuildWar.StartError.UNKNOWN_ERROR");
		}
		return;
	}

	// ÇÊµåÀü Ã¼Å©¸¸ ÇÏ°í ¼¼¼¼ÇÑ Ã¼Å©´Â »ó´ë¹æÀÌ ½Â³«ÇÒ¶§ ÇÑ´Ù.
	if (!opp_g->CanStartWar(GUILD_WAR_TYPE_FIELD))
		[...]
		return;
	}

	do
	{
//After do { replace below all with this:
//replace:
#ifdef ENABLE_COLEADER_WAR_PRIVILEGES
		if (bIsLeaderOnline) {
			if (g->GetMasterCharacter() != NULL)
				break;
		}
		else {
			if (g->GetMember(ch->GetPlayerID())->grade == 2)
				break;
		}

		ch->ChatPacket(CHAT_TYPE_INFO, "[LS;1048]");
#else
		if (g->GetMasterCharacter() != NULL)
			break;

		CCI *pCCI = P2P_MANAGER::instance().FindByPID(g->GetMasterPID());

		if (pCCI != NULL)
			break;

		ch->ChatPacket(CHAT_TYPE_INFO, "[LS;1317]");
#endif
		g->RequestRefuseWar(opp_g->GetID());
		return;

	} while (false);

	do
	{
#ifdef ENABLE_COLEADER_WAR_PRIVILEGES
		bool boppIsLeaderOnline = opp_g->IsOnlineLeader();

		if (boppIsLeaderOnline) {
			if (opp_g->GetMasterCharacter() != NULL)
				break;
		}
		else {
			if (opp_g->GetMember(ch->GetPlayerID())->grade == 2)
				break;
		}

		ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("Gildenmeister und CoLeader sind offline2"));
#else
		if (opp_g->GetMasterCharacter() != NULL)
			break;
		
		CCI *pCCI = P2P_MANAGER::instance().FindByPID(opp_g->GetMasterPID());
		
		if (pCCI != NULL)
			break;

		ch->ChatPacket(CHAT_TYPE_INFO, "[LS;1317]");
#endif
		g->RequestRefuseWar(opp_g->GetID());
		return;

	} while (false);

#ifdef ENABLE_NEW_WAR_OPTIONS
	g->RequestDeclareWar(opp_g->GetID(), type, flag, round, points, time);
#else
	g->RequestDeclareWar(opp_g->GetID(), type);
#endif
}

******Compare******
//You need have this:
	// ÇÊµåÀü Ã¼Å©¸¸ ÇÏ°í ¼¼¼¼ÇÑ Ã¼Å©´Â »ó´ë¹æÀÌ ½Â³«ÇÒ¶§ ÇÑ´Ù.
	if (!opp_g->CanStartWar(GUILD_WAR_TYPE_FIELD))
	{
		if (opp_g->GetLadderPoint() == 0)
			ch->ChatPacket(CHAT_TYPE_INFO, "[LS;544]");
		else if (opp_g->GetMemberCount() < GUILD_WAR_MIN_MEMBER_COUNT)
			ch->ChatPacket(CHAT_TYPE_INFO, "[LS;545]");
		return;
	}

	do
	{
#ifdef ENABLE_COLEADER_WAR_PRIVILEGES
		if (bIsLeaderOnline) {
			if (g->GetMasterCharacter() != NULL)
				break;
		}
		else {
			if (g->GetMember(ch->GetPlayerID())->grade == 2)
				break;
		}

		ch->ChatPacket(CHAT_TYPE_INFO, "[LS;1048]");
#else
		if (g->GetMasterCharacter() != NULL)
			break;

		CCI *pCCI = P2P_MANAGER::instance().FindByPID(g->GetMasterPID());

		if (pCCI != NULL)
			break;

		ch->ChatPacket(CHAT_TYPE_INFO, "[LS;1317]");
#endif
		g->RequestRefuseWar(opp_g->GetID());
		return;

	} while (false);

	do
	{
#ifdef ENABLE_COLEADER_WAR_PRIVILEGES
		bool boppIsLeaderOnline = opp_g->IsOnlineLeader();

		if (boppIsLeaderOnline) {
			if (opp_g->GetMasterCharacter() != NULL)
				break;
		}
		else {
			if (opp_g->GetMember(ch->GetPlayerID())->grade == 2)
				break;
		}

		ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("Gildenmeister und CoLeader sind offline2"));
#else
		if (opp_g->GetMasterCharacter() != NULL)
			break;
		
		CCI *pCCI = P2P_MANAGER::instance().FindByPID(opp_g->GetMasterPID());
		
		if (pCCI != NULL)
			break;

		ch->ChatPacket(CHAT_TYPE_INFO, "[LS;1317]");
#endif
		g->RequestRefuseWar(opp_g->GetID());
		return;

	} while (false);

#ifdef ENABLE_NEW_WAR_OPTIONS
	g->RequestDeclareWar(opp_g->GetID(), type, flag, round, points, time);
#else
	g->RequestDeclareWar(opp_g->GetID(), type);
#endif
}******
