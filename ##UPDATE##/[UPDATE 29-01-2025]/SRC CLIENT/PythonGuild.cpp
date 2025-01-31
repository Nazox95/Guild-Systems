//Open PythonGuild.cpp find
	PyObject * poModule = Py_InitModule("guild", s_methods);
	PyModule_AddIntConstant(poModule, "AUTH_ADD_MEMBER", GUILD_AUTH_ADD_MEMBER);
	PyModule_AddIntConstant(poModule, "AUTH_REMOVE_MEMBER", GUILD_AUTH_REMOVE_MEMBER);
	PyModule_AddIntConstant(poModule, "AUTH_NOTICE", GUILD_AUTH_NOTICE);
	PyModule_AddIntConstant(poModule, "AUTH_SKILL", GUILD_AUTH_SKILL);
//add
#ifdef ENABLE_GUILDRENEWAL_SYSTEM
	PyModule_AddIntConstant(poModule, "AUTH_WAR", GUILD_AUTH_WAR);
	PyModule_AddIntConstant(poModule, "AUTH_BANK", GUILD_AUTH_BANK);
#endif
	PyModule_AddIntConstant(poModule, "ENEMY_GUILD_SLOT_MAX_COUNT", CPythonGuild::ENEMY_GUILD_SLOT_MAX_COUNT);
}
