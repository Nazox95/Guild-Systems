//find
	protected:
		// Game Cursor Data
		TPixelPosition			m_MovingCursorPosition;
		float					m_fMovingCursorSettingTime;
		DWORD					m_adwEffect[EFFECT_NUM];

		DWORD					m_dwVIDPicked;
		DWORD					m_dwIIDPicked;
		int						m_aeMBFButton[MBT_NUM];

		DWORD					m_dwTargetVID;
		DWORD					m_dwTargetEndTime;
		DWORD					m_dwPlayTime;
		SAutoPotionInfo			m_kAutoPotionInfo[AUTO_POTION_TYPE_NUM];
//add
#ifdef ENABLE_SECOND_GUILDRENEWAL_SYSTEM
protected:
	bool m_bParaState;
public:
	void SetParalysis(bool bParaState) { m_bParaState = bParaState; };
#endif
