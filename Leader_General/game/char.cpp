//Find:
void CHARACTER::EncodeInsertPacket(LPENTITY entity)
{

	LPDESC d;
	[...]

		if (GetGuild() != nullptr)
			addPacket.dwGuildID = GetGuild()->GetID();
		else
			addPacket.dwGuildID = 0;

			addPacket.sAlignment = m_iAlignment / 10;
		}

		d->Packet(&addPacket, sizeof(TPacketGCCharacterAdditionalInfo));
	}

	if (iDur)
//Replace like this:
#ifdef ENABLE_SHOW_LIDER_AND_GENERAL_GUILD
			if (GetGuild() != NULL)
			{	
				addPacket.dwGuildID = GetGuild()->GetID();
				CGuild* pGuild = this->GetGuild();
				if (pGuild->GetMasterPID() == GetPlayerID())
					addPacket.dwNewIsGuildName = 3;
				else if (pGuild->IsCoLeader(GetPlayerID()))
					addPacket.dwNewIsGuildName = 2;
				else
					addPacket.dwNewIsGuildName = 1;
			}
			else
			{
				addPacket.dwGuildID = 0;
				addPacket.dwNewIsGuildName = 0;
			}
#else
			if (GetGuild() != nullptr)
				addPacket.dwGuildID = GetGuild()->GetID();
			else
				addPacket.dwGuildID = 0;
#endif

			addPacket.sAlignment = m_iAlignment / 10;
		}

		d->Packet(&addPacket, sizeof(TPacketGCCharacterAdditionalInfo));
	}

	if (iDur)
		[...]

//Now Find :
void CHARACTER::UpdatePacket()
{
	if (GetSectree() == NULL) return;
	[...]
	pack.dwGuildID	= 0;
	pack.sAlignment	= m_iAlignment / 10;
	pack.bPKMode	= m_bPKMode;
	pack.dwMountVnum	= GetMountVnum();

//Replace like this:
	pack.dwGuildID	= 0;
	pack.sAlignment	= m_iAlignment / 10;
#ifdef ENABLE_NEW_PET_SYSTEM
	pack.dwLevel = GetLevel();
#endif
	pack.bPKMode	= m_bPKMode;

#ifdef ENABLE_SHOW_LIDER_AND_GENERAL_GUILD
	if (GetGuild())
		pack.dwGuildID = GetGuild()->GetID();
	CGuild* pGuild = this->GetGuild();
	if (pGuild)
	{
		if (pGuild->GetMasterPID() == GetPlayerID())
			pack.dwNewIsGuildName = 3;
		else if (pGuild->IsCoLeader(GetPlayerID()))
			pack.dwNewIsGuildName = 2;
		else
			pack.dwNewIsGuildName = 1;
	}
	else
	{
		pack.dwNewIsGuildName = 0;
	}
#endif

	pack.dwMountVnum	= GetMountVnum();
