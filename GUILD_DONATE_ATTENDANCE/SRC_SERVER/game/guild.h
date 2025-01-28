//open Guild.h and replace:
typedef struct SGuildMember
{
	DWORD pid; // player Å×ÀÌºíÀÇ id; primary key
	BYTE grade; // ±æµå»óÀÇ ÇÃ·¹ÀÌ¾îÀÇ °è±Þ 1 to 15 (1ÀÌ Â¯)
	BYTE is_general;
	BYTE job;
	BYTE level;
	DWORD offer_exp; // °øÇåÇÑ °æÇèÄ¡
	BYTE _dummy;

	std::string name;
#ifdef ENABLE_GUILD_DONATE_ATTENDANCE
	DWORD join_date;			// Time Check
	BYTE donate_limit;		// Exp-Donateboard -> 0/3 Limit
	DWORD last_donation;		// Time Check
	BYTE daily_donate_count;	// DonationCount
	DWORD last_daily_donate;	// Lock/Unlock
#endif
	SGuildMember(LPCHARACTER ch, BYTE grade, DWORD offer_exp
#ifdef ENABLE_GUILD_DONATE_ATTENDANCE
		, DWORD join_date, BYTE donate_limit, DWORD last_donation, BYTE daily_donate_count, DWORD last_daily_donate
#endif
	);
	SGuildMember(DWORD pid, BYTE grade, BYTE is_general, BYTE job, BYTE level, DWORD offer_exp, char* name
#ifdef ENABLE_GUILD_DONATE_ATTENDANCE
		, DWORD join_date, BYTE donate_limit, DWORD last_donation, BYTE daily_donate_count, DWORD last_daily_donate
#endif
	);
} TGuildMember;

//Find:
bool		OfferExp(LPCHARACTER ch, int amount);
//add
#ifdef ENABLE_GUILD_DONATE_ATTENDANCE
		bool		OfferExpNew(LPCHARACTER ch, int amount);
#endif
//Find and replace
		void		LevelChange(DWORD pid, BYTE level);
		void		ChangeMemberData(DWORD pid, DWORD offer, BYTE level, BYTE grade
#ifdef ENABLE_GUILD_DONATE_ATTENDANCE
					, DWORD join_date, BYTE donate_limit, DWORD last_donation, BYTE daily_donate_count, DWORD last_daily_donate
#endif
		);

//Find:
		int			GetGuildMoney() const noexcept { return m_data.gold; }
		void		SetGuildMoney(int gold) { m_data.gold = gold; }
//add
	// Guild Donate
#ifdef ENABLE_GUILD_DONATE_ATTENDANCE
		void SetGuildDonateInfo();
		DWORD GetMemberJoinDate(DWORD pid) noexcept;
		int GetGuildMemberDonateCount(DWORD pid) noexcept;
		DWORD GetMemberLastDonation(DWORD pid) noexcept;

		int GetDailyGuildDonatePoints(DWORD pid) noexcept;
		DWORD GetMemberLastDailyDonate(DWORD pid) noexcept;
		void SetGuildAttendanceState(DWORD pid, int donateCount, DWORD dwTime);
		void ResetGuildMemberDonateCount(DWORD pid);
#endif
