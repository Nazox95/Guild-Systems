//Open PythonApplicationModule.cpp and add
#ifdef ENABLE_GUILDSTORAGE_SYSTEM
		PyModule_AddIntConstant(poModule, "ENABLE_GUILDSTORAGE_SYSTEM", true);
#else
		PyModule_AddIntConstant(poModule, "ENABLE_GUILDSTORAGE_SYSTEM", false);
#endif
