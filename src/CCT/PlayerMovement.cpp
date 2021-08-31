#include "PlayerMovement.h"

PlayerMovement::PlayerMovement()
{
	speed = 0.05;
	oldInput = vec2(0);
}

void PlayerMovement::checkKeys(int key, int action)
{
	if (action == GLFW_PRESS)
	{
		keys[key] = true;
		if (key == GLFW_KEY_S || key == GLFW_KEY_W)
		{
			newestInput[0] = key;
		}
		else if (key == GLFW_KEY_A || key == GLFW_KEY_D)
		{
			newestInput[1] = key;
		}
	}
	else if (action == GLFW_RELEASE)
	{
		keys[key] = false;

	}
}


void PlayerMovement::doMovement(float dt)
{
	vec3 movement(0);
	//smooth axis
	vec2 axis = getInputAxis(dt);
	//minus here because of left-Handed Coordinate Systems
	movement = vec3(-axis.x, 0, axis.y);
	//cout << "input is:" << axis.x << " and " << axis.y << endl;
	player->move(movement* speed, dt);
}

vec2 PlayerMovement::getInputAxis(float dt)
{
	float accelerationSpeed = 10;


	if (keys[GLFW_KEY_W] && (newestInput[0] == GLFW_KEY_W || keys[GLFW_KEY_W] != keys[GLFW_KEY_S]))
	{
		if (oldInput.y < 1)
		{
			oldInput.y += 1 * dt * accelerationSpeed;
			if (oldInput.y > 1)
			{
				oldInput.y = 1;
			}
		}
	}
	else
	{
		if (oldInput.y > 0)
		{
			oldInput.y -= 1 * dt * accelerationSpeed;
			if (oldInput.y < 0)
			{
				oldInput.y = 0;
			}
		}
	}
	if (keys[GLFW_KEY_S] && (newestInput[0] == GLFW_KEY_S || keys[GLFW_KEY_S] != keys[GLFW_KEY_W]))
	{
		if (oldInput.y > -1)
		{
			oldInput.y -= 1 * dt * accelerationSpeed;
			if (oldInput.y < -1)
			{
				oldInput.y = -1;
			}
		}
	}
	else
	{
		if (oldInput.y < 0)
		{
			oldInput.y += 1 * dt * accelerationSpeed;
			if (oldInput.y > 0)
			{
				oldInput.y = 0;
			}
		}
	}

	if (keys[GLFW_KEY_D] && (newestInput[1] == GLFW_KEY_D || keys[GLFW_KEY_D] != keys[GLFW_KEY_A]))
	{
		if (oldInput.x < 1)
		{
			oldInput.x += 1 * dt * accelerationSpeed;
			if (oldInput.x > 1)
			{
				oldInput.x = 1;
			}
		}
	}
	else
	{
		if (oldInput.x > 0)
		{
			oldInput.x -= 1 * dt * accelerationSpeed;
			if (oldInput.x < 0)
			{
				oldInput.x = 0;
			}
		}
	}
	if (keys[GLFW_KEY_A] && (newestInput[1] == GLFW_KEY_A || keys[GLFW_KEY_A] != keys[GLFW_KEY_D]))
	{
		if (oldInput.x > -1)
		{
			oldInput.x -= 1 * dt * accelerationSpeed;
			if (oldInput.x < -1)
			{
				oldInput.x = -1;
			}
		}
	}
	else
	{
		if (oldInput.x < 0)
		{
			oldInput.x += 1 * dt * accelerationSpeed;
			if (oldInput.x > 0)
			{
				oldInput.x = 0;
			}
		}
	}


	if (glm::sqrt(oldInput.x * oldInput.x + oldInput.y *oldInput.y)>= 1)
	{
		vec2 normalazedInput = glm::normalize(oldInput);
		//cout << normalazedInput.x << " and " << normalazedInput.y << endl;
		return normalazedInput;
	}
	return oldInput;
	return vec2();

}

vec2 PlayerMovement::getInput()
{
	return vec2();
}
