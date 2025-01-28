//Search
void CClientManager::RESULT_SAFEBOX_LOAD(CPeer * pkPeer, SQLMsg * msg)
{
  [..]
					// DWORD dwSocket2 = 0;
					DWORD dwSocket2 = pItemAward->dwSocket2; //Fix

					if (pItemTable->bType == ITEM_UNIQUE)
					{
						if (pItemAward->dwSocket2 != 0)
							dwSocket2 = pItemAward->dwSocket2;
						else
							dwSocket2 = pItemTable->alValues[0];
					}
					else if ((dwItemVnum == 50300 || dwItemVnum == 70037) && pItemAward->dwSocket0 == 0)
					{
						DWORD dwSkillIdx;
						DWORD dwSkillVnum;

						do
						{
[...]
//Replace with
					// DWORD dwSocket2 = 0;
					DWORD dwSocket2 = pItemAward->dwSocket2; //Fix

					if (pItemTable->bType == ITEM_UNIQUE)
					{
						if (pItemAward->dwSocket2 != 0)
							dwSocket2 = pItemAward->dwSocket2;
						else
							dwSocket2 = pItemTable->alValues[0];
					}
					#ifdef ENABLE_SKILL_FORGOT_BOOK //50341 is the new item change if u want.
					else if ((dwItemVnum == 50300 || dwItemVnum == 70037 || dwItemVnum == 50341) && pItemAward->dwSocket0 == 0)
					#else
					else if ((dwItemVnum == 50300 || dwItemVnum == 70037) && pItemAward->dwSocket0 == 0)
					#endif
					{
						DWORD dwSkillIdx;
						DWORD dwSkillVnum;

						do
						{
[...]
