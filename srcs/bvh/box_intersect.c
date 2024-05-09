/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   box_intersect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 23:20:42 by marvin            #+#    #+#             */
/*   Updated: 2024/05/07 23:20:42 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float step(float edge, float x)
{
    return x < edge ? 0.0 : 1.0;
}

t_vec3f		step_v(t_vec3f edge, t_vec3f x)
{
    return (t_vec3f){step(edge.x, x.x), step(edge.y, x.y), step(edge.z, x.z)};
}

int	boxIntersection(t_ray ray, t_vec3f origin, t_vec3f rad) 
{
	ray.origin = v_sub_v(ray.origin, origin);
    t_vec3f m = (t_vec3f){1.0/ray.direction.x, 1.0/ray.direction.y, 1.0/ray.direction.z};
    t_vec3f n = v_mul_v(m, ray.origin);
    t_vec3f k = (t_vec3f){fabs(m.x) * rad.x, fabs(m.y) * rad.y, fabs(m.z) * rad.z};
    t_vec3f t1 = v_sub_v(v_mul_f(n, -1.0), k);
    t_vec3f t2 = v_add_v(v_mul_f(n, -1.0), k);
	ray.origin = v_add_v(ray.origin, origin);

    float tN = fmax( fmax( t1.x, t1.y ), t1.z );
    float tF = fmin( fmin( t2.x, t2.y ), t2.z );
	
    if(tN>tF || tF<0.0)
		return (0);
	return (1);
	// printf("%f %f\n", tN, tF);
	// return (1);

    // hit_info.normal = v_mul_f((t_vec3f){sign(ray.direction.x), sign(ray.direction.y), sign(ray.direction.z)}, -1.0f);
	// hit_info.normal = v_mul_v(hit_info.normal, step_v((t_vec3f){t1.y, t1.z, t1.x}, t1));
	// hit_info.normal = v_mul_v(hit_info.normal, step_v((t_vec3f){t1.z, t1.y, t1.x}, t1));
	// hit_info.distance = tN;
	// if (hit_info.distance < 0.0f)
	// 	hit_info.distance = tF;
	// hit_info.position = v_add_v(ray.origin, v_mul_f(ray.direction, hit_info.distance));
	// return (hit_info);
}