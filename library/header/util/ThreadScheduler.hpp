/*
2018 Maximilian Wittmer
wittmaxi@linux.pizza

https://github.com/Wittmaxi/ZENeural/blob/master/LICENSE

*/

#pragma once
#include <thread>
#include <vector>
#include <functional>
#include <atomic>
#include <queue>
#include <mutex>

namespace ZNN
{
namespace UTIL
{
enum class SIGNALS : int
{
    RUNNING = 0,
    DONE = 1,
    EXIT = 2
};

struct FunctionBase
{
    virtual void callFunction() = 0;
    virtual ~FunctionBase() {};
};

template <class callable, class ...args>
class Function : public FunctionBase
{
  public:
    using bind_type = decltype(std::bind(std::declval<callable>(), std::declval<args>()...));

    Function(callable f, args... arguments)
        : bind_(f, arguments...)
    {
    }

    ~Function () {

    }

    void callFunction()
    {
        bind_();
    }

  private:
    bind_type bind_;
};

void execLoop(bool* exit, std::queue<std::unique_ptr<FunctionBase>>* fun)
{
    while (!*exit)
        if (!fun->empty())
        {
            fun->front()->callFunction();
            fun->pop();
        }
}

struct Thread
{
    Thread() : loopThread(std::thread (execLoop, &exit, &fun))
    {
    }
    Thread (const Thread& other) : loopThread(std::thread (execLoop, &exit, &fun)) {
    }
    ~Thread()
    {
        exit = true;
        loopThread.join();
        while (!fun.empty())
            fun.pop();
    }
    void stop()
    {
        exit = true;
    }
    void waitUntilStopped () {
        while (!fun.empty());
    }
    template <class callable, class... args>
    void queueFunction(callable f, args... arguments)
    {
        std::lock_guard guard (queueMutex);
        fun.push(std::make_unique <Function<callable, args...>>(f, arguments...));
    }
    bool exit = false;
    std::queue<std::unique_ptr<FunctionBase>> fun;
    std::thread loopThread;
    std::mutex queueMutex;
};

struct ThreadScheduler
{
    ThreadScheduler(unsigned int amountOfThreads) : threads(amountOfThreads, Thread{})
    {
    }
    void waitUntilAllClosed()
    {
        for (auto &i : threads)
            i.stop();
    }
    void waitUntilAllStopped () {
        for (auto &i : threads)
            i.waitUntilStopped();
    }
    template <class callable, class... args>
    void runFunction(callable function, args... arguments) noexcept
    {
        threads [dispatcher % (threads.size() - 1)].queueFunction (function, arguments...);
        dispatcher++;
    }
    ~ThreadScheduler()
    {
        waitUntilAllClosed();
    }

  private:
    std::vector<Thread> threads;
    unsigned int dispatcher;
};
} // namespace UTIL
} // namespace ZNN