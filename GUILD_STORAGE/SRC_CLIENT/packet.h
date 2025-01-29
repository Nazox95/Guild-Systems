//Open packet.h find
	HEADER_CG_PARTY_REMOVE											= 74,
	HEADER_CG_PARTY_SET_STATE										= 75,
	HEADER_CG_PARTY_USE_SKILL										= 76,
	HEADER_CG_SAFEBOX_ITEM_MOVE										= 77,
	HEADER_CG_PARTY_PARAMETER										= 78,
	//HEADER_BLANK68												= 79,
	HEADER_CG_GUILD													= 80,
	HEADER_CG_ANSWER_MAKE_GUILD										= 81,
	HEADER_CG_FISHING												= 82,
	HEADER_CG_GIVE_ITEM												= 83,
//add
#ifdef ENABLE_GUILDSTORAGE_SYSTEM
	HEADER_CG_GUILDSTORAGE_CHECKIN									= 84,
	HEADER_CG_GUILDSTORAGE_CHECKOUT									= 85,
#endif

//find
	HEADER_GC_GUILD_SYMBOL_DATA										= 133,
	HEADER_GC_DIG_MOTION											= 134,
	HEADER_GC_DAMAGE_INFO											= 135,
	HEADER_GC_CHAR_ADDITIONAL_INFO									= 136,
	// SUPPORT_BGM
	HEADER_GC_MAIN_CHARACTER3_BGM									= 137,
	HEADER_GC_MAIN_CHARACTER4_BGM_VOL								= 138,
	// END_OF_SUPPORT_BGM
//add
#ifdef ENABLE_GUILDSTORAGE_SYSTEM
		HEADER_GC_GUILDSTORAGE_OPEN									= 141,
		HEADER_GC_GUILDSTORAGE_SET									= 142,
		HEADER_GC_GUILDSTORAGE_DEL									= 143,
#endif

//find
typedef struct command_mall_checkout
{
	BYTE		bHeader;
	BYTE		bMallPos;
	TItemPos	ItemPos;
} TPacketCGMallCheckout;
//add
#ifdef ENABLE_GUILDSTORAGE_SYSTEM
typedef struct command_guildstorage_checkin
{
	BYTE bHeader;
	BYTE bSafePos;
	TItemPos ItemPos;
} TPacketCGGuildstorageCheckin;

typedef struct command_guildstorage_checkout
{
	BYTE bHeader;
	BYTE bGuildstoragePos;
	TItemPos ItemPos;
} TPacketCGGuildstorageCheckout;
#endif

//find
typedef struct packet_guild_sub_info
{
	WORD member_count;
	WORD max_member_count;
	DWORD guild_id;
	DWORD master_pid;
	DWORD exp;
	BYTE level;
	char name[GUILD_NAME_MAX_LEN+1];
	DWORD gold;
	BYTE hasLand;
//add
#if defined(ENABLE_GUILDRENEWAL_SYSTEM) && defined(ENABLE_GUILDSTORAGE_SYSTEM)
	char goldCheckout[CHARACTER_NAME_MAX_LEN + 1];
	char itemCheckout[CHARACTER_NAME_MAX_LEN + 1];
#endif
} TPacketGCGuildInfo;

//find
typedef struct packet_mall_open
{
	BYTE bHeader;
	BYTE bSize;
} TPacketGCMallOpen;
//add
#ifdef ENABLE_GUILDSTORAGE_SYSTEM
typedef struct packet_guildstorage_open
{
	BYTE bHeader;
	BYTE bSize;
} TPacketGCGuildstorageOpen;
#endif
