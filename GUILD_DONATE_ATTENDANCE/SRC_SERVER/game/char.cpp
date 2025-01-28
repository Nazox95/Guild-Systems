//Open Char.cpp find:
void CHARACTER::Initialize()
{
	CEntity::Initialize(ENTITY_CHARACTER);

	m_bNoOpenedShop = true;

	m_bOpeningSafebox = false;
	[...]
//in the end of this function add:
#ifdef ENABLE_GUILD_DONATE_ATTENDANCE
	m_dwLastOfferNewExpTime = 0;
#endif
//before this
}
