//If you have Sort inventory from Mali (__BL_SORT_INVENT__) add in const int CustomSort() const {
#ifdef __BL_SORT_INVENT__
		const int CustomSort() const {
			switch (m_pProto->bType) {
				case ITEM_WEAPON:	return 1;
				case ITEM_ARMOR:	return 2;
				case ITEM_USE:	return 3;
				case ITEM_BELT:	return 4;
				case ITEM_COSTUME:	return 5;
				case ITEM_SKILLBOOK:
				case ITEM_SKILLFORGET:	return 6;
#ifdef ENABLE_SKILL_FORGOT_BOOK
				case ITEM_SKILLFORGETGUILD: return 7;
#endif
			}
			return 8;
		}
#endif
