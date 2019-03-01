#include "OZDSP_ToneGen.h"
#include "IPlug_include_in_plug_src.h"
#include "IControl.h"
#include "resource.h"

const int kNumPrograms = 0;

enum EParams
{
	kPitchPid,
	kWaveformPid,
	kVolumePid,
	kNumParams
};

enum ELayout
{
	kPitchLabelX = 15,
	kPitchLabelY = 160,
	kPitchLabelWidth = 120,

	kVolumeLabelX = 155,
	kVolumeLabelY = 160,
	kVolumeLabelWidth = 80
};

std::vector<ParameterInfo> kParameterList  = 
{
	ParameterInfo()
		.InitParam("Pitch", kPitchPid, 15, 50)
		.MakeFrequencyParam(),
	ParameterInfo()
		.InitParam("Volume", kVolumePid, 155, 90)
		.MakeVolumeReductionParam(),
	ParameterInfo()
		.InitParam("Waveform", kWaveformPid, 155, 10)
		.MakeWaveformParam()
};

OZDSP_ToneGen::OZDSP_ToneGen(IPlugInstanceInfo instanceInfo) :
	CommonPlugBase(instanceInfo, kNumParams, kNumPrograms,
		MakeGraphics(this, GUI_WIDTH, GUI_HEIGHT),
		COMMONPLUG_CTOR_PARAMS)
{	
	GetGraphics()->AttachBackground(BACKGROUND_RID, BACKGROUND_FN);

	IBitmap knob80 = GetGraphics()->LoadIBitmap(KNOB_80_RID, KNOB_80_FN, KNOB_FRAMES);
	IBitmap knob120 = GetGraphics()->LoadIBitmap(KNOB_120_RID, KNOB_120_FN, KNOB_FRAMES);
	IBitmap waveSelect = GetGraphics()->LoadIBitmap(WAVEFORMS_RID, WAVEFORMS_FN, WAVESELECT_FRAMES);

	InitializeParameter(kParameterList[0], knob120);
	InitializeParameter(kParameterList[1], knob80);
	InitializeParameter(kParameterList[2], waveSelect);

	// TODO clean up this
	mpPitchLabel = new ParamValueLabel(this, kPitchPid, kPitchLabelX, kPitchLabelY, kPitchLabelWidth);
	InitFrequencyLabel(mpPitchLabel);
	mpVolumeLabel = new ParamValueLabel(this, kVolumePid, kVolumeLabelX, kVolumeLabelY, kVolumeLabelWidth);

	GetGraphics()->AttachControl(mpPitchLabel);
	GetGraphics()->AttachControl(mpVolumeLabel);

	FinishConstruction();
}

OZDSP_ToneGen::~OZDSP_ToneGen() {}

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
		sampleValue = mVolumeControl.GetAdjustedSample(sampleValue);
		for (int j = 0; j < nChannels; j++)
		{
			outputs[j][i] = sampleValue;
		}
	}
}

void OZDSP_ToneGen::Reset()
{
	CommonPlugBase::Reset();
	mOscillator.SetSampleRate(GetSampleRate());
}

void OZDSP_ToneGen::OnParamChange(int paramIdx)
{
	CommonPlugBase::OnParamChange(paramIdx);

	// TODO clean this up
	switch (paramIdx)
	{
	case kPitchPid:
		mOscillator.SetFrequency(GetParam(kPitchPid)->Value());
		mpPitchLabel->UpdateDisplay();
		break;
	case kWaveformPid:
		mOscillator.SetMode(GetParam(kWaveformPid)->Int());
		break;
	case kVolumePid:
		HandleVolumeParamChange(GetParam(kVolumePid), &mVolumeControl);
		mpVolumeLabel->UpdateDisplay();
		break;
	default:
		break;
	}
}
