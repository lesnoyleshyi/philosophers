
#include "../srcs/philo.h"
#include "stdio.h"

void	*hello_world(void *args);

int	main(void)
{
	pthread_t	thread;
	int			status;
	int			status_addr;

	status = pthread_create(&thread, NULL, hello_world, NULL);
	if (status != 0)
	{
		printf("main error: can't create thread, status = %d\n", status);
		exit(EXIT_FAILURE);
	}
	printf("\tHello from main!\n");
	status = pthread_join(thread, (void **)&status_addr);
	if (status)
	{
		printf("main error: can't join thread, status = %d\n", status);
		exit(EXIT_FAILURE);
	}
	printf("joined with address %d\n", status_addr);
	return (0);
}

void	*hello_world(void *args)
{
	args = NULL;
	printf("Hello from thread!\n");
	return (0);
}
