//Open cmd_general.cpp find all if (ch->IsObserverMode() || ch->GetExchange() (or you have) andd include 
#	ifdef ENABLE_GUILDSTORAGE_SYSTEM
		|| ch->IsOpenGuildstorage()
#	endif
//e.j:
	if (ch->IsObserverMode() || ch->GetExchange() || ch->IsOpenSafebox() || ch->GetShopOwner() || ch->IsCubeOpen() || ch->GetMyShop()
#	ifdef ENABLE_GUILDSTORAGE_SYSTEM
		|| ch->IsOpenGuildstorage()
#	endif
		)
		return;

//add in the end 
#ifdef ENABLE_GUILDSTORAGE_SYSTEM
ACMD(do_click_guildstorage)
{
	ch->SetGuildstorageOpenPosition();
	ch->ReqGuildstorageLoad();
}

ACMD(do_guildstorage_close)
{
	if (ch->GetGuildstorage())
	{
		CGuild* pGuild = ch->GetGuild();
		if (!pGuild) {
			return;// no guild ptr fix
		}

		ch->CloseGuildstorage();
		ch->Save();
		pGuild->SetStorageState(false, 0);
	}
}

ACMD(do_update_guildstorage)
{
	CGuild* pGuild = ch->GetGuild();
	pGuild->SetGuildstorage(1);
}
#endif
