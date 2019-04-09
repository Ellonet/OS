#include <stdlib.h>
#include <iostream>
#include "Thread.h"
#include "uthreads.h"
#include <deque>
#include <map>
#include <queue>
#include <set>
#include <algorithm>
#include <signal.h>
#include <setjmp.h>
#include "sleeping_threads_list.h"
#include <sys/time.h>

using namespace std;

/////////////////////////////////// global variables ///////////////////////////////////

map<int, Thread *> all_threads;
deque<Thread *> ready_queue;
int lib_quantum;
set<int> available_ids;
Thread *curr_running;
SleepingThreadsList *nap_manager = new SleepingThreadsList();
struct itimerval global_timer;
struct sigaction sa = {nullptr};
sigset_t blocked_signals_set;
int total_quantums;


/////////////////////////////////// private functions ///////////////////////////////////


void block_all_signals() {
    sigemptyset(&blocked_signals_set);
    sigaddset(&blocked_signals_set, SIGALRM);
    sigaddset(&blocked_signals_set, SIGVTALRM);
    sigaddset(&blocked_signals_set, SIGINT);
    sigprocmask(SIG_BLOCK, &blocked_signals_set, nullptr);
}

void unblock_all_signals() {
    sigprocmask(SIG_UNBLOCK, &blocked_signals_set, nullptr);
}

void set_timer() {
    global_timer.it_value.tv_sec = lib_quantum / 1000000;   // first time interval, seconds part
    global_timer.it_value.tv_usec = lib_quantum % 1000000;  // first time interval, microseconds part
    global_timer.it_interval.tv_sec = 0;                    // following time intervals, seconds part
    global_timer.it_interval.tv_usec = 0;                   // following time intervals, microseconds part
    setitimer(ITIMER_VIRTUAL, &global_timer, nullptr);
}

int get_next_id() {
    static int next_id = 1;
    int id;
    if (available_ids.empty()) {
        id = next_id;
        ++next_id;
    } else {
        id = *available_ids.begin();
        available_ids.erase(id);
    }
    return id;
}


Thread *get_next_thread() {
    block_all_signals();
    if (ready_queue.empty()) {
        cout << "no threads left, exiting..." << endl;
        uthread_terminate(all_threads[0]->get_id());
    }
    Thread *temp = ready_queue.front();
    ready_queue.pop_front();
    unblock_all_signals();
    return temp;
}

void switch_threads(state new_st) {
    block_all_signals();
    int ret_val = sigsetjmp(*(curr_running->get_env()), 1); //TODO update curr_run
    if (ret_val == 1) {
        set_timer();
        return;
    }

    switch (new_st) {
        case (BLOCKED):
            curr_running->set_status(new_st);
            break;
        case (TERMINATE):
            all_threads.erase(curr_running->get_id()); //TODO - make sure deletes thread
            break;
        case (READY):
            ready_queue.push_back(curr_running);
            curr_running->set_status(READY);
            break;
        default:
            break;
    }
    // start running next thread:
    Thread *next_th = get_next_thread();
    curr_running = next_th;
    curr_running->set_status(RUNNING);
    curr_running->inc_times_ran();
    set_timer();
    ++total_quantums;
    // jump
    unblock_all_signals();
    siglongjmp(*(next_th->get_env()), 1);
}

void clean_up() {
    for (auto &i : all_threads) {
        delete (i.second);
    }
    all_threads.clear();
    ready_queue.clear(); //TODO - make sure cleans up
}

Thread *check_existance(int tid) {
    block_all_signals();
    if (tid < 0 || tid > MAX_THREAD_NUM - 1) {
        cout << "thread library error: the thread id is invalid (it needs to be  between 0 to " << MAX_THREAD_NUM - 1
             << ")" << endl;
        return nullptr;
    }
    auto it = all_threads.find(tid);
    if (it == all_threads.end()) {
        cout << "thread library error: the thread id's cell is empty in the threadsArr" << endl;
        return nullptr;
    }
    unblock_all_signals();
    return (it->second);
}

timeval calc_wake_up_timeval(int usecs_to_sleep) {
    timeval now, time_to_sleep, wake_up_timeval;
    gettimeofday(&now, nullptr);
    time_to_sleep.tv_sec = usecs_to_sleep / 1000000;
    time_to_sleep.tv_usec = usecs_to_sleep % 1000000;
    timeradd(&now, &time_to_sleep, &wake_up_timeval);
    return wake_up_timeval;
}

