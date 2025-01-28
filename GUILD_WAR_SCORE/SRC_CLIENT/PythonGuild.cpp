//Open  PythonGuild.cpp add before
void initguild()
//
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
