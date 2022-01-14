
#include "../philo.h"
#include "stdio.h"
#include "string.h"
#define SUCCESS 0
#define FAILURE 1

typedef struct some_args_tag {
	int	id;
	const char *msg;
	int	out;
}				some_args_t;

void *hello_world(void *args);

int	main(void)
{
	pthread_t	threads[4];
	int			status;
	int			i;
	int			status_addr;
	some_args_t	args[4];
	const char	*messages[] = {"First", NULL, "Third arg", "The fourth"};

	for (i = 0; i < 4; i++)
	{
		args[i].id = i;
		args[i].msg = messages[i];
	}
	for (i = 0; i < 4; i++)
	{
		status = pthread_create(&threads[i], NULL, hello_world, (void *) &args[i]);
		if (status != 0)
		{
			printf("error: can't create thread, status: %d\n", status);
			exit(EXIT_FAILURE);
		}
	}
//	for (i = 0; i < 4; i++)
//	{
//		status = pthread_join(threads[i], (void **) &status_addr);
//		if (status != 0)
//		{
//			printf("error: can't join thread, status: %d\n", status);
//			exit(EXIT_FAILURE);
//		}
//		printf("joined with address %d\n", status_addr);
//	}
// В цикле почему-то не работает

	status = pthread_join(threads[3], (void **) &status_addr);
	if (status != 0)
	{
		printf("error: can't join thread1, status: %d\n", status);
		exit(EXIT_FAILURE);
	}
	printf("joined with address %d\n", status_addr);

	status = pthread_join(threads[2], (void **) &status_addr);
	if (status != 0)
	{
		printf("error: can't join thread2, status: %d\n", status);
		exit(EXIT_FAILURE);
	}
	printf("joined with address %d\n", status_addr);

	status = pthread_join(threads[1], (void **) &status_addr);
	if (status != 0)
	{
		printf("error: can't join thread3, status: %d\n", status);
		exit(EXIT_FAILURE);
	}
	printf("joined with address %d\n", status_addr);

	status = pthread_join(threads[0], (void **) &status_addr);
	if (status != 0)
	{
		printf("error: can't join thread4, status: %d\n", status);
		exit(EXIT_FAILURE);
	}
	printf("joined with address %d\n", status_addr);
	for (i = 0; i < 4; i++)
		printf("thread %d arg.out = %d\n", i, args[i].out);
	return (0);
}

void *hello_world(void *args)
{
	some_args_t	*arg;
	int			len;

	arg = (some_args_t *)args;
	if (arg->msg == NULL)
		return ((int *)FAILURE);
	printf("msg: %s\n", arg->msg);
	len = strlen(arg->msg);
	arg->out = len;
	return (SUCCESS);
}
