#pragma once

#include <iostream>
#include <vector>
#include <functional>

template<typename... Parameters>
struct Action
{
	Action(std::function<void(Parameters...)> pFunction, int pId)
	{
		function = pFunction;
		id = pId;
	}

	~Action()
	{
		//std::cout << "action destroyed\n";
	}

	bool operator==(const Action action)
	{
		if (id == action.id)
		{
			return true;
		}
		return false;
	}

	std::function<void(Parameters...)> function;
	int id;
};

template<typename... Parameters>
class Event
{
public:
	void AddListener(const std::function<void(Parameters...)> pFunction)
	{
		actions.push_back(Action<Parameters...>(pFunction, actions.size()));
	}

	void RemoveListener(const std::function<void(Parameters...)> pFunction)
	{
		for (Action<Parameters...> action : actions)
		{
			if (*(long*)(char*)&pFunction == *(long*)(char*)&action.function)
			{
				auto it = std::find(actions.begin(), actions.end(), action);
				actions.erase(it);
			}
		}
	}

	void ClearSubscribers()
	{
		actions.clear();
	}

	void Invoke(Parameters&... parameters)
	{
		if (actions.size() <= 0)
			return;

		for (Action<Parameters...> action : actions)
		{
			action.function(parameters...);
		}
	}	

private:
	std::vector<Action<Parameters...>> actions;
};