//Add
#ifdef ENABLE_SKILL_FORGOT_BOOK
#include "guild.h"
#endif

//Search and add after
		case ITEM_SKILLFORGET:
			{
				if (!item->GetSocket(0))
				{
					ITEM_MANAGER::instance().RemoveItem(item);
					return false;
        [...]
			break;
#ifdef ENABLE_SKILL_FORGOT_BOOK
			case ITEM_SKILLFORGETGUILD:
			{
				if (GetGuild() == NULL)
				{
					ChatPacket(CHAT_TYPE_INFO, "[LS;1597]");
					return false;
				}

				// Check is the player is the leader of the guild.
				if (GetGuild()->GetMasterPID() != GetPlayerID())
				{
					ChatPacket(CHAT_TYPE_INFO, "[LS;1590]");
					return false;
				}

				// Check if skill have socket0.
				if (!item->GetSocket(0))
				{
					ITEM_MANAGER::instance().RemoveItem(item);
					return false;
				}

				// Find the number of the skill.
				DWORD dwVnum = item->GetSocket(0);

				if (GetGuild()->SkillLevelDown(dwVnum))
				{
					item->SetCount(item->GetCount() - 1);
					ChatPacket(CHAT_TYPE_INFO, "[LS;78]");
				}
				else
				{
					ChatPacket(CHAT_TYPE_INFO, "[LS;88]");
				}
			}
			break;
#endif
