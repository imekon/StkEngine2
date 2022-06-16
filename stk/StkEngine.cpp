#include <math.h>

#include "STKEngine.h"
#include "Utilities.h"

using namespace stk;

#define DEFAULT_TEMPO 120.0

StkEngine::StkEngine()
{
#ifdef _DEBUG
	//// Get current flag
	//int tmpFlag = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);

	//// Turn on leak-checking bit.
	//tmpFlag |= _CRTDBG_LEAK_CHECK_DF | _CRTDBG_CHECK_CRT_DF;

	//// Set flag to the new value.
	//_CrtSetDbgFlag(tmpFlag);
#endif

	Stk::setSampleRate(44100.0);

	setTempo(DEFAULT_TEMPO, 4);

	RtAudio::StreamParameters parameters;
	parameters.deviceId = dac.getDefaultOutputDevice();
	parameters.nChannels = 2;
	RtAudioFormat format = (sizeof(StkFloat) == 8) ? RTAUDIO_FLOAT64 : RTAUDIO_FLOAT32;
	unsigned int bufferFrames = RT_BUFFER_SIZE;
	dac.openStream(&parameters, nullptr, format, static_cast<unsigned int>(Stk::sampleRate()), &bufferFrames, rtAudioTick, this);

	globals[STK_GLOBAL_STATUS] = 0.0;
	globals[STK_GLOBAL_REVERB_MIX] = 0.5;
	globals[STK_GLOBAL_REVERB_DAMPING] = reverb.getDamping();
	globals[STK_GLOBAL_REVERB_MODE] = reverb.getMode() ? -1.0 : 0.0;
	globals[STK_GLOBAL_REVERB_ROOMSIZE] = reverb.getRoomSize();
	globals[STK_GLOBAL_REVERB_WIDTH] = reverb.getWidth();
	globals[STK_GLOBAL_VOLUME] = 0.7;

	tickEvent = CreateEvent(nullptr, FALSE, FALSE, L"StkTickEvent");
}

StkEngine::~StkEngine()
{
	dac.closeStream();

	CloseHandle(tickEvent);
}

void StkEngine::setGlobal(STK_GLOBALS global, stk::StkFloat value)
{
	globals[global] = value;

	switch(global)
	{
	case STK_GLOBAL_REVERB_MIX:
		reverb.setEffectMix(value);
		break;

	case STK_GLOBAL_REVERB_DAMPING:
		reverb.setDamping(value);
		break;

	case STK_GLOBAL_REVERB_ROOMSIZE:
		reverb.setRoomSize(value);
		break;

	case STK_GLOBAL_REVERB_WIDTH:
		reverb.setWidth(value);
		break;

	case STK_GLOBAL_REVERB_MODE:
		reverb.setMode(value != 0);
		break;

	default:
		break;
	}
}

void StkEngine::setTempo(StkFloat tempo, int steps)
{
	double duration = (4.0 * 60.0 * 1000.0 / tempo) / steps;
	Utilities::trace("setTempo: duration %1.2f\n", duration);
	setInterval(static_cast<int>(duration));
}

int StkEngine::rtAudioTick(void *outputBuffer,
	void *inputBuffer,
	unsigned int nBufferFrames,
	double streamTime,
	RtAudioStreamStatus status,
	void *dataPointer)
{
	StkEngine *engine = static_cast<StkEngine *>(dataPointer);
	register StkFloat *samples = static_cast<StkFloat *>(outputBuffer);
	double left, right;
	double vuLeft = 0.0;
	double vuRight = 0.0;
	for (unsigned int i = 0; i < nBufferFrames; i++)
	{
		engine->oscManager.tick(&engine->reverb, left, right);

		vuLeft += left;
		vuRight += right;

		*samples++ = left * engine->globals[STK_GLOBAL_VOLUME];
		*samples++ = right * engine->globals[STK_GLOBAL_VOLUME];
	}

	engine->globals[STK_GLOBAL_VU_LEFT] = vuLeft / nBufferFrames;
	engine->globals[STK_GLOBAL_VU_RIGHT] = vuRight / nBufferFrames;

	return 0;
}

void StkEngine::tick()
{
	if (!SetEvent(tickEvent))
		Utilities::trace("tick SetEvent failed\n");
}

void StkEngine::start()
{
	Timer::start();

	dac.startStream();
}

void StkEngine::stop()
{
	Timer::stop();

	dac.stopStream();
}

void StkEngine::addOsc(ParametricOsc* osc)
{
	oscManager.addOscillator(osc);
}

bool StkEngine::removeOsc(ParametricOsc* osc)
{
	return oscManager.removeOscillator(osc);
}

bool StkEngine::waitTick() const
{
	DWORD result = WaitForSingleObject(tickEvent, INFINITE);

	if (result == WAIT_OBJECT_0)
		return true;

	return false;
}
