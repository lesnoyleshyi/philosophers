
#include "../philo.h"
#include "stdio.h"
#include "unistd.h"
#define NUM_OF_TREADS 10000

typedef struct	use_mutex_tag	{
	pthread_mutex_t	mutex;
	int				*p_to_counter;
}				use_mutex_t		;

void	*minus(void *args);
void	*plus(void *args);

int	main(void)
{
	pthread_t	threads[NUM_OF_TREADS];
	size_t		i;
	use_mutex_t	param;
	static int	counter;

	param.p_to_counter = &counter;
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
		local = *(arg->p_to_counter);
		printf("%d minus\n", *(arg->p_to_counter));
		local -= 1;
		*(arg->p_to_counter) = local;
		usleep(100000);
	pthread_mutex_unlock(&(arg->mutex));
	return (NULL);
}

void	*plus(void *args)
{
	int			local;
	use_mutex_t	*arg;

	arg = (use_mutex_t *)args;
	pthread_mutex_lock(&(arg->mutex));
		local = *(arg->p_to_counter);
		printf("%d plus\n", *(arg->p_to_counter));
		local += 1;
		*(arg->p_to_counter) = local;
		usleep(100000);
	pthread_mutex_unlock(&(arg->mutex));
	return (NULL);
}

//Тут почему-то нет конкурентности. Вынесение переменной counter в глобальную
// область видимости тоже ничего не даёт
