/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Singleton.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 20:51:07 by ldutriez          #+#    #+#             */
/*   Updated: 2022/07/19 08:41:26 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LCPPGL_SINGLETON_HPP
#define LCPPGL_SINGLETON_HPP

namespace lcppgl
{
	// The Singleton class is a template class that implements the Singleton design
	class Singleton
	{
	public:
		static Singleton &instance()
		{
			static Singleton instance;
			return instance;
		}
		~Singleton() {}

	protected:
		Singleton() {}
		Singleton(Singleton const &src)
		{
			*this = src;
		}
		Singleton &operator=(Singleton const &rhs)
		{
			if (this != &rhs)
			{
				;
			}
			return *this;
		}
	};
}

#endif