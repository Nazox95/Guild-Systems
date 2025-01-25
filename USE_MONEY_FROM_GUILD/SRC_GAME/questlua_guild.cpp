//Open questlua_guild.cpp add BEFORE:
void RegisterGuildFunctionTable()
//add BEFORE:
#ifdef ENABLE_USE_MONEY_FROM_GUILD
	int guild_money_in(lua_State* L)
	{
		if (!lua_isnumber(L, 1))
		{
			sys_err("QUEST : wrong argument");
			return 0;
		}

		int iGoldIn = (int)lua_tonumber(L, 1);

		if (iGoldIn <= 0)
		{
			sys_err("QUEST : gold amount less then zero");
			return 0;
		}

		LPCHARACTER ch = CQuestManager::instance().GetCurrentCharacterPtr();
		CGuild* pGuild = ch->GetGuild();

		if (!ch || !pGuild)
			return 0;

		if ((pGuild->GetGuildMoney() + iGoldIn) > (GOLD_MAX))
		{
			ch->ChatPacket(CHAT_TYPE_INFO, "[LS;1243]");
			return 0;
		}

		if (false == ch->CanDeposit())
		{
			ch->ChatPacket(CHAT_TYPE_INFO, "[LS;82]");
			return 0;
		}

		pGuild->RequestDepositMoney(ch, iGoldIn);
		ch->ChatPacket(CHAT_TYPE_INFO, "[LS;338;%d]", iGoldIn);

		return 0;
	}
	int guild_money_out(lua_State* L)
	{
		if (!lua_isnumber(L, 1))
		{
			sys_err("QUEST : wrong argument");
			return 0;
		}

		int iGoldOut = (int)lua_tonumber(L, 1);

		if (iGoldOut <= 0)
		{
			sys_err("QUEST : gold amount less then zero");
			return 0;
		}

		LPCHARACTER ch = CQuestManager::instance().GetCurrentCharacterPtr();
		CGuild* pGuild = ch->GetGuild();

		if (!ch || !pGuild)
			return 0;

		if ((ch->GetGold() + iGoldOut) > (GOLD_MAX))
		{
			ch->ChatPacket(CHAT_TYPE_INFO, "[LS;1243]");
			return 0;
		}

		if (false == ch->CanDeposit())
		{
			ch->ChatPacket(CHAT_TYPE_INFO, "[LS;82]");
			return 0;
		}

		pGuild->RequestWithdrawMoney(ch, iGoldOut);
		ch->ChatPacket(CHAT_TYPE_INFO, "[LS;1273;%d]", iGoldOut);

		return 0;
	}

	int guild_get_money0(lua_State* L)
	{
		LPCHARACTER ch = CQuestManager::Instance().GetCurrentCharacterPtr();

		CGuild* pGuild = ch->GetGuild();

		lua_pushnumber(L, (pGuild!=nullptr)?pGuild->GetGuildMoney():0);
		return 1;
	}
#endif

//Now add in 	void RegisterGuildFunctionTable():
#ifdef ENABLE_USE_MONEY_FROM_GUILD
			{ "money_in", guild_money_in },
			{ "money_out", guild_money_out },
			{ "get_money0",				guild_get_money0			},
#endif
