//Open PythonApplicationModule.cpp and add (if you don't have)
#ifdef ENABLE_GUILDRENEWAL_SYSTEM
PyModule_AddIntConstant(poModule, "ENABLE_GUILDRENEWAL_SYSTEM", true);
#else
PyModule_AddIntConstant(poModule, "ENABLE_GUILDRENEWAL_SYSTEM", false);
#endif
