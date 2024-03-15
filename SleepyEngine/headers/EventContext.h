#pragma once
#include <map>
#include <string>
class SleepyEngine;

struct EventContext {
	SleepyEngine* engine;
	std::map<std::string, void*> params;

	EventContext() : engine(nullptr) {}
};