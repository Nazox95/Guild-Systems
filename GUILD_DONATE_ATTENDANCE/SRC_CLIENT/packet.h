//Open packet.h find
//////////////////////////////////////////////////////////////////////////
// Guild

enum
{
	GUILD_SUBHEADER_GC_LOGIN,
	GUILD_SUBHEADER_GC_LOGOUT,
[..]
	GUILD_SUBHEADER_GC_WAR_POINT,
	GUILD_SUBHEADER_GC_MONEY_CHANGE,
//add
#ifdef ENABLE_GUILD_DONATE_ATTENDANCE
	GUILD_SUBHEADER_GC_DONATE,
#endif
};
