//Open input.h find 
		void		Target(LPCHARACTER ch, const char * pcData);
		void		Warp(LPCHARACTER ch, const char * pcData);
//replace
#ifdef ENABLE_GUILDSTORAGE_SYSTEM
		void		SafeboxCheckin(LPCHARACTER ch, const char* c_pData, int bMall);
		void		SafeboxCheckout(LPCHARACTER ch, const char* c_pData, int bMall);
#else
		void		SafeboxCheckin(LPCHARACTER ch, const char * c_pData);
		void		SafeboxCheckout(LPCHARACTER ch, const char * c_pData, bool bMall);
#endif
//find 
	void		Boot(const char* data);
	void		QuestLoad(LPDESC d, const char * c_pData);
	void		SafeboxLoad(LPDESC d, const char * c_pData);
	void		SafeboxChangeSize(LPDESC d, const char * c_pData);
//add
#ifdef ENABLE_GUILDSTORAGE_SYSTEM
	void		GuildstorageChangeSize(LPDESC d, const char* c_pData);
#endif
//find
	void		SafeboxWrongPassword(LPDESC d);
	void		SafeboxChangePasswordAnswer(LPDESC d, const char* c_pData);
	void		MallLoad(LPDESC d, const char * c_pData);
//add
#ifdef ENABLE_GUILDSTORAGE_SYSTEM
	void		GuildstorageLoad(LPDESC d, const char* c_pData);
#endif
