#pragma once

#include <functional>
#include <iostream>
#include <vector>
#include <memory>
#include "EventHandler.h"

//TODO: move implementation to cpp
class C_Event
{
public:
	void addHandler(const EventHandler &handler) {
		this->handlers.push_back(std::unique_ptr<EventHandler>(new EventHandler{ handler }));
	}

	void removeHandler(const EventHandler &handler) {
		std::vector<std::unique_ptr<EventHandler>>::iterator to_remove = this->handlers.begin();
		for (; to_remove != this->handlers.end(); ++to_remove) {
			if (*(*to_remove) == handler) {
				this->handlers.erase(to_remove);
				break;
			}
		}
	}

	void operator()() {
		this->notifyHandlers();
	}

	C_Event &operator+=(const EventHandler &handler) {
		this->addHandler(handler);

		return *this;
	}

	C_Event &operator-=(const EventHandler &handler) {
		this->removeHandler(handler);

		return *this;
	}

private:
	std::vector<std::unique_ptr<EventHandler>> handlers;

	void notifyHandlers() {
		std::vector<std::unique_ptr<EventHandler>>::iterator func = this->handlers.begin();
		for (; func != this->handlers.end(); ++func) {
			if (*func != nullptr) {
				(*(*func))();
			}
		}
	}
};