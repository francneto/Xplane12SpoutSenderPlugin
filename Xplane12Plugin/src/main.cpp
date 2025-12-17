#include "XPLMPlugin.h"
#include "XPLMDisplay.h"
#include "XPLMGraphics.h"
#include "XPLMUtilities.h"
#include "SpoutSender.h"


static SpoutSender gSpout;
XPLMDrawingPhase selectedPhase = xplm_Phase_Window;

int DrawCallback(
	XPLMDrawingPhase phase,
	int isBefore,
	void* refcon)
{

	if (isBefore)
		return 1;
	if (phase != selectedPhase)
		return 1;


	XPLMSetGraphicsState(
		0,  // fog
		0,  // number of texture units
		0,  // lighting
		0,  // alpha testing
		0,   // alpha blending
		0,   // depth testing
		0   // depth writing
	);

	gSpout.SendFrame();
	return 1;
}


PLUGIN_API int XPluginStart(
	char* outName,
	char* outSig,
	char* outDesc)
{
	strncpy_s(outName, 256, "X-Plane Spout Sender", _TRUNCATE);
	strncpy_s(outSig, 256, "example.xplane.spout", _TRUNCATE);
	strncpy_s(outDesc, 256, "Spout output for X-Plane 12", _TRUNCATE);


	XPLMRegisterDrawCallback(
		DrawCallback,
		selectedPhase,
		0,
		nullptr
	);


	return 1;
}


PLUGIN_API void XPluginStop(void)
{
	XPLMUnregisterDrawCallback(DrawCallback, selectedPhase, 0, nullptr);
	gSpout.Shutdown();
}


PLUGIN_API int XPluginEnable(void) { return 1; }
PLUGIN_API void XPluginDisable(void) {}
PLUGIN_API void XPluginReceiveMessage(
	XPLMPluginID from,
	int msg,
	void* param) {
}