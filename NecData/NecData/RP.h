#pragma once
#include <string>
#include "NecCommand.h"

#ifdef NECDATA_EXPORTS  
#define NECDATA_API __declspec(dllexport)   
#else  
#define NECDATA_API __declspec(dllimport)   
#endif 


class RP: public NecCommand {
public:
	NECDATA_API RP(int mode, int thetaNumber, int phiNumber, std::string XNDA,	double theta0, double phi0, double thetaInc, double phiInc);
	NECDATA_API RP(RP &rp);
	NECDATA_API ~RP();
	NECDATA_API std::string toString();
	NECDATA_API int getThetaNumber();
	NECDATA_API int getPhiNumber();
	NECDATA_API int getThetaInc();
	NECDATA_API int getPhiInc();
private:
	int mode;
	int thetaNumber;
	int phiNumber;
	std::string XNDA;
	double theta0;
	double phi0;
	double thetaInc;
	double phiInc;
};

