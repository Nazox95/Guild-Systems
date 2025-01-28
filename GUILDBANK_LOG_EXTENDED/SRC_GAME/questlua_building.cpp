//Open questlua_building.cpp add
#ifdef ENABLE_GUILDBANK_EXTENDED_LOGS
#include "log.h"
#endif

//find and replace
	int building_set_land_owner(lua_State * L)
	{
		if (!lua_isnumber(L, 1) || !lua_isnumber(L, 2))
		{
			sys_err("invalid argument");
			return 0;
		}

		using namespace building;

		CLand * pkLand = CManager::instance().FindLand((DWORD) lua_tonumber(L, 1));

		if (pkLand)
		{
			if (pkLand->GetData().dwGuildID == 0)
				pkLand->SetOwner((DWORD) lua_tonumber(L, 2));
		}

#if defined(ENABLE_GUILDRENEWAL_SYSTEM) && defined(ENABLE_GUILDBANK_EXTENDED_LOGS)
		LPCHARACTER ch = CQuestManager::Instance().GetCurrentCharacterPtr();
		auto pmsg(DBManager::Instance().DirectQuery("INSERT INTO log.guildstorage (guild_id, time, playerid, chrname, itemvnum, itemname, iteminout, itemcount, datatype) VALUES(%u, NOW(), %u, '%s', %d, '%s', %d, %u, %d)",
			pkLand->GetData().dwGuildID, ch->GetPlayerID(), ch->GetName(), 0, "Object", GUILD_GOLD_TYPE_BUY_GUILD_LAND, pkLand->GetData().dwPrice, 1));
#endif

//find and replace
	int building_reconstruct(lua_State* L)
	{
		using namespace building;

		DWORD dwNewBuilding = (DWORD)lua_tonumber(L, 1);

		CQuestManager& q = CQuestManager::instance();

		LPCHARACTER npc = q.GetCurrentNPCCharacterPtr();
		if (!npc)
			return 0;

		CGuild* pGuild = npc->GetGuild();
		if (!pGuild)
			return 0;

		CLand* pLand = CManager::instance().FindLandByGuild(pGuild->GetID());
		if (!pLand)
			return 0;

		LPOBJECT pObject = pLand->FindObjectByNPC(npc);
		if (!pObject)
			return 0;

		pObject->Reconstruct(dwNewBuilding);

#if defined(ENABLE_GUILDRENEWAL_SYSTEM) && defined(ENABLE_GUILDBANK_EXTENDED_LOGS)
		LPCHARACTER ch = CQuestManager::Instance().GetCurrentCharacterPtr();

		int price = pObject->GetPrice();

		const TObjectProto* t = CManager::Instance().GetObjectProto(dwNewBuilding);

		//Guild-Bank
		if (dwNewBuilding == 14072)
			LogManager::Instance().GuildLog(ch, pGuild->GetID(), dwNewBuilding, "Object", GUILD_GOLD_TYPE_UPGRADE_GUILDBANK, price, 1);	//Bank-Ausbau [Stage 2]
		else if (dwNewBuilding == 14073)	
			LogManager::Instance().GuildLog(ch, pGuild->GetID(), dwNewBuilding, "Object", GUILD_GOLD_TYPE_UPGRADE_GUILDBANK, price, 1);	//Bank-Ausbau [Stage 3]

		//Altar
		if (dwNewBuilding == 14062)
			LogManager::Instance().GuildLog(ch, pGuild->GetID(), dwNewBuilding, "Object", GUILD_GOLD_TYPE_UPGRADE_ALTEROFPOWER, price, 1);	//Altar-Ausbau [Stage 2]
		else if (dwNewBuilding == 14063)
			LogManager::Instance().GuildLog(ch, pGuild->GetID(), dwNewBuilding, "Object", GUILD_GOLD_TYPE_UPGRADE_ALTEROFPOWER, price, 1);	//Altar-Ausbau [Stage 3]

		//Ofen
		if (t->dwGroupVnum == 3)
			LogManager::Instance().GuildLog(ch, pGuild->GetID(), dwNewBuilding, "Object", GUILD_GOLD_TYPE_CHANGE_SMELTER, price, 1);	//Ofen-Umbau

		sys_log(0, "building_reconstruct");
#endif
