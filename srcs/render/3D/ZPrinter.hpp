/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ZPrinter.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 11:38:32 by ldutriez          #+#    #+#             */
/*   Updated: 2022/11/03 15:02:45 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LCPPGL_ZPrinter_HPP
# define LCPPGL_ZPrinter_HPP

# include "lcppgl.hpp"
# include <limits> //Used by numeric_limits<T>
# include <cstring> //Used by memset
# include "Camera.hpp"
# include "Mesh.hpp"
# include "Matrix4x4.hpp"
# include <thread>
# include <mutex>

namespace lcppgl
{
	struct ScanLineData
	{
		int currentY;
		float ndotla;
		float ndotlb;
		float ndotlc;
		float ndotld;

		ScanLineData()
		: currentY(0), ndotla(0.0f), ndotlb(0.0f), ndotlc(0.0f), ndotld(0.0f)
		{}
	};

	/**
	 * @brief A class that have purpose to put 3D shapes with depth on screen.
	 */
	class ZPrinter
	{
		private:
			Context	&	_current_context;
			float *		_z_buffer;
			Camera		_cam;
			std::mutex	_render;

			ZPrinter &	operator = (const ZPrinter & to_copy);
			
			// Transform a 3D point into a screen adjusted 2D point using the given matrix.
			tools::Vertex	_project(const tools::Vertex &vertex,
							const tools::Matrix4x4 &matrix) const;
			
			//! Might return SDL_Point[] later.
			//Algorithm used to put filled triangle.
			void	_scan_line(tools::Color color,
								ScanLineData data,
								const tools::Vector3 & a, const tools::Vector3 & b,
								const tools::Vector3 & c, const tools::Vector3 & d);

			void	_scan_line(ScanLineData data,
								const tools::Vector3 & a, const tools::Vector3 & b,
								const tools::Vector3 & c, const tools::Vector3 & d);

		public:
			tools::Vector3	light_src;
			
			ZPrinter(Context & context, const Camera & cam, const tools::Vector3 & light);
			~ZPrinter();

			__attribute__ ((deprecated)) void	set_current_context(Context & context);

			void	set_draw_color(const SDL_Color & color);
			void	set_draw_color(const Uint8 r, const Uint8 g, const Uint8 b, const Uint8 a);

			void	put_outlined_rect(const tools::Rectangle & rect);
			void	put_outlined_rect(const tools::Rectangle & rect, const tools::Color & color);
			void	put_filled_rect(const tools::Rectangle & rect);
			void	put_filled_rect(const tools::Rectangle & rect, const tools::Color & color);

			/**
			 * @brief Put a line in the linked context.
			 * 
			 * @param points A tools::Rectangle storing x1,y1 and x2,y2.
			 */
			void	put_line(const tools::Rectangle & points);

			/**
			 * @brief Put a line in the linked context.
			 * 
			 * @param points A tools::Rectangle storing x1,y1 and x2,y2.
			 * @param color The color to draw the line with.
			 */
			void	put_line(const tools::Rectangle & points,
								const tools::Color & color);

			//TODO : Do a Triangle class.
			void	put_triangle(int x1, int y1, int x2, int y2, int x3, int y3);
			void	put_triangle(int x1, int y1, int x2, int y2, int x3, int y3,
									const tools::Color & color);
			void	put_filled_triangle(tools::Vertex a, tools::Vertex b,
										tools::Vertex c);
			void	put_filled_triangle(tools::Vector3 a, tools::Vector3 b,
										tools::Vector3 c, tools::Color color);

			void	put_pixel(int x, int y, float z);
			void	put_pixel(int x, int y, float z, const tools::Color & color);
			
			void	put_meshes(tools::Mesh meshes[], int meshes_nb);

			void	clear(void);
			void	present(void);
	};
}

#endif