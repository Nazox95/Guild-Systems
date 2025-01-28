//Find int get_Item_Type_Value(string inputString) and add
int get_Item_Type_Value(string inputString)
{
	string arType[] = {
		"ITEM_NONE", //0
    [...]
#ifdef ENABLE_SKILL_FORGOT_BOOK
		"ITEM_SKILLFORGETGUILD", //37
#endif
	};

//Now find int get_Item_SubType_Value(int type_value, string inputString) and add
int get_Item_SubType_Value(int type_value, string inputString) 
{
  [...]
	static string* arSubType[] = {0,	//0
		arSub1,		//1
    [...]
#ifdef ENABLE_SKILL_FORGOT_BOOK
		0,			//37 Libro olvido
#endif
	};
	static int arNumberOfSubtype[_countof(arSubType)] = {
		0,
		sizeof(arSub1)/sizeof(arSub1[0]),
    [...]
#ifdef ENABLE_SKILL_FORGOT_BOOK
		0, //Libro gremio
#endif
	};
