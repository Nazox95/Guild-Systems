//Open char.h add
#include "../../common/tables.h"
#include "../../common/service.h"

//Find 
		CSafebox *			GetMall() const;
		void				LoadMall(int iItemCount, TPlayerItem * pItems);
		void				CloseMall();

		void				SetSafeboxOpenPosition();
		float				GetDistanceFromSafeboxOpen() const;
//add
#ifdef ENABLE_GUILDSTORAGE_SYSTEM
		int					GetGuildstorageSize() const;
		void				QueryGuildstorageSize();
		void				SetGuildstorageSize(int iSize);
		void				ChangeGuildstorageSize(BYTE bSize);

		CSafebox*			GetGuildstorage() const;
		void				LoadGuildstorage(int iSize, int iItemCount, TPlayerItem* pItems);
		void				CloseGuildstorage();
		void				ReqGuildstorageLoad();

		void				SetGuildstorageOpenPosition();
		float				GetDistanceFromGuildstorageOpen() const;
#endif

//find 
	protected:
		CSafebox *			m_pkSafebox;
		int					m_iSafeboxSize;
		int					m_iSafeboxLoadTime;
		bool				m_bOpeningSafebox;	///< Ã¢°í°¡ ¿­±â ¿äÃ» ÁßÀÌ°Å³ª ¿­·ÁÀÖ´Â°¡ ¿©ºÎ, true ÀÏ °æ¿ì ¿­±â¿äÃ»ÀÌ°Å³ª ¿­·ÁÀÖÀ½.

		CSafebox *			m_pkMall;
		int					m_iMallLoadTime;

		PIXEL_POSITION		m_posSafeboxOpen;
//add
#ifdef ENABLE_GUILDSTORAGE_SYSTEM
		CSafebox*			m_pkGuildstorage;
		int					m_iGuildstorageSize;
		int					m_iGuildstorageLoadTime;
		bool				m_bOpeningGuildstorage;

		PIXEL_POSITION		m_posGuildstorageOpen;
#endif

//find 
		//PREVENT_TRADE_WINDOW
	public:
		bool IsOpenSafebox() const { return m_isOpenSafebox ? true : false; }
		void SetOpenSafebox(bool b){m_isOpenSafebox = b;}

		int		GetSafeboxLoadTime() const { return m_iSafeboxLoadTime; }
		void	SetSafeboxLoadTime() { m_iSafeboxLoadTime = thecore_pulse(); }
//add
#ifdef ENABLE_GUILDSTORAGE_SYSTEM
		bool IsOpenGuildstorage() const { return m_isOpenGuildstorage ? true : false; }
		void SetOpenGuildstorage(bool b) { m_isOpenGuildstorage = b; }

		int GetGuildstorageLoadTime() const { return m_iGuildstorageLoadTime; }
		void SetGuildstorageLoadTime() { m_iGuildstorageLoadTime = thecore_pulse(); }
#endif
//find
		//END_PREVENT_TRADE_WINDOW
	private:
		bool	m_isOpenSafebox;
//add
#ifdef ENABLE_GUILDSTORAGE_SYSTEM
		bool	m_isOpenGuildstorage;
#endif
