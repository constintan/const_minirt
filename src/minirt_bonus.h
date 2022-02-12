/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: konstanting <konstanting@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 00:18:39 by lajudy            #+#    #+#             */
/*   Updated: 2022/02/11 23:48:58 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_BONUS_H
# define MINIRT_BONUS_H

# include <pthread.h>
# include <semaphore.h>

# define THREADS 8

typedef struct s_thread {
	pthread_t	thread;
	int			index;
	t_scene		*scene;
}	t_thread;

typedef struct s_bonus {
	long		timestamp;
	sem_t		*threads1;
	sem_t		*threads2;
	sem_t		*threads3;
	sem_t		*threads4;
}	t_bonus;

int		render_next_frame_bonus(t_scene *scene);
void	*thread_loop(void *thread_void);
long	mtv(void);

#endif