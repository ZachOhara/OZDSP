#ifndef __OZDSP_TONEGEN__
#define __OZDSP_TONEGEN__

#include "IPlug_include_in_plug_hdr.h"

#include "../OZDSP_Common/CommonParameters.h"
#include "../OZDSP_Common/Oscillator.h"
#include "../OZDSP_Common/ParamValueLabel.h"
#include "../OZDSP_Common/VolumeControl.h"

class OZDSP_ToneGen : public IPlug
{
public:
	OZDSP_ToneGen(IPlugInstanceInfo instanceInfo);
	~OZDSP_ToneGen();

	void Reset();
	void OnParamChange(int paramIdx);
	void ProcessDoubleReplacing(double** inputs, double** outputs, int nFrames);

private:
	Oscillator mOscillator;
	VolumeControl mVolumeControl;

	ParamValueLabel* mpPitchLabel;
	ParamValueLabel* mpVolumeLabel;

	void CreatePresets();
};

#endif
