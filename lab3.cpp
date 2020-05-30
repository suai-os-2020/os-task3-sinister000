#include "lab3.h"
#include <windows.h>
#include <iostream>

volatile int n;

using namespace std;

//mutex
HANDLE mutex;

//semaphores
HANDLE semB, semC, semD, semG, wait_long_interval, start_interval;

int q = 3;

void mtx_locked_print(char c) {
    WaitForSingleObject(mutex, INFINITE);
    cout << c << flush;
    ReleaseMutex(mutex);
    computation();
}

unsigned int lab3_thread_graph_id() {
    return 7;
}

const char *lab3_unsynchronized_threads() {
    return "dfgi";
}

const char *lab3_sequential_threads() {
    return "bcdg";
}

DWORD WINAPI thread_a(LPVOID lpParam) {
    for (int i = 0; i < q; i++) {
        mtx_locked_print('a');
    }

    return 0;
}

DWORD WINAPI thread_b(LPVOID lpParam) {
    for (int i = 0; i < q; i++) {
        WaitForSingleObject(semB, INFINITE);
        mtx_locked_print('b');
        ReleaseSemaphore(semC, 1, nullptr);
    }

    return 0;
}

DWORD WINAPI thread_c(LPVOID lpParam) {
    for (int i = 0; i < q; i++) {
        WaitForSingleObject(semC, INFINITE);
        mtx_locked_print('c');
        ReleaseSemaphore(semD, 1, nullptr);
    }

    ReleaseSemaphore(wait_long_interval, 1, nullptr);    //notify of interval completion
    WaitForSingleObject(start_interval, INFINITE);                                  //begin new interval

    for (int i = 0; i < q; i++) {
        mtx_locked_print('c');
    }

    return 0;
}

DWORD WINAPI thread_d(LPVOID lpParam) {
    for (int i = 0; i < q; i++) {
        WaitForSingleObject(semD, INFINITE);
        mtx_locked_print('d');
        ReleaseSemaphore(semG, 1, nullptr);
    }

    ReleaseSemaphore(wait_long_interval, 1, nullptr);    //notify of interval completion
    WaitForSingleObject(start_interval, INFINITE);                                  //begin new interval

    for (int i = 0; i < q; i++) {
        mtx_locked_print('d');
    }

    ReleaseSemaphore(wait_long_interval, 1, nullptr);    //notify of interval completion
    WaitForSingleObject(start_interval, INFINITE);                                  //begin new interval

    for (int i = 0; i < q; i++) {
        mtx_locked_print('d');
    }

    return 0;
}

DWORD WINAPI thread_e(LPVOID lpParam) {
    for (int i = 0; i < q; i++) {
        mtx_locked_print('e');
    }

    return 0;
}

DWORD WINAPI thread_g(LPVOID lpParam) {
    for (int i = 0; i < q; i++) {
        WaitForSingleObject(semG, INFINITE);
        mtx_locked_print('g');
        ReleaseSemaphore(semB, 1, nullptr);
    }

    ReleaseSemaphore(wait_long_interval, 1, nullptr);    //notify of interval completion
    WaitForSingleObject(start_interval, INFINITE);                                  //begin new interval

    for (int i = 0; i < q; i++) {
        mtx_locked_print('g');
    }

    ReleaseSemaphore(wait_long_interval, 1, nullptr);    //notify of interval completion
    WaitForSingleObject(start_interval, INFINITE);                                  //begin new interval

    for (int i = 0; i < q; i++) {
        mtx_locked_print('g');
    }

    ReleaseSemaphore(wait_long_interval, 1, nullptr);    //notify of interval completion
    WaitForSingleObject(start_interval, INFINITE);                                  //begin new interval

    for (int i = 0; i < q; i++) {
        mtx_locked_print('g');
    }

    return 0;
}

DWORD WINAPI thread_f(LPVOID lpParam) {
    for (int i = 0; i < q; i++) {
        mtx_locked_print('f');
    }

    return 0;
}

DWORD WINAPI thread_k(LPVOID lpParam) {
    for (int i = 0; i < q; i++) {
        mtx_locked_print('k');
    }

    return 0;
}

DWORD WINAPI thread_i(LPVOID lpParam) {
    for (int i = 0; i < q; i++) {
        mtx_locked_print('i');
    }

    ReleaseSemaphore(wait_long_interval, 1, nullptr);    //notify of interval completion
    WaitForSingleObject(start_interval, INFINITE);                                  //begin new interval

    for (int i = 0; i < q; i++) {
        mtx_locked_print('i');
    }

    return 0;
}

DWORD WINAPI thread_m(LPVOID lpParam) {
    for (int i = 0; i < q; i++) {
        mtx_locked_print('m');
    }

    ReleaseSemaphore(wait_long_interval, 1, nullptr);    //notify of interval completion
    WaitForSingleObject(start_interval, INFINITE);                                  //begin new interval

    for (int i = 0; i < q; i++) {
        mtx_locked_print('m');
    }

    return 0;
}

DWORD WINAPI thread_n(LPVOID lpParam) {
    for (int i = 0; i < q; i++) {
        mtx_locked_print('n');
    }

    return 0;
}

