//Open cmd.cpp add 
#include "../../common/tables.h"
#include "../../common/service.h"

//add before 
struct command_info cmd_info[]
//
#ifdef ENABLE_GUILDSTORAGE_SYSTEM
ACMD(do_click_guildstorage);
ACMD(do_guildstorage_close);
ACMD(do_update_guildstorage);
#endif
//add inside 
struct command_info cmd_info[]
//
#ifdef ENABLE_GUILDSTORAGE_SYSTEM
	{ "click_guildstorage", do_click_guildstorage, 	0, POS_DEAD,		GM_PLAYER },
	{ "guildstorage_close", do_guildstorage_close, 	0, POS_DEAD,		GM_PLAYER },
	{ "buy_guildstorage", do_update_guildstorage, 	0, POS_DEAD,		GM_PLAYER },
#endif
