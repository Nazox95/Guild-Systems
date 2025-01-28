//Find in LPITEM ITEM_MANAGER::CreateItem(DWORD vnum, DWORD count, DWORD id, bool bTryMagic, int iRarePct, bool bSkipSave)
LPITEM ITEM_MANAGER::CreateItem(DWORD vnum, DWORD count, DWORD id, bool bTryMagic, int iRarePct, bool bSkipSave)
{
   [...]
		if (table->sAddonType)
		{
			item->ApplyAddon(table->sAddonType);
		}

		if (bTryMagic)
		{
			if (iRarePct == -1)
				iRarePct = table->bAlterToMagicItemPct;

			if (number(1, 100) <= iRarePct)
				item->AlterToMagicItem();
		}

		if (table->bGainSocketPct)
			item->AlterToSocketItem(table->bGainSocketPct);

		// 50300 == ±â¼ú ¼ö·Ã¼­
		if (vnum == 50300 || vnum == ITEM_SKILLFORGET_VNUM)
      [....]
  //And add befor if (vnum == 50300 || vnum == ITEM_SKILLFORGET_VNUM)
  #ifdef ENABLE_SKILL_FORGOT_BOOK
		if (vnum == ITEM_SKILLFORGETGUILD_VNUM)
		{
			DWORD dwSkillVnum;

			do
			{
				dwSkillVnum = number(151, 157); //Skill id, you can check db->player->skill_proto

				if (NULL != CSkillManager::instance().Get(dwSkillVnum))
					break;
			} while (true);

			item->SetSocket(0, dwSkillVnum);
		}
#endif
