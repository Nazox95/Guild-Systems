//Open guild.cpp find 
namespace 
{
	struct FGuildNameSender
	{
		FGuildNameSender(DWORD id, const char* guild_name) : id(id), name(guild_name)
		{
			p.header = HEADER_GC_GUILD;
			p.subheader = GUILD_SUBHEADER_GC_GUILD_NAME;
			p.size = sizeof(p) + sizeof(DWORD) + GUILD_NAME_MAX_LEN;
		}

		void operator() (LPCHARACTER ch)
		{
			LPDESC d = ch->GetDesc();

			if (d)
			{
				d->BufferedPacket(&p, sizeof(p));
				d->BufferedPacket(&id, sizeof(id));
				d->Packet(name, GUILD_NAME_MAX_LEN);
			}
		}

		DWORD id;
		const char * name;
		TPacketGCGuild p;
	};
//add
#if defined(ENABLE_GUILDRENEWAL_SYSTEM) && defined(ENABLE_GUILDSTORAGE_SYSTEM)
	struct RefreshInfo
	{
		CGuild * p;
		RefreshInfo(CGuild * p) : p(p){}

		void operator()(LPCHARACTER ch)
		{
			if(ch && p)
				p->SendGuildInfoPacket(ch);
		}
	};
#endif
}

//find 
void CGuild::Initialize()
{
	memset(&m_data, 0, sizeof(m_data));
	m_data.level = 1;

	for (int i = 0; i < GUILD_SKILL_COUNT; ++i)
		abSkillUsable[i] = true;
	m_iMemberCountBonus = 0;
//add
#ifdef ENABLE_GUILDSTORAGE_SYSTEM
	storageOpen = false;
	storagePidOpen = 0;
#endif
}

