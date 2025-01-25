//Open guild.cpp and replace all function (don't worry for the others macros)
#ifdef ENABLE_USE_MONEY_FROM_GUILD
void CGuild::RequestWithdrawMoney(LPCHARACTER ch, int iGold, bool buildPrice)
#else
void CGuild::RequestWithdrawMoney(LPCHARACTER ch, int iGold)
#endif
{
	if (!ch)
		return;

	if (!ch->CanDeposit())
	{
		ch->ChatPacket(CHAT_TYPE_INFO, "[LS;82]");
		return;
	}

#ifndef ENABLE_GUILDSTORAGE_SYSTEM
	if (ch->GetPlayerID() != GetMasterPID())
	{
		ch->ChatPacket(CHAT_TYPE_INFO, "[LS;939]");
		return;
	}
#endif

	if (m_data.gold < iGold)
	{
		ch->ChatPacket(CHAT_TYPE_INFO, "[LS;687]");
		return;
	}

#ifdef ENABLE_GROWTH_PET_SYSTEM
	CGrowthPetSystem* petSystem = ch->GetGrowthPetSystem();
	if (petSystem && petSystem->IsActivePet())
	{
		ch->ChatPacket(CHAT_TYPE_INFO, "[LS;151]");
		return;
	}
#endif

#if defined(ENABLE_GUILDRENEWAL_SYSTEM) && defined(ENABLE_USE_MONEY_FROM_GUILD)
	if (buildPrice)
	{
		int iChangeGoldTax = iGold;
		if (GetLevel() < 20) { // Guild [Bonus 4]
			DWORD dwTax = 0;
			int iVal = 15;

			dwTax = iChangeGoldTax * iVal / 100;
			iChangeGoldTax -= dwTax;
		}

		ch->PointChange(POINT_GOLD, iChangeGoldTax);
		//if (test_server)
		{
			ch->ChatPacket(CHAT_TYPE_INFO, "[LS;2034;%d;%d]", iGold, iChangeGoldTax);
		}
	}
#endif

#if defined(ENABLE_GUILDRENEWAL_SYSTEM) && defined(ENABLE_GUILDSTORAGE_SYSTEM)
	SetLastCheckout(ch->GetName(), GS_GOLD);
	SetLastCheckoutP2P(ch->GetName(), GS_GOLD);
	SendGuildInfoPacket(ch);
	TPacketGGGuild p1{};
	TPacketGGGuildChat p2{};

	p1.bHeader = HEADER_GG_GUILD;
	p1.bSubHeader = GUILD_SUBHEADER_GG_REFRESH;
	p1.dwGuild = GetID();
	strlcpy(p2.szText, "none", sizeof(p2.szText));

	P2P_MANAGER::Instance().Send(&p1, sizeof(TPacketGGGuild));
	P2P_MANAGER::Instance().Send(&p2, sizeof(TPacketGGGuildChat));
#endif

	TPacketGDGuildMoney p{};
	p.dwGuild = GetID();
	p.iGold = iGold;
	db_clientdesc->DBPacket(HEADER_GD_GUILD_WITHDRAW_MONEY, 0, &p, sizeof(p));

#if defined(ENABLE_GUILDRENEWAL_SYSTEM) && defined(ENABLE_USE_MONEY_FROM_GUILD)
	char buf[64 + 1];
	snprintf(buf, sizeof(buf), "%u %s", GetID(), GetName());
	LogManager::Instance().CharLog(ch, iGold, "GUILD_WITHDRAW", buf);
#endif

#if defined(ENABLE_GUILDRENEWAL_SYSTEM) && defined(ENABLE_GUILDBANK_EXTENDED_LOGS)
#	ifdef ENABLE_USE_MONEY_FROM_GUILD
	if (buildPrice)
#	endif
	{
		LogManager::Instance().GuildLog(ch, ch->GetGuild()->GetID(), 0, "Yang", GUILD_GOLD_TYPE_OUT, iGold, 1);
	}
#endif

	ch->UpdateDepositPulse();
	sys_log(0, "GUILD: WITHDRAW %s:%u player %s[%u] gold %d", GetName(), GetID(), ch->GetName(), ch->GetPlayerID(), iGold);
}

//Find and replace:
#ifndef ENABLE_USE_MONEY_FROM_GUILD
void CGuild::RecvWithdrawMoneyGive(int iChangeGold)
{
	LPCHARACTER ch = GetMasterCharacter();

	if (ch) {
		ch->PointChange(POINT_GOLD, iChangeGold);
		sys_log(0, "GUILD: WITHDRAW %s:%u player %s[%u] gold %d", GetName(), GetID(), ch->GetName(), ch->GetPlayerID(), iChangeGold);
	}

	TPacketGDGuildMoneyWithdrawGiveReply p;
	p.dwGuild = GetID();
	p.iChangeGold = iChangeGold;
	p.bGiveSuccess = ch ? 1 : 0;
	db_clientdesc->DBPacket(HEADER_GD_GUILD_WITHDRAW_MONEY_GIVE_REPLY, 0, &p, sizeof(p));
}
#endif
