/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 21:20:58 by marvin            #+#    #+#             */
/*   Updated: 2024/04/26 21:20:58 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <sys/time.h>
#include <stdio.h>

u_int64_t	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * (u_int64_t)1000) + (tv.tv_usec / 1000));
}

float	ft_random(int i, int min, int max)
{
	static int		seeds[16] = {0};

	if (seeds[i] == 0)
		seeds[i] = rand();
	seeds[i] = seeds[i] * 1103515245 + 12345;
	return min + (float)((unsigned int)(seeds[i]) % 2147483647) / (float)(2147483647) * (max - min);
}

#include <stdio.h>

typedef union {
    struct {
        float x;
        float y;
        float z;
    };
    float data[3];
} t_vec3f_union;

t_vec3f_union 	vec3f_add_v_opti(t_vec3f_union a, t_vec3f_union b) {
    t_vec3f_union result;
	result.data[0] = a.data[0] * b.data[0];
	result.data[1] = a.data[1] * b.data[1];
	result.data[2] = a.data[2] * b.data[2];
    
	return result;
}

t_vec3f_union	vec3f_add_v(t_vec3f_union a, t_vec3f_union b)
{
	return ((t_vec3f_union){a.x * b.x, a.y * b.y, a.z * b.z});
}

int main(void)
{
	t_vec3f_union		sum;
	u_int64_t	start;
	u_int64_t	tmp;

	start = 0;
	long int	i = 0;
	while (i < 100000000)
	{
		t_vec3f_union a = {ft_random(0, -1000,1000), ft_random(0, -1000,1000), ft_random(0, -1000,1000)};
		t_vec3f_union b = {ft_random(0, -1000,1000), ft_random(0, -1000,1000), ft_random(0, -1000,1000)};
		tmp = get_time();
		sum = vec3f_add_v(a, b);
		start += get_time() - tmp;
		i++;
	}
	printf("%lu ms\n", start);
	return (0);
}