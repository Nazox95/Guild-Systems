//Open packet.h find:
enum
{
	GUILD_SUBHEADER_CG_ADD_MEMBER,
	GUILD_SUBHEADER_CG_REMOVE_MEMBER,
	[...]
	GUILD_SUBHEADER_CG_DEPOSIT_MONEY,
	GUILD_SUBHEADER_CG_WITHDRAW_MONEY,
//add
#if defined(ENABLE_GUILDRENEWAL_SYSTEM) && defined(ENABLE_EXTENDED_RENEWAL_FEATURES)
	GUILD_SUBHEADER_CG_CHANGE_GUILDMASTER,
	GUILD_SUBHEADER_CG_DELETE_LAND,
#endif
};
