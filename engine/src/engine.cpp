#include "engine.h"
#include "maths.h"
#include "system_physics.h"
#include "system_renderer.h"
#include "system_resources.h"
#include <SFML/Graphics.hpp>
#include <future>
#include <iostream>
#include <stdexcept>
#include <map>


using namespace sf;
using namespace std;
Scene* Engine::_activeScene = nullptr;
std::string Engine::_gameName;
std::string Engine::lastKeyPressed = "";
static bool loading = false;
static float loadingspinner = 0.f;
static float loadingTime;
bool switchModeCheck = true;
bool _windowed = false;
bool _fullscreen = false;
static RenderWindow* _window;
std::string Engine::_currRes = "1920x1080";
bool Engine::_resolutionChange = false;


const std::map<std::string, pair<int, int>> Engine::RESOLUTION
{
	{"1920x1080", make_pair(1920, 1080)},
	{"1920x1200", make_pair(1920, 1200)},
	{"1680x1050", make_pair(1680, 1050)},
	{"1440x900", make_pair(1440, 900)},
	{"1366x768", make_pair(1366, 768)},
	{"1280x800", make_pair(1280, 800)},
	{"800x600", make_pair(800, 600)},
	{"640x480", make_pair(640, 480)}
};

void Loading_update(float dt, const Scene* const scn) {
	//  cout << "Eng: Loading Screen\n";
	if (scn->isLoaded()) {
		cout << "Eng: Exiting Loading Screen\n";
		loading = false;
	}
	else {
		loadingspinner += 220.0f * dt;
		loadingTime += dt;
	}
}
void Loading_render() {
	// cout << "Eng: Loading Screen Render\n";
	static CircleShape octagon(80, 8);
	octagon.setOrigin(80, 80);
	octagon.setRotation(loadingspinner);
	octagon.setPosition(Vcast<float>(Engine::getWindowSize()) * .5f);
	octagon.setFillColor(Color(255, 255, 255, min(255.f, 40.f*loadingTime)));
	static Text t("Loading", *Resources::get<sf::Font>("RobotoMono-Regular.ttf"));
	t.setFillColor(Color(255, 255, 255, min(255.f, 40.f*loadingTime)));
	t.setPosition(Vcast<float>(Engine::getWindowSize()) * Vector2f(0.4f, 0.3f));
	Renderer::queue(&t);
	Renderer::queue(&octagon);
}

float frametimes[256] = {};
uint8_t ftc = 0;

void Engine::Update() {
	static sf::Clock clock;
	float dt = clock.restart().asSeconds();
	{
		frametimes[++ftc] = dt;
		static string avg = _gameName + " FPS:";
		if (ftc % 60 == 0) {
			double davg = 0;
			for (const auto t : frametimes) {
				davg += t;
			}
			davg = 1.0 / (davg / 255.0);
			_window->setTitle(avg + toStrDecPt(2, davg));
		}
	}

	if (loading) {
		Loading_update(dt, _activeScene);
	}
	else if (_activeScene != nullptr) {
		Physics::update(dt);
		_activeScene->Update(dt);
	}
}

void Engine::Render(RenderWindow& window) {
	if (loading) {
		Loading_render();
	}
	else if (_activeScene != nullptr) {
		_activeScene->Render();
	}

	Renderer::render();
}

