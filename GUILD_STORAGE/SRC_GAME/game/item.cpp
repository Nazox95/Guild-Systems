//Open item.cpp find
LPITEM CItem::RemoveFromCharacter()
{
	if (!m_pOwner)
	{
		sys_err("Item::RemoveFromCharacter owner null");
		return (this);
	}

	LPCHARACTER pOwner = m_pOwner;

	if (m_bEquipped)	// ÀåÂøµÇ¾ú´Â°¡?
	{
		Unequip();
		//pOwner->UpdatePacket();

		SetWindow(RESERVED_WINDOW);
		Save();
		return (this);
	}
	else
	{
//add
		if (GetWindow() != SAFEBOX && GetWindow() != MALL
#ifdef ENABLE_GUILDSTORAGE_SYSTEM
			&& GetWindow() != GUILDBANK
#endif
			)
			[....]
	}
}
