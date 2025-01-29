//Open packet_info.cpp find 
	Set(HEADER_CG_CLIENT_VERSION, sizeof(TPacketCGClientVersion), "Version", true);
	Set(HEADER_CG_CLIENT_VERSION2, sizeof(TPacketCGClientVersion2), "Version", true);
	Set(HEADER_CG_PONG, sizeof(BYTE), "Pong", true);
	Set(HEADER_CG_MALL_CHECKOUT, sizeof(TPacketCGSafeboxCheckout), "MallCheckout", true);
//add
#ifdef ENABLE_GUILDSTORAGE_SYSTEM
	Set(HEADER_CG_GUILDSTORAGE_CHECKIN, sizeof(TPacketCGSafeboxCheckin), "GuildstorageCheckin", true);
	Set(HEADER_CG_GUILDSTORAGE_CHECKOUT, sizeof(TPacketCGSafeboxCheckout), "GuildstorageCheckout", true);
#endif