int lab3_init() {
    //Create mutex:
    mutex = CreateMutex(nullptr, FALSE, nullptr);
    if (mutex == nullptr) cerr << "Mutex init failed";

    //Create semaphores:
    //create semaphores B, C, D, G
    semB = CreateSemaphore(nullptr, 1, 1, nullptr);
    semC = CreateSemaphore(nullptr, 0, 1, nullptr);
    semD = CreateSemaphore(nullptr, 0, 1, nullptr);
    semG = CreateSemaphore(nullptr, 0, 1, nullptr);

    //initialize wait/start semaphores
    wait_long_interval = CreateSemaphore(nullptr, 0, 3, nullptr);
    start_interval = CreateSemaphore(nullptr, 0, 3, nullptr);

    HANDLE threadA, threadB, threadC, threadD, threadE, threadF, threadG, threadI, threadK, threadM, threadN;

    //Create and run threads:
    //1 interval (a)
    threadA = CreateThread(nullptr, 0, thread_a, nullptr, 0, nullptr);
    if (threadA == nullptr) return GetLastError();

    WaitForSingleObject(threadA, INFINITE);                             //join with ended thread A

    //2 interval (bcdg)
    threadB = CreateThread(nullptr, 0, thread_b, nullptr, 0, nullptr);
    if (threadB == nullptr) return GetLastError();

    threadC = CreateThread(nullptr, 0, thread_c, nullptr, 0, nullptr);
    if (threadC == nullptr) return GetLastError();

    threadD = CreateThread(nullptr, 0, thread_d, nullptr, 0, nullptr);
    if (threadD == nullptr) return GetLastError();

    threadG = CreateThread(nullptr, 0, thread_g, nullptr, 0, nullptr);
    if (threadG == nullptr) return GetLastError();

    WaitForSingleObject(threadB, INFINITE);                              //join with ended thread B
    WaitForSingleObject(wait_long_interval, INFINITE);                   //wait for thread C to finish
    WaitForSingleObject(wait_long_interval, INFINITE);                   //wait for thread D to finish
    WaitForSingleObject(wait_long_interval, INFINITE);                   //wait for thread G to finish


    //3 interval (cdeg)
    ReleaseSemaphore(start_interval, 1, nullptr);            //continue thread G
    ReleaseSemaphore(start_interval, 1, nullptr);            //continue thread C
    ReleaseSemaphore(start_interval, 1, nullptr);            //continue thread D

    threadE = CreateThread(nullptr, 0, thread_e, nullptr, 0, nullptr);
    if (threadE == nullptr) return GetLastError();

    WaitForSingleObject(threadE, INFINITE);                     //join with ended thread E
    WaitForSingleObject(threadC, INFINITE);                     //join with ended thread C
    WaitForSingleObject(wait_long_interval, INFINITE);          //wait for thread D to finish
    WaitForSingleObject(wait_long_interval, INFINITE);          //wait for thread G to finish


    //4 interval (dfgi)
    ReleaseSemaphore(start_interval, 1, nullptr);            //continue thread G
    ReleaseSemaphore(start_interval, 1, nullptr);            //continue thread D

    threadF = CreateThread(nullptr, 0, thread_f, nullptr, 0, nullptr);
    if (threadF == nullptr) return GetLastError();

    threadI = CreateThread(nullptr, 0, thread_i, nullptr, 0, nullptr);
    if (threadI == nullptr) return GetLastError();

    WaitForSingleObject(threadF, INFINITE);                     //join with ended thread F
    WaitForSingleObject(threadD, INFINITE);                     //join with ended thread D
    WaitForSingleObject(wait_long_interval, INFINITE);          //wait for thread I to finish
    WaitForSingleObject(wait_long_interval, INFINITE);          //wait for thread G to finish


    //5 interval (gikm)
    ReleaseSemaphore(start_interval, 1, nullptr);            //continue thread G
    ReleaseSemaphore(start_interval, 1, nullptr);            //continue thread I

    threadK = CreateThread(nullptr, 0, thread_k, nullptr, 0, nullptr);
    if (threadK == nullptr) return GetLastError();

    threadM = CreateThread(nullptr, 0, thread_m, nullptr, 0, nullptr);
    if (threadM == nullptr) return GetLastError();

    WaitForSingleObject(threadG, INFINITE);                     //join with ended thread G
    WaitForSingleObject(threadI, INFINITE);                     //join with ended thread I
    WaitForSingleObject(threadK, INFINITE);                     //join with ended thread K
    WaitForSingleObject(wait_long_interval, INFINITE);          //wait for thread M to finish


    //6 interval (mn)
    ReleaseSemaphore(start_interval, 1, nullptr);            //continue thread M

    threadN = CreateThread(nullptr, 0, thread_n, nullptr, 0, nullptr);
    if (threadN == nullptr) return GetLastError();

    WaitForSingleObject(threadM, INFINITE);                     //join with ended thread M
    WaitForSingleObject(threadN, INFINITE);                     //join with ended thread N

    //Close descriptors
    CloseHandle(threadA);
    CloseHandle(threadB);
    CloseHandle(threadC);
    CloseHandle(threadD);
    CloseHandle(threadE);
    CloseHandle(threadF);
    CloseHandle(threadG);
    CloseHandle(threadI);
    CloseHandle(threadK);
    CloseHandle(threadM);
    CloseHandle(threadN);

    CloseHandle(mutex);

    CloseHandle(semB);
    CloseHandle(semC);
    CloseHandle(semD);
    CloseHandle(semG);

    CloseHandle(wait_long_interval);
    CloseHandle(start_interval);
    return 0;
}
