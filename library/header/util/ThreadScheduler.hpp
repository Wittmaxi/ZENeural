/*
2018 Maximilian Wittmer
wittmaxi@linux.pizza

https://github.com/Wittmaxi/ZENeural/blob/master/LICENSE

*/

#pragma once
#include <thread>
#include <vector>
#include <functional>

namespace ZNN {
    namespace UTIL {
        struct ThreadScheduler {
            ThreadScheduler() {
                
            }
            ThreadScheduler(ThreadScheduler& other) {
                std::swap (threads, other.threads);
            }
            void waitUntilAllClosed () {
                for (auto &i : threads)
                    i.join();

                threads.resize(0);
            }
            template <class T, class... args>
            void addThread (T function, args... arguments) noexcept {
                threads.emplace_back(std::thread(function, arguments...));
            }
            ~ThreadScheduler() {
                waitUntilAllClosed();
            }
            std::vector <std::thread> threads;
        };
    }
}