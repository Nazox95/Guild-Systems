//Open cmd_general.cpp add in the end:
#ifdef ENABLE_GUILD_DONATE_ATTENDANCE
ACMD(do_gdonate)
{
	if (!ch)
		return;

	const int iPulse = thecore_pulse();
	if (iPulse - ch->GetLastOfferNewExpTime() < PASSES_PER_SEC(10))
	{
		ch->ChatPacket(CHAT_TYPE_INFO, "[LS;1554]");
		return;
	}

	CGuild* g = ch->GetGuild();
	if (!g)
		return;

	const DWORD g_id = g->GetID();
	const time_t waitTime = (g->GetMemberLastDailyDonate(ch->GetPlayerID()) + (60 * 60 * 24));
	if (waitTime > get_global_time())
	{
		ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("You have already attended today."));
		return;
	}

	const int donateCount = g->GetDailyGuildDonatePoints(g_id);

	int donateBonus = 0;
	if (donateCount <= 19)
		donateBonus = 1;
	else if (donateCount <= 29)
		donateBonus = 2;
	else if (donateCount <= 39)
		donateBonus = 4;
	else if (donateCount <= 49)
		donateBonus = 6;
	else if (donateCount <= 59)
		donateBonus = 8;
	else if (donateCount <= 69)
		donateBonus = 10;
	else if (donateCount <= 100)
		donateBonus = 12;

	//ch->PointChange(POINT_MEDAL_OF_HONOR, donateBonus, true);
	ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("%d Donate points earned!"), donateBonus);

	g->SetGuildAttendanceState(ch->GetPlayerID(), donateBonus, get_global_time());
	ch->SetLastOfferNewExpTime();
}
#endif
