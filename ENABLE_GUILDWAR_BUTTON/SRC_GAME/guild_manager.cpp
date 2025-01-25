//Open guild_manager.cpp add in the end of function like this:
void SendGuildWarOverNotice(CGuild* g1, CGuild* g2, bool bDraw)
{
	if (g1 && g2)
	{
		char buf[256];

		if (bDraw)
		{
			snprintf(buf, sizeof(buf), "[LS;479;%s;%s]", g1->GetName(), g2->GetName());
		}
		else
		{
			if ( g1->GetWarScoreAgainstTo( g2->GetID() ) > g2->GetWarScoreAgainstTo( g1->GetID() ) )
			{
				snprintf(buf, sizeof(buf), "[LS;480;%s;%s]", g1->GetName(), g2->GetName());
			}
			else
			{
				snprintf(buf, sizeof(buf), "[LS;480;%s;%s]", g2->GetName(), g1->GetName());
			}
		}

		SendNotice(buf);
	}
#ifdef ENABLE_GUILDWAR_BUTTON
	g1->SendAllMembersButtonState(false);
	g2->SendAllMembersButtonState(false);
#endif
}

//Find and add like:
void CGuildManager::SendGuildWar(LPCHARACTER ch)
{
	if (!ch->GetDesc())
		return;

	TEMP_BUFFER buf;
	TPacketGCGuild p;
	p.header= HEADER_GC_GUILD;
	p.subheader = GUILD_SUBHEADER_GC_GUILD_WAR_LIST;
	p.size = sizeof(p) + (sizeof(DWORD) * 2) * m_GuildWar.size();
	buf.write(&p, sizeof(p));

	itertype(m_GuildWar) it;

	for (it = m_GuildWar.begin(); it != m_GuildWar.end(); ++it)
	{
		buf.write(&it->first, sizeof(DWORD));
		buf.write(&it->second, sizeof(DWORD));
	}

#ifdef ENABLE_GUILDWAR_BUTTON
	ch->SendWarTeleportButton(m_GuildWar.size() <= 0 ? false : true);
#endif
	ch->GetDesc()->Packet(buf.read_peek(), buf.size());
}
