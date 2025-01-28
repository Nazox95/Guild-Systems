//Search inside this function:
PyObject * guildGetGuildExperience(PyObject * poSelf, PyObject * poArgs)
[....]
int GULID_MAX_LEVEL = 20; //old
[...]
  
//Now Replace function with:
#if defined(ENABLE_EXTENDED_GUILD_LEVEL)
	int GULID_MAX_LEVEL = 40; //New
#else
	int GULID_MAX_LEVEL = 20; //old
#endif
