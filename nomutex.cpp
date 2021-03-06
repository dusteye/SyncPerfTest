#include <pthread.h>
#include <iostream>
#include <time.h>

using namespace std;

int count = 0;


void *thread_routine(void *args){
    for (int i = 0; i < 100000000; i++)
        count++;

    return (void *)0;
}

timespec diff(timespec start, timespec end)
{
    timespec temp;
    if ((end.tv_nsec-start.tv_nsec)<0) {
        temp.tv_sec = end.tv_sec-start.tv_sec-1;
        temp.tv_nsec = 1000000000+end.tv_nsec-start.tv_nsec;
    } else {
        temp.tv_sec = end.tv_sec-start.tv_sec;
        temp.tv_nsec = end.tv_nsec-start.tv_nsec;
    }
    return temp;
}

void displayTimespec(const timespec &ts){

    double nsec2sec = (double)ts.tv_nsec / 1e9;

    cout << (double)ts.tv_sec + nsec2sec << " seconds" << endl;
}


int main(){
    struct timespec time1, time2;

    clock_gettime(CLOCK_REALTIME, &time1);

    pthread_t tids[4];
    
    for (int i = 0; i < 4; i++){
        pthread_create(&tids[i], NULL, thread_routine, NULL);
    }

    for (int i = 0; i < 4; i++){
        pthread_join(tids[i], NULL);
    }
    

    clock_gettime(CLOCK_REALTIME, &time2);
    displayTimespec(diff(time1,time2));
    cout << count << endl;
    return 0;
}
