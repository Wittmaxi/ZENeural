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
            void waitUntilAllClosed () {
                for (auto &i : threads)
                    i.join();
            }
            void addThread (const std::function <void (void)> &function) {
                threads.push_back (std::thread (function));
            }
            std::vector <std::thread> threads;
        };
    }
}