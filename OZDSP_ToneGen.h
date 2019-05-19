#ifndef __OZDSP_TONEGEN__
#define __OZDSP_TONEGEN__

#include "IPlug_include_in_plug_hdr.h"

#include "../OZDSP_Core/CorePlugBase.h"
#include "../OZDSP_Core/parameter/ParameterInfo.h"

#include "../OZDSP_Core/audio/Oscillator.h"
#include "../OZDSP_Core/audio/VolumeProcessor.h"

class OZDSP_ToneGen : public CorePlugBase
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
