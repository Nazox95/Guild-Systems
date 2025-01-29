//Add to project in UserInterface
#include "StdAfx.h"
#include "PythonGuildBank.h"

CPythonGuildBank::CPythonGuildBank() {}
CPythonGuildBank::~CPythonGuildBank() = default;

#ifdef ENABLE_GUILDSTORAGE_SYSTEM
void CPythonGuildBank::OpenGuildBank(int iSize)
{
	if (m_GuildBankItemInstanceVector.size())
		m_GuildBankItemInstanceVector.clear();

	m_GuildBankItemInstanceVector.resize(GUILDBANK_SLOT_X_COUNT * iSize);

	for (DWORD i = 0; i < m_GuildBankItemInstanceVector.size(); ++i)
	{
		TItemData& rInstance = m_GuildBankItemInstanceVector[i];
		ZeroMemory(&rInstance, sizeof(rInstance));
	}
}

void CPythonGuildBank::SetGuildBankItemData(DWORD dwSlotIndex, const TItemData& rItemData)
{
	if (dwSlotIndex >= m_GuildBankItemInstanceVector.size())
	{
		TraceError("CPythonGuildBank::SetGuildBankItemData(dwSlotIndex=%d) - Strange slot index", dwSlotIndex);
		return;
	}

	m_GuildBankItemInstanceVector[dwSlotIndex] = rItemData;
}

void CPythonGuildBank::DelGuildBankItemData(DWORD dwSlotIndex)
{
	if (dwSlotIndex >= m_GuildBankItemInstanceVector.size())
	{
		TraceError("CPythonGuildBank::DelGuildBankItemData(dwSlotIndex=%d) - Strange slot index", dwSlotIndex);
		return;
	}

	TItemData& rInstance = m_GuildBankItemInstanceVector[dwSlotIndex];
	ZeroMemory(&rInstance, sizeof(rInstance));
}

BOOL CPythonGuildBank::GetGuildBankItemDataPtr(DWORD dwSlotIndex, TItemData** ppInstance)
{
	if (dwSlotIndex >= m_GuildBankItemInstanceVector.size())
	{
		TraceError("CPythonGuildBank::GetGuildBankSlotItemID(dwSlotIndex=%d) - Strange slot index", dwSlotIndex);
		return FALSE;
	}

	*ppInstance = &m_GuildBankItemInstanceVector[dwSlotIndex];

	return TRUE;
}

BOOL CPythonGuildBank::GetSlotGuildBankItemID(DWORD dwSlotIndex, DWORD* pdwItemID)
{
	if (dwSlotIndex >= m_GuildBankItemInstanceVector.size())
	{
		TraceError("CPythonGuildBank::GetGuildBankSlotItemID(dwSlotIndex=%d) - Strange slot index", dwSlotIndex);
		return FALSE;
	}

	*pdwItemID = m_GuildBankItemInstanceVector[dwSlotIndex].vnum;

	return TRUE;
}

DWORD CPythonGuildBank::GetGuildBankSize()
{
	return m_GuildBankItemInstanceVector.size();
}

PyObject* guildbankGetItemID(PyObject* poSelf, PyObject* poArgs)
{
	int ipos;
	if (!PyTuple_GetInteger(poArgs, 0, &ipos))
		return Py_BadArgument();

	TItemData* pInstance;
	if (!CPythonGuildBank::Instance().GetGuildBankItemDataPtr(ipos, &pInstance))
		return Py_BuildException();

	return Py_BuildValue("i", pInstance->vnum);
}

PyObject* guildbankGetGuildBankItemCount(PyObject* poSelf, PyObject* poArgs)
{
	int ipos;
	if (!PyTuple_GetInteger(poArgs, 0, &ipos))
		return Py_BadArgument();

	TItemData* pInstance;
	if (!CPythonGuildBank::Instance().GetGuildBankItemDataPtr(ipos, &pInstance))
		return Py_BuildException();

	return Py_BuildValue("i", pInstance->count);
}

