/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lcppgl.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 20:00:58 by ldutriez          #+#    #+#             */
/*   Updated: 2022/11/19 11:38:42 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LCPPGL_HPP
# define LCPPGL_HPP

struct key_pressed
{
	bool up;
	bool down;
	bool left;
	bool right;
	bool w;
	bool a;
	bool s;
	bool d;
	bool e;
	bool q;
	bool plus;
	bool minus;

	key_pressed()
	: up(false), down(false), left(false), right(false)
	, w(false), a(false), s(false), d(false)
	, e(false), q(false), plus(false), minus(false)
	{}

	void	reset()
	{
		up = false;
		down = false;
		left = false;
		right = false;
		w = false;
		a = false;
		s = false;
		d = false;
		e = false;
		q = false;
		plus = false;
		minus = false;
	}
};

# include <iostream>
# include <stdlib.h>
# include "SDL.h"
# include "SDL_ttf.h"
# include "SDL_image.h"
# include "SDL_audio.h"

# include "Application.hpp"
# include "Context.hpp"
# include "lcppgl_tools.hpp"
# include "Printer.hpp"
# include "ZPrinter.hpp"
# include "Camera.hpp"
# include "Writer.hpp"

#endif