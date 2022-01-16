
#include "../srcs/philo.h"
#include "stdio.h"
#define NUM_OF_TREADS 5

typedef struct	use_mutex_tag	{
	pthread_mutex_t	mutex;
}				use_mutex_t		;

void	*minus(void *args);
void	*plus(void *args);

static int	counter = 0;

int	main(void)
{
	pthread_t	threads[NUM_OF_TREADS];
	size_t		i;
	use_mutex_t	param;

	printf("init counter = %d\n", counter);
	pthread_mutex_init(&(param.mutex), NULL);
	for (i = 0; i < NUM_OF_TREADS / 2; i++)
		pthread_create(&threads[i], NULL, minus, &param);
	for (; i < NUM_OF_TREADS; i++)
		pthread_create(&threads[i], NULL, plus, &param);
	for (i = 0; i <NUM_OF_TREADS; i++)
	{
		pthread_join(threads[i], NULL);
	}
	pthread_mutex_destroy(&(param.mutex));
	printf("result counter = %d\n", counter);
	return (0);
}

void	*minus(void *args)
{
	int			local;
	use_mutex_t	*arg;

	arg = (use_mutex_t *)args;
	pthread_mutex_lock(&(arg->mutex));
		local = counter;
		printf("%d minus\n", counter);
		local -= 1;
		counter = local;
	pthread_mutex_unlock(&(arg->mutex));
	return (NULL);
}

void	*plus(void *args)
{
	int			local;
	use_mutex_t	*arg;

	arg = (use_mutex_t *)args;
	pthread_mutex_lock(&(arg->mutex));
		local = counter;
		printf("%d plus\n", counter);
		local += 1;
		counter = local;
	pthread_mutex_unlock(&(arg->mutex));
	return (NULL);
}
