//open PythonNetworkStreamPhaseGame.cpp find:

case GUILD_SUBHEADER_GC_MONEY_CHANGE:
{
	[...]
}
//add after function:
#ifdef ENABLE_GUILD_LAND_INFO
		case GUILD_SUBHEADER_GC_LAND_INFO:
		{
			int mindex;	//Baseinfo
			int guildAltar;	//Altar der Kraft LV.
			int guildAlchemist;	//Gildenalchemist
			int guildBlacksmith;	//Gildenschmied
			int storage_lv;	//Gildenlager LV.

			if (!Recv(sizeof(mindex), &mindex))
				return false;
			if (!Recv(sizeof(guildAltar), &guildAltar))
				return false;
			if (!Recv(sizeof(guildAlchemist), &guildAlchemist))
				return false;
			if (!Recv(sizeof(guildBlacksmith), &guildBlacksmith))
				return false;
			if (!Recv(sizeof(storage_lv), &storage_lv))
				return false;

			CPythonGuild::Instance().SetGuildLandInfo(mindex, guildAltar, guildAlchemist, guildBlacksmith, storage_lv);
			PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "RefreshGuildBaseInfoPage", Py_BuildValue("()"));
			__RefreshGuildWindowInfoPage();
			break;
		}
#endif
