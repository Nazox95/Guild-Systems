//Open GuildManager.h add or replace if you have:
	void	DepositMoney(DWORD dwGuild, INT lGold);
#ifdef ENABLE_USE_MONEY_FROM_GUILD
	void	WithdrawMoney(DWORD dwGuild, INT lGold);
#else
	void	WithdrawMoney(CPeer* peer, DWORD dwGuild, INT lGold);
#endif

//Note: IF you have problems, add in all files:
#include "../../common/service.h"
#include "../../common/tables.h"
