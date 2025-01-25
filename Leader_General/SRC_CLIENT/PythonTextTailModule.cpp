//Open PythonTextTailModule.cpp replace this function:
PyObject* textTailRegisterCharacterTextTail(PyObject* poSelf, PyObject* poArgs)
{
	int iGuildID;
	if (!PyTuple_GetInteger(poArgs, 0, &iGuildID))
		return Py_BuildException();
#ifdef ENABLE_SHOW_LIDER_AND_GENERAL_GUILD
	int iNewIsGuildName;
	if (!PyTuple_GetInteger(poArgs, 1, &iNewIsGuildName))
		return Py_BuildException();
	int iVirtualID;
	if (!PyTuple_GetInteger(poArgs, 2, &iVirtualID))
		return Py_BuildException();
#else
	int iVirtualID;
	if (!PyTuple_GetInteger(poArgs, 1, &iVirtualID))
		return Py_BuildException();
#endif

#ifdef ENABLE_SHOW_LIDER_AND_GENERAL_GUILD
	CPythonTextTail::Instance().RegisterCharacterTextTail(iGuildID, iVirtualID, iNewIsGuildName, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
#else
	CPythonTextTail::Instance().RegisterCharacterTextTail(iGuildID, iVirtualID, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
#endif
	return Py_BuildNone();
}
