//open log.cpp add in the end
#if defined(ENABLE_GUILDRENEWAL_SYSTEM) && defined(ENABLE_GUILDBANK_LOG)
void LogManager::GuildLog(LPCHARACTER ch, int guildID, DWORD vnum, const char* typeName, int iteminout, int count, DWORD datatype)
{
	//ch
	//guildID	= GildenID
	//vnum		= ItemVnum
	//typeName	= "Yang" / "Object" / (names)
	//iteminout	= 0=In / 1=Out
	//count		= Anzahl
	//stage		= Datentyp (Yang = 1 / Items = 0 / Objecte = )

	if (!ch)
		return;

	Query("INSERT INTO guildstorage%s (guild_id, time, playerid, chrname, itemvnum, itemname, iteminout, itemcount, datatype) VALUES(%u, NOW(), %u, '%s', %d, '%s', %d, %u, %d)",
		get_table_postfix(), guildID, ch->GetPlayerID(), ch->GetName(), vnum, typeName, iteminout, count, datatype);
}
#endif
