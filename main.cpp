#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>






#define WIDTH  800
#define HEIGHT 600



SDL_Window* window;
SDL_Renderer* renderer;
SDL_Texture* texture;
SDL_Event event;
uint32_t* textureBuffer;

struct Vec2 {
	float x, y;


	// operations
	Vec2 operator+(const Vec2& other) const {
		return { x + other.x, y + other.y };
	}

	Vec2 operator-(const Vec2& other) const {
		return { x - other.x, y - other.y };
	}

	Vec2 operator*(const Vec2& other) const {
		return { x * other.x, y * other.y };
	}

	Vec2 operator/(const Vec2& other) const {
		return { x / other.x, y / other.y };
	}

	float dot(const Vec2& other) const {
		return { x * other.x + y * other.y };
	}

};

struct Vec3 {
	float x, y, z;


	// operations
	Vec3 operator+(const Vec3& other) const {
		return { x + other.x, y + other.y, z + other.z };
	}

	Vec3 operator-(const Vec3& other) const {
		return { x - other.x, y - other.y, z - other.z };
	}

	Vec3 operator*(const Vec3& other) const {
		return { x * other.x, y * other.y, z * other.z };
	}

	Vec3 operator/(const Vec3& other) const {
		return { x / other.x, y / other.y, z / other.z };
	}

	float dot(const Vec3& other) const {
		return { x * other.x + y * other.y + z * other.z };
	}

	Vec3 cross(const Vec3& other) const {
		return { y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x };
	}

	float length() const {
		return sqrtf(x * x + y * y + z * z);
	}

	Vec3 normalized() const {
		float len = length();
		return { x / len, y / len, z / len };
	}

};

/*struct Mat4 {

	float m[16];

	

	Mat4 operator+(const Mat4& other) {
		Mat4 result;

		for (int s = 0; s < m.size(); s++) {
			for (int i = 0; i < m[s].size(); i++) {
				m[s][i] = m[s][i] + other.m[s][i];
			}
		}


		return { result };

	}

	Mat4 operator-(const Mat4& other) {

	}
};*/


void putPixel(int x, int y, Uint8 r, Uint8 g, Uint8 b, Uint8 a = SDL_ALPHA_OPAQUE) {
	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT) {
		uint32_t color = (a << 24) | (r << 16) | (g << 8) | b;
		textureBuffer[y * WIDTH + x] = color;
	}
}


//bresenham
void drawLineH(int x0, int y0, int x1, int y1, Uint8 r, Uint8 g, Uint8 b) {
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
			putPixel(x0 + i, y, r, g, b);

			if (p >= 0) {
				y += dir;
				p = p - 2 * dx;
			}
			p = p + 2 * dy;


		}
	}

};


void drawLineV(int x0, int y0, int x1, int y1, Uint8 r, Uint8 g, Uint8 b) {
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
			putPixel(x, y0 + i, r, g, b);

			if (p >= 0) {
				x += dir;
				p = p - 2 * dy;
			}
			p = p + 2 * dx;


		}
	}

};

// uses bresenham
void drawLine(int x0, int y0, int x1, int y1, Uint8 r, Uint8 g, Uint8 b) {
	if (abs(x1 - x0) > abs(y1 - y0)) {
		drawLineH(x0, y0, x1, y1, r, g, b);
	}
	else {
		drawLineV(x0, y0, x1, y1, r, g, b);
	}
}

bool edgeFunc(const Vec2 &a, const Vec2 &b, const Vec2 &c) {
	// center point of pixel

	return ((c.x - a.x) * (b.y - a.y) - (c.y - a.y) * (b.x - a.x) >= 0);
}



int main(int argc, char* argv[]) {



	std::vector<Vec2> vertices;
	vertices.push_back({ 400, 100 });
	vertices.push_back({ 200, 450 });
	vertices.push_back({ 600, 450 });
	//vertices.push_back({ 400, 100 });

	//vertices.push_back({ 400, 100 });



	/* 
	bresenhams algo 

	draw lines from left to right
	x1 < x2 and y1 < y2
	Slope of the line is between 0 and 1. Draw from lower left to upper right
	
	
	*/






	if (!SDL_Init(SDL_INIT_VIDEO)) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL: %s", SDL_GetError());
		return 3;
	}

	window = SDL_CreateWindow(
		"JM Render",
		WIDTH,
		HEIGHT,
		SDL_WINDOW_RESIZABLE
	);


	
	renderer = SDL_CreateRenderer(window, NULL);
	texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, WIDTH, HEIGHT);
	textureBuffer = new uint32_t[WIDTH * HEIGHT];


	/*Mat4 matrix1;
	matrix1.matrix[0][3] = 5;
	std::cout << matrix1.matrix[0][3] << std::endl;*/



	// main loop
	bool running = true;
	while (running) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_EVENT_QUIT) {
				running = false;
			}
		}

			// clear
			memset(textureBuffer, 0, WIDTH * HEIGHT * sizeof(uint32_t));


			for (int i = 0; i < vertices.size(); i++) {
				int next = (i + 1) % vertices.size();
				drawLine(vertices[i].x, vertices[i].y, vertices[next].x, vertices[next].y, 255, 255, 255);

			}

			bool inside = true;


			//bresenham(100, 100, 400, 300, 255, 0, 0);    // red diagonal
			//bresenham(0, 200, 600, 200, 0, 255, 0);      // green horizontal
			/*utPixel(300, 240, 0, 0, 0, 255);
			putPixel(450, 140, 0, 0, 0, 255);
			putPixel(150, 340, 0, 0, 0, 255);
			*/



			SDL_UpdateTexture(texture, NULL, textureBuffer, WIDTH * sizeof(Uint32));
			SDL_RenderTexture(renderer, texture, NULL, NULL);
			SDL_RenderPresent(renderer);


		}

		SDL_DestroyTexture(texture);
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
		return 0;
	}
