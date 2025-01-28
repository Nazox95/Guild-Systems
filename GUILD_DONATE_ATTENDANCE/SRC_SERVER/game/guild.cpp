//Open guild.cpp add
#ifdef ENABLE_GUILD_DONATE_ATTENDANCE
#	include "item.h"
#	include "item_manager.h"
#endif

//Replace:
	SGuildMember::SGuildMember(LPCHARACTER ch, BYTE grade, DWORD offer_exp
#ifdef ENABLE_GUILD_DONATE_ATTENDANCE
	, DWORD join_date, BYTE donate_limit, DWORD last_donation, BYTE daily_donate_count, DWORD last_daily_donate
#endif
)
: pid(ch->GetPlayerID()), grade(grade), is_general(0), job(ch->GetJob()), level(ch->GetLevel()), offer_exp(offer_exp), name(ch->GetName())
#ifdef ENABLE_GUILD_DONATE_ATTENDANCE
	, join_date(join_date), donate_limit(donate_limit), last_donation(last_donation), daily_donate_count(daily_donate_count), last_daily_donate(last_daily_donate)
#endif
{}
	SGuildMember::SGuildMember(DWORD pid, BYTE grade, BYTE is_general, BYTE job, BYTE level, DWORD offer_exp, char* name
#ifdef ENABLE_GUILD_DONATE_ATTENDANCE
	, DWORD join_date, BYTE donate_limit, DWORD last_donation, BYTE daily_donate_count, DWORD last_daily_donate
#endif
)
: pid(pid), grade(grade), is_general(is_general), job(job), level(level), offer_exp(offer_exp), name(name)
#ifdef ENABLE_GUILD_DONATE_ATTENDANCE
	, join_date(join_date), donate_limit(donate_limit), last_donation(last_donation), daily_donate_count(daily_donate_count), last_daily_donate(last_daily_donate)
#endif
{}

