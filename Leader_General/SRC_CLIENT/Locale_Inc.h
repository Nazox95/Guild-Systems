//Add on Locale_inc.h:
///Gremio
#define ENABLE_GUILDRENEWAL_SYSTEM	//Extensión de Gremio like Official
#if defined(ENABLE_GUILDRENEWAL_SYSTEM)
	#define ENABLE_SECOND_GUILDRENEWAL_SYSTEM //
#ifndef ENABLE_SHOW_LIDER_AND_GENERAL_GUILD //Líder y general en gremio
	#define ENABLE_SHOW_LIDER_AND_GENERAL_GUILD
	#define ENABLE_SHOW_LIDER_AND_GENERAL_GUILD_VALUE1 "|cFF00FFFF|H|h[Líder] - "
	#define ENABLE_SHOW_LIDER_AND_GENERAL_GUILD_VALUE2 "|cFF00FF00|H|h[General] - "
#endif
	#define ENABLE_EXTENDED_GUILD_LEVEL //Nivel 40 gremio.
	#define ENABLE_EXTENDED_RENEWAL_FEATURES //Cambiar Lider | Eliminar tierras de gremio
	#define ENABLE_GUILD_LAND_INFO //Info de tierras de Gremio panel.
	#define ENABLE_SKILL_FORGOT_BOOK //Libro olvido Gremial
	#define ENABLE_GUILDWAR_BUTTON //Boton de guerra de gremio ingame
	#define ENABLE_GUILD_DONATE_ATTENDANCE //Nueva donación gremio
	#define ENABLE_NEW_WORLD_GUILDRENEWAL //Sin acabar (Lo uso para activar el ENABLE)
	#define ENABLE_GUILDBANK_LOG //Logs Almacén especial de gremio y banco
	#define ENABLE_GUILDSTORAGE_SYSTEM //Almacén de gremio - Banco
	#define ENABLE_NEW_WAR_OPTIONS //Guerra de gremios rondas, puntos, tiempo
	#define ENABLE_GUILD_WAR_SCORE //Pagina de guerras
	#define ENABLE_GUILD_MARK_RENEWAL //Complemento
#endif
///Fin Gremio
