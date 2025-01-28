//Open PythonApplicationModule.cpp and add:
#ifdef ENABLE_GUILDBANK_LOG
		PyModule_AddIntConstant(poModule, "ENABLE_GUILDBANK_LOG", true);
#else
		PyModule_AddIntConstant(poModule, "ENABLE_GUILDBANK_LOG", false);
#endif
