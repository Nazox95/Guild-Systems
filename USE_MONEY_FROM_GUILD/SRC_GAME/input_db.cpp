//Open input_db.cpp:
//Note: Check if you have the function, if you have, replace, if you don't add:
//after this function:
void CInputDB::GuildMoneyChange(const char* c_pData)
//add
#ifndef ENABLE_USE_MONEY_FROM_GUILD
void CInputDB::GuildWithdrawMoney(const char* c_pData)
{
	const TPacketDGGuildMoneyWithdraw* p = (TPacketDGGuildMoneyWithdraw*)c_pData;

	CGuild* g = CGuildManager::Instance().TouchGuild(p->dwGuild);
	if (g)
		g->RecvWithdrawMoneyGive(p->iChangeGold);
}
#endif

//find:
[...]
	case HEADER_DG_CHANGE_GUILD_PRIV:
		ChangeGuildPriv(c_pData);
		break;

	case HEADER_DG_CHANGE_CHARACTER_PRIV:
		ChangeCharacterPriv(c_pData);
		break;

	case HEADER_DG_MONEY_LOG:
		MoneyLog(c_pData);
		break;
//add
#ifndef ENABLE_USE_MONEY_FROM_GUILD
	case HEADER_DG_GUILD_WITHDRAW_MONEY_GIVE:
		GuildWithdrawMoney(c_pData);
		break;
#endif
