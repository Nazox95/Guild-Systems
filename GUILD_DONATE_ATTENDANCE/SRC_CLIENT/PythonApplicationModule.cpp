//Open PythonApplicationModule.cpp and add:
#ifdef ENABLE_GUILD_DONATE_ATTENDANCE
		PyModule_AddIntConstant(poModule, "ENABLE_GUILD_DONATE_ATTENDANCE", true);
#else
		PyModule_AddIntConstant(poModule, "ENABLE_GUILD_DONATE_ATTENDANCE", false);
#endif
