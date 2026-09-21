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
void mouse_call(SDL_Window* window, double xposIn, double yposIn);
void scroll_callback(SDL_Window* window, double xoffest, double yoffset);


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




//Camera
Vec3 cameraPos = Vec3(0.0, 0.0, 3.0);
Vec3 cameraFront = Vec3(0.0, 0.0, -1.0);
Vec3 cameraUp = Vec3(0.0, 1.0, 0.0);

bool firstMouse = true;
float yaw = -90.0f;
float pitch = 0.0f;
float lastX = 800.0f / 2.0;
float lastY = 600.0 / 2.0;
float fov = 45.0f;

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
	if (area > 0) return; //backface cull


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


// linear interpolation
static Vec4 lerp(const Vec4& a, const Vec4& b, float t) {
	return { a.x + (b.x - a.x) * t,
			 a.y + (b.y - a.y) * t,
			 a.z + (b.z - a.z) * t,
			 a.w + (b.w - a.w) * t };
}

static int clipNear(Vec4 a, Vec4 b, Vec4 c, Vec4* out) {
	Vec4 in[3] = { a, b, c };
	int n = 0;
	for (int i = 0; i < 3; i++) {
		const Vec4& cur = in[i];
		const Vec4& nxt = in[(i + 1) % 3];
		bool curIn = cur.z >= 0.0f;
		bool nxtIn = nxt.z >= 0.0f;
		if (curIn) out[n++] = cur;
		if (curIn != nxtIn) {
			float t = cur.z / (cur.z - nxt.z);
			out[n++] = lerp(cur, nxt, t);
		}
	}
	return n;
}

// vertex to clip space no divide
Vec4 toClip(const Vertex& in, const Mat4& mvp) {
	return mvp * Vec4{ in.pos.x, in.pos.y, in.pos.z, 1.0f };
}

//divide
Vertex toScreen(const Vec4& clip) {
	Vec4 ndc = clip.p_divide();
	Vertex out{};
	out.pos.x = (ndc.x + 1.0f) * 0.5f * WIDTH;
	out.pos.y = (1.0f - ndc.y) * 0.5f * HEIGHT; // flip y
	out.pos.z = ndc.z;
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

	// capture mouse
	SDL_SetWindowRelativeMouseMode(window, true); //hides mouse and captures it

	
	renderer = SDL_CreateRenderer(window, NULL);
	texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, framebuffer.Width, framebuffer.Height);
	SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_NONE);


	// main loop
	bool running = true;
	while (running) {

		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_EVENT_QUIT) running = false;
			else if (event.type == SDL_EVENT_MOUSE_MOTION) {
				float sensitivity = 0.1f;
				yaw += event.motion.xrel * sensitivity;
				pitch -= event.motion.yrel * sensitivity;
				if (pitch > 89.0f) pitch = 89.0f;
				if (pitch < -89.0f) pitch = -89.0f;

				Vec3 dir;
				dir.x = std::cos(rad(yaw))* std::cos(rad(pitch));
				dir.y = std::sin(rad(pitch));
				dir.z = std::sin(rad(yaw)) * std::cos(rad(pitch));
				cameraFront = dir.normalized();
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


		Mat4 mvp = projectMat * view;


		for (int i = 0; i < model.numfaces(); i++) {
			Vertex a = model.vert(i, 0);
			Vertex b = model.vert(i, 1);
			Vertex c = model.vert(i, 2);

			// flat shading
			Vec3 n = (b.pos - a.pos).cross(c.pos - a.pos).normalized();
			Vec3 lightDir = Vec3(0.5f, 1.0f, 0.7f).normalized();
			float key = n.dot(lightDir);        if (key < 0) key = 0;
			float fill = n.dot(lightDir * -1.0f); if (fill < 0) fill = 0;
			float intensity = 0.15f + 0.7f * key + 0.3f * fill;
			Vec3 flatColor = { intensity, intensity, intensity };

			//clip space
			Vec4 ca = toClip(a, mvp), cb = toClip(b, mvp), cc = toClip(c, mvp);

			// near plane clip
			Vec4 poly[4];
			int count = clipNear(ca, cb, cc, poly);

			// fan triangulate, divide + rasterize
			for (int i = 1; i + 1 < count; i++) {
				Vertex pa = toScreen(poly[0]);     pa.color = flatColor;
				Vertex pb = toScreen(poly[i]);     pb.color = flatColor;
				Vertex pc = toScreen(poly[i + 1]); pc.color = flatColor;
				triangle({ pa, pb, pc }, framebuffer, zbuffer);
			}
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
			//std::cout << cameraPos << "\n";
		}

		if (key_states[SDL_SCANCODE_S]) {
			cameraPos -= cameraFront * cameraSpeed;
			//std::cout << cameraPos << "\n";
		}


		if (key_states[SDL_SCANCODE_A]) {
			cameraPos -= cameraFront.cross(cameraUp).normalized() * cameraSpeed;
			//std::cout << cameraPos << "\n";
		}

		if (key_states[SDL_SCANCODE_D]) {
			cameraPos += cameraFront.cross(cameraUp).normalized() * cameraSpeed;
			//std::cout << cameraPos << "\n";
		}

		if (key_states[SDL_SCANCODE_ESCAPE]) {
			SDL_SetWindowRelativeMouseMode(window, false);
			SDL_CaptureMouse(false);
		}

	}

