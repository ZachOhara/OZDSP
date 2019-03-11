#ifndef __OZDSP_TONEGEN__
#define __OZDSP_TONEGEN__

#include "IPlug_include_in_plug_hdr.h"

#include "../OZDSP_Common/CommonPlugBase.h"
#include "../OZDSP_Common/parameter/ParameterInfo.h"

#include "../OZDSP_Common/processing/Oscillator.h"
#include "../OZDSP_Common/processing/VolumeProcessor.h"

class OZDSP_ToneGen : public CommonPlugBase
{
public:
	OZDSP_ToneGen(IPlugInstanceInfo instanceInfo);
	~OZDSP_ToneGen();

	void ProcessDoubleReplacing(double** inputs, double** outputs, int nFrames) override;

protected:
	void CreatePresets() override;

private:
	Oscillator mOscillator;
	VolumeProcessor mVolumeProcessor;
};

#endif
