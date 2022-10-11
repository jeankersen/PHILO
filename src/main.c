#include "../include/philo.h"


void *fn_philo(void *arg)
{
	t_arg *input = (t_arg *) arg;
	while (1)
	{

		time_t time;
		time = get_time_in_ms();
		int val = get_random(2);
		pthread_mutex_lock(&input->robot.mutex_stock);
    	sleep (get_random (3));
		if(input->t == 1)
		if(val > input->robot.stock)
		{
			pthread_cond_signal(&input->robot.cond_stock);
			pthread_cond_wait(&input->robot.cond_clients, &input->robot.mutex_stock);
		}
		input->robot.stock =  input->robot.stock - val;
		printf("\n\n[%ld] philo #%ld!, i take %d reste %d \n", time - input->start_time, input->t,  val, input->robot.stock);
	//printf("time is: %ld\n", data.start_time);
		pthread_mutex_unlock(&input->robot.mutex_stock);
	}

	return NULL;
}

 void *fn_manager (void *arg)
{
	t_arg *input = (t_arg *) arg;
   while (1)
   {
		pthread_mutex_lock(&input->robot.mutex_stock);
		pthread_cond_wait(&input->robot.cond_stock, &input->robot.mutex_stock);

		input->robot.fork[input->t] = INITIAL_STOCK;
     	input->robot.stock = INITIAL_STOCK;
    	 printf ("Remplissage du stock de %d articles !\n", input->robot.stock);

	  	pthread_cond_signal(&input->robot.cond_clients);
	  	pthread_mutex_unlock(&input->robot.mutex_stock);
   }

   return NULL;
}

void creat_philo(t_arg *data)
{
	int ret;
	printf("Creation du thread du magasin!\n");
	ret = pthread_create(
		&data->thread_manager, NULL, fn_manager,(void *) data
	);
	if(!ret)
	{

		while (data->t <= data->nbr_of_philo)
		{
			printf("In main: creaint thread %ld\n", data->t);
			ret = pthread_create(
				&data->robot.threads_philo[data->t],  NULL, fn_philo, (void *) data
				);
			//printf("put 1 in tab fork\n");
			data->robot.fork[data->t] = 1;
			//printf("fork[%ld] = : for[%d]\n", data->t, data->robot.fork[data->t]);
			if(ret)
			{
				printf("ERROR; return code from pthread_create() iss %d\n", ret);
			}
	 		data->t++;
		}
	}
		else
		{
			printf("ERROR; return code from pthread_create() iss %d\n", ret);
		}
	data->t = 1;
	while (data->t <= data->nbr_of_philo)
	{
		pthread_join(data->robot.threads_philo[data->t], NULL);
		data->t++;
	}
	pthread_join(data->thread_manager, NULL);
}


/*

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

oeihore
epije
repire */

int main(int argc, char **argv)
{
	t_arg data;
	//t_philo_fork store;
	data.robot.stock = INITIAL_STOCK;
	//ata.robot.mutex_stock = PTHREAD_MUTEX_INITIALIZER;
	pthread_mutex_init(&data.robot.mutex_stock,0);
	pthread_cond_init(&data.robot.cond_stock, 0);
	pthread_cond_init(&data.robot.cond_clients, 0);

	if (argc == 5)
	{
		init_arg(&data, argv);
		creat_philo(&data);
	}

  return 0;
}
