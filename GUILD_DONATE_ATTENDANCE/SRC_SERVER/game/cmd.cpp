//Open cmd.cpp add
#include "../../common/tables.h"
#include "../../common/service.h"

//add before 
struct command_info cmd_info[] =
//
#ifdef ENABLE_GUILD_DONATE_ATTENDANCE
ACMD(do_gdonate);
#endif

//add in
struct command_info cmd_info[] =
//
#ifdef ENABLE_GUILD_DONATE_ATTENDANCE
	{ "gdonate",	do_gdonate,	0,			POS_DEAD,	GM_PLAYER	},
#endif
