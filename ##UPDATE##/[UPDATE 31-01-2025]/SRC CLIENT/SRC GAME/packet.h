//Open packet.h, find and replace

#ifdef ENABLE_GUILDSTORAGE_SYSTEM
typedef struct packet_guildstorage_open
{
	BYTE bHeader;
	BYTE bSize;
} TPacketGCGuildstorageOpen;
#endif
