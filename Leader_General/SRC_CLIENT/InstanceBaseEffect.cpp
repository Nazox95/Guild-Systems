//Open InstanceBaseEffect.cpp find:
void CInstanceBase::AttachTextTail()
{
	[...]
//Replace:
#ifdef ENABLE_SHOW_LIDER_AND_GENERAL_GUILD
	CPythonTextTail::Instance().RegisterCharacterTextTail(m_dwGuildID, m_dwNewIsGuildName, dwVID, s_kD3DXClrTextTail, fTextTailHeight);
#else
	CPythonTextTail::Instance().RegisterCharacterTextTail(m_dwGuildID, dwVID, s_kD3DXClrTextTail, fTextTailHeight);
#endif
}
-----------------------
-----------------------
-----------------------
//Open NetworkActorManager.cpp and find:
void SNetworkActorData::__copy__(const SNetworkActorData& src)
{
	m_bType = src.m_bType;
	m_dwVID = src.m_dwVID;
	[...]
	m_dwGuildID = src.m_dwGuildID;
//Add
#ifdef ENABLE_SHOW_LIDER_AND_GENERAL_GUILD
	m_dwNewIsGuildName = src.m_dwNewIsGuildName;
#endif
	m_dwLevel = src.m_dwLevel;

//Find:
InstanceBase* CNetworkActorManager::__AppendCharacterManagerActor(SNetworkActorData& rkNetActorData)
{
	Lognf(0, "CNetworkActorManager::__AppendCharacterManagerActor(%d, %s)", rkNetActorData.m_dwVID, rkNetActorData.m_stName.c_str());

	DWORD dwVID=rkNetActorData.m_dwVID;

	CPythonCharacterManager & rkChrMgr = CPythonCharacterManager::Instance();


	CInstanceBase::SCreateData kCreateData;
	kCreateData.m_bType=rkNetActorData.m_bType;
	kCreateData.m_dwLevel=rkNetActorData.m_dwLevel;
	[...]
	kCreateData.m_dwMountVnum=rkNetActorData.m_dwMountVnum;
//add
#ifdef ENABLE_SHOW_LIDER_AND_GENERAL_GUILD
	kCreateData.m_dwNewIsGuildName = rkNetActorData.m_dwNewIsGuildName;
#endif

//Find:
void CNetworkActorManager::UpdateActor(const SNetworkUpdateActorData& c_rkNetUpdateActorData)
{
	std::map<DWORD, SNetworkActorData>::iterator f=m_kNetActorDict.find(c_rkNetUpdateActorData.m_dwVID);
	if (m_kNetActorDict.end()==f)
	{
#ifdef _DEBUG
		TraceError("CNetworkActorManager::UpdateActor(dwVID=%d) - NOT EXIST VID", c_rkNetUpdateActorData.m_dwVID);
#endif
		return;
	}

	SNetworkActorData& rkNetActorData=f->second;

	CInstanceBase* pkInstFind=__FindActor(rkNetActorData);
	if (pkInstFind)
	{
		pkInstFind->ChangeArmor(c_rkNetUpdateActorData.m_dwArmor);		
		pkInstFind->ChangeWeapon(c_rkNetUpdateActorData.m_dwWeapon);
		[..]
//Replace:
#ifdef ENABLE_SHOW_LIDER_AND_GENERAL_GUILD
		pkInstFind->ChangeGuild(c_rkNetUpdateActorData.m_dwGuildID, c_rkNetUpdateActorData.m_dwNewIsGuildName);
#else
		pkInstFind->ChangeGuild(c_rkNetUpdateActorData.m_dwGuildID);
#endif

//In the same function find:
	rkNetActorData.m_kAffectFlags=c_rkNetUpdateActorData.m_kAffectFlags;
	rkNetActorData.m_dwGuildID=c_rkNetUpdateActorData.m_dwGuildID;
//Add
#ifdef ENABLE_SHOW_LIDER_AND_GENERAL_GUILD
	rkNetActorData.m_dwNewIsGuildName = c_rkNetUpdateActorData.m_dwNewIsGuildName;
#endif
	//rkNetActorData.m_dwLevel=c_rkNetUpdateActorData.m_dwLevel;
	rkNetActorData.m_dwMovSpd=c_rkNetUpdateActorData.m_dwMovSpd;
	rkNetActorData.m_dwAtkSpd=c_rkNetUpdateActorData.m_dwAtkSpd;
