//Open guild_manager.cpp after 
void CGuildManager::Initialize()
//add
#ifdef ENABLE_GUILDSTORAGE_SYSTEM
void CGuildManager::InitializeDonate()
{
	auto pMsg(DBManager::Instance().DirectQuery("UPDATE guild%s SET guildstoragestate = 0", get_table_postfix()));
}
#endif
