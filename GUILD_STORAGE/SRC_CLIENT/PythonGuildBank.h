//Add to project in UserInterface
#pragma once

#ifdef ENABLE_GUILDSTORAGE_SYSTEM
class CPythonGuildBank : public CSingleton<CPythonGuildBank>
{
public:
	enum
	{
		GUILDBANK_SLOT_X_COUNT = 5,
		GUILDBANK_SLOT_Y_COUNT = 9,
		GUILDBANK_PAGE_SIZE = GUILDBANK_SLOT_X_COUNT * GUILDBANK_SLOT_Y_COUNT
	};

	using TItemGuildBankInstanceVector = std::vector<TItemData>;

	CPythonGuildBank();
	~CPythonGuildBank();
	CLASS_DELETE_COPYMOVE(CPythonGuildBank);

	void OpenGuildBank(int iSize);
	void SetGuildBankItemData(DWORD dwSlotIndex, const TItemData& rItemData);
	void DelGuildBankItemData(DWORD dwSlotIndex);
	BOOL GetGuildBankItemDataPtr(DWORD dwSlotIndex, TItemData** ppInstance);
	BOOL GetSlotGuildBankItemID(DWORD dwSlotIndex, DWORD* pdwItemID);
	DWORD GetGuildBankSize();

protected:
	TItemGuildBankInstanceVector m_GuildBankItemInstanceVector;
};
#endif
