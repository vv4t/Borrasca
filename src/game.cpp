#include "game.hpp"

#include "mesh.hpp"
#include "vertex.hpp"
#include "shader.hpp"
#include "core_engine.hpp"
#include "render_engine.hpp"
#include "uniform_buffer.hpp"
#include "assetlib.hpp"
#include "math3d.hpp"
#include "input.hpp"
#include "transform.hpp"
#include "camera.hpp"
#include "sprite_render.hpp"
#include "character_controller.hpp"
#include "terrain_component.hpp"
#include "bat_component.hpp"
#include "ghost_component.hpp"
#include "shadow_map.hpp"
#include "terrain_collider.hpp"
#include "rigid_body.hpp"
#include "particle_system.hpp"
#include "entity_type.hpp"
#include "circle_collider.hpp"
#include "item.hpp"
#include "torch_item.hpp"
#include "net_item.hpp"
#include "flare_gun_item.hpp"
#include "flashlight_component.hpp"
#include "pickaxe_item.hpp"
#include "trail_particle.hpp"
#include "health.hpp"
#include "player_gui.hpp"
#include "golem_component.hpp"
#include "director.hpp"
#include "window.hpp"
#include "menu_component.hpp"
#include "crate_component.hpp"

#define WIDTH 800
#define HEIGHT 600

game::game() {
	win = new loli::window(WIDTH, HEIGHT, "Borrasca");
	loli::input::init(win);
	assetlib = loli::assetlib();
	engine = new loli::core_engine(win);
	render = &engine->get_render_engine();
}

game::~game() {
	// clean();
	// delete win;
}

void game::init_menu() {
	// float tex = 1.0 / 16.0;
	
	// loli::vertex vertices[4] = {
		// loli::vertex(loli::vec3(-0.5f, -0.5f,  0.5f), loli::vec3(0, 0, 1), loli::vec2(0.0f , 1)),	 //front bottom left	0
		// loli::vertex(loli::vec3( 0.5f, -0.5f,  0.5f), loli::vec3(0, 0, 1), loli::vec2(1, 1)),	 //front bottom right	1
		// loli::vertex(loli::vec3(-0.5f,  0.5f,  0.5f), loli::vec3(0, 0, 1), loli::vec2(0.0f , 0.0f )),//front top left		2
		// loli::vertex(loli::vec3( 0.5f,  0.5f,  0.5f), loli::vec3(0, 0, 1), loli::vec2(1, 0.0f )),	 //front top right		3
	// };
	
	// unsigned int indices[6] = {
		// 0, 1, 2,
		// 1, 2, 3
	// };
	
	// render->add_mesh()->init(&vertices[0], 4).index(&indices[0], 6);
	// render->add_shader(assetlib.load_file("assets/shader/shader.vs"), assetlib.load_file("assets/shader/shader.fs"));
	// render->add_shader(assetlib.load_file("assets/shader/shadow.vs"), assetlib.load_file("assets/shader/shadow.fs"));
	// render->add_shader(assetlib.load_file("assets/shader/gui.vs"), assetlib.load_file("assets/shader/gui.fs"));
	// float ar = (float) WIDTH / (float) HEIGHT;
	
	// render->add_texture(assetlib.load_bitmap("assets/sprite/start.png"));
	// render->bind_texture(0, 0);
	// render->bind_shader(2);
	// render->get_shader()->uniform_int("u_sampler", 0);
	
	// loli::entity* e = engine->add_entity();
	// e->add_component(new menu_component(this));
	
	// engine->start();
	// engine->run();
}

void game::init() {
	std::cout << sizeof(crate_component) << std::endl;

}