bool check_wake(timeval &now, timeval &wakie) {
    if (now.tv_sec == wakie.tv_sec) {
        return now.tv_usec > wakie.tv_usec;
    }
    return now.tv_sec > wakie.tv_sec;
}

void timer_handler(int sig) {
//  get current time:
    timeval now{};
    gettimeofday(&now, nullptr);
    // first - we wake up all the sleeping threads.
    wake_up_info *first_to_wake = nap_manager->peek(); //get the first

    while ((first_to_wake != nullptr) && (check_wake(now, first_to_wake->awaken_tv))) {
        Thread *Thread_to_wake = check_existance(first_to_wake->id);
        if (!Thread_to_wake) {
            throw "Error - couldnt wakeup";
        }
        ready_queue.push_back(Thread_to_wake);
        Thread_to_wake->set_status(READY);
        nap_manager->pop();
        first_to_wake = nap_manager->peek();
    }
    // call thread switch:
    switch_threads(READY);
}



/////////////////////////////////// public functions ////////////////////////////////////////////////////////////////////////////////////
/*
 * Description: This function initializes the thread library.
 * You may assume that this function is called before any other thread library
 * function, and that it is called exactly once. The input to the function is
 * the length of a _times_ran in micro-seconds. It is an error to call this
 * function with non-positive quantum_usecs.
 * Return value: On success, return 0. On failure, return -1.
*/
int uthread_init(int quantum_usecs) {
    block_all_signals();
    if (quantum_usecs <= 0) {
        cout << "Error - Illegal quantum value" << endl;
        return -1;
    }
    lib_quantum = quantum_usecs;

    try {
        auto *thread_0 = new Thread(0, nullptr, STACK_SIZE);
        thread_0->set_status(RUNNING);
        thread_0->inc_times_ran();
        all_threads[0] = thread_0;
        curr_running = thread_0;
        total_quantums = 1;
        sa.sa_handler = timer_handler;
        sigaction(SIGVTALRM, &sa, nullptr);
        set_timer();
    }
    catch (exception &e) {
        cout << "Error - library initialization failed" << endl;
        return -1;
    }
    unblock_all_signals();
    return 0;
}

/*
 * Description: This function creates a new thread, whose entry point is the
 * function f with the signature void f(void). The thread is added to the end
 * of the READY threads list. The uthread_spawn function should fail if it
 * would cause the number of concurrent threads to exceed the limit
 * (MAX_THREAD_NUM). Each thread should be allocated with a stack of size
 * STACK_SIZE bytes.
 * Return value: On success, return the ID of the created thread.
 * On failure, return -1.
*/
int uthread_spawn(void (*f)()) { // TODO - check allocation success
    block_all_signals();
    // check thread count
    if (all_threads.size() < MAX_THREAD_NUM -1) {
        int id = get_next_id();
        auto *new_thread = new Thread(id, f, STACK_SIZE);
        // add thread to all_threads list and to ready list
        all_threads[id] = new_thread;
        ready_queue.push_back(new_thread);
        unblock_all_signals();
        return new_thread->get_id();
    }
    cout << "Error - exceeded num of allowed threads MADAFAKA" << endl;
    return -1;
}


/*
 * Description: This function terminates the thread with ID tid and deletes
 * it from all relevant control structures. All the resources allocated by
 * the library for this thread should be released. If no thread with ID tid
 * exists it is considered an error. Terminating the main thread
 * (tid == 0) will result in the termination of the entire process using
 * exit(0) [after releasing the assigned library memory].
 * Return value: The function returns 0 if the thread was successfully
 * terminated and -1 otherwise. If a thread terminates itself or the main
 * thread is terminated, the function does not return.
*/
int uthread_terminate(int tid) {    // TODO - make sure to free the allocations using delete
    block_all_signals();
    if (!tid) { // in case of deleting the main thread
        clean_up();
        exit(0);
    }

    Thread *toKill = check_existance(tid);
    if (!(toKill)) {
        return -1;
    }
    switch (toKill->get_status()) {
        case (READY):
            ready_queue.erase(find(ready_queue.begin(), ready_queue.end(), toKill));
            break;
        case (RUNNING):
            switch_threads(TERMINATE);
            break;
        default: // if blocked nothing extra to be done just erase and happens anyway
            break;
    }

    available_ids.insert(tid); // re-use the id, and delete the thread.
    all_threads.erase(tid);
    unblock_all_signals();
    return 0;
}


