#include "Event.h"

void Event::Subscribe(const std::function<void(void)> pFunction)
{
	this->actions.push_back(Action(pFunction, actions.size()));
}

void Event::Unsubscribe(const std::function<void(void)> pFunction)
{
	for (Action action : actions)
	{
		if (*(long*)(char*)&pFunction == *(long*)(char*)&action.function)
		{
			auto it = std::find(actions.begin(), actions.end(), action);
			actions.erase(it);
		}
	}
}

void Event::ClearSubscribers()
{
	actions.clear();
}

void Event::Invoke()
{
	if (this->actions.size() <= 0)
		return;
	
	for (Action action : actions)
	{
		action.function();
	}
}