PyObject* guildbankGetItemMetinSocket(PyObject* poSelf, PyObject* poArgs)
{
	int iSlotIndex;
	if (!PyTuple_GetInteger(poArgs, 0, &iSlotIndex))
		return Py_BadArgument();
	int iSocketIndex;
	if (!PyTuple_GetInteger(poArgs, 1, &iSocketIndex))
		return Py_BadArgument();

	if (iSocketIndex >= ITEM_SOCKET_SLOT_MAX_NUM)
		return Py_BuildException();

	TItemData* pItemData;
	if (!CPythonGuildBank::Instance().GetGuildBankItemDataPtr(iSlotIndex, &pItemData))
		return Py_BuildException();

	return Py_BuildValue("i", pItemData->alSockets[iSocketIndex]);
}

PyObject* guildbankGetItemAttribute(PyObject* poSelf, PyObject* poArgs)
{
	int iSlotIndex;
	if (!PyTuple_GetInteger(poArgs, 0, &iSlotIndex))
		return Py_BuildException();
	int iAttrSlotIndex;
	if (!PyTuple_GetInteger(poArgs, 1, &iAttrSlotIndex))
		return Py_BuildException();

	if (iAttrSlotIndex >= 0 && iAttrSlotIndex < ITEM_ATTRIBUTE_SLOT_MAX_NUM)
	{
		TItemData* pItemData;
		if (CPythonGuildBank::Instance().GetGuildBankItemDataPtr(iSlotIndex, &pItemData))
			return Py_BuildValue("ii", pItemData->aAttr[iAttrSlotIndex].bType, pItemData->aAttr[iAttrSlotIndex].sValue);
	}

	return Py_BuildValue("ii", 0, 0);
}

PyObject* guildbankGetGuildBankInfoSize(PyObject* poSelf, PyObject* poArgs)
{
	return Py_BuildValue("i", CPythonGuildBank::Instance().GetGuildBankSize());
}

PyObject* guildbankGetItemFlags(PyObject* poSelf, PyObject* poArgs)
{
	int ipos;
	if (!PyTuple_GetInteger(poArgs, 0, &ipos))
		return Py_BadArgument();

	TItemData* pInstance;
	if (!CPythonGuildBank::Instance().GetGuildBankItemDataPtr(ipos, &pInstance))
		return Py_BuildException();

	return Py_BuildValue("i", pInstance->flags);
}

#	ifdef ENABLE_CHANGE_LOOK_SYSTEM
PyObject* guildbankGetItemChangeLookVnum(PyObject* poSelf, PyObject* poArgs)
{
	int iPos;
	if (!PyTuple_GetInteger(poArgs, 0, &iPos))
		return Py_BadArgument();

	TItemData* pInstance;
	if (!CPythonGuildBank::Instance().GetGuildBankItemDataPtr(iPos, &pInstance))
		return Py_BuildException();

	return Py_BuildValue("i", pInstance->dwTransmutationVnum);
}
#	endif

#	ifdef ENABLE_REFINE_ELEMENT //GUILDBANK_ELEMENT
PyObject* guildbankGetElement(PyObject* poSelf, PyObject* poArgs)
{
	int iPos;
	if (!PyTuple_GetInteger(poArgs, 0, &iPos))
		return Py_BadArgument();

	TItemData* pInstance;
	if (!CPythonGuildBank::Instance().GetGuildBankItemDataPtr(iPos, &pInstance))
		return Py_BuildException();

	if (pInstance->grade_element > 0)
		return Py_BuildValue("iiii", pInstance->grade_element, pInstance->attack_element[pInstance->grade_element - 1], pInstance->element_type_bonus, pInstance->elements_value_bonus[pInstance->grade_element - 1]);

	return Py_BuildValue("iiii", 0, 0, 0, 0);
}
#	endif

