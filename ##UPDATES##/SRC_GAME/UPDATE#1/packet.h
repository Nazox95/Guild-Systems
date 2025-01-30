//Open packet.h, find and replace [UPDATE 30/01/2025]

#ifdef ENABLE_GUILDSTORAGE_SYSTEM
typedef struct packet_guildstorage_open
{
	BYTE bHeader;
	BYTE bSize;
} TPacketGCGuildstorageOpen;
#endif
