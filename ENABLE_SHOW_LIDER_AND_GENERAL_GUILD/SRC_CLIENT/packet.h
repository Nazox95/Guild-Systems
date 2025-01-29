//Open packet.h and find:
typedef struct packet_char_additional_info
{
	BYTE	header;
	[...]
	DWORD   dwMountVnum;
#ifdef ENABLE_SHOW_LIDER_AND_GENERAL_GUILD
	BYTE	dwNewIsGuildName;
#endif
} TPacketGCCharacterAdditionalInfo;

//find:
typedef struct packet_add_char2
{
	BYTE		header;
	[...]
#ifdef ENABLE_SHOW_LIDER_AND_GENERAL_GUILD
	BYTE		dwNewIsGuildName;
#endif
} TPacketGCCharacterAdd2;

//find:
typedef struct packet_update_char
{
	BYTE		header;
	DWORD	   dwVID;
	[...]
	DWORD		dwMountVnum;
#ifdef ENABLE_SHOW_LIDER_AND_GENERAL_GUILD
	BYTE		dwNewIsGuildName;
#endif
} TPacketGCCharacterUpdate;

//Find:
typedef struct packet_update_char2
{
	BYTE		header;
	DWORD	   dwVID;
	[...]
#ifdef ENABLE_SHOW_LIDER_AND_GENERAL_GUILD
	BYTE		dwNewIsGuildName;
#endif
} TPacketGCCharacterUpdate2;
