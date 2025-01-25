//Open GuildManager.cpp and replace if you have or add:
#ifdef ENABLE_USE_MONEY_FROM_GUILD
void CGuildManager::WithdrawMoney(DWORD dwGuild, INT iGold)
{
	if (iGold <= 0)
		return;

	const auto it = m_map_kGuild.find(dwGuild);

	if (it == m_map_kGuild.end())
	{
		sys_err("No guild by id %u", dwGuild);
		return;
	}

	it->second.gold -= iGold;
	sys_log(0, "GUILD: %u Withdraw %u Total %d", dwGuild, iGold, it->second.gold);

	MoneyChange(dwGuild, it->second.gold);
}
#else
void CGuildManager::WithdrawMoney(CPeer* peer, DWORD dwGuild, INT iGold)
{
	const auto it = m_map_kGuild.find(dwGuild);

	if (it == m_map_kGuild.end())
	{
		sys_err("No guild by id %u", dwGuild);
		return;
	}

	// If you have money, withdraw it and upload it
	if (it->second.gold >= iGold)
	{
		it->second.gold -= iGold;
		sys_log(0, "GUILD: %u Withdraw %d Total %d", dwGuild, iGold, it->second.gold);

		TPacketDGGuildMoneyWithdraw p{};
		p.dwGuild = dwGuild;
		p.iChangeGold = iGold;

		peer->EncodeHeader(HEADER_DG_GUILD_WITHDRAW_MONEY_GIVE, 0, sizeof(TPacketDGGuildMoneyWithdraw));
		peer->Encode(&p, sizeof(TPacketDGGuildMoneyWithdraw));
	}
}
#endif
