/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Context.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 20:48:15 by ldutriez          #+#    #+#             */
/*   Updated: 2021/11/13 21:53:45 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Context.hpp"

lcppgl::Context::Context(unsigned char id, const char * title, int width, int height) :
 _window(NULL), _renderer(NULL), _id(id),
 _is_running(true), _fps_limit(30),
 _event_functors(), _render_functors()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		throw std::invalid_argument(SDL_GetError());
	if (!(_window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_OPENGL)))
		throw std::invalid_argument(SDL_GetError());
	if (!(_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)))
		throw std::invalid_argument(SDL_GetError());
	if (TTF_Init() == -1)
		throw std::invalid_argument(TTF_GetError());
	if (IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) == 0)
		throw std::invalid_argument(IMG_GetError());
}

lcppgl::Context::Context(const Context &src)
{
	*this = src;
}

lcppgl::Context::~Context(void)
{
	_event_functors.clear();
	_render_functors.clear();
	if (_renderer)
		SDL_DestroyRenderer(_renderer);
	if (_window)
	{
		SDL_DestroyWindow(_window);
	}
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

SDL_Window *
lcppgl::Context::window(void) const
{
	return _window;
}

SDL_Renderer *
lcppgl::Context::renderer(void) const
{
	return _renderer;
}

int
lcppgl::Context::width(void) const
{
	int w;
	SDL_GetWindowSize(_window, &w, NULL);
	return w;
}

int
lcppgl::Context::height(void) const
{
	int h;
	SDL_GetWindowSize(_window, NULL, &h);
	return h;
}

unsigned char
lcppgl::Context::id(void) const
{
	return _id;
}

bool
lcppgl::Context::is_running(void) const
{
	return _is_running;
}

std::string
lcppgl::Context::title(void) const
{
	return SDL_GetWindowTitle(_window);
}

bool
lcppgl::Context::is_fullscreen(void) const
{
	return SDL_GetWindowFlags(_window) & SDL_WINDOW_FULLSCREEN;
}

bool
lcppgl::Context::is_resizable(void) const
{
	return SDL_GetWindowFlags(_window) & SDL_WINDOW_RESIZABLE;
}

bool
lcppgl::Context::is_borderless(void) const
{
	return SDL_GetWindowFlags(_window) & SDL_WINDOW_BORDERLESS;
}

void
lcppgl::Context::set_id(const unsigned char id)
{
	_id = id;
}

void
lcppgl::Context::set_title(const std::string & title)
{
	SDL_SetWindowTitle(_window, title.c_str());
}

void
lcppgl::Context::set_size(const int width, const int height)
{
	SDL_SetWindowSize(_window, width, height);
}

void
lcppgl::Context::set_fullscreen(const bool fullscreen)
{
	SDL_SetWindowFullscreen(_window, fullscreen ? SDL_WINDOW_FULLSCREEN : 0);
}

void
lcppgl::Context::set_resizable(const bool resizable)
{
	SDL_SetWindowResizable(_window, resizable ? SDL_FALSE : SDL_TRUE);
}

void
lcppgl::Context::set_borderless(const bool borderless)
{
	SDL_SetWindowBordered(_window, borderless ? SDL_FALSE : SDL_TRUE);
}

void
lcppgl::Context::set_draw_color(const SDL_Color & color)
{
	SDL_SetRenderDrawColor(_renderer, color.r, color.g, color.b, color.a);
}

void
lcppgl::Context::set_draw_color(const Uint8 r, const Uint8 g, const Uint8 b, const Uint8 a)
{
	SDL_SetRenderDrawColor(_renderer, r, g, b, a);
}

void
lcppgl::Context::set_fps_limit(const unsigned int fps_limit)
{
	_fps_limit = (fps_limit != 0) ? fps_limit : UINT32_MAX;
}

void
lcppgl::Context::clear(void)
{
	SDL_RenderClear(_renderer);
}

void
lcppgl::Context::present(void)
{
	SDL_RenderPresent(_renderer);
}

void
lcppgl::Context::update(void)
{
	const unsigned int frame_delay(1000 / _fps_limit);
	static unsigned int frame_start(SDL_GetTicks());
	
	event_manager();
	if (_is_running == true && SDL_GetTicks() - frame_start >= frame_delay)
	{
		frame_start = SDL_GetTicks();
		render_manager();
	}
}

void
lcppgl::Context::stop(void)
{
	_is_running = false;
}

void
lcppgl::Context::put_outlined_rect(const SDL_Rect & rect)
{
	SDL_RenderDrawRect(_renderer, &rect);
}

void
lcppgl::Context::put_filled_rect(const SDL_Rect & rect)
{
	SDL_RenderFillRect(_renderer, &rect);
}

void
lcppgl::Context::event_manager(void)
{
	// std::cout << "Context::event_manager()" << std::endl;
	for (size_t i(0); i < _event_functors.size(); i++)
		_event_functors[i](*this);
}

void
lcppgl::Context::render_manager(void)
{
	for (size_t i(0); i < _render_functors.size(); i++)
		_render_functors[i](*this);
}

int
lcppgl::Context::add_event_functor(void (*functor)(lcppgl::Context &))
{
	_event_functors.push_back(functor);
	return _event_functors.size() - 1;
}

void
lcppgl::Context::remove_event_functor(const int index)
{
	_event_functors.erase(_event_functors.begin() + index);
}

int
lcppgl::Context::add_render_functor(void (*functor)(lcppgl::Context &))
{
	_render_functors.push_back(functor);
	return _render_functors.size() - 1;
}

void
lcppgl::Context::remove_render_functor(const int index)
{
	_render_functors.erase(_render_functors.begin() + index);
}

lcppgl::Context &
lcppgl::Context::operator=(const Context & src)
{
	if (this != &src)
	{
		_window = src._window;
		_renderer = src._renderer;
		_id = src._id;
		_event_functors = src._event_functors;
		_render_functors = src._render_functors;
	}
	return *this;
}