//Open PythonPlayerModule.cpp find
	PyModule_AddIntConstant(poModule, "SLOT_TYPE_EMOTION",					SLOT_TYPE_EMOTION);
	PyModule_AddIntConstant(poModule, "SLOT_TYPE_DRAGON_SOUL_INVENTORY",	SLOT_TYPE_DRAGON_SOUL_INVENTORY);
//add
#ifdef ENABLE_GUILDSTORAGE_SYSTEM
	PyModule_AddIntConstant(poModule, "SLOT_TYPE_GUILDBANK", SLOT_TYPE_GUILDBANK);
#endif
