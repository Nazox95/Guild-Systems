//Open PythonNetworkStream.cpp find
			Set(HEADER_GC_MALL_OPEN, CNetworkPacketHeaderMap::TPacketType(sizeof(TPacketGCMallOpen), STATIC_SIZE_PACKET));
			Set(HEADER_GC_MALL_SET, CNetworkPacketHeaderMap::TPacketType(sizeof(TPacketGCItemSet), STATIC_SIZE_PACKET));
			Set(HEADER_GC_MALL_DEL, CNetworkPacketHeaderMap::TPacketType(sizeof(TPacketGCItemDel), STATIC_SIZE_PACKET));
//add
#ifdef ENABLE_GUILDSTORAGE_SYSTEM
			Set(HEADER_GC_GUILDSTORAGE_OPEN, CNetworkPacketHeaderMap::TPacketType(sizeof(TPacketGCGuildstorageOpen), STATIC_SIZE_PACKET));
			Set(HEADER_GC_GUILDSTORAGE_SET, CNetworkPacketHeaderMap::TPacketType(sizeof(TPacketGCItemSet), STATIC_SIZE_PACKET));
			Set(HEADER_GC_GUILDSTORAGE_DEL, CNetworkPacketHeaderMap::TPacketType(sizeof(TPacketGCItemDel), STATIC_SIZE_PACKET));
#endif
