//If you have ENABLE_EXTENDED_ITEMNAME_ON_GROUND from xP3NG3Rx find
#ifdef ENABLE_EXTENDED_ITEMNAME_ON_GROUND
void CPythonItem::CreateItem(DWORD dwVirtualID, DWORD dwVirtualNumber, float x, float y, float z, bool bDrop, long alSockets[ITEM_SOCKET_SLOT_MAX_NUM], TPlayerItemAttribute aAttrs[ITEM_ATTRIBUTE_SLOT_MAX_NUM])
#else
void CPythonItem::CreateItem(DWORD dwVirtualID, DWORD dwVirtualNumber, float x, float y, float z, bool bDrop)
#endif
//Inside this function search and replace
#if defined(ENABLE_EXTENDED_ITEMNAME_ON_GROUND) && defined(ENABLE_SKILL_FORGOT_BOOK)
	static char szItemName[128];
	ZeroMemory(szItemName, sizeof(szItemName));
	int len = 0;
	switch (pItemData->GetType())
	{
	case CItemData::ITEM_TYPE_POLYMORPH:
	{
		const char* c_szTmp;
		CPythonNonPlayer& rkNonPlayer = CPythonNonPlayer::Instance();
		rkNonPlayer.GetName(alSockets[0], &c_szTmp);
		len += snprintf(szItemName, sizeof(szItemName), "%s", c_szTmp);
		break;
	}
	case CItemData::ITEM_TYPE_SKILLBOOK:
	case CItemData::ITEM_TYPE_SKILLFORGET:
	case CItemData::ITEM_SKILLFORGETGUILD:
	{
			const DWORD dwSkillVnum = (dwVirtualNumber == 50300 || dwVirtualNumber == 70037 || dwVirtualNumber == 50341) ? alSockets[0] : 0;
			CPythonSkill::SSkillData* c_pSkillData;
			if ((dwSkillVnum != 0) && CPythonSkill::Instance().GetSkillData(dwSkillVnum, &c_pSkillData))
				len += snprintf(szItemName, sizeof(szItemName), "%s", c_pSkillData->GradeData[0].strName.c_str());

			break;
		}
	}

	len += snprintf(szItemName + len, sizeof(szItemName) - len, (len > 0) ? " %s" : "%s", pItemData->GetName());

	bool bHasAttr = false;
	for (size_t i = 0; i < ITEM_ATTRIBUTE_SLOT_MAX_NUM; ++i)
	{
		if (aAttrs[i].bType != 0 && aAttrs[i].sValue != 0)
		{
			bHasAttr = true;
			break;
		}
	}
	rkTextTail.RegisterItemTextTail(
		dwVirtualID,
		szItemName,
		&pGroundItemInstance->ThingInstance,
		bHasAttr);
#else
	rkTextTail.RegisterItemTextTail(
		dwVirtualID,
		pItemData->GetName(),
		&pGroundItemInstance->ThingInstance);
#endif
}
