//Open PythonNetworkStream.h find
		// SafeBox
		bool SendSafeBoxMoneyPacket(BYTE byState, DWORD dwMoney);
		bool SendSafeBoxCheckinPacket(TItemPos InventoryPos, BYTE bySafeBoxPos);
		bool SendSafeBoxCheckoutPacket(BYTE bySafeBoxPos, TItemPos InventoryPos);
		bool SendSafeBoxItemMovePacket(BYTE bySourcePos, BYTE byTargetPos, BYTE byCount);

		// Mall
		bool SendMallCheckoutPacket(BYTE byMallPos, TItemPos InventoryPos);
//add
#ifdef ENABLE_GUILDSTORAGE_SYSTEM
		bool SendGuildstorageCheckinPacket(TItemPos InventoryPos, BYTE byGuildstoragePos);
		bool SendGuildstorageCheckoutPacket(BYTE byGuildstoragePos, TItemPos InventoryPos);
#endif

//find
		// Mall
		bool RecvMallOpenPacket();
		bool RecvMallItemSetPacket();
		bool RecvMallItemDelPacket();
//add
#ifdef ENABLE_GUILDSTORAGE_SYSTEM
		bool RecvGuildstorageOpenPacket();
		bool RecvGuildstorageItemSetPacket();
		bool RecvGuildstorageItemDelPacket();
#endif
#ifdef ENABLE_GUILDBANK_LOG
		void GuildBankInfoOpen();
		bool SendGuildBankInfoOpen();
#endif
#ifdef ENABLE_GUILD_DONATE_ATTENDANCE
		void GuildDonateInfoOpen();
#endif

//find
		void __DownloadMark();
		void __DownloadSymbol(const std::vector<DWORD> & c_rkVec_dwGuildID);

		void __PlayInventoryItemUseSound(TItemPos uSlotPos);
		void __PlayInventoryItemDropSound(TItemPos uSlotPos);
		//void __PlayShopItemDropSound(UINT uSlotPos);
		void __PlaySafeBoxItemDropSound(UINT uSlotPos);
		void __PlayMallItemDropSound(UINT uSlotPos);
//add
#ifdef ENABLE_GUILDSTORAGE_SYSTEM
		void __PlayGuildstorageItemDropSound(DWORD uSlotPos);
#endif

//below find
		enum REFRESH_WINDOW_TYPE
		{
			RefreshStatus = (1 << 0),
			RefreshAlignmentWindow = (1 << 1),
			RefreshCharacterWindow = (1 << 2),
			RefreshEquipmentWindow = (1 << 3), 
			RefreshInventoryWindow = (1 << 4),
			RefreshExchangeWindow = (1 << 5),
			RefreshSkillWindow = (1 << 6),
			RefreshSafeboxWindow  = (1 << 7),
			RefreshMessengerWindow = (1 << 8),
			RefreshGuildWindowInfoPage = (1 << 9),
			RefreshGuildWindowBoardPage = (1 << 10),
			RefreshGuildWindowMemberPage = (1 << 11), 
			RefreshGuildWindowMemberPageGradeComboBox = (1 << 12),
			RefreshGuildWindowSkillPage = (1 << 13),
			RefreshGuildWindowGradePage = (1 << 14),
			RefreshTargetBoard = (1 << 15),
			RefreshMallWindow = (1 << 16),
//add
#ifdef ENABLE_GUILDSTORAGE_SYSTEM
			RefreshGuildstorageWindow = (1 << 17),
#endif
		};

//below find 
		void __RefreshStatus();
		void __RefreshAlignmentWindow();
		void __RefreshCharacterWindow();
		void __RefreshEquipmentWindow();
		void __RefreshInventoryWindow();
		void __RefreshExchangeWindow();
		void __RefreshSkillWindow();
		void __RefreshSafeboxWindow();
		void __RefreshMessengerWindow();
		void __RefreshGuildWindowInfoPage();
		void __RefreshGuildWindowBoardPage();
		void __RefreshGuildWindowMemberPage();
		void __RefreshGuildWindowMemberPageGradeComboBox();
		void __RefreshGuildWindowSkillPage();
		void __RefreshGuildWindowGradePage();
		void __RefreshTargetBoardByVID(DWORD dwVID);
		void __RefreshTargetBoardByName(const char * c_szName);
		void __RefreshTargetBoard();
		void __RefreshMallWindow();
//add
#ifdef ENABLE_GUILDSTORAGE_SYSTEM
		void __RefreshGuildstorageWindow();
#endif

//find
		bool m_isRefreshStatus;
		bool m_isRefreshCharacterWnd;
		bool m_isRefreshEquipmentWnd;
		bool m_isRefreshInventoryWnd;
		bool m_isRefreshExchangeWnd;
		bool m_isRefreshSkillWnd;
		bool m_isRefreshSafeboxWnd;
		bool m_isRefreshMallWnd;
		bool m_isRefreshMessengerWnd;
		bool m_isRefreshGuildWndInfoPage;
		bool m_isRefreshGuildWndBoardPage;
		bool m_isRefreshGuildWndMemberPage;
		bool m_isRefreshGuildWndMemberPageGradeComboBox;
		bool m_isRefreshGuildWndSkillPage;
		bool m_isRefreshGuildWndGradePage;
//add
#ifdef ENABLE_GUILDSTORAGE_SYSTEM
		bool m_isRefreshGuildstorageWnd;
#endif
