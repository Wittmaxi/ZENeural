/*
2018 Maximilian Wittmer
wittmaxi@linux.pizza

https://github.com/Wittmaxi/ZENeural/blob/master/LICENSE

*/
#include <iostream>

void testFunction ();

void testFunction () {
    ZNN::ASYNC::ThreadScheduler sc{2};
    int a = 0;
    int b = 0;
    sc.runFunction ([&a] () noexcept {
        for (int i = 0; i < 100000; i++)
            a++;
    });
    sc.runFunction ([&b] () noexcept {
        for (int i = 0; i < 100000; i++)
            b++;
    });
    sc.waitUntilAllStopped();
    CHECK (a == 100000);
    CHECK (b == 100000);
}

TEST_CASE("Thread Scheduler")
{
    testFunction();
}
