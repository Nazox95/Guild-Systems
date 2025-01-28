//This is optional, if you want give 3 points for skills after create a new guild.
//This is basically if you want all skills to reach their maximum level (7) as the
//default is not reached, whether you are level 20 or level 40.
//find this function:
CGuild::CGuild(TGuildCreateParameter & cp)
{
      Initialize();
      [...]
//Find and replace:
 [...]
      ComputeGuildPoints();
      m_data.power	= m_data.max_power;
      m_data.ladder_point	= 0;
      db_clientdesc->DBPacket(HEADER_GD_GUILD_CREATE, 0, &m_data.guild_id, sizeof(DWORD));

      TPacketGuildSkillUpdate guild_skill;
      guild_skill.guild_id = m_data.guild_id;
      guild_skill.amount = 0;
#if defined(ENABLE_EXTENDED_GUILD_LEVEL)
      guild_skill.skill_point = 3; //Start with 3 pints after create guild.
#else
      guild_skill.skill_point = 0; //Original
#endif
      memset(guild_skill.skill_levels, 0, GUILD_SKILL_COUNT);
