//Open char.h find:
	protected:
		CGuild *		m_pGuild;
		DWORD			m_dwUnderGuildWarInfoMessageTime;
		CWarMap *		m_pWarMap;
//add
#ifdef ENABLE_GUILD_DONATE_ATTENDANCE
	public:
		int GetLastOfferNewExpTime() const noexcept { return m_dwLastOfferNewExpTime; }
		void SetLastOfferNewExpTime() noexcept { m_dwLastOfferNewExpTime = thecore_pulse(); }

	private:
		int m_dwLastOfferNewExpTime;
#endif
