//Open building.h find
			DWORD	GetVnum()		{ return m_pProto ? m_pProto->dwVnum : 0; }
			DWORD	GetGroup()		{ return m_pProto ? m_pProto->dwGroupVnum : 0; }
//add
#ifdef ENABLE_GUILDBANK_LOG
			INT GetPrice() const { return m_pProto ? m_pProto->dwPrice : 0; }
#endif
//find
	class CLand
	{
		public:
			CLand(TLand * pData);
			~CLand();

			void	Destroy();

			const TLand & GetData();
			void	PutData(const TLand * data);

			DWORD	GetID() const { return m_data.dwID; }
			void	SetOwner(DWORD dwGID);
			DWORD	GetOwner() const { return m_data.dwGuildID; }
//add
#ifdef ENABLE_GUILDBANK_LOG
			INT GetPrice() const { return m_data.dwPrice; }
#endif
