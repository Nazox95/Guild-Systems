//Open item_manager.cpp add 
#ifdef ENABLE_GUILDSTORAGE_SYSTEM
#	include "guild.h"
#endif

//Note, here, take care, adapt with your files, if you can't see 'GUILDBANK' on navicat and safebox ingame, the problem is here.
	sys_log(1, "ITEM_SAVE %s:%d in %s window %d", item->GetName(), item->GetID(), item->GetOwner()->GetName(), item->GetWindow());

	TPlayerItem t{};

	t.id = item->GetID();
	t.window = item->GetWindow();
	t.pos = t.window == EQUIPMENT ? item->GetCell() - INVENTORY_MAX_NUM : item->GetCell();
	t.count = item->GetCount();
	t.vnum = item->GetOriginalVnum();
//adapt
	t.owner = (t.window == SAFEBOX || t.window == MALL) ? item->GetOwner()->GetDesc()->GetAccountTable().id : item->GetOwner()->GetPlayerID();
#ifdef ENABLE_GUILDSTORAGE_SYSTEM
	if (t.window == GUILDBANK) 
	{
		if (item->GetOwner()->GetGuild())  // Verifica si el jugador tiene gremio
		{
			t.owner = item->GetOwner()->GetGuild()->GetID();  // Asigna el ID del gremio como dueño del ítem
		}
		else
		{
			sys_err("Item en Guild Bank pero jugador no tiene gremio: %s", item->GetName());
			return;  // Evita guardar el ítem si el jugador no pertenece a un gremio
		}
	}
#endif
	thecore_memcpy(t.alSockets, item->GetSockets(), sizeof(t.alSockets));
	thecore_memcpy(t.aAttr, item->GetAttributes(), sizeof(t.aAttr));

	db_clientdesc->DBPacketHeader(HEADER_GD_ITEM_SAVE, 0, sizeof(TPlayerItem));
	db_clientdesc->Packet(&t, sizeof(TPlayerItem));
}

//find 
void ITEM_MANAGER::RemoveItem(LPITEM item, const char * c_pszReason)
{
	LPCHARACTER o;

	if ((o = item->GetOwner()))
	{
		char szHint[64];
		snprintf(szHint, sizeof(szHint), "%s %u ", item->GetName(), item->GetCount());
		LogManager::instance().ItemLog(o, item, c_pszReason ? c_pszReason : "REMOVE", szHint);
//replace
		// SAFEBOX_TIME_LIMIT_ITEM_BUG_FIX
#ifdef ENABLE_GUILDSTORAGE_SYSTEM
		if (item->GetWindow() == MALL || item->GetWindow() == SAFEBOX || item->GetWindow() == GUILDBANK)
#else
		if (item->GetWindow() == MALL || item->GetWindow() == SAFEBOX)
#endif
		{
#ifdef ENABLE_GUILDSTORAGE_SYSTEM
			CSafebox* pSafebox = item->GetWindow() == MALL ? o->GetMall() : (item->GetWindow() == GUILDBANK ? o->GetGuildstorage() : o->GetSafebox());
#else
			CSafebox* pSafebox = item->GetWindow() == MALL ? o->GetMall() : o->GetSafebox();
#endif
