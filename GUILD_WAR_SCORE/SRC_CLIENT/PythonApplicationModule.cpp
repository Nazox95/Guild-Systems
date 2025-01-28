//Open PythonApplicationModule.cpp add
#ifdef ENABLE_GUILD_WAR_SCORE
		PyModule_AddIntConstant(poModule, "ENABLE_GUILD_WAR_SCORE", true);
#else
		PyModule_AddIntConstant(poModule, "ENABLE_GUILD_WAR_SCORE", false);
#endif
