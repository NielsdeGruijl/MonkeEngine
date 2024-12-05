#include "Event.h"

void Event::Subscribe(const std::function<void(void)> pFunction)
{
	//subscribers.push_back(pFunction);
	this->actions.push_back(Action(pFunction, actions.size()));
}

void Event::Unsubscribe(const std::function<void(void)> pFunction)
{
	//const auto& it = std::find(subscribers.begin(), subscribers.end(), subscriber);
	//subscribers.erase(it);
}

void Event::Invoke()
{
	//if (subscribers.size() <= 0)
	//	return;
	//
	//for (size_t i = 0; i < subscribers.size(); i++)
	//{
	//	std::function<void()> f = subscribers[i];
	//	f();
	//}

	if (this->actions.size() <= 0)
		return;
	
	for (Action action : actions)
	{
		action.function();
	}
}