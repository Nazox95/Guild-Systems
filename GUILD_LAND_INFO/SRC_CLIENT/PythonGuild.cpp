//open PythonGuild.cpp before:
void initguild()
//create macro:
#ifdef ENABLE_GUILDRENEWAL_SYSTEM
#endif

//and add in this macro:
PyObject* guildGetBaseInfo(PyObject* poSelf, PyObject* poArgs)
{
#ifdef ENABLE_GUILD_LAND_INFO
	CPythonGuild::TGuildInfo& rGuildInfo = CPythonGuild::Instance().GetGuildInfoRef();
	return Py_BuildValue("i", rGuildInfo.mindex);
#else
	return Py_BuildValue("i", 0);
#endif
}

PyObject* guildGetbuildingInfo(PyObject* poSelf, PyObject* poArgs)
{
#ifdef ENABLE_GUILD_LAND_INFO
	CPythonGuild::TGuildInfo& rGuildInfo = CPythonGuild::Instance().GetGuildInfoRef();
	return Py_BuildValue("iiii", rGuildInfo.guildAltar, rGuildInfo.guildAlchemist, rGuildInfo.guildBlacksmith, rGuildInfo.storage_lv);
#else
	return Py_BuildValue("iiii", 0, 0, 0, 0);
#endif
}
