/*
2018 Maximilian Wittmer
wittmaxi@linux.pizza

https://github.com/Wittmaxi/ZENeural/blob/master/LICENSE

*/

#pragma once
#include <thread>
#include <vector>
#include <functional>
#include <queue>
#include <mutex>

namespace ZNN
{
namespace ASYNC
{
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
        std::lock_guard<std::mutex> guard (queueMutex);
        fun.push(std::make_unique <Function<callable, args...>>(f, arguments...));
    }
    bool exit = false;
    std::queue<std::unique_ptr<FunctionBase>> fun;
    std::thread loopThread;
    std::mutex queueMutex;
};

struct ThreadScheduler
{
    ThreadScheduler(unsigned int amountOfThreads = 1) : threads(amountOfThreads, Thread{})
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
        threads [dispatcher % size()].queueFunction (function, arguments...);
        dispatcher++;
    }
    size_t size() {
        return threads.size();
    }
    void resize (size_t newSize) {
        waitUntilAllStopped();
        waitUntilAllClosed();
        threads = std::vector<Thread> (newSize, Thread{});
    }
    ~ThreadScheduler()
    {
        waitUntilAllClosed();
    }

  private:
    std::vector<Thread> threads;
    unsigned int dispatcher;
} ts;
} // namespace UTIL
} // namespace ZNN