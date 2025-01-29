//Open questlua_guild.cpp add
#ifdef ENABLE_GUILDSTORAGE_SYSTEM
#	include "db.h"
#endif

//add before
void RegisterGuildFunctionTable()
//
#ifdef ENABLE_GUILDSTORAGE_SYSTEM
	int guild_open_guildstorage(lua_State* L)
	{
		CQuestManager& q = CQuestManager::Instance();
		LPCHARACTER ch = q.GetCurrentCharacterPtr();

		ch->SetGuildstorageOpenPosition();
		ch->ChatPacket(CHAT_TYPE_COMMAND, "ShowMeGuildstorage");
		return 0;
	}

	int guild_buy_guildstorage(lua_State* L)
	{
		CQuestManager& q = CQuestManager::Instance();
		LPCHARACTER ch = q.GetCurrentCharacterPtr();
		CGuild* pGuild = ch->GetGuild();

		if (!ch->GetGuild())
			return 0;

		if (pGuild->GetGuildstorage() >= 3) {
			ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("GUILDSTORAGE_STAGE_MAX_REACHED"));
			return 0;
		}

		/*//V1
		auto pMsg(DBManager::Instance().DirectQuery("SELECT guildstoragestate FROM guild%s WHERE id = %d", pGuild->GetID()));
		MYSQL_ROW row = mysql_fetch_row(pMsg->Get()->pSQLResult);
		int storageState = atoi(row[0]);
		if (storageState == 1)
			return 0;

		//V2
		if (pGuild->IsStorageOpen() == 1)	//TEST
			return 0;*/

		pGuild->SetGuildstorage(1);
		//DBManager::Instance().DirectQuery("UPDATE player.guild SET guildstorage = 1 WHERE id = %d", ch->GetGuild()->GetID());
		return 0;
	}

	int guild_has_guildstorage(lua_State* L)
	{
		LPCHARACTER ch = CQuestManager::Instance().GetCurrentCharacterPtr();
		CGuild* pGuild = ch->GetGuild();

		lua_pushboolean(L, pGuild->GetGuildstorage() ? pGuild->GetGuildstorage() >= 1 : 0);
		return 1;
	}

	int guild_get_guildstorage_level(lua_State* L)
	{
		CQuestManager& q = CQuestManager::Instance();
		lua_pushnumber(L, q.GetCurrentCharacterPtr()->GetGuildstorageSize() / SAFEBOX_PAGE_SIZE);
		return 1;
	}

	int guild_set_guildstorage_level(lua_State* L)
	{
		CQuestManager& q = CQuestManager::Instance();

		TGuildstorageChangeSizePacket p;
		LPCHARACTER ch = CQuestManager::Instance().GetCurrentCharacterPtr();

		//p.dwID = q.GetCurrentCharacterPtr()->GetDesc()->GetAccountTable().id;
		p.dwID = ch->GetGuild()->GetID();
		p.bSize = (int)lua_tonumber(L, -1);
		db_clientdesc->DBPacket(HEADER_DG_GUILDSTORAGE_CHANGE_SIZE, q.GetCurrentCharacterPtr()->GetDesc()->GetHandle(), &p, sizeof(p));

		q.GetCurrentCharacterPtr()->SetGuildstorageSize(SAFEBOX_PAGE_SIZE * (int)lua_tonumber(L, -1));
		return 0;
	}

#	ifdef ENABLE_GUILDRENEWAL_SYSTEM
	int guild_not_has_permission_for_open(lua_State* L)
	{
		LPCHARACTER ch = CQuestManager::Instance().GetCurrentCharacterPtr();
		CGuild* pGuild = ch->GetGuild();

		const TGuildMember* m = pGuild->GetMember(ch->GetPlayerID());
		if (!pGuild->HasGradeAuth(m->grade, GUILD_AUTH_BANK))
			return 0;

		return 0;
	}
#	endif
#endif

//add after
void RegisterGuildFunctionTable()
//NOTE: If you don't the others systems here, add
#ifdef ENABLE_USE_MONEY_FROM_GUILD
			{ "money_in", guild_money_in },
			{ "money_out", guild_money_out },
			{ "get_money0",				guild_get_money0			},
#endif
#ifdef ENABLE_GUILDSTORAGE_SYSTEM
			{ "open_guildstorage",			guild_open_guildstorage			},
			{ "buy_guildstorage",			guild_buy_guildstorage			},
			{ "has_guildstorage",			guild_has_guildstorage			},

			{ "get_guildstorage_level",		guild_get_guildstorage_level	},
			{ "set_guildstorage_level",		guild_set_guildstorage_level	},
#	ifdef ENABLE_GUILDRENEWAL_SYSTEM
			{ "not_has_permission_for_open",guild_not_has_permission_for_open	},
#	endif
#endif
