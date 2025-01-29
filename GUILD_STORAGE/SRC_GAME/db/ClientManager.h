//Open ClientManager.h add
#include <unordered_map>
#include <chrono>
#include <unordered_set>
#include <algorithm>
#include <cstring>
#include "../../common/stl.h"
#include "../../common/building.h"
#include "../../common/auction_table.h"
#include "../../common/tables.h"
#include "../../common/service.h"
#include "buffer_manager.h"

#include "Peer.h"
#include "DBManager.h"
#include "LoginData.h"

//find 
	void		QUERY_QUEST_SAVE(CPeer * pkPeer, TQuestTable *, DWORD dwLen);
	void		QUERY_ADD_AFFECT(CPeer * pkPeer, TPacketGDAddAffect * p);
	void		QUERY_REMOVE_AFFECT(CPeer * pkPeer, TPacketGDRemoveAffect * p);
//replace
#ifdef ENABLE_GUILDSTORAGE_SYSTEM
	void		QUERY_SAFEBOX_LOAD(CPeer* pkPeer, DWORD dwHandle, const TSafeboxLoadPacket*, int bMall);
#else
	void		QUERY_SAFEBOX_LOAD(CPeer* pkPeer, DWORD dwHandle, const TSafeboxLoadPacket*, bool bMall);
#endif
//find
	void		QUERY_SAFEBOX_SAVE(CPeer * pkPeer, TSafeboxTable * pTable);
	void		QUERY_SAFEBOX_CHANGE_SIZE(CPeer * pkPeer, DWORD dwHandle, TSafeboxChangeSizePacket * p);
//add
#ifdef ENABLE_GUILDSTORAGE_SYSTEM
	void		QUERY_GUILDSTORAGE_CHANGE_SIZE(CPeer* pkPeer, DWORD dwHandle, TGuildstorageChangeSizePacket* p);
#endif
//find
	void		QUERY_SAFEBOX_CHANGE_PASSWORD(CPeer * pkPeer, DWORD dwHandle, TSafeboxChangePasswordPacket * p);
//add
#if defined(__BL_MOVE_CHANNEL__)
	void		QUERY_MOVE_CHANNEL(CPeer* pkPeer, DWORD dwHandle, TMoveChannel*);
#endif
//find
	void		RESULT_SAFEBOX_LOAD(CPeer * pkPeer, SQLMsg * msg);
	void		RESULT_SAFEBOX_CHANGE_SIZE(CPeer * pkPeer, SQLMsg * msg);
//add
#ifdef ENABLE_GUILDSTORAGE_SYSTEM
	void		RESULT_GUILDSTORAGE_CHANGE_SIZE(CPeer* pkPeer, SQLMsg* msg);
#endif
