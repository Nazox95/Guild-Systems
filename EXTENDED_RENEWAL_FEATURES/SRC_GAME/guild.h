//Open guild.h find:
		void		Invite( LPCHARACTER pchInviter, LPCHARACTER pchInvitee );

		/// ±æµåÃÊ´ë¿¡ ´ëÇÑ »ó´ë character ÀÇ ¼ö¶ôÀ» Ã³¸®ÇÑ´Ù.
		/**
		 * @param	pchInvitee ÃÊ´ë¹ÞÀº character
		 *
		 * ±æµå¿¡ °¡ÀÔ°¡´ÉÇÑ »óÅÂ°¡ ¾Æ´Ï¶ó¸é ÇØ´çÇÏ´Â Ã¤ÆÃ ¸Þ¼¼Áö¸¦ Àü¼ÛÇÑ´Ù.
		 */
		void		InviteAccept( LPCHARACTER pchInvitee );

		/// ±æµåÃÊ´ë¿¡ ´ëÇÑ »ó´ë character ÀÇ °ÅºÎ¸¦ Ã³¸®ÇÑ´Ù.
		/**
		 * @param	dwPID ÃÊ´ë¹ÞÀº character ÀÇ PID
		 */
		void		InviteDeny( DWORD dwPID );
//Add:
#if defined(ENABLE_GUILDRENEWAL_SYSTEM) && defined(ENABLE_EXTENDED_RENEWAL_FEATURES)
		int			GetGuildLandDeletePulse() const { return m_guildLandDeletePulse; }
		void		SetGuildLandDeletePulse(int landPulse) { m_guildLandDeletePulse = landPulse; }
		int			m_guildLandDeletePulse;
#endif
