//Open PythonGuild.cpp add before
void initguild()
//
#ifdef ENABLE_GUILD_DONATE_ATTENDANCE
PyObject* guildGetGuildDonateStats(PyObject* poSelf, PyObject* poArgs)
{
	int normal_donate = 3;
	int normal_exp = 1000;

	int middle_donate = 10;
	int middle_exp = 10000;

	int high_donate = 30;
	int high_exp = 30000;

	return Py_BuildValue("iiiiii", normal_donate, normal_exp, middle_donate, middle_exp, high_donate, high_exp);
}

PyObject* guildGetGuildDonateCount(PyObject* poSelf, PyObject* poArgs)
{
	int donate_max = 3;

	CPythonGuild::TGuildInfo& rGuildInfo = CPythonGuild::Instance().GetGuildInfoRef();
	return Py_BuildValue("ii", rGuildInfo.bDonateCount, donate_max);
}
#endif
//Now, add in
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
