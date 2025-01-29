//Open PythonNetworkStreamModule.cpp add
#ifdef ENABLE_GUILDSTORAGE_SYSTEM
PyObject* netSendGuildstorageCheckinPacket(PyObject* poSelf, PyObject* poArgs)
{
	TItemPos InventoryPos;
	int iGuildstoragePos;

	switch (PyTuple_Size(poArgs))
	{
	case 2:
		InventoryPos.window_type = INVENTORY;
		if (!PyTuple_GetInteger(poArgs, 0, &InventoryPos.cell))
			return Py_BuildException();
		if (!PyTuple_GetInteger(poArgs, 1, &iGuildstoragePos))
			return Py_BuildException();
		break;

	case 3:
		if (!PyTuple_GetInteger(poArgs, 0, &InventoryPos.window_type))
			return Py_BuildException();
		if (!PyTuple_GetInteger(poArgs, 1, &InventoryPos.cell))
			return Py_BuildException();
		if (!PyTuple_GetInteger(poArgs, 2, &iGuildstoragePos))
			return Py_BuildException();
		break;
	}

	CPythonNetworkStream& rns = CPythonNetworkStream::Instance();
	rns.SendGuildstorageCheckinPacket(InventoryPos, iGuildstoragePos);

	return Py_BuildNone();
}

PyObject* netSendGuildstorageCheckoutPacket(PyObject* poSelf, PyObject* poArgs)
{
	int iGuildstoragePos = 0;
	TItemPos InventoryPos;

	switch (PyTuple_Size(poArgs))
	{
	case 2:
		if (!PyTuple_GetInteger(poArgs, 0, &iGuildstoragePos))
			return Py_BuildException();
		if (!PyTuple_GetInteger(poArgs, 1, &InventoryPos.cell))
			return Py_BuildException();
		break;

	case 3:
		if (!PyTuple_GetInteger(poArgs, 0, &iGuildstoragePos))
			return Py_BuildException();
		if (!PyTuple_GetInteger(poArgs, 1, &InventoryPos.window_type))
			return Py_BuildException();
		if (!PyTuple_GetInteger(poArgs, 2, &InventoryPos.cell))
			return Py_BuildException();
		break;

	default:
		return Py_BuildException();
	}
	CPythonNetworkStream& rns = CPythonNetworkStream::Instance();
	rns.SendGuildstorageCheckoutPacket(iGuildstoragePos, InventoryPos);

	return Py_BuildNone();
}

PyObject* netSendGuildBankMove(PyObject* poSelf, PyObject* poArgs)
{
	int iSourcePos;
	if (!PyTuple_GetInteger(poArgs, 0, &iSourcePos))
		return Py_BuildException();
	int iTargetPos;
	if (!PyTuple_GetInteger(poArgs, 1, &iTargetPos))
		return Py_BuildException();
	int iCount;
	if (!PyTuple_GetInteger(poArgs, 2, &iCount))
		return Py_BuildException();

	CPythonNetworkStream& rns = CPythonNetworkStream::Instance();
	rns.SendSafeBoxItemMovePacket(iSourcePos, iTargetPos, iCount);

	return Py_BuildNone();
}
#endif

//find
		// Mall
		{ "SendMallCheckoutPacket",				netSendMallCheckoutPacket,				METH_VARARGS },
//add
#ifdef ENABLE_GUILDSTORAGE_SYSTEM
		{ "SendGuildstorageCheckinPacket",		netSendGuildstorageCheckinPacket,		METH_VARARGS },
		{ "SendGuildstorageCheckoutPacket",		netSendGuildstorageCheckoutPacket,		METH_VARARGS },
		{ "SendGuildBankMove",					netSendGuildBankMove,					METH_VARARGS },
#endif
