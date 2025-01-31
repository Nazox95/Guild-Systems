	// Guild Money
		void		RequestDepositMoney(LPCHARACTER ch, int iGold);
#ifdef ENABLE_USE_MONEY_FROM_GUILD
		void		RequestWithdrawMoney(LPCHARACTER ch, int iGold, bool buildPrice = true);
#else
		void		RequestWithdrawMoney(LPCHARACTER ch, int iGold);
#endif

		void		RecvMoneyChange(int iGold);
#ifndef ENABLE_USE_MONEY_FROM_GUILD
		void		RecvWithdrawMoneyGive(int iChangeGold);
#endif

		int			GetGuildMoney() const noexcept { return m_data.gold; }
		void		SetGuildMoney(int gold) { m_data.gold = gold; }
