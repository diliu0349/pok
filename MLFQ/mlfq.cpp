#include <iostream>
#include <queue>
#include <unistd.h>

using namespace std;

#define THREAD_NUM 5  // Thread number
#define Q_NUM      3  // Queue number
#define S          25 // Flush time

typedef struct thread {
    int pid;
    int cur_qid;
    int time_capacity;
    int run_time;
    int slice_time;
} thread_t;

int cnt = 0;
thread_t *current;
queue<thread_t*> q[Q_NUM];
thread_t threads[THREAD_NUM];

int queue_timeslice[Q_NUM] = {
    1,
    2,
    3
};

// 初始化
void init() {
    srand((unsigned)time(NULL));
    for (int i = 0; i < THREAD_NUM; i++) {
        threads[i].pid = i;
        threads[i].cur_qid = 0;
        threads[i].time_capacity = rand() % 20 + 1;
        threads[i].run_time = 0;
        threads[i].slice_time = 0;
        q[0].push(&threads[i]);  // 初始放入 queue 0
    }
    current = NULL;
    cnt     = 0;
}

// 将所有任务插入到优先级最高的队列
void flush() {
    cout << "Flush!" << endl;
    for (int i = 1; i < Q_NUM; i++) {
        while (!q[i].empty()) {
            q[0].push(q[i].front());
            q[i].front()->cur_qid = 0;
            q[i].pop();
        }
    }
    if (current != NULL) {
        current->cur_qid = 0;
        q[0].push(current);
        current = NULL;
    }
}

// 线程选择
void chose_thread() {
    if (cnt >= S) {
        cnt = 0;
        flush();
    }
    if (current != NULL && current->run_time < current->time_capacity) {
        // 当前线程的时间片用尽，降低其优先级
        int dst_qid = min(Q_NUM - 1, current->cur_qid + 1);
        current->cur_qid = dst_qid;
        current->slice_time = 0;
        q[dst_qid].push(current);
    }
    
    thread_t* temp = NULL;
    for (int i = 0; i < Q_NUM; i++) {
        if(!q[i].empty()) {
            temp = q[i].front();
            q[i].pop();
            break;
        }
    }

    current = temp;
}

// 线程调度主函数
void sched()
{
    if (current == NULL) {
        chose_thread();
        return;
    }
    if (current -> slice_time < queue_timeslice[current->cur_qid] && current -> run_time < current -> time_capacity) {
        return;
    }
    chose_thread();
}

void run() {
    while (1) {
        sched();
        sleep(0.5);
        if (current == NULL) {
            break; // 所有的线程都已经执行完毕，结束调度
        }
        cout << "Thead " << current->pid + 1 << " running! Remaining run time: " << current->time_capacity - current->run_time - 1 << endl;
        current->slice_time++;
        current->run_time++;
        cnt++;
    }
}


int main()
{
    int r = 1;
    while (r) {
        init();
        run();
        cout << "Finish! Another run? (Continue: 1, Exit: 0) \n";
        cin >> r;
        while (r != 0 && r != 1) {
            cout << "Input error, please retry! \n";
            cin >> r;
        }
    }
    return 0;
}