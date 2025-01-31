#ifdef ENABLE_SECOND_GUILDRENEWAL_SYSTEM
PyObject* playerSetParalysis(PyObject* poSelf, PyObject* poArgs)
{
	BOOL bState = 0;
	if (!PyTuple_GetInteger(poArgs, 0, &bState))
		return Py_BadArgument();

	CPythonPlayer::Instance().SetParalysis(bState);
	return Py_BuildNone();
}
#endif

//Now add in void init
#ifdef ENABLE_SECOND_GUILDRENEWAL_SYSTEM
		{ "SetParalysis",		playerSetParalysis,		METH_VARARGS },
#endif
