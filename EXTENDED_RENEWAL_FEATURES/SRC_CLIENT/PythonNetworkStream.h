//Open PythonNetworkStream.h find:
	public:
		CPythonNetworkStream();
		virtual ~CPythonNetworkStream();
		
		bool SendSpecial(int nLen, void * pvBuf);
		[...]
		// Guild
		bool SendGuildAddMemberPacket(DWORD dwVID);
		bool SendGuildRemoveMemberPacket(DWORD dwPID);
//add
#if defined(ENABLE_GUILDRENEWAL_SYSTEM) && defined(ENABLE_EXTENDED_RENEWAL_FEATURES)
		bool SendGuildVoteChangeMaster(DWORD dwPID);
		bool SendGuildVoteLandAbndon(int iVID);
#endif
		bool SendGuildChangeGradeNamePacket(BYTE byGradeNumber, const char * c_szName);
		[...]
