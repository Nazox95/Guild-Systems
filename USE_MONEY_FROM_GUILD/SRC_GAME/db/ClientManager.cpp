//SOURCE DB -> Open ClientManager.cpp find:
//Note: If you have the function, replace if you don't, add:
void CClientManager::GuildDepositMoney(TPacketGDGuildMoney* p)
{
	CGuildManager::instance().DepositMoney(p->dwGuild, p->iGold);
}

#ifdef ENABLE_USE_MONEY_FROM_GUILD
void CClientManager::GuildWithdrawMoney(const TPacketGDGuildMoney* p)
{
	CGuildManager::Instance().WithdrawMoney(p->dwGuild, p->iGold);
}
#else
void CClientManager::GuildWithdrawMoney(CPeer* peer, const TPacketGDGuildMoney* p)
{
	CGuildManager::Instance().WithdrawMoney(peer, p->dwGuild, p->iGold);
}
#endif

//Find:
			case HEADER_GD_REQUEST_CHARACTER_PRIV:
				AddCharacterPriv((TPacketGiveCharacterPriv*) data);
				break;

			case HEADER_GD_MONEY_LOG:
				MoneyLog((TPacketMoneyLog*)data);
				break;

			case HEADER_GD_GUILD_DEPOSIT_MONEY:
				GuildDepositMoney((TPacketGDGuildMoney*)data);
				break;

//add or replace if you have:
			case HEADER_GD_GUILD_WITHDRAW_MONEY:
#ifdef ENABLE_USE_MONEY_FROM_GUILD
				GuildWithdrawMoney((TPacketGDGuildMoney*)data);
#else
				GuildWithdrawMoney(peer, (TPacketGDGuildMoney*)data);
#endif
				break;
