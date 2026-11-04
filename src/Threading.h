#ifndef THREADING_H
#define THREADING_H

#include "SecurityEvent.h"

#include <atomic>
#include <cstddef>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

// C++ equivalent of Java's Runnable interface.
class Runnable
{
public:
    virtual ~Runnable() = default;
    virtual void run() = 0;
};

// Educational Thread base class backed by std::thread.
// It supports both "extends Thread" and "implements Runnable" styles.
class Thread : public Runnable
{
public:
    enum class State
    {
        NEW,
        RUNNABLE,
        RUNNING,
        TIMED_WAITING,
        TERMINATED
    };

private:
    std::thread worker;
    Runnable* target;
    std::atomic<State> state;
    static thread_local Thread* currentThread;

    void threadEntry();

public:
    Thread();
    explicit Thread(Runnable& runnableTarget);
    virtual ~Thread();

    Thread(const Thread&) = delete;
    Thread& operator=(const Thread&) = delete;

    void start();
    void run() override;
    void join();

    static void sleep(unsigned int milliseconds);
    static void yield();

    State getState() const;
    static std::string stateName(State state);
};

// Shared result protected by a mutex. Both workers update this object.
class ThreadSafeEventMetrics
{
private:
    mutable std::mutex metricsMutex;
    int processedEvents;
    int highSeverityEvents;
    int loginEvents;
    int networkEvents;

public:
    ThreadSafeEventMetrics();

    void record(const SecurityEvent& event);
    int getProcessedEvents() const;
    int getHighSeverityEvents() const;
    int getLoginEvents() const;
    int getNetworkEvents() const;
};

// Creation style 1: extend Thread and override run().
class EventMonitoringThread final : public Thread
{
private:
    const std::vector<SecurityEvent*>& events;
    std::size_t beginIndex;
    std::size_t endIndex;
    ThreadSafeEventMetrics& metrics;

public:
    EventMonitoringThread(
        const std::vector<SecurityEvent*>& sourceEvents,
        std::size_t begin,
        std::size_t end,
        ThreadSafeEventMetrics& sharedMetrics
    );

    void run() override;
};

// Creation style 2: implement Runnable and pass it to Thread.
class EventMonitoringTask final : public Runnable
{
private:
    const std::vector<SecurityEvent*>& events;
    std::size_t beginIndex;
    std::size_t endIndex;
    ThreadSafeEventMetrics& metrics;

public:
    EventMonitoringTask(
        const std::vector<SecurityEvent*>& sourceEvents,
        std::size_t begin,
        std::size_t end,
        ThreadSafeEventMetrics& sharedMetrics
    );

    void run() override;
};

#endif