/*
 * Description: This function blocks the thread with ID tid. The thread may
 * be resumed later using uthread_resume. If no thread with ID tid exists it
 * is considered as an error. In addition, it is an error to try blocking the
 * main thread (tid == 0). If a thread blocks itself, a scheduling decision
 * should be made. Blocking a thread in BLOCKED state has no
 * effect and is not considered an error.
 * Return value: On success, return 0. On failure, return -1.
*/
int uthread_block(int tid) {
    block_all_signals();

    if (!tid) {
        cout << "thread library error: it's illegal to block the main thread" << endl;
        return -1;
    }

    Thread *toKill = check_existance(tid);
    if (!(toKill)) {
        return -1;
    }

    switch (toKill->get_status()) {
        case (READY):
            ready_queue.erase(find(ready_queue.begin(), ready_queue.end(), toKill));
            break;
        case (RUNNING):
            switch_threads(BLOCKED);
            break;
        default: // in this case - do nothing.
            break;
    }

    all_threads[tid]->set_status(BLOCKED);
    unblock_all_signals();
    return 0;
}


/*
 * Description: This function resumes a blocked thread with ID tid and moves
 * it to the READY state. Resuming a thread in a RUNNING or READY state
 * has no effect and is not considered as an error. If no thread with
 * ID tid exists it is considered an error.
 * Return value: On success, return 0. On failure, return -1.
*/
int uthread_resume(int tid) {
    block_all_signals();
    Thread *toResume = check_existance(tid);
    if (!(toResume)) {
        return -1;
    }
    toResume->set_status(READY);
    if ((find(ready_queue.begin(), ready_queue.end(), toResume) == ready_queue.end())) {
        ready_queue.push_back(toResume);
    }
    unblock_all_signals();
    return 0;
    // TODO - check
}

/*
 * Description: This function blocks the RUNNING thread for usecs micro-seconds in real time (not virtual
 * time on the cpu). It is considered an error if the main thread (tid==0) calls this function. Immediately after
 * the RUNNING thread transitions to the BLOCKED state a scheduling decision should be made.
 * After the sleeping time is over, the thread should go back to the end of the READY threads list.
 * Return value: On success, return 0. On failure, return -1.
*/
int uthread_sleep(unsigned int usec) {
    block_all_signals();
    timeval wake_me = calc_wake_up_timeval(usec);
    int currId = uthread_get_tid(); // block thread
    nap_manager->add(currId, wake_me);
    uthread_block(currId);
    unblock_all_signals();
    return 0;
}


/*
 * Description: This function returns the thread ID of the calling thread.
 * Return value: The ID of the calling thread.
*/
int uthread_get_tid() {
    int res = curr_running->get_id();
    return res;
}


/*
 * Description: This function returns the total number of quantums since
 * the library was initialized, including the current _times_ran.
 * Right after the call to uthread_init, the value should be 1.
 * Each time a new _times_ran starts, regardless of the reason, this number
 * should be increased by 1.
 * Return value: The total number of quantums.
*/
int uthread_get_total_quantums() {
    return total_quantums;
}


/*
 * Description: This function returns the number of quantums the thread with
 * ID tid was in RUNNING state. On the first time a thread runs, the function
 * should return 1. Every additional _times_ran that the thread starts should
 * increase this value by 1 (so if the thread with ID tid is in RUNNING state
 * when this function is called, include also the current _times_ran). If no
 * thread with ID tid exists it is considered an error.
 * Return value: On success, return the number of quantums of the thread with ID tid.
 * 			     On failure, return -1.
*/
int uthread_get_quantums(int tid) {
    Thread *temp = check_existance(tid);
    if (temp) {
        return temp->get_times_ran();
    }
    return -1;
}

//TODO - MATLAB
//TODO - check sleep
//TODO - resume -> check if not sleeping , if awaken -> check if not blocked