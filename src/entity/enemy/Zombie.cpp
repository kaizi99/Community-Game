#include "Zombie.h"

#include "../../Application.h"
#include "../../level/Level.h"
#include "../Player.h"
#include "../../util/Maths.h"

namespace Framework
{
	Zombie::Zombie()
	{
		sprite = sf::Sprite(Application::instance->getResources().textures.get("player_modelDefault"), sf::IntRect(0, 0, 32, 64));

		m_animator.addAnim("idle", 0, 0, 32, 8, 7);
		m_animator.addAnim("run", 0, 64, 32, 8, 14);
		m_animator.setAnim("idle");
		m_speedWalk = 60;

		constexpr static uint health = 400;
		auto hb = std::make_shared<HealthBoost>(DURATION_INFINITE, health, 0);
		addEffect(hb);

		m_health = health;
	}

	void Zombie::update(const Timestep& ts)
	{
		Creature::update(ts);

		float dx = level->player->position.x - position.x;
		float dy = level->player->position.y - position.y;
		float theta = atan2(dy, dx);

		float angle = toDegrees(theta);

		int xdir = 0;
		int ydir = 0;

		if (angle > -135 && angle < -45)
			ydir--; //UP
		if (angle < 135 && angle > 45)
			ydir++; //DOWN
		if (angle > 135 || angle < -135)
			xdir--; //LEFT
		if (angle > -45 && angle < 45)
			xdir++; //RIGHT

		if (xdir > 0)
		{
			if (ydir > 0)
				walk(DOWN_RIGHT);
			else if (ydir < 0)
				walk(UP_RIGHT);
			else
				walk(RIGHT);
			m_direction = true;
		}
		else if (xdir < 0)
		{
			if (ydir > 0)
				walk(DOWN_LEFT);
			else if (ydir < 0)
				walk(UP_LEFT);
			else
				walk(LEFT);
			m_direction = false;
		}
		else
		{
			if (ydir > 0)
				walk(DOWN);
			else if (ydir < 0)
				walk(UP);
		}

		applyVelocity(ts.asSeconds());
		m_animator.setAnim(m_walking ? "run" : "idle");
	}
}