//Open exchange.cpp find
bool CHARACTER::ExchangeStart(LPCHARACTER victim)
{
	if (this == victim)	// ÀÚ±â ÀÚ½Å°ú´Â ±³È¯À» ¸øÇÑ´Ù.
		return false;

	if (IsObserverMode())
	{
		ChatPacket(CHAT_TYPE_INFO, "[LS;893]");
		return false;
	}

	if (victim->IsNPC())
		return false;

	//PREVENT_TRADE_WINDOW
//add
	if ( IsOpenSafebox() || GetShopOwner() || GetMyShop() || IsCubeOpen()
#ifdef ENABLE_GUILDSTORAGE_SYSTEM
		|| IsOpenGuildstorage()
#endif
		)
	{
		ChatPacket( CHAT_TYPE_INFO, "[LS;894]");
		return false;
	}
//add
	if ( victim->IsOpenSafebox() || victim->GetShopOwner() || victim->GetMyShop() || victim->IsCubeOpen() 
#ifdef ENABLE_GUILDSTORAGE_SYSTEM
		|| victim->IsOpenGuildstorage()
#endif
		)
	{
		ChatPacket( CHAT_TYPE_INFO, "[LS;895]");
		return false;
	}
