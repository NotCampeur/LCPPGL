/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ZPrinter.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 11:41:59 by ldutriez          #+#    #+#             */
/*   Updated: 2022/10/31 11:53:53 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ZPrinter.hpp"

using namespace lcppgl::tools;

lcppgl::ZPrinter::ZPrinter(lcppgl::Context & context, const Camera & cam)
: _current_context(context)
, _z_buffer(new float[_current_context.width() * _current_context.height()])
, _cam(cam)
{
	float	max(std::numeric_limits<float>::max());
	int		buff_size(_current_context.width() * _current_context.height());
	
	for (int i(0); i < buff_size; ++i)
		_z_buffer[i] = max;
}

lcppgl::ZPrinter::~ZPrinter()
{
	delete []_z_buffer;
}

void
lcppgl::ZPrinter::set_current_context(lcppgl::Context & context)
{
	_current_context = context;
}

void
lcppgl::ZPrinter::set_draw_color(const SDL_Color & color)
{
	SDL_SetRenderDrawColor(_current_context.renderer(), color.r, color.g, color.b, color.a);
}

void
lcppgl::ZPrinter::set_draw_color(const Uint8 r, const Uint8 g, const Uint8 b, const Uint8 a)
{
	SDL_SetRenderDrawColor(_current_context.renderer(), r, g, b, a);
}

void
lcppgl::ZPrinter::put_outlined_rect(const Rectangle & rect)
{
	SDL_RenderDrawRect(_current_context.renderer(), (SDL_Rect *)&rect);
}

void
lcppgl::ZPrinter::put_outlined_rect(const Rectangle & rect, const Color & color)
{
	Uint8 r, g, b, a;

	SDL_GetRenderDrawColor(_current_context.renderer(), &r, &g, &b, &a);
	set_draw_color(color);
	SDL_RenderDrawRect(_current_context.renderer(), (SDL_Rect *)&rect);
	set_draw_color(r, g, b, a);
}

void
lcppgl::ZPrinter::put_filled_rect(const Rectangle & rect)
{
	SDL_RenderFillRect(_current_context.renderer(), (SDL_Rect *)&rect);
}

void
lcppgl::ZPrinter::put_filled_rect(const Rectangle & rect, const Color & color)
{
	Uint8 r, g, b, a;

	SDL_GetRenderDrawColor(_current_context.renderer(), &r, &g, &b, &a);
	set_draw_color(color);
	SDL_RenderFillRect(_current_context.renderer(), (SDL_Rect *)&rect);
	set_draw_color(r, g, b, a);
}

void
lcppgl::ZPrinter::put_line(const Rectangle & points)
{
	SDL_RenderDrawLine(_current_context.renderer(),
		points.x(), points.y(), points.width(), points.height());
}

void
lcppgl::ZPrinter::put_line(const Rectangle & points, const Color & color)
{
	Uint8 r, g, b, a;

	SDL_GetRenderDrawColor(_current_context.renderer(), &r, &g, &b, &a);
	set_draw_color(color);
	SDL_RenderDrawLine(_current_context.renderer(),
		points.x(), points.y(), points.width(), points.height());
	set_draw_color(r, g, b, a);
}

void
lcppgl::ZPrinter::put_triangle(int x1, int y1, int x2, int y2, int x3, int y3)
{
	int width(_current_context.width());
	int height(_current_context.height());
	
	if (x1 < 0 || x2 < 0 || x3 < 0
		|| x1 >= width || x2 >= width || x3 >= width
		|| y1 < 0 || y2 < 0 || y3 < 0
		|| y1 >= height || y2 >= height || y3 >= height)
		return ;

	SDL_RenderDrawLine(_current_context.renderer(), x1, y1, x2, y2);
	SDL_RenderDrawLine(_current_context.renderer(), x2, y2, x3, y3);
	SDL_RenderDrawLine(_current_context.renderer(), x3, y3, x1, y1);
}

void
lcppgl::ZPrinter::put_triangle(int x1, int y1, int x2, int y2, int x3, int y3,
				const tools::Color & color)
{
	Uint8 r, g, b, a;

	SDL_GetRenderDrawColor(_current_context.renderer(), &r, &g, &b, &a);
	set_draw_color(color);

	put_triangle(x1, y1, x2, y2, x3, y3);

	set_draw_color(r, g, b, a);
}

void
lcppgl::ZPrinter::put_pixel(int x, int y, float z)
{
	int width(_current_context.width());
	int height(_current_context.height());
	
	if (x < 0 || x >= width || y < 0 || y >= height)
		return ;
	int buffer_pos(y * width + x);
	if (z <= _z_buffer[buffer_pos])
	{
		_render.lock();
		_z_buffer[buffer_pos] = z;
		SDL_RenderDrawPoint(_current_context.renderer(), x, y);
		_render.unlock();
	}
}

void
lcppgl::ZPrinter::put_pixel(int x, int y, float z, const tools::Color & color)
{
	Uint8 r, g, b, a;

	int width(_current_context.width());
	int height(_current_context.height());
	
	if (x < 0 || x >= width || y < 0 || y >= height)
		return ;
	int buffer_pos(y * width + x);
	if (z <= _z_buffer[buffer_pos])
	{
		_render.lock();
		_z_buffer[buffer_pos] = z;
		SDL_GetRenderDrawColor(_current_context.renderer(), &r, &g, &b, &a);
		set_draw_color(color);
		SDL_RenderDrawPoint(_current_context.renderer(), x, y);
		set_draw_color(r, g, b, a);
		_render.unlock();
	}
}

Vector3
lcppgl::ZPrinter::_project(const Vector3 &vertex, const Matrix4x4 &matrix) const
{
	Vector3 td_point = matrix * vertex;

	td_point.x = (td_point.x + 1) * 0.5 * _current_context.width();
	td_point.y = (1 - (td_point.y + 1) * 0.5) * _current_context.height();
	
	return td_point;
}

void
lcppgl::ZPrinter::_scan_line(float y,
								const Vector3 & a, const Vector3 & b,
								const Vector3 & c, const Vector3 & d)
{
	float gradient1 = (a.y != b.y) ? (y - a.y) / (b.y - a.y) : 1.0f;
	float gradient2 = (c.y != d.y) ? (y - c.y) / (d.y - c.y) : 1.0f;

	float start_x(interpolate(a.x, b.x, gradient1));
	float end_x(interpolate(c.x, d.x, gradient2));

	float z1 = interpolate(a.z, b.z, gradient1);
	float z2 = interpolate(c.z, d.z, gradient2);

	for (float x(start_x); x < end_x; ++x)
	{
		float z_gradient = (x - start_x) / (end_x - start_x);
		float current_z = interpolate(z1, z2, z_gradient);
		put_pixel(x, y, current_z);
	}
}

void
lcppgl::ZPrinter::_scan_line(Color color,
								float y,
								const Vector3 & a, const Vector3 & b,
								const Vector3 & c, const Vector3 & d)
{
	float gradient1 = (a.y != b.y) ? (y - a.y) / (b.y - a.y) : 1.0f;
	float gradient2 = (c.y != d.y) ? (y - c.y) / (d.y - c.y) : 1.0f;

	float start_x(interpolate(a.x, b.x, gradient1));
	float end_x(interpolate(c.x, d.x, gradient2));

	float z1 = interpolate(a.z, b.z, gradient1);
	float z2 = interpolate(c.z, d.z, gradient2);

	for (float x(start_x); x < end_x; ++x)
	{
		float z_gradient = (x - start_x) / (end_x - start_x);
		float current_z = interpolate(z1, z2, z_gradient);
		put_pixel(x, y, current_z, color);
	}
}

void
lcppgl::ZPrinter::put_filled_triangle(Vector3 a, Vector3 b, Vector3 c)
{
	float a_b_slope(0.0f);
	float a_c_slope(0.0f);

	// Sort vertices based on their y position.
	if (a.y > b.y)
		std::swap(a, b);
	if (b.y > c.y)
		std::swap(b, c);
	if (a.y > b.y)
		std::swap(a, b);

	if (b.y - a.y > 0)
		a_b_slope = (b.x - a.x) / (b.y - a.y);
	if (c.y - a.y > 0)
		a_c_slope = (c.x - a.x) / (c.y - a.y);
	
	if (a_b_slope > a_c_slope)
	{
		for (float y(a.y); y < c.y; ++y)
			if (y < b.y)
				_scan_line(y, a, c, a, b);
			else
				_scan_line(y, a, c, b, c);
	}
	else
	{
		for (float y(a.y); y < c.y; ++y)
			if (y < b.y)
				_scan_line(y, a, b, a, c);
			else
				_scan_line(y, b, c, a, c);
	}
}

void
lcppgl::ZPrinter::put_filled_triangle(Vector3 a, Vector3 b, Vector3 c,
										Color color)
{
	float a_b_slope(0.0f);
	float a_c_slope(0.0f);

	// Sort vertices based on their y position.
	if (a.y > b.y)
		std::swap(a, b);
	if (b.y > c.y)
		std::swap(b, c);
	if (a.y > b.y)
		std::swap(a, b);

	if (b.y - a.y > 0)
		a_b_slope = (b.x - a.x) / (b.y - a.y);
	if (c.y - a.y > 0)
		a_c_slope = (c.x - a.x) / (c.y - a.y);
	
	if (a_b_slope > a_c_slope)
	{
		for (float y(a.y); y < c.y; ++y)
			if (y < b.y)
				_scan_line(color, y, a, c, a, b);
			else
				_scan_line(color, y, a, c, b, c);
	}
	else
	{
		for (float y(a.y); y < c.y; ++y)
			if (y < b.y)
				_scan_line(color, y, a, b, a, c);
			else
				_scan_line(color, y, b, c, a, c);
	}
}

void
lcppgl::ZPrinter::put_meshes(Mesh meshes[], int meshes_nb)
{
	Matrix4x4	view(Matrix4x4::look_at(_cam.pos, _cam.target, Vector3(0, 1, 0)));
	Matrix4x4	projection(Matrix4x4::perspective(0.7854f,
		static_cast<float>(_current_context.width()) / static_cast<float>(_current_context.height()),
		1.0f, 0.01f));

	Uint8 r, g, b, a;
	
	SDL_GetRenderDrawColor(_current_context.renderer(), &r, &g, &b, &a);

	for (int i(0); i < meshes_nb; ++i)
	{
		Matrix4x4	world;
		Matrix4x4	rotation;
		Matrix4x4	translation;

		rotation.set_to_rotate(meshes[i].rotation.x, meshes[i].rotation.y, meshes[i].rotation.z);
		translation.set_to_translate(meshes[i].pos.x, meshes[i].pos.y, meshes[i].pos.z);

		world = rotation * translation;

		Matrix4x4 transform;
		transform = world * view * projection;
		

		// std::vector<std::thread>	thread_list;

		for (size_t f(0); f < meshes[i].faces.size(); ++f)
		{
			auto draw_face = [&, meshes, i, f]() {
				Color white(f % 255, f % 255, f % 255, 255);
				set_draw_color(white);
				Vector3 vertex_a = meshes[i].vertices[meshes[i].faces[f].a];
				Vector3 vertex_b = meshes[i].vertices[meshes[i].faces[f].b];
				Vector3 vertex_c = meshes[i].vertices[meshes[i].faces[f].c];

				Vector3 pixel_a = _project(vertex_a, transform);
				Vector3 pixel_b = _project(vertex_b, transform);
				Vector3 pixel_c = _project(vertex_c, transform);
				// put_triangle(pixel_a.x, pixel_a.y, pixel_b.x, pixel_b.y,
				// 					pixel_c.x, pixel_c.y, white);
				put_filled_triangle(pixel_a, pixel_b, pixel_c);
			};
			// thread_list.push_back(std::thread(draw_face));
			draw_face();
		}
		// for (std::thread & obj : thread_list)
		// 	obj.join();
	}
	set_draw_color(r, g, b, a);
}

void
lcppgl::ZPrinter::clear(void)
{
	float	max(std::numeric_limits<float>::max());
	int		buff_size(_current_context.width() * _current_context.height());
	
	for (int i(0); i < buff_size; ++i)
		_z_buffer[i] = max;
	SDL_RenderClear(_current_context.renderer());
}

void
lcppgl::ZPrinter::present(void)
{
	SDL_RenderPresent(_current_context.renderer());
}