//find 
void CGuild::LoadGuildData(SQLMsg* pmsg)
{
	if (pmsg->Get()->uiNumRows == 0)
	{
		sys_err("Query failed: getting guild data %s", pmsg->stQuery.c_str());
		return;
	}

	MYSQL_ROW row = mysql_fetch_row(pmsg->Get()->pSQLResult);
	m_data.master_pid = strtoul(row[0], (char **)NULL, 10);
	m_data.level = (BYTE)strtoul(row[1], (char **)NULL, 10);
	m_data.exp = strtoul(row[2], (char **)NULL, 10);
	strlcpy(m_data.name, row[3], sizeof(m_data.name));

	m_data.skill_point = (BYTE) strtoul(row[4], (char **) NULL, 10);
	if (row[5])
		thecore_memcpy(m_data.abySkill, row[5], sizeof(BYTE) * GUILD_SKILL_COUNT);
	else
		memset(m_data.abySkill, 0, sizeof(BYTE) * GUILD_SKILL_COUNT);

	m_data.power = MAX(0, strtoul(row[6], (char **) NULL, 10));

	str_to_number(m_data.ladder_point, row[7]);

	if (m_data.ladder_point < 0)
		m_data.ladder_point = 0;

	str_to_number(m_data.win, row[8]);
	str_to_number(m_data.draw, row[9]);
	str_to_number(m_data.loss, row[10]);
	str_to_number(m_data.gold, row[11]);
#ifdef ENABLE_GUILD_WAR_SCORE
	for (int w = 0; w < 3; ++w)
		str_to_number(m_data.winTypes[w], row[12+w]);
	for (int d = 0; d < 3; ++d)
		str_to_number(m_data.drawTypes[d], row[15+d]);
	for (int l = 0; l < 3; ++l)
		str_to_number(m_data.lossType[l], row[18+l]);
#endif
#ifdef ENABLE_GUILDSTORAGE_SYSTEM
	str_to_number(m_data.guildstorage, row[21]);
	strlcpy(m_data.lastGold, row[22], sizeof(m_data.lastGold));
	strlcpy(m_data.lastItem, row[23], sizeof(m_data.lastItem));
	str_to_number(m_data.guildstoragestate, row[24]);
	str_to_number(m_data.guildstoragewho, row[25]);
#endif
	ComputeGuildPoints();
}
//NOTE: You need have the same row in sql / here to work, so check you're  values
//find
void CGuild::Load(DWORD guild_id)
{
	Initialize();

	m_data.guild_id = guild_id;

	DBManager::instance().FuncQuery(std::bind(&CGuild::LoadGuildData, this, std::placeholders::_1),
			"SELECT master, level, exp, name, skill_point, skill, sp, ladder_point, win, draw, loss, gold"
#ifdef ENABLE_GUILD_WAR_SCORE
			", wintype0, wintype1, wintype2, drawtype0, drawtype1, drawtype2, losstype0, losstype1, losstype2"
#endif
//add
#ifdef ENABLE_GUILDSTORAGE_SYSTEM
			", guildstorage, lastGold, lastItem, guildstoragestate, guildstoragewho"
#endif
			" FROM guild%s WHERE id = %u", get_table_postfix(), m_data.guild_id);

	sys_log(0, "GUILD: loading guild id %12s %u", m_data.name, guild_id);

//find 
	memset(&pack_sub, 0, sizeof(TPacketGCGuildInfo));
	pack_sub.member_count = GetMemberCount(); 
	pack_sub.max_member_count = GetMaxMemberCount();
	pack_sub.guild_id = m_data.guild_id;
	pack_sub.master_pid = m_data.master_pid;
	pack_sub.exp	= m_data.exp;
	pack_sub.level	= m_data.level;
	strlcpy(pack_sub.name, m_data.name, sizeof(pack_sub.name));
	pack_sub.gold	= m_data.gold;
	pack_sub.has_land	= HasLand();
//add
#if defined(ENABLE_GUILDRENEWAL_SYSTEM) && defined(ENABLE_GUILDSTORAGE_SYSTEM)
	strlcpy(pack_sub.goldCheckout, GetLastCheckout(GS_GOLD), sizeof(pack_sub.goldCheckout));
	strlcpy(pack_sub.itemCheckout, GetLastCheckout(GS_ITEM), sizeof(pack_sub.itemCheckout));
#endif

	sys_log(0, "GMC guild_name %s", m_data.name);
	sys_log(0, "GMC master %d", m_data.master_pid);

//add below function 
#if defined(ENABLE_GUILDRENEWAL_SYSTEM) && defined(ENABLE_GUILDSTORAGE_SYSTEM)
const char* CGuild::GetLastCheckout(int type)
{
	const char* name = "None";

	if (type == 1)
		name = m_data.lastItem;
	else if (type == 2)
		name = m_data.lastGold;

	return name;
}

void CGuild::SetLastCheckoutP2P(const char* szName, int type)
{
	if(type < GS_ITEM || type > GS_GOLD)
		return;

	std::map<DWORD, const char*> data;
	data[GS_GOLD] = "lastGold";
	data[GS_ITEM] = "lastItem";

	if (type == 1)
		strlcpy(m_data.lastItem, szName, sizeof(m_data.lastItem));
	else if (type == 2)
		strlcpy(m_data.lastGold, szName, sizeof(m_data.lastGold));

	auto pmsg(DBManager::Instance().DirectQuery("UPDATE guild%s SET %s = '%s' WHERE id = %d", get_table_postfix(), data[type], szName, GetID()));
}

void CGuild::RefreshP2P(CGuild * p)
{
	std::for_each(m_memberOnline.begin(), m_memberOnline.end(), RefreshInfo(p));
}

void CGuild::SetLastCheckout(const char* szName, int type)
{
	TPacketGGGuild p1{};
	TPacketGGGuildChat p2{};

	p1.bHeader = HEADER_GG_GUILD;
	p1.bSubHeader = GUILD_SUBHEADER_GG_REFRESH1;
	p1.dwGuild = GetID();
	p2.dwGuild = type;
	strlcpy(p2.szText, szName, sizeof(p2.szText));

	P2P_MANAGER::Instance().Send(&p1, sizeof(TPacketGGGuild));
	P2P_MANAGER::Instance().Send(&p2, sizeof(TPacketGGGuildChat));
}
#endif

//find and replace all function (have the other systems, so check it if u don't want replace)
#ifdef ENABLE_USE_MONEY_FROM_GUILD
void CGuild::RequestWithdrawMoney(LPCHARACTER ch, int iGold, bool buildPrice)
#else
void CGuild::RequestWithdrawMoney(LPCHARACTER ch, int iGold)
#endif
{
	if (!ch)
		return;

	if (!ch->CanDeposit())
	{
		ch->ChatPacket(CHAT_TYPE_INFO, "[LS;82]");
		return;
	}

#ifndef ENABLE_GUILDSTORAGE_SYSTEM
	if (ch->GetPlayerID() != GetMasterPID())
	{
		ch->ChatPacket(CHAT_TYPE_INFO, "[LS;939]");
		return;
	}
#endif

	if (m_data.gold < iGold)
	{
		ch->ChatPacket(CHAT_TYPE_INFO, "[LS;687]");
		return;
	}

#if defined(ENABLE_GUILDRENEWAL_SYSTEM) && defined(ENABLE_USE_MONEY_FROM_GUILD)
	if (buildPrice)
	{
		int iChangeGoldTax = iGold;
		if (GetLevel() < 20) { // [Bonus 4]
			DWORD dwTax = 0;
			int iVal = 15;

			dwTax = iChangeGoldTax * iVal / 100;
			iChangeGoldTax -= dwTax;
		}

		ch->PointChange(POINT_GOLD, iChangeGoldTax);
		//if (test_server)
		{
			ch->ChatPacket(CHAT_TYPE_INFO, "[LS;2034;%d;%d]", iGold, iChangeGoldTax);
		}
	}
#endif

#if defined(ENABLE_GUILDRENEWAL_SYSTEM) && defined(ENABLE_GUILDSTORAGE_SYSTEM)
	SetLastCheckout(ch->GetName(), GS_GOLD);
	SetLastCheckoutP2P(ch->GetName(), GS_GOLD);
	SendGuildInfoPacket(ch);
	TPacketGGGuild p1{};
	TPacketGGGuildChat p2{};

	p1.bHeader = HEADER_GG_GUILD;
	p1.bSubHeader = GUILD_SUBHEADER_GG_REFRESH;
	p1.dwGuild = GetID();
	strlcpy(p2.szText, "none", sizeof(p2.szText));

	P2P_MANAGER::Instance().Send(&p1, sizeof(TPacketGGGuild));
	P2P_MANAGER::Instance().Send(&p2, sizeof(TPacketGGGuildChat));
#endif

	TPacketGDGuildMoney p{};
	p.dwGuild = GetID();
	p.iGold = iGold;
	db_clientdesc->DBPacket(HEADER_GD_GUILD_WITHDRAW_MONEY, 0, &p, sizeof(p));

#if defined(ENABLE_GUILDRENEWAL_SYSTEM) && defined(ENABLE_USE_MONEY_FROM_GUILD)
	char buf[64 + 1];
	snprintf(buf, sizeof(buf), "%u %s", GetID(), GetName());
	LogManager::Instance().CharLog(ch, iGold, "GUILD_WITHDRAW", buf);
#endif

#if defined(ENABLE_GUILDRENEWAL_SYSTEM) && defined(ENABLE_GUILDBANK_EXTENDED_LOGS)
#	ifdef ENABLE_USE_MONEY_FROM_GUILD
	if (buildPrice)
#	endif
	{
		LogManager::Instance().GuildLog(ch, ch->GetGuild()->GetID(), 0, "Yang", GUILD_GOLD_TYPE_OUT, iGold, 1);
	}
#endif

	ch->UpdateDepositPulse();
	sys_log(0, "GUILD: WITHDRAW %s:%u player %s[%u] gold %d", GetName(), GetID(), ch->GetName(), ch->GetPlayerID(), iGold);
}

//find
void CGuild::RecvMoneyChange(int iGold)
{
	m_data.gold = iGold;

	TPacketGCGuild p;
	p.header = HEADER_GC_GUILD;
	p.size = sizeof(p) + sizeof(int);
	p.subheader = GUILD_SUBHEADER_GC_MONEY_CHANGE;

	for (itertype(m_memberOnline) it = m_memberOnline.begin(); it != m_memberOnline.end(); ++it)
	{
		LPCHARACTER ch = *it;
		LPDESC d = ch->GetDesc();
		d->BufferedPacket(&p, sizeof(p));
		d->Packet(&iGold, sizeof(int));
	}
}
//add
#ifdef ENABLE_GUILDSTORAGE_SYSTEM
void CGuild::SetStorageState(bool val, DWORD pid)
{
	m_data.guildstoragestate = val ? 1 : 0;
	m_data.guildstoragewho = pid;
	auto pmsg(DBManager::Instance().DirectQuery("UPDATE guild%s SET guildstoragestate=%d, guildstoragewho = %d WHERE id = %d", get_table_postfix(), m_data.guildstoragestate, pid, GetID()));
};

void CGuild::SetGuildstorage(int val)
{
	m_data.guildstorage = val;
	auto pmsg(DBManager::Instance().DirectQuery("UPDATE guild%s SET guildstorage=%d WHERE id = %d", get_table_postfix(), m_data.guildstorage, GetID()));
}
#endif
