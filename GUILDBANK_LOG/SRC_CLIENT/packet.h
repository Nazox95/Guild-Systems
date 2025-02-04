//Open packet.h find
//////////////////////////////////////////////////////////////////////////
// Guild

enum
{
	GUILD_SUBHEADER_CG_ADD_MEMBER,
	GUILD_SUBHEADER_CG_REMOVE_MEMBER,
	GUILD_SUBHEADER_CG_CHANGE_GRADE_NAME,
	[...]
	//add
#ifdef ENABLE_GUILDBANK_LOG
	GUILD_SUBHEADER_CG_REFRESH,
#endif
};

//Find:
enum
{
	GUILD_SUBHEADER_GC_LOGIN,
	GUILD_SUBHEADER_GC_LOGOUT,
	GUILD_SUBHEADER_GC_LIST,
	[...]
//add
#ifdef ENABLE_GUILDBANK_LOG
	GUILD_SUBHEADER_GC_BANK_INFO,
	GUILD_SUBHEADER_GC_BANK_DELETE,
#endif
};
