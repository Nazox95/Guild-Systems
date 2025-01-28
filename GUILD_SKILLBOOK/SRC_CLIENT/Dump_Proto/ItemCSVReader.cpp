//Find
int get_Item_Type_Value(string inputString)
{
	string arType[] = {
		"ITEM_NONE", //0
//Add new value
int get_Item_Type_Value(string inputString)
{
	string arType[] = {
		"ITEM_NONE", //0
    [...]
#ifdef ENABLE_SKILL_FORGOT_BOOK
		"ITEM_SKILLFORGETGUILD", //37
#endif
	};

//Now find
int get_Item_SubType_Value(int type_value, string inputString)
{
	[...]
	string* arSubType[] = { 0,
	[...]

//Add new value
int get_Item_SubType_Value(int type_value, string inputString)
{
	[...]
	string* arSubType[] = { 0,
	[...]
#ifdef ENABLE_SKILL_FORGOT_BOOK
		0,			//37 Libro Gremio
#endif
	};
	int arNumberOfSubtype[38]{}; //Add +1 in my case skillbook is 37, so here i need change to 38
	arNumberOfSubtype[0] = 0;
	arNumberOfSubtype[1] = sizeof(arSub1) / sizeof(arSub1[0]);
#ifdef ENABLE_SKILL_FORGOT_BOOK
	0; //37 Libro gremio
#endif
