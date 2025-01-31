void CGuild::RequestDepositMoney(LPCHARACTER ch, int iGold)
{
	if (false==ch->CanDeposit())
	{
		ch->ChatPacket(CHAT_TYPE_INFO, "[LS;994]");
		return;
	}

	if (ch->GetGold() < iGold)
		return;


	ch->PointChange(POINT_GOLD, -iGold);

	TPacketGDGuildMoney p;
	p.dwGuild = GetID();
	p.iGold = iGold;
	db_clientdesc->DBPacket(HEADER_GD_GUILD_DEPOSIT_MONEY, 0, &p, sizeof(p));

	char buf[64+1];
	snprintf(buf, sizeof(buf), "%u %s", GetID(), GetName());
	LogManager::instance().CharLog(ch, iGold, "GUILD_DEPOSIT", buf);
#if defined(ENABLE_GUILDRENEWAL_SYSTEM) && defined(ENABLE_GUILDBANK_EXTENDED_LOGS)
	LogManager::Instance().GuildLog(ch, ch->GetGuild()->GetID(), 0, "Yang", GUILD_GOLD_TYPE_IN, iGold, 1);
#endif

	ch->UpdateDepositPulse();
	sys_log(0, "GUILD: DEPOSIT %s:%u player %s[%u] gold %d", GetName(), GetID(), ch->GetName(), ch->GetPlayerID(), iGold);
}

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
		if (GetLevel() < 20) { // [Bonus 4]
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
