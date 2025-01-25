//Open cmd.cpp add before command_info cmd_info[] =:
#ifdef ENABLE_GUILDWAR_BUTTON
ACMD(do_guildwar_request_enter);
#endif

//add with others functions in command_info cmd_info:
#ifdef ENABLE_GUILDWAR_BUTTON
	{ "guildwar_request_enter", 	do_guildwar_request_enter,	0,		POS_DEAD,	GM_PLAYER },
#endif
