//Open input.h find:
[...]
	void		GuildDisband(const char* c_pData);
	void		GuildLadder(const char* c_pData);
	void		GuildWar(const char* c_pData);
	void		GuildWarScore(const char* c_pData);
	void		GuildSkillUsableChange(const char* c_pData);
	void		GuildMoneyChange(const char* c_pData);
//add
#ifndef ENABLE_USE_MONEY_FROM_GUILD
	void		GuildWithdrawMoney(const char* c_pData);
#endif
