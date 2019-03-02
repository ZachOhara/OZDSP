#ifndef __OZDSP_TONEGEN__
#define __OZDSP_TONEGEN__

#include "IPlug_include_in_plug_hdr.h"

#include "../OZDSP_Common/CommonPlugBase.h"
#include "../OZDSP_Common/ParameterInfo.h"

#include "../OZDSP_Common/CommonParameters.h"
#include "../OZDSP_Common/Oscillator.h"
#include "../OZDSP_Common/VolumeControl.h"

class OZDSP_ToneGen : public CommonPlugBase
{
public:
	OZDSP_ToneGen(IPlugInstanceInfo instanceInfo);
	~OZDSP_ToneGen();

	void Reset() override;
	void OnParamChange(int paramIdx) override;
	void ProcessDoubleReplacing(double** inputs, double** outputs, int nFrames) override;

protected:
	void CreatePresets() override;

private:
	Oscillator mOscillator;
	VolumeControl mVolumeControl;
};

#endif
