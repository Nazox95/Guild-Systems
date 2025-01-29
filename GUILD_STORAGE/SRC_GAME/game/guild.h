//Open guild.h add 
#include "skill.h"
#if defined(ENABLE_GUILDRENEWAL_SYSTEM) && defined(ENABLE_GUILDSTORAGE_SYSTEM)
#define GS_ITEM 1
#define GS_GOLD 2
#endif
#ifdef ENABLE_GUILD_REQUEST
#include "packet.h"
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
	BYTE has_land;
//add
#if defined(ENABLE_GUILDRENEWAL_SYSTEM) && defined(ENABLE_GUILDSTORAGE_SYSTEM)
	char goldCheckout[CHARACTER_NAME_MAX_LEN + 1];
	char itemCheckout[CHARACTER_NAME_MAX_LEN + 1];
#endif
} TPacketGCGuildInfo;

//find 
typedef struct SGuildData
{
	DWORD	guild_id;
	DWORD	master_pid;
	DWORD	exp;
	BYTE	level;
	char	name[GUILD_NAME_MAX_LEN+1];

	TGuildGrade	grade_array[GUILD_GRADE_COUNT];

	BYTE	skill_point;
	BYTE	abySkill[GUILD_SKILL_COUNT];

	int		power;
	int		max_power;

	int		ladder_point;

	int		win;
	int		draw;
	int		loss;

	int		gold;
#ifdef ENABLE_GUILD_WAR_SCORE
	int winTypes[3];
	int drawTypes[3];
	int lossType[3];
#endif
//add
#ifdef ENABLE_GUILDSTORAGE_SYSTEM
	int guildstorage;
	char lastGold[CHARACTER_NAME_MAX_LEN + 1];
	char lastItem[CHARACTER_NAME_MAX_LEN + 1];
	int guildstoragestate;
	int guildstoragewho;
#endif
} TGuildData;

//find 
class CGuild
{
	public:
		CGuild(TGuildCreateParameter& cp);
		explicit CGuild(DWORD guild_id) { Load(guild_id); }
		~CGuild();

		DWORD		GetID() const	{ return m_data.guild_id; }
		const char*	GetName() const	{ return m_data.name; }
		int		GetSP() const		{ return m_data.power; }
		int		GetMaxSP() { return m_data.max_power; }
		DWORD		GetMasterPID() const	{ return m_data.master_pid; }
		LPCHARACTER	GetMasterCharacter();
#ifdef ENABLE_COLEADER_WAR_PRIVILEGES
		bool		IsOnlineLeader();
#endif
		BYTE		GetLevel() const		{ return m_data.level; }
//add
#ifdef ENABLE_GUILDSTORAGE_SYSTEM
		void SetStorageState(bool val, DWORD pid);
		bool IsStorageOpen() { return m_data.guildstoragestate; }
		DWORD GetStoragePid() { return m_data.guildstoragewho; }

		int GetGuildstorage() { return m_data.guildstorage; }
		void SetGuildstorage(int val);
#endif
#if defined(ENABLE_GUILDRENEWAL_SYSTEM) && defined(ENABLE_GUILDSTORAGE_SYSTEM)
		void RefreshP2P(CGuild* p);
		void SetLastCheckout(const char* szName, int type = -1);
		void SetLastCheckoutP2P(const char* szName, int type = -1);
		const char* GetLastCheckout(int type = -1);
#endif
		void		Reset() { m_data.power = m_data.max_power; }

//find 
		void		InviteDeny( DWORD dwPID );
		// END_OF_GUILD_JOIN_BUG_FIX

#if defined(ENABLE_GUILDRENEWAL_SYSTEM) && defined(ENABLE_EXTENDED_RENEWAL_FEATURES)
		int			GetGuildLandDeletePulse() const { return m_guildLandDeletePulse; }
		void		SetGuildLandDeletePulse(int landPulse) { m_guildLandDeletePulse = landPulse; }
		int			m_guildLandDeletePulse;
#endif

	private:
		void		Initialize();

		TGuildData	m_data;
		int		m_general_count;
//add
#ifdef ENABLE_GUILDSTORAGE_SYSTEM
		bool storageOpen;
		DWORD storagePidOpen;
#endif
