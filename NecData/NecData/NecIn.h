#pragma once
#include "NecCommand.h"
#include "FileStructure.h"
#include <vector>
#include "CM.h"
#include "CE.h"
#include "GW.h"
#include "GE.h"
#include "GN.h"
#include "FR.h"
#include "EX.h"
#include "PT.h"
#include "RP.h"
#include "EN.h"

#ifdef NECDATA_EXPORTS  
#define NECDATA_API __declspec(dllexport)   
#else  
#define NECDATA_API __declspec(dllimport)   
#endif 


class NecIn: public FileStructure
{
public:
	NECDATA_API NecIn();
	NECDATA_API ~NecIn();

	NECDATA_API void setCM(CM &cm);
	NECDATA_API void setCE(CE &ce);
	NECDATA_API void setGW(std::vector<GW *> *gw);
	NECDATA_API void pushGW(GW &gw);
	NECDATA_API void setGE(GE &ge);
	NECDATA_API void setGN(GN &gn);
	NECDATA_API void setFR(FR &fr);
	NECDATA_API void setEX(std::vector<EX*> *ex);
	NECDATA_API void pushEX(EX &ex);
	NECDATA_API void setPT(PT &pt);
	NECDATA_API void setRP(RP &rp);
	NECDATA_API void setEN(EN &en);

	NECDATA_API CM *getCM();
	NECDATA_API CE *getCE();
	NECDATA_API std::vector<GW *> *getGW();
	NECDATA_API GE *getGE();
	NECDATA_API GN *getGN();
	NECDATA_API FR *getFR();
	NECDATA_API std::vector<EX *> *getEX();
	NECDATA_API PT *getPT();
	NECDATA_API RP *getRP();
	NECDATA_API EN *getEN();

	


private:
	CM *cm;
	CE *ce;
	std::vector<GW *> *gw;
	GE *ge;
	GN *gn;
	FR *fr;
	std::vector<EX *> *ex;
	PT *pt;
	RP *rp;
	EN *en;

};

