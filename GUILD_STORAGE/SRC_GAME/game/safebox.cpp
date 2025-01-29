//Open safebox.cpp find 
bool CSafebox::Add(DWORD dwPos, LPITEM pkItem)
{
	if (!pkItem)
		return false;
	
	if (!IsValidPosition(dwPos))
	{
		sys_err("SAFEBOX: item on wrong position at %d (size of grid = %d)", dwPos, m_pkGrid->GetSize());
		return false;
	}

	pkItem->SetWindow(m_bWindowMode);
	pkItem->SetCell(m_pkChrOwner, dwPos);
	pkItem->Save(); // °­Á¦·Î Save¸¦ ºÒ·¯Áà¾ß ÇÑ´Ù.
	ITEM_MANAGER::instance().FlushDelayedSave(pkItem);

	m_pkGrid->Put(dwPos, 1, pkItem->GetSize());
	m_pkItems[dwPos] = pkItem;

	TPacketGCItemSet pack;
//replace
#ifdef ENABLE_GUILDSTORAGE_SYSTEM
	if (m_bWindowMode == SAFEBOX)
		pack.header = HEADER_GC_SAFEBOX_SET;
	else if(m_bWindowMode == GUILDBANK)
		pack.header = HEADER_GC_GUILDSTORAGE_SET;
	else 
		pack.header = HEADER_GC_MALL_SET;
#else
	pack.header = m_bWindowMode == SAFEBOX ? HEADER_GC_SAFEBOX_SET : HEADER_GC_MALL_SET;
#endif

//find
LPITEM CSafebox::Remove(DWORD dwPos)
{
	LPITEM pkItem = Get(dwPos);

	if (!pkItem)
		return nullptr;

	if (!m_pkGrid)
		sys_err("Safebox::Remove : nil grid");
	else
		m_pkGrid->Get(dwPos, 1, pkItem->GetSize());

	pkItem->RemoveFromCharacter();

	m_pkItems[dwPos] = nullptr;

	TPacketGCItemDel pack;
//replace
#ifdef ENABLE_GUILDSTORAGE_SYSTEM
	if (m_bWindowMode == SAFEBOX)
		pack.header = HEADER_GC_SAFEBOX_DEL;
	else if(m_bWindowMode == GUILDBANK)
		pack.header = HEADER_GC_GUILDSTORAGE_DEL;
	else 
		pack.header = HEADER_GC_MALL_DEL;
#else
	pack.header = m_bWindowMode == SAFEBOX ? HEADER_GC_SAFEBOX_DEL : HEADER_GC_MALL_DEL;
#endif
