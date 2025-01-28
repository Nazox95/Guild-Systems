//Open common->tables add
#include "length.h"
#include "service.h"
#include "item_length.h"

//find and replace
typedef struct SPacketGuildChangeMemberData
{
	DWORD guild_id;
	DWORD pid;
	DWORD offer;
	BYTE level;
	BYTE grade;
#ifdef ENABLE_GUILD_DONATE_ATTENDANCE
	DWORD join_date;
	BYTE donate_limit;
	DWORD last_donation;
	BYTE daily_donate_count;
	DWORD last_daily_donate;
#endif
} TPacketGuildChangeMemberData;

//find and replace
typedef struct SPacketDGGuildMember
{
	DWORD	dwPID;
	DWORD	dwGuild;
	BYTE	bGrade;
	BYTE	isGeneral;
	BYTE	bJob;
	BYTE	bLevel;
	DWORD	dwOffer;
	char	szName[CHARACTER_NAME_MAX_LEN + 1];
#ifdef ENABLE_GUILD_DONATE_ATTENDANCE
	DWORD dwJoinDate;
	BYTE bDonateLimit;
	DWORD dwLastDonation;
	BYTE bDailyDonateCount;
	DWORD dwLastDailyDonate;
#endif
} TPacketDGGuildMember;
