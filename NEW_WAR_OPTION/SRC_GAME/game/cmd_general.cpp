//Open cmd_general.cpp find and replace
ACMD(do_war)
{
	//³» ±æµå Á¤º¸¸¦ ¾ò¾î¿À°í
	CGuild * g = ch->GetGuild();

	if (!g)
		return;

	//ÀüÀïÁßÀÎÁö Ã¼Å©ÇÑ¹ø!
	if (g->UnderAnyWar())
	{
		ch->ChatPacket(CHAT_TYPE_INFO, "[LS;533]");
		return;
	}

	//ÆÄ¶ó¸ÞÅÍ¸¦ µÎ¹è·Î ³ª´©°í
#ifdef ENABLE_NEW_WAR_OPTIONS
	char arg1[256], arg2[256], arg3[256], arg4[256], arg5[256], arg6[256];
	DWORD type = GUILD_WAR_TYPE_FIELD; //fixme102 base int modded uint
	DWORD flag = 0;
	DWORD round = 0;
	DWORD points = 0;
	DWORD time = 0;
	six_arguments(argument, arg1, sizeof(arg1), arg2, sizeof(arg2), arg3, sizeof(arg3), arg4, sizeof(arg4), arg5, sizeof(arg5), arg6, sizeof(arg6));
#else
	char arg1[256], arg2[256];
	int type = GUILD_WAR_TYPE_FIELD;
	two_arguments(argument, arg1, sizeof(arg1), arg2, sizeof(arg2));
#endif

	if (!*arg1)
		return;

	if (*arg2)
	{
		str_to_number(type, arg2);

		if(type < 0)
		{ // Fix
			ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("<error> can't declare war with type less than zero."));
			return;
		}

		if (type >= GUILD_WAR_TYPE_MAX_NUM)
			type = GUILD_WAR_TYPE_FIELD;
	}

#ifdef ENABLE_NEW_WAR_OPTIONS
	if (*arg3) {	//Banderas
		str_to_number(flag, arg3);
	}

	if (*arg4) {	//Rondas
		str_to_number(round, arg4);
	}

	if (*arg5) {	//Puntos
		str_to_number(points, arg5);
	}

	if (*arg6) {	//Tiempo
		str_to_number(time, arg6);
	}

	sys_err("do_war: type %d flag %d round %d points %d time %d", type, flag, round, points, time);
#endif

//Find
	if (!g->CanStartWar(type))
	{
		[...]
		if (g->GetLadderPoint() == 0)
		{
			ch->ChatPacket(CHAT_TYPE_INFO, "[LS;542]");
			sys_log(0, "GuildWar.StartError.NEED_LADDER_POINT");
		}
		else if (g->GetMemberCount() < GUILD_WAR_MIN_MEMBER_COUNT)
		{
			ch->ChatPacket(CHAT_TYPE_INFO, "[LS;543;%d]", GUILD_WAR_MIN_MEMBER_COUNT);
			sys_log(0, "GuildWar.StartError.NEED_MINIMUM_MEMBER[%d]", GUILD_WAR_MIN_MEMBER_COUNT);
		}
		else
		{
			sys_log(0, "GuildWar.StartError.UNKNOWN_ERROR");
		}
		return;
	}
	[...]

	do
	{
		[....]
		g->RequestRefuseWar(opp_g->GetID());
		return;

	} while (false);
//replace
#ifdef ENABLE_NEW_WAR_OPTIONS
	g->RequestDeclareWar(opp_g->GetID(), type, flag, round, points, time);
#else
	g->RequestDeclareWar(opp_g->GetID(), type);
#endif
}
