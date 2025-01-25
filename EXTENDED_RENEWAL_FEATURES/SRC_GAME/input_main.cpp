//Open input_main.cpp find:
size_t GetSubPacketSize(const GUILD_SUBHEADER_CG& header)
{
	switch (header)
	{
		case GUILD_SUBHEADER_CG_DEPOSIT_MONEY:				return sizeof(int);
		[...]
		case GUILD_SUBHEADER_CG_CHANGE_MEMBER_GENERAL:		return sizeof(DWORD) + sizeof(BYTE);
		case GUILD_SUBHEADER_CG_GUILD_INVITE_ANSWER:		return sizeof(DWORD) + sizeof(BYTE);
//add
#if defined(ENABLE_EXTENDED_RENEWAL_FEATURES)
		case GUILD_SUBHEADER_CG_CHANGE_GUILDMASTER:
			return sizeof(DWORD);
		case GUILD_SUBHEADER_CG_DELETE_LAND:
			return sizeof(int);
#endif
}

//Find:
		case GUILD_SUBHEADER_CG_GUILD_INVITE_ANSWER:
			{
				const DWORD guild_id = *reinterpret_cast<const DWORD*>(c_pData);
				const BYTE accept = *(c_pData + sizeof(DWORD));

				CGuild * g = CGuildManager::instance().FindGuild(guild_id);

				if (g)
				{
					if (accept)
						g->InviteAccept(ch);
					else
						g->InviteDeny(ch->GetPlayerID());
				}
			}
			return SubPacketLen;
//after add:

#if defined(ENABLE_EXTENDED_RENEWAL_FEATURES)
		case GUILD_SUBHEADER_CG_CHANGE_GUILDMASTER:
			{
				if (pGuild->UnderAnyWar() != 0)
				{
					ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("<±æµå> ±æµåÀü Áß¿¡´Â ±æµå¿øÀ» Å»Åð½ÃÅ³ ¼ö ¾ø½À´Ï´Ù."));
					return SubPacketLen;
				}

				const DWORD pid = *reinterpret_cast<const DWORD*>(c_pData);
				const TGuildMember* m = pGuild->GetMember(ch->GetPlayerID());

				if (NULL == m)
					return -1;

				LPCHARACTER member = CHARACTER_MANAGER::Instance().FindByPID(pid);
				LPCHARACTER myself = CHARACTER_MANAGER::Instance().FindByPID(ch->GetPlayerID());

				if (!ch->CountSpecifyItem(71099)) {	//anillo
					ch->ChatPacket(CHAT_TYPE_INFO, "[LS;2021]");
					return SubPacketLen;
				}

				if (member)
				{
					if (member->GetGuild() != pGuild) {
						ch->ChatPacket(CHAT_TYPE_INFO, "[LS;689]");
						return SubPacketLen;
					}
					if (member == myself) {
						ch->ChatPacket(CHAT_TYPE_INFO, "[LS;2022]");
						return SubPacketLen;
					}

					if (pGuild->ChangeMasterTo(member->GetPlayerID()))
					{
						ch->RemoveSpecifyItem(71099, 1);	//Anillo
						ch->ChatPacket(CHAT_TYPE_INFO, "[LS;2023]");
					}
					else
						ch->ChatPacket(CHAT_TYPE_INFO, "[LS;688]");
				}
			}
			return SubPacketLen;

		case GUILD_SUBHEADER_CG_DELETE_LAND:
			{
				const int vid = *reinterpret_cast<const int*>(c_pData);
				const TGuildMember* m = pGuild->GetMember(ch->GetPlayerID());

				if (NULL == m)
					return -1;

				if (m->grade != GUILD_LEADER_GRADE) {
					ch->ChatPacket(CHAT_TYPE_INFO, "[LS;2024]");
				}
				else {
					if (!pGuild->HasLand()) {
						ch->ChatPacket(CHAT_TYPE_INFO, "[LS;2025]");
						return SubPacketLen;
					}

					if (pGuild->GetGuildLandDeletePulse() > time(0)/* && !ch->IsGM()*/) {
						int deltaInSeconds = pGuild->GetGuildLandDeletePulse() - time(0);

						DWORD minutes, hours, secs_left, mins_left;
						hours = deltaInSeconds / 3600;
						minutes = deltaInSeconds / 60;
						mins_left = minutes % 60;
						secs_left = deltaInSeconds % 60;

						ch->ChatPacket(CHAT_TYPE_INFO, "[LS;2026;%02d;%02d;%02d]", hours, mins_left, secs_left);
						return SubPacketLen;
					}

					pGuild->SetGuildLandDeletePulse(time(0) + 86400);	//[seconds] to do action again

					building::CManager::Instance().ClearLandByGuildID(vid);
					ch->ChatPacket(CHAT_TYPE_INFO, "[LS;2027]");

					pGuild->SetGuildLandInfo();
				}
			}
			return SubPacketLen;
#endif

	}

	return 0;
}
