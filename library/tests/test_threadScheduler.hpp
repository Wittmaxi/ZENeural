/*
2018 Maximilian Wittmer
wittmaxi@linux.pizza

https://github.com/Wittmaxi/ZENeural/blob/master/LICENSE

*/
#include <iostream>

void testFunction ();

void testFunction () {
    ZNN::UTIL::ThreadScheduler sc;
    int a = 0;
    int b = 0;
    sc.addThread ([&a] () {
        for (int i = 0; i < 100000; i++)
            a++;
    });
    sc.addThread ([&b] () {
        for (int i = 0; i < 100000; i++)
            b++;
    });
    sc.waitUntilAllClosed();
    CHECK (a == 100000);
    CHECK (b == 100000);
}

TEST_CASE("Thread Scheduler")
{
    testFunction();
}
