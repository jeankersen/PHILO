#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <pthread.h>
#include <unistd.h>
#define NBR_PHILO 500
#define INITIAL_STOCK 20


typedef struct s_philo_fork
{
	int stock;

	pthread_t threads_philo[NBR_PHILO];
	int fork[NBR_PHILO];
	pthread_mutex_t mutex_stock;
	pthread_cond_t cond_stock;
	pthread_cond_t cond_clients;
} t_philo_fork;


typedef struct s_arg
{
	time_t start_time;
	long t;
	int nbr_of_philo;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int nmbr_of_time_philo_must_eat;
	t_philo_fork robot;
	pthread_t thread_manager;
}	t_arg;


//size_t	ft_tab_size(char **s);
int	ft_atoi(const char *str);
time_t	get_time_in_ms(void);
void init_arg(t_arg *arg, char **s);
 int get_random (int max);

#endif


/*peifngpeikrf

Passing arguments to pthread function

    Recall the helloworld program you compile in the "Compile" section:

#include <stdio.h>
#include <pthread.h>

void * hello(void *input) {
    printf("%s\n", (char *)input);
    pthread_exit(NULL);
}

int main(void) {
    pthread_t tid;
    pthread_create(&tid, NULL, hello, "hello world");
    pthread_join(tid, NULL);
    return 0;
}

    We use "pthread_create" to create a thread, thread id is the first argument, NULL is the second argument(which should be some attribute, but we may not use it), the third argument is the function, then the last argument is what we want to pass to the new thread.
    When we define the function hello(void *), this function can accept a pointer as an argument.
    In this example we just pass one string to the function, what if we want to pass more than one argument? We can use structure in c.

wpifnpwefp;ewmfewfofew
ef[eopfnewf]8 */