void game::init_game() {
	
	float tex = 1.0 / 16.0;
	
	loli::vertex vertices[4] = {
		loli::vertex(loli::vec3(-0.5f, -0.5f,  0.5f), loli::vec3(0, 0, 1), loli::vec2(0.0f , tex)),	 //front bottom left	0
		loli::vertex(loli::vec3( 0.5f, -0.5f,  0.5f), loli::vec3(0, 0, 1), loli::vec2(tex, tex)),	 //front bottom right	1
		loli::vertex(loli::vec3(-0.5f,  0.5f,  0.5f), loli::vec3(0, 0, 1), loli::vec2(0.0f , 0.0f )),//front top left		2
		loli::vertex(loli::vec3( 0.5f,  0.5f,  0.5f), loli::vec3(0, 0, 1), loli::vec2(tex, 0.0f )),	 //front top right		3
	};
	
	unsigned int indices[6] = {
		0, 1, 2,
		1, 2, 3
	};
	
	
	float ar = (float) WIDTH / (float) HEIGHT;
	
	render->get_cam().set_projection(loli::mat4().isometric(-5.0f * ar, 5.0f * ar, 5.0f, -5.0f, -5.0f * ar, 5.0f * ar));
	
	render->add_mesh()->init(&vertices[0], 4).index(&indices[0], 6);
	render->add_shader(assetlib.load_file("assets/shader/shader.vs"), assetlib.load_file("assets/shader/shader.fs"));
	render->add_shader(assetlib.load_file("assets/shader/shadow.vs"), assetlib.load_file("assets/shader/shadow.fs"));
	render->add_shader(assetlib.load_file("assets/shader/gui.vs"), assetlib.load_file("assets/shader/gui.fs"));
	render->add_texture(assetlib.load_bitmap("assets/sprite/spritemap.png"));
	render->add_texture(assetlib.load_bitmap("assets/sprite/inventory.png"));
	render->add_texture(assetlib.load_bitmap("assets/sprite/gameover.png"));
	
	render->bind_shader(0);
	render->get_light().add_light(loli::vec3(5.0, 5.0, 0.0), loli::vec3(1.0, 1.0, 0.7), 7.0, 0.0, 0.5);
	render->get_light().add_light(loli::vec3(5.0, 5.0, 0.0), loli::vec3(1.0, 0.8, 0.6), 5.0, 0.0, M_PI * 2);
	
	render->get_light().get_light(0)->enable_shadow(true);
	render->get_light().get_light(1)->enable_shadow(true);
	loli::entity* terrain = engine->add_entity();
	terrain->add_component(new shadow_map());
	terrain->add_component(new terrain_component());
	terrain->set_type(ENTITY_TERRAIN);
	
	loli::entity* collision = engine->add_entity();
	collision->add_component(new collision_engine());
	
	loli::entity* player = engine->add_entity();
	player->add_component(new rigid_body());
	player->add_component(new character_controller());
	player->add_component(new sprite_render());
	player->add_component(new terrain_collider());
	player->add_component(new circle_collider(0.5));
	player->add_component(new health(100, 100));
	player->add_component(new player_gui);
	player->set_type(ENTITY_PLAYER);
	
	loli::entity* player_item = engine->add_entity();
	player_item->add_component(new sprite_render());
	player_item->add_component(new item_component());
	player_item->get_component<item_component*>(1)->add_item(new torch_item());
	player_item->get_component<item_component*>(1)->add_item(new net_item());
	player_item->get_component<item_component*>(1)->add_item(new flare_gun_item());
	player_item->get_component<item_component*>(1)->add_item(new pickaxe_item());
	
	loli::entity* flashlight = engine->add_entity();
	flashlight->add_component(new rigid_body());
	flashlight->add_component(new flashlight_component());
	flashlight->add_component(new circle_collider(0.25));
	flashlight->set_type(ENTITY_FLASHLIGHT);
	
	player_item->get_component<item_component*>(1)->equip(0);
	
	loli::entity* d = engine->add_entity();
	d->add_component(new director());
	director* _director = d->get_component<director*>(0);
	engine->start();
	terrain->get_component<terrain_component*>(1)->load_map(assetlib.load_bitmap("assets/level/level1.png"));
	
	render->get_shader()->uniform_int("u_sampler", 0);
	render->get_shader()->uniform_int("u_depth", 1);
	render->bind_texture(0, 0);
	
	engine->run();
}

void game::clean() {
	// delete engine;
	
	// engine = new loli::core_engine(win);
}