//Open GuildManager.h add
#include "Peer.h"
#include <queue>
#include <utility>
#include "../../libsql/libsql.h"
#include "../../libpoly/Poly.h"
#include "../../common/service.h"

//Find and replace (TGuildDeclareInfo, TGuildWaitStartInfo, TGuildWarPQElement)
enum
{
    GUILD_WARP_WAR_CHANNEL = 99
};

class CGuildWarReserve;

struct TGuildDeclareInfo
{
	BYTE bType;
#ifdef ENABLE_NEW_WAR_OPTIONS
	BYTE bRound;
	BYTE bPoints;
	BYTE bTime;
#endif
	DWORD dwGuildID[2];

#ifdef ENABLE_NEW_WAR_OPTIONS
	TGuildDeclareInfo(BYTE _bType, BYTE _bRound, BYTE _bPoints, BYTE _bTime, DWORD _dwGuildID1, DWORD _dwGuildID2)
		: bType(_bType), bRound(_bRound), bPoints(_bPoints), bTime(_bTime)
#else
	TGuildDeclareInfo(BYTE _bType, DWORD _dwGuildID1, DWORD _dwGuildID2)
		: bType(_bType)
#endif
	{
		dwGuildID[0] = _dwGuildID1;
		dwGuildID[1] = _dwGuildID2;
	}

	bool operator < (const TGuildDeclareInfo& r) const
	{
		return ((dwGuildID[0] < r.dwGuildID[0]) || ((dwGuildID[0] == r.dwGuildID[0]) && (dwGuildID[1] < r.dwGuildID[1])));
	}

	TGuildDeclareInfo& operator = (const TGuildDeclareInfo& r)
	{
		bType = r.bType;
#ifdef ENABLE_NEW_WAR_OPTIONS
		bRound = r.bRound;
		bPoints = r.bPoints;
		bTime = r.bTime;
#endif
		dwGuildID[0] = r.dwGuildID[0];
		dwGuildID[1] = r.dwGuildID[1];
		return *this;
	}
};

struct TGuildWaitStartInfo
{
	BYTE bType;
#ifdef ENABLE_NEW_WAR_OPTIONS
	BYTE bRound;
	BYTE bPoints;
	BYTE bTime;
#endif
	DWORD GID[2];
	long lWarPrice;
	long lInitialScore;
	CGuildWarReserve* pkReserve;

	TGuildWaitStartInfo(BYTE _bType,
#ifdef ENABLE_NEW_WAR_OPTIONS
		BYTE _bRound,
		BYTE _bPoints,
		BYTE _bTime,
#endif
		DWORD _g1,
		DWORD _g2,
		long _lWarPrice,
		long _lInitialScore,
		CGuildWarReserve* _pkReserve)
#ifdef ENABLE_NEW_WAR_OPTIONS
		: bType(_bType), bRound(_bRound), bPoints(_bPoints), bTime(_bTime), lWarPrice(_lWarPrice), lInitialScore(_lInitialScore), pkReserve(_pkReserve)
#else
		: bType(_bType), lWarPrice(_lWarPrice), lInitialScore(_lInitialScore), pkReserve(_pkReserve)
#endif
	{
		GID[0] = _g1;
		GID[1] = _g2;
	}

	bool operator < (const TGuildWaitStartInfo& r) const
	{
		return ((GID[0] < r.GID[0]) || ((GID[0] == r.GID[0]) && (GID[1] < r.GID[1])));
	}
};

struct TGuildWarPQElement
{
	bool bEnd;
	BYTE bType;
#ifdef ENABLE_NEW_WAR_OPTIONS
	BYTE bRound;
	BYTE bPoints;
	BYTE bTime;
#endif
	DWORD GID[2];
	DWORD iScore[2];
	DWORD iBetScore[2];

#ifdef ENABLE_NEW_WAR_OPTIONS
	TGuildWarPQElement(BYTE _bType, BYTE _bRound, BYTE _bPoints, BYTE _bTime, DWORD GID1, DWORD GID2) : bEnd(false), bType(_bType)
#else
	TGuildWarPQElement(BYTE _bType, DWORD GID1, DWORD GID2) : bEnd(false), bType(_bType)
#endif
	{
		bType = _bType;
#ifdef ENABLE_NEW_WAR_OPTIONS
		bRound = _bRound;
		bPoints = _bPoints;
		bTime = _bTime;
#endif
		GID[0] = GID1;
		GID[1] = GID2;
		iScore[0] = iScore[1] = 0;
		iBetScore[0] = iBetScore[1] = 0;
	}
};

//Find
class CGuildManager : public singleton<CGuildManager>
{
    public:
	CGuildManager();
	virtual ~CGuildManager();

	void	Initialize();

	void	Load(DWORD dwGuildID);

	TGuild & TouchGuild(DWORD GID);

	void	Update();

	void	OnSetup(CPeer * peer);
//replace
#ifdef ENABLE_NEW_WAR_OPTIONS
	void	StartWar(BYTE bType, DWORD GID1, DWORD GID2, BYTE bRound, BYTE bPoints, BYTE bTime, CGuildWarReserve* pkReserve = nullptr);
#else
	void	StartWar(BYTE bType, DWORD GID1, DWORD GID2, CGuildWarReserve * pkReserve = NULL);
#endif
//Find
	void	UpdateScore(DWORD guild_gain_point, DWORD guild_opponent, int iScore, int iBetScore);
//Replace
#ifdef ENABLE_NEW_WAR_OPTIONS
	void	AddDeclare(BYTE bType, DWORD guild_from, DWORD guild_to, BYTE bRound, BYTE bPoints, BYTE bTime);
#else
	void	AddDeclare(BYTE bType, DWORD guild_from, DWORD guild_to);
#endif
	void	RemoveDeclare(DWORD guild_from, DWORD guild_to);
