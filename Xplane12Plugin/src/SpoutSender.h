#pragma once


#include "Spout.h"


class SpoutSender {
public:
	SpoutSender();
	void SendFrame();
	void Shutdown();


private:
	void InitIfNeeded();


	Spout spout;
	bool initialized{ false };
};