/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_radian.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 16:28:45 by ldutriez          #+#    #+#             */
/*   Updated: 2022/10/25 16:29:01 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cmath>

float	to_radian(int degree)
{
	return (static_cast<float>(degree * (M_PI / 180)));
}