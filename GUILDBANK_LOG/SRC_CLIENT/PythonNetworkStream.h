//Open PythonNetworkStream.h find:
		// Mall
		bool RecvMallOpenPacket();
		bool RecvMallItemSetPacket();
		bool RecvMallItemDelPacket();
//add:
#ifdef ENABLE_GUILDBANK_LOG
		void GuildBankInfoOpen();
		bool SendGuildBankInfoOpen();
#endif
