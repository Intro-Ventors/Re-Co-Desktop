// Copyright (c) 2022 Intro-Ventors

#pragma once

#include <functional>
#include <queue>
#include <condition_variable>
#include <mutex>
#include <thread>

namespace WebRTC
{
	/**
	 * Reactor class.
	 * This class will contain a single thread, and is used to execute a task on another thread.
	 */
	class Reactor
	{
		using Function = std::function<void()>;

	public:
		/**
		 * Default constructor.
		 */
		Reactor();

		/**
		 * Default destructor.
		 */
		~Reactor();

		/**
		 * Issue a command to the reactor.
		 *
		 * @param command The command to be executed on the thread.
		 */
		void issueCommand(const Function& command);

		/**
		 * Issue a command to the reactor.
		 *
		 * @param command The command to be executed on the thread.
		 */
		void issueCommand(Function&& command);

		/**
		 * Clear everything in the queue.
		 */
		void clear();

	private:
		/**
		 * Worker function.
		 * This function will execute all the submitted commands.
		 */
		void workerFunction();

	private:
		std::queue<Function> m_Queue;
		std::mutex m_Mutex;
		std::condition_variable m_Conditional;
		std::jthread m_Worker;
		bool m_bShouldStop = false;
	};
}