#include <iostream>
#include "GameSystem/SystemManager/SystemManager.h"


using namespace std;

int main() {
	auto init_errors = g_manager.init();

	if (init_errors){
		cout << init_errors.toString() << endl;
		getchar();
		return 1;
	}

	auto loop_errors = g_manager.loop();

	if (loop_errors) {
		cout << loop_errors.toString() << endl;
		getchar();
		return 2;
	}

	auto free_errors = g_manager.free();

	if (free_errors) {
		cout << free_errors.toString() << endl;
		getchar();
		return 3;
	}

	return 0;
}

/*
float getRandScaled1() {
	return (static_cast <float> (rand()) / static_cast <float> (RAND_MAX) - 0.5) * 2;
}

int main() {

	UniformReference modelUniform("model");
	UniformReference projectionUniform("projection");
	UniformReference viewUniform("view");	

	ShaderPipeline pipeline;

	ShaderManager shaders;
	Window window;
	FPSController fpsController;
	GLManager glManager;
	shared_ptr<GLProgram> program(new GLProgram());
	shared_ptr<Mesh> piramid(new Mesh());
	shared_ptr<Texture2D> dirtTexture(new Texture2D());
	PhisicWorld world;

	ErrorList errors;
	errors += window.init();
	errors += glManager.init();

	int bufferSizeX, bufferSizeY;
	window.getBufferSize(bufferSizeX, bufferSizeY);
	glManager.setViewportSize(bufferSizeX, bufferSizeY);

	ShaderInfo buffShader;

	errors += piramid->loadFromFile("resources/models/onime/girl.blend"); 
	errors += dirtTexture->loadFromFile("resources/models/onime/textures.png");

	errors += shaders.compileShader("resources/shaders/default.frag", buffShader);
	pipeline.shaderSet.push_back(buffShader);
	
	errors += shaders.compileShader("resources/shaders/default.vert", buffShader);
	pipeline.shaderSet.push_back(buffShader);

	if(!errors)
		errors += program->setupPipeline(pipeline);

	errors += program->getUniformSystem().registerUniform(modelUniform);
	errors += program->getUniformSystem().registerUniform(projectionUniform);
	errors += program->getUniformSystem().registerUniform(viewUniform);

	if (errors) {
		cout << "Occur init errors: " << endl;
		cout << errors.toString() << endl;
		system("pause");
		return static_cast<int>(ErrorCode::General);
	}

	glm::mat4 projection = glm::perspective(45.0f, (float)window.getAspectRatio(), 0.1f, 1000.0f);
	vector<vector<GraphicObject>> triangleArray;


	int gridSize = 1;
	for (int y = 0; y < gridSize; y++) {
		triangleArray.push_back(vector<GraphicObject>());
		for (int x = 0; x < gridSize; x++) {
			triangleArray[y].push_back(GraphicObject());
			triangleArray[y].back().setModelUniform(modelUniform);
			triangleArray[y].back().setTexture(dirtTexture);
			triangleArray[y].back().setProjectionUniform(projectionUniform);
			triangleArray[y].back().setViewUniform(viewUniform);
			triangleArray[y].back().setMesh(piramid);
			triangleArray[y].back().setProgram(program);
			triangleArray[y].back().setProjection(projection);
			triangleArray[y].back().setPosition({(x - gridSize/2) * 0.4,(y - gridSize/2) * 0.4,-3.0});
			triangleArray[y].back().setScale(glm::vec3(1.0));
		}
	}

	std::shared_ptr<Camera> camera(new Camera());
	world.registerObject(std::dynamic_pointer_cast<IPhisicSimulatable>(camera));
	window.addListener(std::dynamic_pointer_cast<IControlHandler>(camera));
	fpsController.setTargetFPS(60);

	while (!window.shouldClose()) {
		program->enableThis();

		window.setTitle(string("fps: ") + to_string((int)fpsController.getSmoothFPS()));
		window.poll();
		world.simulate(fpsController.getFrameDelta());

		float flexRotate = 0.05;
		float flexPosition = 0.01;
		float flexScale = 0.005;

		//game logic
		for (int y = 0; y < gridSize; y++) {
			for (int x = 0; x < gridSize; x++) {
				triangleArray[y][x].setView(camera->getView());
				triangleArray[y][x].addRotation({0.0,0.01,0.0});
				//triangleArray[y][x].addRotation({ flexRotate * getRandScaled1(), flexRotate * getRandScaled1(), flexRotate * getRandScaled1 ()});
				//triangleArray[y][x].addPosition({ flexPosition * getRandScaled1(), flexPosition * getRandScaled1(), flexPosition * getRandScaled1() });
				//triangleArray[y][x].addScale({ flexScale * getRandScaled1(), flexScale * getRandScaled1(), flexScale * getRandScaled1() });
			}
		}

		glClearColor(0.1, 0.1, 0.15, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		for (int y = 0; y < gridSize; y++) {
			for (int x = 0; x < gridSize; x++) {
				triangleArray[y][x].render();
			}
		}

		program->disablePrograms();

		window.draw();
		fpsController.seek();
	}

	return 0;
}
*/

