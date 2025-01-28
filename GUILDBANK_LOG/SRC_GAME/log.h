//Open log.h and add
#if defined(ENABLE_GUILDRENEWAL_SYSTEM) && defined(ENABLE_GUILDBANK_LOG)
		void GuildLog(LPCHARACTER ch, int guildID, DWORD vnum, const char* typeName, int iteminout, int bPrice, DWORD datatype);
#endif
