//Open PythonNetworkStreamModule.cpp and add before:
void initnet()
//
#ifdef ENABLE_GUILD_DONATE_ATTENDANCE
PyObject* netGuildDonateInfoOpen(PyObject* poSelf, PyObject* poArgs)
{
	CPythonNetworkStream& rkNetStream = CPythonNetworkStream::Instance();
	rkNetStream.GuildDonateInfoOpen();

	return Py_BuildNone();
}
#endif

//Now add in 
void initnet()
//
#ifdef ENABLE_GUILD_DONATE_ATTENDANCE
		{ "GuildDonateInfoOpen",					netGuildDonateInfoOpen,					METH_VARARGS },
#endif
