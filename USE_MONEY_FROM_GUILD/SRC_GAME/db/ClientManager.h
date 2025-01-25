//Open ClientManager.h add or replace if you have:
	void		GuildUseSkill(TPacketGuildUseSkill* p);
	void		GuildDepositMoney(TPacketGDGuildMoney* p);
#ifdef ENABLE_USE_MONEY_FROM_GUILD
	void		GuildWithdrawMoney(const TPacketGDGuildMoney* p);
#else
	void		GuildWithdrawMoney(CPeer* peer, const TPacketGDGuildMoney* p);
#endif
