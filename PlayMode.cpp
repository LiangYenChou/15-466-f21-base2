#include "PlayMode.hpp"

#include "LitColorTextureProgram.hpp"

#include "DrawLines.hpp"
#include "Mesh.hpp"
#include "Load.hpp"
#include "gl_errors.hpp"
#include "data_path.hpp"

#include <glm/gtc/type_ptr.hpp>

#include <random>
#include <cmath>

// Credit:
// The Playmode is reference base code and inspired by previous project: hungry_man 
// The models and scene credit to Yixin He's works: garden.blend
//

//Notes: There are some offset issues for different models in the scene which need to be fixed.


GLuint hexapod_meshes_for_lit_color_texture_program = 0;
Load< MeshBuffer > hexapod_meshes(LoadTagDefault, []() -> MeshBuffer const * {
	MeshBuffer const *ret = new MeshBuffer(data_path("garden.pnct"));
	hexapod_meshes_for_lit_color_texture_program = ret->make_vao_for_program(lit_color_texture_program->program);
	return ret;
});

Load< Scene > hexapod_scene(LoadTagDefault, []() -> Scene const * {
	return new Scene(data_path("garden.scene"), [&](Scene &scene, Scene::Transform *transform, std::string const &mesh_name){
		Mesh const &mesh = hexapod_meshes->lookup(mesh_name);

		scene.drawables.emplace_back(transform);
		Scene::Drawable &drawable = scene.drawables.back();

		drawable.pipeline = lit_color_texture_program_pipeline;

		drawable.pipeline.vao = hexapod_meshes_for_lit_color_texture_program;
		drawable.pipeline.type = mesh.type;
		drawable.pipeline.start = mesh.start;
		drawable.pipeline.count = mesh.count;

	});
});

PlayMode::PlayMode() : scene(*hexapod_scene) {
	//get pointers to leg for convenience:
/*	for (auto &transform : scene.transforms) {
		if (transform.name == "Hip.FL") hip = &transform;
		else if (transform.name == "UpperLeg.FL") upper_leg = &transform;
		else if (transform.name == "LowerLeg.FL") lower_leg = &transform;
	}
	if (hip == nullptr) throw std::runtime_error("Hip not found.");
	if (upper_leg == nullptr) throw std::runtime_error("Upper leg not found.");
	if (lower_leg == nullptr) throw std::runtime_error("Lower leg not found.");

	hip_base_rotation = hip->rotation;
	upper_leg_base_rotation = upper_leg->rotation;
	lower_leg_base_rotation = lower_leg->rotation;*/
	for (auto &transform : scene.transforms){
		//std::cout << transform.name << std::endl;
		if (transform.name == "water opossum") {
			rat = &transform;
			objects.emplace_back("water opossum");
			scene_transforms.emplace_back(rat);
			scene_base_positions.emplace_back(rat->position);
		}
		else if (transform.name == "carrot.001") {
			carrot001 = &transform;
			objects.emplace_back("carrot.001");
			scene_transforms.emplace_back(carrot001);
			scene_base_positions.emplace_back(carrot001->position);
		}
		else if (transform.name == "carrot.003") {
			carrot003 = &transform;
			objects.emplace_back("carrot.003");
			scene_transforms.emplace_back(carrot003);
			scene_base_positions.emplace_back(carrot003->position);
		}
		else if (transform.name == "carrot.007") {
			carrot007 = &transform;
			objects.emplace_back("carrot.007");
			scene_transforms.emplace_back(carrot007);
			scene_base_positions.emplace_back(carrot007->position);
		}
		else if (transform.name == "carrot.011") {
			carrot011 = &transform;
			objects.emplace_back("carrot.011");
			scene_transforms.emplace_back(carrot011);
			scene_base_positions.emplace_back(carrot011->position);
		}
		else if (transform.name == "carrot.012") {
			carrot012 = &transform;
			objects.emplace_back("carrot.012");
			scene_transforms.emplace_back(carrot012);
			scene_base_positions.emplace_back(carrot012->position);
		}

		else if (transform.name == "carrot.008") {
			carrot008 = &transform;
			objects.emplace_back("carrot.008");
			scene_transforms.emplace_back(carrot008);
			scene_base_positions.emplace_back(carrot008->position);
		}
		else if (transform.name == "dirt") {
			ground = &transform;
			objects.emplace_back("dirt");
			scene_transforms.emplace_back(ground);
			scene_base_positions.emplace_back(ground->position);
		}
		

	}
	//std::cout<< (scene_transforms[0])->position.x << "nnnn"<<(scene_transforms[0])->position.z << std::endl;
	pos_offset = glm::vec3(175.0f, 35.0f, 10.0f);

	//get pointer to camera for convenience:
	if (scene.cameras.size() != 1) throw std::runtime_error("Expecting scene to have exactly one camera, but it has " + std::to_string(scene.cameras.size()));
	camera = &scene.cameras.front();



}

