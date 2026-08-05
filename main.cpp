#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>
#include <list>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <random>
#include "JM_Math.h"
#include "model.h"
#include <cmath>

void processInput(SDL_Window* window);


SDL_Window* window;
SDL_Renderer* renderer;
SDL_Texture* texture;
SDL_Event event;

constexpr int WIDTH = 1200;
constexpr int HEIGHT = 800;

struct Texture {
	int Height;
	int Width;
	std::unique_ptr<uint32_t[]> pixels;

	Texture(int w, int h)
		: Width(w), Height(h),
		pixels(std::make_unique<uint32_t[]>(w * h)) {}
};



struct App {

};

//Camera
Vec3 cameraPos = Vec3(0.0, 0.0, 3.0);
Vec3 cameraFront = Vec3(0.0, 0.0, -1.0);
Vec3 cameraUp = Vec3(0.0, 1.0, 0.0);

//time
float deltaTime = 0.0f;
float lastFrame = 0.0f;


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
double signedArea(const Vertex& a, const Vertex& b, const Vertex& c) {

	return .5 * ((b.pos.y - a.pos.y) * (b.pos.x + a.pos.x) + (c.pos.y - b.pos.y) * (c.pos.x + b.pos.x) + (a.pos.y - c.pos.y) * (a.pos.x + c.pos.x));
}


void triangle(const std::vector<Vertex>& v, Texture& framebuffer, std::vector<float>& zbuffer) {

	double area = signedArea(v[0], v[1], v[2]);
	if (std::abs(area) < 1) return; //rejects degenerate triangles


	int minx = std::max(0, (int)std::min({ v[0].pos.x, v[1].pos.x, v[2].pos.x }));
	int miny = std::max(0, (int)std::min({ v[0].pos.y, v[1].pos.y, v[2].pos.y }));
	int maxx = std::min(framebuffer.Width - 1, (int)std::max({ v[0].pos.x, v[1].pos.x, v[2].pos.x }));
	int maxy = std::min(framebuffer.Height - 1, (int)std::max({ v[0].pos.y, v[1].pos.y, v[2].pos.y }));


	// iteration for drawing line
	for (int x = minx; x <= maxx; x++) {
		for (int y = miny; y <= maxy; y++) {
			float a = signedArea(Vertex{ {(float)x,(float)y} }, v[1], v[2]) / area;
			float b = signedArea(Vertex{ {(float)x,(float)y} }, v[2], v[0]) / area;
			float c = signedArea(Vertex{ {(float)x,(float)y} }, v[0], v[1]) / area;
			if (a >= 0 && b >= 0 && c >= 0){
				float z = a * v[0].pos.z + b * v[1].pos.z + c * v[2].pos.z;
			int idx = y * framebuffer.Width + x;

			if (z < zbuffer[idx]) {
				zbuffer[idx] = z;
				Uint8 s = (Uint8)(v[0].color.x * 255.0f + 0.5f);
				putPixel(x, y, s, s, s, framebuffer);
				}
			}
		}
	}
}



Vertex project(const Vertex& in, const Mat4& mvp) {
	Vec4 clip = (mvp * Vec4{ in.pos.x, in.pos.y, in.pos.z, 1.0f }).p_divide();

	Vertex out = in;
	out.pos.x = (clip.x + 1.0f) * 0.5f * WIDTH;
	out.pos.y = (1.0f - clip.y) * 0.5f * HEIGHT; // flip y
	out.pos.z = clip.z;
	return out;
}



int main(int argc, char* argv[]) {

	// quick area to load in any model.
	std::string mdlPath;
	std::cout << "Input path of obj model";
	std::cin >> mdlPath;

	Texture framebuffer(WIDTH, HEIGHT);

	std::vector<float> zbuffer(WIDTH * HEIGHT, 1e9f); //statrts infinitely far
	
	Model model(mdlPath);

	float aspect = (float)WIDTH / (float)HEIGHT;
	Mat4 projectMat = Mat4::perspective(60.0f, aspect, 0.1f, 100.0f);


	if (!SDL_Init(SDL_INIT_VIDEO)) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL: %s", SDL_GetError());
		return 3;
	}

	SDL_Window* window = SDL_CreateWindow(
		"JM Render",
		framebuffer.Width,
		framebuffer.Height,
		SDL_WINDOW_RESIZABLE
	);


	
	renderer = SDL_CreateRenderer(window, NULL);
	texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, framebuffer.Width, framebuffer.Height);
	SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_NONE);


	float angle = 0.0f;

	// main loop
	bool running = true;
	while (running) {

		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_EVENT_QUIT) {
				running = false;
			}
		}

		//per-frame time logic
		float curFrame = SDL_GetTicks() / 1000.0f;
		deltaTime = curFrame - lastFrame;
		lastFrame = curFrame;

		// Input
		processInput(window);

		// clear
		memset(framebuffer.pixels.get(), 0, framebuffer.Width * framebuffer.Height * sizeof(uint32_t));
		for (float& d : zbuffer) d = 1e9f;



		Mat4 view;
		float radius = 5.0f;

		view = view.lookAt(cameraPos, cameraPos + cameraFront, cameraUp);


		//Mat4 mvp = projectMat * (Mat4::translate(0, 0, -4) * Mat4::rotateY(angle)); //old way hardcoded in.
		Mat4 mvp = projectMat * view;


			for (int i = 0; i < model.numfaces(); i++) {
				Vertex a = model.vert(i, 0);
				Vertex b = model.vert(i, 1);
				Vertex c = model.vert(i, 2);

				Vec3 n = (b.pos - a.pos).cross(c.pos - a.pos).normalized();

				Vec3 lightDir = Vec3(std::sin(curFrame) * radius, 0.0f, std::cos(curFrame) * radius).normalized();
				float key = n.dot(lightDir);        if (key < 0) key = 0;
				float fill = n.dot(lightDir * -1.0f); if (fill < 0) fill = 0;
				float intensity = 0.15f + 0.7f * key + 0.3f * fill;

				Vertex pa = project(a, mvp); pa.color = { intensity, intensity, intensity };
				Vertex pb = project(b, mvp); pb.color = { intensity, intensity, intensity };
				Vertex pc = project(c, mvp); pc.color = { intensity, intensity, intensity };

				triangle({pa, pb, pc}, framebuffer, zbuffer);

			}

		SDL_UpdateTexture(texture, NULL, framebuffer.pixels.get(), framebuffer.Width * sizeof(uint32_t));
		SDL_RenderClear(renderer);
		SDL_RenderTexture(renderer, texture, NULL, NULL);
		SDL_RenderPresent(renderer);
		}

		SDL_DestroyTexture(texture);
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
		return 0;
	}


	void processInput(SDL_Window* window) {

		const bool* key_states = SDL_GetKeyboardState(NULL);
		float cameraSpeed = static_cast<float>(2.5 * deltaTime);

		if (key_states[SDL_SCANCODE_W]) {
			cameraPos += cameraFront * cameraSpeed;
			std::cout << cameraPos << "\n";
		}

		if (key_states[SDL_SCANCODE_S]) {
			cameraPos -= cameraFront * cameraSpeed;
			std::cout << cameraPos << "\n";
		}


		if (key_states[SDL_SCANCODE_A]) {
			cameraPos -= cameraFront.cross(cameraUp).normalized() * cameraSpeed;
			std::cout << cameraPos << "\n";
		}

		if (key_states[SDL_SCANCODE_D]) {
			cameraPos += cameraFront.cross(cameraUp).normalized() * cameraSpeed;
			std::cout << cameraPos << "\n";
		}
	}
