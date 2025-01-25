#ifdef ENABLE_GUILD_LAND_INFO
		PyModule_AddIntConstant(poModule, "ENABLE_GUILD_LAND_INFO", true);
#else
		PyModule_AddIntConstant(poModule, "ENABLE_GUILD_LAND_INFO", false);
#endif
---------