void Engine::Start(unsigned int width, unsigned int height,
	const std::string& gameName, Scene* scn) {
	_resolutionChange = false;
	RenderWindow window(VideoMode(width, height), gameName, _windowed ? Style::Titlebar : Style::Fullscreen | Style::Close);
	_gameName = gameName;
	_window = &window;
	Renderer::initialise(window);
	Physics::initialise();
	ChangeScene(scn);

	// Handle resize with letterbox
	sf::View view;
	view.setSize(width, height);
	view.setCenter(view.getSize().x / 2, view.getSize().y / 2);

	while (window.isOpen()) 
	{
		Event event;
		while (window.pollEvent(event)) 
		{
			if (event.type == Event::Closed) 
			{
				window.close();
			}

			if (event.type == sf::Event::TextEntered)
			{
				if (event.text.unicode < 0x80) // it's printable
				{
					lastKeyPressed = (char)event.text.unicode;
				}
			}
		}

		if (Engine::_resolutionChange)
		{
			 window.create(VideoMode(RESOLUTION.at(_currRes).first, RESOLUTION.at(_currRes).second), gameName,
				(Style::Titlebar | Style::Close));
			_window = &window;
			_resolutionChange = false;
		}

		if (Keyboard::isKeyPressed(Keyboard::Escape)) {
			window.close();
		}
		if (_windowed)
		{
			window.create(VideoMode(RESOLUTION.at(_currRes).first, RESOLUTION.at(_currRes).second), gameName, Style::Titlebar | Style::Close);
			_window = &window;
			_windowed = false;
		}
		if (_fullscreen)
		{
			window.create(VideoMode(RESOLUTION.at(_currRes).first, RESOLUTION.at(_currRes).second), gameName, Style::Fullscreen | Style::Close);
			_window = &window;
			_fullscreen = false;
		}

		window.clear();
		Update();
		window.setView(view);
		Render(window);
		window.display();
	}

	if (_activeScene != nullptr) {
		_activeScene->UnLoad();
		_activeScene = nullptr;
	}
	window.close();
	Physics::shutdown();
	// Render::shutdown();
}

std::string Engine::CurrRes()
{
	return _currRes;
}
void Engine::ChangeResolution(string resolution)
{
	_resolutionChange = true;
	_currRes = resolution;
}

void Engine::setVsync(bool b) { _window->setVerticalSyncEnabled(b); }

void Engine::ChangeScene(Scene* s) {
	cout << "Eng: changing scene: " << s << endl;
	auto old = _activeScene;
	_activeScene = s;

	if (old != nullptr) {
		old->UnLoad(); // todo: Unload Async
	}

	if (!s->isLoaded()) {
		cout << "Eng: Entering Loading Screen\n";
		loadingTime = 0;
		_activeScene->LoadAsync();
		loading = true;
	}
}

void Engine::setWindowedMode()
{
	if (!_windowed && switchModeCheck)
	{
		_windowed = true;
		switchModeCheck = false;
	}
	else if (!_fullscreen && !switchModeCheck)
	{
		_fullscreen = true;
		switchModeCheck = true;
	}
}

void Scene::Update(const double& dt) { ents.update(dt); }

void Scene::Render() { ents.render(); }

bool Scene::isLoaded() const {
	{
		std::lock_guard<std::mutex> lck(_loaded_mtx);
		// Are we already loading asynchronously?
		if (_loaded_future.valid() // yes
			&&                     // Has it finished?
			_loaded_future.wait_for(chrono::seconds(0)) ==
			future_status::ready) {
			// Yes
			_loaded_future.get();
			_loaded = true;
		}
		return _loaded;
	}
}
void Scene::setLoaded(bool b) {
	{
		std::lock_guard<std::mutex> lck(_loaded_mtx);
		_loaded = b;
	}
}

void Scene::UnLoad() {
	ents.list.clear();
	setLoaded(false);
}

void Scene::LoadAsync() { _loaded_future = std::async(&Scene::Load, this); }

sf::Vector2u Engine::getWindowSize() { return _window->getSize(); } 

sf::RenderWindow& Engine::GetWindow() { return *_window; }

namespace timing {
	// Return time since Epoc
	long long now() {
		return std::chrono::high_resolution_clock::now()
			.time_since_epoch()
			.count();
	}
	// Return time since last() was last called.
	long long last() {
		auto n = now();
		static auto then = now();
		auto dt = n - then;
		then = n;
		return dt;
	}
} // namespace timing


std::shared_ptr<Entity> Scene::makeEntity() {
	auto e = make_shared<Entity>(this);
	ents.list.push_back(e);
	return std::move(e);
}

Scene* Engine::GetActiveScene()
{
	return _activeScene;
}

Scene::~Scene() { UnLoad(); }