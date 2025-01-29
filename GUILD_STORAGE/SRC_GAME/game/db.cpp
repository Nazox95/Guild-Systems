//Open db.cpp find 
		case QID_SAFEBOX_SIZE:
			{
				LPCHARACTER ch = CHARACTER_MANAGER::instance().FindByPID(qi->dwIdent);

				if (ch)
				{
					if (pMsg->Get()->uiNumRows > 0)
					{
						MYSQL_ROW row = mysql_fetch_row(pMsg->Get()->pSQLResult);
						int	size = 0;
						str_to_number(size, row[0]);
						ch->SetSafeboxSize(SAFEBOX_PAGE_SIZE * size);
					}
				}
			}
			break;
//add
#ifdef ENABLE_GUILDSTORAGE_SYSTEM
		case QID_GUILDSTORAGE_SIZE:
			{
				LPCHARACTER ch = CHARACTER_MANAGER::Instance().FindByPID(qi->dwIdent);

				if (ch)
				{
					if (pMsg->Get()->uiNumRows > 0)
					{
						MYSQL_ROW row = mysql_fetch_row(pMsg->Get()->pSQLResult);
						int size = 0;
						str_to_number(size, row[0]);
						ch->SetGuildstorageSize(SAFEBOX_PAGE_SIZE * size);
					}
				}
			}
			break;
#endif
