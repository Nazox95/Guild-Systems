//Open char_battle.cpp find
	CShopManager::instance().StopShopping(this);
	CloseMyShop();
	CloseSafebox();
//add
#ifdef ENABLE_GUILDSTORAGE_SYSTEM
	CloseGuildstorage();
#endif
	
	if (true == IsMonster() && 2493 == GetMobTable().dwVnum)
	{
		if (NULL != pkKiller && NULL != pkKiller->GetGuild())
		{
			CDragonLairManager::instance().OnDragonDead( this, pkKiller->GetGuild()->GetID() );
		}
		else
		{
			sys_err("DragonLair: Dragon killed by nobody");
		}
	}
}
