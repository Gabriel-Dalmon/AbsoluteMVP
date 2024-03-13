#pragma once
#include "System.h"
#include "EventsName.h"
#include "FunctionCommand.h"
#include "MethodCommand.h"

typedef enum EventCallbackReturn
{
	SUCCESS = 0,
	FAILURE,
	STOP_PROPAGATE,
	EVENT_CALLBACK_RETURN_COUNT
}EventCallback;

class EventManager : public System
{
public:
	EventManager() {};
	~EventManager() {};

	// Init
	void Init();

	// Setter / Getter


	void subscribe(EventName eventName, void(*callback)())
	{
		eventCallbacksMap[eventName].push_back(new FunctionCommand(callback));
		std::cout << "Pushed Back" << eventName << "|" << eventCallbacksMap[eventName].size() << "\n";
	}

	template<typename T, typename baseClass>
	void subscribe(EventName eventName, void(T::* methodPointer)(), baseClass base)
	{
		eventCallbacksMap[eventName].push_back(new MethodCommand<T>(base, methodPointer));
		std::cout << "Pushed Back" << eventName << "|" << eventCallbacksMap[eventName].size() << "\n";
	}

	//SHOULD BE TURNED BACK INTO A TEMPLATE FUNCTION - in order not to allocate a whole new command
	void unsubscribe(EventName eventName, AbstractCommand* commandToDelete)
	{
		std::cout << "Pre Removed" << eventName << "|" << eventCallbacksMap[eventName].size() << "\n";
		std::vector<AbstractCommand*>* eventCommands = &eventCallbacksMap[eventName];
		int index = 0;
		for (AbstractCommand* command : *eventCommands) {
			if (commandToDelete->compareCommandsIdentifier(command->commandIdentifier)) {
				eventCommands->erase(eventCommands->begin() + index);
			}
			index++;
		}
		std::cout << "Removed" << eventName << "|" << eventCallbacksMap[eventName].size() << "\n";

	}

	void HandleEvents();

	void OnKeyPressed(int key);
	void OnKeyReleased(int key);

	// Release
	void Release();

private:

	EventContext context;
	std::unordered_map<EventName, std::vector<AbstractCommand*>> eventCallbacksMap;

	std::vector<int> m_InputList;
	std::map<int, EventName> m_CodeToEventNamePressed;
	std::map<int, EventName> m_CodeToEventNameReleased;
	std::map<EventName, int> m_EventPressControl;
};