PlayMode::~PlayMode() {
}

bool PlayMode::handle_event(SDL_Event const &evt, glm::uvec2 const &window_size) {

	if (evt.type == SDL_KEYDOWN) {
		if (evt.key.keysym.sym == SDLK_ESCAPE) {
			SDL_SetRelativeMouseMode(SDL_FALSE);
			return true;
		} else if (evt.key.keysym.sym == SDLK_a) {
			left.downs += 1;
			left.pressed = true;
			return true;
		} else if (evt.key.keysym.sym == SDLK_d) {
			right.downs += 1;
			right.pressed = true;
			return true;
		} else if (evt.key.keysym.sym == SDLK_w) {
			up.downs += 1;
			up.pressed = true;
			return true;
		} else if (evt.key.keysym.sym == SDLK_s) {
			down.downs += 1;
			down.pressed = true;
			return true;
		}
		else if (evt.key.keysym.sym == SDLK_LEFT) {
			rat_left.downs += 1;
			rat_left.pressed = true;
			return true;
		}
		else if (evt.key.keysym.sym == SDLK_RIGHT) {
			rat_right.downs += 1;
			rat_right.pressed = true;
			return true;
		}
		else if (evt.key.keysym.sym == SDLK_UP) {
			rat_up.downs += 1;
			rat_up.pressed = true;
			return true;
		}
		else if (evt.key.keysym.sym == SDLK_DOWN) {
			rat_down.downs += 1;
			rat_down.pressed = true;
			return true;
		}
	} else if (evt.type == SDL_KEYUP) {
		if (evt.key.keysym.sym == SDLK_a) {
			left.pressed = false;
			return true;
		} else if (evt.key.keysym.sym == SDLK_d) {
			right.pressed = false;
			return true;
		} else if (evt.key.keysym.sym == SDLK_w) {
			up.pressed = false;
			return true;
		} else if (evt.key.keysym.sym == SDLK_s) {
			down.pressed = false;
			return true;
		}
		else if (evt.key.keysym.sym == SDLK_LEFT) {
			rat_left.pressed = false;
			return true;
		}
		else if (evt.key.keysym.sym == SDLK_RIGHT) {

			rat_right.pressed = false;
			return true;
		}
		else if (evt.key.keysym.sym == SDLK_UP) {

			rat_up.pressed = false;
			return true;
		}
		else if (evt.key.keysym.sym == SDLK_DOWN) {

			rat_down.pressed = false;
			return true;
		}
	} else if (evt.type == SDL_MOUSEBUTTONDOWN) {
		if (SDL_GetRelativeMouseMode() == SDL_FALSE) {
			SDL_SetRelativeMouseMode(SDL_TRUE);
			return true;
		}
	} else if (evt.type == SDL_MOUSEMOTION) {
		if (SDL_GetRelativeMouseMode() == SDL_TRUE) {
			glm::vec2 motion = glm::vec2(
				evt.motion.xrel / float(window_size.y),
				-evt.motion.yrel / float(window_size.y)
			);
			camera->transform->rotation = glm::normalize(
				camera->transform->rotation
				* glm::angleAxis(-motion.x * camera->fovy, glm::vec3(0.0f, 1.0f, 0.0f))
				* glm::angleAxis(motion.y * camera->fovy, glm::vec3(1.0f, 0.0f, 0.0f))
			);
			return true;
		}
	}

	return false;
}

