#pragma once
#include "Complex.h"
#include <vector>
#include "FileStructure.h"

#ifdef NECDATA_EXPORTS  
#define NECDATA_API __declspec(dllexport)   
#else  
#define NECDATA_API __declspec(dllimport)   
#endif 

using namespace Math;

class NecOut: public FileStructure {
public:
	NECDATA_API NecOut();
	NECDATA_API ~NecOut();
	

	class Source {
	public:
		NECDATA_API Source();
		NECDATA_API Source(int tag, int seg, double vRe, double vIm, double iRe, double iIm, double zRe, double zIm, double aRe, double aIm, double power);
		NECDATA_API Complex getI();
		NECDATA_API Complex getV();
		NECDATA_API Complex getZ();
		NECDATA_API ~Source();
	private:
		int tag; 
		int seg;
		Complex v;
		Complex i;
		Complex z;
		Complex a;
		double power;
	};

	class RadiationPattern {
	public:
		NECDATA_API RadiationPattern(double theta, double phi, double verticalGain, double horisontalGain, double totalGain, double axialPolarisation, double polarisationTilt, std::string polarisationSense, double eThetaMagnitude, double eThetaPhase, double ePhiMagnitude, double ePhiPhase);
		NECDATA_API ~RadiationPattern();
		NECDATA_API RadiationPattern();
		NECDATA_API double getTheta();
		NECDATA_API double getPhi();
		NECDATA_API double getGain();
		NECDATA_API double getMagnitude();
		NECDATA_API double getPhase();
		NECDATA_API Complex getE();
	
	private:
		double theta;
		double phi;
		double verticalGain;
		double horisontalGain;
		double totalGain; 
		double axialPolarisation; 
		double polarisationTilt;
		std::string polarisationSense;
		double eThetaMagnitude;
		double eThetaPhase;
		double ePhiMagnitude;
		double ePhiPhase;
	};

	NECDATA_API void addSource(int tag, int seg, double vRe, double vIm, double iRe, double iIm, double zRe, double zIm, double aRe, double aIm, double power);
	NECDATA_API std::vector<NecOut::Source> getSources();

	NECDATA_API void addRadiationPattern(double theta, double phi, double verticalGain, double horisontalGain, double totalGain, double axialPolarisation, double polarisationTilt, std::string polarisationSense, double eThetaMagnitude, double eThetaPhase, double ePhiMagnitude, double ePhiPhase);
	NECDATA_API std::vector<NecOut::RadiationPattern> getRadiationPatterns();

private:
	std::vector<NecOut::Source> sources;
	std::vector<NecOut::RadiationPattern> radiationPatters;
};

