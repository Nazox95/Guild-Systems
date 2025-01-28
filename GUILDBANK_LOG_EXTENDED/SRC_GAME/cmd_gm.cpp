//open cmd_gm.cpp find:
// BUILD_BUILDING
ACMD(do_build)
{
	using namespace building;

	char arg1[256], arg2[256], arg3[256], arg4[256];
	const char * line = one_argument(argument, arg1, sizeof(arg1));
	BYTE GMLevel = ch->GetGMLevel();
	[...]
					{
						int i;
						for (i = 0; i < OBJECT_MATERIAL_MAX_NUM; ++i)
						{
							DWORD dwItemVnum = t->kMaterials[i].dwItemVnum;
							DWORD dwItemCount = t->kMaterials[i].dwCount;

							if (dwItemVnum == 0)
								break;

							sys_log(0, "BUILD: material %d %u %u", i, dwItemVnum, dwItemCount);
							ch->RemoveSpecifyItem(dwItemVnum, dwItemCount);
						}
					}
				}
//add
#if defined(ENABLE_GUILDRENEWAL_SYSTEM) && defined(ENABLE_GUILDBANK_EXTENDED_LOGS)
				if (dwVnum != 14062 || dwVnum != 14063 || dwVnum != 14072 || dwVnum != 14073) {
					if (t->dwGroupVnum == 1 || t->dwGroupVnum == 2 || t->dwGroupVnum == 3 || t->dwGroupVnum == 4 /*14062, 14063*/ || t->dwGroupVnum == 6 /*14072, 14073*/) {
						LogManager::Instance().GuildLog(ch, ch->GetGuild()->GetID(), dwVnum, "Object", GUILD_GOLD_TYPE_OBJECT_CREATE, t->dwPrice, 1);
						sys_log(0, "BUILD_LOG_OBJECT: %d", dwVnum);
					}
				}
#endif
