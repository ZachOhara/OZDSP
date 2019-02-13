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
	kWidth = GUI_WIDTH,
	kHeight = GUI_HEIGHT,
	kKnobFrames = 128,
	kWaveformFrames = 4,

	kPitchKnobX = 15,
	kPitchKnobY = 50,
	kVolumeKnobX = 155,
	kVolumeKnobY = 90,
	kWaveSelectX = 155,
	kWaveSelectY = 10,
};

OZDSP_ToneGen::OZDSP_ToneGen(IPlugInstanceInfo instanceInfo) :
	IPLUG_CTOR(kNumParams, kNumPrograms, instanceInfo),
	mLevel(0.5)
{
	TRACE;

	//arguments are: name, defaultVal, minVal, maxVal, step, label
	GetParam(kPitchPid)->InitDouble("Frequency", 440.0, 50.0, 10000.0, 0.01, "Hz");
	GetParam(kPitchPid)->SetShape(3.0);
	GetParam(kVolumePid)->InitDouble("Volume", 50.0, 0.0, 100.0, 0.01, "");
	GetParam(kWaveformPid)->InitEnum("Waveform", 0, kNumOscillatorModes);

	// Set up waveforms
	GetParam(kWaveformPid)->SetDisplayText(0, "Sine");
	GetParam(kWaveformPid)->SetDisplayText(1, "Triangle");
	GetParam(kWaveformPid)->SetDisplayText(2, "Square");
	GetParam(kWaveformPid)->SetDisplayText(3, "Sawtooth");

	IGraphics* pGraphics = MakeGraphics(this, kWidth, kHeight);
	pGraphics->AttachBackground(BACKGROUND_RID, BACKGROUND_FN);

	IBitmap knob80 = pGraphics->LoadIBitmap(KNOB_80_RID, KNOB_80_FN, kKnobFrames);
	IBitmap knob120 = pGraphics->LoadIBitmap(KNOB_120_RID, KNOB_120_FN, kKnobFrames);
	IBitmap waveSelect = pGraphics->LoadIBitmap(WAVEFORMS_RID, WAVEFORMS_FN, kWaveformFrames);

	pGraphics->AttachControl(new IKnobMultiControl(this, kPitchKnobX, kPitchKnobY, kPitchPid, &knob120));
	pGraphics->AttachControl(new IKnobMultiControl(this, kVolumeKnobX, kVolumeKnobY, kVolumePid, &knob80));
	pGraphics->AttachControl(new ISwitchControl(this, kWaveSelectX, kWaveSelectY, kWaveformPid, &waveSelect));

	AttachGraphics(pGraphics);

	CreatePresets();
}

OZDSP_ToneGen::~OZDSP_ToneGen() {}

void OZDSP_ToneGen::CreatePresets()
{
	// TODO
	/*
	MakePreset("clean", 100.0);
	MakePreset("distorted", 80.0);
	MakePreset("wooo", 40.0);
	MakePreset("waaa", 20.0);
	MakePreset("buzz", 0.1);
	*/
}

void OZDSP_ToneGen::ProcessDoubleReplacing(double** inputs, double** outputs, int nFrames)
{
	// Mutex is already locked for us.
	const int nChannels = 2;

	for (int i = 0; i < nFrames; i++)
	{
		double sampleValue = mOscillator.getNextSample();
		sampleValue *= mLevel;
		for (int j = 0; j < nChannels; j++)
		{
			outputs[j][i] = sampleValue;
		}
	}
}

void OZDSP_ToneGen::Reset()
{
	TRACE;
	IMutexLock lock(this);
	mOscillator.setSampleRate(GetSampleRate());
}

void OZDSP_ToneGen::OnParamChange(int paramIdx)
{
	IMutexLock lock(this);

	switch (paramIdx)
	{
	case kPitchPid:
		mOscillator.setFrequency(GetParam(kPitchPid)->Value());
		break;
	case kWaveformPid:
		mOscillator.setMode(GetParam(kWaveformPid)->Int());
		break;
	case kVolumePid:
		mLevel = scaleParam(GetParam(kVolumePid)->Value() / 100.0);
		break;

	default:
		break;
	}
}

double OZDSP_ToneGen::scaleParam(double raw)
{
	return pow(raw, exp(1));
}
