#include <GLFW/glfw3.h>
#include <thread>         // std::this_thread::sleep_for
#include <vector>

using namespace std;


const int width = 1000;
const int height = 800;
const int line_width = 2;
const int circle_number = 20;
float* pixels = new float[width*height * 3];

void drawPixel(const int& i, const int& j, const float& red, const float& green, const float& blue);
void drawOnPixelBuffer();



class Circle
{
	float red = 1.0f, green = 0, blue = 0;
	int i0 = 500, j0 = 500;
	float r = 80;
	int bold = 300;

public:
	void draw()
	{
		for (int i = i0 - r; i <= i0 + r; i++) {
			for (int j = j0 - r; j <= j0 + r; j++) {
				int f = (i - i0)*(i - i0) + (j - j0)*(j - j0) - r*r;
				if (f <= 0 && f >= -bold) {
					drawPixel(i, j, red, green, blue);
				}
			}
		}
	}
};

class Box
{
	int i0 = 300, j0 = 300;
	int length = 100;
	float red = 1.0, green = 0.0, blue = 0.0;

public:
	void draw()
	{
		for (int i = i0 - length / 2; i <= i0 + length / 2; i++)
		{
			drawPixel(i, j0 + length / 2, red, green, blue);
		}
		for (int i = i0 - length / 2; i <= i0 + length / 2; i++)
		{
			drawPixel(i, j0 - length / 2, red, green, blue);
		}
		for (int j = j0 - length / 2; j <= j0 + length / 2; j++)
		{
			drawPixel(i0 - length / 2, j, red, green, blue);
		}
		for (int j = j0 - length / 2; j <= j0 + length / 2; j++)
		{
			drawPixel(i0 + length / 2, j, red, green, blue);
		}
	}
};

class GeometricObjectInterface
{
public:
	virtual void draw() = 0;
};

template<class T_HOW_TO_DRAW>
class GeometricObject : public GeometricObjectInterface
{
public:
	void draw()
	{
		T_HOW_TO_DRAW draw_in_color;
		draw_in_color.draw();
	}
};



int main(void)
{
	GLFWwindow* window;
	double xpos, ypos;

	if (!glfwInit())
		return -1;
	window = glfwCreateWindow(width, height, "Hello World", NULL, NULL);
	if (!window) {
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glClearColor(1, 1, 1, 1);

	vector<GeometricObjectInterface *> shape_list;
	shape_list.push_back(new GeometricObject<Circle>);
	shape_list.push_back(new GeometricObject<Box>);

	while (!glfwWindowShouldClose(window))
	{
		drawOnPixelBuffer();
		glfwGetCursorPos(window, &xpos, &ypos);

		for (auto itr : shape_list)
			itr->draw();


		glDrawPixels(width, height, GL_RGB, GL_FLOAT, pixels);
		glfwSwapBuffers(window);
		glfwPollEvents();
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	glfwTerminate();
	delete[] pixels;
	return 0;
}


void drawPixel(const int& i, const int& j, const float& red, const float& green, const float& blue)
{
	pixels[(i + width* j) * 3 + 0] = red;
	pixels[(i + width* j) * 3 + 1] = green;
	pixels[(i + width* j) * 3 + 2] = blue;
}


void drawOnPixelBuffer()
{
	//std::memset(pixels, 1.0f, sizeof(float)*width*height * 3); // doesn't work
	std::fill_n(pixels, width*height * 3, 1.0f);	// white background

													//for (int i = 0; i<width*height; i++) {
													//	pixels[i * 3 + 0] = 1.0f; // red 
													//	pixels[i * 3 + 1] = 1.0f; // green
													//	pixels[i * 3 + 2] = 1.0f; // blue
													//}

	const int i = rand() % width, j = rand() % height;
	drawPixel(i, j, 0.0f, 0.0f, 0.0f);

	// drawing a line
	//TODO: anti-aliasing
	const int i0 = 100, i1 = 200;
	const int j0 = 50, j1 = 80;

	//TODO: try moving object
}