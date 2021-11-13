/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Application.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 20:48:15 by ldutriez          #+#    #+#             */
/*   Updated: 2021/11/13 18:12:42 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Application.hpp"

lcppgl::Application::Application(void) : lcppgl::Singleton()
, _window(NULL), _renderer(NULL), _is_running(false), _fps_limit(60)
, _event_functors(), _render_functors()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		throw std::invalid_argument(SDL_GetError());
	if (!(_window = SDL_CreateWindow("LCppGL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_OPENGL)))
		throw std::invalid_argument(SDL_GetError());
	if (!(_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)))
		throw std::invalid_argument(SDL_GetError());
	if (TTF_Init() == -1)
		throw std::invalid_argument(TTF_GetError());
	if (IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) == 0)
		throw std::invalid_argument(IMG_GetError());
}

lcppgl::Application::~Application(void)
{
	_event_functors.clear();
	_render_functors.clear();
	if (_renderer)
		SDL_DestroyRenderer(_renderer);
	if (_window)
		SDL_DestroyWindow(_window);
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

lcppgl::Application &
lcppgl::Application::instance(void)
{
	static Application instance;
	return instance;
}

int
lcppgl::Application::width(void) const
{
	int w;
	SDL_GetWindowSize(_window, &w, NULL);
	return w;
}

int
lcppgl::Application::height(void) const
{
	int h;
	SDL_GetWindowSize(_window, NULL, &h);
	return h;
}

bool
lcppgl::Application::is_fullscreen(void) const
{
	return SDL_GetWindowFlags(_window) & SDL_WINDOW_FULLSCREEN;
}

bool
lcppgl::Application::is_resizable(void) const
{
	return SDL_GetWindowFlags(_window) & SDL_WINDOW_RESIZABLE;
}

bool
lcppgl::Application::is_borderless(void) const
{
	return SDL_GetWindowFlags(_window) & SDL_WINDOW_BORDERLESS;
}

void
lcppgl::Application::set_window_title(const std::string & title)
{
	SDL_SetWindowTitle(_window, title.c_str());
}

void
lcppgl::Application::set_window_size(const int width, const int height)
{
	SDL_SetWindowSize(_window, width, height);
}

void
lcppgl::Application::set_window_fullscreen(const bool fullscreen)
{
	SDL_SetWindowFullscreen(_window, fullscreen ? SDL_WINDOW_FULLSCREEN : 0);
}

void
lcppgl::Application::set_window_resizable(const bool resizable)
{
	SDL_SetWindowResizable(_window, resizable ? SDL_FALSE : SDL_TRUE);
}

void
lcppgl::Application::set_window_borderless(const bool borderless)
{
	SDL_SetWindowBordered(_window, borderless ? SDL_FALSE : SDL_TRUE);
}

void
lcppgl::Application::set_render_draw_color(const SDL_Color & color)
{
	SDL_SetRenderDrawColor(_renderer, color.r, color.g, color.b, color.a);
}

void
lcppgl::Application::set_render_draw_color(const Uint8 r, const Uint8 g, const Uint8 b, const Uint8 a)
{
	SDL_SetRenderDrawColor(_renderer, r, g, b, a);
}

void
lcppgl::Application::set_fps_limit(const unsigned int fps_limit)
{
	_fps_limit = (fps_limit != 0) ? fps_limit : UINT32_MAX;
}

void
lcppgl::Application::clear_window(void)
{
	SDL_RenderClear(_renderer);
}

void
lcppgl::Application::present_window(void)
{
	SDL_RenderPresent(_renderer);
}

void
lcppgl::Application::put_outlined_rect(const SDL_Rect & rect)
{
	SDL_RenderDrawRect(_renderer, &rect);
}

void
lcppgl::Application::put_filled_rect(const SDL_Rect & rect)
{
	SDL_RenderFillRect(_renderer, &rect);
}

void
lcppgl::Application::event_manager(void)
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		for (size_t i(0); i < _event_functors.size(); i++)
			_event_functors[i](event);
	}
}

void
lcppgl::Application::render_manager(void)
{
	for (size_t i(0); i < _render_functors.size(); i++)
		_render_functors[i]();
}

void
lcppgl::Application::run(void)
{
	// Limit the framerate
	const unsigned int frame_delay(1000 / _fps_limit);
	unsigned int frame_start(SDL_GetTicks());
	
	_is_running = true;
	while (_is_running == true)
	{
		event_manager();
		if (SDL_GetTicks() - frame_start >= frame_delay)
		{
			render_manager();
			frame_start = SDL_GetTicks();
		}
	}
}

void
lcppgl::Application::stop(void)
{
	_is_running = false;
}

void
lcppgl::Application::quit(void)
{
	this->~Application();
}

int
lcppgl::Application::add_event_functor(void (*functor)(SDL_Event))
{
	_event_functors.push_back(functor);
	return _event_functors.size() - 1;
}

void
lcppgl::Application::remove_event_functor(const int index)
{
	_event_functors.erase(_event_functors.begin() + index);
}

int
lcppgl::Application::add_render_functor(void (*functor)(void))
{
	_render_functors.push_back(functor);
	return _render_functors.size() - 1;
}

void
lcppgl::Application::remove_render_functor(const int index)
{
	_render_functors.erase(_render_functors.begin() + index);
}