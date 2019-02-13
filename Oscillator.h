#ifndef __OSCILLATOR__
#define __OSCILLATOR__

#include <iostream>
#include <math.h>

# define M_PI 3.14159265358979323846

enum OscillatorMode {
	kModeSine,
	kModeTriangle,
	kModeSquare,
	kModeSawtooth,
	kNumOscillatorModes
};

class Oscillator
{
public:
	Oscillator();
	~Oscillator();

	void setMode(int newMode);
	void setFrequency(double frequency);
	void setSampleRate(double sampleRate);

	double getNextSample();

private:
	int mOscillatorMode;

	double mFrequency;
	double mSampleRate;

	double mPhasePosition;
	double mPhaseIncrement;

	void updatePhaseIncrement();
};

#endif // !__OSCILLATOR__

