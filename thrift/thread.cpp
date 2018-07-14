#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

pthread_mutex_t mutex_worker;
pthread_cond_t condition_worker;
int worker_count = 0;

pthread_mutex_t mutex_work;
pthread_cond_t condition_work;
int work_submit = 0;
int work_done = 0;
int work = 0;
int worker_thread = 1;

void * thread_main(void * arg)
{
	int thread_id = reinterpret_cast<int>(arg);
	printf("thread run %d\n", thread_id);

	pthread_mutex_lock(&mutex_worker);
	worker_count++;
	pthread_mutex_unlock(&mutex_worker);
	pthread_cond_signal(&condition_worker);

	while(true)
	{
		pthread_mutex_lock(&mutex_work);
		while(work <= 0 || worker_thread != thread_id)
		{
			pthread_cond_wait(&condition_work, &mutex_work);
		}
		work -= 1;
		work_done += 1;
		printf("T%d,i=%d,j=%d\n", thread_id, work_submit, work_done);
		pthread_mutex_unlock(&mutex_work);
		pthread_cond_broadcast(&condition_work);
	}
}

int main()
{
	pthread_mutex_init(&mutex_worker, NULL);
	pthread_cond_init(&condition_worker, NULL);

	pthread_mutex_init(&mutex_work, NULL);
	pthread_cond_init(&condition_work, NULL);

	const int thread_count = 10;
	pthread_t pid[thread_count];
	for(int i = 0; i < thread_count; ++i)
	{
		pthread_create(&pid[i], NULL, thread_main, i);
	}

	pthread_mutex_lock(&mutex_worker);
	while(worker_count != thread_count)
	{
		struct timespec tm;
		clock_gettime(CLOCK_REALTIME, &tm);
		tm.tv_sec += 5;
		printf("Main timed wait before\n");
		pthread_cond_timedwait(&condition_worker, &mutex_worker, &tm);
		printf("Main timed wait after\n");
	}
	pthread_mutex_unlock(&mutex_worker);

	printf("main workder already\n");
	while(true)
	{
		pthread_mutex_lock(&mutex_work);
		while(work > 0)
		{
			pthread_cond_wait(&condition_work, &mutex_work);
		}

		sleep(1);
		work = 10;
		work_submit += work;
		worker_thread = rand() % thread_count;
		printf("Main add=%d,i=%d,j=%d,worker_thread=%d\n", work, work_submit, work_done, worker_thread);
		pthread_cond_broadcast(&condition_work);
		pthread_mutex_unlock(&mutex_work);
	}
	for(int i = 0; i < thread_count; ++i)
	{
		pthread_join(pid[i], NULL);
	}
	return 0;
}
