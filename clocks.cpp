//
// Created by bogdan on 10/11/23.
//
#include <ctime> // why time.h is deprecated?
#include <cmath> // why math.h is deprecated?
#include <iostream>
#include <unistd.h> // no namespace here, so just sleep()
#include <future>

using std::cout;
using std::endl;
using std::sin;
using ::timespec;

double duration(timespec a, timespec b) {
    return a.tv_sec - b.tv_sec + 1e-9*(a.tv_nsec - b.tv_nsec);
}


int main(){
    timespec rt0, ct0, tt0;
    clock_gettime(CLOCK_REALTIME, &rt0);
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &ct0);
    clock_gettime(CLOCK_THREAD_CPUTIME_ID, &tt0);

    constexpr double X = 1e7;
    double s1 = 0, s2 = 0;
    auto f = std::async(std::launch::async,
                        [&]{ for (double x = 0; x < X; x += 0.1) s1 += sin(x);
                            });

    for (double x = 0; x < X; x += 0.1) s2 += sin(x);
    f.wait();

//    cout << s1 << endl;
//    cout << s2 << endl;

    timespec rt1, ct1, tt1;
    clock_gettime(CLOCK_REALTIME, &rt1);
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &ct1);
    clock_gettime(CLOCK_THREAD_CPUTIME_ID, &tt1);
    cout << "Real time: " << duration(rt1, rt0) << "s, "
            "CPU time: " << duration(ct1, ct0) << "s, "
            "Thread time: " << duration(tt1, tt0) << "s" <<
            endl;

}