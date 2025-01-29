//Open InstanceBase.cpp add:
DWORD CInstanceBase::GetGuildID()
{
	return m_dwGuildID;
}

#ifdef ENABLE_SHOW_LIDER_AND_GENERAL_GUILD
BYTE CInstanceBase::GetNewIsGuildName()
{
	return m_dwNewIsGuildName;
}
#endif

//Now find in:
bool CInstanceBase::Create(const SCreateData& c_rkCreateData)
{
	[---]
	m_dwLevel = c_rkCreateData.m_dwLevel;
	m_dwGuildID = c_rkCreateData.m_dwGuildID;
	m_dwEmpireID = c_rkCreateData.m_dwEmpireID;
//add:
#ifdef ENABLE_SHOW_LIDER_AND_GENERAL_GUILD
	m_dwNewIsGuildName = c_rkCreateData.m_dwNewIsGuildName;
#endif
	[...]
}

//Find and replace:
#ifdef ENABLE_SHOW_LIDER_AND_GENERAL_GUILD
void CInstanceBase::ChangeGuild(DWORD dwGuildID, DWORD dwNewIsGuildName)
#else
void CInstanceBase::ChangeGuild(DWORD dwGuildID)
#endif
{
	m_dwGuildID = dwGuildID;
#ifdef ENABLE_SHOW_LIDER_AND_GENERAL_GUILD
	m_dwNewIsGuildName = dwNewIsGuildName;
#endif
	DetachTextTail();
	AttachTextTail();
	RefreshTextTail();
}

//Now find:
void CInstanceBase::__Initialize()
{
	__Warrior_Initialize();
	__StoneSmoke_Inialize();
	__EffectContainer_Initialize();
	__InitializeRotationSpeed();

	SetEventHandler(CActorInstance::IEventHandler::GetEmptyPtr());

	m_kAffectFlagContainer.Clear();

	m_dwLevel = 0;
	m_dwGuildID = 0;
//Add:
#ifdef ENABLE_SHOW_LIDER_AND_GENERAL_GUILD
	m_dwNewIsGuildName = 0;
#endif
