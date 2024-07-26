#include "terrain.hpp"

Water::Water()
	: gridSize{ 10.f }, grids{ 300 }, window{ nullptr }, renderer{ nullptr },
	t { 0.f }
{}

void Water::Init(Renderer::Window* windowPtr, Renderer::Render* rendererPtr)
{
	window = windowPtr;
	renderer = rendererPtr;

	// setup the vertex attributes
	surfaceShader.attach(window);
	surfaceShader.createFromFile("./shaders/surface.vert", "./shaders/surface.frag", true);
	surfaceShader.vertexAttribAdd(0, Renderer::AttribType::VEC3);
	//surfaceShader.vertexAttribAdd(1, Renderer::AttribType::VEC3);
	surfaceShader.vertexAttribsEnable();

	// setup the uniform variables
	surfaceShader.uniformAdd("u_projection", Renderer::UniformType::MAT4);
	surfaceShader.uniformAdd("u_view", Renderer::UniformType::MAT4);
	surfaceShader.uniformAdd("u_camera", Renderer::UniformType::VEC3);
	surfaceShader.uniformAdd("u_skybox", Renderer::UniformType::INT);
	surfaceShader.uniformAdd("u_time", Renderer::UniformType::FLOAT);
	
	// texture bound to slot 0 ... cuz there's only 1 image lul
	surfaceShader.setUniformInt("u_skybox", 0);
	surfaceShader.setUniformFloat("u_time", t);

	// create the projection matrix
	float fov = PI / 4.f;
	float aspect = static_cast<float>(WINDOW_WIDTH) / static_cast<float>(WINDOW_HEIGHT);
	std::cout << aspect << "\n";
	float far = 5000.f;
	float near = 1.f;
	Renderer::Mat4<float> projection(
			1.f / (aspect * std::tan(fov / 2.f)), 0.f, 0.f, 0.f,
			0.f, 1.f / (std::tan(fov / 2.f)), 0.f, 0.f,
			0.f, 0.f, -(far + near) / (far - near), -2.f * far * near / (far - near),
			0.f, 0.f, -1.f, 0.f
	);
	surfaceShader.setUniformMatrix("u_projection", *projection);
}

void Water::Render(const Renderer::Mat4<float>& view, const Renderer::Vec3<float>& position)
{
	t += 0.05;
	// rendering stuff
	surfaceShader.setUniformMatrix("u_view", *view);
	surfaceShader.setUniformFloat("u_camera", *position);
	surfaceShader.setUniformFloat("u_time", t);

	renderer->bindShader(&surfaceShader);

	// offsets
	float offset_x = -grids / 2.f * gridSize;
	float offset_z = -100.f;
	float offset_y = -200.f;

	// rendering
	for(int row=0;row<grids;++row)
	{
		for(int col=0;col<grids;++col)
		{
			renderer->beginShape(Renderer::DrawType::TRIANGLE, 4, 0);

			renderer->vertex3f(offset_x + col * gridSize, offset_y, offset_z + row * -gridSize);
			renderer->nextVertex();

			renderer->vertex3f(offset_x + col * gridSize, offset_y, offset_z + row * -gridSize - gridSize);
			renderer->nextVertex();

			renderer->vertex3f(offset_x + col * gridSize + gridSize, offset_y, offset_z + row * -gridSize - gridSize);
			renderer->nextVertex();

			renderer->vertex3f(offset_x + col * gridSize + gridSize, offset_y, offset_z + row * -gridSize);

			renderer->endShape();
		}
	}
}

Water::~Water()
{
}
