#include "Portal.h"

Portal::Portal()
{
	initialNormal = vec3(0, 0, 1);
	nonColorShader = new Shader("portal");
}

Portal::~Portal()
{
	delete nonColorShader;
}

void Portal::renderInsides(glm::mat4& projection, glm::mat4& view, int maxLevelRecursion, Scene* scene, float fov)
{
	this->fov = fov;
	drawRecursive(projection, view, maxLevelRecursion, 0, scene);
}

void Portal::attachPortal(Portal* p)
{
	secPortal = p;
}

void Portal::setMeshes(Meshes* m)
{
	meshes = m;
}

mat4 Portal::getMat3()
{
	mat4 m = mat3((transform.getMatix()));
	return m;
}

vec3 Portal::getNormal()
{
	normal = transform.q * initialNormal;
	return normal;
}

glm::vec3 Portal::getIitialNormal()
{
	return initialNormal;
}

void Portal::drawRecursive(glm::mat4& projection, glm::mat4& view, int maxLevelRecursion, int levelRecursion, Scene* scene)
{
	glm::mat4 model2;
	model2 = glm::translate(this->getTransform().getMatix(), glm::vec3(0, 0, -0.01));
	model2 = glm::scale(model2, glm::vec3(3, 6, 0.02));

	//Настройка трафарета
	glDepthMask(GL_FALSE);
	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
	glEnable(GL_STENCIL_TEST);

	glStencilFunc(GL_EQUAL, levelRecursion, 0xFF);
	glStencilOp(GL_KEEP, GL_KEEP, GL_INCR);
	glStencilMask(0xff);

	//рисуем трафрарет
	nonColorShader->use();
	nonColorShader->setMat4("projection", projection);
	nonColorShader->setMat4("view", view);
	//Рисуем как узкий куб что бы у камеры есть near clip plane
	nonColorShader->setMat4("model", model2);
	(*meshes)["cubeNotTexture"]->draw();
	//================================================================================
	//Рисуем сцену в портале
	glm::mat4 secView = getPotalView(this->getTransform().getMatix(), secPortal->getTransform().getMatix(), view);
	glm::mat4 secProj = getPotalProjection(secPortal->getTransform().getMatix(), secView);
	if (levelRecursion == maxLevelRecursion)
	{
		glEnable(GL_DEPTH_TEST);
		glDepthMask(GL_TRUE);
		glClear(GL_DEPTH_BUFFER_BIT);
		glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
		glEnable(GL_STENCIL_TEST);

		glStencilFunc(GL_EQUAL, levelRecursion + 1, 0xFF);
		glStencilMask(0x00);

		scene->drawNonPortals(secProj, secView);
	}
	else
	{
		drawRecursive(secProj, secView, maxLevelRecursion, levelRecursion + 1, scene);
	}

	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
	glDepthMask(GL_FALSE);
	glEnable(GL_STENCIL_TEST);
	glStencilMask(0xFF);
	glStencilFunc(GL_NOTEQUAL, levelRecursion + 1, 0xFF);
	glStencilOp(GL_DECR, GL_KEEP, GL_KEEP);
	nonColorShader->use();
	nonColorShader->setMat4("projection", projection);
	nonColorShader->setMat4("view", view);
	nonColorShader->setMat4("model", model2);
	(*meshes)["cubeNotTexture"]->draw();

	//==============================================
	glDisable(GL_STENCIL_TEST);
	glStencilMask(0x00);
	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);

	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	//glDepthFunc(GL_ALWAYS);
	glClear(GL_DEPTH_BUFFER_BIT);

	nonColorShader->use();
	nonColorShader->setMat4("projection", projection);
	nonColorShader->setMat4("view", view);
	nonColorShader->setMat4("model", model2);
	(*meshes)["cubeNotTexture"]->draw();

	//glDepthFunc(GL_LESS);
	//===================================================
	//Все остальное

	if (levelRecursion != 0)
	{
		glEnable(GL_STENCIL_TEST);
		glStencilMask(0x00);

		glStencilFunc(GL_LEQUAL, levelRecursion, 0xFF);

		glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
		glEnable(GL_DEPTH_TEST);
		glDepthMask(GL_TRUE);
		scene->drawNonPortals(projection, view);
	}
	//		shaders["standart_s"].use();
	//		shaders["standart_s"].setMat4("projection", projection);
	//		shaders["standart_s"].setMat4("view", view);
	//		shaders["standart_s"].setMat4("model", portals[i]->model);
	//		glBindTexture(GL_TEXTURE_2D, textures[i ? "blue_wall" : "orange_wall"].id);
	//		meshes["mirrorPlane"].draw();
}

glm::mat4 Portal::getPotalView(const glm::mat4& m1, const  glm::mat4& m2, const glm::mat4& v)
{
	glm::mat4 viewRef = glm::inverse(glm::rotate(m2, glm::radians(180.0f), glm::vec3(0, 1, 0)) * glm::inverse(m1) * glm::inverse(v));
	return viewRef;
}

glm::mat4 Portal::getPotalProjection(const glm::mat4& m2, const glm::mat4& v)
{
	//Projection Clip plane 
	glm::vec3 portal2Pos(glm::column(m2, 3));
	glm::vec3 portal2Normal = glm::normalize(glm::mat3(glm::transpose(glm::inverse(m2))) * this->getIitialNormal());


	//|||||||||||||||||||||||||||ВНИМАНИЕ|||||||||||||||||||||||||||||
	//VVVVVVVVVVVVVVVVVVVVVVVVVVV        VVVVVVVVVVVVVVVVVVVVVVVVVVVVV
	//ВНИМАНИЕ ---> ЗДЕСЬ РАНЬШЕ БЫЛО -portal2Normal, И ВСЕ РАБОТАЛО, А СЕЙЧАС РАБОТАЕТ ТОЛЬКО БЕЗ МИНУСА. ЭТО ЧЕРНАЯ МАГИЯ!!!
	glm::vec4 viewSpacePortal = glm::normalize(v * glm::vec4(-portal2Normal, 0));
	//ɅɅɅɅɅɅɅɅɅɅɅɅɅɅɅɅɅɅɅɅɅɅɅɅɅɅɅ        ɅɅɅɅɅɅɅɅɅɅɅɅɅɅɅɅɅɅɅɅɅɅɅɅɅɅɅɅɅ
	//|||||||||||||||||||||||||||ВНИМАНИЕ|||||||||||||||||||||||||||||
	//Обновленно:
	//ААААААААААААААААААААААА НИЕГО НЕ РАБОТАЕТ ДАЖЕ ТААААААААААААААААААКК
	//Обновлено: проблема решена. Усножение было в неправильеом порядке.

	float lengthToPlane = abs(glm::dot(portal2Normal, glm::vec3(glm::column(glm::inverse(v), 3))) - glm::dot(portal2Pos, portal2Normal)) / 1;
	if (lengthToPlane < 0.01)
		lengthToPlane = 0.01;
	glm::mat4 projectionClip = getProjectionClipMat(glm::vec4(viewSpacePortal.x, viewSpacePortal.y, viewSpacePortal.z, lengthToPlane));
	return projectionClip;
}

inline float sgn(float x)
{
	if (x > 0.0F) return (1.0F);
	if (x < 0.0F) return (-1.0F);
	return (0.0F);
}
glm::mat4 Portal::getProjectionClipMat(glm::vec4 clipPlane)
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