
#include "../srcs/philo.h"
#include "stdio.h"
#define NUM_OF_TREADS 5

void	*minus(void *args);
void	*plus(void *args);

int	main(void)
{
	pthread_t		threads[NUM_OF_TREADS];
	size_t			i;
	pthread_mutex_t	mutex;
	static int		counter;

	printf("init counter = %d\n", counter);
	pthread_mutex_init(&mutex, NULL);
	for (i = 0; i < NUM_OF_TREADS / 2; i++)
		pthread_create(&threads[i], NULL, minus, &mutex);
	for (; i < NUM_OF_TREADS; i++)
		pthread_create(&threads[i], NULL, plus, &mutex);
	for (i = 0; i <NUM_OF_TREADS; i++)
	{
		pthread_join(threads[i], NULL);
	}
	pthread_mutex_destroy(&mutex);
	printf("result counter = %d\n", counter);
	return (0);
}

void	*minus(void *args)
{
	int				local;
	pthread_mutex_t	*p_to_mutex;

	p_to_mutex = (pthread_mutex_t *)args;
	pthread_mutex_lock(p_to_mutex);
		local = counter;
		printf("%d minus\n", counter);
		local -= 1;
		counter = local;
	pthread_mutex_unlock(p_to_mutex);
	return (NULL);
}

void	*plus(void *args)
{
	int				local;
	pthread_mutex_t *p_to_mutex;

	p_to_mutex = (pthread_mutex_t *)args;
	pthread_mutex_lock(p_to_mutex);
		local = counter;
		printf("%d plus\n", counter);
		local += 1;
		counter = local;
	pthread_mutex_unlock(p_to_mutex);
	return (NULL);
}

// По сравнению с  sample4 тут мьютекс не запихивается в структуру и всё при
// этом работает аналогично. К чему был этот финт ушами - не понятно.
// Наверное, чтоб в функции можно было передавать допом ещё что-то кроме
// мьютекса