void PlayMode::update(float elapsed) {


	//slowly change carrot positions
	//Control Carrot Movement

	float cur_hieght = (scene_transforms[1])->position.y;
	(scene_transforms[1])->position += carrot_move;

	//std::cout<< cur_hieght << std::endl;

	if (cur_hieght >= 3.0f && isGoingUp){
		isGoingUp = false;
		carrot_move = down_velocity;
		
	}
	else if (cur_hieght <= -5.0f){
		isGoingUp = true;
		carrot_move = up_velocity;
	}

	//move water oppossum:
	constexpr float RatSpeed = 30.0f;
	glm::vec2 RatMove = glm::vec2(0.0f);
	if (rat_left.pressed && !rat_right.pressed) RatMove.x = 1.0f;
	if (!rat_left.pressed && rat_right.pressed) RatMove.x =-1.0f;
	if (rat_down.pressed && !rat_up.pressed) RatMove.y = 1.0f;
	if (!rat_down.pressed && rat_up.pressed) RatMove.y =-1.0f;

	if (RatMove != glm::vec2(0.0f)) RatMove = glm::normalize(RatMove) * RatSpeed * elapsed;
	
	glm::vec3 face_right = glm::vec3(1.0f, 0.0f, 0.0f);
	glm::vec3 face_forward = glm::vec3(0.0f, 1.0f, 0.0f);

	(scene_transforms[0])->position += RatMove.x * face_right + RatMove.y * face_forward;

	rat_col = (scene_transforms[0])->position + pos_offset;
	//std::cout<< (scene_transforms[0])->position.x << "nnnn"<<(scene_transforms[0])->position.y << std::endl;
	//std::cout<< (scene_transforms[1])->position.x << "nnnn"<<(scene_transforms[1])->position.z << std::endl;

	float dis = pow((scene_transforms[1])->position.x - rat_col.x,2) + pow((scene_transforms[1])->position.z - rat_col.y,2);
	
	std::cout << dis << std::endl;
	if ( dis <= pow(5,2)) {
		std::cout<< "eat!" << std::endl;
		for (auto itr = scene.drawables.begin(); itr != scene.drawables.end(); itr++) {
			std::string name = itr->transform->name;
			if (objects[1] == name) {
				scene.drawables.erase(itr);
			}
		}

		scene_transforms.erase(scene_transforms.begin()+1);
		objects.erase(objects.begin()+1);


		return;
	}

	//move camera:
	{

		//combine inputs into a move:
		constexpr float PlayerSpeed = 30.0f;
		glm::vec2 move = glm::vec2(0.0f);
		if (left.pressed && !right.pressed) move.x =-1.0f;
		if (!left.pressed && right.pressed) move.x = 1.0f;
		if (down.pressed && !up.pressed) move.y =-1.0f;
		if (!down.pressed && up.pressed) move.y = 1.0f;

		//make it so that moving diagonally doesn't go faster:
		if (move != glm::vec2(0.0f)) move = glm::normalize(move) * PlayerSpeed * elapsed;

		glm::mat4x3 frame = camera->transform->make_local_to_parent();
		glm::vec3 right = frame[0];
		//glm::vec3 up = frame[1];
		glm::vec3 forward = -frame[2];

		camera->transform->position += move.x * right + move.y * forward;
	}

	//reset button press counters:
	left.downs = 0;
	right.downs = 0;
	up.downs = 0;
	down.downs = 0;

	rat_left.downs = 0;
	rat_right.downs = 0;
	rat_up.downs = 0;
	rat_down.downs = 0;
}

void PlayMode::draw(glm::uvec2 const &drawable_size) {
	//update camera aspect ratio for drawable:
	camera->aspect = float(drawable_size.x) / float(drawable_size.y);

	//set up light type and position for lit_color_texture_program:
	// TODO: consider using the Light(s) in the scene to do this
	glUseProgram(lit_color_texture_program->program);
	glUniform1i(lit_color_texture_program->LIGHT_TYPE_int, 1);
	glUniform3fv(lit_color_texture_program->LIGHT_DIRECTION_vec3, 1, glm::value_ptr(glm::vec3(0.0f, 0.0f,-1.0f)));
	glUniform3fv(lit_color_texture_program->LIGHT_ENERGY_vec3, 1, glm::value_ptr(glm::vec3(1.0f, 1.0f, 0.95f)));
	glUseProgram(0);

	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	glClearDepth(1.0f); //1.0 is actually the default value to clear the depth buffer to, but FYI you can change it.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS); //this is the default depth comparison function, but FYI you can change it.

	GL_ERRORS(); //print any errors produced by this setup code

	scene.draw(*camera);

	{ //use DrawLines to overlay some text:
		glDisable(GL_DEPTH_TEST);
		float aspect = float(drawable_size.x) / float(drawable_size.y);
		DrawLines lines(glm::mat4(
			1.0f / aspect, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		));

		constexpr float H = 0.09f;
		lines.draw_text("Mouse rotates camera; WASD moves; escape ungrabs mouse; Arrows control water opossum to eat the carrot!",
			glm::vec3(-aspect + 0.1f * H, -1.0 + 0.1f * H, 0.0),
			glm::vec3(H, 0.0f, 0.0f), glm::vec3(0.0f, H, 0.0f),
			glm::u8vec4(0x00, 0x00, 0x00, 0x00));
		float ofs = 2.0f / drawable_size.y;
		lines.draw_text("Mouse rotates camera; WASD moves; escape ungrabs mouse; Arrows control water opossum to eat the carrot!",
			glm::vec3(-aspect + 0.1f * H + ofs, -1.0 + + 0.1f * H + ofs, 0.0),
			glm::vec3(H, 0.0f, 0.0f), glm::vec3(0.0f, H, 0.0f),
			glm::u8vec4(0xff, 0xff, 0xff, 0x00));
	}
}
