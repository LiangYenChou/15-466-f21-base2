#include "Mode.hpp"

#include "Scene.hpp"

#include <glm/glm.hpp>

#include <vector>
#include <deque>

struct PlayMode : Mode {
	PlayMode();
	virtual ~PlayMode();

	//functions called by main loop:
	virtual bool handle_event(SDL_Event const &, glm::uvec2 const &window_size) override;
	virtual void update(float elapsed) override;
	virtual void draw(glm::uvec2 const &drawable_size) override;

	//----- game state -----

	//input tracking:
	struct Button {
		uint8_t downs = 0;
		uint8_t pressed = 0;
	} left, right, down, up, rat_left, rat_right, rat_up, rat_down;

	//local copy of the game scene (so code can change it during gameplay):
	Scene scene;
	std::vector<std::string> objects = {};

	//hexapod leg to wobble:
	Scene::Transform *hip = nullptr;
	Scene::Transform *upper_leg = nullptr;
	Scene::Transform *lower_leg = nullptr;
	glm::quat hip_base_rotation;
	glm::quat upper_leg_base_rotation;
	glm::quat lower_leg_base_rotation;
	float wobble = 0.0f;

	//garden items
	Scene::Transform *rat = nullptr;
	Scene::Transform *carrot001 = nullptr;
	Scene::Transform *carrot002 = nullptr;
	Scene::Transform *carrot003 = nullptr;
	Scene::Transform *carrot004 = nullptr;
	Scene::Transform *carrot005 = nullptr;
	Scene::Transform *carrot006 = nullptr;
	Scene::Transform *carrot007 = nullptr;
	Scene::Transform *carrot008 = nullptr;
	Scene::Transform *carrot009 = nullptr;
	Scene::Transform *carrot010 = nullptr;
	Scene::Transform *carrot011 = nullptr;
	Scene::Transform *carrot012 = nullptr;
	Scene::Transform *carrot013 = nullptr;
	Scene::Transform *carrot014 = nullptr;
	Scene::Transform *carrot015 = nullptr;
	Scene::Transform *carrot016 = nullptr;
	Scene::Transform *carrot017 = nullptr;
	Scene::Transform *carrot018 = nullptr;
	Scene::Transform *carrot019 = nullptr;
	Scene::Transform *carrot020 = nullptr;
	Scene::Transform *carrot021 = nullptr;
	Scene::Transform *carrot022 = nullptr;
	Scene::Transform *carrot023 = nullptr;
	Scene::Transform *carrot024 = nullptr;
	Scene::Transform *carrot025 = nullptr;
	Scene::Transform *carrot026 = nullptr;
	Scene::Transform *carrot027 = nullptr;
	Scene::Transform *ground = nullptr;
	// glm::quat bacon_base_rotation;
	// glm::quat cake_base_rotation;
	// glm::quat sandwich_base_rotation;
	// glm::vec3 bacon_base_position;
	// glm::vec3 cake_base_position;
	// glm::vec3 sandwich_base_position;
	// glm::vec3 cactus_base_position;
	// glm::vec3 egg_base_position;
	// glm::vec3 pancakes_base_position;
	std::vector<Scene::Transform*> scene_transforms;
	std::vector<glm::vec3> scene_base_positions;
	glm::vec3 table_base_position;


	glm::vec3 up_velocity = glm::vec3(0.0f, 0.1f, 0.0f);
	glm::vec3 down_velocity = glm::vec3(0.0f, -0.1f, 0.0f);
	glm::vec3 carrot_move = up_velocity;
	glm::vec3 pos_offset;
	glm::vec3 rat_col;
	bool isGoingUp = true;

	
	//camera:
	Scene::Camera *camera = nullptr;

};
