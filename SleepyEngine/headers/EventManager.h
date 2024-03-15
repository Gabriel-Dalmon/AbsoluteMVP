#pragma once
#include "System.h"
#include "EventsName.h"
#include "FunctionCommand.h"
#include "MethodCommand.h"
#include "EventContext.h"

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


	void subscribe(EventName eventName, void(*callback)(EventContext context),EventContext context ,std::string id)
	{
		eventCallbacksMap[eventName].push_back(new FunctionCommand(callback));
		std::pair<EventName, AbstractCommand*> m = { eventName, eventCallbacksMap[eventName].back() };
		callbacks.insert({ id, m });
		eventCallbacksContextMap.insert({ eventCallbacksMap[eventName].back(), context });
		std::cout << "Pushed Back" << eventName << "|" << eventCallbacksMap[eventName].size() << "\n";
	}

	template<typename T, typename baseClass>
	void subscribe(EventName eventName, void(T::* methodPointer)(), baseClass base, std::string id)
	{
		eventCallbacksMap[eventName].push_back(new MethodCommand<T>(base, methodPointer));
		std::pair<EventName, AbstractCommand*> m = { eventName, eventCallbacksMap[eventName].back() };
		callbacks.insert({ id, m });
		std::cout << "Pushed Back" << eventName << "|" << eventCallbacksMap[eventName].size() << "\n";
	}

	//SHOULD BE TURNED BACK INTO A TEMPLATE FUNCTION - in order not to allocate a whole new command
	// I think it's done now?
	void unsubscribe(std::string id)
	{
		std::pair<EventName, AbstractCommand*> callRem = callbacks[id];
		callbacks.erase(callbacks.find(id));
		std::vector<AbstractCommand*>* eventCommands = &eventCallbacksMap[callRem.first];
		std::cout << "Pre Removed" << callRem.first << "|" << eventCallbacksMap[callRem.first].size() << "\n";
		int index = 0;
		for (AbstractCommand* command : *eventCommands) {
			if (callRem.second->compareCommandsIdentifier(command->commandIdentifier)) {
				eventCallbacksContextMap.erase(eventCallbacksContextMap.find(command));
				eventCommands->erase(eventCommands->begin() + index);
				break;
			}
			index++;
		}
		std::cout << "Removed" << callRem.first << "|" << eventCallbacksMap[callRem.first].size() << "\n";

	}

	void trigger(EventName eventName, EventContext* context)
	{
		for (int i = 0; i < eventCallbacksMap[eventName].size(); i++)
		{
			eventCallbacksMap[eventName][i]->execute(*context);
		}
	}

	void HandleEvents();

	void OnKeyPressed(int key);
	void OnKeyReleased(int key);

	// Release
	void Release();

private:

	EventContext context;
	std::unordered_map<EventName, std::vector<AbstractCommand*>> eventCallbacksMap;
	std::unordered_map<AbstractCommand*, EventContext> eventCallbacksContextMap;

	std::vector<int> m_InputList;
	std::map<int, EventName> m_CodeToEventNamePressed;
	std::map<int, EventName> m_CodeToEventNameReleased;
	std::vector<int> m_EventPressControl;

	std::unordered_map<std::string, std::pair<EventName, AbstractCommand*>> callbacks;
};


