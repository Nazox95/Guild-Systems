//Open PythonNetworkStream.h find in:
	public:
		CPythonNetworkStream();
		virtual ~CPythonNetworkStream();
		[...]
		void SetMarkServer(const char* c_szAddr, UINT uPort);
		void ConnectLoginServer(const char* c_szAddr, UINT uPort);
		void ConnectGameServer(UINT iChrSlot);

		void SetLoginInfo(const char* c_szID, const char* c_szPassword);
		void SetLoginKey(DWORD dwLoginKey);
		void ClearLoginInfo( void );
		[...]
		//add 
#ifdef ENABLE_GUILD_DONATE_ATTENDANCE
		void GuildDonateInfoOpen();
#endif
