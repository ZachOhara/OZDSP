#include "OZDSP_ToneGen.h"
#include "IPlug_include_in_plug_src.h"
#include "resource.h"

const int kNumPrograms = 0;

enum EParams
{
	kPitchPid,
	kVolumePid,
	kWaveformPid,
	kNumParams
};

std::vector<ParameterInfo> kParameterList =
{
	ParameterInfo()
		.InitParam("Pitch", kPitchPid, PITCH_CONTROL_ID, 26, 50)
		.InitLabel()
		.MakeFrequencyParam(),
	ParameterInfo()
		.InitParam("Volume", kVolumePid, VOLUME_CONTROL_ID, 150, 85)
		.InitLabel()
		.MakeVolumeReductionParam(),
	ParameterInfo()
		.InitParam("Waveform", kWaveformPid, WAVEFORM_CONTROL_ID, 155, 10)
		.MakeWaveformParam(),
};

OZDSP_ToneGen::OZDSP_ToneGen(IPlugInstanceInfo instanceInfo) :
	CorePlugBase(instanceInfo, kNumParams, kNumPrograms,
		MakeGraphics(this, GUI_WIDTH, GUI_HEIGHT),
		COMMONPLUG_CTOR_PARAMS)
{
	SetBackground(BACKGROUND_ID, BACKGROUND_FN);

	RegisterBitmap(PITCH_CONTROL_ID, PITCH_CONTROL_FN, PITCH_CONTROL_FRAMES);
	RegisterBitmap(VOLUME_CONTROL_ID, VOLUME_CONTROL_FN, VOLUME_CONTROL_FRAMES);
	RegisterBitmap(WAVEFORM_CONTROL_ID, WAVEFORM_CONTROL_FN, WAVEFORM_CONTROL_FRAMES);

	AddParameterList(kParameterList);

	RegisterProcessor(&mOscillator);
	mOscillator.RegisterParameter(kPitchPid, Oscillator::kFrequencyParam);
	mOscillator.RegisterParameter(kWaveformPid, Oscillator::kWaveformParam);

	RegisterProcessor(&mVolumeProcessor);
	mVolumeProcessor.RegisterParameter(kVolumePid, VolumeProcessor::kDecibelsParam);

	FinishConstruction();
}

OZDSP_ToneGen::~OZDSP_ToneGen()
{
}

void OZDSP_ToneGen::CreatePresets()
{
	// No presets
}

void OZDSP_ToneGen::ProcessDoubleReplacing(double** inputs, double** outputs, int nFrames)
{
	// Mutex is already locked for us.
	const int nChannels = 2;

	for (int i = 0; i < nFrames; i++)
	{
		double sampleValue = mOscillator.GetNextSample();
		sampleValue = mVolumeProcessor.GetAdjustedSample(sampleValue);
		for (int j = 0; j < nChannels; j++)
		{
			outputs[j][i] = sampleValue;
		}
	}
}
