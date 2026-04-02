#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include "JM_Math.h"
#include "mdl_importer.h"




SDL_Window* window;
SDL_Renderer* renderer;
SDL_Texture* texture;
SDL_Event event;

struct Texture {
	int Height;
	int Width;
	std::unique_ptr<uint32_t[]> pixels;

	Texture(int w, int h)
		: Width(w), Height(h),
		pixels(std::make_unique<uint32_t[]>(w * h)) {}
};









void putPixel(int x, int y, Uint8 r, Uint8 g, Uint8 b, Texture& framebuffer) {
	Uint8 a = SDL_ALPHA_OPAQUE;
	if (x >= 0 && x < framebuffer.Width && y >= 0 && y < framebuffer.Height) {
		uint32_t color = (a << 24) | (r << 16) | (g << 8) | b;
		framebuffer.pixels[y * framebuffer.Width + x] = color;
	}
}


//bresenham
void drawLineH(int x0, int y0, int x1, int y1, Uint8 r, Uint8 g, Uint8 b, Texture& framebuffer) {
	if (x0 > x1) {
		std::swap(x0, x1);
		std::swap(y0, y1);
	}


	int dx = x1 - x0;
	int dy = y1 - y0;

	int dir;

	if (dy < 0) {
		dir = -1;
	}
	else {
		dir = 1;
	}


	dy *= dir;


	if (dx != 0) {
		int y = y0;
		int p = 2 * dy - dx;
		for (int i = 0; i < dx + 1; i++) {
			putPixel(x0 + i, y, r, g, b, framebuffer);

			if (p >= 0) {
				y += dir;
				p = p - 2 * dx;
			}
			p = p + 2 * dy;


		}
	}

}


void drawLineV(int x0, int y0, int x1, int y1, Uint8 r, Uint8 g, Uint8 b, Texture& framebuffer) {
	if (y0 > y1) {
		std::swap(x0, x1);
		std::swap(y0, y1);
	}


	int dx = x1 - x0;
	int dy = y1 - y0;

	int dir;

	if (dx < 0) {
		dir = -1;
	}
	else {
		dir = 1;
	}


	dx *= dir;


	if (dy != 0) {
		int x = x0;
		int p = 2 * dx - dy;
		for (int i = 0; i < dy + 1; i++) {
			putPixel(x, y0 + i, r, g, b, framebuffer);

			if (p >= 0) {
				x += dir;
				p = p - 2 * dy;
			}
			p = p + 2 * dx;


		}
	}

}

// uses bresenham
void drawLine(int x0, int y0, int x1, int y1, Uint8 r, Uint8 g, Uint8 b, Texture& framebuffer) {
	if (!framebuffer.pixels) {
		printf("pixels is null!\n");
		return;
	}
	
	
	if (abs(x1 - x0) > abs(y1 - y0)) {
		drawLineH(x0, y0, x1, y1, r, g, b, framebuffer);
	}
	else {
		drawLineV(x0, y0, x1, y1, r, g, b, framebuffer);
	}
}






// edge function using barycentric coordinates
double signedArea(const Vec2& a, const Vec2& b, const Vec2& c) {

	return .5 * ((b.y - a.y) * (b.x + a.x) + (c.y - b.y) * (c.x + b.x) + (a.y - c.y) * (a.x + c.x));
}


void triangle(const std::vector<Vec2>& vertices, Texture& framebuffer) {

	double area = signedArea(vertices[0], vertices[1], vertices[2]);

	int minx = std::min(std::min(vertices[0].x, vertices[1].x), vertices[2].x);
	int miny = std::min(std::min(vertices[0].y, vertices[1].y), vertices[2].y);
	int maxx = std::max(std::max(vertices[0].x, vertices[1].x), vertices[2].x);
	int maxy = std::max(std::max(vertices[0].y, vertices[1].y), vertices[2].y);
	//if (area < 1) return; //backface culling

	// iteration for drawing line
	for (int i = 0; i < vertices.size(); i++) {
		int next = (i + 1) % vertices.size();
		drawLine(vertices[i].x, vertices[i].y, vertices[next].x, vertices[next].y, 255, 255, 255, framebuffer);

	}

	for (int x = minx; x <= maxx; x++) {
		for (int y = miny; y <= maxy; y++) {
			float a = signedArea(Vec2{ static_cast<float>(x), static_cast<float>(y) }, vertices[1], vertices[2]) / area;
			float b = signedArea(Vec2{ static_cast<float>(x), static_cast<float>(y) }, vertices[2], vertices[0]) / area;
			float c = signedArea(Vec2{ static_cast<float>(x), static_cast<float>(y) }, vertices[0], vertices[1]) / area;
			if (a > 0 && b > 0 && c > 0) {
				putPixel(x, y, 255, 255, 255, framebuffer);
			}

		}

	}
}







int main(int argc, char* argv[]) {
	constexpr int WIDTH = 800;
	constexpr int HEIGHT = 600;
	Texture framebuffer(WIDTH, HEIGHT);



	std::vector<Vec2> vertices;
	vertices.push_back({ 400, 100 });
	vertices.push_back({ 200, 450 });
	vertices.push_back({ 600, 450 });


	importer();








	if (!SDL_Init(SDL_INIT_VIDEO)) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL: %s", SDL_GetError());
		return 3;
	}

	window = SDL_CreateWindow(
		"JM Render",
		framebuffer.Width,
		framebuffer.Height,
		SDL_WINDOW_RESIZABLE
	);


	
	renderer = SDL_CreateRenderer(window, NULL);
	texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, framebuffer.Width, framebuffer.Height);




	// main loop
	bool running = true;
	while (running) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_EVENT_QUIT) {
				running = false;
			}
		}

			// clear
			memset(framebuffer.pixels.get(), 0, framebuffer.Width * framebuffer.Height * sizeof(uint32_t));


			triangle(vertices, framebuffer);



			SDL_UpdateTexture(texture, NULL, framebuffer.pixels.get(), framebuffer.Width * sizeof(Uint32));
			SDL_RenderTexture(renderer, texture, NULL, NULL);
			SDL_RenderPresent(renderer);


		}

		SDL_DestroyTexture(texture);
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
		return 0;
	}
