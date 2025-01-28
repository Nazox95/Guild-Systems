//Open guild.cpp find
void CGuild::RequestDepositMoney(LPCHARACTER ch, int iGold)
[...]
	char buf[64+1];
	snprintf(buf, sizeof(buf), "%u %s", GetID(), GetName());
	LogManager::instance().CharLog(ch, iGold, "GUILD_DEPOSIT", buf);
//add
#if defined(ENABLE_GUILDRENEWAL_SYSTEM) && defined(ENABLE_GUILDBANK_EXTENDED_LOGS)
	LogManager::Instance().GuildLog(ch, ch->GetGuild()->GetID(), 0, "Yang", GUILD_GOLD_TYPE_IN, iGold, 1);
#endif
