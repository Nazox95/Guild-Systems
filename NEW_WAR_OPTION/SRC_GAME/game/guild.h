//Open guild.h find
typedef struct SGuildWar
{
	DWORD war_start_time;
	DWORD score;
	DWORD state;
	BYTE type;
	//add
#ifdef ENABLE_NEW_WAR_OPTIONS
	BYTE round;
	BYTE points;
	BYTE time;
#endif
//find
	DWORD map_index;

	SGuildWar(BYTE type)
		: war_start_time(0),
		score(0),
		state(GUILD_WAR_RECV_DECLARE),
		type(type),
//add
#ifdef ENABLE_NEW_WAR_OPTIONS
		round(0),
		points(0),
		time(0),
#endif
		map_index(0)
	{
	}
	bool IsWarBegin() const
	{
		return state == GUILD_WAR_ON_WAR;
	}
} TGuildWar;

//find and replace 
		// War general
#ifdef ENABLE_NEW_WAR_OPTIONS
		void		GuildWarPacket(DWORD guild_id, BYTE bWarType, BYTE bWarState, BYTE bRound, BYTE bPoints, BYTE bTime);
#else
		void		GuildWarPacket(DWORD guild_id, BYTE bWarType, BYTE bWarState);
#endif

//find
		// War map relative
		void		SetGuildWarMapIndex(DWORD dwGuildID, long lMapIndex);
		int			GetGuildWarType(DWORD dwGuildOpponent);
		DWORD		GetGuildWarMapIndex(DWORD dwGuildOpponent);
//add
#ifdef ENABLE_NEW_WAR_OPTIONS
		int			GetGuildWarSettingRound(DWORD dwOppGID);
		int			GetGuildWarSettingPoints(DWORD dwOppGID);
		int			GetGuildWarSettingTime(DWORD dwOppGID);
#endif
//find
		// War entry question
		void		GuildWarEntryAsk(DWORD guild_opp);
		void		GuildWarEntryAccept(DWORD guild_opp, LPCHARACTER ch);

		// War state relative
		void		NotifyGuildMaster(const char* msg);
//replace
#ifdef ENABLE_NEW_WAR_OPTIONS
		void		RequestDeclareWar(DWORD guild_id, BYTE type, BYTE flag, BYTE round, BYTE points, DWORD time);
#else
		void		RequestDeclareWar(DWORD guild_id, BYTE type);
#endif
		void		RequestRefuseWar(DWORD guild_id); 
//replace too
#ifdef ENABLE_NEW_WAR_OPTIONS
		bool		DeclareWar(DWORD guild_id, BYTE type, BYTE state, BYTE round, BYTE points, BYTE time);
#else
		bool		DeclareWar(DWORD guild_id, BYTE type, BYTE state); 
#endif
		void		RefuseWar(DWORD guild_id); 