#	ifdef ENABLE_YOHARA_SYSTEM
PyObject* guildbankGuildbankGetItemApplyRandom(PyObject* poSelf, PyObject* poArgs)
{
	int iSlotIndex;
	if (!PyTuple_GetInteger(poArgs, 0, &iSlotIndex))
		return Py_BuildException();
	int iAttrSlotIndex;
	if (!PyTuple_GetInteger(poArgs, 1, &iAttrSlotIndex))
		return Py_BuildException();

	if (iAttrSlotIndex >= 0 && iAttrSlotIndex < APPLY_RANDOM_SLOT_MAX_NUM)
	{
		TItemData* pItemData;
		if (CPythonGuildBank::Instance().GetGuildBankItemDataPtr(iSlotIndex, &pItemData))
			return Py_BuildValue("ii", pItemData->aApplyRandom[iAttrSlotIndex].wType, pItemData->aApplyRandom[iAttrSlotIndex].sValue);
	}

	return Py_BuildValue("ii", 0, 0);
}

PyObject* guildbankGetRandomValue(PyObject* poSelf, PyObject* poArgs)
{
	int iSlotIndex;
	if (!PyTuple_GetInteger(poArgs, 0, &iSlotIndex))
		return Py_BadArgument();

	int iRandomValueIndex;
	if (!PyTuple_GetInteger(poArgs, 1, &iRandomValueIndex))
		return Py_BadArgument();

	if (iRandomValueIndex >= ITEM_RANDOM_VALUES_MAX_NUM)
		return Py_BuildException();

	TItemData* pItemData;
	if (!CPythonGuildBank::Instance().GetGuildBankItemDataPtr(iSlotIndex, &pItemData))
		return Py_BuildException();

	return Py_BuildValue("i", pItemData->alRandomValues[iRandomValueIndex]);
}
#	endif

#	ifdef ENABLE_SET_ITEM
PyObject* guildbankGetItemSetValue(PyObject* poSelf, PyObject* poArgs)
{
	int iPos;
	if (!PyTuple_GetInteger(poArgs, 0, &iPos))
		return Py_BadArgument();

	TItemData* pInstance;
	if (!CPythonGuildBank::Instance().GetGuildBankItemDataPtr(iPos, &pInstance))
		return Py_BuildException();

	return Py_BuildValue("i", pInstance->set_value);
}
#	endif

void initguildbank()
{
	static PyMethodDef s_methods[] = {// Guildbank
		{ "GetItemID",							guildbankGetItemID,							METH_VARARGS },
		{ "GetGuildBankItemCount",				guildbankGetGuildBankItemCount,				METH_VARARGS },
		{ "GetItemMetinSocket",					guildbankGetItemMetinSocket,				METH_VARARGS },
		{ "GetItemAttribute",					guildbankGetItemAttribute,					METH_VARARGS },
		{ "GetGuildBankInfoSize",				guildbankGetGuildBankInfoSize,				METH_VARARGS },
		{ "GetItemFlags",						guildbankGetItemFlags,						METH_VARARGS },
#	ifdef ENABLE_CHANGE_LOOK_SYSTEM
		{"GetItemChangeLookVnum",				guildbankGetItemChangeLookVnum,				METH_VARARGS},
#	endif
#	ifdef ENABLE_REFINE_ELEMENT //GUILDBANK_ELEMENT
		{"GetItemRefineElement",				guildbankGetElement,						METH_VARARGS},
#	endif
#	ifdef ENABLE_YOHARA_SYSTEM
		{"GetItemApplyRandom",					guildbankGuildbankGetItemApplyRandom,		METH_VARARGS},
		{"GetRandomValue",						guildbankGetRandomValue,					METH_VARARGS},
#	endif
#	ifdef ENABLE_SET_ITEM
		{"GetItemSetValue",						guildbankGetItemSetValue,					METH_VARARGS},
#	endif

		{nullptr, nullptr, 0}
	};

	PyObject* poModule = Py_InitModule("guildbank", s_methods);
	PyModule_AddIntConstant(poModule, "GUILDBANK_SLOT_X_COUNT", CPythonGuildBank::GUILDBANK_SLOT_X_COUNT);
	PyModule_AddIntConstant(poModule, "GUILDBANK_SLOT_Y_COUNT", CPythonGuildBank::GUILDBANK_SLOT_Y_COUNT);
	PyModule_AddIntConstant(poModule, "GUILDBANK_PAGE_SIZE", CPythonGuildBank::GUILDBANK_PAGE_SIZE);
}
#endif

