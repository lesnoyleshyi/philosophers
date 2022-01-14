
#include "../philo.h"
#include "stdio.h"
#define NUM_OF_THREADS 5
static int	counter = 0;
pthread_mutex_t	mutex;

void	*minus(void *args);
void	*plus(void *args);

int	main(void)
{
	pthread_t	threads[NUM_OF_THREADS];
	size_t		i;

	printf("init counter = %d\n", counter);
	pthread_mutex_init(&mutex, NULL);
	for (i = 0; i < NUM_OF_THREADS / 2; i++)
		pthread_create(&threads[i], NULL, minus, NULL);
	for (; i < NUM_OF_THREADS; i++)
		pthread_create(&threads[i], NULL, plus, NULL);
	for (i = 0; i < NUM_OF_THREADS; i++)
		pthread_join(threads[i], NULL);
	pthread_mutex_destroy(&mutex);
	printf("result counter = %d\n", counter);
	return (0);
}

void	*minus(void *args)
{
	int	local;

	args = NULL;
	pthread_mutex_lock(&mutex);
		local = counter;
		printf("%d minus\n", counter);
		local -= 1;
		counter = local;
	pthread_mutex_unlock(&mutex);
	return (NULL);
}

void	*plus(void *args)
{
	int	local;

	args = NULL;
	pthread_mutex_lock(&mutex);
		local = counter;
		printf("%d plus\n", counter);
		local += 1;
		counter = local;
	pthread_mutex_unlock(&mutex);
	return (NULL);
}
