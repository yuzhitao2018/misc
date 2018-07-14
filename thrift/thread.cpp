#include<pthread.h>
#include<stdio.h>

pthread_mutex_t mutex_modify;
pthread_mutex_t mutex_inc;
pthread_mutex_t mutex_dec;
pthread_cond_t condition_inc;
pthread_cond_t condition_dec;

int inc = 0;
int dec = 0;

int int_i = 7;
int int_j = 0;

void * thread_main(void * arg)
{
	int thread_id = reinterpret_cast<int>(arg);
	printf("thread run %d\n", thread_id);
	while(true)
	{
		pthread_mutex_lock(&mutex_dec);
		while(dec == 0)
		{
			pthread_cond_wait(&condition_dec, &mutex_dec);
		}
		dec = 0;

		pthread_mutex_lock(&mutex_modify):
		int_i++;
		int_j--;
		printf("main i=%d,j=%d\n", int_i, int_j);
		pthread_mutex_unlock(&mutex_modify):

		pthread_mutex_unlock(&mutex_dec);
	}
}

int main()
{
	pthread_mutex_init(&mutex_modify, NULL);
	pthread_mutex_init(&mutex_inc, NULL);
	pthread_mutex_init(&mutex_dec, NULL);
	pthread_cond_init(&condition_inc, NULL);
	pthread_cond_init(&condition_dec, NULL);

	const int thread_count = 10;
	pthread_t pid[thread_count];
	for(int i = 0; i < thread_count; ++i)
	{
		pthread_create(&pid[i], NULL, thread_main, i);
	}
	while(true)
	{
		pthread_mutex_lock(&mutex_inc);
		while(inc == 0)
		{
			pthread_cond_wait(&condition_inc, &mutex_inc);
		}
		inc = 0;

		pthread_mutex_lock(&mutex_modify):
		int_i++;
		int_j--;
		printf("main i=%d,j=%d\n", int_i, int_j);
		pthread_mutex_unlock(&mutex_modify):

		pthread_mutex_unlock(&mutex_inc);
	}
	for(int i = 0; i < thread_count; ++i)
	{
		pthread_join(pid[i], NULL);
	}
	return 0;
}
