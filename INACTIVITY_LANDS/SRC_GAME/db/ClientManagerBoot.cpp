//Add
#include "../../common/service.h"

//Now Search this and add below
bool CClientManager::InitializeLandTable()
{
	using namespace building;

#ifdef ENABLE_GUILDLAND_INACTIVITY_DELETE
	// Update guild_id to 0 for inactive guilds.
	CDBManager::Instance().DirectQuery("UPDATE player.land " //Update land from player->land.sql
		"INNER JOIN player.guild ON land.guild_id = guild.id " //search guild_id 
		"INNER JOIN player.player ON guild.master = player.id " //Search guild_master id to check leader.
		"INNER JOIN account.account ON player.account_id = account.id " //Check if the same id in player and account
		"SET land.guild_id = 0 " //Put land guild in 0
		"WHERE land.guild_id > 0 "
		"AND DATE_SUB(NOW(), INTERVAL 5 MINUTE) > account.last_play;"); //This check the last_play from account, check your innactive account.
		//"AND DATE_SUB(NOW(), INTERVAL 5 SECONDS) > account.last_play;"); //If u want Seconds
  		//"AND DATE_SUB(NOW(), INTERVAL 5 MONTH) > account.last_play;"); //If u want month
  		//"AND DATE_SUB(NOW(), INTERVAL 5 YEAR) > account.last_play;"); //if u want year

	// Remove object if guild_id is = 0,
	CDBManager::Instance().DirectQuery("DELETE object "
		"FROM player.object "
		"INNER JOIN player.land ON land.id = object.land_id "
		"WHERE land.guild_id = 0;");
#endif
