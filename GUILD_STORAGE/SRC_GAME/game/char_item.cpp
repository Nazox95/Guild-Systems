//Open char_item.cpp find 
	case SAFEBOX:
		if (NULL != m_pkSafebox)
			return m_pkSafebox->IsValidPosition(cell);
		else
			return false;

	case MALL:
		if (NULL != m_pkMall)
			return m_pkMall->IsValidPosition(cell);
		else
			return false;
//add
#ifdef ENABLE_GUILDSTORAGE_SYSTEM
		case GUILDBANK:
			if (nullptr != m_pkGuildstorage)
				return m_pkGuildstorage->IsValidPosition(cell);
			else
				return false;
#endif
	default:
		return false;
	}
}
