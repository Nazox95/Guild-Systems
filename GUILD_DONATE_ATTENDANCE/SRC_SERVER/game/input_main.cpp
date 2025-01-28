//Open input_main.cpp find and replace
		case GUILD_SUBHEADER_CG_OFFER:
			{
				DWORD offer = *reinterpret_cast<const DWORD*>(c_pData);

				if (pGuild->GetLevel() >= GUILD_MAX_LEVEL && LC_IsHongKong() == false)
				{
					ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("<±æµå> ±æµå°¡ ÀÌ¹Ì ÃÖ°í ·¹º§ÀÔ´Ï´Ù."));
				}
				else
				{
					offer /= 100;
					offer *= 100;

#	ifdef ENABLE_GUILD_DONATE_ATTENDANCE
					if (pGuild->GetLevel() >= 20)
					{
						pGuild->OfferExpNew(ch, offer);
					}
#	endif
					if (pGuild->OfferExp(ch, offer))
					{
						ch->ChatPacket(CHAT_TYPE_INFO, "[LS;699;%u]", offer);
					}
					else
					{
						ch->ChatPacket(CHAT_TYPE_INFO, "[LS;700]");
					}
				}
			}
			return SubPacketLen;
