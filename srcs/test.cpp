/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 19:59:07 by ldutriez          #+#    #+#             */
/*   Updated: 2022/10/29 23:07:33 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lcppgl.hpp"
#include <cmath>

int id;

#include <math.h>
#define PI2 6.28318530718

float timing = 0;
float freq = 440;

void exit_input(lcppgl::Context &context, void *param)
{
	bool * slow(reinterpret_cast<bool *>(param));
	
	SDL_Event event;
	if (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
				context.stop();
				break;
			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_ESCAPE)
				{
					context.remove_render_functor(0);
					lcppgl::Application::instance().stop();
				}
				else if (event.key.keysym.sym == SDLK_F11)
				{
					context.set_fullscreen(!context.is_fullscreen());
					if (context.is_fullscreen())
						context.set_size(1920, 1080);
					else
						context.set_size(1920, 1080);
				}
				else if (event.key.keysym.sym == SDLK_s)
				{
					(*slow) = !(*slow);
				}
				break;
			default:
				break;
		}
	}
}

// Put two overlapping rectangles on the screen to test color blending.
void overlapping_rectangles(lcppgl::Context &context, void * param)
{
	(void)param;
	lcppgl::Printer render(context);
	lcppgl::Writer writer(context, "/usr/share/fonts/truetype/freefont/FreeSans.ttf", 25);
	lcppgl::tools::Color red;
	lcppgl::tools::Color green;

	red = lcppgl::tools::Color(255, 0, 0, 120);
	green = lcppgl::tools::Color(0, 255, 0, 255);
	render.clear();
	SDL_SetRenderDrawBlendMode(context.renderer(), SDL_BLENDMODE_ADD);

	render.put_filled_rect(lcppgl::tools::Rectangle(400, 0, 400, 400),
						   red);
	render.put_filled_rect(lcppgl::tools::Rectangle(400, 200, 400, 400),
						   green);

	render.put_filled_rect(lcppgl::tools::Rectangle(0, 200, 400, 200),
						   red + green);

	render.put_outlined_rect(lcppgl::tools::Rectangle(0, 200, 400, 200),
							 lcppgl::tools::Color(255, 255, 255, 255));
	render.put_outlined_rect(lcppgl::tools::Rectangle(400, 200, 400, 200),
							 lcppgl::tools::Color(255, 255, 255, 255));

	writer.put_text("Actual", lcppgl::tools::Rectangle(150, 300, 100, 25),
					lcppgl::tools::Color(0, 0, 0, 255));
	writer.put_text("Expected", lcppgl::tools::Rectangle(550, 300, 100, 25),
					lcppgl::tools::Color(0, 0, 0, 255));
	render.present();
}

#include <sstream> // Needed since you can't use to_string() in C++98.
// Put random text on the screen at rendom position to test text rendering.
// Put text on the screen in the three different ways.
void text_rendering(lcppgl::Context &context, void * param)
{
	(void)param;
	lcppgl::Printer render(context);
	lcppgl::Writer writer(context, "/usr/share/fonts/truetype/freefont/FreeSans.ttf", 80);
	context.set_fps_limit(2);

	render.clear();
	writer.put_text("Hello World!", lcppgl::tools::Rectangle(20, 50, 480, 80),
					lcppgl::tools::Color(255, 255, 255, 255));
	writer.put_text_and_bg("Hello World!", lcppgl::tools::Rectangle(20, 150, 480, 80),
						   lcppgl::tools::Color(255, 255, 255, 255), lcppgl::tools::Color(100, 100, 100, 255));
	writer.put_pretty_text("Hello World!", lcppgl::tools::Rectangle(20, 250, 480, 80),
						   lcppgl::tools::Color(255, 255, 255, 255));

	std::ostringstream nb;

	nb << rand() % 100;
	writer.put_text(nb.str(), lcppgl::tools::Rectangle(rand() % (context.width() - 40), rand() % (context.height() - 80) + 40, 40, 40),
					lcppgl::tools::Color(rand() % 255, rand() % 255, rand() % 255, 255));
	render.present();
}

void great_rendering(lcppgl::Context &context, void * param)
{
	(void)param;
	try
	{
		lcppgl::tools::Texture texture(context, "./ressources/great.png");
		lcppgl::tools::Rectangle img_rect(0, 0, texture.width(), texture.height());
		lcppgl::tools::Rectangle screen_rect(context.width() / 3, context.height() / 3, context.width() / 3, context.height() / 3);
		
		lcppgl::Printer render(context);

		context.set_fps_limit(2);
		
		render.clear();
		texture.render(&img_rect, &screen_rect);
		render.present();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
}

void grid_rendering(lcppgl::Context &context, void * param)
{
	(void)param;
	try
	{
		lcppgl::Printer render(context);
		
		context.set_fps_limit(0);
		render.clear();
		

		for (int i(0); i < context.height() / (20 + 1); i++)
		{
			for (int j(0); j < context.width() / (20 + 1); j++)
			{
				if (rand() % 2 == 0)
					render.set_draw_color(lcppgl::tools::Color(0, 0, 0, 255));
				else
					render.set_draw_color(lcppgl::tools::Color(200, 200, 200, 255));
				render.put_filled_rect(lcppgl::tools::Rectangle(j * (20 + 1), i * (20 + 1), 20, 20));
			}
		}

		render.set_draw_color(lcppgl::tools::Color(0, 0, 0, 255));
		render.present();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
}

void inner_triangle(lcppgl::Printer & printer,
				int i, int a_x, int a_y, int b_x, int b_y, int c_x, int c_y)
{
	lcppgl::tools::Color color(rand() % 255, rand() % 255, rand() % 255, 255);
	
	if (i == 0)
		return;
	
	int ab_center_x((a_x + b_x) / 2);
	int ab_center_y((a_y + b_y) / 2);
	int bc_center_x((b_x + c_x) / 2);
	int bc_center_y((b_y + c_y) / 2);
	int ca_center_x((c_x + a_x) / 2);
	int ca_center_y((c_y + a_y) / 2);

	printer.put_triangle(ab_center_x, ab_center_y, bc_center_x, bc_center_y, ca_center_x, ca_center_y, color);

	inner_triangle(printer, i - 1,
	ab_center_x, ab_center_y, bc_center_x, bc_center_y, ca_center_x, ca_center_y);

	inner_triangle(printer, i - 1,
	ab_center_x, ab_center_y, bc_center_x, bc_center_y, b_x, b_y);
	inner_triangle(printer, i - 1,
	a_x, a_y, ca_center_x, ca_center_y, ab_center_x, ab_center_y);
	inner_triangle(printer, i - 1,
	c_x, c_y, bc_center_x, bc_center_y, ca_center_x, ca_center_y);
}

// The Sierpinski Triangle
void	draw_triangle(lcppgl::Context &context, void * param)
{
	(void)param;
	SDL_PauseAudioDevice(id, false);
	SDL_Delay(100);
	lcppgl::Printer printer(context);

	lcppgl::tools::Rectangle ab(context.width() / 2, 0, context.width() - 1, context.height() - 1);
	lcppgl::tools::Rectangle c(0, context.height() - 1);
	static lcppgl::tools::Color color(255, 255, 255, 255);
	static int i(0);
	static int y(1);

	printer.clear();
	context.set_fps_limit(y);

	printer.put_triangle(ab.x(), ab.y(), ab.width(), ab.height(), c.x(), c.y(), color);
	inner_triangle(printer, i, ab.x(), ab.y(), ab.width(), ab.height(), c.x(), c.y());

	printer.present();
	++i;
	if (i > 11)
		i = 0;
	freq = i * 400 + 400;
	++y;
	SDL_PauseAudioDevice(id, true);
}

void	draw_graph(lcppgl::Context &context, void * param)
{
	(void)param;
	lcppgl::Printer printer(context);
	lcppgl::Writer writer(context, "/usr/share/fonts/truetype/freefont/FreeSans.ttf", 80);

	static lcppgl::tools::Rectangle v_line(context.width() / 10, context.height() / 10,
		context.width() / 10, context.height() - context.height() / 10);
	static lcppgl::tools::Rectangle h_line(v_line.x(), v_line.height(),
		context.width() - v_line.x(), v_line.height());
	static lcppgl::tools::Color white(255, 255, 255, 255);
	
	context.set_fps_limit(0);
	printer.clear();

	printer.put_line(v_line, white);
	printer.put_line(h_line, white);

	// x = 2^n;
	writer.put_pretty_text("f(2^n) = x",
		lcppgl::tools::Rectangle(context.width() * 0.5f - 90, v_line.y(), 180, 30),
		white);
	writer.put_pretty_text("x",
		lcppgl::tools::Rectangle(v_line.x() - 30, v_line.y() - 30 , 20, 30),
		white);
	writer.put_pretty_text("n",
		lcppgl::tools::Rectangle(h_line.width() + 20, h_line.y() + 15, 20, 30),
		white);
		
	int x(0);
	for (int i(0); i < 8; ++i)
	{
		lcppgl::tools::Color current_color(35 * i, 255 / (i + 1), 35 * i, 255);

		x = pow(2, i);
		lcppgl::tools::Rectangle point(v_line.x() + x * 11, h_line.y() - i * 110 - 10,
										5, 5);
		printer.put_filled_rect(point, current_color);

		writer.put_text(std::to_string(i), lcppgl::tools::Rectangle(point.x() - 10, h_line.y() + 3, 20, 20),
					current_color);
		writer.put_text(std::to_string(x), lcppgl::tools::Rectangle(v_line.x() - 30, point.y() - 10, 20, 20),
					current_color);
	}
	printer.present();
}

void	draw_cube(lcppgl::Context &, void * param);

void	choose_the_test(lcppgl::Context &context, void *param)
{
	lcppgl::Writer writer(context, "/usr/share/fonts/truetype/freefont/FreeSans.ttf", 100);
	lcppgl::Printer render(context);

	int size(7);
	std::string str[size] = {"1. overlapping rectangles",
							"2. text rendering",
							"3. image rendering",
							"4. grid rendering",
							"5. Sierpinski Triangle",
							"6. Draw graph",
							"7. 3D rendering"};
	render.clear();
	for (int i(0); i < size; ++i)
	{
		writer.put_pretty_text(str[i], lcppgl::tools::Rectangle(15,
			context.height() / size * i + 15, str[i].size() * 20, 80),
			lcppgl::tools::Color(255, 255, 255, 255));
	}
	render.present();

	SDL_Event event;
	for (bool choosen(false); choosen != true;)
	{
		SDL_WaitEvent(&event);
		switch (event.type)
		{
			case SDL_QUIT:
				context.stop();
				choosen = true;
				break;
			case SDL_KEYDOWN:
				choosen = true;
				if (event.key.keysym.sym == SDLK_ESCAPE)
					context.stop();
				else if (event.key.keysym.sym == SDLK_KP_1 || event.key.keysym.sym == SDLK_1)
						context.add_render_functor(overlapping_rectangles, param);
				else if (event.key.keysym.sym == SDLK_KP_2 || event.key.keysym.sym == SDLK_2)
					context.add_render_functor(text_rendering, param);
				else if (event.key.keysym.sym == SDLK_KP_3 || event.key.keysym.sym == SDLK_3)
					context.add_render_functor(great_rendering, param);
				else if (event.key.keysym.sym == SDLK_KP_4 || event.key.keysym.sym == SDLK_4)
					context.add_render_functor(grid_rendering, param);
				else if (event.key.keysym.sym == SDLK_KP_5 || event.key.keysym.sym == SDLK_5)
					context.add_render_functor(draw_triangle, param);
				else if (event.key.keysym.sym == SDLK_KP_6 || event.key.keysym.sym == SDLK_6)
					context.add_render_functor(draw_graph, param);
				else if (event.key.keysym.sym == SDLK_KP_7 || event.key.keysym.sym == SDLK_7)
					context.add_render_functor(draw_cube, param);
				else
					choosen = false;
				break;
			default:
				break;
		}
	}
	render.clear();
}

void callback(void* userdata, Uint8* stream, int len) {
	(void)userdata;
	short * snd = reinterpret_cast<short*>(stream);
	len /= sizeof(*snd);
	for(int i = 0; i < len; i++) //Fill array with frequencies, mathy-math stuff
	{
		snd[i] = 32000 * sin(timing);
		
		timing += freq * PI2 / 48000.0;
		if(timing >= PI2)
			timing -= PI2;
	}
}

void audio_test(void)
{
	SDL_AudioSpec spec, aspec; // the specs of our piece of "music"
	SDL_zero(spec);
	spec.freq = 48000; //declare specs
	spec.format = AUDIO_S16SYS;
	spec.channels = 1;
	spec.samples = 4096;
	spec.callback = callback;
	spec.userdata = NULL;

  //Open audio, if error, print
	if ((id = SDL_OpenAudioDevice(nullptr, 0, &spec, &aspec, SDL_AUDIO_ALLOW_ANY_CHANGE)) <= 0 )
	{
	  fprintf(stderr, "Couldn't open audio: %s\n", SDL_GetError());
	  exit(-1);
	}

	SDL_PauseAudioDevice(id, true);

}

int main(void)
{
	try
	{
		bool slow(false);
		lcppgl::Context &main_context = lcppgl::Application::instance().create_context("lcppgl tests", 1920, 1080);

		main_context.add_event_functor(exit_input, &slow);
		audio_test();
		while (1)
		{
			choose_the_test(main_context, &slow);
			if (main_context.is_running() == false)
				break ;
			lcppgl::Application::instance().run();
		}
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << '\n';
	}
	return EXIT_SUCCESS;
}