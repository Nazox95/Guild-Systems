//Open Guild.h find and replace
typedef struct SGuildData
{
	DWORD	guild_id;
	DWORD	master_pid;
	DWORD	exp;
	BYTE	level;
	char	name[GUILD_NAME_MAX_LEN+1];

	TGuildGrade	grade_array[GUILD_GRADE_COUNT];

	BYTE	skill_point;
	BYTE	abySkill[GUILD_SKILL_COUNT];

	int		power;
	int		max_power;

	int		ladder_point;

	int		win;
	int		draw;
	int		loss;

	int		gold;
#ifdef ENABLE_GUILD_WAR_SCORE
	int winTypes[3];
	int drawTypes[3];
	int lossType[3];
#endif
} TGuildData;

//find
		int			GetGuildMoney() const noexcept { return m_data.gold; }
		void		SetGuildMoney(int gold) { m_data.gold = gold; }

//add
	// War general
#ifdef ENABLE_GUILD_WAR_SCORE
		void		SetWarInfo();
#endif

//Find 
		int			GetLadderPoint() const	{ return m_data.ladder_point; }
		void		SetLadderPoint(int point);

		void		SetWarData(int iWin, int iDraw, int iLoss) { m_data.win = iWin, m_data.draw = iDraw, m_data.loss = iLoss; }
//add
#ifdef ENABLE_GUILD_WAR_SCORE
		void		SetNewWarData(long iWin[3], long iDraw[3], long iLoss[3]) noexcept
		{
			for (int i = 0; i < 3; ++i)
			{
				m_data.winTypes[i] = iWin[i];
				m_data.drawTypes[i] = iDraw[i];
				m_data.lossType[i] = iLoss[i];
			}
		}
#endif
