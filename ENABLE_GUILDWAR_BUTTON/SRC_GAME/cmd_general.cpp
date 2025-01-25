//Open cmd_general.cpp add in the end:
#ifdef ENABLE_GUILDWAR_BUTTON
ACMD(do_guildwar_request_enter)
{
	if (!ch)
		return;

	if (ch->GetGuild())
		ch->GetGuild()->GuildWarEntryAccept(ch->GetGuild()->UnderAnyWar(), ch);
}
#endif
