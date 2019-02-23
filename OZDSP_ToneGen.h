#ifndef __OZDSP_TONEGEN__
#define __OZDSP_TONEGEN__

#include "IPlug_include_in_plug_hdr.h"

#include "Oscillator.h"

class OZDSP_ToneGen : public IPlug
{
public:
	OZDSP_ToneGen(IPlugInstanceInfo instanceInfo);
	~OZDSP_ToneGen();

	void Reset();
	void OnParamChange(int paramIdx);
	void ProcessDoubleReplacing(double** inputs, double** outputs, int nFrames);

private:
	double mLevel;

	Oscillator mOscillator;

	static double ScaleParam(double raw);

	void CreatePresets();
};

#endif
