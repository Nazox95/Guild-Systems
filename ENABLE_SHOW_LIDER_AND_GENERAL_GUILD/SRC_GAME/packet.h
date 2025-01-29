//Open packet.h add:
#include "../../common/service.h"

//Find and replace:
typedef struct packet_char_additional_info
{
	BYTE    header;
	DWORD   dwVID;
	char    name[CHARACTER_NAME_MAX_LEN + 1];
	WORD    awPart[CHR_EQUIPPART_NUM];
	BYTE	bEmpire;
	DWORD   dwGuildID;
	DWORD   dwLevel;
	short	sAlignment;
	BYTE	bPKMode;
	DWORD	dwMountVnum;
#ifdef ENABLE_SHOW_LIDER_AND_GENERAL_GUILD
	BYTE	dwNewIsGuildName;
#endif	
} TPacketGCCharacterAdditionalInfo;

//Find and replace:
typedef struct packet_update_char
{
	BYTE	header;
	DWORD	dwVID;

	WORD        awPart[CHR_EQUIPPART_NUM];
	BYTE	bMovingSpeed;
	BYTE	bAttackSpeed;

	BYTE	bStateFlag;
	DWORD	dwAffectFlag[2];

	DWORD	dwGuildID;
	short	sAlignment;
	#ifdef ENABLE_NEW_PET_SYSTEM
	DWORD	dwLevel;
	#endif
	BYTE	bPKMode;
	DWORD	dwMountVnum;
	//WORD	wRaceNum;
#ifdef ENABLE_SHOW_LIDER_AND_GENERAL_GUILD
	BYTE	dwNewIsGuildName;
#endif	
} TPacketGCCharacterUpdate;
