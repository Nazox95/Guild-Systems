//Open PythonGuild.cpp check if you have for the other systems, if you don't have add:
#ifdef ENABLE_GUILDRENEWAL_SYSTEM
PyObject* guildGetWarRecode(PyObject* poSelf, PyObject* poArgs)
{
#ifdef ENABLE_GUILD_WAR_SCORE
	int index;

	if (!PyTuple_GetInteger(poArgs, 0, &index))
		return Py_BuildException();

	CPythonGuild::TGuildInfo& rGuildInfo = CPythonGuild::Instance().GetGuildInfoRef();
	int win = rGuildInfo.winTypes[index];
	int lose = rGuildInfo.lossTypes[index];
	int draw = rGuildInfo.drawTypes[index];

	int all = draw + lose + win;

	return Py_BuildValue("iiii", win, lose, draw, all);
#else
	return Py_BuildValue("iiii", 0, 0, 0, 0);
#endif
}

PyObject* guildGetGuildLadderRanking(PyObject* poSelf, PyObject* poArgs)
{
#ifdef ENABLE_GUILD_WAR_SCORE
	CPythonGuild::TGuildInfo& rGuildInfo = CPythonGuild::Instance().GetGuildInfoRef();
	int ladder = rGuildInfo.ladderPoints;
	int ranking = rGuildInfo.rank;

	return Py_BuildValue("ii", ladder, ranking);
#else
	return Py_BuildValue("ii", 0, 0);
#endif
}

PyObject* guildGetBaseInfoBankGold(PyObject* poSelf, PyObject* poArgs)
{
	CPythonGuild::TGuildInfo& rGuildInfo = CPythonGuild::Instance().GetGuildInfoRef();
#if defined(ENABLE_GUILDRENEWAL_SYSTEM) && defined(ENABLE_GUILDSTORAGE_SYSTEM)
	return Py_BuildValue("iss", rGuildInfo.dwGuildMoney, rGuildInfo.goldCheckout, rGuildInfo.itemCheckout);
#else
	return Py_BuildValue("iss", rGuildInfo.dwGuildMoney, " ", " ");
#endif
}

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
#endif

//Chekf if you have for the others systems, if you don't a dd in
void initguild()
//
#ifdef ENABLE_GUILD_DONATE_ATTENDANCE
		{ "GetWarRecode",					guildGetWarRecode,					METH_VARARGS },
		{ "GetGuildLadderRanking",			guildGetGuildLadderRanking,			METH_VARARGS },
		{ "GetBaseInfoBankGold",			guildGetBaseInfoBankGold,			METH_VARARGS },
		{ "GetBaseInfo",					guildGetBaseInfo,					METH_VARARGS },
		{ "GetGuildBankInfoSize",			guildGetGuildBankInfoSize,			METH_VARARGS },
		{ "GetGuildBankInfoData",			guildGetGuildBankInfoData,			METH_VARARGS },
		{ "GetbuildingInfo",				guildGetbuildingInfo,				METH_VARARGS },
		{ "GetGuildDonateStats",			guildGetGuildDonateStats,			METH_VARARGS },
		{ "GetGuildDonateCount",			guildGetGuildDonateCount,			METH_VARARGS },
#endif
