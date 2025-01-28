//Open PythonNetworkStreamModule.cpp and add before:
void initnet()
//
#ifdef ENABLE_GUILDBANK_LOG
PyObject* netGuildBankInfoOpen(PyObject* poSelf, PyObject* poArgs)
{
	CPythonNetworkStream& rkNetStream = CPythonNetworkStream::Instance();
	rkNetStream.GuildBankInfoOpen();

	return Py_BuildNone();
}

PyObject* netSendGuildBankInfoOpen(PyObject* poSelf, PyObject* poArgs)
{
	CPythonNetworkStream& rkNetStream = CPythonNetworkStream::Instance();
	rkNetStream.SendGuildBankInfoOpen();

	return Py_BuildNone();
}
#endif

//Now add in 
void initnet()
//
#ifdef ENABLE_GUILDBANK_LOG
		{ "GuildBankInfoOpen",						netGuildBankInfoOpen,						METH_VARARGS },
		{ "SendGuildBankInfoOpen",					netSendGuildBankInfoOpen,					METH_VARARGS },
#endif
