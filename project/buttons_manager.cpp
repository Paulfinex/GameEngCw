#include "components/cmp_sprite.h"
#include "system_renderer.h"
#include "system_resources.h"

using namespace std;
using namespace sf;

bool IsSelected(shared_ptr<Entity> button, Vector2f mousePos)
{
	if (button->get_components<ShapeComponent>()[0]->getShape().getGlobalBounds().contains(mousePos))
	{
		button->get_components<ShapeComponent>()[0]->getShape().setFillColor(Color(116, 80, 67));
		return true;
	}
	else
	{
		button->get_components<ShapeComponent>()[0]->getShape().setFillColor(Color(116, 63, 67, 100));
		return false;
	}
}

bool ButtonHandling(shared_ptr<Entity> button, Vector2f mousePos)
{
	return IsSelected(button, mousePos) && Mouse::isButtonPressed(Mouse::Left);
}