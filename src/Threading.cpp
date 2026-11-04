#include "Threading.h"

#include <chrono>
#include <stdexcept>

thread_local Thread* Thread::currentThread = nullptr;

Thread::Thread() : target(nullptr), state(State::NEW) {}

Thread::Thread(Runnable& runnableTarget)
    : target(&runnableTarget), state(State::NEW) {}

Thread::~Thread()
{
    if (worker.joinable())
    {
        worker.join();
    }
}

void Thread::threadEntry()
{
    currentThread = this;
    state.store(State::RUNNING);
    run();
    state.store(State::TERMINATED);
    currentThread = nullptr;
}

void Thread::start()
{
    State expected = State::NEW;
    if (!state.compare_exchange_strong(expected, State::RUNNABLE))
    {
        throw std::logic_error("A thread can only be started once.");
    }
    worker = std::thread(&Thread::threadEntry, this);
}

void Thread::run()
{
    if (target != nullptr)
    {
        target->run();
    }
}

void Thread::join()
{
    if (worker.joinable())
    {
        worker.join();
    }
}

void Thread::sleep(unsigned int milliseconds)
{
    if (currentThread != nullptr)
    {
        currentThread->state.store(State::TIMED_WAITING);
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
    if (currentThread != nullptr)
    {
        currentThread->state.store(State::RUNNING);
    }
}

void Thread::yield()
{
    if (currentThread != nullptr)
    {
        currentThread->state.store(State::RUNNABLE);
    }
    std::this_thread::yield();
    if (currentThread != nullptr)
    {
        currentThread->state.store(State::RUNNING);
    }
}

Thread::State Thread::getState() const
{
    return state.load();
}

std::string Thread::stateName(State currentState)
{
    switch (currentState)
    {
        case State::NEW: return "NEW";
        case State::RUNNABLE: return "RUNNABLE";
        case State::RUNNING: return "RUNNING";
        case State::TIMED_WAITING: return "TIMED_WAITING";
        case State::TERMINATED: return "TERMINATED";
    }
    return "UNKNOWN";
}

ThreadSafeEventMetrics::ThreadSafeEventMetrics()
    : processedEvents(0),
      highSeverityEvents(0),
      loginEvents(0),
      networkEvents(0) {}

void ThreadSafeEventMetrics::record(const SecurityEvent& event)
{
    // SYNCHRONIZATION: only one thread may update the counters at a time.
    std::lock_guard<std::mutex> lock(metricsMutex);
    ++processedEvents;
    if (event.getSeverity() >= 4) ++highSeverityEvents;
    if (event.getEventType() == "LOGIN_EVENT") ++loginEvents;
    if (event.getEventType() == "NETWORK_EVENT") ++networkEvents;
}

int ThreadSafeEventMetrics::getProcessedEvents() const
{
    std::lock_guard<std::mutex> lock(metricsMutex);
    return processedEvents;
}

int ThreadSafeEventMetrics::getHighSeverityEvents() const
{
    std::lock_guard<std::mutex> lock(metricsMutex);
    return highSeverityEvents;
}

int ThreadSafeEventMetrics::getLoginEvents() const
{
    std::lock_guard<std::mutex> lock(metricsMutex);
    return loginEvents;
}

int ThreadSafeEventMetrics::getNetworkEvents() const
{
    std::lock_guard<std::mutex> lock(metricsMutex);
    return networkEvents;
}

EventMonitoringThread::EventMonitoringThread(
    const std::vector<SecurityEvent*>& sourceEvents,
    std::size_t begin,
    std::size_t end,
    ThreadSafeEventMetrics& sharedMetrics
)
    : events(sourceEvents),
      beginIndex(begin),
      endIndex(end),
      metrics(sharedMetrics) {}

void EventMonitoringThread::run()
{
    for (std::size_t i = beginIndex; i < endIndex; ++i)
    {
        metrics.record(*events[i]);
        Thread::yield();
        Thread::sleep(2);
    }
}

EventMonitoringTask::EventMonitoringTask(
    const std::vector<SecurityEvent*>& sourceEvents,
    std::size_t begin,
    std::size_t end,
    ThreadSafeEventMetrics& sharedMetrics
)
    : events(sourceEvents),
      beginIndex(begin),
      endIndex(end),
      metrics(sharedMetrics) {}

void EventMonitoringTask::run()
{
    for (std::size_t i = beginIndex; i < endIndex; ++i)
    {
        metrics.record(*events[i]);
        Thread::yield();
        Thread::sleep(2);
    }
}
