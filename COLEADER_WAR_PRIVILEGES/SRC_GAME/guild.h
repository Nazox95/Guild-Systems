//Open Guild.h find:
class CGuild
{
	public:
		CGuild(TGuildCreateParameter& cp);
		explicit CGuild(DWORD guild_id) { Load(guild_id); }
		~CGuild();
		[...]
		DWORD		GetMasterPID() const	{ return m_data.master_pid; }
		LPCHARACTER	GetMasterCharacter();
//add
#ifdef ENABLE_COLEADER_WAR_PRIVILEGES
		bool		IsOnlineLeader();
#endif
