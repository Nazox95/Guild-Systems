//Open cube.cpp (if you use cube_renewal.cpp too) find something like this 
	if (ch->IsCubeOpen())
	{
		ch->ChatPacket(CHAT_TYPE_INFO, "[LS;989]");
		return;
	}
//add
	if ( ch->GetExchange() || ch->GetMyShop() || ch->GetShopOwner() || ch->IsOpenSafebox() || ch->IsCubeOpen() 
#ifdef ENABLE_GUILDSTORAGE_SYSTEM
		|| ch->IsOpenGuildstorage()
#endif
		)
	{
		ch->ChatPacket(CHAT_TYPE_INFO, "[LS;990]");
		return;
	}
