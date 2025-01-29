//Open guild_manager.h find 
class CGuildManager : public singleton<CGuildManager>
{
	public:
		CGuildManager();
		virtual ~CGuildManager();

		DWORD		CreateGuild(TGuildCreateParameter& gcp);
		CGuild *	FindGuild(DWORD guild_id);
		CGuild *	FindGuildByName(const std::string guild_name);
		void		LoadGuild(DWORD guild_id);
		CGuild *	TouchGuild(DWORD guild_id);
		void		DisbandGuild(DWORD guild_id);

		void		Initialize();
//add
#ifdef ENABLE_GUILDSTORAGE_SYSTEM
		void InitializeDonate();
#endif
