	switch (SubHeader)
	{
		case GUILD_SUBHEADER_CG_DEPOSIT_MONEY:	//Einzahlen
			{
#ifndef ENABLE_GUILDRENEWAL_SYSTEM
				return SubPacketLen;
#endif
				const int gold = MIN(*reinterpret_cast<const int*>(c_pData), __deposit_limit());

				if (gold < 0)
				{
					ch->ChatPacket(CHAT_TYPE_INFO, "[LS;686]");
					return SubPacketLen;
				}

				if (ch->GetGold() < gold)
				{
					ch->ChatPacket(CHAT_TYPE_INFO, "[LS;687]");
					return SubPacketLen;
				}

#ifdef ENABLE_GUILDSTORAGE_SYSTEM
				if (gold > GOLD_MAX - 1) {	//Can't Put more than 2kkk into Guildstorage from your Pocket
					ch->ChatPacket(CHAT_TYPE_INFO, "[LS;2039]");
					return SubPacketLen;
				}

				if ((gold + pGuild->GetGuildMoney()) > (GOLD_MAX - 1)) {
					int gold_add = (GOLD_MAX - 1) - pGuild->GetGuildMoney();
					ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("GUILDSTORAGE_TOOK_INSTEAD %d"), gold_add);
					pGuild->RequestDepositMoney(ch, gold_add);
				}
				else
					pGuild->RequestDepositMoney(ch, gold);
#else
				pGuild->RequestDepositMoney(ch, gold);
#endif
			}
			return SubPacketLen;

		case GUILD_SUBHEADER_CG_WITHDRAW_MONEY:	//Auszahlen
			{
#ifndef ENABLE_GUILDRENEWAL_SYSTEM
				return SubPacketLen;
				const int gold = MIN(*reinterpret_cast<const int*>(c_pData), 500000);
#else
				const int gold = MIN(*reinterpret_cast<const int*>(c_pData), __deposit_limit());
#endif

				if (gold < 0) {
					ch->ChatPacket(CHAT_TYPE_INFO, "[LS;686]");
					return SubPacketLen;
				}

#ifdef ENABLE_GUILDSTORAGE_SYSTEM
				if (gold > GOLD_MAX) {
					ch->ChatPacket(CHAT_TYPE_INFO, "[LS;2040]");
					return SubPacketLen;
				}
				if (gold > pGuild->GetGuildMoney()) {	//Can't put out more than Money in Guildbank
					ch->ChatPacket(CHAT_TYPE_INFO, "[LS;2041]");
					return SubPacketLen;
				}

				if ((gold + ch->GetGold()) > (GOLD_MAX - 1)) {
					int gold_add = (GOLD_MAX - 1) - ch->GetGold();
					ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("GUILDSTORAGE_TOOK_INSTEAD %d"), gold_add);
					pGuild->RequestWithdrawMoney(ch, gold_add);
				}
				else
					pGuild->RequestWithdrawMoney(ch, gold);
#else
				pGuild->RequestWithdrawMoney(ch, gold);
#endif
			}
			return SubPacketLen;
