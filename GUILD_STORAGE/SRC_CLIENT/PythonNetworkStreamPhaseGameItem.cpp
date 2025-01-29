//Open PythonNetworkStreamPhaseGameItem.cpp add
#ifdef ENABLE_GUILDSTORAGE_SYSTEM
#	include "PythonGuildBank.h"
#endif

//find
bool CPythonNetworkStream::SendSafeBoxItemMovePacket(BYTE bySourcePos, BYTE byTargetPos, BYTE byCount)
{
//add
#ifdef ENABLE_GUILDSTORAGE_SYSTEM
	if (byCount != 2)
		__PlaySafeBoxItemDropSound(bySourcePos);
#else
	__PlaySafeBoxItemDropSound(bySourcePos);
#endif

	TPacketCGItemMove kItemMove;
	kItemMove.header = HEADER_CG_SAFEBOX_ITEM_MOVE;
	kItemMove.pos = TItemPos(INVENTORY, bySourcePos);
	kItemMove.num = byCount;
	kItemMove.change_pos = TItemPos(INVENTORY, byTargetPos);
	if (!Send(sizeof(kItemMove), &kItemMove))
		return false;

	return SendSequence();
}

//find
// Item
// Recieve
bool CPythonNetworkStream::RecvItemSetPacket()
//add before
#ifdef ENABLE_GUILDSTORAGE_SYSTEM
bool CPythonNetworkStream::SendGuildstorageCheckinPacket(TItemPos InventoryPos, BYTE byGuildstoragePos)
{
	__PlayInventoryItemDropSound(InventoryPos);

	TPacketCGGuildstorageCheckin kGuildstorageCheckin;
	kGuildstorageCheckin.bHeader = HEADER_CG_GUILDSTORAGE_CHECKIN;
	kGuildstorageCheckin.ItemPos = InventoryPos;
	kGuildstorageCheckin.bSafePos = byGuildstoragePos;
	if (!Send(sizeof(kGuildstorageCheckin), &kGuildstorageCheckin))
		return false;

	return SendSequence();
}

bool CPythonNetworkStream::SendGuildstorageCheckoutPacket(BYTE byGuildstoragePos, TItemPos InventoryPos)
{
	__PlayGuildstorageItemDropSound(byGuildstoragePos);

	TPacketCGGuildstorageCheckout kGuildstorageCheckoutPacket;
	kGuildstorageCheckoutPacket.bHeader = HEADER_CG_GUILDSTORAGE_CHECKOUT;
	kGuildstorageCheckoutPacket.bGuildstoragePos = byGuildstoragePos;
	kGuildstorageCheckoutPacket.ItemPos = InventoryPos;
	if (!Send(sizeof(kGuildstorageCheckoutPacket), &kGuildstorageCheckoutPacket))
		return false;

	return SendSequence();
}

bool CPythonNetworkStream::RecvGuildstorageOpenPacket()
{
	TPacketGCGuildstorageOpen kGuildstorageOpen;
	if (!Recv(sizeof(kGuildstorageOpen), &kGuildstorageOpen))
		return false;

	CPythonGuildBank::Instance().OpenGuildBank(kGuildstorageOpen.bSize);
	PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "OpenGuildstorageWindow", Py_BuildValue("(i)", kGuildstorageOpen.bSize));

	return true;
}

bool CPythonNetworkStream::RecvGuildstorageItemSetPacket()
{
	TPacketGCItemSet2 kItemSet;
	if (!Recv(sizeof(kItemSet), &kItemSet))
		return false;

	TItemData kItemData;
	kItemData.vnum = kItemSet.vnum;
	kItemData.count = kItemSet.count;
	kItemData.flags = kItemSet.flags;
	kItemData.anti_flags = kItemSet.anti_flags;

	for (int isocket = 0; isocket < ITEM_SOCKET_SLOT_MAX_NUM; ++isocket)
		kItemData.alSockets[isocket] = kItemSet.alSockets[isocket];
	for (int iattr = 0; iattr < ITEM_ATTRIBUTE_SLOT_MAX_NUM; ++iattr)
		kItemData.aAttr[iattr] = kItemSet.aAttr[iattr];

	CPythonGuildBank::Instance().SetGuildBankItemData(kItemSet.Cell.cell, kItemData);

	__RefreshGuildstorageWindow();

	return true;
}

bool CPythonNetworkStream::RecvGuildstorageItemDelPacket()
{
	TPacketGCItemDel kItemDel;
	if (!Recv(sizeof(kItemDel), &kItemDel))
		return false;

	CPythonGuildBank::Instance().DelGuildBankItemData(kItemDel.pos);

	__RefreshGuildstorageWindow();
	Tracef(" >> CPythonNetworkStream::RecvGuildstorageItemDelPacket\n");

	return true;
}
#endif

//find
void CPythonNetworkStream::__PlayMallItemDropSound(UINT uSlotPos)
{
	DWORD dwItemID;
	CPythonSafeBox& rkSafeBox=CPythonSafeBox::Instance();
	if (!rkSafeBox.GetSlotMallItemID(uSlotPos, &dwItemID))
		return;

	CPythonItem& rkItem=CPythonItem::Instance();
	rkItem.PlayDropSound(dwItemID);
}
//add
#ifdef ENABLE_GUILDSTORAGE_SYSTEM
void CPythonNetworkStream::__PlayGuildstorageItemDropSound(DWORD uSlotPos)
{
	DWORD dwItemID;
	CPythonGuildBank& rkSafeBox = CPythonGuildBank::Instance();
	if (!rkSafeBox.GetSlotGuildBankItemID(uSlotPos, &dwItemID))
		return;

	CPythonItem& rkItem = CPythonItem::Instance();
	rkItem.PlayDropSound(dwItemID);
}
#endif
