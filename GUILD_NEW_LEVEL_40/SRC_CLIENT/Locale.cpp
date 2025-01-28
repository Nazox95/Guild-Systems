//In UserInterface->Locale.cpp find:
unsigned LocaleService_GetLastExp(int level)
{
  [...]
//And replace all function with this:
unsigned LocaleService_GetLastExp(int level)
{
#if defined(ENABLE_EXTENDED_GUILD_LEVEL)
	static const int GUILD_LEVEL_MAX = 40;
#else
	static const int GUILD_LEVEL_MAX = 20;
#endif
	if (LocaleService_IsCHEONMA())
	{
		static DWORD CHEONMA_GUILDEXP_LIST[GUILD_LEVEL_MAX + 1] =
		{
			0,			// 0
			15000ul,	// 1
			45000ul,	// 2
			90000ul,	// 3
			160000ul,	// 4
			235000ul,	// 5
			325000ul,	// 6
			430000ul,	// 7
			550000ul,	// 8
			685000ul,	// 9
			835000ul,	// 10
			1000000ul,	// 11
			1500000ul,	// 12
			2100000ul,	// 13
			2800000ul,	// 14
			3600000ul,	// 15
			4500000ul,	// 16
			6500000ul,	// 17
			8000000ul,	// 18
			10000000ul,	// 19			
			42000000UL	// 20+21
		};
		if (level < 0 && level >= GUILD_LEVEL_MAX)
			return 0;
		
		return CHEONMA_GUILDEXP_LIST[level];
	}
	
	static DWORD INTERNATIONAL_GUILDEXP_LIST[GUILD_LEVEL_MAX+1] = 
	{
		0,			// 0 //Fix
		6000UL,		// 1
		18000UL,	// 2
		36000UL,	// 3
		64000UL,	// 4
		94000UL,	// 5
		130000UL,	// 6
		172000UL,	// 7
		220000UL,	// 8
		274000UL,	// 9
		334000UL,	// 10
		400000UL,	// 11
		600000UL,	// 12
		840000UL,	// 13
		1120000UL,	// 14
		1440000UL,	// 15
		1800000UL,	// 16
		2600000UL,	// 17
		3200000UL,	// 18
		4000000UL,	// 19			
#if defined(ENABLE_EXTENDED_GUILD_LEVEL)
		4200000ul,	//21
		4400000ul,	//22
		4600000ul,	//23
		4800000ul,	//24
		5000000ul,	//25
		5200000ul,	//26
		5400000ul,	//27
		5600000ul,	//28
		5800000ul,	//29
		6000000ul,	//30
		6200000ul,	//31
		6400000ul,	//32
		6800000ul,	//33
		7000000ul,	//34
		7200000ul,	//35
		7400000ul,	//36
		7600000ul,	//37
		7800000ul,	//38
		8000000ul,	//39
		9000000ul, 	//40
#endif
		16800000UL	// 20	
	};

#ifdef ENABLE_EXTENDED_GUILD_LEVEL
	if (level < 0 || level >= GUILD_LEVEL_MAX)
		return 0;
#else
	if (level < 0 && level >= GUILD_LEVEL_MAX)
		return 0;
#endif
	
	return INTERNATIONAL_GUILDEXP_LIST[level];	
}
