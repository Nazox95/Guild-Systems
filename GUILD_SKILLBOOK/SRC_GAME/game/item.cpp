//If you have EXTENDED_ITEMNAME_ON_GROUND by xP3NG3Rx add in const char * CItem::GetName() new function
#if defined(ENABLE_EXTENDED_ITEMNAME_ON_GROUND) && defined(ENABLE_SKILL_FORGOT_BOOK)
const char * CItem::GetName()
{
	static char szItemName[128];
	memset(szItemName, 0, sizeof(szItemName));
	if (GetProto())
	{
		int len = 0;
		switch (GetType())
		{
			case ITEM_POLYMORPH:
			{
				const DWORD dwMobVnum = GetSocket(0);
				const CMob* pMob = CMobManager::instance().Get(dwMobVnum);
				if (pMob)
					len = snprintf(szItemName, sizeof(szItemName), "%s", pMob->m_table.szLocaleName);

				break;
			}
			case ITEM_SKILLBOOK:
			case ITEM_SKILLFORGET:
			case ITEM_SKILLFORGETGUILD:
			{
				const DWORD dwSkillVnum = (GetVnum() == ITEM_SKILLBOOK_VNUM || GetVnum() == ITEM_SKILLFORGET_VNUM || GetVnum() == ITEM_SKILLFORGETGUILD_VNUM) ? GetSocket(0) : 0;
				const CSkillProto* pSkill = (dwSkillVnum != 0) ? CSkillManager::instance().Get(dwSkillVnum) : NULL;
				if (pSkill)
					len = snprintf(szItemName, sizeof(szItemName), "%s", pSkill->szName);

				break;
			}
		}
		len += snprintf(szItemName + len, sizeof(szItemName) - len, (len>0)?" %s":"%s", GetProto()->szLocaleName);
	}

	return szItemName;
}
#endif
