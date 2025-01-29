//Open main.cpp find 
	MessengerManager::instance().Initialize();
	CGuildManager::instance().Initialize();
	fishing::Initialize();
	OXEvent_manager.Initialize();
	if (speed_server)
		CSpeedServerManager::instance().Initialize();

	Cube_init();
	Blend_Item_init();
	ani_init();
	PanamaLoad();
//add
#ifdef ENABLE_GUILDSTORAGE_SYSTEM
	if (!g_bAuthServer)
	{
		guild_manager.InitializeDonate();
	}
#endif
