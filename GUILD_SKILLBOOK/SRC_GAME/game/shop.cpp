//If you have Search shop item for offline shop Try to find something like
#ifdef SHOP_SEARCH
#ifdef SHOP_SEARCH_PRICE_MIN
inline bool SHOP_SEARCH_PRICE_VAILD(long long item_price,long long price) {return (item_price <= price || price == 0);}
#else
inline bool SHOP_SEARCH_PRICE_VAILD(long long item_price,long long price) {return (item_price >= price);}
#endif
bool CShop::SearchItem(DWORD vnum, long long price,DWORD book)
{
	for (DWORD i = 0; i < m_itemVector.size() && i < SHOP_HOST_ITEM_MAX_NUM; ++i)
	{
		const SHOP_ITEM & item = m_itemVector[i];
		if (!item.pkItem)
			continue;
		if(item.vnum != vnum)
			continue;
		switch(item.vnum)
		{
			case 50300://skill book
			case 70037://forget skill book
#ifdef ENABLE_SKILL_FORGOT_BOOK
			case 50341://Olvido Gremio
#endif
			case 70055://forget skill book
				if (SHOP_SEARCH_PRICE_VAILD(item.price,price) && item.pkItem->GetSocket(0) == book)
					return true;
				break;
			default:
				if (SHOP_SEARCH_PRICE_VAILD(item.price,price))
					return true;
				break;
		}

	}

	return false;
}
#endif

//And add new value, maybe you call special items in other functions but you need add here for found item in search shop.
