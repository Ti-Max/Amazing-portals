#include "Camera.h"
Camera::Camera()
{
}

Camera::Camera(glm::vec3 pos)
{
	this->pos = pos;
}

void Camera::checkKeys(int key, int action)
{
	key = key == GLFW_KEY_W ? 0 : key == GLFW_KEY_A ? 1 : key == GLFW_KEY_S ? 2 : key == GLFW_KEY_D ? 3 : key == GLFW_KEY_LEFT_SHIFT ? 4 : key == GLFW_KEY_SPACE? 5 : 6;
	if (action == GLFW_PRESS)
		keys[key] = true;
	else if(action == GLFW_RELEASE)
		keys[key] = false;
}

void Camera::checkMouse(float xpos, float ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	float sensitivity = 0.05;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	this->front = glm::normalize(front);
	
}

void Camera::checkScroll(float yoffset)
{
	if (fov >= 1.0f && fov <= 90.0f)
		fov -= yoffset;
	if (fov <= 1.0f)
		fov = 1.0f;
	if (fov >= 90.0f)
		fov = 90.0f;
}

float O;
float Fi;
void Camera::do_movement()
{
	//std::cout << std::fixed;
	//std::cout.precision(0);
	
	/*float currentTime = glfwGetTime();
	float deltaTime = currentTime - lastTime;
	lastTime = currentTime;

	float speed = this->speed * deltaTime;
	if (keys[KEY_CONTROL] || movingAfterCtrl) {
		speed *= 2;
		movingAfterCtrl = true;
	}
	int disableNum = 0;

	if (keys[KEY_UP])
		pos += glm::vec3(speed * cos(glm::radians(yaw)), 0.0f, speed * sin(glm::radians(yaw)));
	else
		disableNum++;
	if (keys[KEY_DOWN])
		pos -= glm::vec3(speed * cos(glm::radians(yaw)), 0.0f, speed * sin(glm::radians(yaw)));
	else
		disableNum++;
	if (keys[KEY_LEFT])
		pos -= glm::normalize(glm::cross(front, up)) * speed;
	else
		disableNum++;
	if (keys[KEY_RIGHT])
		pos += glm::normalize(glm::cross(front, up)) * speed;
	else
		disableNum++;

	if (keys[KEY_SHIFT])
		pos.y -= speed;
	if (keys[KEY_SPACE])
		pos.y += speed; 

	if (disableNum == 4)
		movingAfterCtrl = false;*/

	//distance from the camera
	vec3 offset = vec3(0, 0, 4);
	//freelook Rotation around the player
	quat xRot = angleAxis( radians(yaw), vec3(0,-1,0));
	quat yRot = angleAxis(radians(pitch), vec3(1, 0, 0));

	quat rotation = xRot * yRot;
	offset = rotation * offset;
	pos = offset + followedTransform->p;
	//cout << "YAW: " << yaw << endl;
}

glm::mat4 Camera::getViewMat()
{
	glm::mat4 view(1.0f);
	view = glm::lookAt(pos, followedTransform->p , up);
	return  view;
}

glm::mat4 Camera::getReflectionViewMat(glm::vec3 mPos, glm::vec3 n)
{
	glm::mat4 view(1.0f);

	glm::vec3 cV(mPos - pos);
	distans = glm::length(cV);
	glm::vec3 R(glm::normalize(glm::reflect(glm::normalize(cV), n)));

	glm::vec3 RR(R * glm::vec3(-1));
	glm::vec3 mToRC(RR*distans);

	glm::vec3 RcPos(mPos + mToRC);
	glm::vec3 frontReflect(glm::reflect(front, n));
	view = glm::lookAt(RcPos, RcPos + frontReflect, up);


	return view;
}

glm::mat4 Camera::getPortalViewMat(glm::vec3 p1Pos, glm::vec3 p2Pos, glm::mat3 m1, glm::mat3 m2/*, glm::mat4 camM*/)
{
	
	//glm::vec4 camPos = glm::column(camM, 3);
	//Поворот для того, чтобы мы смотрели через портал в направлении нормали
	glm::mat3 toSecPortalSpace = glm::rotate(glm::mat4(glm::inverse(m2) * m1), glm::radians(180.0f), glm::vec3(0, 1, 0));
	//toSecPortalSpace
	glm::vec3 toCam = pos - p1Pos;
	glm::vec3 toCam2 = toSecPortalSpace * toCam;

	glm::vec3 cam2Pos = p2Pos + toCam2;
	glm::vec3 front2 = toSecPortalSpace * front;
	posSecCam = cam2Pos;
	glm::mat4 view(1.0f);
	view = glm::lookAt(cam2Pos, cam2Pos + front2, up);
	return view;
}

inline float sgn(float x)
{
	if (x > 0.0F) return (1.0F);
	if (x < 0.0F) return (-1.0F);
	return (0.0F);
}
glm::mat4 Camera::getProjectionClipMat(glm::vec4 clipPlane)
{
	glm::mat4 matrixProjection = glm::perspective(glm::radians(fov), (float)1280 / (float)720, 0.1f, 100.0f);
	float* R = glm::value_ptr(matrixProjection);

	glm::vec4 vcamera;
	vcamera.x = (sgn(clipPlane.x) - R[8]) / R[0];
	vcamera.y = (sgn(clipPlane.y) - R[9]) / R[5];
	vcamera.z = 1.0F;
	vcamera.w = R[10] / R[14];

	float m = -1.0f / glm::dot(clipPlane, vcamera);
	R[2] = m * clipPlane.x;
	R[6] = m * clipPlane.y;
	R[10] = m * clipPlane.z + 1.0F;
	R[14] = m * clipPlane.w;

	glm::mat4 mat = glm::make_mat4x4(R);
	return mat;
}

void Camera::setFolowedTransform(Transform* trans, vec3 offset)
{
	followedTransform = trans;
	cameraoffset = offset;
}
