/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lcppgl_tools.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 21:20:57 by ldutriez          #+#    #+#             */
/*   Updated: 2022/10/25 16:50:38 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LCPPGL_TOOLS_HPP
# define LCPPGL_TOOLS_HPP

// Render tools
# include "Rectangle.hpp"
# include "Color.hpp"
# include "Texture.hpp"

// Math tools

namespace lcppgl
{
	namespace tools
	{
		/**
		 * @brief Take an angle in degree and return an angle in radian
		 */
		float	to_radian(int degree);
	}
}

# include "Vector3.hpp"

#endif