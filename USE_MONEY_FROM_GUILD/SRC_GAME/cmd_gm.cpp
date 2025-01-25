//Open cmd_gm.cpp and find:
// BUILD_BUILDING
ACMD(do_build)
{
	[...]
	switch (LOWER(*arg1))
	{
		case 'c':
			{
				// /build c vnum x y x_rot y_rot z_rot
				char arg5[256], arg6[256];
				line = one_argument(two_arguments(line, arg1, sizeof(arg1), arg2, sizeof(arg2)), arg3, sizeof(arg3)); // vnum x y
				one_argument(two_arguments(line, arg4, sizeof(arg4), arg5, sizeof(arg5)), arg6, sizeof(arg6)); // x_rot y_rot z_rot

				if (!*arg1 || !*arg2 || !*arg3 || !*arg4 || !*arg5 || !*arg6)
				{
					ch->ChatPacket(CHAT_TYPE_INFO, "Invalid syntax");
					return;
				}
				[...]
				if (t->dwDependOnGroupVnum)
				{
					//		const TObjectProto * dependent = CManager::Instance().GetObjectProto(dwVnum);
					//		if (dependent)
					{
						// Áö¾îÁ®ÀÖ´Â°¡?
						if (!pkLand->FindObjectByGroup(t->dwDependOnGroupVnum))
						{
							ch->ChatPacket(CHAT_TYPE_INFO, "[LS;748]");
							return;
						}
					}
				}

				if (test_server || GMLevel == GM_PLAYER)
				{
					// GMÀÌ ¾Æ´Ò°æ¿ì¸¸ (Å×¼·¿¡¼­´Â GMµµ ¼Ò¸ð)
					// °Ç¼³ ºñ¿ë Ã¼Å©
					if (t->dwPrice > BUILDING_MAX_PRICE)
					{
						ch->ChatPacket(CHAT_TYPE_INFO, "[LS;749]");
						return;
					}
//Replace
#ifdef ENABLE_USE_MONEY_FROM_GUILD
					CGuild* g = ch->GetGuild();
					if (g->GetGuildMoney() < (int)t->dwPrice)
#else
					if (ch->GetGold() < (int)t->dwPrice)
#endif
					{
						ch->ChatPacket(CHAT_TYPE_INFO, "[LS;750]");
						return;
					}
}
//Find in the same function (below)
[...]
				float x_rot = atof(arg4);
				float y_rot = atof(arg5);
				float z_rot = atof(arg6);
				// 20050811.myevan.°Ç¹° È¸Àü ±â´É ºÀÀÎ ÇØÁ¦
				/*
				   if (x_rot != 0.0f || y_rot != 0.0f || z_rot != 0.0f)
				   {
				   ch->ChatPacket(CHAT_TYPE_INFO, "°Ç¹° È¸Àü ±â´ÉÀº ¾ÆÁ÷ Á¦°øµÇÁö ¾Ê½À´Ï´Ù");
				   return;
				   }
				 */

				long map_x = 0;
				str_to_number(map_x, arg2);
				long map_y = 0;
				str_to_number(map_y, arg3);

				bool isSuccess = pkLand->RequestCreateObject(dwVnum,
						ch->GetMapIndex(),
						map_x,
						map_y,
						x_rot,
						y_rot,
						z_rot, true);

				if (!isSuccess)
				{
					if (test_server)
						ch->ChatPacket(CHAT_TYPE_INFO, "[LS;752]");
					return;
				}

				//if (test_server || GMLevel == GM_PLAYER)
				if (!test_server)	//@fixme529
				{
//Replace
#ifdef ENABLE_USE_MONEY_FROM_GUILD
					CGuild* g = ch->GetGuild();
					if (!g)
						return;
					g->RequestWithdrawMoney(ch, t->dwPrice, false);
					ch->PointChange(POINT_GOLD, -static_cast<int>(t->dwPrice));	//@fixme501
#else
					//ch->PointChange(POINT_GOLD, -t->dwPrice);
					ch->PointChange(POINT_GOLD, -static_cast<int>(t->dwPrice));	//@fixme501
#endif

					// ¾ÆÀÌÅÛ ÀÚÀç »ç¿ëÇÏ±â
					{
						int i;
						for (i = 0; i < OBJECT_MATERIAL_MAX_NUM; ++i)
						{
							DWORD dwItemVnum = t->kMaterials[i].dwItemVnum;
							DWORD dwItemCount = t->kMaterials[i].dwCount;

							if (dwItemVnum == 0)
								break;

							sys_log(0, "BUILD: material %d %u %u", i, dwItemVnum, dwItemCount);
							ch->RemoveSpecifyItem(dwItemVnum, dwItemCount);
						}
					}
				}
