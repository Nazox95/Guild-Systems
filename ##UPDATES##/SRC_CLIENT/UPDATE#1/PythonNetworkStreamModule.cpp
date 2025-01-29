//Open PythonNetworStreamModule.cpp find
PyObject* netSendGuildRemoveMemberPacket(PyObject* poSelf, PyObject* poArgs)
{
	char * szKey;
	if (!PyTuple_GetString(poArgs, 0, &szKey))
		return Py_BuildException();

	CPythonGuild::TGuildMemberData * pGuildMemberData;
	if (!CPythonGuild::Instance().GetMemberDataPtrByName(szKey, &pGuildMemberData))
	{
		TraceError("netSendGuildRemoveMemberPacket(szKey=%s) - Can't Find Guild Member\n", szKey);
		return Py_BuildNone();
	}

	CPythonNetworkStream& rns=CPythonNetworkStream::Instance();
	rns.SendGuildRemoveMemberPacket(pGuildMemberData->dwPID);

	return Py_BuildNone();
}
//Add
#if defined(ENABLE_GUILDRENEWAL_SYSTEM) && defined(ENABLE_EXTENDED_RENEWAL_FEATURES)
PyObject* netSendGuildVoteMemberOut(PyObject* poSelf, PyObject* poArgs)
{
	char* szKey;
	if (!PyTuple_GetString(poArgs, 0, &szKey))
		return Py_BuildException();

	CPythonGuild::TGuildMemberData* pGuildMemberData;
	if (!CPythonGuild::Instance().GetMemberDataPtrByName(szKey, &pGuildMemberData))
	{
		TraceError("netSendGuildRemoveMemberPacket(szKey=%s) - Can't Find Guild Member\n", szKey);
		return Py_BuildNone();
	}

	CPythonNetworkStream& rns = CPythonNetworkStream::Instance();
	rns.SendGuildRemoveMemberPacket(pGuildMemberData->dwPID);

	return Py_BuildNone();
}

PyObject* netSendGuildVoteChangeMaster(PyObject* poSelf, PyObject* poArgs)
{
	char* szKey;
	if (!PyTuple_GetString(poArgs, 0, &szKey))
		return Py_BuildException();

	CPythonGuild::TGuildMemberData* pGuildMemberData;
	if (!CPythonGuild::Instance().GetMemberDataPtrByName(szKey, &pGuildMemberData))
	{
		TraceError("netSendGuildVoteChangeMaster(szKey=%s) - Can't Find Guild Member\n", szKey);
		return Py_BuildNone();
	}

	CPythonNetworkStream& rns = CPythonNetworkStream::Instance();
	rns.SendGuildVoteChangeMaster(pGuildMemberData->dwPID);

	return Py_BuildNone();
}

PyObject* netSendGuildVoteLandAbndon(PyObject* poSelf, PyObject* poArgs)
{
	int iVID;
	if (!PyTuple_GetInteger(poArgs, 0, &iVID))
		return Py_BuildException();

	CPythonNetworkStream& rns = CPythonNetworkStream::Instance();
	rns.SendGuildVoteLandAbndon(iVID);

	return Py_BuildNone();
}
#endif
//find
		// Guild
		{ "SendAnswerMakeGuildPacket",				netSendAnswerMakeGuildPacket,				METH_VARARGS },
		{ "SendQuestInputStringPacket",				netSendQuestInputStringPacket,				METH_VARARGS },
		{ "SendQuestConfirmPacket",					netSendQuestConfirmPacket,					METH_VARARGS },
		{ "SendGuildAddMemberPacket",				netSendGuildAddMemberPacket,				METH_VARARGS },
		{ "SendGuildRemoveMemberPacket",			netSendGuildRemoveMemberPacket,				METH_VARARGS },
//add
#if defined(ENABLE_GUILDRENEWAL_SYSTEM) && defined(ENABLE_EXTENDED_RENEWAL_FEATURES)
		{ "SendGuildVoteMemberOut",					netSendGuildVoteMemberOut,					METH_VARARGS },
		{ "SendGuildVoteChangeMaster",				netSendGuildVoteChangeMaster,				METH_VARARGS },
		{ "SendGuildVoteLandAbndon",				netSendGuildVoteLandAbndon,					METH_VARARGS },
#endif