//find and replace:
void CGuild::AddMember(TPacketDGGuildMember * p)
{
	TGuildMemberContainer::iterator it;

	if ((it = m_member.find(p->dwPID)) == m_member.end())
		m_member.insert(std::make_pair(p->dwPID, TGuildMember(p->dwPID, p->bGrade, p->isGeneral, p->bJob, p->bLevel, p->dwOffer, p->szName
#ifdef ENABLE_GUILD_DONATE_ATTENDANCE
			, p->dwJoinDate, p->bDonateLimit, p->dwLastDonation, p->bDailyDonateCount, p->dwLastDailyDonate
#endif
		)));
	else
	{
		TGuildMember & r_gm = it->second;
		r_gm.pid = p->dwPID;
		r_gm.grade = p->bGrade;
		r_gm.job = p->bJob;
		r_gm.offer_exp = p->dwOffer;
		r_gm.is_general = p->isGeneral;
#ifdef ENABLE_GUILD_DONATE_ATTENDANCE
		r_gm.join_date = p->dwJoinDate;
		r_gm.donate_limit = p->bDonateLimit;
		r_gm.last_donation = p->dwLastDonation;
		r_gm.daily_donate_count = p->bDailyDonateCount;
		r_gm.last_daily_donate = p->dwLastDailyDonate;
#endif
	}

//Now find:
void CGuild::LoadGuildMemberData(SQLMsg* pmsg)
{
//in this function find and replace:
	for (uint i = 0; i < pmsg->Get()->uiNumRows; ++i)
	{
		MYSQL_ROW row = mysql_fetch_row(pmsg->Get()->pSQLResult);

		DWORD pid = strtoul(row[0], (char**) NULL, 10);
		BYTE grade = (BYTE) strtoul(row[1], (char**) NULL, 10);
		BYTE is_general = 0;

		if (row[2] && *row[2] == '1')
			is_general = 1;

		DWORD offer = strtoul(row[3], (char**) NULL, 10);
#ifdef ENABLE_GUILD_DONATE_ATTENDANCE
		DWORD join_date = (DWORD)strtoul(row[4], (char**) NULL, 10); // 4
		BYTE donate_limit = (BYTE)strtoul(row[5], (char**) NULL, 10); // 5
		DWORD last_donation = (DWORD)strtoul(row[6], (char**) NULL, 10); // 6
		BYTE daily_donate_count = (BYTE)strtoul(row[7], (char**) NULL, 10); // 7
		DWORD last_daily_donate = (DWORD)strtoul(row[8], (char**) NULL, 10); // 8
		BYTE level = (BYTE)strtoul(row[9], (char**) NULL, 10); // 9
		BYTE job = (BYTE)strtoul(row[10], (char**) NULL, 10); // 10
		char* name = row[11]; // 11
#else
		BYTE level = (BYTE)strtoul(row[4], (char**) NULL, 10);
		BYTE job = (BYTE)strtoul(row[5], (char**) NULL, 10);
		char * name = row[6];
#endif
		if (is_general)
			m_general_count++;

		m_member.insert(std::make_pair(pid, TGuildMember(pid, grade, is_general, job, level, offer, name
#ifdef ENABLE_GUILD_DONATE_ATTENDANCE
			, join_date, donate_limit, last_donation, daily_donate_count, last_daily_donate
#endif
		)));
		CGuildManager::instance().Link(pid, this);
	}

//Now find:
	void CGuild::Load(DWORD guild_id)
{
	Initialize();
	[...]
//Now find and replace:
	DBManager::instance().FuncQuery(std::bind(&CGuild::LoadGuildGradeData, this, std::placeholders::_1), 
			"SELECT grade, name, auth+0 FROM guild_grade%s WHERE guild_id = %u", get_table_postfix(), m_data.guild_id);

	DBManager::instance().FuncQuery(std::bind(&CGuild::LoadGuildMemberData, this, std::placeholders::_1), 
			"SELECT pid, grade, is_general, offer,"
#ifdef ENABLE_GUILD_DONATE_ATTENDANCE
			"UNIX_TIMESTAMP(join_date), donate_limit, UNIX_TIMESTAMP(last_donation), daily_donate_count, UNIX_TIMESTAMP(last_daily_donate), "
#endif
			" level, job, name FROM guild_member%s, player%s WHERE guild_id = %u and pid = id", get_table_postfix(), get_table_postfix(), guild_id);

//Now before:
void CGuild::__P2PUpdateGrade(SQLMsg* pmsg)
//add:
#ifdef ENABLE_GUILD_DONATE_ATTENDANCE
DWORD CGuild::GetMemberJoinDate(DWORD pid) noexcept	// Donationboard - Time Check
{
	for (auto& iter : m_member)
	{
		if (iter.first == pid)
			return iter.second.join_date;
	}

	return 0;
}

int CGuild::GetGuildMemberDonateCount(DWORD pid) noexcept // Donationboard 0/3 Count
{
	for (auto& iter : m_member)
	{
		if (iter.first == pid)
			return iter.second.donate_limit;
	}
	return 0;
}

DWORD CGuild::GetMemberLastDonation(DWORD pid) noexcept // Last Donation time check
{
	for (auto& iter : m_member)
	{
		if (iter.first == pid)
			return iter.second.last_donation;
	}
	return 0;
}

int CGuild::GetDailyGuildDonatePoints(DWORD pid) noexcept	// Get Player Donation Points
{
	for (auto& iter : m_member)
	{
		if (iter.first == pid)
			return iter.second.daily_donate_count;
	}
	return 0;
}

DWORD CGuild::GetMemberLastDailyDonate(DWORD pid) noexcept // Last daily donate time check
{
	for (auto& iter : m_member)
	{
		if (iter.first == pid)
			return iter.second.last_daily_donate;
	}
	return 0;
}

void CGuild::SetGuildAttendanceState(DWORD pid, int donateCount, DWORD dwTime) // Lock Donate Button [Main-Page] and add the count
{
	const TGuildMemberContainer::iterator it = m_member.find(pid);

	if (it == m_member.end())
		return;

	it->second.daily_donate_count += donateCount;
	it->second.last_daily_donate = dwTime;
	SaveMember(pid);
}

void CGuild::ResetGuildMemberDonateCount(DWORD pid)	//Reset Daily Donation
{
	const TGuildMemberContainer::iterator it = m_member.find(pid);

	if (it == m_member.end())
		return;

	it->second.donate_limit = 0;
	SaveMember(pid);
}
#endif

//Now find:
void CGuild::SendGuildInfoPacket(LPCHARACTER ch)
{
	LPDESC d = ch->GetDesc();

	if (!d)
		return;

	TPacketGCGuild pack;
	pack.header = HEADER_GC_GUILD;
	pack.size = sizeof(TPacketGCGuild) + sizeof(TPacketGCGuildInfo);
	pack.subheader = GUILD_SUBHEADER_GC_INFO;
	[...]
//in the end before
}
//add
#ifdef ENABLE_GUILD_DONATE_ATTENDANCE
	SetGuildDonateInfo();
#endif
}

//Now find
bool CGuild::OfferExp(LPCHARACTER ch, int, amount)
//replace all:
bool CGuild::OfferExp(LPCHARACTER ch, int amount)
{
	TGuildMemberContainer::iterator cit = m_member.find(ch->GetPlayerID());

	if (cit == m_member.end())
		return false;

	if (m_data.exp+amount < m_data.exp)
		return false;

	if (amount < 0)
		return false;

	if (ch->GetExp() < (DWORD) amount)
	{
		ch->ChatPacket(CHAT_TYPE_INFO, "[LS;929]");
		return false;
	}

	if (ch->GetExp() - (DWORD) amount > ch->GetExp())
	{
		sys_err("Wrong guild offer amount %d by %s[%u]", amount, ch->GetName(), ch->GetPlayerID());
		return false;
	}

	ch->PointChange(POINT_EXP, -amount);

	TPacketGuildExpUpdate guild_exp;
	guild_exp.guild_id = GetID();
	guild_exp.amount = amount / 100;
	db_clientdesc->DBPacket(HEADER_GD_GUILD_EXP_UPDATE, 0, &guild_exp, sizeof(guild_exp));
	GuildPointChange(POINT_EXP, amount / 100, true);

	cit->second.offer_exp += amount / 100;
	cit->second._dummy = 0;

	TPacketGCGuild pack;
	pack.header = HEADER_GC_GUILD;

	for (TGuildMemberOnlineContainer::iterator it = m_memberOnline.begin(); it != m_memberOnline.end(); ++it)
	{
		LPDESC d = (*it)->GetDesc();
		if (d)
		{
			pack.subheader = GUILD_SUBHEADER_GC_LIST;
			pack.size = sizeof(pack) + 13;
			d->BufferedPacket(&pack, sizeof(pack));
			d->Packet(&(cit->second), sizeof(DWORD) * 3 + 1);
		}
	}

	SaveMember(ch->GetPlayerID());

	TPacketGuildChangeMemberData gd_guild;

	gd_guild.guild_id = GetID();
	gd_guild.pid = ch->GetPlayerID();
	gd_guild.offer = cit->second.offer_exp;
	gd_guild.level = ch->GetLevel();
	gd_guild.grade = cit->second.grade;
#ifdef ENABLE_GUILD_DONATE_ATTENDANCE
	gd_guild.join_date = cit->second.join_date;
	gd_guild.donate_limit = cit->second.donate_limit;
	gd_guild.last_donation = cit->second.last_donation;
	gd_guild.daily_donate_count = cit->second.daily_donate_count;
	gd_guild.last_daily_donate = cit->second.last_daily_donate;
#endif

	db_clientdesc->DBPacket(HEADER_GD_GUILD_CHANGE_MEMBER_DATA, 0, &gd_guild, sizeof(gd_guild));
	return true;
}

#ifdef ENABLE_GUILD_DONATE_ATTENDANCE
bool CGuild::OfferExpNew(LPCHARACTER ch, int amount)
{
	if (!ch)
		return false;

	const TGuildMemberContainer::iterator cit = m_member.find(ch->GetPlayerID());
	if (cit == m_member.end())
		return false;

	if (amount < 0 || amount >= 3)
		return false;

	if (ch->GetLevel() < 40) //Level Max guild
	{
		ch->ChatPacket(CHAT_TYPE_INFO, "[LS;1927]");
		return false;
	}

	const time_t waitJoinTime = (cit->second.join_date + (60 * 60 * 24));
	if (waitJoinTime > get_global_time())
	{
		ch->ChatPacket(CHAT_TYPE_INFO, "[LS;1926]");
		return false;
	}

	const time_t waitLastDonationTime = (cit->second.last_donation + (60 * 60 * 24));
	if (waitLastDonationTime > get_global_time())
	{
		ch->ChatPacket(CHAT_TYPE_INFO, "[LS;2032]"); // Custom Text
		return false;
	}

	int iEmptyPos;
	const int experience[] = { 20000, 80000, 150000 }; //20k exp, 80k y 150k
	const int donation_required[] = { 120000, 500000, 1000000 }; //120k , 500k + mats y 1kk + mats
	//const int medal_reward[] = { 3, 10, 30 };
	const int required_items[] = { 90010, 90011, 90012 }; //Chapeado, piedra fundición, troncos
	const int required_counts[] = { 3, 5, 15 }; //Cantidades

	switch (amount)
	{
		case 0: // Yang + x3 mats
		{
			if (ch->GetGold() < donation_required[amount])
			{
				ch->ChatPacket(CHAT_TYPE_INFO, "[LS;785]");
				return false;
			}
			else if (ch->CountSpecifyItem(required_items[0]) < required_counts[0] ||
					ch->CountSpecifyItem(required_items[1]) < required_counts[0] ||
					ch->CountSpecifyItem(required_items[2]) < required_counts[0])
	   		{
				ch->ChatPacket(CHAT_TYPE_INFO, "[LS;2033]"); // Mensaje si faltan materiales
				return false;
			}
		}
		break;

		case 1: // Yang + x5 mats (medio)
		{
			if (ch->CountSpecifyItem(donation_required[1]) < 1)
			{
				ch->ChatPacket(CHAT_TYPE_INFO, "[LS;1925]");
				return false;
			}
			else if (ch->CountSpecifyItem(required_items[0]) < required_counts[1] || 
					ch->CountSpecifyItem(required_items[1]) < required_counts[1] ||
					ch->CountSpecifyItem(required_items[2]) < required_counts[1])
			{
				ch->ChatPacket(CHAT_TYPE_INFO, "[LS;2033]"); // Mensaje si faltan materiales
				return false;
			}
		}
		break;

		case 2: // Yang + x15 mats (máximo)
		{
			if (ch->CountSpecifyItem(donation_required[2]) < 1)
			{
				ch->ChatPacket(CHAT_TYPE_INFO, "[LS;1924]");
				return false;
			}
			else if (ch->CountSpecifyItem(required_items[0]) < required_counts[2] || 
					ch->CountSpecifyItem(required_items[1]) < required_counts[2] ||
					ch->CountSpecifyItem(required_items[2]) < required_counts[2])
			{
				ch->ChatPacket(CHAT_TYPE_INFO, "[LS;2033]"); // Mensaje si faltan materiales
				return false;
			}
		}
		break;

		default:
			break;
	}

	if (cit->second.donate_limit == MAX_GUILD_DONATION_PER_DAY - 1) // max donations
		cit->second.last_donation = get_global_time();

	if (cit->second.donate_limit >= MAX_GUILD_DONATION_PER_DAY) // max donations
	{
		ch->ChatPacket(CHAT_TYPE_INFO, "[LS;2032]");
		return false;
	}

	if (amount == 0)
		ch->PointChange(POINT_GOLD, -(donation_required[amount]));
	else
		ch->RemoveSpecifyItem((donation_required[amount]), 1);

	//ch->PointChange(POINT_MEDAL_OF_HONOR, medal_reward[amount], true);

	if (amount == 0)  // Donación pequeña: 3 de cada material
	{
		ch->RemoveSpecifyItem(required_items[0], required_counts[0]);
		ch->RemoveSpecifyItem(required_items[1], required_counts[0]);
		ch->RemoveSpecifyItem(required_items[2], required_counts[0]);
	}
	else if (amount == 1)  // Donación media: 5 de cada material
	{
		ch->RemoveSpecifyItem(required_items[0], required_counts[1]);
		ch->RemoveSpecifyItem(required_items[1], required_counts[1]);
		ch->RemoveSpecifyItem(required_items[2], required_counts[1]);
	}
	else if (amount == 2)  // Donación máxima: 15 de cada material
	{
		ch->RemoveSpecifyItem(required_items[0], required_counts[2]);
		ch->RemoveSpecifyItem(required_items[1], required_counts[2]);
		ch->RemoveSpecifyItem(required_items[2], required_counts[2]);
	}

	ch->ChatPacket(CHAT_TYPE_INFO, "[LS;1485;%d]", experience[amount]);

	TPacketGuildExpUpdate guild_exp{};
	guild_exp.guild_id = GetID();
	guild_exp.amount = experience[amount] / 100;
	db_clientdesc->DBPacket(HEADER_GD_GUILD_EXP_UPDATE, 0, &guild_exp, sizeof(guild_exp));

	GuildPointChange(POINT_EXP, experience[amount] / 100, true);

	cit->second.offer_exp += experience[amount] / 100;
	cit->second._dummy = 0;
#ifdef ENABLE_GUILD_DONATE_ATTENDANCE
	cit->second.donate_limit += 1;
#endif

	TPacketGCGuild pack{};
	pack.header = HEADER_GC_GUILD;

	for (TGuildMemberOnlineContainer::iterator it = m_memberOnline.begin(); it != m_memberOnline.end(); ++it)
	{
		LPDESC d = (*it)->GetDesc();
		if (d)
		{
			pack.subheader = GUILD_SUBHEADER_GC_LIST;
			pack.size = sizeof(pack) + 13;
			d->BufferedPacket(&pack, sizeof(pack));
			d->Packet(&(cit->second), sizeof(DWORD) * 3 + 1);
		}
	}

	SaveMember(ch->GetPlayerID());
#ifdef ENABLE_GUILD_DONATE_ATTENDANCE
	SetGuildDonateInfo();
#endif

	TPacketGuildChangeMemberData gd_guild{};

	gd_guild.guild_id = GetID();
	gd_guild.pid = ch->GetPlayerID();
	gd_guild.offer = cit->second.offer_exp;
	gd_guild.level = ch->GetLevel();
	gd_guild.grade = cit->second.grade;
#ifdef ENABLE_GUILD_DONATE_ATTENDANCE
	gd_guild.join_date = cit->second.join_date;
	gd_guild.donate_limit = cit->second.donate_limit;
	gd_guild.last_donation = cit->second.last_donation;
	gd_guild.daily_donate_count = cit->second.daily_donate_count;
	gd_guild.last_daily_donate = cit->second.last_daily_donate;
#endif

	db_clientdesc->DBPacket(HEADER_GD_GUILD_CHANGE_MEMBER_DATA, 0, &gd_guild, sizeof(gd_guild));
	//M2_DESTROY_ITEM(item);
	return true;
}
#endif

//Now in
void CGuild::ChangeMemberGrade(DWORD pid, BYTE grade)
{
[...]
	gd_guild.guild_id = GetID();
	gd_guild.pid = pid;
	gd_guild.offer = it->second.offer_exp;
	gd_guild.level = it->second.level;
	gd_guild.grade = grade;
//add
#ifdef ENABLE_GUILD_DONATE_ATTENDANCE
	gd_guild.join_date = it->second.join_date;
	gd_guild.donate_limit = it->second.donate_limit;
	gd_guild.last_donation = it->second.last_donation;
	gd_guild.daily_donate_count = it->second.daily_donate_count;
	gd_guild.last_daily_donate = it->second.last_daily_donate;
#endif

	db_clientdesc->DBPacket(HEADER_GD_GUILD_CHANGE_MEMBER_DATA, 0, &gd_guild, sizeof(gd_guild));
}

//Find and replace:
void CGuild::SaveMember(DWORD pid)
{
	TGuildMemberContainer::iterator it = m_member.find(pid);

	if (it == m_member.end())
		return;

	DBManager::instance().Query(
			"UPDATE guild_member%s SET grade = %d, offer = %u, is_general = %d "
#ifdef ENABLE_GUILD_DONATE_ATTENDANCE
			", join_date = FROM_UNIXTIME(%d), donate_limit = %d, last_donation = FROM_UNIXTIME(%d), daily_donate_count = %d, last_daily_donate = FROM_UNIXTIME(%d)"
#endif
			"WHERE pid = %u and guild_id = %u",
			get_table_postfix(), it->second.grade, it->second.offer_exp, it->second.is_general,
#ifdef ENABLE_GUILD_DONATE_ATTENDANCE
		it->second.join_date, it->second.donate_limit, it->second.last_donation, it->second.daily_donate_count, it->second.last_daily_donate,
#endif
pid, m_data.guild_id);
}

//Find and replace:
void CGuild::LevelChange(DWORD pid, BYTE level)
{
	TGuildMemberContainer::iterator cit = m_member.find(pid);

	if (cit == m_member.end())
		return;

	cit->second.level = level;

	TPacketGuildChangeMemberData gd_guild;

	gd_guild.guild_id = GetID();
	gd_guild.pid = pid;
	gd_guild.offer = cit->second.offer_exp;
	gd_guild.grade = cit->second.grade;
	gd_guild.level = level;
#ifdef ENABLE_GUILD_DONATE_ATTENDANCE
	gd_guild.join_date = cit->second.join_date;
	gd_guild.donate_limit = cit->second.donate_limit;
	gd_guild.last_donation = cit->second.last_donation;
	gd_guild.daily_donate_count = cit->second.daily_donate_count;
	gd_guild.last_daily_donate = cit->second.last_daily_donate;
#endif
	db_clientdesc->DBPacket(HEADER_GD_GUILD_CHANGE_MEMBER_DATA, 0, &gd_guild, sizeof(gd_guild));

	TPacketGCGuild pack;
	pack.header = HEADER_GC_GUILD;
	cit->second._dummy = 0;

	for (TGuildMemberOnlineContainer::iterator it = m_memberOnline.begin(); it != m_memberOnline.end(); ++it)
	{
		LPDESC d = (*it)->GetDesc();

		if (d)
		{
			pack.subheader = GUILD_SUBHEADER_GC_LIST;
			pack.size = sizeof(pack) + 13;
			d->BufferedPacket(&pack, sizeof(pack));
			d->Packet(&(cit->second), sizeof(DWORD) * 3 + 1);
		}
	}
}

//Find and replace:
void CGuild::ChangeMemberData(DWORD pid, DWORD offer, BYTE level, BYTE grade
#ifdef ENABLE_GUILD_DONATE_ATTENDANCE
	, DWORD join_date, BYTE donate_limit, DWORD last_donation, BYTE daily_donate_count, DWORD last_daily_donate
#endif
)
{
	TGuildMemberContainer::iterator cit = m_member.find(pid);

	if (cit == m_member.end())
		return;

	cit->second.offer_exp = offer;
	cit->second.level = level;
	cit->second.grade = grade;
	cit->second._dummy = 0;
#ifdef ENABLE_GUILD_DONATE_ATTENDANCE
	cit->second.join_date = join_date;
	cit->second.donate_limit = donate_limit;
	cit->second.last_donation = last_donation;
	cit->second.daily_donate_count = daily_donate_count;
	cit->second.last_daily_donate = last_daily_donate;
#endif
	TPacketGCGuild pack;
	memset(&pack, 0, sizeof(pack));
	pack.header = HEADER_GC_GUILD;

	for (TGuildMemberOnlineContainer::iterator it = m_memberOnline.begin(); it != m_memberOnline.end(); ++it)
	{
		LPDESC d = (*it)->GetDesc();
		if (d)
		{
			pack.subheader = GUILD_SUBHEADER_GC_LIST;
			pack.size = sizeof(pack) + 13;
			d->BufferedPacket(&pack, sizeof(pack));
			d->Packet(&(cit->second), sizeof(DWORD) * 3 + 1);
		}
	}
}

namespace
{
	struct FGuildChat
	{
		const char* c_pszText;

		FGuildChat(const char* c_pszText)
			: c_pszText(c_pszText)
			{}

		void operator()(LPCHARACTER ch)
		{
			ch->ChatPacket(CHAT_TYPE_GUILD, "%s", c_pszText);
		}
	};
}

//Before
void CGuild::RecvWithdrawMoneyGive(int iChangeGold)
//add
#ifdef ENABLE_GUILD_DONATE_ATTENDANCE
void CGuild::SetGuildDonateInfo()
{
	for (itertype(m_memberOnline) it = m_memberOnline.begin(); it != m_memberOnline.end(); ++it)
	{
		const LPCHARACTER& ch = *it;
		if (!ch)
			continue;
		LPDESC d = ch->GetDesc();
		if (!d)
			continue;
		//int medals = ch->GetMedalHonor();

		int donateCount = GetGuildMemberDonateCount(ch->GetPlayerID());
		if (!donateCount)
			donateCount = 0;

		const time_t waitTime = (GetMemberLastDonation(ch->GetPlayerID()) + (60 * 60 * 24));
		if ((donateCount >= MAX_GUILD_DONATION_PER_DAY) && (waitTime < get_global_time()))
		{
			ResetGuildMemberDonateCount(ch->GetPlayerID());
			donateCount = 0;
		}

		TPacketGCGuild p{};
		p.header = HEADER_GC_GUILD;
		//p.size = sizeof(p) + sizeof(medals);
		p.subheader = GUILD_SUBHEADER_GC_DONATE;

		d->BufferedPacket(&p, sizeof(p));
		//d->Packet(&medals, sizeof(medals));
		d->Packet(&donateCount, sizeof(donateCount));
	}
}
#endif
