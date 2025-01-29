//Open PythonApplication.h add
#ifdef ENABLE_GUILDSTORAGE_SYSTEM
#	include "PythonGuildBank.h"
#endif

//find
		CPythonBackground			m_pyBackground;
		CPythonSkill				m_pySkill;
		CPythonResource				m_pyRes;
		CPythonQuest				m_pyQuest;
		CPythonMessenger			m_pyManager;
		CPythonSafeBox				m_pySafeBox;
//add
#ifdef ENABLE_GUILDSTORAGE_SYSTEM
		CPythonGuildBank			m_pyGuildBank;
#endif
