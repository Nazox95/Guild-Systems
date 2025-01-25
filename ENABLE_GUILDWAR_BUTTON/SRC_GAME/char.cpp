//Open char.cpp find
EVENTFUNC(RefreshShopEvent)
{
	char_event_info* info = dynamic_cast<char_event_info*>(event->info);
	if (info == NULL)
	{
		sys_err("ishop_refresh_event> <Factor> Null pointer");
		return 0;
	}

	LPCHARACTER	ch = info->ch;

	if (NULL == ch)
		return 0;

//add:
#ifdef ENABLE_GUILDWAR_BUTTON
void CHARACTER::SendWarTeleportButton(bool show) 
{
	if (CWarMapManager::Instance().IsWarMap(GetMapIndex()))
		show = false;

	ChatPacket(CHAT_TYPE_COMMAND, "guild_war %d", show);
}
#endif

//Note: If you don't find the function, add in the end.
