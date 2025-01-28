//Open input_main.cpp find and replace:
		case GUILD_SUBHEADER_CG_CHARGE_GSP:
			{
				const int offer = *reinterpret_cast<const int*>(c_pData);
				const int gold = offer * 100;

				if (offer < 0 || gold < offer || gold < 0 || ch->GetGold() < gold)
				{
					ch->ChatPacket(CHAT_TYPE_INFO, "[LS;701]");
					return SubPacketLen;
				}

				if (!pGuild->ChargeSP(ch, offer))
				{
					ch->ChatPacket(CHAT_TYPE_INFO, "[LS;702]");
				}
#if defined(ENABLE_GUILDRENEWAL_SYSTEM) && defined(ENABLE_GUILDBANK_EXTENDED_LOGS)
				int _gold;
				if (pGuild->GetLevel() >= 15)	// Preisnachlass: Drachengeist (10% weniger Yang ben?igt) [Bonus 3]
					_gold = gold * 0.90;
				else
					_gold = gold;

				LogManager::Instance().GuildLog(ch, ch->GetGuild()->GetID(), 0, "DragonSP", GUILD_GOLD_TYPE_DRAGON_SP_RECOVER, _gold, 1);
				/*auto pmsg(DBManager::Instance().DirectQuery("INSERT INTO log.guildstorage (guild_id, time, playerid, chrname, itemvnum, itemname, iteminout, itemcount, datatype) VALUES(%u, NOW(), %u, '%s', %d, '%s', %d, %u, %d)",
					pGuild->GetID(), ch->GetPlayerID(), ch->GetName(), 0, "DragonSP", GUILD_GOLD_TYPE_DRAGON_SP_RECOVER, gold, 1));*/
#endif
			}
			return SubPacketLen;
