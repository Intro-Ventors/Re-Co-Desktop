// Copyright (c) 2022 Intro-Ventors

#include "Reactor.hpp"

namespace WebRTC
{
	Reactor::Reactor()
	{
		// Setup the worker thread.
		m_Worker = std::jthread(&Reactor::workerFunction, this);
	}

	Reactor::~Reactor()
	{
		// Set the should stop boolean to true, to indicate that we're about to finish executing.
		{
			auto lock = std::scoped_lock(m_Mutex);
			m_bShouldStop = true;
		}

		m_Conditional.notify_one();

		// Now wait till the thread 
		m_Worker.join();
	}

	void Reactor::issueCommand(const Function& command)
	{
		// Issue the command to the queue.
		{
			auto lock = std::scoped_lock(m_Mutex);
			m_Queue.push(command);
		}

		// Notify that we have a command ready.
		m_Conditional.notify_one();
	}

	void Reactor::issueCommand(Function&& command)
	{
		// Issue the command to the queue.
		{
			auto lock = std::scoped_lock(m_Mutex);
			m_Queue.push(std::move(command));
		}

		// Notify that we have a command ready.
		m_Conditional.notify_one();
	}

	void Reactor::clear()
	{
		std::unique_lock<std::mutex> lock(m_Mutex);
		m_Queue = {};
	}

	void Reactor::workerFunction()
	{
		auto lock = std::unique_lock(m_Mutex);

		do
		{
			// Wait until we have something to execute, or if we need to stop execution.
			m_Conditional.wait(lock, [this]
				{
					return !m_Queue.empty() || m_bShouldStop;
				}
			);

			// If we have something to execute, lets execute one command.
			if (!m_Queue.empty())
			{
				auto command = std::move(m_Queue.front());
				m_Queue.pop();

				// Unlock resources now that we can execute the command.
				lock.unlock();

				// Execute the command.
				command();

				// Lock everything back in place.
				lock.lock();
			}

		} while (!m_bShouldStop);

		// Unlock resources now, we can finish everything.
		lock.unlock();

		// Lets finish all the commands if we have any so we don't miss something important.
		while (!m_Queue.empty())
		{
			// Get the command and remove it from the list.
			auto command = std::move(m_Queue.front());
			m_Queue.pop();

			// Execute the command.
			command();
		}
	}
}