/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lcppgl_tools.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 21:20:57 by ldutriez          #+#    #+#             */
/*   Updated: 2022/10/25 16:30:15 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LCPPGL_TOOLS_HPP
# define LCPPGL_TOOLS_HPP

# include "Rectangle.hpp"
# include "Color.hpp"
# include "Texture.hpp"

/**
 * @brief Take an angle in degree and return an angle in radian
 */
float	to_radian(int degree);

#endif