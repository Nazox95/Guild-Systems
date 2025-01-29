//Open guild.h and find:
typedef struct _SQLMsg SQLMsg;

enum
{
	GUILD_GRADE_NAME_MAX_LEN = 8,
	GUILD_GRADE_COUNT = 15,
	GUILD_COMMENT_MAX_COUNT = 12,
	GUILD_COMMENT_MAX_LEN = 50,
	GUILD_LEADER_GRADE = 1,
	GUILD_BASE_POWER = 400,
	GUILD_POWER_PER_SKILL_LEVEL = 200,
	GUILD_POWER_PER_LEVEL = 100,
	GUILD_MINIMUM_LEADERSHIP = 40, 
	GUILD_WAR_MIN_MEMBER_COUNT = 1, //Min 8 1 para testeo
	GUILD_LADDER_POINT_PER_LEVEL = 1000,
	GUILD_CREATE_ITEM_VNUM = 70101,
};

//Add after LEADER_GRADE:
GUILD_COLEADER_GRADE = 2,	// ENABLE_SHOW_GUILD_LEADER

//Now Find:
		int		GetMaxGeneralCount() const	{ return 1 /*+ GetSkillLevel(GUILD_SKILL_DEUNGYONG)/3*/;}
		int		GetGeneralCount() const		{ return m_general_count; }

		TGuildMember*	GetMember(DWORD pid);
		DWORD			GetMemberPID(const std::string& strName);

//Add:
#ifdef ENABLE_SHOW_LIDER_AND_GENERAL_GUILD
		BYTE			NewIsGuildGeneral(DWORD pid);
		bool			IsCoLeader(DWORD pid);
#endif
