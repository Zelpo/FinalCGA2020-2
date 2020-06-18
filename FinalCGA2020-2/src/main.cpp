#define _USE_MATH_DEFINES
#include <cmath>
//glew include
#include <GL/glew.h>

//std includes
#include <string>
#include <iostream>

// contains new std::shuffle definition
#include <algorithm>
#include <random>

//glfw include
#include <GLFW/glfw3.h>

// program include
#include "Headers/TimeManager.h"

// Shader include
#include "Headers/Shader.h"

// Model geometric includes
#include "Headers/Sphere.h"
#include "Headers/Cylinder.h"
#include "Headers/Box.h"
#include "Headers/FirstPersonCamera.h"
#include "Headers/ThirdPersonCamera.h"

//GLM include
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Headers/Texture.h"

// Include loader Model class
#include "Headers/Model.h"

// Include Terrain
#include "Headers/Terrain.h"

#include "Headers/AnimationUtils.h"

// Include Colision headers functions
#include "Headers/Colisiones.h"

// Shadow box include
#include "Headers/ShadowBox.h"

// OpenAL include
#include <AL/alut.h>

#define ARRAY_SIZE_IN_ELEMENTS(a) (sizeof(a)/sizeof(a[0]))

int screenWidth;
int screenHeight;

const unsigned int SHADOW_WIDTH = 2048, SHADOW_HEIGHT = 2048;

GLFWwindow *window;

Shader shader;
//Shader con skybox
Shader shaderSkybox;
//Shader con multiples luces
Shader shaderMulLighting;
//Shader para el terreno
Shader shaderTerrain;
//Shader para las particulas de fountain
Shader shaderParticlesFountain;
//Shader para las particulas de fuego
Shader shaderParticlesFire;
//Shader para visualizar el buffer de profundidad
Shader shaderViewDepth;
//Shader para dibujar el buffer de profunidad
Shader shaderDepth;

std::shared_ptr<Camera> camera(new ThirdPersonCamera());
float distanceFromTarget = 3.0;

Sphere skyboxSphere(20, 20);
Box boxCollider;
Sphere sphereCollider(10, 10);
Box boxViewDepth;
Box boxLightViewBox;

ShadowBox * shadowBox;

// Models complex instances

// Boo's
Model modelBoo1;
Model modelBoo2;
Model modelBoo3;
Model modelBoo4;

//Pared de la entrada
Model modelCuerpo;

// Laberinto
Model modelPEA;
Model modelPEB;
Model modelPEI;
Model modelPED;
Model modelPC1;
Model modelPC2;
Model modelPC3;
Model modelPC4;
Model modelPC5;
Model modelPC6;
Model modelPC7;
Model modelPC8;
Model modelPC9;
Model modelPC10;
Model modelPC11;
Model modelPC12;
Model modelPC13;
Model modelPC14;
Model modelPC15;
Model modelPC16;
Model modelPC17;
Model modelPC18;
Model modelPC19;
Model modelPC20;
Model modelPC21;
Model modelPC22;
Model modelPC23;
Model modelPC24;
Model modelPC25;
Model modelPC26;
Model modelPC27;
Model modelPC28;
Model modelPC29;
Model modelPC30;
Model modelPC31;
Model modelPC32;
Model modelPC33;
Model modelPC34;
Model modelPC35;
Model modelPC36;
Model modelPC37;
Model modelPC38;
Model modelPC39;
Model modelPC40;
Model modelPC41;
Model modelPC42;
Model modelPC43;
Model modelPC44;
Model modelPC45;
Model modelPC46;
Model modelPC47;
Model modelPC48;
Model modelPC49;
Model modelPC50;
Model modelPC51;
Model modelPC52;
Model modelPC53;
Model modelPC54;
Model modelPC55;
Model modelPC56;
Model modelPC57;
Model modelPC58;
Model modelPC59;
Model modelPC60;
Model modelPC61;
Model modelPC62;
Model modelPC63;
Model modelPC64;
Model modelPC65;
Model modelPC66;
Model modelPC67;
Model modelPC68;
Model modelPC69;
Model modelPC70;
Model modelPC71;
Model modelPC72;
Model modelPC73;
Model modelPC74;
Model modelPC75;
Model modelPC76;
Model modelPC77;
Model modelPC78;
Model modelPC79;
Model modelPC80;
Model modelPC81;
Model modelPC82;
Model modelPC83;
Model modelPC84;
Model modelPC85;
Model modelPC86;
Model modelPC87;
Model modelPC88;
Model modelPC89;
Model modelPC90;
Model modelPC91;
Model modelPC92;
Model modelPC93;
Model modelPC94;
Model modelPC95;
Model modelPC96;
Model modelPC97;
Model modelPC98;
Model modelPC99;
Model modelPC100;
Model modelPC101;
Model modelPC102;
Model modelPC103;
Model modelPC104;
Model modelPC105;
Model modelPC106;
Model modelPC107;
Model modelPC108;
Model modelPC109;
Model modelPC110;
Model modelPC111;
Model modelPC112;
Model modelPC113;
Model modelPC114;
Model modelPC115;
Model modelPC116;
Model modelPC117;
Model modelPC118;
Model modelPC119;
Model modelPC120;
Model modelPC121;
Model modelPC122;
Model modelPC123;
Model modelPC124;
Model modelPC125;
Model modelPC126;
Model modelPC127;
Model modelPC128;
Model modelPC129;
Model modelPC130;
Model modelPC131;
Model modelPC132;
Model modelPC133;
Model modelPC134;
Model modelPC135;
Model modelPC136;
Model modelPC137;
Model modelPC138;
Model modelPC139;
Model modelPC140;
Model modelPC141;
Model modelPC142;
Model modelPC143;
Model modelPC144;
Model modelPC145;
Model modelPC146;
Model modelPC147;
Model modelPC148;
Model modelPC149;
Model modelPC150;
Model modelPC151;
Model modelPC152;
Model modelPC153;
Model modelPC154;
Model modelPC155;
Model modelPC156;
Model modelPC157;
Model modelPC158;
Model modelPC159;
Model modelPC160;
Model modelPC161;
Model modelPC162;
Model modelPC163;
Model modelPC164;
Model modelPC165;
Model modelPC166;
Model modelPC167;
Model modelPC168;
Model modelPC169;
Model modelPC170;
Model modelPC171;
Model modelPC172;
Model modelPC173;
Model modelPC174;
Model modelPC175;
Model modelPC176;
Model modelPC177;
Model modelPC178;
Model modelPC179;
Model modelPC180;
Model modelPC181;
Model modelPC182;
Model modelPC183;
Model modelPC184;
Model modelPC185;
Model modelPC186;

// Mayow
Model mayowModelAnimate;
// Terrain model instance
Terrain terrain(-1, -1, 200, 16, "../Textures/heightmap.png");

GLuint textureCespedID, textureWallID, textureWindowID, textureHighwayID, textureLandingPadID;
GLuint textureTerrainBackgroundID, textureTerrainRID, textureTerrainGID, textureTerrainBID, textureTerrainBlendMapID;
GLuint textureParticleFountainID, textureParticleFireID, texId;
GLuint skyboxTextureID;

GLenum types[6] = {
GL_TEXTURE_CUBE_MAP_POSITIVE_X,
GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
GL_TEXTURE_CUBE_MAP_NEGATIVE_Z };

std::string fileNames[6] = { "../Textures/mp_bloodvalley/blood-valley_ft.tga",
		"../Textures/mp_bloodvalley/blood-valley_bk.tga",
		"../Textures/mp_bloodvalley/blood-valley_up.tga",
		"../Textures/mp_bloodvalley/blood-valley_dn.tga",
		"../Textures/mp_bloodvalley/blood-valley_rt.tga",
		"../Textures/mp_bloodvalley/blood-valley_lf.tga" };

bool exitApp = false;
int lastMousePosX, offsetX = 0;
int lastMousePosY, offsetY = 0;

// Model matrix definitions
glm::mat4 modelMatrixMayow = glm::mat4(1.0f);
glm::mat4 modelMatrixBoo1 = glm::mat4(1.0f);
glm::mat4 modelMatrixBoo2 = glm::mat4(1.0f);
glm::mat4 modelMatrixBoo3 = glm::mat4(1.0f);
glm::mat4 modelMatrixBoo4 = glm::mat4(1.0f);
glm::mat4 modelMatrixCuerpo = glm::mat4(1.0f);

// Model matrix Laberinto
glm::mat4 modelMatrixPEA = glm::mat4(1.0f);
glm::mat4 modelMatrixPEB = glm::mat4(1.0f);
glm::mat4 modelMatrixPEI = glm::mat4(1.0f);
glm::mat4 modelMatrixPED = glm::mat4(1.0f);
glm::mat4 modelMatrixPC1 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC2 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC3 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC4 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC5 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC6 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC7 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC8 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC9 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC10 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC11 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC12 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC13 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC14 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC15 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC16 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC17 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC18 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC19 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC20 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC21 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC22 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC23 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC24 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC25 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC26 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC27 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC28 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC29 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC30 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC31 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC32 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC33 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC34 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC35 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC36 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC37 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC38 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC39 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC40 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC41 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC42 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC43 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC44 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC45 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC46 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC47 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC48 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC49 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC50 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC51 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC52 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC53 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC54 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC55 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC56 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC57 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC58 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC59 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC60 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC61 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC62 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC63 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC64 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC65 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC66 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC67 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC68 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC69 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC70 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC71 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC72 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC73 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC74 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC75 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC76 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC77 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC78 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC79 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC80 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC81 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC82 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC83 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC84 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC85 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC86 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC87 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC88 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC89 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC90 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC91 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC92 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC93 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC94 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC95 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC96 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC97 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC98 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC99 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC100 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC101 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC102 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC103 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC104 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC105 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC106 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC107 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC108 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC109 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC110 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC111 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC112 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC113 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC114 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC115 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC116 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC117 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC118 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC119 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC120 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC121 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC122 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC123 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC124 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC125 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC126 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC127 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC128 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC129 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC130 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC131 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC132 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC133 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC134 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC135 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC136 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC137 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC138 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC139 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC140 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC141 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC142 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC143 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC144 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC145 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC146 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC147 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC148 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC149 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC150 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC151 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC152 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC153 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC154 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC155 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC156 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC157 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC158 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC159 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC160 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC161 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC162 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC163 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC164 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC165 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC166 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC167 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC168 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC169 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC170 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC171 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC172 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC173 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC174 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC175 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC176 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC177 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC178 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC179 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC180 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC181 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC182 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC183 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC184 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC185 = glm::mat4(1.0f);
glm::mat4 modelMatrixPC186 = glm::mat4(1.0f);

int animationIndex = 1;
int modelSelected = 2;
bool enableCountSelected = true;

// Blending model unsorted
std::map<std::string, glm::vec3> blendingUnsorted = {
		{"aircraft", glm::vec3(10.0, 0.0, -17.5)},
		{"lambo", glm::vec3(23.0, 0.0, 0.0)},
		{"heli", glm::vec3(5.0, 10.0, -5.0)},
		{"fountain", glm::vec3(5.0, 0.0, -40.0)},
		{"fire", glm::vec3(0.0, 0.0, 7.0)}
};

double deltaTime;
double currTime, lastTime;

// Definition for the particle system
GLuint initVel, startTime;
GLuint VAOParticles;
GLuint nParticles = 8000;
double currTimeParticlesAnimation, lastTimeParticlesAnimation;

// Definition for the particle system fire
GLuint initVelFire, startTimeFire;
GLuint VAOParticlesFire;
GLuint nParticlesFire = 2000;
GLuint posBuf[2], velBuf[2], age[2];
GLuint particleArray[2];
GLuint feedback[2];
GLuint drawBuf = 1;
float particleSize = 0.5, particleLifetime = 3.0;
double currTimeParticlesAnimationFire, lastTimeParticlesAnimationFire;

// Colliders
std::map<std::string, std::tuple<AbstractModel::OBB, glm::mat4, glm::mat4> > collidersOBB;
std::map<std::string, std::tuple<AbstractModel::SBB, glm::mat4, glm::mat4> > collidersSBB;

// Framesbuffers
GLuint depthMap, depthMapFBO;

/**********************
 * OpenAL config
 */

// OpenAL Defines
#define NUM_BUFFERS 4
#define NUM_SOURCES 4
#define NUM_ENVIRONMENTS 1
// Listener
ALfloat listenerPos[] = { 0.0, 0.0, 4.0 };
ALfloat listenerVel[] = { 0.0, 0.0, 0.0 };
ALfloat listenerOri[] = { 0.0, 0.0, 1.0, 0.0, 1.0, 0.0 };
// Source 0
ALfloat source0Pos[] = { -2.0, 0.0, 0.0 };
ALfloat source0Vel[] = { 0.0, 0.0, 0.0 };
// Source 1
ALfloat source1Pos[] = { 2.0, 0.0, 0.0 };
ALfloat source1Vel[] = { 0.0, 0.0, 0.0 };
// Source 2
ALfloat source2Pos[] = { 2.0, 0.0, 0.0 };
ALfloat source2Vel[] = { 0.0, 0.0, 0.0 };
// Source 3
ALfloat source3Pos[] = { 0.0, 0.0, 0.0 };
ALfloat source3Vel[] = { 0.0, 0.0, 0.0 };
// Buffers
ALuint buffer[NUM_BUFFERS];
ALuint source[NUM_SOURCES];
ALuint environment[NUM_ENVIRONMENTS];
// Configs
ALsizei size, freq;
ALenum format;
ALvoid *data;
int ch;
ALboolean loop;
std::vector<bool> sourcesPlay = {true, true, true, true};

// Se definen todos las funciones.
void reshapeCallback(GLFWwindow *Window, int widthRes, int heightRes);
void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mode);
void mouseCallback(GLFWwindow *window, double xpos, double ypos);
void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
void mouseButtonCallback(GLFWwindow *window, int button, int state, int mod);
void initParticleBuffers();
void init(int width, int height, std::string strTitle, bool bFullScreen);
void destroy();
bool processInput(bool continueApplication = true);
void prepareScene();
void prepareDepthScene();
void renderScene(bool renderParticles = true);

void initParticleBuffers() {
	// Generate the buffers
	glGenBuffers(1, &initVel);   // Initial velocity buffer
	glGenBuffers(1, &startTime); // Start time buffer

	// Allocate space for all buffers
	int size = nParticles * 3 * sizeof(float);
	glBindBuffer(GL_ARRAY_BUFFER, initVel);
	glBufferData(GL_ARRAY_BUFFER, size, NULL, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, startTime);
	glBufferData(GL_ARRAY_BUFFER, nParticles * sizeof(float), NULL, GL_STATIC_DRAW);

	// Fill the first velocity buffer with random velocities
	glm::vec3 v(0.0f);
	float velocity, theta, phi;
	GLfloat *data = new GLfloat[nParticles * 3];
	for (unsigned int i = 0; i < nParticles; i++) {

		theta = glm::mix(0.0f, glm::pi<float>() / 6.0f, ((float)rand() / RAND_MAX));
		phi = glm::mix(0.0f, glm::two_pi<float>(), ((float)rand() / RAND_MAX));

		v.x = sinf(theta) * cosf(phi);
		v.y = cosf(theta);
		v.z = sinf(theta) * sinf(phi);

		velocity = glm::mix(0.6f, 0.8f, ((float)rand() / RAND_MAX));
		v = glm::normalize(v) * velocity;

		data[3 * i] = v.x;
		data[3 * i + 1] = v.y;
		data[3 * i + 2] = v.z;
	}
	glBindBuffer(GL_ARRAY_BUFFER, initVel);
	glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);

	// Fill the start time buffer
	delete[] data;
	data = new GLfloat[nParticles];
	float time = 0.0f;
	float rate = 0.00075f;
	for (unsigned int i = 0; i < nParticles; i++) {
		data[i] = time;
		time += rate;
	}
	glBindBuffer(GL_ARRAY_BUFFER, startTime);
	glBufferSubData(GL_ARRAY_BUFFER, 0, nParticles * sizeof(float), data);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	delete[] data;

	glGenVertexArrays(1, &VAOParticles);
	glBindVertexArray(VAOParticles);
	glBindBuffer(GL_ARRAY_BUFFER, initVel);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, startTime);
	glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
}

void initParticleBuffersFire() {
	// Generate the buffers
	glGenBuffers(2, posBuf);    // position buffers
	glGenBuffers(2, velBuf);    // velocity buffers
	glGenBuffers(2, age);       // age buffers

	// Allocate space for all buffers
	int size = nParticlesFire * sizeof(GLfloat);
	glBindBuffer(GL_ARRAY_BUFFER, posBuf[0]);
	glBufferData(GL_ARRAY_BUFFER, 3 * size, 0, GL_DYNAMIC_COPY);
	glBindBuffer(GL_ARRAY_BUFFER, posBuf[1]);
	glBufferData(GL_ARRAY_BUFFER, 3 * size, 0, GL_DYNAMIC_COPY);
	glBindBuffer(GL_ARRAY_BUFFER, velBuf[0]);
	glBufferData(GL_ARRAY_BUFFER, 3 * size, 0, GL_DYNAMIC_COPY);
	glBindBuffer(GL_ARRAY_BUFFER, velBuf[1]);
	glBufferData(GL_ARRAY_BUFFER, 3 * size, 0, GL_DYNAMIC_COPY);
	glBindBuffer(GL_ARRAY_BUFFER, age[0]);
	glBufferData(GL_ARRAY_BUFFER, size, 0, GL_DYNAMIC_COPY);
	glBindBuffer(GL_ARRAY_BUFFER, age[1]);
	glBufferData(GL_ARRAY_BUFFER, size, 0, GL_DYNAMIC_COPY);

	// Fill the first age buffer
	std::vector<GLfloat> initialAge(nParticlesFire);
	float rate = particleLifetime / nParticlesFire;
	for(unsigned int i = 0; i < nParticlesFire; i++ ) {
		int index = i - nParticlesFire;
		float result = rate * index;
		initialAge[i] = result;
	}
	// Shuffle them for better looking results
	//Random::shuffle(initialAge);
	auto rng = std::default_random_engine {};
	std::shuffle(initialAge.begin(), initialAge.end(), rng);
	glBindBuffer(GL_ARRAY_BUFFER, age[0]);
	glBufferSubData(GL_ARRAY_BUFFER, 0, size, initialAge.data());

	glBindBuffer(GL_ARRAY_BUFFER,0);

	// Create vertex arrays for each set of buffers
	glGenVertexArrays(2, particleArray);

	// Set up particle array 0
	glBindVertexArray(particleArray[0]);
	glBindBuffer(GL_ARRAY_BUFFER, posBuf[0]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, velBuf[0]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, age[0]);
	glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(2);

	// Set up particle array 1
	glBindVertexArray(particleArray[1]);
	glBindBuffer(GL_ARRAY_BUFFER, posBuf[1]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, velBuf[1]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, age[1]);
	glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);

	// Setup the feedback objects
	glGenTransformFeedbacks(2, feedback);

	// Transform feedback 0
	glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, feedback[0]);
	glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, posBuf[0]);
	glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 1, velBuf[0]);
	glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 2, age[0]);

	// Transform feedback 1
	glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, feedback[1]);
	glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, posBuf[1]);
	glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 1, velBuf[1]);
	glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 2, age[1]);

	glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, 0);
}

// Implementacion de todas las funciones.
void init(int width, int height, std::string strTitle, bool bFullScreen) {

	if (!glfwInit()) {
		std::cerr << "Failed to initialize GLFW" << std::endl;
		exit(-1);
	}

	screenWidth = width;
	screenHeight = height;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	if (bFullScreen)
		window = glfwCreateWindow(width, height, strTitle.c_str(),
				glfwGetPrimaryMonitor(), nullptr);
	else
		window = glfwCreateWindow(width, height, strTitle.c_str(), nullptr,
				nullptr);

	if (window == nullptr) {
		std::cerr
				<< "Error to create GLFW window, you can try download the last version of your video card that support OpenGL 3.3+"
				<< std::endl;
		destroy();
		exit(-1);
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(0);

	glfwSetWindowSizeCallback(window, reshapeCallback);
	glfwSetKeyCallback(window, keyCallback);
	glfwSetCursorPosCallback(window, mouseCallback);
	glfwSetScrollCallback(window, scrollCallback);
	glfwSetMouseButtonCallback(window, mouseButtonCallback);
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	// Init glew
	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if (GLEW_OK != err) {
		std::cerr << "Failed to initialize glew" << std::endl;
		exit(-1);
	}

	glViewport(0, 0, screenWidth, screenHeight);
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	// Inicialización de los shaders
	shader.initialize("../Shaders/colorShader.vs", "../Shaders/colorShader.fs");
	shaderSkybox.initialize("../Shaders/skyBox.vs", "../Shaders/skyBox_fog.fs");
	shaderMulLighting.initialize("../Shaders/iluminacion_textura_animation_shadow.vs", "../Shaders/multipleLights_shadow.fs");
	shaderTerrain.initialize("../Shaders/terrain_shadow.vs", "../Shaders/terrain_shadow.fs");
	shaderParticlesFountain.initialize("../Shaders/particlesFountain.vs", "../Shaders/particlesFountain.fs");
	shaderParticlesFire.initialize("../Shaders/particlesFire.vs", "../Shaders/particlesFire.fs", {"Position", "Velocity", "Age"});
	shaderViewDepth.initialize("../Shaders/texturizado.vs", "../Shaders/texturizado_depth_view.fs");
	shaderDepth.initialize("../Shaders/shadow_mapping_depth.vs", "../Shaders/shadow_mapping_depth.fs");

	// Inicializacion de los objetos.
	skyboxSphere.init();
	skyboxSphere.setShader(&shaderSkybox);
	skyboxSphere.setScale(glm::vec3(100.0f, 100.0f, 100.0f));

	boxCollider.init();
	boxCollider.setShader(&shader);
	boxCollider.setColor(glm::vec4(1.0, 1.0, 1.0, 1.0));

	sphereCollider.init();
	sphereCollider.setShader(&shader);
	sphereCollider.setColor(glm::vec4(1.0, 1.0, 1.0, 1.0));

	boxViewDepth.init();
	boxViewDepth.setShader(&shaderViewDepth);

	boxLightViewBox.init();
	boxLightViewBox.setShader(&shaderViewDepth);

	terrain.init();
	terrain.setShader(&shaderTerrain);
	terrain.setPosition(glm::vec3(100, 0, 100));

	//Mayow
	mayowModelAnimate.loadModel("../models/mayow/personaje2.fbx");
	mayowModelAnimate.setShader(&shaderMulLighting);
	
	//Boo's
	modelBoo1.loadModel("../models/Boo/Boo1.obj");
	modelBoo1.setShader(&shaderMulLighting);

	modelBoo2.loadModel("../models/Boo/Boo2.obj");
	modelBoo2.setShader(&shaderMulLighting);

	modelBoo3.loadModel("../models/Boo/Boo3.obj");
	modelBoo3.setShader(&shaderMulLighting);

	modelBoo4.loadModel("../models/Boo/Boo4.obj");
	modelBoo4.setShader(&shaderMulLighting);

	// Cuerpo
	modelCuerpo.loadModel("../models/Cuerpo/Cuerpo.obj");
	modelCuerpo.setShader(&shaderMulLighting);
	
	//Laberinto
	modelPEA.loadModel("../models/laberinto/PEA.obj");
	modelPEA.setShader(&shaderMulLighting);

	modelPEB.loadModel("../models/laberinto/PEB.obj");
	modelPEB.setShader(&shaderMulLighting);

	modelPEI.loadModel("../models/laberinto/PEI.obj");
	modelPEI.setShader(&shaderMulLighting);

	modelPED.loadModel("../models/laberinto/PED.obj");
	modelPED.setShader(&shaderMulLighting);

	modelPC1.loadModel("../models/laberinto/PC1.obj");
	modelPC1.setShader(&shaderMulLighting);

	modelPC2.loadModel("../models/laberinto/PC2.obj");
	modelPC2.setShader(&shaderMulLighting);

	modelPC3.loadModel("../models/laberinto/PC3.obj");
	modelPC3.setShader(&shaderMulLighting);

	modelPC4.loadModel("../models/laberinto/PC4.obj");
	modelPC4.setShader(&shaderMulLighting);

	modelPC5.loadModel("../models/laberinto/PC5.obj");
	modelPC5.setShader(&shaderMulLighting);

	modelPC6.loadModel("../models/laberinto/PC6.obj");
	modelPC6.setShader(&shaderMulLighting);

	modelPC7.loadModel("../models/laberinto/PC7.obj");
	modelPC7.setShader(&shaderMulLighting);

	modelPC8.loadModel("../models/laberinto/PC8.obj");
	modelPC8.setShader(&shaderMulLighting);

	modelPC9.loadModel("../models/laberinto/PC9.obj");
	modelPC9.setShader(&shaderMulLighting);

	modelPC10.loadModel("../models/laberinto/PC10.obj");
	modelPC10.setShader(&shaderMulLighting);

	modelPC11.loadModel("../models/laberinto/PC11.obj");
	modelPC11.setShader(&shaderMulLighting);

	modelPC12.loadModel("../models/laberinto/PC12.obj");
	modelPC12.setShader(&shaderMulLighting);

	modelPC13.loadModel("../models/laberinto/PC13.obj");
	modelPC13.setShader(&shaderMulLighting);

	modelPC14.loadModel("../models/laberinto/PC14.obj");
	modelPC14.setShader(&shaderMulLighting);

	modelPC15.loadModel("../models/laberinto/PC15.obj");
	modelPC15.setShader(&shaderMulLighting);

	modelPC16.loadModel("../models/laberinto/PC16.obj");
	modelPC16.setShader(&shaderMulLighting);

	modelPC17.loadModel("../models/laberinto/PC17.obj");
	modelPC17.setShader(&shaderMulLighting);

	modelPC18.loadModel("../models/laberinto/PC18.obj");
	modelPC18.setShader(&shaderMulLighting);

	modelPC19.loadModel("../models/laberinto/PC19.obj");
	modelPC19.setShader(&shaderMulLighting);

	modelPC20.loadModel("../models/laberinto/PC20.obj");
	modelPC20.setShader(&shaderMulLighting);

	modelPC21.loadModel("../models/laberinto/PC21.obj");
	modelPC21.setShader(&shaderMulLighting);

	modelPC22.loadModel("../models/laberinto/PC22.obj");
	modelPC22.setShader(&shaderMulLighting);

	modelPC23.loadModel("../models/laberinto/PC23.obj");
	modelPC23.setShader(&shaderMulLighting);

	modelPC24.loadModel("../models/laberinto/PC24.obj");
	modelPC24.setShader(&shaderMulLighting);

	modelPC25.loadModel("../models/laberinto/PC25.obj");
	modelPC25.setShader(&shaderMulLighting);

	modelPC26.loadModel("../models/laberinto/PC26.obj");
	modelPC26.setShader(&shaderMulLighting);

	modelPC27.loadModel("../models/laberinto/PC27.obj");
	modelPC27.setShader(&shaderMulLighting);

	modelPC28.loadModel("../models/laberinto/PC28.obj");
	modelPC28.setShader(&shaderMulLighting);

	modelPC29.loadModel("../models/laberinto/PC29.obj");
	modelPC29.setShader(&shaderMulLighting);

	modelPC30.loadModel("../models/laberinto/PC30.obj");
	modelPC30.setShader(&shaderMulLighting);

	modelPC31.loadModel("../models/laberinto/PC31.obj");
	modelPC31.setShader(&shaderMulLighting);

	modelPC32.loadModel("../models/laberinto/PC32.obj");
	modelPC32.setShader(&shaderMulLighting);

	modelPC33.loadModel("../models/laberinto/PC33.obj");
	modelPC33.setShader(&shaderMulLighting);

	modelPC34.loadModel("../models/laberinto/PC34.obj");
	modelPC34.setShader(&shaderMulLighting);

	modelPC35.loadModel("../models/laberinto/PC35.obj");
	modelPC35.setShader(&shaderMulLighting);

	modelPC36.loadModel("../models/laberinto/PC36.obj");
	modelPC36.setShader(&shaderMulLighting);

	modelPC37.loadModel("../models/laberinto/PC37.obj");
	modelPC37.setShader(&shaderMulLighting);

	modelPC38.loadModel("../models/laberinto/PC38.obj");
	modelPC38.setShader(&shaderMulLighting);

	modelPC39.loadModel("../models/laberinto/PC39.obj");
	modelPC39.setShader(&shaderMulLighting);

	modelPC40.loadModel("../models/laberinto/PC40.obj");
	modelPC40.setShader(&shaderMulLighting);

	modelPC41.loadModel("../models/laberinto/PC41.obj");
	modelPC41.setShader(&shaderMulLighting);

	modelPC42.loadModel("../models/laberinto/PC42.obj");
	modelPC42.setShader(&shaderMulLighting);

	modelPC43.loadModel("../models/laberinto/PC43.obj");
	modelPC43.setShader(&shaderMulLighting);

	modelPC44.loadModel("../models/laberinto/PC44.obj");
	modelPC44.setShader(&shaderMulLighting);

	modelPC45.loadModel("../models/laberinto/PC45.obj");
	modelPC45.setShader(&shaderMulLighting);

	modelPC46.loadModel("../models/laberinto/PC46.obj");
	modelPC46.setShader(&shaderMulLighting);

	modelPC47.loadModel("../models/laberinto/PC47.obj");
	modelPC47.setShader(&shaderMulLighting);

	modelPC48.loadModel("../models/laberinto/PC48.obj");
	modelPC48.setShader(&shaderMulLighting);

	modelPC49.loadModel("../models/laberinto/PC49.obj");
	modelPC49.setShader(&shaderMulLighting);

	modelPC50.loadModel("../models/laberinto/PC50.obj");
	modelPC50.setShader(&shaderMulLighting);

	modelPC51.loadModel("../models/laberinto/PC51.obj");
	modelPC51.setShader(&shaderMulLighting);

	modelPC52.loadModel("../models/laberinto/PC52.obj");
	modelPC52.setShader(&shaderMulLighting);

	modelPC53.loadModel("../models/laberinto/PC53.obj");
	modelPC53.setShader(&shaderMulLighting);

	modelPC54.loadModel("../models/laberinto/PC54.obj");
	modelPC54.setShader(&shaderMulLighting);

	modelPC55.loadModel("../models/laberinto/PC55.obj");
	modelPC55.setShader(&shaderMulLighting);

	modelPC56.loadModel("../models/laberinto/PC56.obj");
	modelPC56.setShader(&shaderMulLighting);

	modelPC57.loadModel("../models/laberinto/PC57.obj");
	modelPC57.setShader(&shaderMulLighting);

	modelPC58.loadModel("../models/laberinto/PC58.obj");
	modelPC58.setShader(&shaderMulLighting);

	modelPC59.loadModel("../models/laberinto/PC59.obj");
	modelPC59.setShader(&shaderMulLighting);

	modelPC60.loadModel("../models/laberinto/PC60.obj");
	modelPC60.setShader(&shaderMulLighting);

	modelPC61.loadModel("../models/laberinto/PC61.obj");
	modelPC61.setShader(&shaderMulLighting);

	modelPC62.loadModel("../models/laberinto/PC62.obj");
	modelPC62.setShader(&shaderMulLighting);

	modelPC63.loadModel("../models/laberinto/PC63.obj");
	modelPC63.setShader(&shaderMulLighting);

	modelPC64.loadModel("../models/laberinto/PC64.obj");
	modelPC64.setShader(&shaderMulLighting);

	modelPC65.loadModel("../models/laberinto/PC65.obj");
	modelPC65.setShader(&shaderMulLighting);

	modelPC66.loadModel("../models/laberinto/PC66.obj");
	modelPC66.setShader(&shaderMulLighting);

	modelPC67.loadModel("../models/laberinto/PC67.obj");
	modelPC67.setShader(&shaderMulLighting);

	modelPC68.loadModel("../models/laberinto/PC68.obj");
	modelPC68.setShader(&shaderMulLighting);

	modelPC69.loadModel("../models/laberinto/PC69.obj");
	modelPC69.setShader(&shaderMulLighting);

	modelPC70.loadModel("../models/laberinto/PC70.obj");
	modelPC70.setShader(&shaderMulLighting);

	modelPC71.loadModel("../models/laberinto/PC71.obj");
	modelPC71.setShader(&shaderMulLighting);

	modelPC72.loadModel("../models/laberinto/PC72.obj");
	modelPC72.setShader(&shaderMulLighting);

	modelPC73.loadModel("../models/laberinto/PC73.obj");
	modelPC73.setShader(&shaderMulLighting);

	modelPC74.loadModel("../models/laberinto/PC74.obj");
	modelPC74.setShader(&shaderMulLighting);

	modelPC75.loadModel("../models/laberinto/PC75.obj");
	modelPC75.setShader(&shaderMulLighting);

	modelPC76.loadModel("../models/laberinto/PC76.obj");
	modelPC76.setShader(&shaderMulLighting);

	modelPC77.loadModel("../models/laberinto/PC77.obj");
	modelPC77.setShader(&shaderMulLighting);

	modelPC78.loadModel("../models/laberinto/PC78.obj");
	modelPC78.setShader(&shaderMulLighting);

	modelPC79.loadModel("../models/laberinto/PC79.obj");
	modelPC79.setShader(&shaderMulLighting);

	modelPC80.loadModel("../models/laberinto/PC80.obj");
	modelPC80.setShader(&shaderMulLighting);

	modelPC81.loadModel("../models/laberinto/PC81.obj");
	modelPC81.setShader(&shaderMulLighting);

	modelPC82.loadModel("../models/laberinto/PC82.obj");
	modelPC82.setShader(&shaderMulLighting);

	modelPC83.loadModel("../models/laberinto/PC83.obj");
	modelPC83.setShader(&shaderMulLighting);

	modelPC84.loadModel("../models/laberinto/PC84.obj");
	modelPC84.setShader(&shaderMulLighting);

	modelPC85.loadModel("../models/laberinto/PC85.obj");
	modelPC85.setShader(&shaderMulLighting);

	modelPC86.loadModel("../models/laberinto/PC86.obj");
	modelPC86.setShader(&shaderMulLighting);

	modelPC87.loadModel("../models/laberinto/PC87.obj");
	modelPC87.setShader(&shaderMulLighting);

	modelPC88.loadModel("../models/laberinto/PC88.obj");
	modelPC88.setShader(&shaderMulLighting);

	modelPC89.loadModel("../models/laberinto/PC89.obj");
	modelPC89.setShader(&shaderMulLighting);

	modelPC90.loadModel("../models/laberinto/PC90.obj");
	modelPC90.setShader(&shaderMulLighting);

	modelPC91.loadModel("../models/laberinto/PC91.obj");
	modelPC91.setShader(&shaderMulLighting);

	modelPC92.loadModel("../models/laberinto/PC92.obj");
	modelPC92.setShader(&shaderMulLighting);

	modelPC93.loadModel("../models/laberinto/PC93.obj");
	modelPC93.setShader(&shaderMulLighting);

	modelPC94.loadModel("../models/laberinto/PC94.obj");
	modelPC94.setShader(&shaderMulLighting);

	modelPC95.loadModel("../models/laberinto/PC95.obj");
	modelPC95.setShader(&shaderMulLighting);

	modelPC96.loadModel("../models/laberinto/PC96.obj");
	modelPC96.setShader(&shaderMulLighting);

	modelPC97.loadModel("../models/laberinto/PC97.obj");
	modelPC97.setShader(&shaderMulLighting);

	modelPC98.loadModel("../models/laberinto/PC98.obj");
	modelPC98.setShader(&shaderMulLighting);

	modelPC99.loadModel("../models/laberinto/PC99.obj");
	modelPC99.setShader(&shaderMulLighting);

	modelPC100.loadModel("../models/laberinto/PC100.obj");
	modelPC100.setShader(&shaderMulLighting);

	modelPC101.loadModel("../models/laberinto/PC101.obj");
	modelPC101.setShader(&shaderMulLighting);

	modelPC102.loadModel("../models/laberinto/PC102.obj");
	modelPC102.setShader(&shaderMulLighting);

	modelPC103.loadModel("../models/laberinto/PC103.obj");
	modelPC103.setShader(&shaderMulLighting);

	modelPC104.loadModel("../models/laberinto/PC104.obj");
	modelPC104.setShader(&shaderMulLighting);

	modelPC105.loadModel("../models/laberinto/PC105.obj");
	modelPC105.setShader(&shaderMulLighting);

	modelPC106.loadModel("../models/laberinto/PC106.obj");
	modelPC106.setShader(&shaderMulLighting);

	modelPC107.loadModel("../models/laberinto/PC107.obj");
	modelPC107.setShader(&shaderMulLighting);

	modelPC108.loadModel("../models/laberinto/PC108.obj");
	modelPC108.setShader(&shaderMulLighting);

	modelPC109.loadModel("../models/laberinto/PC109.obj");
	modelPC109.setShader(&shaderMulLighting);

	modelPC110.loadModel("../models/laberinto/PC110.obj");
	modelPC110.setShader(&shaderMulLighting);

	modelPC111.loadModel("../models/laberinto/PC111.obj");
	modelPC111.setShader(&shaderMulLighting);

	modelPC112.loadModel("../models/laberinto/PC112.obj");
	modelPC112.setShader(&shaderMulLighting);

	modelPC113.loadModel("../models/laberinto/PC113.obj");
	modelPC113.setShader(&shaderMulLighting);

	modelPC114.loadModel("../models/laberinto/PC114.obj");
	modelPC114.setShader(&shaderMulLighting);

	modelPC115.loadModel("../models/laberinto/PC115.obj");
	modelPC115.setShader(&shaderMulLighting);

	modelPC116.loadModel("../models/laberinto/PC116.obj");
	modelPC116.setShader(&shaderMulLighting);

	modelPC117.loadModel("../models/laberinto/PC117.obj");
	modelPC117.setShader(&shaderMulLighting);

	modelPC118.loadModel("../models/laberinto/PC118.obj");
	modelPC118.setShader(&shaderMulLighting);

	modelPC119.loadModel("../models/laberinto/PC119.obj");
	modelPC119.setShader(&shaderMulLighting);

	modelPC120.loadModel("../models/laberinto/PC120.obj");
	modelPC120.setShader(&shaderMulLighting);

	modelPC121.loadModel("../models/laberinto/PC121.obj");
	modelPC121.setShader(&shaderMulLighting);

	modelPC122.loadModel("../models/laberinto/PC122.obj");
	modelPC122.setShader(&shaderMulLighting);

	modelPC123.loadModel("../models/laberinto/PC123.obj");
	modelPC123.setShader(&shaderMulLighting);

	modelPC124.loadModel("../models/laberinto/PC124.obj");
	modelPC124.setShader(&shaderMulLighting);

	modelPC125.loadModel("../models/laberinto/PC125.obj");
	modelPC125.setShader(&shaderMulLighting);

	modelPC126.loadModel("../models/laberinto/PC126.obj");
	modelPC126.setShader(&shaderMulLighting);

	modelPC127.loadModel("../models/laberinto/PC127.obj");
	modelPC127.setShader(&shaderMulLighting);

	modelPC128.loadModel("../models/laberinto/PC128.obj");
	modelPC128.setShader(&shaderMulLighting);

	modelPC129.loadModel("../models/laberinto/PC129.obj");
	modelPC129.setShader(&shaderMulLighting);

	modelPC130.loadModel("../models/laberinto/PC130.obj");
	modelPC130.setShader(&shaderMulLighting);

	modelPC131.loadModel("../models/laberinto/PC131.obj");
	modelPC131.setShader(&shaderMulLighting);

	modelPC132.loadModel("../models/laberinto/PC132.obj");
	modelPC132.setShader(&shaderMulLighting);

	modelPC133.loadModel("../models/laberinto/PC133.obj");
	modelPC133.setShader(&shaderMulLighting);

	modelPC134.loadModel("../models/laberinto/PC134.obj");
	modelPC134.setShader(&shaderMulLighting);

	modelPC135.loadModel("../models/laberinto/PC135.obj");
	modelPC135.setShader(&shaderMulLighting);

	modelPC136.loadModel("../models/laberinto/PC136.obj");
	modelPC136.setShader(&shaderMulLighting);

	modelPC137.loadModel("../models/laberinto/PC137.obj");
	modelPC137.setShader(&shaderMulLighting);

	modelPC138.loadModel("../models/laberinto/PC138.obj");
	modelPC138.setShader(&shaderMulLighting);

	modelPC139.loadModel("../models/laberinto/PC139.obj");
	modelPC139.setShader(&shaderMulLighting);

	modelPC140.loadModel("../models/laberinto/PC140.obj");
	modelPC140.setShader(&shaderMulLighting);

	modelPC141.loadModel("../models/laberinto/PC141.obj");
	modelPC141.setShader(&shaderMulLighting);

	modelPC142.loadModel("../models/laberinto/PC142.obj");
	modelPC142.setShader(&shaderMulLighting);

	modelPC143.loadModel("../models/laberinto/PC143.obj");
	modelPC143.setShader(&shaderMulLighting);

	modelPC144.loadModel("../models/laberinto/PC144.obj");
	modelPC144.setShader(&shaderMulLighting);

	modelPC145.loadModel("../models/laberinto/PC145.obj");
	modelPC145.setShader(&shaderMulLighting);

	modelPC146.loadModel("../models/laberinto/PC146.obj");
	modelPC146.setShader(&shaderMulLighting);

	modelPC147.loadModel("../models/laberinto/PC147.obj");
	modelPC147.setShader(&shaderMulLighting);

	modelPC148.loadModel("../models/laberinto/PC148.obj");
	modelPC148.setShader(&shaderMulLighting);

	modelPC149.loadModel("../models/laberinto/PC149.obj");
	modelPC149.setShader(&shaderMulLighting);

	modelPC150.loadModel("../models/laberinto/PC150.obj");
	modelPC150.setShader(&shaderMulLighting);

	modelPC151.loadModel("../models/laberinto/PC151.obj");
	modelPC151.setShader(&shaderMulLighting);

	modelPC152.loadModel("../models/laberinto/PC152.obj");
	modelPC152.setShader(&shaderMulLighting);

	modelPC153.loadModel("../models/laberinto/PC153.obj");
	modelPC153.setShader(&shaderMulLighting);

	modelPC154.loadModel("../models/laberinto/PC154.obj");
	modelPC154.setShader(&shaderMulLighting);

	modelPC155.loadModel("../models/laberinto/PC155.obj");
	modelPC155.setShader(&shaderMulLighting);

	modelPC156.loadModel("../models/laberinto/PC156.obj");
	modelPC156.setShader(&shaderMulLighting);

	modelPC157.loadModel("../models/laberinto/PC157.obj");
	modelPC157.setShader(&shaderMulLighting);

	modelPC158.loadModel("../models/laberinto/PC158.obj");
	modelPC158.setShader(&shaderMulLighting);

	modelPC159.loadModel("../models/laberinto/PC159.obj");
	modelPC159.setShader(&shaderMulLighting);

	modelPC160.loadModel("../models/laberinto/PC160.obj");
	modelPC160.setShader(&shaderMulLighting);

	modelPC161.loadModel("../models/laberinto/PC161.obj");
	modelPC161.setShader(&shaderMulLighting);

	modelPC162.loadModel("../models/laberinto/PC162.obj");
	modelPC162.setShader(&shaderMulLighting);

	modelPC163.loadModel("../models/laberinto/PC163.obj");
	modelPC163.setShader(&shaderMulLighting);

	modelPC164.loadModel("../models/laberinto/PC164.obj");
	modelPC164.setShader(&shaderMulLighting);

	modelPC165.loadModel("../models/laberinto/PC165.obj");
	modelPC165.setShader(&shaderMulLighting);

	modelPC166.loadModel("../models/laberinto/PC166.obj");
	modelPC166.setShader(&shaderMulLighting);

	modelPC167.loadModel("../models/laberinto/PC167.obj");
	modelPC167.setShader(&shaderMulLighting);

	modelPC168.loadModel("../models/laberinto/PC168.obj");
	modelPC168.setShader(&shaderMulLighting);

	modelPC169.loadModel("../models/laberinto/PC169.obj");
	modelPC169.setShader(&shaderMulLighting);

	modelPC170.loadModel("../models/laberinto/PC170.obj");
	modelPC170.setShader(&shaderMulLighting);

	modelPC171.loadModel("../models/laberinto/PC171.obj");
	modelPC171.setShader(&shaderMulLighting);

	modelPC172.loadModel("../models/laberinto/PC172.obj");
	modelPC172.setShader(&shaderMulLighting);

	modelPC173.loadModel("../models/laberinto/PC173.obj");
	modelPC173.setShader(&shaderMulLighting);

	modelPC174.loadModel("../models/laberinto/PC174.obj");
	modelPC174.setShader(&shaderMulLighting);

	modelPC175.loadModel("../models/laberinto/PC175.obj");
	modelPC175.setShader(&shaderMulLighting);

	modelPC176.loadModel("../models/laberinto/PC176.obj");
	modelPC176.setShader(&shaderMulLighting);

	modelPC177.loadModel("../models/laberinto/PC177.obj");
	modelPC177.setShader(&shaderMulLighting);

	modelPC178.loadModel("../models/laberinto/PC178.obj");
	modelPC178.setShader(&shaderMulLighting);

	modelPC179.loadModel("../models/laberinto/PC179.obj");
	modelPC179.setShader(&shaderMulLighting);

	modelPC180.loadModel("../models/laberinto/PC180.obj");
	modelPC180.setShader(&shaderMulLighting);

	modelPC181.loadModel("../models/laberinto/PC181.obj");
	modelPC181.setShader(&shaderMulLighting);

	modelPC182.loadModel("../models/laberinto/PC182.obj");
	modelPC182.setShader(&shaderMulLighting);

	modelPC183.loadModel("../models/laberinto/PC183.obj");
	modelPC183.setShader(&shaderMulLighting);

	modelPC184.loadModel("../models/laberinto/PC184.obj");
	modelPC184.setShader(&shaderMulLighting);

	modelPC185.loadModel("../models/laberinto/PC185.obj");
	modelPC185.setShader(&shaderMulLighting);

	modelPC186.loadModel("../models/laberinto/PC186.obj");
	modelPC186.setShader(&shaderMulLighting);
	
	camera->setPosition(glm::vec3(0.0, 0.0, 10.0));
	camera->setDistanceFromTarget(distanceFromTarget);
	camera->setSensitivity(0.5);

	// Definimos el tamanio de la imagen
	int imageWidth, imageHeight;
	FIBITMAP *bitmap;
	unsigned char *data;

	// Carga de texturas para el skybox
	Texture skyboxTexture = Texture("");
	glGenTextures(1, &skyboxTextureID);
	// Tipo de textura CUBE MAP
	glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxTextureID);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	for (int i = 0; i < ARRAY_SIZE_IN_ELEMENTS(types); i++) {
		skyboxTexture = Texture(fileNames[i]);
		FIBITMAP *bitmap = skyboxTexture.loadImage(true);
		unsigned char *data = skyboxTexture.convertToData(bitmap, imageWidth,
				imageHeight);
		if (data) {
			glTexImage2D(types[i], 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		} else
			std::cout << "Failed to load texture" << std::endl;
		skyboxTexture.freeImage(bitmap);
	}

	// Definiendo la textura a utilizar
	Texture textureCesped("../Textures/cesped.jpg");
	// Carga el mapa de bits (FIBITMAP es el tipo de dato de la libreria)
	bitmap = textureCesped.loadImage();
	// Convertimos el mapa de bits en un arreglo unidimensional de tipo unsigned char
	data = textureCesped.convertToData(bitmap, imageWidth,
			imageHeight);
	// Creando la textura con id 1
	glGenTextures(1, &textureCespedID);
	// Enlazar esa textura a una tipo de textura de 2D.
	glBindTexture(GL_TEXTURE_2D, textureCespedID);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT); // set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Verifica si se pudo abrir la textura
	if (data) {
		// Transferis los datos de la imagen a memoria
		// Tipo de textura, Mipmaps, Formato interno de openGL, ancho, alto, Mipmaps,
		// Formato interno de la libreria de la imagen, el tipo de dato y al apuntador
		// a los datos
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
		GL_BGRA, GL_UNSIGNED_BYTE, data);
		// Generan los niveles del mipmap (OpenGL es el ecargado de realizarlos)
		glGenerateMipmap(GL_TEXTURE_2D);
	} else
		std::cout << "Failed to load texture" << std::endl;
	// Libera la memoria de la textura
	textureCesped.freeImage(bitmap);

	// Definiendo la textura a utilizar
	Texture textureWall("../Textures/whiteWall.jpg");
	// Carga el mapa de bits (FIBITMAP es el tipo de dato de la libreria)
	bitmap = textureWall.loadImage();
	// Convertimos el mapa de bits en un arreglo unidimensional de tipo unsigned char
	data = textureWall.convertToData(bitmap, imageWidth,
			imageHeight);
	// Creando la textura con id 1
	glGenTextures(1, &textureWallID);
	// Enlazar esa textura a una tipo de textura de 2D.
	glBindTexture(GL_TEXTURE_2D, textureWallID);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Verifica si se pudo abrir la textura
	if (data) {
		// Transferis los datos de la imagen a memoria
		// Tipo de textura, Mipmaps, Formato interno de openGL, ancho, alto, Mipmaps,
		// Formato interno de la libreria de la imagen, el tipo de dato y al apuntador
		// a los datos
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
		GL_BGRA, GL_UNSIGNED_BYTE, data);
		// Generan los niveles del mipmap (OpenGL es el ecargado de realizarlos)
		glGenerateMipmap(GL_TEXTURE_2D);
	} else
		std::cout << "Failed to load texture" << std::endl;
	// Libera la memoria de la textura
	textureWall.freeImage(bitmap);

	// Definiendo la textura a utilizar
	Texture textureWindow("../Textures/ventana.png");
	// Carga el mapa de bits (FIBITMAP es el tipo de dato de la libreria)
	bitmap = textureWindow.loadImage();
	// Convertimos el mapa de bits en un arreglo unidimensional de tipo unsigned char
	data = textureWindow.convertToData(bitmap, imageWidth,
			imageHeight);
	// Creando la textura con id 1
	glGenTextures(1, &textureWindowID);
	// Enlazar esa textura a una tipo de textura de 2D.
	glBindTexture(GL_TEXTURE_2D, textureWindowID);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Verifica si se pudo abrir la textura
	if (data) {
		// Transferis los datos de la imagen a memoria
		// Tipo de textura, Mipmaps, Formato interno de openGL, ancho, alto, Mipmaps,
		// Formato interno de la libreria de la imagen, el tipo de dato y al apuntador
		// a los datos
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
		GL_BGRA, GL_UNSIGNED_BYTE, data);
		// Generan los niveles del mipmap (OpenGL es el ecargado de realizarlos)
		glGenerateMipmap(GL_TEXTURE_2D);
	} else
		std::cout << "Failed to load texture" << std::endl;
	// Libera la memoria de la textura
	textureWindow.freeImage(bitmap);

	// Definiendo la textura a utilizar
	Texture textureHighway("../Textures/highway.jpg");
	// Carga el mapa de bits (FIBITMAP es el tipo de dato de la libreria)
	bitmap = textureHighway.loadImage();
	// Convertimos el mapa de bits en un arreglo unidimensional de tipo unsigned char
	data = textureHighway.convertToData(bitmap, imageWidth,
			imageHeight);
	// Creando la textura con id 1
	glGenTextures(1, &textureHighwayID);
	// Enlazar esa textura a una tipo de textura de 2D.
	glBindTexture(GL_TEXTURE_2D, textureHighwayID);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Verifica si se pudo abrir la textura
	if (data) {
		// Transferis los datos de la imagen a memoria
		// Tipo de textura, Mipmaps, Formato interno de openGL, ancho, alto, Mipmaps,
		// Formato interno de la libreria de la imagen, el tipo de dato y al apuntador
		// a los datos
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
		GL_BGRA, GL_UNSIGNED_BYTE, data);
		// Generan los niveles del mipmap (OpenGL es el ecargado de realizarlos)
		glGenerateMipmap(GL_TEXTURE_2D);
	} else
		std::cout << "Failed to load texture" << std::endl;
	// Libera la memoria de la textura
	textureHighway.freeImage(bitmap);

	// Definiendo la textura a utilizar
	Texture textureLandingPad("../Textures/landingPad.jpg");
	// Carga el mapa de bits (FIBITMAP es el tipo de dato de la libreria)
	bitmap = textureLandingPad.loadImage();
	// Convertimos el mapa de bits en un arreglo unidimensional de tipo unsigned char
	data = textureLandingPad.convertToData(bitmap, imageWidth,
			imageHeight);
	// Creando la textura con id 1
	glGenTextures(1, &textureLandingPadID);
	// Enlazar esa textura a una tipo de textura de 2D.
	glBindTexture(GL_TEXTURE_2D, textureLandingPadID);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Verifica si se pudo abrir la textura
	if (data) {
		// Transferis los datos de la imagen a memoria
		// Tipo de textura, Mipmaps, Formato interno de openGL, ancho, alto, Mipmaps,
		// Formato interno de la libreria de la imagen, el tipo de dato y al apuntador
		// a los datos
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
		GL_BGRA, GL_UNSIGNED_BYTE, data);
		// Generan los niveles del mipmap (OpenGL es el ecargado de realizarlos)
		glGenerateMipmap(GL_TEXTURE_2D);
	} else
		std::cout << "Failed to load texture" << std::endl;
	// Libera la memoria de la textura
	textureLandingPad.freeImage(bitmap);

	// Definiendo la textura a utilizar
	Texture textureTerrainBackground("../Textures/grassy2.png");
	// Carga el mapa de bits (FIBITMAP es el tipo de dato de la libreria)
	bitmap = textureTerrainBackground.loadImage();
	// Convertimos el mapa de bits en un arreglo unidimensional de tipo unsigned char
	data = textureTerrainBackground.convertToData(bitmap, imageWidth,
			imageHeight);
	// Creando la textura con id 1
	glGenTextures(1, &textureTerrainBackgroundID);
	// Enlazar esa textura a una tipo de textura de 2D.
	glBindTexture(GL_TEXTURE_2D, textureTerrainBackgroundID);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Verifica si se pudo abrir la textura
	if (data) {
		// Transferis los datos de la imagen a memoria
		// Tipo de textura, Mipmaps, Formato interno de openGL, ancho, alto, Mipmaps,
		// Formato interno de la libreria de la imagen, el tipo de dato y al apuntador
		// a los datos
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
		GL_BGRA, GL_UNSIGNED_BYTE, data);
		// Generan los niveles del mipmap (OpenGL es el ecargado de realizarlos)
		glGenerateMipmap(GL_TEXTURE_2D);
	} else
		std::cout << "Failed to load texture" << std::endl;
	// Libera la memoria de la textura
	textureTerrainBackground.freeImage(bitmap);

	// Definiendo la textura a utilizar
	Texture textureTerrainR("../Textures/mud.png");
	// Carga el mapa de bits (FIBITMAP es el tipo de dato de la libreria)
	bitmap = textureTerrainR.loadImage();
	// Convertimos el mapa de bits en un arreglo unidimensional de tipo unsigned char
	data = textureTerrainR.convertToData(bitmap, imageWidth,
			imageHeight);
	// Creando la textura con id 1
	glGenTextures(1, &textureTerrainRID);
	// Enlazar esa textura a una tipo de textura de 2D.
	glBindTexture(GL_TEXTURE_2D, textureTerrainRID);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Verifica si se pudo abrir la textura
	if (data) {
		// Transferis los datos de la imagen a memoria
		// Tipo de textura, Mipmaps, Formato interno de openGL, ancho, alto, Mipmaps,
		// Formato interno de la libreria de la imagen, el tipo de dato y al apuntador
		// a los datos
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
		GL_BGRA, GL_UNSIGNED_BYTE, data);
		// Generan los niveles del mipmap (OpenGL es el ecargado de realizarlos)
		glGenerateMipmap(GL_TEXTURE_2D);
	} else
		std::cout << "Failed to load texture" << std::endl;
	// Libera la memoria de la textura
	textureTerrainR.freeImage(bitmap);

	// Definiendo la textura a utilizar
	Texture textureTerrainG("../Textures/grassFlowers.png");
	// Carga el mapa de bits (FIBITMAP es el tipo de dato de la libreria)
	bitmap = textureTerrainG.loadImage();
	// Convertimos el mapa de bits en un arreglo unidimensional de tipo unsigned char
	data = textureTerrainG.convertToData(bitmap, imageWidth,
			imageHeight);
	// Creando la textura con id 1
	glGenTextures(1, &textureTerrainGID);
	// Enlazar esa textura a una tipo de textura de 2D.
	glBindTexture(GL_TEXTURE_2D, textureTerrainGID);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Verifica si se pudo abrir la textura
	if (data) {
		// Transferis los datos de la imagen a memoria
		// Tipo de textura, Mipmaps, Formato interno de openGL, ancho, alto, Mipmaps,
		// Formato interno de la libreria de la imagen, el tipo de dato y al apuntador
		// a los datos
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
		GL_BGRA, GL_UNSIGNED_BYTE, data);
		// Generan los niveles del mipmap (OpenGL es el ecargado de realizarlos)
		glGenerateMipmap(GL_TEXTURE_2D);
	} else
		std::cout << "Failed to load texture" << std::endl;
	// Libera la memoria de la textura
	textureTerrainG.freeImage(bitmap);

	// Definiendo la textura a utilizar
	Texture textureTerrainB("../Textures/path.png");
	// Carga el mapa de bits (FIBITMAP es el tipo de dato de la libreria)
	bitmap = textureTerrainB.loadImage();
	// Convertimos el mapa de bits en un arreglo unidimensional de tipo unsigned char
	data = textureTerrainB.convertToData(bitmap, imageWidth,
			imageHeight);
	// Creando la textura con id 1
	glGenTextures(1, &textureTerrainBID);
	// Enlazar esa textura a una tipo de textura de 2D.
	glBindTexture(GL_TEXTURE_2D, textureTerrainBID);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Verifica si se pudo abrir la textura
	if (data) {
		// Transferis los datos de la imagen a memoria
		// Tipo de textura, Mipmaps, Formato interno de openGL, ancho, alto, Mipmaps,
		// Formato interno de la libreria de la imagen, el tipo de dato y al apuntador
		// a los datos
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
		GL_BGRA, GL_UNSIGNED_BYTE, data);
		// Generan los niveles del mipmap (OpenGL es el ecargado de realizarlos)
		glGenerateMipmap(GL_TEXTURE_2D);
	} else
		std::cout << "Failed to load texture" << std::endl;
	// Libera la memoria de la textura
	textureTerrainB.freeImage(bitmap);

	// Definiendo la textura a utilizar
	Texture textureTerrainBlendMap("../Textures/blendMap.png");
	// Carga el mapa de bits (FIBITMAP es el tipo de dato de la libreria)
	bitmap = textureTerrainBlendMap.loadImage(true);
	// Convertimos el mapa de bits en un arreglo unidimensional de tipo unsigned char
	data = textureTerrainBlendMap.convertToData(bitmap, imageWidth,
			imageHeight);
	// Creando la textura con id 1
	glGenTextures(1, &textureTerrainBlendMapID);
	// Enlazar esa textura a una tipo de textura de 2D.
	glBindTexture(GL_TEXTURE_2D, textureTerrainBlendMapID);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Verifica si se pudo abrir la textura
	if (data) {
		// Transferis los datos de la imagen a memoria
		// Tipo de textura, Mipmaps, Formato interno de openGL, ancho, alto, Mipmaps,
		// Formato interno de la libreria de la imagen, el tipo de dato y al apuntador
		// a los datos
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
		GL_BGRA, GL_UNSIGNED_BYTE, data);
		// Generan los niveles del mipmap (OpenGL es el ecargado de realizarlos)
		glGenerateMipmap(GL_TEXTURE_2D);
	} else
		std::cout << "Failed to load texture" << std::endl;
	// Libera la memoria de la textura
	textureTerrainBlendMap.freeImage(bitmap);

	Texture textureParticlesFountain("../Textures/bluewater.png");
	bitmap = textureParticlesFountain.loadImage();
	data = textureParticlesFountain.convertToData(bitmap, imageWidth, imageHeight);
	glGenTextures(1, &textureParticleFountainID);
	glBindTexture(GL_TEXTURE_2D, textureParticleFountainID);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	textureParticlesFountain.freeImage(bitmap);

	Texture textureParticleFire("../Textures/fire.png");
	bitmap = textureParticleFire.loadImage();
	data = textureParticleFire.convertToData(bitmap, imageWidth, imageHeight);
	glGenTextures(1, &textureParticleFireID);
	glBindTexture(GL_TEXTURE_2D, textureParticleFireID);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	textureParticleFire.freeImage(bitmap);

	std::uniform_real_distribution<float> distr01 = std::uniform_real_distribution<float>(0.0f, 1.0f);
	std::mt19937 generator;
	std::random_device rd;
	generator.seed(rd());
	int size = nParticlesFire * 2;
	std::vector<GLfloat> randData(size);
	for( int i = 0; i < randData.size(); i++ ) {
		randData[i] = distr01(generator);
	}

	glGenTextures(1, &texId);
	glBindTexture(GL_TEXTURE_1D, texId);
	glTexStorage1D(GL_TEXTURE_1D, 1, GL_R32F, size);
	glTexSubImage1D(GL_TEXTURE_1D, 0, 0, size, GL_RED, GL_FLOAT, randData.data());
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	shaderParticlesFire.setInt("Pass", 1);
	shaderParticlesFire.setInt("ParticleTex", 0);
	shaderParticlesFire.setInt("RandomTex", 1);
	shaderParticlesFire.setFloat("ParticleLifetime", particleLifetime);
	shaderParticlesFire.setFloat("ParticleSize", particleSize);
	shaderParticlesFire.setVectorFloat3("Accel", glm::value_ptr(glm::vec3(0.0f,0.1f,0.0f)));
	shaderParticlesFire.setVectorFloat3("Emitter", glm::value_ptr(glm::vec3(0.0f)));

	glm::mat3 basis;
	glm::vec3 u, v, n;
	v = glm::vec3(0,1,0);
	n = glm::cross(glm::vec3(1,0,0), v);
	if( glm::length(n) < 0.00001f ) {
		n = glm::cross(glm::vec3(0,1,0), v);
	}
	u = glm::cross(v,n);
	basis[0] = glm::normalize(u);
	basis[1] = glm::normalize(v);
	basis[2] = glm::normalize(n);
	shaderParticlesFire.setMatrix3("EmitterBasis", 1, false, glm::value_ptr(basis));

	/*******************************************
	 * Inicializacion de los buffers de la fuente
	 *******************************************/
	initParticleBuffers();

	/*******************************************
	 * Inicializacion de los buffers del fuego
	 *******************************************/
	initParticleBuffersFire();

	/*******************************************
	 * Inicializacion del framebuffer para
	 * almacenar el buffer de profunidadad
	 *******************************************/
	glGenFramebuffers(1, &depthMapFBO);
	glGenTextures(1, &depthMap);
	glBindTexture(GL_TEXTURE_2D, depthMap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT,
				 SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	/*glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);*/
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	float borderColor[] = { 1.0, 1.0, 1.0, 1.0 };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
	glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	/*******************************************
	 * OpenAL init
	 *******************************************/
	alutInit(0, nullptr);
	alListenerfv(AL_POSITION, listenerPos);
	alListenerfv(AL_VELOCITY, listenerVel);
	alListenerfv(AL_ORIENTATION, listenerOri);
	alGetError(); // clear any error messages
	if (alGetError() != AL_NO_ERROR) {
		printf("- Error creating buffers !!\n");
		exit(1);
	}
	else {
		printf("init() - No errors yet.");
	}
	// Config source 0
	// Generate buffers, or else no sound will happen!
	int errorAlut = alutGetError();
	if (errorAlut != ALUT_ERROR_NO_ERROR){
		printf("- Error open files with alut %d !!\n", errorAlut);
		exit(2);
	}


	alGetError(); /* clear error */
	alGenSources(NUM_SOURCES, source);

	if (alGetError() != AL_NO_ERROR) {
		printf("- Error creating sources !!\n");
		exit(2);
	}
	else {
		printf("init - no errors after alGenSources\n");
	}
	alSourcef(source[0], AL_PITCH, 1.0f);
	alSourcef(source[0], AL_GAIN, 3.0f);
	alSourcefv(source[0], AL_POSITION, source0Pos);
	alSourcefv(source[0], AL_VELOCITY, source0Vel);
	alSourcei(source[0], AL_BUFFER, buffer[0]);
	alSourcei(source[0], AL_LOOPING, AL_TRUE);
	alSourcef(source[0], AL_MAX_DISTANCE, 2000);

	alSourcef(source[1], AL_PITCH, 1.0f);
	alSourcef(source[1], AL_GAIN, 3.0f);
	alSourcefv(source[1], AL_POSITION, source1Pos);
	alSourcefv(source[1], AL_VELOCITY, source1Vel);
	alSourcei(source[1], AL_BUFFER, buffer[1]);
	alSourcei(source[1], AL_LOOPING, AL_TRUE);
	alSourcef(source[1], AL_MAX_DISTANCE, 2000);

	alSourcef(source[2], AL_PITCH, 1.0f);
	alSourcef(source[2], AL_GAIN, 0.3f);
	alSourcefv(source[2], AL_POSITION, source2Pos);
	alSourcefv(source[2], AL_VELOCITY, source2Vel);
	alSourcei(source[2], AL_BUFFER, buffer[2]);
	alSourcei(source[2], AL_LOOPING, AL_TRUE);
	alSourcef(source[2], AL_MAX_DISTANCE, 500);

	alSourcef(source[3], AL_PITCH, 1.0f);
	alSourcef(source[3], AL_GAIN, 1.0f);
	alSourcefv(source[3], AL_POSITION, source3Pos);
	alSourcefv(source[3], AL_VELOCITY, source3Vel);
	alSourcei(source[3], AL_BUFFER, buffer[3]);
	alSourcei(source[3], AL_LOOPING, AL_TRUE);
	alSourcef(source[3], AL_MAX_DISTANCE, 500);
}

void destroy() {
	glfwDestroyWindow(window);
	glfwTerminate();
	// --------- IMPORTANTE ----------
	// Eliminar los shader y buffers creados.

	// Shaders Delete
	shader.destroy();
	shaderMulLighting.destroy();
	shaderSkybox.destroy();
	shaderTerrain.destroy();
	shaderParticlesFountain.destroy();
	shaderParticlesFire.destroy();

	// Basic objects Delete
	skyboxSphere.destroy();
	boxCollider.destroy();
	sphereCollider.destroy();
	boxViewDepth.destroy();

	// Terrains objects Delete
	terrain.destroy();

	// Custom objects Delete

	// Custom objects animate
	mayowModelAnimate.destroy();
	
	modelBoo1.destroy();
	modelBoo2.destroy();
	modelBoo3.destroy();
	modelBoo4.destroy();

	modelCuerpo.destroy();
	
	// Laberinto delete
	modelPEA.destroy();
	modelPEB.destroy();
	modelPEI.destroy();
	modelPED.destroy();
	modelPC1.destroy();
	modelPC2.destroy();
	modelPC3.destroy();
	modelPC4.destroy();
	modelPC5.destroy();
	modelPC6.destroy();
	modelPC7.destroy();
	modelPC8.destroy();
	modelPC9.destroy();
	modelPC10.destroy();
	modelPC11.destroy();
	modelPC12.destroy();
	modelPC13.destroy();
	modelPC14.destroy();
	modelPC15.destroy();
	modelPC16.destroy();
	modelPC17.destroy();
	modelPC18.destroy();
	modelPC19.destroy();
	modelPC20.destroy();
	modelPC21.destroy();
	modelPC22.destroy();
	modelPC23.destroy();
	modelPC24.destroy();
	modelPC25.destroy();
	modelPC26.destroy();
	modelPC27.destroy();
	modelPC28.destroy();
	modelPC29.destroy();
	modelPC30.destroy();
	modelPC31.destroy();
	modelPC32.destroy();
	modelPC33.destroy();
	modelPC34.destroy();
	modelPC35.destroy();
	modelPC36.destroy();
	modelPC37.destroy();
	modelPC38.destroy();
	modelPC39.destroy();
	modelPC40.destroy();
	modelPC41.destroy();
	modelPC42.destroy();
	modelPC43.destroy();
	modelPC44.destroy();
	modelPC45.destroy();
	modelPC46.destroy();
	modelPC47.destroy();
	modelPC48.destroy();
	modelPC49.destroy();
	modelPC50.destroy();
	modelPC51.destroy();
	modelPC52.destroy();
	modelPC53.destroy();
	modelPC54.destroy();
	modelPC55.destroy();
	modelPC56.destroy();
	modelPC57.destroy();
	modelPC58.destroy();
	modelPC59.destroy();
	modelPC60.destroy();
	modelPC61.destroy();
	modelPC62.destroy();
	modelPC63.destroy();
	modelPC64.destroy();
	modelPC65.destroy();
	modelPC66.destroy();
	modelPC67.destroy();
	modelPC68.destroy();
	modelPC69.destroy();
	modelPC70.destroy();
	modelPC71.destroy();
	modelPC72.destroy();
	modelPC73.destroy();
	modelPC74.destroy();
	modelPC75.destroy();
	modelPC76.destroy();
	modelPC77.destroy();
	modelPC78.destroy();
	modelPC79.destroy();
	modelPC80.destroy();
	modelPC81.destroy();
	modelPC82.destroy();
	modelPC83.destroy();
	modelPC84.destroy();
	modelPC85.destroy();
	modelPC86.destroy();
	modelPC87.destroy();
	modelPC88.destroy();
	modelPC89.destroy();
	modelPC90.destroy();
	modelPC91.destroy();
	modelPC92.destroy();
	modelPC93.destroy();
	modelPC94.destroy();
	modelPC95.destroy();
	modelPC96.destroy();
	modelPC97.destroy();
	modelPC98.destroy();
	modelPC99.destroy();
	modelPC100.destroy();
	modelPC101.destroy();
	modelPC102.destroy();
	modelPC103.destroy();
	modelPC104.destroy();
	modelPC105.destroy();
	modelPC106.destroy();
	modelPC107.destroy();
	modelPC108.destroy();
	modelPC109.destroy();
	modelPC110.destroy();
	modelPC111.destroy();
	modelPC112.destroy();
	modelPC113.destroy();
	modelPC114.destroy();
	modelPC115.destroy();
	modelPC116.destroy();
	modelPC117.destroy();
	modelPC118.destroy();
	modelPC119.destroy();
	modelPC120.destroy();
	modelPC121.destroy();
	modelPC122.destroy();
	modelPC123.destroy();
	modelPC124.destroy();
	modelPC125.destroy();
	modelPC126.destroy();
	modelPC127.destroy();
	modelPC128.destroy();
	modelPC129.destroy();
	modelPC130.destroy();
	modelPC131.destroy();
	modelPC132.destroy();
	modelPC133.destroy();
	modelPC134.destroy();
	modelPC135.destroy();
	modelPC136.destroy();
	modelPC137.destroy();
	modelPC138.destroy();
	modelPC139.destroy();
	modelPC140.destroy();
	modelPC141.destroy();
	modelPC142.destroy();
	modelPC143.destroy();
	modelPC144.destroy();
	modelPC145.destroy();
	modelPC146.destroy();
	modelPC147.destroy();
	modelPC148.destroy();
	modelPC149.destroy();
	modelPC150.destroy();
	modelPC151.destroy();
	modelPC152.destroy();
	modelPC153.destroy();
	modelPC154.destroy();
	modelPC155.destroy();
	modelPC156.destroy();
	modelPC157.destroy();
	modelPC158.destroy();
	modelPC159.destroy();
	modelPC160.destroy();
	modelPC161.destroy();
	modelPC162.destroy();
	modelPC163.destroy();
	modelPC164.destroy();
	modelPC165.destroy();
	modelPC166.destroy();
	modelPC167.destroy();
	modelPC168.destroy();
	modelPC169.destroy();
	modelPC170.destroy();
	modelPC171.destroy();
	modelPC172.destroy();
	modelPC173.destroy();
	modelPC174.destroy();
	modelPC175.destroy();
	modelPC176.destroy();
	modelPC177.destroy();
	modelPC178.destroy();
	modelPC179.destroy();
	modelPC180.destroy();
	modelPC181.destroy();
	modelPC182.destroy();
	modelPC183.destroy();
	modelPC184.destroy();
	modelPC185.destroy();
	modelPC186.destroy();
	
	
	// Textures Delete
	glBindTexture(GL_TEXTURE_2D, 0);
	glDeleteTextures(1, &textureCespedID);
	glDeleteTextures(1, &textureWallID);
	glDeleteTextures(1, &textureWindowID);
	glDeleteTextures(1, &textureHighwayID);
	glDeleteTextures(1, &textureLandingPadID);
	glDeleteTextures(1, &textureTerrainBackgroundID);
	glDeleteTextures(1, &textureTerrainRID);
	glDeleteTextures(1, &textureTerrainGID);
	glDeleteTextures(1, &textureTerrainBID);
	glDeleteTextures(1, &textureTerrainBlendMapID);
	glDeleteTextures(1, &textureParticleFountainID);
	glDeleteTextures(1, &textureParticleFireID);

	// Cube Maps Delete
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	glDeleteTextures(1, &skyboxTextureID);

	// Remove the buffer of the fountain particles
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &initVel);
	glDeleteBuffers(1, &startTime);
	glBindVertexArray(0);
	glDeleteVertexArrays(1, &VAOParticles);

	// Remove the buffer of the fire particles
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(2, posBuf);
	glDeleteBuffers(2, velBuf);
	glDeleteBuffers(2, age);
	glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, 0);
	glDeleteTransformFeedbacks(2, feedback);
	glBindVertexArray(0);
	glDeleteVertexArrays(1, &VAOParticlesFire);
}

void reshapeCallback(GLFWwindow *Window, int widthRes, int heightRes) {
	screenWidth = widthRes;
	screenHeight = heightRes;
	glViewport(0, 0, widthRes, heightRes);
}

void keyCallback(GLFWwindow *window, int key, int scancode, int action,
		int mode) {
	if (action == GLFW_PRESS) {
		switch (key) {
		case GLFW_KEY_ESCAPE:
			exitApp = true;
			break;
		}
	}
}

void mouseCallback(GLFWwindow *window, double xpos, double ypos) {
	offsetX = xpos - lastMousePosX;
	offsetY = ypos - lastMousePosY;
	lastMousePosX = xpos;
	lastMousePosY = ypos;
}

void scrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
	distanceFromTarget -= yoffset;
	if (distanceFromTarget > 5.0)
		distanceFromTarget = 5.0;
	camera->setDistanceFromTarget(distanceFromTarget);
}

void mouseButtonCallback(GLFWwindow *window, int button, int state, int mod) {
	if (state == GLFW_PRESS) {
		switch (button) {
		case GLFW_MOUSE_BUTTON_RIGHT:
			std::cout << "lastMousePos.y:" << lastMousePosY << std::endl;
			break;
		case GLFW_MOUSE_BUTTON_LEFT:
			std::cout << "lastMousePos.x:" << lastMousePosX << std::endl;
			break;
		case GLFW_MOUSE_BUTTON_MIDDLE:
			std::cout << "lastMousePos.x:" << lastMousePosX << std::endl;
			std::cout << "lastMousePos.y:" << lastMousePosY << std::endl;
			break;
		}
	}
}

bool processInput(bool continueApplication) {
	if (exitApp || glfwWindowShouldClose(window) != 0) {
		return false;
	}

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
		camera->mouseMoveCamera(offsetX, offsetY, deltaTime);
	}
	offsetX = 0;
	offsetY = 0;

	// Seleccionar modelo
	if (enableCountSelected && glfwGetKey(window, GLFW_KEY_TAB) == GLFW_PRESS){
		enableCountSelected = false;
		modelSelected++;
		std::cout << "modelSelected:" << modelSelected << std::endl;
	}
	else if(glfwGetKey(window, GLFW_KEY_TAB) == GLFW_RELEASE)
		enableCountSelected = true;


	if (modelSelected == 2 && glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
		modelMatrixMayow = glm::rotate(modelMatrixMayow, glm::radians(4.0f), glm::vec3(0, 1, 0));
		animationIndex = 0;
	}else if (modelSelected == 2 && glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
		modelMatrixMayow = glm::rotate(modelMatrixMayow, glm::radians(-4.0f), glm::vec3(0, 1, 0));
		animationIndex = 0;
	}if (modelSelected == 2 && glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
		modelMatrixMayow = glm::translate(modelMatrixMayow, glm::vec3(0, 0, 0.2));
		animationIndex = 0;
	}else if (modelSelected == 2 && glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
		modelMatrixMayow = glm::translate(modelMatrixMayow, glm::vec3(0, 0, -0.2));
		animationIndex = 0;
	}

	glfwPollEvents();
	return continueApplication;
}

void applicationLoop() {
	bool psi = true;

	glm::mat4 view;
	glm::vec3 axis;
	glm::vec3 target;
	float angleTarget;

	modelMatrixMayow = glm::translate(modelMatrixMayow, glm::vec3(-2.5f, 0.0f, -5.5f));
	modelMatrixMayow = glm::rotate(modelMatrixMayow, glm::radians(180.0f), glm::vec3(0, 1, 0));
	
	modelMatrixBoo1 = glm::translate(modelMatrixBoo1, glm::vec3(0, 0, 0));
	modelMatrixBoo2 = glm::translate(modelMatrixBoo2, glm::vec3(0, 0, 0));
	modelMatrixBoo3 = glm::translate(modelMatrixBoo3, glm::vec3(0, 0, 0));
	modelMatrixBoo4 = glm::translate(modelMatrixBoo4, glm::vec3(0, 0, 0));

	modelMatrixCuerpo = glm::translate(modelMatrixCuerpo, glm::vec3(0, 0, 0));
	
	// Laberinto
	modelMatrixPEA = glm::translate(modelMatrixPEA, glm::vec3(0, 0, 0));
	modelMatrixPEB = glm::translate(modelMatrixPEB, glm::vec3(0, 0, 0));
	modelMatrixPEI = glm::translate(modelMatrixPEI, glm::vec3(0, 0, 0));
	modelMatrixPED = glm::translate(modelMatrixPED, glm::vec3(0, 0, 0));
	modelMatrixPC1 = glm::translate(modelMatrixPC1, glm::vec3(0, 0, 0));
	modelMatrixPC2 = glm::translate(modelMatrixPC2, glm::vec3(0, 0, 0));
	modelMatrixPC3 = glm::translate(modelMatrixPC3, glm::vec3(0, 0, 0));
	modelMatrixPC4 = glm::translate(modelMatrixPC4, glm::vec3(0, 0, 0));
	modelMatrixPC5 = glm::translate(modelMatrixPC5, glm::vec3(0, 0, 0));
	modelMatrixPC6 = glm::translate(modelMatrixPC6, glm::vec3(0, 0, 0));
	modelMatrixPC7 = glm::translate(modelMatrixPC7, glm::vec3(0, 0, 0));
	modelMatrixPC8 = glm::translate(modelMatrixPC8, glm::vec3(0, 0, 0));
	modelMatrixPC9 = glm::translate(modelMatrixPC8, glm::vec3(0, 0, 0));
	modelMatrixPC10 = glm::translate(modelMatrixPC10, glm::vec3(0, 0, 0));
	modelMatrixPC11 = glm::translate(modelMatrixPC11, glm::vec3(0, 0, 0));
	modelMatrixPC12 = glm::translate(modelMatrixPC12, glm::vec3(0, 0, 0));
	modelMatrixPC13 = glm::translate(modelMatrixPC13, glm::vec3(0, 0, 0));
	modelMatrixPC14 = glm::translate(modelMatrixPC14, glm::vec3(0, 0, 0));
	modelMatrixPC15 = glm::translate(modelMatrixPC15, glm::vec3(0, 0, 0));
	modelMatrixPC16 = glm::translate(modelMatrixPC16, glm::vec3(0, 0, 0));
	modelMatrixPC17 = glm::translate(modelMatrixPC17, glm::vec3(0, 0, 0));
	modelMatrixPC18 = glm::translate(modelMatrixPC18, glm::vec3(0, 0, 0));
	modelMatrixPC19 = glm::translate(modelMatrixPC19, glm::vec3(0, 0, 0));
	modelMatrixPC20 = glm::translate(modelMatrixPC20, glm::vec3(0, 0, 0));
	modelMatrixPC21 = glm::translate(modelMatrixPC21, glm::vec3(0, 0, 0));
	modelMatrixPC22 = glm::translate(modelMatrixPC22, glm::vec3(0, 0, 0));
	modelMatrixPC23 = glm::translate(modelMatrixPC23, glm::vec3(0, 0, 0));
	modelMatrixPC24 = glm::translate(modelMatrixPC24, glm::vec3(0, 0, 0));
	modelMatrixPC25 = glm::translate(modelMatrixPC25, glm::vec3(0, 0, 0));
	modelMatrixPC26 = glm::translate(modelMatrixPC26, glm::vec3(0, 0, 0));
	modelMatrixPC27 = glm::translate(modelMatrixPC27, glm::vec3(0, 0, 0));
	modelMatrixPC28 = glm::translate(modelMatrixPC28, glm::vec3(0, 0, 0));
	modelMatrixPC29 = glm::translate(modelMatrixPC29, glm::vec3(0, 0, 0));
	modelMatrixPC30 = glm::translate(modelMatrixPC30, glm::vec3(0, 0, 0));
	modelMatrixPC31 = glm::translate(modelMatrixPC31, glm::vec3(0, 0, 0));
	modelMatrixPC32 = glm::translate(modelMatrixPC32, glm::vec3(0, 0, 0));
	modelMatrixPC33 = glm::translate(modelMatrixPC33, glm::vec3(0, 0, 0));
	modelMatrixPC34 = glm::translate(modelMatrixPC34, glm::vec3(0, 0, 0));
	modelMatrixPC35 = glm::translate(modelMatrixPC35, glm::vec3(0, 0, 0));
	modelMatrixPC36 = glm::translate(modelMatrixPC36, glm::vec3(0, 0, 0));
	modelMatrixPC37 = glm::translate(modelMatrixPC37, glm::vec3(0, 0, 0));
	modelMatrixPC38 = glm::translate(modelMatrixPC38, glm::vec3(0, 0, 0));
	modelMatrixPC39 = glm::translate(modelMatrixPC39, glm::vec3(0, 0, 0));
	modelMatrixPC40 = glm::translate(modelMatrixPC40, glm::vec3(0, 0, 0));
	modelMatrixPC41 = glm::translate(modelMatrixPC41, glm::vec3(0, 0, 0));
	modelMatrixPC42 = glm::translate(modelMatrixPC42, glm::vec3(0, 0, 0));
	modelMatrixPC43 = glm::translate(modelMatrixPC43, glm::vec3(0, 0, 0));
	modelMatrixPC44 = glm::translate(modelMatrixPC44, glm::vec3(0, 0, 0));
	modelMatrixPC45 = glm::translate(modelMatrixPC45, glm::vec3(0, 0, 0));
	modelMatrixPC46 = glm::translate(modelMatrixPC46, glm::vec3(0, 0, 0));
	modelMatrixPC47 = glm::translate(modelMatrixPC47, glm::vec3(0, 0, 0));
	modelMatrixPC48 = glm::translate(modelMatrixPC48, glm::vec3(0, 0, 0));
	modelMatrixPC49 = glm::translate(modelMatrixPC49, glm::vec3(0, 0, 0));
	modelMatrixPC50 = glm::translate(modelMatrixPC50, glm::vec3(0, 0, 0));
	modelMatrixPC51 = glm::translate(modelMatrixPC51, glm::vec3(0, 0, 0));
	modelMatrixPC52 = glm::translate(modelMatrixPC52, glm::vec3(0, 0, 0));
	modelMatrixPC53 = glm::translate(modelMatrixPC53, glm::vec3(0, 0, 0));
	modelMatrixPC54 = glm::translate(modelMatrixPC54, glm::vec3(0, 0, 0));
	modelMatrixPC55 = glm::translate(modelMatrixPC55, glm::vec3(0, 0, 0));
	modelMatrixPC56 = glm::translate(modelMatrixPC56, glm::vec3(0, 0, 0));
	modelMatrixPC57 = glm::translate(modelMatrixPC57, glm::vec3(0, 0, 0));
	modelMatrixPC58 = glm::translate(modelMatrixPC58, glm::vec3(0, 0, 0));
	modelMatrixPC59 = glm::translate(modelMatrixPC59, glm::vec3(0, 0, 0));
	modelMatrixPC60 = glm::translate(modelMatrixPC60, glm::vec3(0, 0, 0));
	modelMatrixPC61 = glm::translate(modelMatrixPC61, glm::vec3(0, 0, 0));
	modelMatrixPC62 = glm::translate(modelMatrixPC62, glm::vec3(0, 0, 0));
	modelMatrixPC63 = glm::translate(modelMatrixPC63, glm::vec3(0, 0, 0));
	modelMatrixPC64 = glm::translate(modelMatrixPC64, glm::vec3(0, 0, 0));
	modelMatrixPC65 = glm::translate(modelMatrixPC65, glm::vec3(0, 0, 0));
	modelMatrixPC66 = glm::translate(modelMatrixPC66, glm::vec3(0, 0, 0));
	modelMatrixPC67 = glm::translate(modelMatrixPC67, glm::vec3(0, 0, 0));
	modelMatrixPC68 = glm::translate(modelMatrixPC68, glm::vec3(0, 0, 0));
	modelMatrixPC69 = glm::translate(modelMatrixPC69, glm::vec3(0, 0, 0));
	modelMatrixPC70 = glm::translate(modelMatrixPC70, glm::vec3(0, 0, 0));
	modelMatrixPC71 = glm::translate(modelMatrixPC71, glm::vec3(0, 0, 0));
	modelMatrixPC72 = glm::translate(modelMatrixPC72, glm::vec3(0, 0, 0));
	modelMatrixPC73 = glm::translate(modelMatrixPC73, glm::vec3(0, 0, 0));
	modelMatrixPC74 = glm::translate(modelMatrixPC74, glm::vec3(0, 0, 0));
	modelMatrixPC75 = glm::translate(modelMatrixPC75, glm::vec3(0, 0, 0));
	modelMatrixPC76 = glm::translate(modelMatrixPC76, glm::vec3(0, 0, 0));
	modelMatrixPC77 = glm::translate(modelMatrixPC77, glm::vec3(0, 0, 0));
	modelMatrixPC78 = glm::translate(modelMatrixPC78, glm::vec3(0, 0, 0));
	modelMatrixPC79 = glm::translate(modelMatrixPC79, glm::vec3(0, 0, 0));
	modelMatrixPC80 = glm::translate(modelMatrixPC80, glm::vec3(0, 0, 0));
	modelMatrixPC81 = glm::translate(modelMatrixPC81, glm::vec3(0, 0, 0));
	modelMatrixPC82 = glm::translate(modelMatrixPC82, glm::vec3(0, 0, 0));
	modelMatrixPC83 = glm::translate(modelMatrixPC83, glm::vec3(0, 0, 0));
	modelMatrixPC84 = glm::translate(modelMatrixPC84, glm::vec3(0, 0, 0));
	modelMatrixPC85 = glm::translate(modelMatrixPC85, glm::vec3(0, 0, 0));
	modelMatrixPC86 = glm::translate(modelMatrixPC86, glm::vec3(0, 0, 0));
	modelMatrixPC87 = glm::translate(modelMatrixPC87, glm::vec3(0, 0, 0));
	modelMatrixPC88 = glm::translate(modelMatrixPC88, glm::vec3(0, 0, 0));
	modelMatrixPC89 = glm::translate(modelMatrixPC89, glm::vec3(0, 0, 0));
	modelMatrixPC90 = glm::translate(modelMatrixPC90, glm::vec3(0, 0, 0));
	modelMatrixPC91 = glm::translate(modelMatrixPC91, glm::vec3(0, 0, 0));
	modelMatrixPC92 = glm::translate(modelMatrixPC92, glm::vec3(0, 0, 0));
	modelMatrixPC93 = glm::translate(modelMatrixPC93, glm::vec3(0, 0, 0));
	modelMatrixPC94 = glm::translate(modelMatrixPC94, glm::vec3(0, 0, 0));
	modelMatrixPC95 = glm::translate(modelMatrixPC95, glm::vec3(0, 0, 0));
	modelMatrixPC96 = glm::translate(modelMatrixPC96, glm::vec3(0, 0, 0));
	modelMatrixPC97 = glm::translate(modelMatrixPC97, glm::vec3(0, 0, 0));
	modelMatrixPC98 = glm::translate(modelMatrixPC98, glm::vec3(0, 0, 0));
	modelMatrixPC99 = glm::translate(modelMatrixPC99, glm::vec3(0, 0, 0));
	modelMatrixPC100 = glm::translate(modelMatrixPC100, glm::vec3(0, 0, 0));
	modelMatrixPC101 = glm::translate(modelMatrixPC101, glm::vec3(0, 0, 0));
	modelMatrixPC102 = glm::translate(modelMatrixPC102, glm::vec3(0, 0, 0));
	modelMatrixPC103 = glm::translate(modelMatrixPC103, glm::vec3(0, 0, 0));
	modelMatrixPC104 = glm::translate(modelMatrixPC104, glm::vec3(0, 0, 0));
	modelMatrixPC105 = glm::translate(modelMatrixPC105, glm::vec3(0, 0, 0));
	modelMatrixPC106 = glm::translate(modelMatrixPC106, glm::vec3(0, 0, 0));
	modelMatrixPC107 = glm::translate(modelMatrixPC107, glm::vec3(0, 0, 0));
	modelMatrixPC108 = glm::translate(modelMatrixPC108, glm::vec3(0, 0, 0));
	modelMatrixPC109 = glm::translate(modelMatrixPC108, glm::vec3(0, 0, 0));
	modelMatrixPC110 = glm::translate(modelMatrixPC110, glm::vec3(0, 0, 0));
	modelMatrixPC111 = glm::translate(modelMatrixPC111, glm::vec3(0, 0, 0));
	modelMatrixPC112 = glm::translate(modelMatrixPC112, glm::vec3(0, 0, 0));
	modelMatrixPC113 = glm::translate(modelMatrixPC113, glm::vec3(0, 0, 0));
	modelMatrixPC114 = glm::translate(modelMatrixPC114, glm::vec3(0, 0, 0));
	modelMatrixPC115 = glm::translate(modelMatrixPC115, glm::vec3(0, 0, 0));
	modelMatrixPC116 = glm::translate(modelMatrixPC116, glm::vec3(0, 0, 0));
	modelMatrixPC117 = glm::translate(modelMatrixPC117, glm::vec3(0, 0, 0));
	modelMatrixPC118 = glm::translate(modelMatrixPC118, glm::vec3(0, 0, 0));
	modelMatrixPC119 = glm::translate(modelMatrixPC119, glm::vec3(0, 0, 0));
	modelMatrixPC120 = glm::translate(modelMatrixPC120, glm::vec3(0, 0, 0));
	modelMatrixPC121 = glm::translate(modelMatrixPC121, glm::vec3(0, 0, 0));
	modelMatrixPC122 = glm::translate(modelMatrixPC122, glm::vec3(0, 0, 0));
	modelMatrixPC123 = glm::translate(modelMatrixPC123, glm::vec3(0, 0, 0));
	modelMatrixPC124 = glm::translate(modelMatrixPC124, glm::vec3(0, 0, 0));
	modelMatrixPC125 = glm::translate(modelMatrixPC125, glm::vec3(0, 0, 0));
	modelMatrixPC126 = glm::translate(modelMatrixPC126, glm::vec3(0, 0, 0));
	modelMatrixPC127 = glm::translate(modelMatrixPC127, glm::vec3(0, 0, 0));
	modelMatrixPC128 = glm::translate(modelMatrixPC128, glm::vec3(0, 0, 0));
	modelMatrixPC129 = glm::translate(modelMatrixPC129, glm::vec3(0, 0, 0));
	modelMatrixPC130 = glm::translate(modelMatrixPC130, glm::vec3(0, 0, 0));
	modelMatrixPC131 = glm::translate(modelMatrixPC131, glm::vec3(0, 0, 0));
	modelMatrixPC132 = glm::translate(modelMatrixPC132, glm::vec3(0, 0, 0));
	modelMatrixPC133 = glm::translate(modelMatrixPC133, glm::vec3(0, 0, 0));
	modelMatrixPC134 = glm::translate(modelMatrixPC134, glm::vec3(0, 0, 0));
	modelMatrixPC135 = glm::translate(modelMatrixPC135, glm::vec3(0, 0, 0));
	modelMatrixPC136 = glm::translate(modelMatrixPC136, glm::vec3(0, 0, 0));
	modelMatrixPC137 = glm::translate(modelMatrixPC137, glm::vec3(0, 0, 0));
	modelMatrixPC138 = glm::translate(modelMatrixPC138, glm::vec3(0, 0, 0));
	modelMatrixPC139 = glm::translate(modelMatrixPC139, glm::vec3(0, 0, 0));
	modelMatrixPC140 = glm::translate(modelMatrixPC140, glm::vec3(0, 0, 0));
	modelMatrixPC141 = glm::translate(modelMatrixPC141, glm::vec3(0, 0, 0));
	modelMatrixPC142 = glm::translate(modelMatrixPC142, glm::vec3(0, 0, 0));
	modelMatrixPC143 = glm::translate(modelMatrixPC143, glm::vec3(0, 0, 0));
	modelMatrixPC144 = glm::translate(modelMatrixPC144, glm::vec3(0, 0, 0));
	modelMatrixPC145 = glm::translate(modelMatrixPC145, glm::vec3(0, 0, 0));
	modelMatrixPC146 = glm::translate(modelMatrixPC146, glm::vec3(0, 0, 0));
	modelMatrixPC147 = glm::translate(modelMatrixPC147, glm::vec3(0, 0, 0));
	modelMatrixPC148 = glm::translate(modelMatrixPC148, glm::vec3(0, 0, 0));
	modelMatrixPC149 = glm::translate(modelMatrixPC149, glm::vec3(0, 0, 0));
	modelMatrixPC150 = glm::translate(modelMatrixPC150, glm::vec3(0, 0, 0));
	modelMatrixPC151 = glm::translate(modelMatrixPC151, glm::vec3(0, 0, 0));
	modelMatrixPC152 = glm::translate(modelMatrixPC152, glm::vec3(0, 0, 0));
	modelMatrixPC153 = glm::translate(modelMatrixPC153, glm::vec3(0, 0, 0));
	modelMatrixPC154 = glm::translate(modelMatrixPC154, glm::vec3(0, 0, 0));
	modelMatrixPC155 = glm::translate(modelMatrixPC155, glm::vec3(0, 0, 0));
	modelMatrixPC156 = glm::translate(modelMatrixPC156, glm::vec3(0, 0, 0));
	modelMatrixPC157 = glm::translate(modelMatrixPC157, glm::vec3(0, 0, 0));
	modelMatrixPC158 = glm::translate(modelMatrixPC158, glm::vec3(0, 0, 0));
	modelMatrixPC159 = glm::translate(modelMatrixPC159, glm::vec3(0, 0, 0));
	modelMatrixPC160 = glm::translate(modelMatrixPC160, glm::vec3(0, 0, 0));
	modelMatrixPC161 = glm::translate(modelMatrixPC161, glm::vec3(0, 0, 0));
	modelMatrixPC162 = glm::translate(modelMatrixPC162, glm::vec3(0, 0, 0));
	modelMatrixPC163 = glm::translate(modelMatrixPC163, glm::vec3(0, 0, 0));
	modelMatrixPC164 = glm::translate(modelMatrixPC164, glm::vec3(0, 0, 0));
	modelMatrixPC165 = glm::translate(modelMatrixPC165, glm::vec3(0, 0, 0));
	modelMatrixPC166 = glm::translate(modelMatrixPC166, glm::vec3(0, 0, 0));
	modelMatrixPC167 = glm::translate(modelMatrixPC167, glm::vec3(0, 0, 0));
	modelMatrixPC168 = glm::translate(modelMatrixPC168, glm::vec3(0, 0, 0));
	modelMatrixPC169 = glm::translate(modelMatrixPC169, glm::vec3(0, 0, 0));
	modelMatrixPC170 = glm::translate(modelMatrixPC170, glm::vec3(0, 0, 0));
	modelMatrixPC171 = glm::translate(modelMatrixPC171, glm::vec3(0, 0, 0));
	modelMatrixPC172 = glm::translate(modelMatrixPC172, glm::vec3(0, 0, 0));
	modelMatrixPC173 = glm::translate(modelMatrixPC173, glm::vec3(0, 0, 0));
	modelMatrixPC174 = glm::translate(modelMatrixPC174, glm::vec3(0, 0, 0));
	modelMatrixPC175 = glm::translate(modelMatrixPC175, glm::vec3(0, 0, 0));
	modelMatrixPC176 = glm::translate(modelMatrixPC176, glm::vec3(0, 0, 0));
	modelMatrixPC177 = glm::translate(modelMatrixPC177, glm::vec3(0, 0, 0));
	modelMatrixPC178 = glm::translate(modelMatrixPC178, glm::vec3(0, 0, 0));
	modelMatrixPC179 = glm::translate(modelMatrixPC179, glm::vec3(0, 0, 0));
	modelMatrixPC180 = glm::translate(modelMatrixPC180, glm::vec3(0, 0, 0));
	modelMatrixPC181 = glm::translate(modelMatrixPC181, glm::vec3(0, 0, 0));
	modelMatrixPC182 = glm::translate(modelMatrixPC182, glm::vec3(0, 0, 0));
	modelMatrixPC183 = glm::translate(modelMatrixPC183, glm::vec3(0, 0, 0));
	modelMatrixPC184 = glm::translate(modelMatrixPC184, glm::vec3(0, 0, 0));
	modelMatrixPC185 = glm::translate(modelMatrixPC185, glm::vec3(0, 0, 0));
	modelMatrixPC186 = glm::translate(modelMatrixPC186, glm::vec3(0, 0, 0));

	lastTime = TimeManager::Instance().GetTime();

	// Time for the particles animation
	currTimeParticlesAnimation = lastTime;
	lastTimeParticlesAnimation = lastTime;

	currTimeParticlesAnimationFire = lastTime;
	lastTimeParticlesAnimationFire = lastTime;

	glm::vec3 lightPos = glm::vec3(10.0, 10.0, 0.0);

	// Posicion light, apuntador a la camara, distancia maximo de alcance, plano cercano y el FOV (Field of view)
	shadowBox = new ShadowBox(-lightPos, camera.get(), 15.0f, 0.1, 45.0f);

	while (psi) {
		currTime = TimeManager::Instance().GetTime();
		if(currTime - lastTime < 0.016666667){
			glfwPollEvents();
			continue;
		}
		lastTime = currTime;
		TimeManager::Instance().CalculateFrameRate(true);
		deltaTime = TimeManager::Instance().DeltaTime;
		psi = processInput(true);

		std::map<std::string, bool> collisionDetection;

		glm::mat4 projection = glm::perspective(glm::radians(45.0f),
				(float) screenWidth / (float) screenHeight, 0.1f, 100.0f);

		if(modelSelected == 1){
		}
		else{
			axis = glm::axis(glm::quat_cast(modelMatrixMayow));
			angleTarget = glm::angle(glm::quat_cast(modelMatrixMayow));
			target = modelMatrixMayow[3] + glm::vec4(0.0, 2.0, 0.0, 0.0);
		}

		if(std::isnan(angleTarget))
			angleTarget = 0.0;
		if(axis.y < 0)
			angleTarget = -angleTarget;
		if(modelSelected == 1)
			angleTarget -= glm::radians(90.0f);
		camera->setCameraTarget(target);
		camera->setAngleTarget(angleTarget);
		camera->updateCamera();
		view = camera->getViewMatrix();

		// Se actualiza la caja usando las dimensiones del viewport
		shadowBox->update(screenWidth, screenHeight);
		shadowBox->getCenter();

		// Projection light shadow mapping
		//glm::mat4 lightProjection, lightView;
		//glm::mat4 lightSpaceMatrix;
		//float near_plane = 0.1f, far_plane = 20.0f;
		////lightProjection = glm::perspective(glm::radians(45.0f), (GLfloat)SHADOW_WIDTH / (GLfloat)SHADOW_HEIGHT, near_plane, far_plane); // note that if you use a perspective projection matrix you'll have to change the light position as the current light position isn't enough to reflect the whole scene
		//lightProjection = glm::ortho(-25.0f, 25.0f, -25.0f, 25.0f, near_plane, far_plane);
		//lightView = glm::lookAt(lightPos, glm::vec3(0.0f), glm::vec3(0.0, 1.0, 0.0));
		glm::mat4 lightProjection = glm::mat4(1.0), lightView = glm::mat4(1.0f);
		glm::mat4 lightSpaceMatrix;
		lightProjection[0][0] = 2.0 / shadowBox->getWidth();
		lightProjection[1][1] = 2.0 / shadowBox->getHeight();
		lightProjection[2][2] = -2.0 / shadowBox->getLength();
		lightProjection[3][3] = 1.0;
		lightView = glm::lookAt(shadowBox->getCenter(), shadowBox->getCenter() + glm::normalize(-lightPos), glm::vec3(0, 1.0f, 0));
		lightSpaceMatrix = lightProjection * lightView;
		shaderDepth.setMatrix4("lightSpaceMatrix", 1, false, glm::value_ptr(lightSpaceMatrix));

		// Settea la matriz de vista y projection al shader con solo color
		shader.setMatrix4("projection", 1, false, glm::value_ptr(projection));
		shader.setMatrix4("view", 1, false, glm::value_ptr(view));

		// Settea la matriz de vista y projection al shader con skybox
		shaderSkybox.setMatrix4("projection", 1, false,
				glm::value_ptr(projection));
		shaderSkybox.setMatrix4("view", 1, false,
				glm::value_ptr(glm::mat4(glm::mat3(view))));
		// Settea la matriz de vista y projection al shader con multiples luces
		shaderMulLighting.setMatrix4("projection", 1, false,
					glm::value_ptr(projection));
		shaderMulLighting.setMatrix4("view", 1, false,
				glm::value_ptr(view));
		shaderMulLighting.setMatrix4("lightSpaceMatrix", 1, false,
				glm::value_ptr(lightSpaceMatrix));
		// Settea la matriz de vista y projection al shader con multiples luces
		shaderTerrain.setMatrix4("projection", 1, false,
					glm::value_ptr(projection));
		shaderTerrain.setMatrix4("view", 1, false,
				glm::value_ptr(view));
		shaderTerrain.setMatrix4("lightSpaceMatrix", 1, false,
				glm::value_ptr(lightSpaceMatrix));
		// Settea la matriz de vista y projection al shader para el fountain
		shaderParticlesFountain.setMatrix4("projection", 1, false,
					glm::value_ptr(projection));
		shaderParticlesFountain.setMatrix4("view", 1, false,
				glm::value_ptr(view));
		// Settea la matriz de vista y projection al shader para el fuego
		shaderParticlesFire.setInt("Pass", 2);
		shaderParticlesFire.setMatrix4("projection", 1, false, glm::value_ptr(projection));
		shaderParticlesFire.setMatrix4("view", 1, false, glm::value_ptr(view));

		/*******************************************
		 * Propiedades de neblina
		 *******************************************/
		shaderMulLighting.setVectorFloat3("fogColor", glm::value_ptr(glm::vec3(0.5, 0.5, 0.4)));
		shaderTerrain.setVectorFloat3("fogColor", glm::value_ptr(glm::vec3(0.5, 0.5, 0.4)));
		shaderSkybox.setVectorFloat3("fogColor", glm::value_ptr(glm::vec3(0.5, 0.5, 0.4)));

		/*******************************************
		 * Propiedades Luz direccional
		 *******************************************/
		shaderMulLighting.setVectorFloat3("viewPos", glm::value_ptr(camera->getPosition()));
		shaderMulLighting.setVectorFloat3("directionalLight.light.ambient", glm::value_ptr(glm::vec3(0.005, 0.005, 0.005)));
		shaderMulLighting.setVectorFloat3("directionalLight.light.diffuse", glm::value_ptr(glm::vec3(0.01, 0.01, 0.01)));
		shaderMulLighting.setVectorFloat3("directionalLight.light.specular", glm::value_ptr(glm::vec3(0.2, 0.2, 0.2)));
		shaderMulLighting.setVectorFloat3("directionalLight.direction", glm::value_ptr(glm::vec3(-0.707106781, -0.707106781, 0.0)));

		/*******************************************
		 * Propiedades Luz direccional Terrain
		 *******************************************/
		shaderTerrain.setVectorFloat3("viewPos", glm::value_ptr(camera->getPosition()));
		shaderTerrain.setVectorFloat3("directionalLight.light.ambient", glm::value_ptr(glm::vec3(0.005, 0.005, 0.005)));
		shaderTerrain.setVectorFloat3("directionalLight.light.diffuse", glm::value_ptr(glm::vec3(0.01, 0.01, 0.01)));
		shaderTerrain.setVectorFloat3("directionalLight.light.specular", glm::value_ptr(glm::vec3(0.2, 0.2, 0.2)));
		shaderTerrain.setVectorFloat3("directionalLight.direction", glm::value_ptr(glm::vec3(-0.707106781, -0.707106781, 0.0)));

		/*******************************************
		 * Propiedades SpotLights
		 *******************************************/
		glm::vec3 spotPosition = glm::vec3(modelMatrixMayow * glm::vec4(1.0, 1.5, 1.0, 1.0));
		shaderMulLighting.setInt("spotLightCount", 4);
		shaderTerrain.setInt("spotLightCount", 1);
		shaderMulLighting.setVectorFloat3("spotLights[0].light.ambient", glm::value_ptr(glm::vec3(0.0, 0.0, 0.0)));
		shaderMulLighting.setVectorFloat3("spotLights[0].light.diffuse", glm::value_ptr(glm::vec3(0.5, 0.5, 0.5)));
		shaderMulLighting.setVectorFloat3("spotLights[0].light.specular", glm::value_ptr(glm::vec3(0.3, 0.3, 0.3)));
		shaderMulLighting.setVectorFloat3("spotLights[0].position", glm::value_ptr(spotPosition));
		shaderMulLighting.setVectorFloat3("spotLights[0].direction", glm::value_ptr(glm::vec3(0, 0, -1)));
		shaderMulLighting.setFloat("spotLights[0].constant", 1.0);
		shaderMulLighting.setFloat("spotLights[0].linear", 0.074);
		shaderMulLighting.setFloat("spotLights[0].quadratic", 0.03);
		shaderMulLighting.setFloat("spotLights[0].cutOff", cos(glm::radians(12.5f)));
		shaderMulLighting.setFloat("spotLights[0].outerCutOff", cos(glm::radians(15.0f)));
		shaderTerrain.setVectorFloat3("spotLights[0].light.ambient", glm::value_ptr(glm::vec3(0.0, 0.0, 0.0)));
		shaderTerrain.setVectorFloat3("spotLights[0].light.diffuse", glm::value_ptr(glm::vec3(0.5, 0.5, 0.5)));
		shaderTerrain.setVectorFloat3("spotLights[0].light.specular", glm::value_ptr(glm::vec3(0.3, 0.3, 0.3)));
		shaderTerrain.setVectorFloat3("spotLights[0].position", glm::value_ptr(spotPosition));
		shaderTerrain.setVectorFloat3("spotLights[0].direction", glm::value_ptr(glm::vec3(0, -1, 0)));
		shaderTerrain.setFloat("spotLights[0].constant", 1.0);
		shaderTerrain.setFloat("spotLights[0].linear", 0.074);
		shaderTerrain.setFloat("spotLights[0].quadratic", 0.03);
		shaderTerrain.setFloat("spotLights[0].cutOff", cos(glm::radians(12.5f)));
		shaderTerrain.setFloat("spotLights[0].outerCutOff", cos(glm::radians(15.0f)));

		shaderMulLighting.setVectorFloat3("spotLights[1].light.ambient", glm::value_ptr(glm::vec3(0.0, 0.0, 0.0)));
		shaderMulLighting.setVectorFloat3("spotLights[1].light.diffuse", glm::value_ptr(glm::vec3(0.5, 0.5, 0.5)));
		shaderMulLighting.setVectorFloat3("spotLights[1].light.specular", glm::value_ptr(glm::vec3(0.3, 0.3, 0.3)));
		shaderMulLighting.setVectorFloat3("spotLights[1].position", glm::value_ptr(spotPosition));
		shaderMulLighting.setVectorFloat3("spotLights[1].direction", glm::value_ptr(glm::vec3(0, 0, 1)));
		shaderMulLighting.setFloat("spotLights[1].constant", 1.0);
		shaderMulLighting.setFloat("spotLights[1].linear", 0.074);
		shaderMulLighting.setFloat("spotLights[1].quadratic", 0.03);
		shaderMulLighting.setFloat("spotLights[1].cutOff", cos(glm::radians(12.5f)));
		shaderMulLighting.setFloat("spotLights[1].outerCutOff", cos(glm::radians(15.0f)));

		shaderMulLighting.setVectorFloat3("spotLights[2].light.ambient", glm::value_ptr(glm::vec3(0.0, 0.0, 0.0)));
		shaderMulLighting.setVectorFloat3("spotLights[2].light.diffuse", glm::value_ptr(glm::vec3(0.5, 0.5, 0.5)));
		shaderMulLighting.setVectorFloat3("spotLights[2].light.specular", glm::value_ptr(glm::vec3(0.3, 0.3, 0.3)));
		shaderMulLighting.setVectorFloat3("spotLights[2].position", glm::value_ptr(spotPosition));
		shaderMulLighting.setVectorFloat3("spotLights[2].direction", glm::value_ptr(glm::vec3(-1, 0, 0)));
		shaderMulLighting.setFloat("spotLights[2].constant", 1.0);
		shaderMulLighting.setFloat("spotLights[2].linear", 0.074);
		shaderMulLighting.setFloat("spotLights[2].quadratic", 0.03);
		shaderMulLighting.setFloat("spotLights[2].cutOff", cos(glm::radians(12.5f)));
		shaderMulLighting.setFloat("spotLights[2].outerCutOff", cos(glm::radians(15.0f)));

		shaderMulLighting.setVectorFloat3("spotLights[3].light.ambient", glm::value_ptr(glm::vec3(0.0, 0.0, 0.0)));
		shaderMulLighting.setVectorFloat3("spotLights[3].light.diffuse", glm::value_ptr(glm::vec3(0.5, 0.5, 0.5)));
		shaderMulLighting.setVectorFloat3("spotLights[3].light.specular", glm::value_ptr(glm::vec3(0.3, 0.3, 0.3)));
		shaderMulLighting.setVectorFloat3("spotLights[3].position", glm::value_ptr(spotPosition));
		shaderMulLighting.setVectorFloat3("spotLights[3].direction", glm::value_ptr(glm::vec3(1, 0, 0)));
		shaderMulLighting.setFloat("spotLights[3].constant", 1.0);
		shaderMulLighting.setFloat("spotLights[3].linear", 0.074);
		shaderMulLighting.setFloat("spotLights[3].quadratic", 0.03);
		shaderMulLighting.setFloat("spotLights[3].cutOff", cos(glm::radians(12.5f)));
		shaderMulLighting.setFloat("spotLights[3].outerCutOff", cos(glm::radians(15.0f)));

		/*******************************************
		 * Propiedades PointLights
		 *******************************************/

		/*******************************************
		 * 1.- We render the depth buffer
		 *******************************************/
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// render scene from light's point of view
		glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
		glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
		glClear(GL_DEPTH_BUFFER_BIT);
		//glCullFace(GL_FRONT);
		prepareDepthScene();
		renderScene(false);
		//glCullFace(GL_BACK);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		/*******************************************
		 * Debug to view the texture view map
		 *******************************************/
		// reset viewport
		/*glViewport(0, 0, screenWidth, screenHeight);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// render Depth map to quad for visual debugging
		shaderViewDepth.setMatrix4("projection", 1, false, glm::value_ptr(glm::mat4(1.0)));
		shaderViewDepth.setMatrix4("view", 1, false, glm::value_ptr(glm::mat4(1.0)));
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, depthMap);
		boxViewDepth.setScale(glm::vec3(2.0, 2.0, 1.0));
		boxViewDepth.render();*/

		/*******************************************
		 * 2.- We render the normal objects
		 *******************************************/
		glViewport(0, 0, screenWidth, screenHeight);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		prepareScene();
		glActiveTexture(GL_TEXTURE10);
		glBindTexture(GL_TEXTURE_2D, depthMap);
		shaderMulLighting.setInt("shadowMap", 10);
		shaderTerrain.setInt("shadowMap", 10);
		
		// Boo's

		modelMatrixBoo1[3][1] = terrain.getHeightTerrain(modelMatrixBoo1[3][0], modelMatrixBoo1[3][2]);
		glm::mat4 modelMatrixBoo1Body = glm::mat4(modelMatrixBoo1);
		modelMatrixBoo1Body = glm::scale(modelMatrixBoo1, glm::vec3(0.5, 0.5, 0.5));
		modelBoo1.render(modelMatrixBoo1Body);

		modelMatrixBoo2[3][1] = terrain.getHeightTerrain(modelMatrixBoo2[3][0], modelMatrixBoo2[3][2]);
		glm::mat4 modelMatrixBoo2Body = glm::mat4(modelMatrixBoo2);
		modelMatrixBoo2Body = glm::scale(modelMatrixBoo2, glm::vec3(0.5, 0.5, 0.5));
		modelBoo2.render(modelMatrixBoo2Body);

		modelMatrixBoo3[3][1] = terrain.getHeightTerrain(modelMatrixBoo3[3][0], modelMatrixBoo3[3][2]);
		glm::mat4 modelMatrixBoo3Body = glm::mat4(modelMatrixBoo3);
		modelMatrixBoo3Body = glm::scale(modelMatrixBoo3, glm::vec3(0.5, 0.5, 0.5));
		modelBoo3.render(modelMatrixBoo3Body);

		modelMatrixBoo4[3][1] = terrain.getHeightTerrain(modelMatrixBoo4[3][0], modelMatrixBoo4[3][2]);
		glm::mat4 modelMatrixBoo4Body = glm::mat4(modelMatrixBoo4);
		modelMatrixBoo4Body = glm::scale(modelMatrixBoo4, glm::vec3(0.5, 0.5, 0.5));
		modelBoo4.render(modelMatrixBoo4Body);

		// Cuerpo

		modelMatrixCuerpo[3][1] = terrain.getHeightTerrain(modelMatrixCuerpo[3][0], modelMatrixCuerpo[3][2]);
		glm::mat4 modelMatrixCuerpoBody = glm::mat4(modelMatrixCuerpo);
		modelMatrixCuerpoBody = glm::scale(modelMatrixCuerpo, glm::vec3(0.5, 0.5, 0.5));
		modelCuerpo.render(modelMatrixCuerpoBody);
		
		/*******************************************
		 * Laberinto
		 *******************************************/
		
		modelMatrixPEA[3][1] = terrain.getHeightTerrain(modelMatrixPEA[3][0], modelMatrixPEA[3][2]);
		glm::mat4 modelMatrixPEABody = glm::mat4(modelMatrixPEA);
		modelMatrixPEABody = glm::scale(modelMatrixPEA, glm::vec3(0.5, 0.5, 0.5));
		modelPEA.render(modelMatrixPEABody);

		modelMatrixPEB[3][1] = terrain.getHeightTerrain(modelMatrixPEB[3][0], modelMatrixPEB[3][2]);
		glm::mat4 modelMatrixPEBBody = glm::mat4(modelMatrixPEB);
		modelMatrixPEBBody = glm::scale(modelMatrixPEB, glm::vec3(0.5, 0.5, 0.5));
		modelPEB.render(modelMatrixPEBBody);

		modelMatrixPEI[3][1] = terrain.getHeightTerrain(modelMatrixPEI[3][0], modelMatrixPEI[3][2]);
		glm::mat4 modelMatrixPEIBody = glm::mat4(modelMatrixPEI);
		modelMatrixPEIBody = glm::scale(modelMatrixPEI, glm::vec3(0.5, 0.5, 0.5));
		modelPEI.render(modelMatrixPEIBody);

		modelMatrixPED[3][1] = terrain.getHeightTerrain(modelMatrixPED[3][0], modelMatrixPED[3][2]);
		glm::mat4 modelMatrixPEDBody = glm::mat4(modelMatrixPED);
		modelMatrixPEDBody = glm::scale(modelMatrixPED, glm::vec3(0.5, 0.5, 0.5));
		modelPED.render(modelMatrixPEDBody);
		
		modelMatrixPC1[3][1] = terrain.getHeightTerrain(modelMatrixPC1[3][0], modelMatrixPC1[3][2]);
		glm::mat4 modelMatrixPC1Body = glm::mat4(modelMatrixPC1);
		modelMatrixPC1Body = glm::scale(modelMatrixPC1, glm::vec3(0.5, 0.5, 0.5));
		modelPC1.render(modelMatrixPC1Body);

		modelMatrixPC2[3][1] = terrain.getHeightTerrain(modelMatrixPC2[3][0], modelMatrixPC2[3][2]);
		glm::mat4 modelMatrixPC2Body = glm::mat4(modelMatrixPC2);
		modelMatrixPC2Body = glm::scale(modelMatrixPC2, glm::vec3(0.5, 0.5, 0.5));
		modelPC2.render(modelMatrixPC2Body);

		modelMatrixPC3[3][1] = terrain.getHeightTerrain(modelMatrixPC3[3][0], modelMatrixPC3[3][2]);
		glm::mat4 modelMatrixPC3Body = glm::mat4(modelMatrixPC3);
		modelMatrixPC3Body = glm::scale(modelMatrixPC3, glm::vec3(0.5, 0.5, 0.5));
		modelPC3.render(modelMatrixPC3Body);

		modelMatrixPC4[3][1] = terrain.getHeightTerrain(modelMatrixPC4[3][0], modelMatrixPC4[3][2]);
		glm::mat4 modelMatrixPC4Body = glm::mat4(modelMatrixPC4);
		modelMatrixPC4Body = glm::scale(modelMatrixPC4, glm::vec3(0.5, 0.5, 0.5));
		modelPC4.render(modelMatrixPC4Body);

		modelMatrixPC5[3][1] = terrain.getHeightTerrain(modelMatrixPC5[3][0], modelMatrixPC5[3][2]);
		glm::mat4 modelMatrixPC5Body = glm::mat4(modelMatrixPC5);
		modelMatrixPC5Body = glm::scale(modelMatrixPC5, glm::vec3(0.5, 0.5, 0.5));
		modelPC5.render(modelMatrixPC5Body);

		modelMatrixPC6[3][1] = terrain.getHeightTerrain(modelMatrixPC6[3][0], modelMatrixPC6[3][2]);
		glm::mat4 modelMatrixPC6Body = glm::mat4(modelMatrixPC6);
		modelMatrixPC6Body = glm::scale(modelMatrixPC6, glm::vec3(0.5, 0.5, 0.5));
		modelPC6.render(modelMatrixPC6Body);

		modelMatrixPC7[3][1] = terrain.getHeightTerrain(modelMatrixPC7[3][0], modelMatrixPC7[3][2]);
		glm::mat4 modelMatrixPC7Body = glm::mat4(modelMatrixPC7);
		modelMatrixPC7Body = glm::scale(modelMatrixPC7, glm::vec3(0.5, 0.5, 0.5));
		modelPC7.render(modelMatrixPC7Body);

		modelMatrixPC8[3][1] = terrain.getHeightTerrain(modelMatrixPC8[3][0], modelMatrixPC8[3][2]);
		glm::mat4 modelMatrixPC8Body = glm::mat4(modelMatrixPC8);
		modelMatrixPC8Body = glm::scale(modelMatrixPC8, glm::vec3(0.5, 0.5, 0.5));
		modelPC8.render(modelMatrixPC8Body);

		modelMatrixPC9[3][1] = terrain.getHeightTerrain(modelMatrixPC9[3][0], modelMatrixPC9[3][2]);
		glm::mat4 modelMatrixPC9Body = glm::mat4(modelMatrixPC9);
		modelMatrixPC9Body = glm::scale(modelMatrixPC9, glm::vec3(0.5, 0.5, 0.5));
		modelPC9.render(modelMatrixPC9Body);

		modelMatrixPC10[3][1] = terrain.getHeightTerrain(modelMatrixPC10[3][0], modelMatrixPC10[3][2]);
		glm::mat4 modelMatrixPC10Body = glm::mat4(modelMatrixPC10);
		modelMatrixPC10Body = glm::scale(modelMatrixPC10, glm::vec3(0.5, 0.5, 0.5));
		modelPC10.render(modelMatrixPC10Body);

		modelMatrixPC11[3][1] = terrain.getHeightTerrain(modelMatrixPC11[3][0], modelMatrixPC11[3][2]);
		glm::mat4 modelMatrixPC11Body = glm::mat4(modelMatrixPC11);
		modelMatrixPC11Body = glm::scale(modelMatrixPC11, glm::vec3(0.5, 0.5, 0.5));
		modelPC11.render(modelMatrixPC11Body);

		modelMatrixPC12[3][1] = terrain.getHeightTerrain(modelMatrixPC12[3][0], modelMatrixPC12[3][2]);
		glm::mat4 modelMatrixPC12Body = glm::mat4(modelMatrixPC12);
		modelMatrixPC12Body = glm::scale(modelMatrixPC12, glm::vec3(0.5, 0.5, 0.5));
		modelPC12.render(modelMatrixPC12Body);

		modelMatrixPC13[3][1] = terrain.getHeightTerrain(modelMatrixPC13[3][0], modelMatrixPC13[3][2]);
		glm::mat4 modelMatrixPC13Body = glm::mat4(modelMatrixPC13);
		modelMatrixPC13Body = glm::scale(modelMatrixPC13, glm::vec3(0.5, 0.5, 0.5));
		modelPC13.render(modelMatrixPC13Body);

		modelMatrixPC14[3][1] = terrain.getHeightTerrain(modelMatrixPC14[3][0], modelMatrixPC14[3][2]);
		glm::mat4 modelMatrixPC14Body = glm::mat4(modelMatrixPC14);
		modelMatrixPC14Body = glm::scale(modelMatrixPC14, glm::vec3(0.5, 0.5, 0.5));
		modelPC14.render(modelMatrixPC14Body);

		modelMatrixPC15[3][1] = terrain.getHeightTerrain(modelMatrixPC15[3][0], modelMatrixPC15[3][2]);
		glm::mat4 modelMatrixPC15Body = glm::mat4(modelMatrixPC15);
		modelMatrixPC15Body = glm::scale(modelMatrixPC15, glm::vec3(0.5, 0.5, 0.5));
		modelPC15.render(modelMatrixPC15Body);

		modelMatrixPC16[3][1] = terrain.getHeightTerrain(modelMatrixPC16[3][0], modelMatrixPC16[3][2]);
		glm::mat4 modelMatrixPC16Body = glm::mat4(modelMatrixPC16);
		modelMatrixPC16Body = glm::scale(modelMatrixPC16, glm::vec3(0.5, 0.5, 0.5));
		modelPC16.render(modelMatrixPC16Body);

		modelMatrixPC17[3][1] = terrain.getHeightTerrain(modelMatrixPC17[3][0], modelMatrixPC17[3][2]);
		glm::mat4 modelMatrixPC17Body = glm::mat4(modelMatrixPC17);
		modelMatrixPC17Body = glm::scale(modelMatrixPC17, glm::vec3(0.5, 0.5, 0.5));
		modelPC17.render(modelMatrixPC17Body);

		modelMatrixPC18[3][1] = terrain.getHeightTerrain(modelMatrixPC18[3][0], modelMatrixPC18[3][2]);
		glm::mat4 modelMatrixPC18Body = glm::mat4(modelMatrixPC18);
		modelMatrixPC18Body = glm::scale(modelMatrixPC18, glm::vec3(0.5, 0.5, 0.5));
		modelPC18.render(modelMatrixPC18Body);

		modelMatrixPC19[3][1] = terrain.getHeightTerrain(modelMatrixPC19[3][0], modelMatrixPC19[3][2]);
		glm::mat4 modelMatrixPC19Body = glm::mat4(modelMatrixPC19);
		modelMatrixPC19Body = glm::scale(modelMatrixPC19, glm::vec3(0.5, 0.5, 0.5));
		modelPC19.render(modelMatrixPC19Body);

		modelMatrixPC20[3][1] = terrain.getHeightTerrain(modelMatrixPC20[3][0], modelMatrixPC20[3][2]);
		glm::mat4 modelMatrixPC20Body = glm::mat4(modelMatrixPC20);
		modelMatrixPC20Body = glm::scale(modelMatrixPC20, glm::vec3(0.5, 0.5, 0.5));
		modelPC20.render(modelMatrixPC20Body);

		modelMatrixPC21[3][1] = terrain.getHeightTerrain(modelMatrixPC21[3][0], modelMatrixPC21[3][2]);
		glm::mat4 modelMatrixPC21Body = glm::mat4(modelMatrixPC21);
		modelMatrixPC21Body = glm::scale(modelMatrixPC21, glm::vec3(0.5, 0.5, 0.5));
		modelPC21.render(modelMatrixPC21Body);

		modelMatrixPC22[3][1] = terrain.getHeightTerrain(modelMatrixPC22[3][0], modelMatrixPC22[3][2]);
		glm::mat4 modelMatrixPC22Body = glm::mat4(modelMatrixPC22);
		modelMatrixPC22Body = glm::scale(modelMatrixPC22, glm::vec3(0.5, 0.5, 0.5));
		modelPC22.render(modelMatrixPC22Body);

		modelMatrixPC23[3][1] = terrain.getHeightTerrain(modelMatrixPC23[3][0], modelMatrixPC23[3][2]);
		glm::mat4 modelMatrixPC23Body = glm::mat4(modelMatrixPC23);
		modelMatrixPC23Body = glm::scale(modelMatrixPC23, glm::vec3(0.5, 0.5, 0.5));
		modelPC23.render(modelMatrixPC23Body);

		modelMatrixPC24[3][1] = terrain.getHeightTerrain(modelMatrixPC24[3][0], modelMatrixPC24[3][2]);
		glm::mat4 modelMatrixPC24Body = glm::mat4(modelMatrixPC24);
		modelMatrixPC24Body = glm::scale(modelMatrixPC24, glm::vec3(0.5, 0.5, 0.5));
		modelPC24.render(modelMatrixPC24Body);

		modelMatrixPC25[3][1] = terrain.getHeightTerrain(modelMatrixPC25[3][0], modelMatrixPC25[3][2]);
		glm::mat4 modelMatrixPC25Body = glm::mat4(modelMatrixPC25);
		modelMatrixPC25Body = glm::scale(modelMatrixPC25, glm::vec3(0.5, 0.5, 0.5));
		modelPC25.render(modelMatrixPC25Body);

		modelMatrixPC26[3][1] = terrain.getHeightTerrain(modelMatrixPC26[3][0], modelMatrixPC26[3][2]);
		glm::mat4 modelMatrixPC26Body = glm::mat4(modelMatrixPC26);
		modelMatrixPC26Body = glm::scale(modelMatrixPC26, glm::vec3(0.5, 0.5, 0.5));
		modelPC26.render(modelMatrixPC26Body);

		modelMatrixPC27[3][1] = terrain.getHeightTerrain(modelMatrixPC27[3][0], modelMatrixPC27[3][2]);
		glm::mat4 modelMatrixPC27Body = glm::mat4(modelMatrixPC27);
		modelMatrixPC27Body = glm::scale(modelMatrixPC27, glm::vec3(0.5, 0.5, 0.5));
		modelPC27.render(modelMatrixPC27Body);

		modelMatrixPC28[3][1] = terrain.getHeightTerrain(modelMatrixPC28[3][0], modelMatrixPC28[3][2]);
		glm::mat4 modelMatrixPC28Body = glm::mat4(modelMatrixPC28);
		modelMatrixPC28Body = glm::scale(modelMatrixPC28, glm::vec3(0.5, 0.5, 0.5));
		modelPC28.render(modelMatrixPC28Body);

		modelMatrixPC29[3][1] = terrain.getHeightTerrain(modelMatrixPC29[3][0], modelMatrixPC29[3][2]);
		glm::mat4 modelMatrixPC29Body = glm::mat4(modelMatrixPC29);
		modelMatrixPC29Body = glm::scale(modelMatrixPC29, glm::vec3(0.5, 0.5, 0.5));
		modelPC29.render(modelMatrixPC29Body);

		modelMatrixPC30[3][1] = terrain.getHeightTerrain(modelMatrixPC30[3][0], modelMatrixPC30[3][2]);
		glm::mat4 modelMatrixPC30Body = glm::mat4(modelMatrixPC30);
		modelMatrixPC30Body = glm::scale(modelMatrixPC30, glm::vec3(0.5, 0.5, 0.5));
		modelPC30.render(modelMatrixPC30Body);

		modelMatrixPC31[3][1] = terrain.getHeightTerrain(modelMatrixPC31[3][0], modelMatrixPC31[3][2]);
		glm::mat4 modelMatrixPC31Body = glm::mat4(modelMatrixPC31);
		modelMatrixPC31Body = glm::scale(modelMatrixPC31, glm::vec3(0.5, 0.5, 0.5));
		modelPC31.render(modelMatrixPC31Body);

		modelMatrixPC32[3][1] = terrain.getHeightTerrain(modelMatrixPC32[3][0], modelMatrixPC32[3][2]);
		glm::mat4 modelMatrixPC32Body = glm::mat4(modelMatrixPC32);
		modelMatrixPC32Body = glm::scale(modelMatrixPC32, glm::vec3(0.5, 0.5, 0.5));
		modelPC32.render(modelMatrixPC32Body);

		modelMatrixPC33[3][1] = terrain.getHeightTerrain(modelMatrixPC33[3][0], modelMatrixPC33[3][2]);
		glm::mat4 modelMatrixPC33Body = glm::mat4(modelMatrixPC33);
		modelMatrixPC33Body = glm::scale(modelMatrixPC33, glm::vec3(0.5, 0.5, 0.5));
		modelPC33.render(modelMatrixPC33Body);

		modelMatrixPC34[3][1] = terrain.getHeightTerrain(modelMatrixPC34[3][0], modelMatrixPC34[3][2]);
		glm::mat4 modelMatrixPC34Body = glm::mat4(modelMatrixPC34);
		modelMatrixPC34Body = glm::scale(modelMatrixPC34, glm::vec3(0.5, 0.5, 0.5));
		modelPC34.render(modelMatrixPC34Body);

		modelMatrixPC35[3][1] = terrain.getHeightTerrain(modelMatrixPC35[3][0], modelMatrixPC35[3][2]);
		glm::mat4 modelMatrixPC35Body = glm::mat4(modelMatrixPC35);
		modelMatrixPC35Body = glm::scale(modelMatrixPC35, glm::vec3(0.5, 0.5, 0.5));
		modelPC35.render(modelMatrixPC35Body);

		modelMatrixPC36[3][1] = terrain.getHeightTerrain(modelMatrixPC36[3][0], modelMatrixPC36[3][2]);
		glm::mat4 modelMatrixPC36Body = glm::mat4(modelMatrixPC36);
		modelMatrixPC36Body = glm::scale(modelMatrixPC36, glm::vec3(0.5, 0.5, 0.5));
		modelPC36.render(modelMatrixPC36Body);

		modelMatrixPC37[3][1] = terrain.getHeightTerrain(modelMatrixPC37[3][0], modelMatrixPC37[3][2]);
		glm::mat4 modelMatrixPC37Body = glm::mat4(modelMatrixPC37);
		modelMatrixPC37Body = glm::scale(modelMatrixPC37, glm::vec3(0.5, 0.5, 0.5));
		modelPC37.render(modelMatrixPC37Body);

		modelMatrixPC38[3][1] = terrain.getHeightTerrain(modelMatrixPC38[3][0], modelMatrixPC38[3][2]);
		glm::mat4 modelMatrixPC38Body = glm::mat4(modelMatrixPC38);
		modelMatrixPC38Body = glm::scale(modelMatrixPC38, glm::vec3(0.5, 0.5, 0.5));
		modelPC38.render(modelMatrixPC38Body);

		modelMatrixPC39[3][1] = terrain.getHeightTerrain(modelMatrixPC39[3][0], modelMatrixPC39[3][2]);
		glm::mat4 modelMatrixPC39Body = glm::mat4(modelMatrixPC39);
		modelMatrixPC39Body = glm::scale(modelMatrixPC39, glm::vec3(0.5, 0.5, 0.5));
		modelPC39.render(modelMatrixPC39Body);

		modelMatrixPC40[3][1] = terrain.getHeightTerrain(modelMatrixPC40[3][0], modelMatrixPC40[3][2]);
		glm::mat4 modelMatrixPC40Body = glm::mat4(modelMatrixPC40);
		modelMatrixPC40Body = glm::scale(modelMatrixPC40, glm::vec3(0.5, 0.5, 0.5));
		modelPC40.render(modelMatrixPC40Body);

		modelMatrixPC41[3][1] = terrain.getHeightTerrain(modelMatrixPC41[3][0], modelMatrixPC41[3][2]);
		glm::mat4 modelMatrixPC41Body = glm::mat4(modelMatrixPC41);
		modelMatrixPC41Body = glm::scale(modelMatrixPC41, glm::vec3(0.5, 0.5, 0.5));
		modelPC41.render(modelMatrixPC41Body);

		modelMatrixPC42[3][1] = terrain.getHeightTerrain(modelMatrixPC42[3][0], modelMatrixPC42[3][2]);
		glm::mat4 modelMatrixPC42Body = glm::mat4(modelMatrixPC42);
		modelMatrixPC42Body = glm::scale(modelMatrixPC42, glm::vec3(0.5, 0.5, 0.5));
		modelPC42.render(modelMatrixPC42Body);

		modelMatrixPC43[3][1] = terrain.getHeightTerrain(modelMatrixPC43[3][0], modelMatrixPC43[3][2]);
		glm::mat4 modelMatrixPC43Body = glm::mat4(modelMatrixPC43);
		modelMatrixPC43Body = glm::scale(modelMatrixPC43, glm::vec3(0.5, 0.5, 0.5));
		modelPC43.render(modelMatrixPC43Body);

		modelMatrixPC44[3][1] = terrain.getHeightTerrain(modelMatrixPC44[3][0], modelMatrixPC44[3][2]);
		glm::mat4 modelMatrixPC44Body = glm::mat4(modelMatrixPC44);
		modelMatrixPC44Body = glm::scale(modelMatrixPC44, glm::vec3(0.5, 0.5, 0.5));
		modelPC44.render(modelMatrixPC44Body);

		modelMatrixPC45[3][1] = terrain.getHeightTerrain(modelMatrixPC45[3][0], modelMatrixPC45[3][2]);
		glm::mat4 modelMatrixPC45Body = glm::mat4(modelMatrixPC45);
		modelMatrixPC45Body = glm::scale(modelMatrixPC45, glm::vec3(0.5, 0.5, 0.5));
		modelPC45.render(modelMatrixPC45Body);

		modelMatrixPC46[3][1] = terrain.getHeightTerrain(modelMatrixPC46[3][0], modelMatrixPC46[3][2]);
		glm::mat4 modelMatrixPC46Body = glm::mat4(modelMatrixPC46);
		modelMatrixPC46Body = glm::scale(modelMatrixPC46, glm::vec3(0.5, 0.5, 0.5));
		modelPC46.render(modelMatrixPC46Body);

		modelMatrixPC47[3][1] = terrain.getHeightTerrain(modelMatrixPC47[3][0], modelMatrixPC47[3][2]);
		glm::mat4 modelMatrixPC47Body = glm::mat4(modelMatrixPC47);
		modelMatrixPC47Body = glm::scale(modelMatrixPC47, glm::vec3(0.5, 0.5, 0.5));
		modelPC47.render(modelMatrixPC47Body);

		modelMatrixPC48[3][1] = terrain.getHeightTerrain(modelMatrixPC48[3][0], modelMatrixPC48[3][2]);
		glm::mat4 modelMatrixPC48Body = glm::mat4(modelMatrixPC48);
		modelMatrixPC48Body = glm::scale(modelMatrixPC48, glm::vec3(0.5, 0.5, 0.5));
		modelPC48.render(modelMatrixPC48Body);

		modelMatrixPC49[3][1] = terrain.getHeightTerrain(modelMatrixPC49[3][0], modelMatrixPC49[3][2]);
		glm::mat4 modelMatrixPC49Body = glm::mat4(modelMatrixPC49);
		modelMatrixPC49Body = glm::scale(modelMatrixPC49, glm::vec3(0.5, 0.5, 0.5));
		modelPC49.render(modelMatrixPC49Body);

		modelMatrixPC50[3][1] = terrain.getHeightTerrain(modelMatrixPC50[3][0], modelMatrixPC50[3][2]);
		glm::mat4 modelMatrixPC50Body = glm::mat4(modelMatrixPC50);
		modelMatrixPC50Body = glm::scale(modelMatrixPC50, glm::vec3(0.5, 0.5, 0.5));
		modelPC50.render(modelMatrixPC50Body);

		modelMatrixPC51[3][1] = terrain.getHeightTerrain(modelMatrixPC51[3][0], modelMatrixPC51[3][2]);
		glm::mat4 modelMatrixPC51Body = glm::mat4(modelMatrixPC51);
		modelMatrixPC51Body = glm::scale(modelMatrixPC51, glm::vec3(0.5, 0.5, 0.5));
		modelPC51.render(modelMatrixPC51Body);

		modelMatrixPC52[3][1] = terrain.getHeightTerrain(modelMatrixPC52[3][0], modelMatrixPC52[3][2]);
		glm::mat4 modelMatrixPC52Body = glm::mat4(modelMatrixPC52);
		modelMatrixPC52Body = glm::scale(modelMatrixPC52, glm::vec3(0.5, 0.5, 0.5));
		modelPC52.render(modelMatrixPC52Body);

		modelMatrixPC53[3][1] = terrain.getHeightTerrain(modelMatrixPC53[3][0], modelMatrixPC53[3][2]);
		glm::mat4 modelMatrixPC53Body = glm::mat4(modelMatrixPC53);
		modelMatrixPC53Body = glm::scale(modelMatrixPC53, glm::vec3(0.5, 0.5, 0.5));
		modelPC53.render(modelMatrixPC53Body);

		modelMatrixPC54[3][1] = terrain.getHeightTerrain(modelMatrixPC54[3][0], modelMatrixPC54[3][2]);
		glm::mat4 modelMatrixPC54Body = glm::mat4(modelMatrixPC54);
		modelMatrixPC54Body = glm::scale(modelMatrixPC54, glm::vec3(0.5, 0.5, 0.5));
		modelPC54.render(modelMatrixPC54Body);

		modelMatrixPC55[3][1] = terrain.getHeightTerrain(modelMatrixPC55[3][0], modelMatrixPC55[3][2]);
		glm::mat4 modelMatrixPC55Body = glm::mat4(modelMatrixPC55);
		modelMatrixPC55Body = glm::scale(modelMatrixPC55, glm::vec3(0.5, 0.5, 0.5));
		modelPC55.render(modelMatrixPC55Body);

		modelMatrixPC56[3][1] = terrain.getHeightTerrain(modelMatrixPC56[3][0], modelMatrixPC56[3][2]);
		glm::mat4 modelMatrixPC56Body = glm::mat4(modelMatrixPC56);
		modelMatrixPC56Body = glm::scale(modelMatrixPC56, glm::vec3(0.5, 0.5, 0.5));
		modelPC56.render(modelMatrixPC56Body);

		modelMatrixPC57[3][1] = terrain.getHeightTerrain(modelMatrixPC57[3][0], modelMatrixPC57[3][2]);
		glm::mat4 modelMatrixPC57Body = glm::mat4(modelMatrixPC57);
		modelMatrixPC57Body = glm::scale(modelMatrixPC57, glm::vec3(0.5, 0.5, 0.5));
		modelPC57.render(modelMatrixPC57Body);

		modelMatrixPC58[3][1] = terrain.getHeightTerrain(modelMatrixPC58[3][0], modelMatrixPC58[3][2]);
		glm::mat4 modelMatrixPC58Body = glm::mat4(modelMatrixPC58);
		modelMatrixPC58Body = glm::scale(modelMatrixPC58, glm::vec3(0.5, 0.5, 0.5));
		modelPC58.render(modelMatrixPC58Body);

		modelMatrixPC59[3][1] = terrain.getHeightTerrain(modelMatrixPC59[3][0], modelMatrixPC59[3][2]);
		glm::mat4 modelMatrixPC59Body = glm::mat4(modelMatrixPC59);
		modelMatrixPC59Body = glm::scale(modelMatrixPC59, glm::vec3(0.5, 0.5, 0.5));
		modelPC59.render(modelMatrixPC59Body);

		modelMatrixPC60[3][1] = terrain.getHeightTerrain(modelMatrixPC60[3][0], modelMatrixPC60[3][2]);
		glm::mat4 modelMatrixPC60Body = glm::mat4(modelMatrixPC60);
		modelMatrixPC60Body = glm::scale(modelMatrixPC60, glm::vec3(0.5, 0.5, 0.5));
		modelPC60.render(modelMatrixPC60Body);

		modelMatrixPC61[3][1] = terrain.getHeightTerrain(modelMatrixPC61[3][0], modelMatrixPC61[3][2]);
		glm::mat4 modelMatrixPC61Body = glm::mat4(modelMatrixPC61);
		modelMatrixPC61Body = glm::scale(modelMatrixPC61, glm::vec3(0.5, 0.5, 0.5));
		modelPC61.render(modelMatrixPC61Body);

		modelMatrixPC62[3][1] = terrain.getHeightTerrain(modelMatrixPC62[3][0], modelMatrixPC62[3][2]);
		glm::mat4 modelMatrixPC62Body = glm::mat4(modelMatrixPC62);
		modelMatrixPC62Body = glm::scale(modelMatrixPC62, glm::vec3(0.5, 0.5, 0.5));
		modelPC62.render(modelMatrixPC62Body);

		modelMatrixPC63[3][1] = terrain.getHeightTerrain(modelMatrixPC63[3][0], modelMatrixPC63[3][2]);
		glm::mat4 modelMatrixPC63Body = glm::mat4(modelMatrixPC63);
		modelMatrixPC63Body = glm::scale(modelMatrixPC63, glm::vec3(0.5, 0.5, 0.5));
		modelPC63.render(modelMatrixPC63Body);

		modelMatrixPC64[3][1] = terrain.getHeightTerrain(modelMatrixPC64[3][0], modelMatrixPC64[3][2]);
		glm::mat4 modelMatrixPC64Body = glm::mat4(modelMatrixPC64);
		modelMatrixPC64Body = glm::scale(modelMatrixPC64, glm::vec3(0.5, 0.5, 0.5));
		modelPC64.render(modelMatrixPC64Body);

		modelMatrixPC65[3][1] = terrain.getHeightTerrain(modelMatrixPC65[3][0], modelMatrixPC65[3][2]);
		glm::mat4 modelMatrixPC65Body = glm::mat4(modelMatrixPC65);
		modelMatrixPC65Body = glm::scale(modelMatrixPC65, glm::vec3(0.5, 0.5, 0.5));
		modelPC65.render(modelMatrixPC65Body);

		modelMatrixPC66[3][1] = terrain.getHeightTerrain(modelMatrixPC66[3][0], modelMatrixPC66[3][2]);
		glm::mat4 modelMatrixPC66Body = glm::mat4(modelMatrixPC66);
		modelMatrixPC66Body = glm::scale(modelMatrixPC66, glm::vec3(0.5, 0.5, 0.5));
		modelPC66.render(modelMatrixPC66Body);

		modelMatrixPC67[3][1] = terrain.getHeightTerrain(modelMatrixPC67[3][0], modelMatrixPC67[3][2]);
		glm::mat4 modelMatrixPC67Body = glm::mat4(modelMatrixPC67);
		modelMatrixPC67Body = glm::scale(modelMatrixPC67, glm::vec3(0.5, 0.5, 0.5));
		modelPC67.render(modelMatrixPC67Body);

		modelMatrixPC68[3][1] = terrain.getHeightTerrain(modelMatrixPC68[3][0], modelMatrixPC68[3][2]);
		glm::mat4 modelMatrixPC68Body = glm::mat4(modelMatrixPC68);
		modelMatrixPC68Body = glm::scale(modelMatrixPC68, glm::vec3(0.5, 0.5, 0.5));
		modelPC68.render(modelMatrixPC68Body);

		modelMatrixPC69[3][1] = terrain.getHeightTerrain(modelMatrixPC69[3][0], modelMatrixPC69[3][2]);
		glm::mat4 modelMatrixPC69Body = glm::mat4(modelMatrixPC69);
		modelMatrixPC69Body = glm::scale(modelMatrixPC69, glm::vec3(0.5, 0.5, 0.5));
		modelPC69.render(modelMatrixPC69Body);
		
		modelMatrixPC70[3][1] = terrain.getHeightTerrain(modelMatrixPC70[3][0], modelMatrixPC70[3][2]);
		glm::mat4 modelMatrixPC70Body = glm::mat4(modelMatrixPC70);
		modelMatrixPC70Body = glm::scale(modelMatrixPC70, glm::vec3(0.5, 0.5, 0.5));
		modelPC70.render(modelMatrixPC70Body);
		
		modelMatrixPC71[3][1] = terrain.getHeightTerrain(modelMatrixPC71[3][0], modelMatrixPC71[3][2]);
		glm::mat4 modelMatrixPC71Body = glm::mat4(modelMatrixPC71);
		modelMatrixPC71Body = glm::scale(modelMatrixPC71, glm::vec3(0.5, 0.5, 0.5));
		modelPC71.render(modelMatrixPC71Body);
		
		modelMatrixPC72[3][1] = terrain.getHeightTerrain(modelMatrixPC72[3][0], modelMatrixPC72[3][2]);
		glm::mat4 modelMatrixPC72Body = glm::mat4(modelMatrixPC72);
		modelMatrixPC72Body = glm::scale(modelMatrixPC72, glm::vec3(0.5, 0.5, 0.5));
		modelPC72.render(modelMatrixPC72Body);

		modelMatrixPC73[3][1] = terrain.getHeightTerrain(modelMatrixPC73[3][0], modelMatrixPC73[3][2]);
		glm::mat4 modelMatrixPC73Body = glm::mat4(modelMatrixPC73);
		modelMatrixPC73Body = glm::scale(modelMatrixPC73, glm::vec3(0.5, 0.5, 0.5));
		modelPC73.render(modelMatrixPC73Body);
		
		modelMatrixPC74[3][1] = terrain.getHeightTerrain(modelMatrixPC74[3][0], modelMatrixPC74[3][2]);
		glm::mat4 modelMatrixPC74Body = glm::mat4(modelMatrixPC74);
		modelMatrixPC74Body = glm::scale(modelMatrixPC74, glm::vec3(0.5, 0.5, 0.5));
		modelPC74.render(modelMatrixPC74Body);
		
		modelMatrixPC75[3][1] = terrain.getHeightTerrain(modelMatrixPC75[3][0], modelMatrixPC75[3][2]);
		glm::mat4 modelMatrixPC75Body = glm::mat4(modelMatrixPC75);
		modelMatrixPC75Body = glm::scale(modelMatrixPC75, glm::vec3(0.5, 0.5, 0.5));
		modelPC75.render(modelMatrixPC75Body);
		
		modelMatrixPC76[3][1] = terrain.getHeightTerrain(modelMatrixPC76[3][0], modelMatrixPC76[3][2]);
		glm::mat4 modelMatrixPC76Body = glm::mat4(modelMatrixPC76);
		modelMatrixPC76Body = glm::scale(modelMatrixPC76, glm::vec3(0.5, 0.5, 0.5));
		modelPC76.render(modelMatrixPC76Body);

		modelMatrixPC77[3][1] = terrain.getHeightTerrain(modelMatrixPC77[3][0], modelMatrixPC77[3][2]);
		glm::mat4 modelMatrixPC77Body = glm::mat4(modelMatrixPC77);
		modelMatrixPC77Body = glm::scale(modelMatrixPC77, glm::vec3(0.5, 0.5, 0.5));
		modelPC77.render(modelMatrixPC77Body);
		
		modelMatrixPC78[3][1] = terrain.getHeightTerrain(modelMatrixPC78[3][0], modelMatrixPC78[3][2]);
		glm::mat4 modelMatrixPC78Body = glm::mat4(modelMatrixPC78);
		modelMatrixPC78Body = glm::scale(modelMatrixPC78, glm::vec3(0.5, 0.5, 0.5));
		modelPC78.render(modelMatrixPC78Body);
		
		modelMatrixPC79[3][1] = terrain.getHeightTerrain(modelMatrixPC79[3][0], modelMatrixPC79[3][2]);
		glm::mat4 modelMatrixPC79Body = glm::mat4(modelMatrixPC79);
		modelMatrixPC79Body = glm::scale(modelMatrixPC79, glm::vec3(0.5, 0.5, 0.5));
		modelPC79.render(modelMatrixPC79Body);
		
		modelMatrixPC80[3][1] = terrain.getHeightTerrain(modelMatrixPC80[3][0], modelMatrixPC80[3][2]);
		glm::mat4 modelMatrixPC80Body = glm::mat4(modelMatrixPC80);
		modelMatrixPC80Body = glm::scale(modelMatrixPC80, glm::vec3(0.5, 0.5, 0.5));
		modelPC80.render(modelMatrixPC80Body);
		
		modelMatrixPC81[3][1] = terrain.getHeightTerrain(modelMatrixPC81[3][0], modelMatrixPC81[3][2]);
		glm::mat4 modelMatrixPC81Body = glm::mat4(modelMatrixPC81);
		modelMatrixPC81Body = glm::scale(modelMatrixPC81, glm::vec3(0.5, 0.5, 0.5));
		modelPC81.render(modelMatrixPC81Body);

		modelMatrixPC82[3][1] = terrain.getHeightTerrain(modelMatrixPC82[3][0], modelMatrixPC82[3][2]);
		glm::mat4 modelMatrixPC82Body = glm::mat4(modelMatrixPC82);
		modelMatrixPC82Body = glm::scale(modelMatrixPC82, glm::vec3(0.5, 0.5, 0.5));
		modelPC82.render(modelMatrixPC82Body);

		modelMatrixPC83[3][1] = terrain.getHeightTerrain(modelMatrixPC83[3][0], modelMatrixPC83[3][2]);
		glm::mat4 modelMatrixPC83Body = glm::mat4(modelMatrixPC83);
		modelMatrixPC83Body = glm::scale(modelMatrixPC83, glm::vec3(0.5, 0.5, 0.5));
		modelPC83.render(modelMatrixPC83Body);

		modelMatrixPC84[3][1] = terrain.getHeightTerrain(modelMatrixPC84[3][0], modelMatrixPC84[3][2]);
		glm::mat4 modelMatrixPC84Body = glm::mat4(modelMatrixPC84);
		modelMatrixPC84Body = glm::scale(modelMatrixPC84, glm::vec3(0.5, 0.5, 0.5));
		modelPC84.render(modelMatrixPC84Body);

		modelMatrixPC85[3][1] = terrain.getHeightTerrain(modelMatrixPC85[3][0], modelMatrixPC85[3][2]);
		glm::mat4 modelMatrixPC85Body = glm::mat4(modelMatrixPC85);
		modelMatrixPC85Body = glm::scale(modelMatrixPC85, glm::vec3(0.5, 0.5, 0.5));
		modelPC85.render(modelMatrixPC85Body);

		modelMatrixPC86[3][1] = terrain.getHeightTerrain(modelMatrixPC86[3][0], modelMatrixPC86[3][2]);
		glm::mat4 modelMatrixPC86Body = glm::mat4(modelMatrixPC86);
		modelMatrixPC86Body = glm::scale(modelMatrixPC86, glm::vec3(0.5, 0.5, 0.5));
		modelPC86.render(modelMatrixPC86Body);

		modelMatrixPC87[3][1] = terrain.getHeightTerrain(modelMatrixPC87[3][0], modelMatrixPC87[3][2]);
		glm::mat4 modelMatrixPC87Body = glm::mat4(modelMatrixPC87);
		modelMatrixPC87Body = glm::scale(modelMatrixPC87, glm::vec3(0.5, 0.5, 0.5));
		modelPC87.render(modelMatrixPC87Body);

		modelMatrixPC88[3][1] = terrain.getHeightTerrain(modelMatrixPC88[3][0], modelMatrixPC88[3][2]);
		glm::mat4 modelMatrixPC88Body = glm::mat4(modelMatrixPC88);
		modelMatrixPC88Body = glm::scale(modelMatrixPC88, glm::vec3(0.5, 0.5, 0.5));
		modelPC88.render(modelMatrixPC88Body);

		modelMatrixPC89[3][1] = terrain.getHeightTerrain(modelMatrixPC89[3][0], modelMatrixPC89[3][2]);
		glm::mat4 modelMatrixPC89Body = glm::mat4(modelMatrixPC89);
		modelMatrixPC89Body = glm::scale(modelMatrixPC89, glm::vec3(0.5, 0.5, 0.5));
		modelPC89.render(modelMatrixPC89Body);

		modelMatrixPC90[3][1] = terrain.getHeightTerrain(modelMatrixPC90[3][0], modelMatrixPC90[3][2]);
		glm::mat4 modelMatrixPC90Body = glm::mat4(modelMatrixPC90);
		modelMatrixPC90Body = glm::scale(modelMatrixPC90, glm::vec3(0.5, 0.5, 0.5));
		modelPC90.render(modelMatrixPC90Body);

		modelMatrixPC91[3][1] = terrain.getHeightTerrain(modelMatrixPC91[3][0], modelMatrixPC91[3][2]);
		glm::mat4 modelMatrixPC91Body = glm::mat4(modelMatrixPC91);
		modelMatrixPC91Body = glm::scale(modelMatrixPC91, glm::vec3(0.5, 0.5, 0.5));
		modelPC91.render(modelMatrixPC91Body);

		modelMatrixPC92[3][1] = terrain.getHeightTerrain(modelMatrixPC92[3][0], modelMatrixPC92[3][2]);
		glm::mat4 modelMatrixPC92Body = glm::mat4(modelMatrixPC92);
		modelMatrixPC92Body = glm::scale(modelMatrixPC92, glm::vec3(0.5, 0.5, 0.5));
		modelPC92.render(modelMatrixPC92Body);

		modelMatrixPC93[3][1] = terrain.getHeightTerrain(modelMatrixPC93[3][0], modelMatrixPC93[3][2]);
		glm::mat4 modelMatrixPC93Body = glm::mat4(modelMatrixPC93);
		modelMatrixPC93Body = glm::scale(modelMatrixPC93, glm::vec3(0.5, 0.5, 0.5));
		modelPC93.render(modelMatrixPC93Body);

		modelMatrixPC94[3][1] = terrain.getHeightTerrain(modelMatrixPC94[3][0], modelMatrixPC94[3][2]);
		glm::mat4 modelMatrixPC94Body = glm::mat4(modelMatrixPC94);
		modelMatrixPC94Body = glm::scale(modelMatrixPC94, glm::vec3(0.5, 0.5, 0.5));
		modelPC94.render(modelMatrixPC94Body);

		modelMatrixPC95[3][1] = terrain.getHeightTerrain(modelMatrixPC95[3][0], modelMatrixPC95[3][2]);
		glm::mat4 modelMatrixPC95Body = glm::mat4(modelMatrixPC95);
		modelMatrixPC95Body = glm::scale(modelMatrixPC95, glm::vec3(0.5, 0.5, 0.5));
		modelPC95.render(modelMatrixPC95Body);

		modelMatrixPC96[3][1] = terrain.getHeightTerrain(modelMatrixPC96[3][0], modelMatrixPC96[3][2]);
		glm::mat4 modelMatrixPC96Body = glm::mat4(modelMatrixPC96);
		modelMatrixPC96Body = glm::scale(modelMatrixPC96, glm::vec3(0.5, 0.5, 0.5));
		modelPC96.render(modelMatrixPC96Body);

		modelMatrixPC97[3][1] = terrain.getHeightTerrain(modelMatrixPC97[3][0], modelMatrixPC97[3][2]);
		glm::mat4 modelMatrixPC97Body = glm::mat4(modelMatrixPC97);
		modelMatrixPC97Body = glm::scale(modelMatrixPC97, glm::vec3(0.5, 0.5, 0.5));
		modelPC97.render(modelMatrixPC97Body);

		modelMatrixPC98[3][1] = terrain.getHeightTerrain(modelMatrixPC98[3][0], modelMatrixPC98[3][2]);
		glm::mat4 modelMatrixPC98Body = glm::mat4(modelMatrixPC98);
		modelMatrixPC98Body = glm::scale(modelMatrixPC98, glm::vec3(0.5, 0.5, 0.5));
		modelPC98.render(modelMatrixPC98Body);

		modelMatrixPC99[3][1] = terrain.getHeightTerrain(modelMatrixPC99[3][0], modelMatrixPC99[3][2]);
		glm::mat4 modelMatrixPC99Body = glm::mat4(modelMatrixPC99);
		modelMatrixPC99Body = glm::scale(modelMatrixPC99, glm::vec3(0.5, 0.5, 0.5));
		modelPC99.render(modelMatrixPC99Body);

		modelMatrixPC100[3][1] = terrain.getHeightTerrain(modelMatrixPC100[3][0], modelMatrixPC100[3][2]);
		glm::mat4 modelMatrixPC100Body = glm::mat4(modelMatrixPC100);
		modelMatrixPC100Body = glm::scale(modelMatrixPC100, glm::vec3(0.5, 0.5, 0.5));
		modelPC100.render(modelMatrixPC100Body);

		modelMatrixPC101[3][1] = terrain.getHeightTerrain(modelMatrixPC101[3][0], modelMatrixPC101[3][2]);
		glm::mat4 modelMatrixPC101Body = glm::mat4(modelMatrixPC101);
		modelMatrixPC101Body = glm::scale(modelMatrixPC101, glm::vec3(0.5, 0.5, 0.5));
		modelPC101.render(modelMatrixPC101Body);

		modelMatrixPC102[3][1] = terrain.getHeightTerrain(modelMatrixPC102[3][0], modelMatrixPC102[3][2]);
		glm::mat4 modelMatrixPC102Body = glm::mat4(modelMatrixPC102);
		modelMatrixPC102Body = glm::scale(modelMatrixPC102, glm::vec3(0.5, 0.5, 0.5));
		modelPC102.render(modelMatrixPC102Body);

		modelMatrixPC103[3][1] = terrain.getHeightTerrain(modelMatrixPC103[3][0], modelMatrixPC103[3][2]);
		glm::mat4 modelMatrixPC103Body = glm::mat4(modelMatrixPC103);
		modelMatrixPC103Body = glm::scale(modelMatrixPC103, glm::vec3(0.5, 0.5, 0.5));
		modelPC103.render(modelMatrixPC103Body);

		modelMatrixPC104[3][1] = terrain.getHeightTerrain(modelMatrixPC104[3][0], modelMatrixPC104[3][2]);
		glm::mat4 modelMatrixPC104Body = glm::mat4(modelMatrixPC104);
		modelMatrixPC104Body = glm::scale(modelMatrixPC104, glm::vec3(0.5, 0.5, 0.5));
		modelPC104.render(modelMatrixPC104Body);

		modelMatrixPC105[3][1] = terrain.getHeightTerrain(modelMatrixPC105[3][0], modelMatrixPC105[3][2]);
		glm::mat4 modelMatrixPC105Body = glm::mat4(modelMatrixPC105);
		modelMatrixPC105Body = glm::scale(modelMatrixPC105, glm::vec3(0.5, 0.5, 0.5));
		modelPC105.render(modelMatrixPC105Body);

		modelMatrixPC106[3][1] = terrain.getHeightTerrain(modelMatrixPC106[3][0], modelMatrixPC106[3][2]);
		glm::mat4 modelMatrixPC106Body = glm::mat4(modelMatrixPC106);
		modelMatrixPC106Body = glm::scale(modelMatrixPC106, glm::vec3(0.5, 0.5, 0.5));
		modelPC106.render(modelMatrixPC106Body);

		modelMatrixPC107[3][1] = terrain.getHeightTerrain(modelMatrixPC107[3][0], modelMatrixPC107[3][2]);
		glm::mat4 modelMatrixPC107Body = glm::mat4(modelMatrixPC107);
		modelMatrixPC107Body = glm::scale(modelMatrixPC107, glm::vec3(0.5, 0.5, 0.5));
		modelPC107.render(modelMatrixPC107Body);

		modelMatrixPC108[3][1] = terrain.getHeightTerrain(modelMatrixPC108[3][0], modelMatrixPC108[3][2]);
		glm::mat4 modelMatrixPC108Body = glm::mat4(modelMatrixPC108);
		modelMatrixPC108Body = glm::scale(modelMatrixPC108, glm::vec3(0.5, 0.5, 0.5));
		modelPC108.render(modelMatrixPC108Body);

		modelMatrixPC109[3][1] = terrain.getHeightTerrain(modelMatrixPC109[3][0], modelMatrixPC109[3][2]);
		glm::mat4 modelMatrixPC109Body = glm::mat4(modelMatrixPC109);
		modelMatrixPC109Body = glm::scale(modelMatrixPC109, glm::vec3(0.5, 0.5, 0.5));
		modelPC109.render(modelMatrixPC109Body);

		modelMatrixPC110[3][1] = terrain.getHeightTerrain(modelMatrixPC110[3][0], modelMatrixPC110[3][2]);
		glm::mat4 modelMatrixPC110Body = glm::mat4(modelMatrixPC110);
		modelMatrixPC110Body = glm::scale(modelMatrixPC110, glm::vec3(0.5, 0.5, 0.5));
		modelPC110.render(modelMatrixPC110Body);

		modelMatrixPC111[3][1] = terrain.getHeightTerrain(modelMatrixPC111[3][0], modelMatrixPC111[3][2]);
		glm::mat4 modelMatrixPC111Body = glm::mat4(modelMatrixPC111);
		modelMatrixPC111Body = glm::scale(modelMatrixPC111, glm::vec3(0.5, 0.5, 0.5));
		modelPC111.render(modelMatrixPC111Body);

		modelMatrixPC112[3][1] = terrain.getHeightTerrain(modelMatrixPC112[3][0], modelMatrixPC112[3][2]);
		glm::mat4 modelMatrixPC112Body = glm::mat4(modelMatrixPC112);
		modelMatrixPC112Body = glm::scale(modelMatrixPC112, glm::vec3(0.5, 0.5, 0.5));
		modelPC112.render(modelMatrixPC112Body);

		modelMatrixPC113[3][1] = terrain.getHeightTerrain(modelMatrixPC113[3][0], modelMatrixPC113[3][2]);
		glm::mat4 modelMatrixPC113Body = glm::mat4(modelMatrixPC113);
		modelMatrixPC113Body = glm::scale(modelMatrixPC113, glm::vec3(0.5, 0.5, 0.5));
		modelPC113.render(modelMatrixPC113Body);

		modelMatrixPC114[3][1] = terrain.getHeightTerrain(modelMatrixPC114[3][0], modelMatrixPC114[3][2]);
		glm::mat4 modelMatrixPC114Body = glm::mat4(modelMatrixPC114);
		modelMatrixPC114Body = glm::scale(modelMatrixPC114, glm::vec3(0.5, 0.5, 0.5));
		modelPC114.render(modelMatrixPC114Body);

		modelMatrixPC115[3][1] = terrain.getHeightTerrain(modelMatrixPC115[3][0], modelMatrixPC115[3][2]);
		glm::mat4 modelMatrixPC115Body = glm::mat4(modelMatrixPC115);
		modelMatrixPC115Body = glm::scale(modelMatrixPC115, glm::vec3(0.5, 0.5, 0.5));
		modelPC115.render(modelMatrixPC115Body);

		modelMatrixPC116[3][1] = terrain.getHeightTerrain(modelMatrixPC116[3][0], modelMatrixPC116[3][2]);
		glm::mat4 modelMatrixPC116Body = glm::mat4(modelMatrixPC116);
		modelMatrixPC116Body = glm::scale(modelMatrixPC116, glm::vec3(0.5, 0.5, 0.5));
		modelPC116.render(modelMatrixPC116Body);

		modelMatrixPC117[3][1] = terrain.getHeightTerrain(modelMatrixPC117[3][0], modelMatrixPC117[3][2]);
		glm::mat4 modelMatrixPC117Body = glm::mat4(modelMatrixPC117);
		modelMatrixPC117Body = glm::scale(modelMatrixPC117, glm::vec3(0.5, 0.5, 0.5));
		modelPC117.render(modelMatrixPC117Body);

		modelMatrixPC118[3][1] = terrain.getHeightTerrain(modelMatrixPC118[3][0], modelMatrixPC118[3][2]);
		glm::mat4 modelMatrixPC118Body = glm::mat4(modelMatrixPC118);
		modelMatrixPC118Body = glm::scale(modelMatrixPC118, glm::vec3(0.5, 0.5, 0.5));
		modelPC118.render(modelMatrixPC118Body);

		modelMatrixPC119[3][1] = terrain.getHeightTerrain(modelMatrixPC119[3][0], modelMatrixPC119[3][2]);
		glm::mat4 modelMatrixPC119Body = glm::mat4(modelMatrixPC119);
		modelMatrixPC119Body = glm::scale(modelMatrixPC119, glm::vec3(0.5, 0.5, 0.5));
		modelPC119.render(modelMatrixPC119Body);

		modelMatrixPC120[3][1] = terrain.getHeightTerrain(modelMatrixPC120[3][0], modelMatrixPC120[3][2]);
		glm::mat4 modelMatrixPC120Body = glm::mat4(modelMatrixPC120);
		modelMatrixPC120Body = glm::scale(modelMatrixPC120, glm::vec3(0.5, 0.5, 0.5));
		modelPC120.render(modelMatrixPC120Body);

		modelMatrixPC121[3][1] = terrain.getHeightTerrain(modelMatrixPC121[3][0], modelMatrixPC121[3][2]);
		glm::mat4 modelMatrixPC121Body = glm::mat4(modelMatrixPC121);
		modelMatrixPC121Body = glm::scale(modelMatrixPC121, glm::vec3(0.5, 0.5, 0.5));
		modelPC121.render(modelMatrixPC121Body);

		modelMatrixPC122[3][1] = terrain.getHeightTerrain(modelMatrixPC122[3][0], modelMatrixPC122[3][2]);
		glm::mat4 modelMatrixPC122Body = glm::mat4(modelMatrixPC122);
		modelMatrixPC122Body = glm::scale(modelMatrixPC122, glm::vec3(0.5, 0.5, 0.5));
		modelPC122.render(modelMatrixPC122Body);

		modelMatrixPC123[3][1] = terrain.getHeightTerrain(modelMatrixPC123[3][0], modelMatrixPC123[3][2]);
		glm::mat4 modelMatrixPC123Body = glm::mat4(modelMatrixPC123);
		modelMatrixPC123Body = glm::scale(modelMatrixPC123, glm::vec3(0.5, 0.5, 0.5));
		modelPC123.render(modelMatrixPC123Body);

		modelMatrixPC124[3][1] = terrain.getHeightTerrain(modelMatrixPC124[3][0], modelMatrixPC124[3][2]);
		glm::mat4 modelMatrixPC124Body = glm::mat4(modelMatrixPC124);
		modelMatrixPC124Body = glm::scale(modelMatrixPC124, glm::vec3(0.5, 0.5, 0.5));
		modelPC124.render(modelMatrixPC124Body);

		modelMatrixPC125[3][1] = terrain.getHeightTerrain(modelMatrixPC125[3][0], modelMatrixPC125[3][2]);
		glm::mat4 modelMatrixPC125Body = glm::mat4(modelMatrixPC125);
		modelMatrixPC125Body = glm::scale(modelMatrixPC125, glm::vec3(0.5, 0.5, 0.5));
		modelPC125.render(modelMatrixPC125Body);

		modelMatrixPC126[3][1] = terrain.getHeightTerrain(modelMatrixPC126[3][0], modelMatrixPC126[3][2]);
		glm::mat4 modelMatrixPC126Body = glm::mat4(modelMatrixPC126);
		modelMatrixPC126Body = glm::scale(modelMatrixPC126, glm::vec3(0.5, 0.5, 0.5));
		modelPC126.render(modelMatrixPC126Body);

		modelMatrixPC127[3][1] = terrain.getHeightTerrain(modelMatrixPC127[3][0], modelMatrixPC127[3][2]);
		glm::mat4 modelMatrixPC127Body = glm::mat4(modelMatrixPC127);
		modelMatrixPC127Body = glm::scale(modelMatrixPC127, glm::vec3(0.5, 0.5, 0.5));
		modelPC127.render(modelMatrixPC127Body);

		modelMatrixPC128[3][1] = terrain.getHeightTerrain(modelMatrixPC128[3][0], modelMatrixPC128[3][2]);
		glm::mat4 modelMatrixPC128Body = glm::mat4(modelMatrixPC128);
		modelMatrixPC128Body = glm::scale(modelMatrixPC128, glm::vec3(0.5, 0.5, 0.5));
		modelPC128.render(modelMatrixPC128Body);

		modelMatrixPC129[3][1] = terrain.getHeightTerrain(modelMatrixPC129[3][0], modelMatrixPC129[3][2]);
		glm::mat4 modelMatrixPC129Body = glm::mat4(modelMatrixPC129);
		modelMatrixPC129Body = glm::scale(modelMatrixPC129, glm::vec3(0.5, 0.5, 0.5));
		modelPC129.render(modelMatrixPC129Body);

		modelMatrixPC130[3][1] = terrain.getHeightTerrain(modelMatrixPC130[3][0], modelMatrixPC130[3][2]);
		glm::mat4 modelMatrixPC130Body = glm::mat4(modelMatrixPC130);
		modelMatrixPC130Body = glm::scale(modelMatrixPC130, glm::vec3(0.5, 0.5, 0.5));
		modelPC130.render(modelMatrixPC130Body);
		
		modelMatrixPC131[3][1] = terrain.getHeightTerrain(modelMatrixPC131[3][0], modelMatrixPC131[3][2]);
		glm::mat4 modelMatrixPC131Body = glm::mat4(modelMatrixPC131);
		modelMatrixPC131Body = glm::scale(modelMatrixPC131, glm::vec3(0.5, 0.5, 0.5));
		modelPC131.render(modelMatrixPC131Body);

		modelMatrixPC132[3][1] = terrain.getHeightTerrain(modelMatrixPC132[3][0], modelMatrixPC132[3][2]);
		glm::mat4 modelMatrixPC132Body = glm::mat4(modelMatrixPC132);
		modelMatrixPC132Body = glm::scale(modelMatrixPC132, glm::vec3(0.5, 0.5, 0.5));
		modelPC132.render(modelMatrixPC132Body);

		modelMatrixPC133[3][1] = terrain.getHeightTerrain(modelMatrixPC133[3][0], modelMatrixPC133[3][2]);
		glm::mat4 modelMatrixPC133Body = glm::mat4(modelMatrixPC133);
		modelMatrixPC133Body = glm::scale(modelMatrixPC133, glm::vec3(0.5, 0.5, 0.5));
		modelPC133.render(modelMatrixPC133Body);

		modelMatrixPC134[3][1] = terrain.getHeightTerrain(modelMatrixPC134[3][0], modelMatrixPC134[3][2]);
		glm::mat4 modelMatrixPC134Body = glm::mat4(modelMatrixPC134);
		modelMatrixPC134Body = glm::scale(modelMatrixPC134, glm::vec3(0.5, 0.5, 0.5));
		modelPC134.render(modelMatrixPC134Body);

		modelMatrixPC135[3][1] = terrain.getHeightTerrain(modelMatrixPC135[3][0], modelMatrixPC135[3][2]);
		glm::mat4 modelMatrixPC135Body = glm::mat4(modelMatrixPC135);
		modelMatrixPC135Body = glm::scale(modelMatrixPC135, glm::vec3(0.5, 0.5, 0.5));
		modelPC135.render(modelMatrixPC135Body);

		modelMatrixPC136[3][1] = terrain.getHeightTerrain(modelMatrixPC136[3][0], modelMatrixPC136[3][2]);
		glm::mat4 modelMatrixPC136Body = glm::mat4(modelMatrixPC136);
		modelMatrixPC136Body = glm::scale(modelMatrixPC136, glm::vec3(0.5, 0.5, 0.5));
		modelPC136.render(modelMatrixPC136Body);

		modelMatrixPC137[3][1] = terrain.getHeightTerrain(modelMatrixPC137[3][0], modelMatrixPC137[3][2]);
		glm::mat4 modelMatrixPC137Body = glm::mat4(modelMatrixPC137);
		modelMatrixPC137Body = glm::scale(modelMatrixPC137, glm::vec3(0.5, 0.5, 0.5));
		modelPC137.render(modelMatrixPC137Body);

		modelMatrixPC138[3][1] = terrain.getHeightTerrain(modelMatrixPC138[3][0], modelMatrixPC138[3][2]);
		glm::mat4 modelMatrixPC138Body = glm::mat4(modelMatrixPC138);
		modelMatrixPC138Body = glm::scale(modelMatrixPC138, glm::vec3(0.5, 0.5, 0.5));
		modelPC138.render(modelMatrixPC138Body);

		modelMatrixPC139[3][1] = terrain.getHeightTerrain(modelMatrixPC139[3][0], modelMatrixPC139[3][2]);
		glm::mat4 modelMatrixPC139Body = glm::mat4(modelMatrixPC139);
		modelMatrixPC139Body = glm::scale(modelMatrixPC139, glm::vec3(0.5, 0.5, 0.5));
		modelPC139.render(modelMatrixPC139Body);

		modelMatrixPC140[3][1] = terrain.getHeightTerrain(modelMatrixPC140[3][0], modelMatrixPC140[3][2]);
		glm::mat4 modelMatrixPC140Body = glm::mat4(modelMatrixPC140);
		modelMatrixPC140Body = glm::scale(modelMatrixPC140, glm::vec3(0.5, 0.5, 0.5));
		modelPC140.render(modelMatrixPC140Body);

		modelMatrixPC141[3][1] = terrain.getHeightTerrain(modelMatrixPC141[3][0], modelMatrixPC141[3][2]);
		glm::mat4 modelMatrixPC141Body = glm::mat4(modelMatrixPC141);
		modelMatrixPC141Body = glm::scale(modelMatrixPC141, glm::vec3(0.5, 0.5, 0.5));
		modelPC141.render(modelMatrixPC141Body);

		modelMatrixPC142[3][1] = terrain.getHeightTerrain(modelMatrixPC142[3][0], modelMatrixPC142[3][2]);
		glm::mat4 modelMatrixPC142Body = glm::mat4(modelMatrixPC142);
		modelMatrixPC142Body = glm::scale(modelMatrixPC142, glm::vec3(0.5, 0.5, 0.5));
		modelPC142.render(modelMatrixPC142Body);

		modelMatrixPC143[3][1] = terrain.getHeightTerrain(modelMatrixPC143[3][0], modelMatrixPC143[3][2]);
		glm::mat4 modelMatrixPC143Body = glm::mat4(modelMatrixPC143);
		modelMatrixPC143Body = glm::scale(modelMatrixPC143, glm::vec3(0.5, 0.5, 0.5));
		modelPC143.render(modelMatrixPC143Body);

		modelMatrixPC144[3][1] = terrain.getHeightTerrain(modelMatrixPC144[3][0], modelMatrixPC144[3][2]);
		glm::mat4 modelMatrixPC144Body = glm::mat4(modelMatrixPC144);
		modelMatrixPC144Body = glm::scale(modelMatrixPC144, glm::vec3(0.5, 0.5, 0.5));
		modelPC144.render(modelMatrixPC144Body);

		modelMatrixPC145[3][1] = terrain.getHeightTerrain(modelMatrixPC145[3][0], modelMatrixPC145[3][2]);
		glm::mat4 modelMatrixPC145Body = glm::mat4(modelMatrixPC145);
		modelMatrixPC145Body = glm::scale(modelMatrixPC145, glm::vec3(0.5, 0.5, 0.5));
		modelPC145.render(modelMatrixPC145Body);

		modelMatrixPC146[3][1] = terrain.getHeightTerrain(modelMatrixPC146[3][0], modelMatrixPC146[3][2]);
		glm::mat4 modelMatrixPC146Body = glm::mat4(modelMatrixPC146);
		modelMatrixPC146Body = glm::scale(modelMatrixPC146, glm::vec3(0.5, 0.5, 0.5));
		modelPC146.render(modelMatrixPC146Body);

		modelMatrixPC147[3][1] = terrain.getHeightTerrain(modelMatrixPC147[3][0], modelMatrixPC147[3][2]);
		glm::mat4 modelMatrixPC147Body = glm::mat4(modelMatrixPC147);
		modelMatrixPC147Body = glm::scale(modelMatrixPC147, glm::vec3(0.5, 0.5, 0.5));
		modelPC147.render(modelMatrixPC147Body);

		modelMatrixPC148[3][1] = terrain.getHeightTerrain(modelMatrixPC148[3][0], modelMatrixPC148[3][2]);
		glm::mat4 modelMatrixPC148Body = glm::mat4(modelMatrixPC148);
		modelMatrixPC148Body = glm::scale(modelMatrixPC148, glm::vec3(0.5, 0.5, 0.5));
		modelPC148.render(modelMatrixPC148Body);

		modelMatrixPC149[3][1] = terrain.getHeightTerrain(modelMatrixPC149[3][0], modelMatrixPC149[3][2]);
		glm::mat4 modelMatrixPC149Body = glm::mat4(modelMatrixPC149);
		modelMatrixPC149Body = glm::scale(modelMatrixPC149, glm::vec3(0.5, 0.5, 0.5));
		modelPC149.render(modelMatrixPC149Body);

		modelMatrixPC150[3][1] = terrain.getHeightTerrain(modelMatrixPC150[3][0], modelMatrixPC150[3][2]);
		glm::mat4 modelMatrixPC150Body = glm::mat4(modelMatrixPC150);
		modelMatrixPC150Body = glm::scale(modelMatrixPC150, glm::vec3(0.5, 0.5, 0.5));
		modelPC150.render(modelMatrixPC150Body);
		
		modelMatrixPC151[3][1] = terrain.getHeightTerrain(modelMatrixPC151[3][0], modelMatrixPC151[3][2]);
		glm::mat4 modelMatrixPC151Body = glm::mat4(modelMatrixPC151);
		modelMatrixPC151Body = glm::scale(modelMatrixPC151, glm::vec3(0.5, 0.5, 0.5));
		modelPC151.render(modelMatrixPC151Body);
		
		modelMatrixPC152[3][1] = terrain.getHeightTerrain(modelMatrixPC152[3][0], modelMatrixPC152[3][2]);
		glm::mat4 modelMatrixPC152Body = glm::mat4(modelMatrixPC152);
		modelMatrixPC152Body = glm::scale(modelMatrixPC152, glm::vec3(0.5, 0.5, 0.5));
		modelPC152.render(modelMatrixPC152Body);

		modelMatrixPC153[3][1] = terrain.getHeightTerrain(modelMatrixPC153[3][0], modelMatrixPC153[3][2]);
		glm::mat4 modelMatrixPC153Body = glm::mat4(modelMatrixPC153);
		modelMatrixPC153Body = glm::scale(modelMatrixPC153, glm::vec3(0.5, 0.5, 0.5));
		modelPC153.render(modelMatrixPC153Body);

		modelMatrixPC154[3][1] = terrain.getHeightTerrain(modelMatrixPC154[3][0], modelMatrixPC154[3][2]);
		glm::mat4 modelMatrixPC154Body = glm::mat4(modelMatrixPC154);
		modelMatrixPC154Body = glm::scale(modelMatrixPC154, glm::vec3(0.5, 0.5, 0.5));
		modelPC154.render(modelMatrixPC154Body);

		modelMatrixPC155[3][1] = terrain.getHeightTerrain(modelMatrixPC155[3][0], modelMatrixPC155[3][2]);
		glm::mat4 modelMatrixPC155Body = glm::mat4(modelMatrixPC155);
		modelMatrixPC155Body = glm::scale(modelMatrixPC155, glm::vec3(0.5, 0.5, 0.5));
		modelPC155.render(modelMatrixPC155Body);
		
		modelMatrixPC156[3][1] = terrain.getHeightTerrain(modelMatrixPC156[3][0], modelMatrixPC156[3][2]);
		glm::mat4 modelMatrixPC156Body = glm::mat4(modelMatrixPC156);
		modelMatrixPC156Body = glm::scale(modelMatrixPC156, glm::vec3(0.5, 0.5, 0.5));
		modelPC156.render(modelMatrixPC156Body);

		modelMatrixPC157[3][1] = terrain.getHeightTerrain(modelMatrixPC157[3][0], modelMatrixPC157[3][2]);
		glm::mat4 modelMatrixPC157Body = glm::mat4(modelMatrixPC157);
		modelMatrixPC157Body = glm::scale(modelMatrixPC157, glm::vec3(0.5, 0.5, 0.5));
		modelPC157.render(modelMatrixPC157Body);

		modelMatrixPC158[3][1] = terrain.getHeightTerrain(modelMatrixPC158[3][0], modelMatrixPC158[3][2]);
		glm::mat4 modelMatrixPC158Body = glm::mat4(modelMatrixPC158);
		modelMatrixPC158Body = glm::scale(modelMatrixPC158, glm::vec3(0.5, 0.5, 0.5));
		modelPC158.render(modelMatrixPC158Body);

		modelMatrixPC159[3][1] = terrain.getHeightTerrain(modelMatrixPC159[3][0], modelMatrixPC159[3][2]);
		glm::mat4 modelMatrixPC159Body = glm::mat4(modelMatrixPC159);
		modelMatrixPC159Body = glm::scale(modelMatrixPC159, glm::vec3(0.5, 0.5, 0.5));
		modelPC159.render(modelMatrixPC159Body);

		modelMatrixPC160[3][1] = terrain.getHeightTerrain(modelMatrixPC160[3][0], modelMatrixPC160[3][2]);
		glm::mat4 modelMatrixPC160Body = glm::mat4(modelMatrixPC160);
		modelMatrixPC160Body = glm::scale(modelMatrixPC160, glm::vec3(0.5, 0.5, 0.5));
		modelPC160.render(modelMatrixPC160Body);

		modelMatrixPC161[3][1] = terrain.getHeightTerrain(modelMatrixPC161[3][0], modelMatrixPC161[3][2]);
		glm::mat4 modelMatrixPC161Body = glm::mat4(modelMatrixPC161);
		modelMatrixPC161Body = glm::scale(modelMatrixPC161, glm::vec3(0.5, 0.5, 0.5));
		modelPC161.render(modelMatrixPC161Body);

		modelMatrixPC162[3][1] = terrain.getHeightTerrain(modelMatrixPC162[3][0], modelMatrixPC162[3][2]);
		glm::mat4 modelMatrixPC162Body = glm::mat4(modelMatrixPC162);
		modelMatrixPC162Body = glm::scale(modelMatrixPC162, glm::vec3(0.5, 0.5, 0.5));
		modelPC162.render(modelMatrixPC162Body);

		modelMatrixPC163[3][1] = terrain.getHeightTerrain(modelMatrixPC163[3][0], modelMatrixPC163[3][2]);
		glm::mat4 modelMatrixPC163Body = glm::mat4(modelMatrixPC163);
		modelMatrixPC163Body = glm::scale(modelMatrixPC163, glm::vec3(0.5, 0.5, 0.5));
		modelPC163.render(modelMatrixPC163Body);

		modelMatrixPC164[3][1] = terrain.getHeightTerrain(modelMatrixPC164[3][0], modelMatrixPC164[3][2]);
		glm::mat4 modelMatrixPC164Body = glm::mat4(modelMatrixPC164);
		modelMatrixPC164Body = glm::scale(modelMatrixPC164, glm::vec3(0.5, 0.5, 0.5));
		modelPC160.render(modelMatrixPC164Body);

		modelMatrixPC165[3][1] = terrain.getHeightTerrain(modelMatrixPC165[3][0], modelMatrixPC165[3][2]);
		glm::mat4 modelMatrixPC165Body = glm::mat4(modelMatrixPC165);
		modelMatrixPC165Body = glm::scale(modelMatrixPC165, glm::vec3(0.5, 0.5, 0.5));
		modelPC165.render(modelMatrixPC165Body);

		modelMatrixPC166[3][1] = terrain.getHeightTerrain(modelMatrixPC166[3][0], modelMatrixPC166[3][2]);
		glm::mat4 modelMatrixPC166Body = glm::mat4(modelMatrixPC166);
		modelMatrixPC166Body = glm::scale(modelMatrixPC166, glm::vec3(0.5, 0.5, 0.5));
		modelPC166.render(modelMatrixPC166Body);

		modelMatrixPC167[3][1] = terrain.getHeightTerrain(modelMatrixPC167[3][0], modelMatrixPC167[3][2]);
		glm::mat4 modelMatrixPC167Body = glm::mat4(modelMatrixPC167);
		modelMatrixPC167Body = glm::scale(modelMatrixPC167, glm::vec3(0.5, 0.5, 0.5));
		modelPC167.render(modelMatrixPC167Body);

		modelMatrixPC168[3][1] = terrain.getHeightTerrain(modelMatrixPC168[3][0], modelMatrixPC168[3][2]);
		glm::mat4 modelMatrixPC168Body = glm::mat4(modelMatrixPC168);
		modelMatrixPC168Body = glm::scale(modelMatrixPC168, glm::vec3(0.5, 0.5, 0.5));
		modelPC168.render(modelMatrixPC168Body);

		modelMatrixPC169[3][1] = terrain.getHeightTerrain(modelMatrixPC169[3][0], modelMatrixPC169[3][2]);
		glm::mat4 modelMatrixPC169Body = glm::mat4(modelMatrixPC169);
		modelMatrixPC169Body = glm::scale(modelMatrixPC169, glm::vec3(0.5, 0.5, 0.5));
		modelPC169.render(modelMatrixPC169Body);
		
		modelMatrixPC170[3][1] = terrain.getHeightTerrain(modelMatrixPC170[3][0], modelMatrixPC170[3][2]);
		glm::mat4 modelMatrixPC170Body = glm::mat4(modelMatrixPC170);
		modelMatrixPC170Body = glm::scale(modelMatrixPC170, glm::vec3(0.5, 0.5, 0.5));
		modelPC170.render(modelMatrixPC170Body);
	
		modelMatrixPC171[3][1] = terrain.getHeightTerrain(modelMatrixPC171[3][0], modelMatrixPC171[3][2]);
		glm::mat4 modelMatrixPC171Body = glm::mat4(modelMatrixPC171);
		modelMatrixPC171Body = glm::scale(modelMatrixPC171, glm::vec3(0.5, 0.5, 0.5));
		modelPC171.render(modelMatrixPC171Body);

		modelMatrixPC172[3][1] = terrain.getHeightTerrain(modelMatrixPC172[3][0], modelMatrixPC172[3][2]);
		glm::mat4 modelMatrixPC172Body = glm::mat4(modelMatrixPC172);
		modelMatrixPC172Body = glm::scale(modelMatrixPC172, glm::vec3(0.5, 0.5, 0.5));
		modelPC172.render(modelMatrixPC172Body);

		modelMatrixPC173[3][1] = terrain.getHeightTerrain(modelMatrixPC173[3][0], modelMatrixPC173[3][2]);
		glm::mat4 modelMatrixPC173Body = glm::mat4(modelMatrixPC173);
		modelMatrixPC173Body = glm::scale(modelMatrixPC173, glm::vec3(0.5, 0.5, 0.5));
		modelPC173.render(modelMatrixPC173Body);

		modelMatrixPC174[3][1] = terrain.getHeightTerrain(modelMatrixPC174[3][0], modelMatrixPC174[3][2]);
		glm::mat4 modelMatrixPC174Body = glm::mat4(modelMatrixPC174);
		modelMatrixPC174Body = glm::scale(modelMatrixPC174, glm::vec3(0.5, 0.5, 0.5));
		modelPC174.render(modelMatrixPC174Body);

		modelMatrixPC175[3][1] = terrain.getHeightTerrain(modelMatrixPC175[3][0], modelMatrixPC175[3][2]);
		glm::mat4 modelMatrixPC175Body = glm::mat4(modelMatrixPC175);
		modelMatrixPC175Body = glm::scale(modelMatrixPC175, glm::vec3(0.5, 0.5, 0.5));
		modelPC175.render(modelMatrixPC175Body);
		
		modelMatrixPC176[3][1] = terrain.getHeightTerrain(modelMatrixPC176[3][0], modelMatrixPC176[3][2]);
		glm::mat4 modelMatrixPC176Body = glm::mat4(modelMatrixPC176);
		modelMatrixPC176Body = glm::scale(modelMatrixPC176, glm::vec3(0.5, 0.5, 0.5));
		modelPC176.render(modelMatrixPC176Body);

		modelMatrixPC177[3][1] = terrain.getHeightTerrain(modelMatrixPC177[3][0], modelMatrixPC177[3][2]);
		glm::mat4 modelMatrixPC177Body = glm::mat4(modelMatrixPC177);
		modelMatrixPC177Body = glm::scale(modelMatrixPC177, glm::vec3(0.5, 0.5, 0.5));
		modelPC177.render(modelMatrixPC177Body);

		modelMatrixPC178[3][1] = terrain.getHeightTerrain(modelMatrixPC178[3][0], modelMatrixPC178[3][2]);
		glm::mat4 modelMatrixPC178Body = glm::mat4(modelMatrixPC178);
		modelMatrixPC178Body = glm::scale(modelMatrixPC178, glm::vec3(0.5, 0.5, 0.5));
		modelPC178.render(modelMatrixPC178Body);

		modelMatrixPC179[3][1] = terrain.getHeightTerrain(modelMatrixPC179[3][0], modelMatrixPC179[3][2]);
		glm::mat4 modelMatrixPC179Body = glm::mat4(modelMatrixPC179);
		modelMatrixPC179Body = glm::scale(modelMatrixPC179, glm::vec3(0.5, 0.5, 0.5));
		modelPC179.render(modelMatrixPC179Body);
		
		modelMatrixPC180[3][1] = terrain.getHeightTerrain(modelMatrixPC180[3][0], modelMatrixPC180[3][2]);
		glm::mat4 modelMatrixPC180Body = glm::mat4(modelMatrixPC180);
		modelMatrixPC180Body = glm::scale(modelMatrixPC180, glm::vec3(0.5, 0.5, 0.5));
		modelPC180.render(modelMatrixPC180Body);

		modelMatrixPC181[3][1] = terrain.getHeightTerrain(modelMatrixPC181[3][0], modelMatrixPC181[3][2]);
		glm::mat4 modelMatrixPC181Body = glm::mat4(modelMatrixPC181);
		modelMatrixPC181Body = glm::scale(modelMatrixPC181, glm::vec3(0.5, 0.5, 0.5));
		modelPC181.render(modelMatrixPC181Body);

		modelMatrixPC182[3][1] = terrain.getHeightTerrain(modelMatrixPC182[3][0], modelMatrixPC182[3][2]);
		glm::mat4 modelMatrixPC182Body = glm::mat4(modelMatrixPC182);
		modelMatrixPC182Body = glm::scale(modelMatrixPC182, glm::vec3(0.5, 0.5, 0.5));
		modelPC182.render(modelMatrixPC182Body);

		modelMatrixPC183[3][1] = terrain.getHeightTerrain(modelMatrixPC183[3][0], modelMatrixPC183[3][2]);
		glm::mat4 modelMatrixPC183Body = glm::mat4(modelMatrixPC183);
		modelMatrixPC183Body = glm::scale(modelMatrixPC183, glm::vec3(0.5, 0.5, 0.5));
		modelPC183.render(modelMatrixPC183Body);

		modelMatrixPC184[3][1] = terrain.getHeightTerrain(modelMatrixPC184[3][0], modelMatrixPC184[3][2]);
		glm::mat4 modelMatrixPC184Body = glm::mat4(modelMatrixPC184);
		modelMatrixPC184Body = glm::scale(modelMatrixPC184, glm::vec3(0.5, 0.5, 0.5));
		modelPC184.render(modelMatrixPC184Body);

		modelMatrixPC185[3][1] = terrain.getHeightTerrain(modelMatrixPC185[3][0], modelMatrixPC185[3][2]);
		glm::mat4 modelMatrixPC185Body = glm::mat4(modelMatrixPC185);
		modelMatrixPC185Body = glm::scale(modelMatrixPC185, glm::vec3(0.5, 0.5, 0.5));
		modelPC185.render(modelMatrixPC185Body);

		modelMatrixPC186[3][1] = terrain.getHeightTerrain(modelMatrixPC186[3][0], modelMatrixPC186[3][2]);
		glm::mat4 modelMatrixPC186Body = glm::mat4(modelMatrixPC186);
		modelMatrixPC186Body = glm::scale(modelMatrixPC186, glm::vec3(0.5, 0.5, 0.5));
		modelPC186.render(modelMatrixPC186Body);
		
		/*******************************************
		 * Skybox
		 *******************************************/
		GLint oldCullFaceMode;
		GLint oldDepthFuncMode;
		// deshabilita el modo del recorte de caras ocultas para ver las esfera desde adentro
		glGetIntegerv(GL_CULL_FACE_MODE, &oldCullFaceMode);
		glGetIntegerv(GL_DEPTH_FUNC, &oldDepthFuncMode);
		shaderSkybox.setFloat("skybox", 0);
		glCullFace(GL_FRONT);
		glDepthFunc(GL_LEQUAL);
		glActiveTexture(GL_TEXTURE0);
		skyboxSphere.render();
		glCullFace(oldCullFaceMode);
		glDepthFunc(oldDepthFuncMode);
		renderScene();
		/*******************************************
		 * Debug to box light box
		 *******************************************/
		/*glm::vec3 front = glm::normalize(-lightPos);
		glm::vec3 right = glm::normalize(glm::cross(glm::vec3(0, 1, 0), front));
		glm::vec3 up = glm::normalize(glm::cross(front, right));
		glDisable(GL_CULL_FACE);
		glm::mat4 boxViewTransform = glm::mat4(1.0f);
		boxViewTransform = glm::translate(boxViewTransform, centerBox);
		boxViewTransform[0] = glm::vec4(right, 0.0);
		boxViewTransform[1] = glm::vec4(up, 0.0);
		boxViewTransform[2] = glm::vec4(front, 0.0);
		boxViewTransform = glm::scale(boxViewTransform, glm::vec3(shadowBox->getWidth(), shadowBox->getHeight(), shadowBox->getLength()));
		boxLightViewBox.enableWireMode();
		boxLightViewBox.render(boxViewTransform);
		glEnable(GL_CULL_FACE);*/

		/*******************************************
		 * Creacion de colliders
		 * IMPORTANT do this before interpolations
		 *******************************************/
		
		// Collider de los Boo's

		glm::mat4 modelMatrixColliderBoo1 = glm::mat4(modelMatrixBoo1);
		AbstractModel::OBB Boo1Collider;
		Boo1Collider.u = glm::quat_cast(modelMatrixBoo1);
		modelMatrixColliderBoo1[3][1] = terrain.getHeightTerrain(modelMatrixColliderBoo1[3][0], modelMatrixColliderBoo1[3][2]);
		modelMatrixColliderBoo1 = glm::scale(modelMatrixColliderBoo1, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderBoo1 = glm::translate(modelMatrixColliderBoo1, modelBoo1.getObb().c);
		Boo1Collider.c = glm::vec3(modelMatrixColliderBoo1[3]);
		Boo1Collider.e = modelBoo1.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "Boo1", Boo1Collider, modelMatrixBoo1);

		glm::mat4 modelMatrixColliderBoo2 = glm::mat4(modelMatrixBoo2);
		AbstractModel::OBB Boo2Collider;
		Boo2Collider.u = glm::quat_cast(modelMatrixBoo2);
		modelMatrixColliderBoo2[3][1] = terrain.getHeightTerrain(modelMatrixColliderBoo2[3][0], modelMatrixColliderBoo2[3][2]);
		modelMatrixColliderBoo2 = glm::scale(modelMatrixColliderBoo2, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderBoo2 = glm::translate(modelMatrixColliderBoo2, modelBoo2.getObb().c);
		Boo2Collider.c = glm::vec3(modelMatrixColliderBoo2[3]);
		Boo2Collider.e = modelBoo2.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "Boo2", Boo2Collider, modelMatrixBoo2);

		glm::mat4 modelMatrixColliderBoo3 = glm::mat4(modelMatrixBoo3);
		AbstractModel::OBB Boo3Collider;
		Boo3Collider.u = glm::quat_cast(modelMatrixBoo3);
		modelMatrixColliderBoo3[3][1] = terrain.getHeightTerrain(modelMatrixColliderBoo3[3][0], modelMatrixColliderBoo3[3][2]);
		modelMatrixColliderBoo3 = glm::scale(modelMatrixColliderBoo3, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderBoo3 = glm::translate(modelMatrixColliderBoo3, modelBoo3.getObb().c);
		Boo3Collider.c = glm::vec3(modelMatrixColliderBoo3[3]);
		Boo3Collider.e = modelBoo3.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "Boo3", Boo3Collider, modelMatrixBoo3);

		glm::mat4 modelMatrixColliderBoo4 = glm::mat4(modelMatrixBoo4);
		AbstractModel::OBB Boo4Collider;
		Boo4Collider.u = glm::quat_cast(modelMatrixBoo4);
		modelMatrixColliderBoo4[3][1] = terrain.getHeightTerrain(modelMatrixColliderBoo4[3][0], modelMatrixColliderBoo4[3][2]);
		modelMatrixColliderBoo4 = glm::scale(modelMatrixColliderBoo4, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderBoo4 = glm::translate(modelMatrixColliderBoo4, modelBoo4.getObb().c);
		Boo4Collider.c = glm::vec3(modelMatrixColliderBoo4[3]);
		Boo4Collider.e = modelBoo4.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "Boo4", Boo4Collider, modelMatrixBoo4);

		// Collider del Cuerpo

		glm::mat4 modelMatrixColliderCuerpo = glm::mat4(modelMatrixCuerpo);
		AbstractModel::OBB CuerpoCollider;
		CuerpoCollider.u = glm::quat_cast(modelMatrixCuerpo);
		modelMatrixColliderCuerpo[3][1] = terrain.getHeightTerrain(modelMatrixColliderCuerpo[3][0], modelMatrixColliderCuerpo[3][2]);
		modelMatrixColliderCuerpo = glm::scale(modelMatrixColliderCuerpo, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderCuerpo = glm::translate(modelMatrixColliderCuerpo, modelCuerpo.getObb().c);
		CuerpoCollider.c = glm::vec3(modelMatrixColliderCuerpo[3]);
		CuerpoCollider.e = modelCuerpo.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "Cuerpo", CuerpoCollider, modelMatrixCuerpo);
		
		// Collider del Laberinto

		glm::mat4 modelMatrixColliderPEA = glm::mat4(modelMatrixPEA);
		AbstractModel::OBB PEACollider;
		PEACollider.u = glm::quat_cast(modelMatrixPEA);
		modelMatrixColliderPEA[3][1] = terrain.getHeightTerrain(modelMatrixColliderPEA[3][0], modelMatrixColliderPEA[3][2]);
		modelMatrixColliderPEA = glm::scale(modelMatrixColliderPEA, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPEA = glm::translate(modelMatrixColliderPEA, modelPEA.getObb().c);
		PEACollider.c = glm::vec3(modelMatrixColliderPEA[3]);
		PEACollider.e = modelPEA.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PEA", PEACollider, modelMatrixPEA);

		glm::mat4 modelMatrixColliderPEB = glm::mat4(modelMatrixPEB);
		AbstractModel::OBB PEBCollider;
		PEBCollider.u = glm::quat_cast(modelMatrixPEB);
		modelMatrixColliderPEB[3][1] = terrain.getHeightTerrain(modelMatrixColliderPEB[3][0], modelMatrixColliderPEB[3][2]);
		modelMatrixColliderPEB = glm::scale(modelMatrixColliderPEB, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPEB = glm::translate(modelMatrixColliderPEB, modelPEB.getObb().c);
		PEBCollider.c = glm::vec3(modelMatrixColliderPEB[3]);
		PEBCollider.e = modelPEB.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PEB", PEBCollider, modelMatrixPEB);

		glm::mat4 modelMatrixColliderPEI = glm::mat4(modelMatrixPEI);
		AbstractModel::OBB PEICollider;
		PEICollider.u = glm::quat_cast(modelMatrixPEI);
		modelMatrixColliderPEI[3][1] = terrain.getHeightTerrain(modelMatrixColliderPEI[3][0], modelMatrixColliderPEI[3][2]);
		modelMatrixColliderPEI = glm::scale(modelMatrixColliderPEI, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPEI = glm::translate(modelMatrixColliderPEI, modelPEI.getObb().c);
		PEICollider.c = glm::vec3(modelMatrixColliderPEI[3]);
		PEICollider.e = modelPEI.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PEI", PEICollider, modelMatrixPEI);

		glm::mat4 modelMatrixColliderPED = glm::mat4(modelMatrixPED);
		AbstractModel::OBB PEDCollider;
		PEDCollider.u = glm::quat_cast(modelMatrixPED);
		modelMatrixColliderPED[3][1] = terrain.getHeightTerrain(modelMatrixColliderPED[3][0], modelMatrixColliderPED[3][2]);
		modelMatrixColliderPED = glm::scale(modelMatrixColliderPED, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPED = glm::translate(modelMatrixColliderPED, modelPED.getObb().c);
		PEDCollider.c = glm::vec3(modelMatrixColliderPED[3]);
		PEDCollider.e = modelPED.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PED", PEDCollider, modelMatrixPED);
		
				glm::mat4 modelMatrixColliderPC1 = glm::mat4(modelMatrixPC1);
		AbstractModel::OBB PC1Collider;
		PC1Collider.u = glm::quat_cast(modelMatrixPC1);
		modelMatrixColliderPC1[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC1[3][0], modelMatrixColliderPC1[3][2]);
		modelMatrixColliderPC1 = glm::scale(modelMatrixColliderPC1, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC1 = glm::translate(modelMatrixColliderPC1, modelPC1.getObb().c);
		PC1Collider.c = glm::vec3(modelMatrixColliderPC1[3]);
		PC1Collider.e = modelPC1.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC1", PC1Collider, modelMatrixPC1);

		glm::mat4 modelMatrixColliderPC2 = glm::mat4(modelMatrixPC2);
		AbstractModel::OBB PC2Collider;
		PC2Collider.u = glm::quat_cast(modelMatrixPC2);
		modelMatrixColliderPC2[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC2[3][0], modelMatrixColliderPC2[3][2]);
		modelMatrixColliderPC2 = glm::scale(modelMatrixColliderPC2, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC2 = glm::translate(modelMatrixColliderPC2, modelPC2.getObb().c);
		PC2Collider.c = glm::vec3(modelMatrixColliderPC2[3]);
		PC2Collider.e = modelPC2.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC2", PC2Collider, modelMatrixPC2);

		glm::mat4 modelMatrixColliderPC3 = glm::mat4(modelMatrixPC3);
		AbstractModel::OBB PC3Collider;
		PC3Collider.u = glm::quat_cast(modelMatrixPC3);
		modelMatrixColliderPC3[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC3[3][0], modelMatrixColliderPC3[3][2]);
		modelMatrixColliderPC3 = glm::scale(modelMatrixColliderPC3, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC3 = glm::translate(modelMatrixColliderPC3, modelPC3.getObb().c);
		PC3Collider.c = glm::vec3(modelMatrixColliderPC3[3]);
		PC3Collider.e = modelPC3.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC3", PC3Collider, modelMatrixPC3);

		glm::mat4 modelMatrixColliderPC4 = glm::mat4(modelMatrixPC4);
		AbstractModel::OBB PC4Collider;
		PC4Collider.u = glm::quat_cast(modelMatrixPC4);
		modelMatrixColliderPC4[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC4[3][0], modelMatrixColliderPC4[3][2]);
		modelMatrixColliderPC4 = glm::scale(modelMatrixColliderPC4, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC4 = glm::translate(modelMatrixColliderPC4, modelPC4.getObb().c);
		PC4Collider.c = glm::vec3(modelMatrixColliderPC4[3]);
		PC4Collider.e = modelPC4.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC4", PC4Collider, modelMatrixPC4);

		glm::mat4 modelMatrixColliderPC5 = glm::mat4(modelMatrixPC5);
		AbstractModel::OBB PC5Collider;
		PC5Collider.u = glm::quat_cast(modelMatrixPC5);
		modelMatrixColliderPC5[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC5[3][0], modelMatrixColliderPC5[3][2]);
		modelMatrixColliderPC5 = glm::scale(modelMatrixColliderPC5, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC5 = glm::translate(modelMatrixColliderPC5, modelPC5.getObb().c);
		PC5Collider.c = glm::vec3(modelMatrixColliderPC5[3]);
		PC5Collider.e = modelPC5.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC5", PC5Collider, modelMatrixPC5);

		glm::mat4 modelMatrixColliderPC6 = glm::mat4(modelMatrixPC6);
		AbstractModel::OBB PC6Collider;
		PC6Collider.u = glm::quat_cast(modelMatrixPC6);
		modelMatrixColliderPC6[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC6[3][0], modelMatrixColliderPC6[3][2]);
		modelMatrixColliderPC6 = glm::scale(modelMatrixColliderPC6, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC6 = glm::translate(modelMatrixColliderPC6, modelPC6.getObb().c);
		PC6Collider.c = glm::vec3(modelMatrixColliderPC6[3]);
		PC6Collider.e = modelPC6.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC6", PC6Collider, modelMatrixPC6);

		glm::mat4 modelMatrixColliderPC7 = glm::mat4(modelMatrixPC7);
		AbstractModel::OBB PC7Collider;
		PC7Collider.u = glm::quat_cast(modelMatrixPC7);
		modelMatrixColliderPC7[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC7[3][0], modelMatrixColliderPC7[3][2]);
		modelMatrixColliderPC7 = glm::scale(modelMatrixColliderPC7, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC7 = glm::translate(modelMatrixColliderPC7, modelPC7.getObb().c);
		PC7Collider.c = glm::vec3(modelMatrixColliderPC7[3]);
		PC7Collider.e = modelPC7.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC7", PC7Collider, modelMatrixPC7);

		glm::mat4 modelMatrixColliderPC8 = glm::mat4(modelMatrixPC8);
		AbstractModel::OBB PC8Collider;
		PC8Collider.u = glm::quat_cast(modelMatrixPC8);
		modelMatrixColliderPC8[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC8[3][0], modelMatrixColliderPC8[3][2]);
		modelMatrixColliderPC8 = glm::scale(modelMatrixColliderPC8, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC8 = glm::translate(modelMatrixColliderPC8, modelPC8.getObb().c);
		PC8Collider.c = glm::vec3(modelMatrixColliderPC8[3]);
		PC8Collider.e = modelPC8.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC8", PC8Collider, modelMatrixPC8);

		glm::mat4 modelMatrixColliderPC9 = glm::mat4(modelMatrixPC9);
		AbstractModel::OBB PC9Collider;
		PC9Collider.u = glm::quat_cast(modelMatrixPC9);
		modelMatrixColliderPC9[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC9[3][0], modelMatrixColliderPC9[3][2]);
		modelMatrixColliderPC9 = glm::scale(modelMatrixColliderPC9, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC9 = glm::translate(modelMatrixColliderPC9, modelPC9.getObb().c);
		PC9Collider.c = glm::vec3(modelMatrixColliderPC9[3]);
		PC9Collider.e = modelPC9.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC9", PC9Collider, modelMatrixPC9);

		glm::mat4 modelMatrixColliderPC10 = glm::mat4(modelMatrixPC10);
		AbstractModel::OBB PC10Collider;
		PC10Collider.u = glm::quat_cast(modelMatrixPC10);
		modelMatrixColliderPC10[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC10[3][0], modelMatrixColliderPC10[3][2]);
		modelMatrixColliderPC10 = glm::scale(modelMatrixColliderPC10, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC10 = glm::translate(modelMatrixColliderPC10, modelPC10.getObb().c);
		PC10Collider.c = glm::vec3(modelMatrixColliderPC10[3]);
		PC10Collider.e = modelPC10.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC10", PC10Collider, modelMatrixPC10);
		
		glm::mat4 modelMatrixColliderPC11 = glm::mat4(modelMatrixPC11);
		AbstractModel::OBB PC11Collider;
		PC11Collider.u = glm::quat_cast(modelMatrixPC11);
		modelMatrixColliderPC11[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC11[3][0], modelMatrixColliderPC11[3][2]);
		modelMatrixColliderPC11 = glm::scale(modelMatrixColliderPC11, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC11 = glm::translate(modelMatrixColliderPC11, modelPC11.getObb().c);
		PC11Collider.c = glm::vec3(modelMatrixColliderPC11[3]);
		PC11Collider.e = modelPC11.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC11", PC11Collider, modelMatrixPC11);

		glm::mat4 modelMatrixColliderPC12 = glm::mat4(modelMatrixPC12);
		AbstractModel::OBB PC12Collider;
		PC12Collider.u = glm::quat_cast(modelMatrixPC12);
		modelMatrixColliderPC12[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC12[3][0], modelMatrixColliderPC12[3][2]);
		modelMatrixColliderPC12 = glm::scale(modelMatrixColliderPC12, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC12 = glm::translate(modelMatrixColliderPC12, modelPC12.getObb().c);
		PC12Collider.c = glm::vec3(modelMatrixColliderPC12[3]);
		PC12Collider.e = modelPC12.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC10", PC12Collider, modelMatrixPC12);

		glm::mat4 modelMatrixColliderPC13 = glm::mat4(modelMatrixPC13);
		AbstractModel::OBB PC13Collider;
		PC13Collider.u = glm::quat_cast(modelMatrixPC13);
		modelMatrixColliderPC13[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC13[3][0], modelMatrixColliderPC13[3][2]);
		modelMatrixColliderPC13 = glm::scale(modelMatrixColliderPC13, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC13 = glm::translate(modelMatrixColliderPC13, modelPC13.getObb().c);
		PC13Collider.c = glm::vec3(modelMatrixColliderPC13[3]);
		PC13Collider.e = modelPC13.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC13", PC13Collider, modelMatrixPC13);

		glm::mat4 modelMatrixColliderPC14 = glm::mat4(modelMatrixPC14);
		AbstractModel::OBB PC14Collider;
		PC14Collider.u = glm::quat_cast(modelMatrixPC14);
		modelMatrixColliderPC14[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC14[3][0], modelMatrixColliderPC14[3][2]);
		modelMatrixColliderPC14 = glm::scale(modelMatrixColliderPC14, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC14 = glm::translate(modelMatrixColliderPC14, modelPC14.getObb().c);
		PC14Collider.c = glm::vec3(modelMatrixColliderPC14[3]);
		PC14Collider.e = modelPC14.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC14", PC14Collider, modelMatrixPC14);

		glm::mat4 modelMatrixColliderPC15 = glm::mat4(modelMatrixPC15);
		AbstractModel::OBB PC15Collider;
		PC15Collider.u = glm::quat_cast(modelMatrixPC15);
		modelMatrixColliderPC15[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC15[3][0], modelMatrixColliderPC15[3][2]);
		modelMatrixColliderPC15 = glm::scale(modelMatrixColliderPC15, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC15 = glm::translate(modelMatrixColliderPC15, modelPC15.getObb().c);
		PC15Collider.c = glm::vec3(modelMatrixColliderPC15[3]);
		PC15Collider.e = modelPC15.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC15", PC15Collider, modelMatrixPC15);

		glm::mat4 modelMatrixColliderPC16 = glm::mat4(modelMatrixPC16);
		AbstractModel::OBB PC16Collider;
		PC16Collider.u = glm::quat_cast(modelMatrixPC16);
		modelMatrixColliderPC16[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC16[3][0], modelMatrixColliderPC16[3][2]);
		modelMatrixColliderPC16 = glm::scale(modelMatrixColliderPC16, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC16 = glm::translate(modelMatrixColliderPC16, modelPC16.getObb().c);
		PC16Collider.c = glm::vec3(modelMatrixColliderPC16[3]);
		PC16Collider.e = modelPC16.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC16", PC16Collider, modelMatrixPC16);

		glm::mat4 modelMatrixColliderPC17 = glm::mat4(modelMatrixPC17);
		AbstractModel::OBB PC17Collider;
		PC17Collider.u = glm::quat_cast(modelMatrixPC17);
		modelMatrixColliderPC17[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC17[3][0], modelMatrixColliderPC17[3][2]);
		modelMatrixColliderPC17 = glm::scale(modelMatrixColliderPC17, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC17 = glm::translate(modelMatrixColliderPC17, modelPC17.getObb().c);
		PC17Collider.c = glm::vec3(modelMatrixColliderPC17[3]);
		PC17Collider.e = modelPC17.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC17", PC17Collider, modelMatrixPC17);

		glm::mat4 modelMatrixColliderPC18 = glm::mat4(modelMatrixPC18);
		AbstractModel::OBB PC18Collider;
		PC18Collider.u = glm::quat_cast(modelMatrixPC18);
		modelMatrixColliderPC18[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC18[3][0], modelMatrixColliderPC18[3][2]);
		modelMatrixColliderPC18 = glm::scale(modelMatrixColliderPC18, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC18 = glm::translate(modelMatrixColliderPC18, modelPC18.getObb().c);
		PC18Collider.c = glm::vec3(modelMatrixColliderPC18[3]);
		PC18Collider.e = modelPC18.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC18", PC18Collider, modelMatrixPC18);

		glm::mat4 modelMatrixColliderPC19 = glm::mat4(modelMatrixPC19);
		AbstractModel::OBB PC19Collider;
		PC19Collider.u = glm::quat_cast(modelMatrixPC19);
		modelMatrixColliderPC19[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC19[3][0], modelMatrixColliderPC19[3][2]);
		modelMatrixColliderPC19 = glm::scale(modelMatrixColliderPC19, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC19 = glm::translate(modelMatrixColliderPC19, modelPC19.getObb().c);
		PC19Collider.c = glm::vec3(modelMatrixColliderPC19[3]);
		PC19Collider.e = modelPC19.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC19", PC19Collider, modelMatrixPC19);

		glm::mat4 modelMatrixColliderPC20 = glm::mat4(modelMatrixPC20);
		AbstractModel::OBB PC20Collider;
		PC20Collider.u = glm::quat_cast(modelMatrixPC20);
		modelMatrixColliderPC20[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC20[3][0], modelMatrixColliderPC20[3][2]);
		modelMatrixColliderPC20 = glm::scale(modelMatrixColliderPC20, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC20 = glm::translate(modelMatrixColliderPC20, modelPC20.getObb().c);
		PC20Collider.c = glm::vec3(modelMatrixColliderPC20[3]);
		PC20Collider.e = modelPC20.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC20", PC20Collider, modelMatrixPC20);
		
		glm::mat4 modelMatrixColliderPC21 = glm::mat4(modelMatrixPC21);
		AbstractModel::OBB PC21Collider;
		PC21Collider.u = glm::quat_cast(modelMatrixPC21);
		modelMatrixColliderPC21[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC21[3][0], modelMatrixColliderPC21[3][2]);
		modelMatrixColliderPC21 = glm::scale(modelMatrixColliderPC21, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC21 = glm::translate(modelMatrixColliderPC21, modelPC21.getObb().c);
		PC21Collider.c = glm::vec3(modelMatrixColliderPC21[3]);
		PC21Collider.e = modelPC21.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC21", PC21Collider, modelMatrixPC21);

		glm::mat4 modelMatrixColliderPC22 = glm::mat4(modelMatrixPC22);
		AbstractModel::OBB PC22Collider;
		PC22Collider.u = glm::quat_cast(modelMatrixPC22);
		modelMatrixColliderPC22[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC22[3][0], modelMatrixColliderPC22[3][2]);
		modelMatrixColliderPC22 = glm::scale(modelMatrixColliderPC22, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC22 = glm::translate(modelMatrixColliderPC22, modelPC22.getObb().c);
		PC22Collider.c = glm::vec3(modelMatrixColliderPC22[3]);
		PC22Collider.e = modelPC22.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC22", PC22Collider, modelMatrixPC22);

		glm::mat4 modelMatrixColliderPC23 = glm::mat4(modelMatrixPC23);
		AbstractModel::OBB PC23Collider;
		PC23Collider.u = glm::quat_cast(modelMatrixPC23);
		modelMatrixColliderPC23[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC23[3][0], modelMatrixColliderPC23[3][2]);
		modelMatrixColliderPC23 = glm::scale(modelMatrixColliderPC23, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC23 = glm::translate(modelMatrixColliderPC23, modelPC23.getObb().c);
		PC23Collider.c = glm::vec3(modelMatrixColliderPC23[3]);
		PC23Collider.e = modelPC23.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC23", PC23Collider, modelMatrixPC23);

		glm::mat4 modelMatrixColliderPC24 = glm::mat4(modelMatrixPC24);
		AbstractModel::OBB PC24Collider;
		PC24Collider.u = glm::quat_cast(modelMatrixPC24);
		modelMatrixColliderPC24[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC24[3][0], modelMatrixColliderPC24[3][2]);
		modelMatrixColliderPC24 = glm::scale(modelMatrixColliderPC24, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC24 = glm::translate(modelMatrixColliderPC24, modelPC24.getObb().c);
		PC24Collider.c = glm::vec3(modelMatrixColliderPC24[3]);
		PC24Collider.e = modelPC24.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC24", PC24Collider, modelMatrixPC24);

		glm::mat4 modelMatrixColliderPC25 = glm::mat4(modelMatrixPC25);
		AbstractModel::OBB PC25Collider;
		PC25Collider.u = glm::quat_cast(modelMatrixPC25);
		modelMatrixColliderPC25[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC25[3][0], modelMatrixColliderPC25[3][2]);
		modelMatrixColliderPC25 = glm::scale(modelMatrixColliderPC25, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC25 = glm::translate(modelMatrixColliderPC25, modelPC25.getObb().c);
		PC25Collider.c = glm::vec3(modelMatrixColliderPC25[3]);
		PC25Collider.e = modelPC25.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC25", PC25Collider, modelMatrixPC25);

		glm::mat4 modelMatrixColliderPC26 = glm::mat4(modelMatrixPC26);
		AbstractModel::OBB PC26Collider;
		PC26Collider.u = glm::quat_cast(modelMatrixPC26);
		modelMatrixColliderPC26[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC26[3][0], modelMatrixColliderPC26[3][2]);
		modelMatrixColliderPC26 = glm::scale(modelMatrixColliderPC26, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC26 = glm::translate(modelMatrixColliderPC26, modelPC26.getObb().c);
		PC26Collider.c = glm::vec3(modelMatrixColliderPC26[3]);
		PC26Collider.e = modelPC26.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC26", PC26Collider, modelMatrixPC26);

		glm::mat4 modelMatrixColliderPC27 = glm::mat4(modelMatrixPC27);
		AbstractModel::OBB PC27Collider;
		PC27Collider.u = glm::quat_cast(modelMatrixPC27);
		modelMatrixColliderPC27[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC27[3][0], modelMatrixColliderPC27[3][2]);
		modelMatrixColliderPC27 = glm::scale(modelMatrixColliderPC27, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC27 = glm::translate(modelMatrixColliderPC27, modelPC27.getObb().c);
		PC27Collider.c = glm::vec3(modelMatrixColliderPC27[3]);
		PC27Collider.e = modelPC27.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC27", PC27Collider, modelMatrixPC27);

		glm::mat4 modelMatrixColliderPC28 = glm::mat4(modelMatrixPC28);
		AbstractModel::OBB PC28Collider;
		PC28Collider.u = glm::quat_cast(modelMatrixPC28);
		modelMatrixColliderPC28[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC28[3][0], modelMatrixColliderPC28[3][2]);
		modelMatrixColliderPC28 = glm::scale(modelMatrixColliderPC28, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC28 = glm::translate(modelMatrixColliderPC28, modelPC28.getObb().c);
		PC28Collider.c = glm::vec3(modelMatrixColliderPC28[3]);
		PC28Collider.e = modelPC28.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC28", PC28Collider, modelMatrixPC28);

		glm::mat4 modelMatrixColliderPC29 = glm::mat4(modelMatrixPC29);
		AbstractModel::OBB PC29Collider;
		PC29Collider.u = glm::quat_cast(modelMatrixPC29);
		modelMatrixColliderPC29[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC29[3][0], modelMatrixColliderPC29[3][2]);
		modelMatrixColliderPC29 = glm::scale(modelMatrixColliderPC29, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC29 = glm::translate(modelMatrixColliderPC29, modelPC29.getObb().c);
		PC29Collider.c = glm::vec3(modelMatrixColliderPC29[3]);
		PC29Collider.e = modelPC29.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC29", PC29Collider, modelMatrixPC29);

		glm::mat4 modelMatrixColliderPC30 = glm::mat4(modelMatrixPC30);
		AbstractModel::OBB PC30Collider;
		PC30Collider.u = glm::quat_cast(modelMatrixPC30);
		modelMatrixColliderPC30[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC30[3][0], modelMatrixColliderPC30[3][2]);
		modelMatrixColliderPC30 = glm::scale(modelMatrixColliderPC30, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC30 = glm::translate(modelMatrixColliderPC30, modelPC30.getObb().c);
		PC30Collider.c = glm::vec3(modelMatrixColliderPC30[3]);
		PC30Collider.e = modelPC30.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC30", PC30Collider, modelMatrixPC30);

		glm::mat4 modelMatrixColliderPC31 = glm::mat4(modelMatrixPC31);
		AbstractModel::OBB PC31Collider;
		PC31Collider.u = glm::quat_cast(modelMatrixPC31);
		modelMatrixColliderPC31[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC31[3][0], modelMatrixColliderPC31[3][2]);
		modelMatrixColliderPC31 = glm::scale(modelMatrixColliderPC31, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC31 = glm::translate(modelMatrixColliderPC31, modelPC31.getObb().c);
		PC31Collider.c = glm::vec3(modelMatrixColliderPC31[3]);
		PC31Collider.e = modelPC31.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC31", PC31Collider, modelMatrixPC31);

		glm::mat4 modelMatrixColliderPC32 = glm::mat4(modelMatrixPC32);
		AbstractModel::OBB PC32Collider;
		PC32Collider.u = glm::quat_cast(modelMatrixPC32);
		modelMatrixColliderPC32[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC32[3][0], modelMatrixColliderPC32[3][2]);
		modelMatrixColliderPC32 = glm::scale(modelMatrixColliderPC32, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC32 = glm::translate(modelMatrixColliderPC32, modelPC32.getObb().c);
		PC32Collider.c = glm::vec3(modelMatrixColliderPC32[3]);
		PC32Collider.e = modelPC32.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC32", PC32Collider, modelMatrixPC32);

		glm::mat4 modelMatrixColliderPC33 = glm::mat4(modelMatrixPC33);
		AbstractModel::OBB PC33Collider;
		PC33Collider.u = glm::quat_cast(modelMatrixPC33);
		modelMatrixColliderPC33[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC33[3][0], modelMatrixColliderPC33[3][2]);
		modelMatrixColliderPC33 = glm::scale(modelMatrixColliderPC33, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC33 = glm::translate(modelMatrixColliderPC33, modelPC33.getObb().c);
		PC33Collider.c = glm::vec3(modelMatrixColliderPC33[3]);
		PC33Collider.e = modelPC33.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC33", PC33Collider, modelMatrixPC33);

		glm::mat4 modelMatrixColliderPC34 = glm::mat4(modelMatrixPC34);
		AbstractModel::OBB PC34Collider;
		PC34Collider.u = glm::quat_cast(modelMatrixPC34);
		modelMatrixColliderPC34[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC34[3][0], modelMatrixColliderPC34[3][2]);
		modelMatrixColliderPC34 = glm::scale(modelMatrixColliderPC34, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC34 = glm::translate(modelMatrixColliderPC34, modelPC34.getObb().c);
		PC34Collider.c = glm::vec3(modelMatrixColliderPC34[3]);
		PC34Collider.e = modelPC34.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC34", PC34Collider, modelMatrixPC34);

		glm::mat4 modelMatrixColliderPC35 = glm::mat4(modelMatrixPC35);
		AbstractModel::OBB PC35Collider;
		PC35Collider.u = glm::quat_cast(modelMatrixPC35);
		modelMatrixColliderPC35[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC35[3][0], modelMatrixColliderPC35[3][2]);
		modelMatrixColliderPC35 = glm::scale(modelMatrixColliderPC35, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC35 = glm::translate(modelMatrixColliderPC35, modelPC35.getObb().c);
		PC35Collider.c = glm::vec3(modelMatrixColliderPC35[3]);
		PC35Collider.e = modelPC35.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC35", PC35Collider, modelMatrixPC35);

		glm::mat4 modelMatrixColliderPC36 = glm::mat4(modelMatrixPC36);
		AbstractModel::OBB PC36Collider;
		PC36Collider.u = glm::quat_cast(modelMatrixPC36);
		modelMatrixColliderPC36[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC36[3][0], modelMatrixColliderPC36[3][2]);
		modelMatrixColliderPC36 = glm::scale(modelMatrixColliderPC36, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC36 = glm::translate(modelMatrixColliderPC36, modelPC36.getObb().c);
		PC36Collider.c = glm::vec3(modelMatrixColliderPC36[3]);
		PC36Collider.e = modelPC36.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC36", PC36Collider, modelMatrixPC36);

		glm::mat4 modelMatrixColliderPC37 = glm::mat4(modelMatrixPC37);
		AbstractModel::OBB PC37Collider;
		PC37Collider.u = glm::quat_cast(modelMatrixPC37);
		modelMatrixColliderPC37[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC37[3][0], modelMatrixColliderPC37[3][2]);
		modelMatrixColliderPC37 = glm::scale(modelMatrixColliderPC37, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC37 = glm::translate(modelMatrixColliderPC37, modelPC37.getObb().c);
		PC37Collider.c = glm::vec3(modelMatrixColliderPC37[3]);
		PC37Collider.e = modelPC37.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC37", PC37Collider, modelMatrixPC37);

		glm::mat4 modelMatrixColliderPC38 = glm::mat4(modelMatrixPC38);
		AbstractModel::OBB PC38Collider;
		PC38Collider.u = glm::quat_cast(modelMatrixPC38);
		modelMatrixColliderPC38[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC38[3][0], modelMatrixColliderPC38[3][2]);
		modelMatrixColliderPC38 = glm::scale(modelMatrixColliderPC38, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC38 = glm::translate(modelMatrixColliderPC38, modelPC38.getObb().c);
		PC38Collider.c = glm::vec3(modelMatrixColliderPC38[3]);
		PC38Collider.e = modelPC38.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC38", PC38Collider, modelMatrixPC38);

		glm::mat4 modelMatrixColliderPC39 = glm::mat4(modelMatrixPC39);
		AbstractModel::OBB PC39Collider;
		PC39Collider.u = glm::quat_cast(modelMatrixPC39);
		modelMatrixColliderPC39[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC39[3][0], modelMatrixColliderPC39[3][2]);
		modelMatrixColliderPC39 = glm::scale(modelMatrixColliderPC39, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC39 = glm::translate(modelMatrixColliderPC39, modelPC39.getObb().c);
		PC39Collider.c = glm::vec3(modelMatrixColliderPC39[3]);
		PC39Collider.e = modelPC39.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC39", PC39Collider, modelMatrixPC39);

		glm::mat4 modelMatrixColliderPC40 = glm::mat4(modelMatrixPC40);
		AbstractModel::OBB PC40Collider;
		PC40Collider.u = glm::quat_cast(modelMatrixPC40);
		modelMatrixColliderPC40[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC40[3][0], modelMatrixColliderPC40[3][2]);
		modelMatrixColliderPC40 = glm::scale(modelMatrixColliderPC40, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC40 = glm::translate(modelMatrixColliderPC40, modelPC40.getObb().c);
		PC40Collider.c = glm::vec3(modelMatrixColliderPC40[3]);
		PC40Collider.e = modelPC40.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC40", PC40Collider, modelMatrixPC40);

		glm::mat4 modelMatrixColliderPC41 = glm::mat4(modelMatrixPC41);
		AbstractModel::OBB PC41Collider;
		PC41Collider.u = glm::quat_cast(modelMatrixPC41);
		modelMatrixColliderPC41[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC41[3][0], modelMatrixColliderPC41[3][2]);
		modelMatrixColliderPC41 = glm::scale(modelMatrixColliderPC41, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC41 = glm::translate(modelMatrixColliderPC41, modelPC41.getObb().c);
		PC41Collider.c = glm::vec3(modelMatrixColliderPC41[3]);
		PC41Collider.e = modelPC41.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC41", PC41Collider, modelMatrixPC41);

		glm::mat4 modelMatrixColliderPC42 = glm::mat4(modelMatrixPC42);
		AbstractModel::OBB PC42Collider;
		PC42Collider.u = glm::quat_cast(modelMatrixPC42);
		modelMatrixColliderPC42[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC42[3][0], modelMatrixColliderPC42[3][2]);
		modelMatrixColliderPC42 = glm::scale(modelMatrixColliderPC42, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC42 = glm::translate(modelMatrixColliderPC42, modelPC42.getObb().c);
		PC42Collider.c = glm::vec3(modelMatrixColliderPC42[3]);
		PC42Collider.e = modelPC42.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC42", PC42Collider, modelMatrixPC42);

		glm::mat4 modelMatrixColliderPC43 = glm::mat4(modelMatrixPC43);
		AbstractModel::OBB PC43Collider;
		PC43Collider.u = glm::quat_cast(modelMatrixPC43);
		modelMatrixColliderPC43[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC43[3][0], modelMatrixColliderPC43[3][2]);
		modelMatrixColliderPC43 = glm::scale(modelMatrixColliderPC43, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC43 = glm::translate(modelMatrixColliderPC43, modelPC43.getObb().c);
		PC43Collider.c = glm::vec3(modelMatrixColliderPC43[3]);
		PC43Collider.e = modelPC43.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC43", PC43Collider, modelMatrixPC43);

		glm::mat4 modelMatrixColliderPC44 = glm::mat4(modelMatrixPC44);
		AbstractModel::OBB PC44Collider;
		PC44Collider.u = glm::quat_cast(modelMatrixPC44);
		modelMatrixColliderPC44[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC44[3][0], modelMatrixColliderPC44[3][2]);
		modelMatrixColliderPC44 = glm::scale(modelMatrixColliderPC44, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC44 = glm::translate(modelMatrixColliderPC44, modelPC44.getObb().c);
		PC44Collider.c = glm::vec3(modelMatrixColliderPC44[3]);
		PC44Collider.e = modelPC44.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC44", PC44Collider, modelMatrixPC44);

		glm::mat4 modelMatrixColliderPC45 = glm::mat4(modelMatrixPC45);
		AbstractModel::OBB PC45Collider;
		PC45Collider.u = glm::quat_cast(modelMatrixPC45);
		modelMatrixColliderPC45[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC45[3][0], modelMatrixColliderPC45[3][2]);
		modelMatrixColliderPC45 = glm::scale(modelMatrixColliderPC45, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC45 = glm::translate(modelMatrixColliderPC45, modelPC45.getObb().c);
		PC45Collider.c = glm::vec3(modelMatrixColliderPC45[3]);
		PC45Collider.e = modelPC45.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC45", PC45Collider, modelMatrixPC45);

		glm::mat4 modelMatrixColliderPC46 = glm::mat4(modelMatrixPC46);
		AbstractModel::OBB PC46Collider;
		PC46Collider.u = glm::quat_cast(modelMatrixPC46);
		modelMatrixColliderPC46[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC46[3][0], modelMatrixColliderPC46[3][2]);
		modelMatrixColliderPC46 = glm::scale(modelMatrixColliderPC46, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC46 = glm::translate(modelMatrixColliderPC46, modelPC46.getObb().c);
		PC46Collider.c = glm::vec3(modelMatrixColliderPC46[3]);
		PC46Collider.e = modelPC46.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC46", PC46Collider, modelMatrixPC46);

		glm::mat4 modelMatrixColliderPC47 = glm::mat4(modelMatrixPC47);
		AbstractModel::OBB PC47Collider;
		PC47Collider.u = glm::quat_cast(modelMatrixPC47);
		modelMatrixColliderPC47[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC47[3][0], modelMatrixColliderPC47[3][2]);
		modelMatrixColliderPC47 = glm::scale(modelMatrixColliderPC47, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC47 = glm::translate(modelMatrixColliderPC47, modelPC47.getObb().c);
		PC47Collider.c = glm::vec3(modelMatrixColliderPC47[3]);
		PC47Collider.e = modelPC47.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC47", PC47Collider, modelMatrixPC47);

		glm::mat4 modelMatrixColliderPC48 = glm::mat4(modelMatrixPC48);
		AbstractModel::OBB PC48Collider;
		PC48Collider.u = glm::quat_cast(modelMatrixPC48);
		modelMatrixColliderPC48[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC48[3][0], modelMatrixColliderPC48[3][2]);
		modelMatrixColliderPC48 = glm::scale(modelMatrixColliderPC48, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC48 = glm::translate(modelMatrixColliderPC48, modelPC48.getObb().c);
		PC48Collider.c = glm::vec3(modelMatrixColliderPC48[3]);
		PC48Collider.e = modelPC48.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC48", PC48Collider, modelMatrixPC48);

		glm::mat4 modelMatrixColliderPC49 = glm::mat4(modelMatrixPC49);
		AbstractModel::OBB PC49Collider;
		PC49Collider.u = glm::quat_cast(modelMatrixPC49);
		modelMatrixColliderPC49[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC49[3][0], modelMatrixColliderPC49[3][2]);
		modelMatrixColliderPC49 = glm::scale(modelMatrixColliderPC49, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC49 = glm::translate(modelMatrixColliderPC49, modelPC49.getObb().c);
		PC49Collider.c = glm::vec3(modelMatrixColliderPC49[3]);
		PC49Collider.e = modelPC49.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC49", PC49Collider, modelMatrixPC49);

		glm::mat4 modelMatrixColliderPC50 = glm::mat4(modelMatrixPC50);
		AbstractModel::OBB PC50Collider;
		PC50Collider.u = glm::quat_cast(modelMatrixPC50);
		modelMatrixColliderPC50[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC50[3][0], modelMatrixColliderPC50[3][2]);
		modelMatrixColliderPC50 = glm::scale(modelMatrixColliderPC50, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC50 = glm::translate(modelMatrixColliderPC50, modelPC50.getObb().c);
		PC50Collider.c = glm::vec3(modelMatrixColliderPC50[3]);
		PC50Collider.e = modelPC50.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC50", PC50Collider, modelMatrixPC50);

		glm::mat4 modelMatrixColliderPC51 = glm::mat4(modelMatrixPC51);
		AbstractModel::OBB PC51Collider;
		PC51Collider.u = glm::quat_cast(modelMatrixPC51);
		modelMatrixColliderPC51[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC51[3][0], modelMatrixColliderPC51[3][2]);
		modelMatrixColliderPC51 = glm::scale(modelMatrixColliderPC51, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC51 = glm::translate(modelMatrixColliderPC51, modelPC51.getObb().c);
		PC51Collider.c = glm::vec3(modelMatrixColliderPC51[3]);
		PC51Collider.e = modelPC51.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC51", PC51Collider, modelMatrixPC51);

		glm::mat4 modelMatrixColliderPC52 = glm::mat4(modelMatrixPC52);
		AbstractModel::OBB PC52Collider;
		PC52Collider.u = glm::quat_cast(modelMatrixPC52);
		modelMatrixColliderPC52[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC52[3][0], modelMatrixColliderPC52[3][2]);
		modelMatrixColliderPC52 = glm::scale(modelMatrixColliderPC52, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC52 = glm::translate(modelMatrixColliderPC52, modelPC52.getObb().c);
		PC52Collider.c = glm::vec3(modelMatrixColliderPC52[3]);
		PC52Collider.e = modelPC52.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC52", PC52Collider, modelMatrixPC52);

		glm::mat4 modelMatrixColliderPC53 = glm::mat4(modelMatrixPC53);
		AbstractModel::OBB PC53Collider;
		PC53Collider.u = glm::quat_cast(modelMatrixPC53);
		modelMatrixColliderPC53[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC53[3][0], modelMatrixColliderPC53[3][2]);
		modelMatrixColliderPC53 = glm::scale(modelMatrixColliderPC53, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC53 = glm::translate(modelMatrixColliderPC53, modelPC53.getObb().c);
		PC53Collider.c = glm::vec3(modelMatrixColliderPC53[3]);
		PC53Collider.e = modelPC53.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC53", PC53Collider, modelMatrixPC53);

		glm::mat4 modelMatrixColliderPC54 = glm::mat4(modelMatrixPC54);
		AbstractModel::OBB PC54Collider;
		PC54Collider.u = glm::quat_cast(modelMatrixPC54);
		modelMatrixColliderPC54[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC54[3][0], modelMatrixColliderPC54[3][2]);
		modelMatrixColliderPC54 = glm::scale(modelMatrixColliderPC54, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC54 = glm::translate(modelMatrixColliderPC54, modelPC54.getObb().c);
		PC54Collider.c = glm::vec3(modelMatrixColliderPC53[3]);
		PC54Collider.e = modelPC54.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC54", PC54Collider, modelMatrixPC54);

		glm::mat4 modelMatrixColliderPC55 = glm::mat4(modelMatrixPC55);
		AbstractModel::OBB PC55Collider;
		PC55Collider.u = glm::quat_cast(modelMatrixPC55);
		modelMatrixColliderPC55[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC55[3][0], modelMatrixColliderPC55[3][2]);
		modelMatrixColliderPC55 = glm::scale(modelMatrixColliderPC55, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC55 = glm::translate(modelMatrixColliderPC55, modelPC55.getObb().c);
		PC55Collider.c = glm::vec3(modelMatrixColliderPC55[3]);
		PC55Collider.e = modelPC55.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC55", PC55Collider, modelMatrixPC55);

		glm::mat4 modelMatrixColliderPC56 = glm::mat4(modelMatrixPC56);
		AbstractModel::OBB PC56Collider;
		PC56Collider.u = glm::quat_cast(modelMatrixPC56);
		modelMatrixColliderPC56[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC56[3][0], modelMatrixColliderPC56[3][2]);
		modelMatrixColliderPC56 = glm::scale(modelMatrixColliderPC56, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC56 = glm::translate(modelMatrixColliderPC56, modelPC56.getObb().c);
		PC56Collider.c = glm::vec3(modelMatrixColliderPC56[3]);
		PC56Collider.e = modelPC56.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC56", PC56Collider, modelMatrixPC56);

		glm::mat4 modelMatrixColliderPC57 = glm::mat4(modelMatrixPC57);
		AbstractModel::OBB PC57Collider;
		PC57Collider.u = glm::quat_cast(modelMatrixPC57);
		modelMatrixColliderPC57[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC57[3][0], modelMatrixColliderPC57[3][2]);
		modelMatrixColliderPC57 = glm::scale(modelMatrixColliderPC57, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC57 = glm::translate(modelMatrixColliderPC57, modelPC57.getObb().c);
		PC57Collider.c = glm::vec3(modelMatrixColliderPC57[3]);
		PC57Collider.e = modelPC57.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC57", PC57Collider, modelMatrixPC57);

		glm::mat4 modelMatrixColliderPC58 = glm::mat4(modelMatrixPC58);
		AbstractModel::OBB PC58Collider;
		PC58Collider.u = glm::quat_cast(modelMatrixPC58);
		modelMatrixColliderPC58[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC58[3][0], modelMatrixColliderPC58[3][2]);
		modelMatrixColliderPC58 = glm::scale(modelMatrixColliderPC58, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC58 = glm::translate(modelMatrixColliderPC58, modelPC58.getObb().c);
		PC58Collider.c = glm::vec3(modelMatrixColliderPC58[3]);
		PC58Collider.e = modelPC58.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC58", PC58Collider, modelMatrixPC58);

		glm::mat4 modelMatrixColliderPC59 = glm::mat4(modelMatrixPC59);
		AbstractModel::OBB PC59Collider;
		PC59Collider.u = glm::quat_cast(modelMatrixPC59);
		modelMatrixColliderPC59[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC59[3][0], modelMatrixColliderPC59[3][2]);
		modelMatrixColliderPC59 = glm::scale(modelMatrixColliderPC59, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC59 = glm::translate(modelMatrixColliderPC59, modelPC59.getObb().c);
		PC59Collider.c = glm::vec3(modelMatrixColliderPC59[3]);
		PC59Collider.e = modelPC59.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC59", PC59Collider, modelMatrixPC59);
		
		glm::mat4 modelMatrixColliderPC60 = glm::mat4(modelMatrixPC60);
		AbstractModel::OBB PC60Collider;
		PC60Collider.u = glm::quat_cast(modelMatrixPC60);
		modelMatrixColliderPC60[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC60[3][0], modelMatrixColliderPC60[3][2]);
		modelMatrixColliderPC60 = glm::scale(modelMatrixColliderPC60, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC60 = glm::translate(modelMatrixColliderPC60, modelPC60.getObb().c);
		PC60Collider.c = glm::vec3(modelMatrixColliderPC60[3]);
		PC60Collider.e = modelPC60.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC60", PC60Collider, modelMatrixPC60);

		glm::mat4 modelMatrixColliderPC61 = glm::mat4(modelMatrixPC61);
		AbstractModel::OBB PC61Collider;
		PC61Collider.u = glm::quat_cast(modelMatrixPC61);
		modelMatrixColliderPC61[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC61[3][0], modelMatrixColliderPC61[3][2]);
		modelMatrixColliderPC61 = glm::scale(modelMatrixColliderPC61, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC61 = glm::translate(modelMatrixColliderPC61, modelPC61.getObb().c);
		PC61Collider.c = glm::vec3(modelMatrixColliderPC61[3]);
		PC61Collider.e = modelPC61.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC61", PC61Collider, modelMatrixPC61);

		glm::mat4 modelMatrixColliderPC62 = glm::mat4(modelMatrixPC62);
		AbstractModel::OBB PC62Collider;
		PC62Collider.u = glm::quat_cast(modelMatrixPC62);
		modelMatrixColliderPC62[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC62[3][0], modelMatrixColliderPC62[3][2]);
		modelMatrixColliderPC62 = glm::scale(modelMatrixColliderPC62, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC62 = glm::translate(modelMatrixColliderPC62, modelPC62.getObb().c);
		PC62Collider.c = glm::vec3(modelMatrixColliderPC62[3]);
		PC62Collider.e = modelPC62.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC62", PC62Collider, modelMatrixPC62);

		glm::mat4 modelMatrixColliderPC63 = glm::mat4(modelMatrixPC63);
		AbstractModel::OBB PC63Collider;
		PC63Collider.u = glm::quat_cast(modelMatrixPC63);
		modelMatrixColliderPC63[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC63[3][0], modelMatrixColliderPC63[3][2]);
		modelMatrixColliderPC63 = glm::scale(modelMatrixColliderPC63, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC63 = glm::translate(modelMatrixColliderPC63, modelPC63.getObb().c);
		PC63Collider.c = glm::vec3(modelMatrixColliderPC63[3]);
		PC63Collider.e = modelPC63.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC63", PC63Collider, modelMatrixPC63);

		glm::mat4 modelMatrixColliderPC64 = glm::mat4(modelMatrixPC64);
		AbstractModel::OBB PC64Collider;
		PC64Collider.u = glm::quat_cast(modelMatrixPC64);
		modelMatrixColliderPC64[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC64[3][0], modelMatrixColliderPC64[3][2]);
		modelMatrixColliderPC64 = glm::scale(modelMatrixColliderPC64, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC64 = glm::translate(modelMatrixColliderPC64, modelPC64.getObb().c);
		PC64Collider.c = glm::vec3(modelMatrixColliderPC64[3]);
		PC64Collider.e = modelPC64.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC64", PC64Collider, modelMatrixPC64);

		glm::mat4 modelMatrixColliderPC65 = glm::mat4(modelMatrixPC65);
		AbstractModel::OBB PC65Collider;
		PC65Collider.u = glm::quat_cast(modelMatrixPC65);
		modelMatrixColliderPC65[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC65[3][0], modelMatrixColliderPC65[3][2]);
		modelMatrixColliderPC65 = glm::scale(modelMatrixColliderPC65, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC65 = glm::translate(modelMatrixColliderPC65, modelPC65.getObb().c);
		PC65Collider.c = glm::vec3(modelMatrixColliderPC65[3]);
		PC65Collider.e = modelPC65.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC65", PC65Collider, modelMatrixPC65);

		glm::mat4 modelMatrixColliderPC66 = glm::mat4(modelMatrixPC66);
		AbstractModel::OBB PC66Collider;
		PC66Collider.u = glm::quat_cast(modelMatrixPC66);
		modelMatrixColliderPC66[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC66[3][0], modelMatrixColliderPC66[3][2]);
		modelMatrixColliderPC66 = glm::scale(modelMatrixColliderPC66, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC66 = glm::translate(modelMatrixColliderPC66, modelPC66.getObb().c);
		PC66Collider.c = glm::vec3(modelMatrixColliderPC66[3]);
		PC66Collider.e = modelPC66.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC66", PC66Collider, modelMatrixPC66);

		glm::mat4 modelMatrixColliderPC67 = glm::mat4(modelMatrixPC67);
		AbstractModel::OBB PC67Collider;
		PC67Collider.u = glm::quat_cast(modelMatrixPC67);
		modelMatrixColliderPC67[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC67[3][0], modelMatrixColliderPC67[3][2]);
		modelMatrixColliderPC67 = glm::scale(modelMatrixColliderPC67, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC67 = glm::translate(modelMatrixColliderPC67, modelPC67.getObb().c);
		PC67Collider.c = glm::vec3(modelMatrixColliderPC67[3]);
		PC67Collider.e = modelPC67.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC67", PC67Collider, modelMatrixPC67);

		glm::mat4 modelMatrixColliderPC68 = glm::mat4(modelMatrixPC68);
		AbstractModel::OBB PC68Collider;
		PC68Collider.u = glm::quat_cast(modelMatrixPC68);
		modelMatrixColliderPC68[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC68[3][0], modelMatrixColliderPC68[3][2]);
		modelMatrixColliderPC68 = glm::scale(modelMatrixColliderPC68, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC68 = glm::translate(modelMatrixColliderPC68, modelPC68.getObb().c);
		PC68Collider.c = glm::vec3(modelMatrixColliderPC68[3]);
		PC68Collider.e = modelPC68.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC68", PC68Collider, modelMatrixPC68);

		glm::mat4 modelMatrixColliderPC69 = glm::mat4(modelMatrixPC69);
		AbstractModel::OBB PC69Collider;
		PC69Collider.u = glm::quat_cast(modelMatrixPC69);
		modelMatrixColliderPC69[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC69[3][0], modelMatrixColliderPC69[3][2]);
		modelMatrixColliderPC69 = glm::scale(modelMatrixColliderPC69, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC69 = glm::translate(modelMatrixColliderPC69, modelPC69.getObb().c);
		PC69Collider.c = glm::vec3(modelMatrixColliderPC69[3]);
		PC69Collider.e = modelPC69.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC69", PC69Collider, modelMatrixPC69);
		
		glm::mat4 modelMatrixColliderPC70 = glm::mat4(modelMatrixPC70);
		AbstractModel::OBB PC70Collider;
		PC70Collider.u = glm::quat_cast(modelMatrixPC70);
		modelMatrixColliderPC70[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC70[3][0], modelMatrixColliderPC70[3][2]);
		modelMatrixColliderPC70 = glm::scale(modelMatrixColliderPC70, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC70 = glm::translate(modelMatrixColliderPC70, modelPC70.getObb().c);
		PC70Collider.c = glm::vec3(modelMatrixColliderPC70[3]);
		PC70Collider.e = modelPC70.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC70", PC70Collider, modelMatrixPC70);

		glm::mat4 modelMatrixColliderPC71 = glm::mat4(modelMatrixPC71);
		AbstractModel::OBB PC71Collider;
		PC71Collider.u = glm::quat_cast(modelMatrixPC70);
		modelMatrixColliderPC71[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC71[3][0], modelMatrixColliderPC71[3][2]);
		modelMatrixColliderPC71 = glm::scale(modelMatrixColliderPC71, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC71 = glm::translate(modelMatrixColliderPC71, modelPC71.getObb().c);
		PC71Collider.c = glm::vec3(modelMatrixColliderPC71[3]);
		PC71Collider.e = modelPC71.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC71", PC71Collider, modelMatrixPC71);

		glm::mat4 modelMatrixColliderPC72 = glm::mat4(modelMatrixPC72);
		AbstractModel::OBB PC72Collider;
		PC72Collider.u = glm::quat_cast(modelMatrixPC72);
		modelMatrixColliderPC72[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC72[3][0], modelMatrixColliderPC72[3][2]);
		modelMatrixColliderPC72 = glm::scale(modelMatrixColliderPC72, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC72 = glm::translate(modelMatrixColliderPC72, modelPC72.getObb().c);
		PC72Collider.c = glm::vec3(modelMatrixColliderPC72[3]);
		PC72Collider.e = modelPC72.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC72", PC72Collider, modelMatrixPC72);

		glm::mat4 modelMatrixColliderPC73 = glm::mat4(modelMatrixPC73);
		AbstractModel::OBB PC73Collider;
		PC73Collider.u = glm::quat_cast(modelMatrixPC73);
		modelMatrixColliderPC73[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC73[3][0], modelMatrixColliderPC73[3][2]);
		modelMatrixColliderPC73 = glm::scale(modelMatrixColliderPC73, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC73 = glm::translate(modelMatrixColliderPC73, modelPC73.getObb().c);
		PC73Collider.c = glm::vec3(modelMatrixColliderPC73[3]);
		PC73Collider.e = modelPC73.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC73", PC73Collider, modelMatrixPC73);

		glm::mat4 modelMatrixColliderPC74 = glm::mat4(modelMatrixPC74);
		AbstractModel::OBB PC74Collider;
		PC74Collider.u = glm::quat_cast(modelMatrixPC74);
		modelMatrixColliderPC74[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC70[3][0], modelMatrixColliderPC70[3][2]);
		modelMatrixColliderPC74 = glm::scale(modelMatrixColliderPC74, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC74 = glm::translate(modelMatrixColliderPC74, modelPC74.getObb().c);
		PC74Collider.c = glm::vec3(modelMatrixColliderPC74[3]);
		PC74Collider.e = modelPC74.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC74", PC74Collider, modelMatrixPC74);

		glm::mat4 modelMatrixColliderPC75 = glm::mat4(modelMatrixPC75);
		AbstractModel::OBB PC75Collider;
		PC75Collider.u = glm::quat_cast(modelMatrixPC75);
		modelMatrixColliderPC75[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC75[3][0], modelMatrixColliderPC75[3][2]);
		modelMatrixColliderPC75 = glm::scale(modelMatrixColliderPC75, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC75 = glm::translate(modelMatrixColliderPC75, modelPC75.getObb().c);
		PC75Collider.c = glm::vec3(modelMatrixColliderPC75[3]);
		PC75Collider.e = modelPC75.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC75", PC75Collider, modelMatrixPC75);

		glm::mat4 modelMatrixColliderPC76 = glm::mat4(modelMatrixPC76);
		AbstractModel::OBB PC76Collider;
		PC76Collider.u = glm::quat_cast(modelMatrixPC70);
		modelMatrixColliderPC76[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC76[3][0], modelMatrixColliderPC76[3][2]);
		modelMatrixColliderPC76 = glm::scale(modelMatrixColliderPC76, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC76 = glm::translate(modelMatrixColliderPC76, modelPC76.getObb().c);
		PC76Collider.c = glm::vec3(modelMatrixColliderPC76[3]);
		PC76Collider.e = modelPC76.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC76", PC76Collider, modelMatrixPC76);

		glm::mat4 modelMatrixColliderPC77 = glm::mat4(modelMatrixPC77);
		AbstractModel::OBB PC77Collider;
		PC77Collider.u = glm::quat_cast(modelMatrixPC77);
		modelMatrixColliderPC77[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC77[3][0], modelMatrixColliderPC77[3][2]);
		modelMatrixColliderPC77 = glm::scale(modelMatrixColliderPC77, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC77 = glm::translate(modelMatrixColliderPC77, modelPC77.getObb().c);
		PC77Collider.c = glm::vec3(modelMatrixColliderPC77[3]);
		PC77Collider.e = modelPC77.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC77", PC77Collider, modelMatrixPC77);

		glm::mat4 modelMatrixColliderPC78 = glm::mat4(modelMatrixPC78);
		AbstractModel::OBB PC78Collider;
		PC78Collider.u = glm::quat_cast(modelMatrixPC78);
		modelMatrixColliderPC78[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC78[3][0], modelMatrixColliderPC78[3][2]);
		modelMatrixColliderPC78 = glm::scale(modelMatrixColliderPC78, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC78 = glm::translate(modelMatrixColliderPC78, modelPC78.getObb().c);
		PC78Collider.c = glm::vec3(modelMatrixColliderPC78[3]);
		PC78Collider.e = modelPC78.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC78", PC78Collider, modelMatrixPC78);

		glm::mat4 modelMatrixColliderPC79 = glm::mat4(modelMatrixPC79);
		AbstractModel::OBB PC79Collider;
		PC79Collider.u = glm::quat_cast(modelMatrixPC79);
		modelMatrixColliderPC79[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC79[3][0], modelMatrixColliderPC79[3][2]);
		modelMatrixColliderPC79 = glm::scale(modelMatrixColliderPC79, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC79 = glm::translate(modelMatrixColliderPC79, modelPC79.getObb().c);
		PC79Collider.c = glm::vec3(modelMatrixColliderPC79[3]);
		PC79Collider.e = modelPC79.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC79", PC79Collider, modelMatrixPC79);
		
		glm::mat4 modelMatrixColliderPC80 = glm::mat4(modelMatrixPC80);
		AbstractModel::OBB PC80Collider;
		PC80Collider.u = glm::quat_cast(modelMatrixPC80);
		modelMatrixColliderPC80[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC80[3][0], modelMatrixColliderPC80[3][2]);
		modelMatrixColliderPC80 = glm::scale(modelMatrixColliderPC80, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC80 = glm::translate(modelMatrixColliderPC80, modelPC80.getObb().c);
		PC80Collider.c = glm::vec3(modelMatrixColliderPC80[3]);
		PC80Collider.e = modelPC80.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC80", PC80Collider, modelMatrixPC80);

		glm::mat4 modelMatrixColliderPC81 = glm::mat4(modelMatrixPC81);
		AbstractModel::OBB PC81Collider;
		PC81Collider.u = glm::quat_cast(modelMatrixPC81);
		modelMatrixColliderPC81[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC81[3][0], modelMatrixColliderPC81[3][2]);
		modelMatrixColliderPC81 = glm::scale(modelMatrixColliderPC81, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC81 = glm::translate(modelMatrixColliderPC81, modelPC81.getObb().c);
		PC81Collider.c = glm::vec3(modelMatrixColliderPC81[3]);
		PC81Collider.e = modelPC81.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC81", PC81Collider, modelMatrixPC81);

		glm::mat4 modelMatrixColliderPC82 = glm::mat4(modelMatrixPC82);
		AbstractModel::OBB PC82Collider;
		PC82Collider.u = glm::quat_cast(modelMatrixPC82);
		modelMatrixColliderPC82[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC82[3][0], modelMatrixColliderPC82[3][2]);
		modelMatrixColliderPC82 = glm::scale(modelMatrixColliderPC82, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC82 = glm::translate(modelMatrixColliderPC82, modelPC82.getObb().c);
		PC82Collider.c = glm::vec3(modelMatrixColliderPC82[3]);
		PC82Collider.e = modelPC82.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC82", PC82Collider, modelMatrixPC82);

		glm::mat4 modelMatrixColliderPC83 = glm::mat4(modelMatrixPC83);
		AbstractModel::OBB PC83Collider;
		PC83Collider.u = glm::quat_cast(modelMatrixPC83);
		modelMatrixColliderPC83[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC83[3][0], modelMatrixColliderPC83[3][2]);
		modelMatrixColliderPC83 = glm::scale(modelMatrixColliderPC83, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC83 = glm::translate(modelMatrixColliderPC83, modelPC83.getObb().c);
		PC83Collider.c = glm::vec3(modelMatrixColliderPC83[3]);
		PC83Collider.e = modelPC83.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC83", PC83Collider, modelMatrixPC83);

		glm::mat4 modelMatrixColliderPC84 = glm::mat4(modelMatrixPC84);
		AbstractModel::OBB PC84Collider;
		PC84Collider.u = glm::quat_cast(modelMatrixPC84);
		modelMatrixColliderPC84[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC84[3][0], modelMatrixColliderPC84[3][2]);
		modelMatrixColliderPC84 = glm::scale(modelMatrixColliderPC84, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC84 = glm::translate(modelMatrixColliderPC84, modelPC84.getObb().c);
		PC84Collider.c = glm::vec3(modelMatrixColliderPC84[3]);
		PC84Collider.e = modelPC84.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC84", PC84Collider, modelMatrixPC84);

		glm::mat4 modelMatrixColliderPC85 = glm::mat4(modelMatrixPC85);
		AbstractModel::OBB PC85Collider;
		PC85Collider.u = glm::quat_cast(modelMatrixPC85);
		modelMatrixColliderPC85[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC85[3][0], modelMatrixColliderPC85[3][2]);
		modelMatrixColliderPC85 = glm::scale(modelMatrixColliderPC85, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC85 = glm::translate(modelMatrixColliderPC85, modelPC85.getObb().c);
		PC85Collider.c = glm::vec3(modelMatrixColliderPC85[3]);
		PC85Collider.e = modelPC85.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC85", PC85Collider, modelMatrixPC85);

		glm::mat4 modelMatrixColliderPC86 = glm::mat4(modelMatrixPC86);
		AbstractModel::OBB PC86Collider;
		PC86Collider.u = glm::quat_cast(modelMatrixPC86);
		modelMatrixColliderPC86[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC86[3][0], modelMatrixColliderPC86[3][2]);
		modelMatrixColliderPC86 = glm::scale(modelMatrixColliderPC86, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC86 = glm::translate(modelMatrixColliderPC86, modelPC86.getObb().c);
		PC86Collider.c = glm::vec3(modelMatrixColliderPC86[3]);
		PC86Collider.e = modelPC86.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC86", PC86Collider, modelMatrixPC86);

		glm::mat4 modelMatrixColliderPC87 = glm::mat4(modelMatrixPC87);
		AbstractModel::OBB PC87Collider;
		PC87Collider.u = glm::quat_cast(modelMatrixPC87);
		modelMatrixColliderPC87[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC87[3][0], modelMatrixColliderPC87[3][2]);
		modelMatrixColliderPC87 = glm::scale(modelMatrixColliderPC87, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC87 = glm::translate(modelMatrixColliderPC87, modelPC87.getObb().c);
		PC87Collider.c = glm::vec3(modelMatrixColliderPC87[3]);
		PC87Collider.e = modelPC87.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC87", PC87Collider, modelMatrixPC87);

		glm::mat4 modelMatrixColliderPC88 = glm::mat4(modelMatrixPC88);
		AbstractModel::OBB PC88Collider;
		PC88Collider.u = glm::quat_cast(modelMatrixPC88);
		modelMatrixColliderPC88[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC88[3][0], modelMatrixColliderPC88[3][2]);
		modelMatrixColliderPC88 = glm::scale(modelMatrixColliderPC88, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC88 = glm::translate(modelMatrixColliderPC88, modelPC88.getObb().c);
		PC88Collider.c = glm::vec3(modelMatrixColliderPC88[3]);
		PC88Collider.e = modelPC88.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC88", PC88Collider, modelMatrixPC88);

		glm::mat4 modelMatrixColliderPC89 = glm::mat4(modelMatrixPC89);
		AbstractModel::OBB PC89Collider;
		PC89Collider.u = glm::quat_cast(modelMatrixPC89);
		modelMatrixColliderPC89[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC89[3][0], modelMatrixColliderPC89[3][2]);
		modelMatrixColliderPC89 = glm::scale(modelMatrixColliderPC89, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC89 = glm::translate(modelMatrixColliderPC89, modelPC89.getObb().c);
		PC89Collider.c = glm::vec3(modelMatrixColliderPC89[3]);
		PC89Collider.e = modelPC89.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC89", PC89Collider, modelMatrixPC89);
	
		glm::mat4 modelMatrixColliderPC90 = glm::mat4(modelMatrixPC90);
		AbstractModel::OBB PC90Collider;
		PC90Collider.u = glm::quat_cast(modelMatrixPC90);
		modelMatrixColliderPC90[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC90[3][0], modelMatrixColliderPC90[3][2]);
		modelMatrixColliderPC90 = glm::scale(modelMatrixColliderPC90, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC90 = glm::translate(modelMatrixColliderPC90, modelPC90.getObb().c);
		PC90Collider.c = glm::vec3(modelMatrixColliderPC90[3]);
		PC90Collider.e = modelPC90.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC90", PC90Collider, modelMatrixPC90);

		glm::mat4 modelMatrixColliderPC91 = glm::mat4(modelMatrixPC91);
		AbstractModel::OBB PC91Collider;
		PC91Collider.u = glm::quat_cast(modelMatrixPC91);
		modelMatrixColliderPC91[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC91[3][0], modelMatrixColliderPC91[3][2]);
		modelMatrixColliderPC91 = glm::scale(modelMatrixColliderPC91, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC91 = glm::translate(modelMatrixColliderPC91, modelPC91.getObb().c);
		PC91Collider.c = glm::vec3(modelMatrixColliderPC91[3]);
		PC91Collider.e = modelPC91.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC91", PC91Collider, modelMatrixPC91);

		glm::mat4 modelMatrixColliderPC92 = glm::mat4(modelMatrixPC92);
		AbstractModel::OBB PC92Collider;
		PC92Collider.u = glm::quat_cast(modelMatrixPC92);
		modelMatrixColliderPC92[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC92[3][0], modelMatrixColliderPC92[3][2]);
		modelMatrixColliderPC92 = glm::scale(modelMatrixColliderPC92, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC92 = glm::translate(modelMatrixColliderPC92, modelPC92.getObb().c);
		PC92Collider.c = glm::vec3(modelMatrixColliderPC92[3]);
		PC92Collider.e = modelPC92.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC92", PC92Collider, modelMatrixPC92);

		glm::mat4 modelMatrixColliderPC93 = glm::mat4(modelMatrixPC93);
		AbstractModel::OBB PC93Collider;
		PC93Collider.u = glm::quat_cast(modelMatrixPC93);
		modelMatrixColliderPC93[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC93[3][0], modelMatrixColliderPC93[3][2]);
		modelMatrixColliderPC93 = glm::scale(modelMatrixColliderPC93, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC93 = glm::translate(modelMatrixColliderPC93, modelPC93.getObb().c);
		PC93Collider.c = glm::vec3(modelMatrixColliderPC93[3]);
		PC93Collider.e = modelPC93.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC93", PC93Collider, modelMatrixPC93);

		glm::mat4 modelMatrixColliderPC94 = glm::mat4(modelMatrixPC94);
		AbstractModel::OBB PC94Collider;
		PC94Collider.u = glm::quat_cast(modelMatrixPC94);
		modelMatrixColliderPC94[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC94[3][0], modelMatrixColliderPC94[3][2]);
		modelMatrixColliderPC94 = glm::scale(modelMatrixColliderPC94, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC94 = glm::translate(modelMatrixColliderPC94, modelPC94.getObb().c);
		PC94Collider.c = glm::vec3(modelMatrixColliderPC94[3]);
		PC94Collider.e = modelPC94.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC94", PC94Collider, modelMatrixPC94);

		glm::mat4 modelMatrixColliderPC95 = glm::mat4(modelMatrixPC95);
		AbstractModel::OBB PC95Collider;
		PC95Collider.u = glm::quat_cast(modelMatrixPC95);
		modelMatrixColliderPC95[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC95[3][0], modelMatrixColliderPC95[3][2]);
		modelMatrixColliderPC95 = glm::scale(modelMatrixColliderPC95, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC95 = glm::translate(modelMatrixColliderPC95, modelPC95.getObb().c);
		PC95Collider.c = glm::vec3(modelMatrixColliderPC95[3]);
		PC95Collider.e = modelPC95.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC95", PC95Collider, modelMatrixPC95);

		glm::mat4 modelMatrixColliderPC96 = glm::mat4(modelMatrixPC96);
		AbstractModel::OBB PC96Collider;
		PC96Collider.u = glm::quat_cast(modelMatrixPC96);
		modelMatrixColliderPC96[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC96[3][0], modelMatrixColliderPC96[3][2]);
		modelMatrixColliderPC96 = glm::scale(modelMatrixColliderPC96, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC96 = glm::translate(modelMatrixColliderPC96, modelPC96.getObb().c);
		PC96Collider.c = glm::vec3(modelMatrixColliderPC96[3]);
		PC96Collider.e = modelPC96.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC96", PC96Collider, modelMatrixPC96);

		glm::mat4 modelMatrixColliderPC97 = glm::mat4(modelMatrixPC97);
		AbstractModel::OBB PC97Collider;
		PC97Collider.u = glm::quat_cast(modelMatrixPC97);
		modelMatrixColliderPC97[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC97[3][0], modelMatrixColliderPC97[3][2]);
		modelMatrixColliderPC97 = glm::scale(modelMatrixColliderPC97, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC97 = glm::translate(modelMatrixColliderPC97, modelPC97.getObb().c);
		PC97Collider.c = glm::vec3(modelMatrixColliderPC97[3]);
		PC97Collider.e = modelPC97.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC97", PC97Collider, modelMatrixPC97);

		glm::mat4 modelMatrixColliderPC98 = glm::mat4(modelMatrixPC98);
		AbstractModel::OBB PC98Collider;
		PC98Collider.u = glm::quat_cast(modelMatrixPC98);
		modelMatrixColliderPC98[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC98[3][0], modelMatrixColliderPC98[3][2]);
		modelMatrixColliderPC98 = glm::scale(modelMatrixColliderPC98, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC98 = glm::translate(modelMatrixColliderPC98, modelPC98.getObb().c);
		PC98Collider.c = glm::vec3(modelMatrixColliderPC98[3]);
		PC98Collider.e = modelPC98.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC98", PC98Collider, modelMatrixPC98);

		glm::mat4 modelMatrixColliderPC99 = glm::mat4(modelMatrixPC99);
		AbstractModel::OBB PC99Collider;
		PC99Collider.u = glm::quat_cast(modelMatrixPC99);
		modelMatrixColliderPC99[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC99[3][0], modelMatrixColliderPC99[3][2]);
		modelMatrixColliderPC99 = glm::scale(modelMatrixColliderPC99, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC99 = glm::translate(modelMatrixColliderPC99, modelPC99.getObb().c);
		PC99Collider.c = glm::vec3(modelMatrixColliderPC99[3]);
		PC99Collider.e = modelPC99.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC99", PC99Collider, modelMatrixPC99);
		
		
		glm::mat4 modelMatrixColliderPC100 = glm::mat4(modelMatrixPC100);
		AbstractModel::OBB PC100Collider;
		PC100Collider.u = glm::quat_cast(modelMatrixPC100);
		modelMatrixColliderPC100[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC100[3][0], modelMatrixColliderPC100[3][2]);
		modelMatrixColliderPC100 = glm::scale(modelMatrixColliderPC100, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC100 = glm::translate(modelMatrixColliderPC100, modelPC100.getObb().c);
		PC100Collider.c = glm::vec3(modelMatrixColliderPC100[3]);
		PC100Collider.e = modelPC100.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC100", PC100Collider, modelMatrixPC100);

		glm::mat4 modelMatrixColliderPC101 = glm::mat4(modelMatrixPC101);
		AbstractModel::OBB PC101Collider;
		PC101Collider.u = glm::quat_cast(modelMatrixPC101);
		modelMatrixColliderPC101[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC101[3][0], modelMatrixColliderPC101[3][2]);
		modelMatrixColliderPC101 = glm::scale(modelMatrixColliderPC101, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC101 = glm::translate(modelMatrixColliderPC101, modelPC101.getObb().c);
		PC101Collider.c = glm::vec3(modelMatrixColliderPC101[3]);
		PC101Collider.e = modelPC101.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC101", PC101Collider, modelMatrixPC101);

		glm::mat4 modelMatrixColliderPC102 = glm::mat4(modelMatrixPC102);
		AbstractModel::OBB PC102Collider;
		PC102Collider.u = glm::quat_cast(modelMatrixPC102);
		modelMatrixColliderPC102[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC102[3][0], modelMatrixColliderPC102[3][2]);
		modelMatrixColliderPC102 = glm::scale(modelMatrixColliderPC102, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC102 = glm::translate(modelMatrixColliderPC102, modelPC102.getObb().c);
		PC102Collider.c = glm::vec3(modelMatrixColliderPC102[3]);
		PC102Collider.e = modelPC102.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC102", PC102Collider, modelMatrixPC102);

		glm::mat4 modelMatrixColliderPC103 = glm::mat4(modelMatrixPC103);
		AbstractModel::OBB PC103Collider;
		PC103Collider.u = glm::quat_cast(modelMatrixPC103);
		modelMatrixColliderPC103[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC103[3][0], modelMatrixColliderPC103[3][2]);
		modelMatrixColliderPC103 = glm::scale(modelMatrixColliderPC103, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC103 = glm::translate(modelMatrixColliderPC103, modelPC103.getObb().c);
		PC103Collider.c = glm::vec3(modelMatrixColliderPC103[3]);
		PC103Collider.e = modelPC103.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC103", PC103Collider, modelMatrixPC103);

		glm::mat4 modelMatrixColliderPC104 = glm::mat4(modelMatrixPC104);
		AbstractModel::OBB PC104Collider;
		PC104Collider.u = glm::quat_cast(modelMatrixPC104);
		modelMatrixColliderPC104[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC104[3][0], modelMatrixColliderPC104[3][2]);
		modelMatrixColliderPC104 = glm::scale(modelMatrixColliderPC104, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC104 = glm::translate(modelMatrixColliderPC104, modelPC104.getObb().c);
		PC104Collider.c = glm::vec3(modelMatrixColliderPC104[3]);
		PC104Collider.e = modelPC104.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC104", PC104Collider, modelMatrixPC104);

		glm::mat4 modelMatrixColliderPC105 = glm::mat4(modelMatrixPC105);
		AbstractModel::OBB PC105Collider;
		PC105Collider.u = glm::quat_cast(modelMatrixPC105);
		modelMatrixColliderPC105[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC105[3][0], modelMatrixColliderPC105[3][2]);
		modelMatrixColliderPC105 = glm::scale(modelMatrixColliderPC105, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC105 = glm::translate(modelMatrixColliderPC105, modelPC105.getObb().c);
		PC105Collider.c = glm::vec3(modelMatrixColliderPC105[3]);
		PC105Collider.e = modelPC105.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC105", PC105Collider, modelMatrixPC105);

		glm::mat4 modelMatrixColliderPC106 = glm::mat4(modelMatrixPC106);
		AbstractModel::OBB PC106Collider;
		PC106Collider.u = glm::quat_cast(modelMatrixPC106);
		modelMatrixColliderPC106[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC106[3][0], modelMatrixColliderPC106[3][2]);
		modelMatrixColliderPC106 = glm::scale(modelMatrixColliderPC106, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC106 = glm::translate(modelMatrixColliderPC106, modelPC106.getObb().c);
		PC106Collider.c = glm::vec3(modelMatrixColliderPC106[3]);
		PC106Collider.e = modelPC106.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC106", PC106Collider, modelMatrixPC106);

		glm::mat4 modelMatrixColliderPC107 = glm::mat4(modelMatrixPC107);
		AbstractModel::OBB PC107Collider;
		PC107Collider.u = glm::quat_cast(modelMatrixPC107);
		modelMatrixColliderPC107[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC107[3][0], modelMatrixColliderPC107[3][2]);
		modelMatrixColliderPC107 = glm::scale(modelMatrixColliderPC107, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC107 = glm::translate(modelMatrixColliderPC107, modelPC107.getObb().c);
		PC107Collider.c = glm::vec3(modelMatrixColliderPC107[3]);
		PC107Collider.e = modelPC107.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC107", PC107Collider, modelMatrixPC107);

		glm::mat4 modelMatrixColliderPC108 = glm::mat4(modelMatrixPC108);
		AbstractModel::OBB PC108Collider;
		PC108Collider.u = glm::quat_cast(modelMatrixPC108);
		modelMatrixColliderPC108[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC108[3][0], modelMatrixColliderPC108[3][2]);
		modelMatrixColliderPC108 = glm::scale(modelMatrixColliderPC108, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC108 = glm::translate(modelMatrixColliderPC108, modelPC108.getObb().c);
		PC108Collider.c = glm::vec3(modelMatrixColliderPC108[3]);
		PC108Collider.e = modelPC108.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC108", PC108Collider, modelMatrixPC108);

		glm::mat4 modelMatrixColliderPC109 = glm::mat4(modelMatrixPC109);
		AbstractModel::OBB PC109Collider;
		PC109Collider.u = glm::quat_cast(modelMatrixPC109);
		modelMatrixColliderPC109[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC109[3][0], modelMatrixColliderPC109[3][2]);
		modelMatrixColliderPC109 = glm::scale(modelMatrixColliderPC109, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC109 = glm::translate(modelMatrixColliderPC109, modelPC109.getObb().c);
		PC109Collider.c = glm::vec3(modelMatrixColliderPC109[3]);
		PC109Collider.e = modelPC109.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC109", PC109Collider, modelMatrixPC109);

		glm::mat4 modelMatrixColliderPC110 = glm::mat4(modelMatrixPC110);
		AbstractModel::OBB PC110Collider;
		PC110Collider.u = glm::quat_cast(modelMatrixPC110);
		modelMatrixColliderPC110[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC110[3][0], modelMatrixColliderPC110[3][2]);
		modelMatrixColliderPC110 = glm::scale(modelMatrixColliderPC110, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC110 = glm::translate(modelMatrixColliderPC110, modelPC110.getObb().c);
		PC110Collider.c = glm::vec3(modelMatrixColliderPC110[3]);
		PC110Collider.e = modelPC110.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC110", PC110Collider, modelMatrixPC110);

		glm::mat4 modelMatrixColliderPC111 = glm::mat4(modelMatrixPC111);
		AbstractModel::OBB PC111Collider;
		PC111Collider.u = glm::quat_cast(modelMatrixPC111);
		modelMatrixColliderPC111[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC111[3][0], modelMatrixColliderPC111[3][2]);
		modelMatrixColliderPC111 = glm::scale(modelMatrixColliderPC111, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC111 = glm::translate(modelMatrixColliderPC111, modelPC111.getObb().c);
		PC111Collider.c = glm::vec3(modelMatrixColliderPC111[3]);
		PC111Collider.e = modelPC111.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC111", PC111Collider, modelMatrixPC111);

		glm::mat4 modelMatrixColliderPC112 = glm::mat4(modelMatrixPC112);
		AbstractModel::OBB PC112Collider;
		PC112Collider.u = glm::quat_cast(modelMatrixPC112);
		modelMatrixColliderPC112[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC112[3][0], modelMatrixColliderPC112[3][2]);
		modelMatrixColliderPC112 = glm::scale(modelMatrixColliderPC112, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC112 = glm::translate(modelMatrixColliderPC112, modelPC112.getObb().c);
		PC112Collider.c = glm::vec3(modelMatrixColliderPC112[3]);
		PC112Collider.e = modelPC112.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC112", PC112Collider, modelMatrixPC112);

		glm::mat4 modelMatrixColliderPC113 = glm::mat4(modelMatrixPC113);
		AbstractModel::OBB PC113Collider;
		PC113Collider.u = glm::quat_cast(modelMatrixPC113);
		modelMatrixColliderPC113[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC113[3][0], modelMatrixColliderPC113[3][2]);
		modelMatrixColliderPC113 = glm::scale(modelMatrixColliderPC113, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC113 = glm::translate(modelMatrixColliderPC113, modelPC113.getObb().c);
		PC113Collider.c = glm::vec3(modelMatrixColliderPC113[3]);
		PC113Collider.e = modelPC113.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC113", PC113Collider, modelMatrixPC113);

		glm::mat4 modelMatrixColliderPC114 = glm::mat4(modelMatrixPC114);
		AbstractModel::OBB PC114Collider;
		PC114Collider.u = glm::quat_cast(modelMatrixPC114);
		modelMatrixColliderPC114[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC114[3][0], modelMatrixColliderPC114[3][2]);
		modelMatrixColliderPC114 = glm::scale(modelMatrixColliderPC114, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC114 = glm::translate(modelMatrixColliderPC114, modelPC114.getObb().c);
		PC114Collider.c = glm::vec3(modelMatrixColliderPC114[3]);
		PC114Collider.e = modelPC114.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC114", PC114Collider, modelMatrixPC114);

		glm::mat4 modelMatrixColliderPC115 = glm::mat4(modelMatrixPC115);
		AbstractModel::OBB PC115Collider;
		PC115Collider.u = glm::quat_cast(modelMatrixPC115);
		modelMatrixColliderPC115[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC115[3][0], modelMatrixColliderPC115[3][2]);
		modelMatrixColliderPC115 = glm::scale(modelMatrixColliderPC115, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC115 = glm::translate(modelMatrixColliderPC115, modelPC115.getObb().c);
		PC115Collider.c = glm::vec3(modelMatrixColliderPC115[3]);
		PC115Collider.e = modelPC115.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC115", PC115Collider, modelMatrixPC115);

		glm::mat4 modelMatrixColliderPC116 = glm::mat4(modelMatrixPC116);
		AbstractModel::OBB PC116Collider;
		PC116Collider.u = glm::quat_cast(modelMatrixPC116);
		modelMatrixColliderPC116[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC116[3][0], modelMatrixColliderPC116[3][2]);
		modelMatrixColliderPC116 = glm::scale(modelMatrixColliderPC116, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC116 = glm::translate(modelMatrixColliderPC116, modelPC116.getObb().c);
		PC116Collider.c = glm::vec3(modelMatrixColliderPC116[3]);
		PC116Collider.e = modelPC116.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC116", PC116Collider, modelMatrixPC116);

		glm::mat4 modelMatrixColliderPC117 = glm::mat4(modelMatrixPC117);
		AbstractModel::OBB PC117Collider;
		PC117Collider.u = glm::quat_cast(modelMatrixPC117);
		modelMatrixColliderPC117[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC117[3][0], modelMatrixColliderPC117[3][2]);
		modelMatrixColliderPC117 = glm::scale(modelMatrixColliderPC117, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC117 = glm::translate(modelMatrixColliderPC117, modelPC117.getObb().c);
		PC117Collider.c = glm::vec3(modelMatrixColliderPC117[3]);
		PC117Collider.e = modelPC117.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC117", PC117Collider, modelMatrixPC117);

		glm::mat4 modelMatrixColliderPC118 = glm::mat4(modelMatrixPC118);
		AbstractModel::OBB PC118Collider;
		PC118Collider.u = glm::quat_cast(modelMatrixPC118);
		modelMatrixColliderPC118[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC118[3][0], modelMatrixColliderPC118[3][2]);
		modelMatrixColliderPC118 = glm::scale(modelMatrixColliderPC118, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC118 = glm::translate(modelMatrixColliderPC118, modelPC118.getObb().c);
		PC118Collider.c = glm::vec3(modelMatrixColliderPC118[3]);
		PC118Collider.e = modelPC118.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC118", PC118Collider, modelMatrixPC118);

		glm::mat4 modelMatrixColliderPC119 = glm::mat4(modelMatrixPC119);
		AbstractModel::OBB PC119Collider;
		PC119Collider.u = glm::quat_cast(modelMatrixPC119);
		modelMatrixColliderPC119[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC119[3][0], modelMatrixColliderPC119[3][2]);
		modelMatrixColliderPC119 = glm::scale(modelMatrixColliderPC119, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC119 = glm::translate(modelMatrixColliderPC119, modelPC119.getObb().c);
		PC119Collider.c = glm::vec3(modelMatrixColliderPC119[3]);
		PC119Collider.e = modelPC119.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC119", PC119Collider, modelMatrixPC119);

		glm::mat4 modelMatrixColliderPC120 = glm::mat4(modelMatrixPC120);
		AbstractModel::OBB PC120Collider;
		PC120Collider.u = glm::quat_cast(modelMatrixPC120);
		modelMatrixColliderPC120[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC120[3][0], modelMatrixColliderPC120[3][2]);
		modelMatrixColliderPC120 = glm::scale(modelMatrixColliderPC120, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC120 = glm::translate(modelMatrixColliderPC120, modelPC120.getObb().c);
		PC120Collider.c = glm::vec3(modelMatrixColliderPC120[3]);
		PC120Collider.e = modelPC120.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC120", PC120Collider, modelMatrixPC120);
		
		glm::mat4 modelMatrixColliderPC121 = glm::mat4(modelMatrixPC121);
		AbstractModel::OBB PC121Collider;
		PC121Collider.u = glm::quat_cast(modelMatrixPC121);
		modelMatrixColliderPC121[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC121[3][0], modelMatrixColliderPC121[3][2]);
		modelMatrixColliderPC121 = glm::scale(modelMatrixColliderPC121, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC121 = glm::translate(modelMatrixColliderPC121, modelPC121.getObb().c);
		PC121Collider.c = glm::vec3(modelMatrixColliderPC121[3]);
		PC121Collider.e = modelPC121.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC121", PC121Collider, modelMatrixPC121);

		glm::mat4 modelMatrixColliderPC122 = glm::mat4(modelMatrixPC122);
		AbstractModel::OBB PC122Collider;
		PC122Collider.u = glm::quat_cast(modelMatrixPC122);
		modelMatrixColliderPC122[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC122[3][0], modelMatrixColliderPC122[3][2]);
		modelMatrixColliderPC122 = glm::scale(modelMatrixColliderPC122, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC122 = glm::translate(modelMatrixColliderPC122, modelPC122.getObb().c);
		PC122Collider.c = glm::vec3(modelMatrixColliderPC122[3]);
		PC122Collider.e = modelPC122.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC122", PC122Collider, modelMatrixPC122);

		glm::mat4 modelMatrixColliderPC123 = glm::mat4(modelMatrixPC123);
		AbstractModel::OBB PC123Collider;
		PC123Collider.u = glm::quat_cast(modelMatrixPC123);
		modelMatrixColliderPC123[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC123[3][0], modelMatrixColliderPC123[3][2]);
		modelMatrixColliderPC123 = glm::scale(modelMatrixColliderPC123, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC123 = glm::translate(modelMatrixColliderPC123, modelPC123.getObb().c);
		PC123Collider.c = glm::vec3(modelMatrixColliderPC123[3]);
		PC123Collider.e = modelPC123.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC123", PC123Collider, modelMatrixPC123);

		glm::mat4 modelMatrixColliderPC124 = glm::mat4(modelMatrixPC124);
		AbstractModel::OBB PC124Collider;
		PC124Collider.u = glm::quat_cast(modelMatrixPC124);
		modelMatrixColliderPC124[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC124[3][0], modelMatrixColliderPC124[3][2]);
		modelMatrixColliderPC124 = glm::scale(modelMatrixColliderPC124, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC124 = glm::translate(modelMatrixColliderPC124, modelPC124.getObb().c);
		PC124Collider.c = glm::vec3(modelMatrixColliderPC124[3]);
		PC124Collider.e = modelPC124.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC124", PC124Collider, modelMatrixPC124);

		glm::mat4 modelMatrixColliderPC125 = glm::mat4(modelMatrixPC125);
		AbstractModel::OBB PC125Collider;
		PC125Collider.u = glm::quat_cast(modelMatrixPC125);
		modelMatrixColliderPC125[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC125[3][0], modelMatrixColliderPC125[3][2]);
		modelMatrixColliderPC125 = glm::scale(modelMatrixColliderPC125, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC125 = glm::translate(modelMatrixColliderPC125, modelPC125.getObb().c);
		PC125Collider.c = glm::vec3(modelMatrixColliderPC125[3]);
		PC125Collider.e = modelPC125.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC125", PC125Collider, modelMatrixPC125);
		
		glm::mat4 modelMatrixColliderPC126 = glm::mat4(modelMatrixPC126);
		AbstractModel::OBB PC126Collider;
		PC126Collider.u = glm::quat_cast(modelMatrixPC126);
		modelMatrixColliderPC126[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC126[3][0], modelMatrixColliderPC126[3][2]);
		modelMatrixColliderPC126 = glm::scale(modelMatrixColliderPC126, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC126 = glm::translate(modelMatrixColliderPC126, modelPC126.getObb().c);
		PC126Collider.c = glm::vec3(modelMatrixColliderPC126[3]);
		PC126Collider.e = modelPC126.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC126", PC126Collider, modelMatrixPC126);
		
		glm::mat4 modelMatrixColliderPC127 = glm::mat4(modelMatrixPC127);
		AbstractModel::OBB PC127Collider;
		PC127Collider.u = glm::quat_cast(modelMatrixPC127);
		modelMatrixColliderPC127[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC127[3][0], modelMatrixColliderPC127[3][2]);
		modelMatrixColliderPC127 = glm::scale(modelMatrixColliderPC127, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC127 = glm::translate(modelMatrixColliderPC127, modelPC127.getObb().c);
		PC127Collider.c = glm::vec3(modelMatrixColliderPC127[3]);
		PC127Collider.e = modelPC127.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC127", PC127Collider, modelMatrixPC127);

		glm::mat4 modelMatrixColliderPC128 = glm::mat4(modelMatrixPC128);
		AbstractModel::OBB PC128Collider;
		PC128Collider.u = glm::quat_cast(modelMatrixPC128);
		modelMatrixColliderPC128[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC128[3][0], modelMatrixColliderPC128[3][2]);
		modelMatrixColliderPC128 = glm::scale(modelMatrixColliderPC128, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC128 = glm::translate(modelMatrixColliderPC128, modelPC128.getObb().c);
		PC128Collider.c = glm::vec3(modelMatrixColliderPC128[3]);
		PC128Collider.e = modelPC128.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC128", PC128Collider, modelMatrixPC128);

		glm::mat4 modelMatrixColliderPC129 = glm::mat4(modelMatrixPC129);
		AbstractModel::OBB PC129Collider;
		PC129Collider.u = glm::quat_cast(modelMatrixPC129);
		modelMatrixColliderPC129[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC129[3][0], modelMatrixColliderPC129[3][2]);
		modelMatrixColliderPC129 = glm::scale(modelMatrixColliderPC129, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC129 = glm::translate(modelMatrixColliderPC129, modelPC129.getObb().c);
		PC129Collider.c = glm::vec3(modelMatrixColliderPC129[3]);
		PC129Collider.e = modelPC129.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC129", PC129Collider, modelMatrixPC129);
		
		glm::mat4 modelMatrixColliderPC130 = glm::mat4(modelMatrixPC130);
		AbstractModel::OBB PC130Collider;
		PC130Collider.u = glm::quat_cast(modelMatrixPC130);
		modelMatrixColliderPC130[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC130[3][0], modelMatrixColliderPC130[3][2]);
		modelMatrixColliderPC130 = glm::scale(modelMatrixColliderPC130, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC130 = glm::translate(modelMatrixColliderPC130, modelPC130.getObb().c);
		PC130Collider.c = glm::vec3(modelMatrixColliderPC130[3]);
		PC130Collider.e = modelPC130.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC130", PC130Collider, modelMatrixPC130);
		//Todo bien hasta aquí
		glm::mat4 modelMatrixColliderPC131 = glm::mat4(modelMatrixPC131);
		AbstractModel::OBB PC131Collider;
		PC131Collider.u = glm::quat_cast(modelMatrixPC131);
		modelMatrixColliderPC131[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC131[3][0], modelMatrixColliderPC131[3][2]);
		modelMatrixColliderPC131 = glm::scale(modelMatrixColliderPC131, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC131 = glm::translate(modelMatrixColliderPC131, modelPC131.getObb().c);
		PC131Collider.c = glm::vec3(modelMatrixColliderPC131[3]);
		PC131Collider.e = modelPC131.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC131", PC131Collider, modelMatrixPC131);

		glm::mat4 modelMatrixColliderPC132 = glm::mat4(modelMatrixPC132);
		AbstractModel::OBB PC132Collider;
		PC132Collider.u = glm::quat_cast(modelMatrixPC132);
		modelMatrixColliderPC130[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC132[3][0], modelMatrixColliderPC132[3][2]);
		modelMatrixColliderPC132 = glm::scale(modelMatrixColliderPC132, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC132 = glm::translate(modelMatrixColliderPC132, modelPC132.getObb().c);
		PC132Collider.c = glm::vec3(modelMatrixColliderPC132[3]);
		PC132Collider.e = modelPC132.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC132", PC132Collider, modelMatrixPC132);

		glm::mat4 modelMatrixColliderPC133 = glm::mat4(modelMatrixPC133);
		AbstractModel::OBB PC133Collider;
		PC133Collider.u = glm::quat_cast(modelMatrixPC133);
		modelMatrixColliderPC133[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC130[3][0], modelMatrixColliderPC130[3][2]);
		modelMatrixColliderPC133 = glm::scale(modelMatrixColliderPC133, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC133 = glm::translate(modelMatrixColliderPC133, modelPC133.getObb().c);
		PC133Collider.c = glm::vec3(modelMatrixColliderPC133[3]);
		PC133Collider.e = modelPC133.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC133", PC133Collider, modelMatrixPC133);

		glm::mat4 modelMatrixColliderPC134 = glm::mat4(modelMatrixPC134);
		AbstractModel::OBB PC134Collider;
		PC134Collider.u = glm::quat_cast(modelMatrixPC134);
		modelMatrixColliderPC134[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC134[3][0], modelMatrixColliderPC134[3][2]);
		modelMatrixColliderPC134 = glm::scale(modelMatrixColliderPC134, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC134 = glm::translate(modelMatrixColliderPC134, modelPC134.getObb().c);
		PC134Collider.c = glm::vec3(modelMatrixColliderPC134[3]);
		PC134Collider.e = modelPC134.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC134", PC134Collider, modelMatrixPC134);

		glm::mat4 modelMatrixColliderPC135 = glm::mat4(modelMatrixPC135);
		AbstractModel::OBB PC135Collider;
		PC135Collider.u = glm::quat_cast(modelMatrixPC135);
		modelMatrixColliderPC135[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC135[3][0], modelMatrixColliderPC135[3][2]);
		modelMatrixColliderPC135 = glm::scale(modelMatrixColliderPC135, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC135 = glm::translate(modelMatrixColliderPC135, modelPC135.getObb().c);
		PC135Collider.c = glm::vec3(modelMatrixColliderPC135[3]);
		PC135Collider.e = modelPC135.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC135", PC135Collider, modelMatrixPC135);

		glm::mat4 modelMatrixColliderPC136 = glm::mat4(modelMatrixPC136);
		AbstractModel::OBB PC136Collider;
		PC136Collider.u = glm::quat_cast(modelMatrixPC136);
		modelMatrixColliderPC136[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC136[3][0], modelMatrixColliderPC136[3][2]);
		modelMatrixColliderPC136 = glm::scale(modelMatrixColliderPC136, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC136 = glm::translate(modelMatrixColliderPC136, modelPC136.getObb().c);
		PC136Collider.c = glm::vec3(modelMatrixColliderPC136[3]);
		PC136Collider.e = modelPC136.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC136", PC136Collider, modelMatrixPC136);

		glm::mat4 modelMatrixColliderPC137 = glm::mat4(modelMatrixPC137);
		AbstractModel::OBB PC137Collider;
		PC137Collider.u = glm::quat_cast(modelMatrixPC137);
		modelMatrixColliderPC137[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC137[3][0], modelMatrixColliderPC137[3][2]);
		modelMatrixColliderPC137 = glm::scale(modelMatrixColliderPC137, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC137 = glm::translate(modelMatrixColliderPC137, modelPC137.getObb().c);
		PC137Collider.c = glm::vec3(modelMatrixColliderPC137[3]);
		PC137Collider.e = modelPC137.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC137", PC137Collider, modelMatrixPC137);

		glm::mat4 modelMatrixColliderPC138 = glm::mat4(modelMatrixPC138);
		AbstractModel::OBB PC138Collider;
		PC138Collider.u = glm::quat_cast(modelMatrixPC138);
		modelMatrixColliderPC138[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC138[3][0], modelMatrixColliderPC138[3][2]);
		modelMatrixColliderPC138 = glm::scale(modelMatrixColliderPC138, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC138 = glm::translate(modelMatrixColliderPC138, modelPC138.getObb().c);
		PC138Collider.c = glm::vec3(modelMatrixColliderPC138[3]);
		PC138Collider.e = modelPC138.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC138", PC138Collider, modelMatrixPC138);

		glm::mat4 modelMatrixColliderPC139 = glm::mat4(modelMatrixPC139);
		AbstractModel::OBB PC139Collider;
		PC139Collider.u = glm::quat_cast(modelMatrixPC139);
		modelMatrixColliderPC139[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC139[3][0], modelMatrixColliderPC139[3][2]);
		modelMatrixColliderPC139 = glm::scale(modelMatrixColliderPC139, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC139 = glm::translate(modelMatrixColliderPC139, modelPC139.getObb().c);
		PC139Collider.c = glm::vec3(modelMatrixColliderPC139[3]);
		PC139Collider.e = modelPC139.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC139", PC139Collider, modelMatrixPC139);

		glm::mat4 modelMatrixColliderPC140 = glm::mat4(modelMatrixPC140);
		AbstractModel::OBB PC140Collider;
		PC140Collider.u = glm::quat_cast(modelMatrixPC140);
		modelMatrixColliderPC140[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC140[3][0], modelMatrixColliderPC140[3][2]);
		modelMatrixColliderPC140 = glm::scale(modelMatrixColliderPC140, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC140 = glm::translate(modelMatrixColliderPC140, modelPC140.getObb().c);
		PC140Collider.c = glm::vec3(modelMatrixColliderPC140[3]);
		PC140Collider.e = modelPC140.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC140", PC140Collider, modelMatrixPC140);

		glm::mat4 modelMatrixColliderPC141 = glm::mat4(modelMatrixPC141);
		AbstractModel::OBB PC141Collider;
		PC141Collider.u = glm::quat_cast(modelMatrixPC141);
		modelMatrixColliderPC141[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC141[3][0], modelMatrixColliderPC141[3][2]);
		modelMatrixColliderPC141 = glm::scale(modelMatrixColliderPC141, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC141 = glm::translate(modelMatrixColliderPC141, modelPC141.getObb().c);
		PC141Collider.c = glm::vec3(modelMatrixColliderPC141[3]);
		PC141Collider.e = modelPC141.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC141", PC141Collider, modelMatrixPC141);

		glm::mat4 modelMatrixColliderPC142 = glm::mat4(modelMatrixPC142);
		AbstractModel::OBB PC142Collider;
		PC142Collider.u = glm::quat_cast(modelMatrixPC142);
		modelMatrixColliderPC142[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC142[3][0], modelMatrixColliderPC142[3][2]);
		modelMatrixColliderPC142 = glm::scale(modelMatrixColliderPC142, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC142 = glm::translate(modelMatrixColliderPC142, modelPC142.getObb().c);
		PC142Collider.c = glm::vec3(modelMatrixColliderPC142[3]);
		PC142Collider.e = modelPC142.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC142", PC142Collider, modelMatrixPC142);

		glm::mat4 modelMatrixColliderPC143 = glm::mat4(modelMatrixPC143);
		AbstractModel::OBB PC143Collider;
		PC143Collider.u = glm::quat_cast(modelMatrixPC143);
		modelMatrixColliderPC143[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC143[3][0], modelMatrixColliderPC143[3][2]);
		modelMatrixColliderPC143 = glm::scale(modelMatrixColliderPC143, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC143 = glm::translate(modelMatrixColliderPC143, modelPC143.getObb().c);
		PC143Collider.c = glm::vec3(modelMatrixColliderPC143[3]);
		PC143Collider.e = modelPC143.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC143", PC143Collider, modelMatrixPC143);

		glm::mat4 modelMatrixColliderPC144 = glm::mat4(modelMatrixPC144);
		AbstractModel::OBB PC144Collider;
		PC144Collider.u = glm::quat_cast(modelMatrixPC144);
		modelMatrixColliderPC144[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC144[3][0], modelMatrixColliderPC144[3][2]);
		modelMatrixColliderPC144 = glm::scale(modelMatrixColliderPC144, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC144 = glm::translate(modelMatrixColliderPC144, modelPC144.getObb().c);
		PC144Collider.c = glm::vec3(modelMatrixColliderPC144[3]);
		PC144Collider.e = modelPC144.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC144", PC144Collider, modelMatrixPC144);

		glm::mat4 modelMatrixColliderPC145 = glm::mat4(modelMatrixPC145);
		AbstractModel::OBB PC145Collider;
		PC145Collider.u = glm::quat_cast(modelMatrixPC145);
		modelMatrixColliderPC145[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC145[3][0], modelMatrixColliderPC145[3][2]);
		modelMatrixColliderPC145 = glm::scale(modelMatrixColliderPC145, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC145 = glm::translate(modelMatrixColliderPC145, modelPC145.getObb().c);
		PC145Collider.c = glm::vec3(modelMatrixColliderPC145[3]);
		PC145Collider.e = modelPC145.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC145", PC145Collider, modelMatrixPC145);

		glm::mat4 modelMatrixColliderPC146 = glm::mat4(modelMatrixPC146);
		AbstractModel::OBB PC146Collider;
		PC146Collider.u = glm::quat_cast(modelMatrixPC146);
		modelMatrixColliderPC146[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC146[3][0], modelMatrixColliderPC146[3][2]);
		modelMatrixColliderPC146 = glm::scale(modelMatrixColliderPC146, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC146 = glm::translate(modelMatrixColliderPC146, modelPC146.getObb().c);
		PC146Collider.c = glm::vec3(modelMatrixColliderPC146[3]);
		PC146Collider.e = modelPC146.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC146", PC146Collider, modelMatrixPC146);

		glm::mat4 modelMatrixColliderPC147 = glm::mat4(modelMatrixPC147);
		AbstractModel::OBB PC147Collider;
		PC147Collider.u = glm::quat_cast(modelMatrixPC147);
		modelMatrixColliderPC147[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC147[3][0], modelMatrixColliderPC147[3][2]);
		modelMatrixColliderPC147 = glm::scale(modelMatrixColliderPC147, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC147 = glm::translate(modelMatrixColliderPC147, modelPC147.getObb().c);
		PC147Collider.c = glm::vec3(modelMatrixColliderPC147[3]);
		PC147Collider.e = modelPC147.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC147", PC147Collider, modelMatrixPC147);

		glm::mat4 modelMatrixColliderPC148 = glm::mat4(modelMatrixPC148);
		AbstractModel::OBB PC148Collider;
		PC148Collider.u = glm::quat_cast(modelMatrixPC148);
		modelMatrixColliderPC148[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC141[3][0], modelMatrixColliderPC141[3][2]);
		modelMatrixColliderPC148 = glm::scale(modelMatrixColliderPC148, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC148 = glm::translate(modelMatrixColliderPC148, modelPC148.getObb().c);
		PC148Collider.c = glm::vec3(modelMatrixColliderPC148[3]);
		PC148Collider.e = modelPC148.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC148", PC148Collider, modelMatrixPC148);

		glm::mat4 modelMatrixColliderPC149 = glm::mat4(modelMatrixPC149);
		AbstractModel::OBB PC149Collider;
		PC149Collider.u = glm::quat_cast(modelMatrixPC149);
		modelMatrixColliderPC149[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC149[3][0], modelMatrixColliderPC149[3][2]);
		modelMatrixColliderPC149 = glm::scale(modelMatrixColliderPC149, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC149 = glm::translate(modelMatrixColliderPC149, modelPC149.getObb().c);
		PC149Collider.c = glm::vec3(modelMatrixColliderPC149[3]);
		PC149Collider.e = modelPC149.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC149", PC149Collider, modelMatrixPC149);

		glm::mat4 modelMatrixColliderPC150 = glm::mat4(modelMatrixPC150);
		AbstractModel::OBB PC150Collider;
		PC150Collider.u = glm::quat_cast(modelMatrixPC150);
		modelMatrixColliderPC150[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC150[3][0], modelMatrixColliderPC150[3][2]);
		modelMatrixColliderPC150 = glm::scale(modelMatrixColliderPC150, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC150 = glm::translate(modelMatrixColliderPC150, modelPC150.getObb().c);
		PC150Collider.c = glm::vec3(modelMatrixColliderPC150[3]);
		PC150Collider.e = modelPC150.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC150", PC150Collider, modelMatrixPC150);

		glm::mat4 modelMatrixColliderPC151 = glm::mat4(modelMatrixPC151);
		AbstractModel::OBB PC151Collider;
		PC151Collider.u = glm::quat_cast(modelMatrixPC151);
		modelMatrixColliderPC151[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC151[3][0], modelMatrixColliderPC151[3][2]);
		modelMatrixColliderPC151 = glm::scale(modelMatrixColliderPC151, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC151 = glm::translate(modelMatrixColliderPC151, modelPC151.getObb().c);
		PC151Collider.c = glm::vec3(modelMatrixColliderPC151[3]);
		PC151Collider.e = modelPC151.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC151", PC151Collider, modelMatrixPC151);

		glm::mat4 modelMatrixColliderPC152 = glm::mat4(modelMatrixPC152);
		AbstractModel::OBB PC152Collider;
		PC152Collider.u = glm::quat_cast(modelMatrixPC152);
		modelMatrixColliderPC152[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC152[3][0], modelMatrixColliderPC152[3][2]);
		modelMatrixColliderPC152 = glm::scale(modelMatrixColliderPC152, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC152 = glm::translate(modelMatrixColliderPC152, modelPC152.getObb().c);
		PC152Collider.c = glm::vec3(modelMatrixColliderPC152[3]);
		PC152Collider.e = modelPC152.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC152", PC152Collider, modelMatrixPC152);

		glm::mat4 modelMatrixColliderPC153 = glm::mat4(modelMatrixPC153);
		AbstractModel::OBB PC153Collider;
		PC153Collider.u = glm::quat_cast(modelMatrixPC153);
		modelMatrixColliderPC153[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC153[3][0], modelMatrixColliderPC153[3][2]);
		modelMatrixColliderPC153 = glm::scale(modelMatrixColliderPC153, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC153 = glm::translate(modelMatrixColliderPC153, modelPC153.getObb().c);
		PC153Collider.c = glm::vec3(modelMatrixColliderPC153[3]);
		PC153Collider.e = modelPC153.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC153", PC153Collider, modelMatrixPC153);

		glm::mat4 modelMatrixColliderPC154 = glm::mat4(modelMatrixPC154);
		AbstractModel::OBB PC154Collider;
		PC154Collider.u = glm::quat_cast(modelMatrixPC154);
		modelMatrixColliderPC154[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC154[3][0], modelMatrixColliderPC154[3][2]);
		modelMatrixColliderPC154 = glm::scale(modelMatrixColliderPC154, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC154 = glm::translate(modelMatrixColliderPC154, modelPC154.getObb().c);
		PC154Collider.c = glm::vec3(modelMatrixColliderPC154[3]);
		PC154Collider.e = modelPC154.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC154", PC154Collider, modelMatrixPC154);

		glm::mat4 modelMatrixColliderPC155 = glm::mat4(modelMatrixPC155);
		AbstractModel::OBB PC155Collider;
		PC155Collider.u = glm::quat_cast(modelMatrixPC155);
		modelMatrixColliderPC155[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC155[3][0], modelMatrixColliderPC155[3][2]);
		modelMatrixColliderPC155 = glm::scale(modelMatrixColliderPC155, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC155 = glm::translate(modelMatrixColliderPC155, modelPC155.getObb().c);
		PC155Collider.c = glm::vec3(modelMatrixColliderPC155[3]);
		PC155Collider.e = modelPC155.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC155", PC155Collider, modelMatrixPC155);

		glm::mat4 modelMatrixColliderPC156 = glm::mat4(modelMatrixPC156);
		AbstractModel::OBB PC156Collider;
		PC156Collider.u = glm::quat_cast(modelMatrixPC156);
		modelMatrixColliderPC156[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC156[3][0], modelMatrixColliderPC156[3][2]);
		modelMatrixColliderPC156 = glm::scale(modelMatrixColliderPC156, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC156 = glm::translate(modelMatrixColliderPC156, modelPC156.getObb().c);
		PC156Collider.c = glm::vec3(modelMatrixColliderPC156[3]);
		PC156Collider.e = modelPC156.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC156", PC156Collider, modelMatrixPC156);

		glm::mat4 modelMatrixColliderPC157 = glm::mat4(modelMatrixPC157);
		AbstractModel::OBB PC157Collider;
		PC157Collider.u = glm::quat_cast(modelMatrixPC157);
		modelMatrixColliderPC157[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC157[3][0], modelMatrixColliderPC157[3][2]);
		modelMatrixColliderPC157 = glm::scale(modelMatrixColliderPC157, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC157 = glm::translate(modelMatrixColliderPC157, modelPC157.getObb().c);
		PC157Collider.c = glm::vec3(modelMatrixColliderPC157[3]);
		PC157Collider.e = modelPC157.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC157", PC157Collider, modelMatrixPC157);

		glm::mat4 modelMatrixColliderPC158 = glm::mat4(modelMatrixPC158);
		AbstractModel::OBB PC158Collider;
		PC158Collider.u = glm::quat_cast(modelMatrixPC158);
		modelMatrixColliderPC158[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC158[3][0], modelMatrixColliderPC158[3][2]);
		modelMatrixColliderPC158 = glm::scale(modelMatrixColliderPC158, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC158 = glm::translate(modelMatrixColliderPC158, modelPC158.getObb().c);
		PC158Collider.c = glm::vec3(modelMatrixColliderPC158[3]);
		PC158Collider.e = modelPC158.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC158", PC158Collider, modelMatrixPC158);

		glm::mat4 modelMatrixColliderPC159 = glm::mat4(modelMatrixPC159);
		AbstractModel::OBB PC159Collider;
		PC159Collider.u = glm::quat_cast(modelMatrixPC159);
		modelMatrixColliderPC159[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC159[3][0], modelMatrixColliderPC159[3][2]);
		modelMatrixColliderPC159 = glm::scale(modelMatrixColliderPC159, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC159 = glm::translate(modelMatrixColliderPC159, modelPC159.getObb().c);
		PC159Collider.c = glm::vec3(modelMatrixColliderPC159[3]);
		PC159Collider.e = modelPC159.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC159", PC159Collider, modelMatrixPC159);

		glm::mat4 modelMatrixColliderPC160 = glm::mat4(modelMatrixPC160);
		AbstractModel::OBB PC160Collider;
		PC160Collider.u = glm::quat_cast(modelMatrixPC160);
		modelMatrixColliderPC160[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC160[3][0], modelMatrixColliderPC160[3][2]);
		modelMatrixColliderPC160 = glm::scale(modelMatrixColliderPC160, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC160 = glm::translate(modelMatrixColliderPC160, modelPC160.getObb().c);
		PC160Collider.c = glm::vec3(modelMatrixColliderPC160[3]);
		PC160Collider.e = modelPC160.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC160", PC160Collider, modelMatrixPC160);

		glm::mat4 modelMatrixColliderPC161 = glm::mat4(modelMatrixPC161);
		AbstractModel::OBB PC161Collider;
		PC161Collider.u = glm::quat_cast(modelMatrixPC161);
		modelMatrixColliderPC161[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC161[3][0], modelMatrixColliderPC161[3][2]);
		modelMatrixColliderPC161 = glm::scale(modelMatrixColliderPC161, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC161 = glm::translate(modelMatrixColliderPC161, modelPC161.getObb().c);
		PC161Collider.c = glm::vec3(modelMatrixColliderPC161[3]);
		PC161Collider.e = modelPC161.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC161", PC161Collider, modelMatrixPC161);

		glm::mat4 modelMatrixColliderPC162 = glm::mat4(modelMatrixPC162);
		AbstractModel::OBB PC162Collider;
		PC162Collider.u = glm::quat_cast(modelMatrixPC162);
		modelMatrixColliderPC162[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC162[3][0], modelMatrixColliderPC162[3][2]);
		modelMatrixColliderPC162 = glm::scale(modelMatrixColliderPC162, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC162 = glm::translate(modelMatrixColliderPC162, modelPC162.getObb().c);
		PC162Collider.c = glm::vec3(modelMatrixColliderPC162[3]);
		PC162Collider.e = modelPC162.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC162", PC162Collider, modelMatrixPC162);

		glm::mat4 modelMatrixColliderPC163 = glm::mat4(modelMatrixPC163);
		AbstractModel::OBB PC163Collider;
		PC163Collider.u = glm::quat_cast(modelMatrixPC163);
		modelMatrixColliderPC163[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC163[3][0], modelMatrixColliderPC163[3][2]);
		modelMatrixColliderPC163 = glm::scale(modelMatrixColliderPC163, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC163 = glm::translate(modelMatrixColliderPC163, modelPC163.getObb().c);
		PC163Collider.c = glm::vec3(modelMatrixColliderPC163[3]);
		PC163Collider.e = modelPC163.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC163", PC163Collider, modelMatrixPC163);

		glm::mat4 modelMatrixColliderPC164 = glm::mat4(modelMatrixPC164);
		AbstractModel::OBB PC164Collider;
		PC164Collider.u = glm::quat_cast(modelMatrixPC164);
		modelMatrixColliderPC164[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC164[3][0], modelMatrixColliderPC164[3][2]);
		modelMatrixColliderPC164 = glm::scale(modelMatrixColliderPC164, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC164 = glm::translate(modelMatrixColliderPC164, modelPC164.getObb().c);
		PC164Collider.c = glm::vec3(modelMatrixColliderPC164[3]);
		PC164Collider.e = modelPC164.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC164", PC164Collider, modelMatrixPC164);

		glm::mat4 modelMatrixColliderPC165 = glm::mat4(modelMatrixPC165);
		AbstractModel::OBB PC165Collider;
		PC165Collider.u = glm::quat_cast(modelMatrixPC165);
		modelMatrixColliderPC165[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC165[3][0], modelMatrixColliderPC165[3][2]);
		modelMatrixColliderPC165 = glm::scale(modelMatrixColliderPC165, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC165 = glm::translate(modelMatrixColliderPC165, modelPC165.getObb().c);
		PC165Collider.c = glm::vec3(modelMatrixColliderPC165[3]);
		PC165Collider.e = modelPC165.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC165", PC165Collider, modelMatrixPC165);

		glm::mat4 modelMatrixColliderPC166 = glm::mat4(modelMatrixPC166);
		AbstractModel::OBB PC166Collider;
		PC166Collider.u = glm::quat_cast(modelMatrixPC166);
		modelMatrixColliderPC166[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC166[3][0], modelMatrixColliderPC166[3][2]);
		modelMatrixColliderPC166 = glm::scale(modelMatrixColliderPC166, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC166 = glm::translate(modelMatrixColliderPC166, modelPC166.getObb().c);
		PC166Collider.c = glm::vec3(modelMatrixColliderPC166[3]);
		PC166Collider.e = modelPC166.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC166", PC166Collider, modelMatrixPC166);

		glm::mat4 modelMatrixColliderPC167 = glm::mat4(modelMatrixPC167);
		AbstractModel::OBB PC167Collider;
		PC167Collider.u = glm::quat_cast(modelMatrixPC167);
		modelMatrixColliderPC167[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC167[3][0], modelMatrixColliderPC167[3][2]);
		modelMatrixColliderPC167 = glm::scale(modelMatrixColliderPC167, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC167 = glm::translate(modelMatrixColliderPC167, modelPC167.getObb().c);
		PC167Collider.c = glm::vec3(modelMatrixColliderPC167[3]);
		PC167Collider.e = modelPC167.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC167", PC167Collider, modelMatrixPC167);

		glm::mat4 modelMatrixColliderPC168 = glm::mat4(modelMatrixPC168);
		AbstractModel::OBB PC168Collider;
		PC168Collider.u = glm::quat_cast(modelMatrixPC168);
		modelMatrixColliderPC168[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC168[3][0], modelMatrixColliderPC168[3][2]);
		modelMatrixColliderPC168 = glm::scale(modelMatrixColliderPC168, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC168 = glm::translate(modelMatrixColliderPC168, modelPC168.getObb().c);
		PC168Collider.c = glm::vec3(modelMatrixColliderPC168[3]);
		PC168Collider.e = modelPC168.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC168", PC168Collider, modelMatrixPC168);

		glm::mat4 modelMatrixColliderPC169 = glm::mat4(modelMatrixPC169);
		AbstractModel::OBB PC169Collider;
		PC169Collider.u = glm::quat_cast(modelMatrixPC169);
		modelMatrixColliderPC169[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC169[3][0], modelMatrixColliderPC169[3][2]);
		modelMatrixColliderPC169 = glm::scale(modelMatrixColliderPC169, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC169 = glm::translate(modelMatrixColliderPC169, modelPC169.getObb().c);
		PC169Collider.c = glm::vec3(modelMatrixColliderPC169[3]);
		PC169Collider.e = modelPC169.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC169", PC169Collider, modelMatrixPC169);

		glm::mat4 modelMatrixColliderPC170 = glm::mat4(modelMatrixPC170);
		AbstractModel::OBB PC170Collider;
		PC170Collider.u = glm::quat_cast(modelMatrixPC170);
		modelMatrixColliderPC170[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC170[3][0], modelMatrixColliderPC170[3][2]);
		modelMatrixColliderPC170 = glm::scale(modelMatrixColliderPC170, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC170 = glm::translate(modelMatrixColliderPC170, modelPC170.getObb().c);
		PC170Collider.c = glm::vec3(modelMatrixColliderPC170[3]);
		PC170Collider.e = modelPC170.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC170", PC170Collider, modelMatrixPC170);

		glm::mat4 modelMatrixColliderPC171 = glm::mat4(modelMatrixPC171);
		AbstractModel::OBB PC171Collider;
		PC171Collider.u = glm::quat_cast(modelMatrixPC171);
		modelMatrixColliderPC171[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC171[3][0], modelMatrixColliderPC171[3][2]);
		modelMatrixColliderPC171 = glm::scale(modelMatrixColliderPC171, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC171 = glm::translate(modelMatrixColliderPC171, modelPC171.getObb().c);
		PC171Collider.c = glm::vec3(modelMatrixColliderPC171[3]);
		PC171Collider.e = modelPC171.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC171", PC171Collider, modelMatrixPC171);

		glm::mat4 modelMatrixColliderPC172 = glm::mat4(modelMatrixPC172);
		AbstractModel::OBB PC172Collider;
		PC172Collider.u = glm::quat_cast(modelMatrixPC172);
		modelMatrixColliderPC172[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC172[3][0], modelMatrixColliderPC172[3][2]);
		modelMatrixColliderPC172 = glm::scale(modelMatrixColliderPC172, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC172 = glm::translate(modelMatrixColliderPC172, modelPC172.getObb().c);
		PC172Collider.c = glm::vec3(modelMatrixColliderPC172[3]);
		PC172Collider.e = modelPC172.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC172", PC172Collider, modelMatrixPC172);

		glm::mat4 modelMatrixColliderPC173 = glm::mat4(modelMatrixPC173);
		AbstractModel::OBB PC173Collider;
		PC173Collider.u = glm::quat_cast(modelMatrixPC173);
		modelMatrixColliderPC173[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC173[3][0], modelMatrixColliderPC173[3][2]);
		modelMatrixColliderPC173 = glm::scale(modelMatrixColliderPC173, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC173 = glm::translate(modelMatrixColliderPC173, modelPC173.getObb().c);
		PC173Collider.c = glm::vec3(modelMatrixColliderPC173[3]);
		PC173Collider.e = modelPC173.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC173", PC173Collider, modelMatrixPC173);

		glm::mat4 modelMatrixColliderPC174 = glm::mat4(modelMatrixPC174);
		AbstractModel::OBB PC174Collider;
		PC174Collider.u = glm::quat_cast(modelMatrixPC174);
		modelMatrixColliderPC174[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC174[3][0], modelMatrixColliderPC174[3][2]);
		modelMatrixColliderPC174 = glm::scale(modelMatrixColliderPC174, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC174 = glm::translate(modelMatrixColliderPC174, modelPC174.getObb().c);
		PC174Collider.c = glm::vec3(modelMatrixColliderPC174[3]);
		PC174Collider.e = modelPC174.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC174", PC174Collider, modelMatrixPC174);

		glm::mat4 modelMatrixColliderPC175 = glm::mat4(modelMatrixPC175);
		AbstractModel::OBB PC175Collider;
		PC175Collider.u = glm::quat_cast(modelMatrixPC175);
		modelMatrixColliderPC175[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC175[3][0], modelMatrixColliderPC175[3][2]);
		modelMatrixColliderPC175 = glm::scale(modelMatrixColliderPC175, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC175 = glm::translate(modelMatrixColliderPC175, modelPC175.getObb().c);
		PC175Collider.c = glm::vec3(modelMatrixColliderPC175[3]);
		PC175Collider.e = modelPC175.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC175", PC175Collider, modelMatrixPC175);

		glm::mat4 modelMatrixColliderPC176 = glm::mat4(modelMatrixPC176);
		AbstractModel::OBB PC176Collider;
		PC176Collider.u = glm::quat_cast(modelMatrixPC176);
		modelMatrixColliderPC176[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC176[3][0], modelMatrixColliderPC176[3][2]);
		modelMatrixColliderPC176 = glm::scale(modelMatrixColliderPC176, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC176 = glm::translate(modelMatrixColliderPC176, modelPC176.getObb().c);
		PC176Collider.c = glm::vec3(modelMatrixColliderPC176[3]);
		PC176Collider.e = modelPC176.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC176", PC176Collider, modelMatrixPC176);

		glm::mat4 modelMatrixColliderPC177 = glm::mat4(modelMatrixPC177);
		AbstractModel::OBB PC177Collider;
		PC177Collider.u = glm::quat_cast(modelMatrixPC177);
		modelMatrixColliderPC177[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC177[3][0], modelMatrixColliderPC177[3][2]);
		modelMatrixColliderPC177 = glm::scale(modelMatrixColliderPC177, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC177 = glm::translate(modelMatrixColliderPC177, modelPC177.getObb().c);
		PC177Collider.c = glm::vec3(modelMatrixColliderPC177[3]);
		PC177Collider.e = modelPC177.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC177", PC177Collider, modelMatrixPC177);

		glm::mat4 modelMatrixColliderPC178 = glm::mat4(modelMatrixPC178);
		AbstractModel::OBB PC178Collider;
		PC178Collider.u = glm::quat_cast(modelMatrixPC178);
		modelMatrixColliderPC178[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC178[3][0], modelMatrixColliderPC178[3][2]);
		modelMatrixColliderPC178 = glm::scale(modelMatrixColliderPC178, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC178 = glm::translate(modelMatrixColliderPC178, modelPC178.getObb().c);
		PC178Collider.c = glm::vec3(modelMatrixColliderPC178[3]);
		PC178Collider.e = modelPC178.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC178", PC178Collider, modelMatrixPC178);

		glm::mat4 modelMatrixColliderPC179 = glm::mat4(modelMatrixPC179);
		AbstractModel::OBB PC179Collider;
		PC179Collider.u = glm::quat_cast(modelMatrixPC179);
		modelMatrixColliderPC179[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC179[3][0], modelMatrixColliderPC179[3][2]);
		modelMatrixColliderPC179 = glm::scale(modelMatrixColliderPC179, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC179 = glm::translate(modelMatrixColliderPC179, modelPC179.getObb().c);
		PC179Collider.c = glm::vec3(modelMatrixColliderPC179[3]);
		PC179Collider.e = modelPC179.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC179", PC179Collider, modelMatrixPC179);

		glm::mat4 modelMatrixColliderPC180 = glm::mat4(modelMatrixPC180);
		AbstractModel::OBB PC180Collider;
		PC180Collider.u = glm::quat_cast(modelMatrixPC180);
		modelMatrixColliderPC180[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC180[3][0], modelMatrixColliderPC180[3][2]);
		modelMatrixColliderPC180 = glm::scale(modelMatrixColliderPC180, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC180 = glm::translate(modelMatrixColliderPC180, modelPC180.getObb().c);
		PC180Collider.c = glm::vec3(modelMatrixColliderPC180[3]);
		PC180Collider.e = modelPC180.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC180", PC180Collider, modelMatrixPC180);

		glm::mat4 modelMatrixColliderPC181 = glm::mat4(modelMatrixPC181);
		AbstractModel::OBB PC181Collider;
		PC181Collider.u = glm::quat_cast(modelMatrixPC181);
		modelMatrixColliderPC181[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC181[3][0], modelMatrixColliderPC181[3][2]);
		modelMatrixColliderPC181 = glm::scale(modelMatrixColliderPC181, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC181 = glm::translate(modelMatrixColliderPC181, modelPC181.getObb().c);
		PC181Collider.c = glm::vec3(modelMatrixColliderPC181[3]);
		PC181Collider.e = modelPC181.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC181", PC181Collider, modelMatrixPC181);

		glm::mat4 modelMatrixColliderPC182 = glm::mat4(modelMatrixPC182);
		AbstractModel::OBB PC182Collider;
		PC182Collider.u = glm::quat_cast(modelMatrixPC182);
		modelMatrixColliderPC182[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC182[3][0], modelMatrixColliderPC182[3][2]);
		modelMatrixColliderPC182 = glm::scale(modelMatrixColliderPC182, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC182 = glm::translate(modelMatrixColliderPC182, modelPC182.getObb().c);
		PC182Collider.c = glm::vec3(modelMatrixColliderPC182[3]);
		PC182Collider.e = modelPC182.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC182", PC182Collider, modelMatrixPC182);

		glm::mat4 modelMatrixColliderPC183 = glm::mat4(modelMatrixPC183);
		AbstractModel::OBB PC183Collider;
		PC183Collider.u = glm::quat_cast(modelMatrixPC183);
		modelMatrixColliderPC183[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC183[3][0], modelMatrixColliderPC183[3][2]);
		modelMatrixColliderPC183 = glm::scale(modelMatrixColliderPC183, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC183 = glm::translate(modelMatrixColliderPC183, modelPC183.getObb().c);
		PC183Collider.c = glm::vec3(modelMatrixColliderPC183[3]);
		PC183Collider.e = modelPC183.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC183", PC183Collider, modelMatrixPC183);

		glm::mat4 modelMatrixColliderPC184 = glm::mat4(modelMatrixPC184);
		AbstractModel::OBB PC184Collider;
		PC184Collider.u = glm::quat_cast(modelMatrixPC184);
		modelMatrixColliderPC184[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC184[3][0], modelMatrixColliderPC184[3][2]);
		modelMatrixColliderPC184 = glm::scale(modelMatrixColliderPC184, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC184 = glm::translate(modelMatrixColliderPC184, modelPC184.getObb().c);
		PC184Collider.c = glm::vec3(modelMatrixColliderPC184[3]);
		PC184Collider.e = modelPC184.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC184", PC184Collider, modelMatrixPC184);

		glm::mat4 modelMatrixColliderPC185 = glm::mat4(modelMatrixPC185);
		AbstractModel::OBB PC185Collider;
		PC185Collider.u = glm::quat_cast(modelMatrixPC185);
		modelMatrixColliderPC185[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC185[3][0], modelMatrixColliderPC185[3][2]);
		modelMatrixColliderPC185 = glm::scale(modelMatrixColliderPC185, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC185 = glm::translate(modelMatrixColliderPC185, modelPC185.getObb().c);
		PC185Collider.c = glm::vec3(modelMatrixColliderPC185[3]);
		PC185Collider.e = modelPC185.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC185", PC185Collider, modelMatrixPC185);

		glm::mat4 modelMatrixColliderPC186 = glm::mat4(modelMatrixPC186);
		AbstractModel::OBB PC186Collider;
		PC186Collider.u = glm::quat_cast(modelMatrixPC186);
		modelMatrixColliderPC186[3][1] = terrain.getHeightTerrain(modelMatrixColliderPC186[3][0], modelMatrixColliderPC186[3][2]);
		modelMatrixColliderPC186 = glm::scale(modelMatrixColliderPC186, glm::vec3(0.5, 0.5, 0.5));
		modelMatrixColliderPC186 = glm::translate(modelMatrixColliderPC186, modelPC186.getObb().c);
		PC186Collider.c = glm::vec3(modelMatrixColliderPC186[3]);
		PC186Collider.e = modelPC186.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "PC186", PC186Collider, modelMatrixPC186);

		// Collider de mayow
		AbstractModel::OBB mayowCollider;
		glm::mat4 modelmatrixColliderMayow = glm::mat4(modelMatrixMayow);
		modelmatrixColliderMayow = glm::rotate(modelmatrixColliderMayow,
				glm::radians(-90.0f), glm::vec3(1, 0, 0));
		// Set the orientation of collider before doing the scale
		mayowCollider.u = glm::quat_cast(modelmatrixColliderMayow);
		modelmatrixColliderMayow = glm::scale(modelmatrixColliderMayow, glm::vec3(0.021, 0.021, 0.021));
		modelmatrixColliderMayow = glm::translate(modelmatrixColliderMayow,
				glm::vec3(mayowModelAnimate.getObb().c.x,
						mayowModelAnimate.getObb().c.y,
						mayowModelAnimate.getObb().c.z));
		mayowCollider.e = mayowModelAnimate.getObb().e * glm::vec3(0.021, 0.021, 0.021) * glm::vec3(0.787401574, 0.787401574, 0.787401574);
		mayowCollider.c = glm::vec3(modelmatrixColliderMayow[3]);
		addOrUpdateColliders(collidersOBB, "mayow", mayowCollider, modelMatrixMayow);

		/*******************************************
		 * Render de colliders
		 *******************************************/
		/*for (std::map<std::string, std::tuple<AbstractModel::OBB, glm::mat4, glm::mat4> >::iterator it =
				collidersOBB.begin(); it != collidersOBB.end(); it++) {
			glm::mat4 matrixCollider = glm::mat4(1.0);
			matrixCollider = glm::translate(matrixCollider, std::get<0>(it->second).c);
			matrixCollider = matrixCollider * glm::mat4(std::get<0>(it->second).u);
			matrixCollider = glm::scale(matrixCollider, std::get<0>(it->second).e * 2.0f);
			boxCollider.setColor(glm::vec4(1.0, 1.0, 1.0, 1.0));
			boxCollider.enableWireMode();
			boxCollider.render(matrixCollider);
		}

		for (std::map<std::string, std::tuple<AbstractModel::SBB, glm::mat4, glm::mat4> >::iterator it =
				collidersSBB.begin(); it != collidersSBB.end(); it++) {
			glm::mat4 matrixCollider = glm::mat4(1.0);
			matrixCollider = glm::translate(matrixCollider, std::get<0>(it->second).c);
			matrixCollider = glm::scale(matrixCollider, glm::vec3(std::get<0>(it->second).ratio * 2.0f));
			sphereCollider.setColor(glm::vec4(1.0, 1.0, 1.0, 1.0));
			sphereCollider.enableWireMode();
			sphereCollider.render(matrixCollider);
		}*/

		// Esto es para ilustrar la transformacion inversa de los coliders
		/*glm::vec3 cinv = glm::inverse(mayowCollider.u) * glm::vec4(rockCollider.c, 1.0);
		glm::mat4 invColliderS = glm::mat4(1.0);
		invColliderS = glm::translate(invColliderS, cinv);
		invColliderS =  invColliderS * glm::mat4(mayowCollider.u);
		invColliderS = glm::scale(invColliderS, glm::vec3(rockCollider.ratio * 2.0, rockCollider.ratio * 2.0, rockCollider.ratio * 2.0));
		sphereCollider.setColor(glm::vec4(1.0, 1.0, 0.0, 1.0));
		sphereCollider.enableWireMode();
		sphereCollider.render(invColliderS);
		glm::vec3 cinv2 = glm::inverse(mayowCollider.u) * glm::vec4(mayowCollider.c, 1.0);
		glm::mat4 invColliderB = glm::mat4(1.0);
		invColliderB = glm::translate(invColliderB, cinv2);
		invColliderB = glm::scale(invColliderB, mayowCollider.e * 2.0f);
		boxCollider.setColor(glm::vec4(1.0, 1.0, 0.0, 1.0));
		boxCollider.enableWireMode();
		boxCollider.render(invColliderB);
		// Se regresa el color blanco
		sphereCollider.setColor(glm::vec4(1.0, 1.0, 1.0, 1.0));
		boxCollider.setColor(glm::vec4(1.0, 1.0, 1.0, 1.0));*/

		/*******************************************
		 * Test Colisions
		 *******************************************/
		for (std::map<std::string,
				std::tuple<AbstractModel::OBB, glm::mat4, glm::mat4> >::iterator it =
				collidersOBB.begin(); it != collidersOBB.end(); it++) {
			bool isCollision = false;
			for (std::map<std::string,
					std::tuple<AbstractModel::OBB, glm::mat4, glm::mat4> >::iterator jt =
					collidersOBB.begin(); jt != collidersOBB.end(); jt++) {
				if (it != jt
						&& testOBBOBB(std::get<0>(it->second),
								std::get<0>(jt->second))) {
					std::cout << "Colision " << it->first << " with "
							<< jt->first << std::endl;
					isCollision = true;
				}
			}
			addOrUpdateCollisionDetection(collisionDetection, it->first, isCollision);
		}

		for (std::map<std::string,
				std::tuple<AbstractModel::SBB, glm::mat4, glm::mat4> >::iterator it =
				collidersSBB.begin(); it != collidersSBB.end(); it++) {
			bool isCollision = false;
			for (std::map<std::string,
					std::tuple<AbstractModel::SBB, glm::mat4, glm::mat4> >::iterator jt =
					collidersSBB.begin(); jt != collidersSBB.end(); jt++) {
				if (it != jt
						&& testSphereSphereIntersection(std::get<0>(it->second),
								std::get<0>(jt->second))) {
					std::cout << "Colision " << it->first << " with "
							<< jt->first << std::endl;
					isCollision = true;
				}
			}
			addOrUpdateCollisionDetection(collisionDetection, it->first, isCollision);
		}

		for (std::map<std::string,
				std::tuple<AbstractModel::SBB, glm::mat4, glm::mat4> >::iterator it =
				collidersSBB.begin(); it != collidersSBB.end(); it++) {
			bool isCollision = false;
			std::map<std::string,
					std::tuple<AbstractModel::OBB, glm::mat4, glm::mat4> >::iterator jt =
					collidersOBB.begin();
			for (; jt != collidersOBB.end(); jt++) {
				if (testSphereOBox(std::get<0>(it->second),
								std::get<0>(jt->second))) {
					std::cout << "Colision " << it->first << " with "
							<< jt->first << std::endl;
					isCollision = true;
					addOrUpdateCollisionDetection(collisionDetection, jt->first, isCollision);
				}
			}
			addOrUpdateCollisionDetection(collisionDetection, it->first, isCollision);
		}

		std::map<std::string, bool>::iterator colIt;
		for (colIt = collisionDetection.begin(); colIt != collisionDetection.end();
				colIt++) {
			std::map<std::string,
					std::tuple<AbstractModel::SBB, glm::mat4, glm::mat4> >::iterator it =
					collidersSBB.find(colIt->first);
			std::map<std::string,
					std::tuple<AbstractModel::OBB, glm::mat4, glm::mat4> >::iterator jt =
					collidersOBB.find(colIt->first);
			if (it != collidersSBB.end()) {
				if (!colIt->second)
					addOrUpdateColliders(collidersSBB, it->first);
			}
			if (jt != collidersOBB.end()) {
				if (!colIt->second)
					addOrUpdateColliders(collidersOBB, jt->first);
				else {
					if (jt->first.compare("mayow") == 0)
						modelMatrixMayow = std::get<1>(jt->second);
				}
			}
		}

		/*******************************************
		 * Interpolation key frames with disconect objects
		 *******************************************/

		// Constantes de animaciones

		/*******************************************
		 * State machines
		 *******************************************/

		glfwSwapBuffers(window);

		/****************************+
		 * Open AL sound data
		 */

		// Listener for the Thris person camera
		listenerPos[0] = modelMatrixMayow[3].x;
		listenerPos[1] = modelMatrixMayow[3].y;
		listenerPos[2] = modelMatrixMayow[3].z;
		alListenerfv(AL_POSITION, listenerPos);

		glm::vec3 upModel = glm::normalize(modelMatrixMayow[1]);
		glm::vec3 frontModel = glm::normalize(modelMatrixMayow[2]);

		listenerOri[0] = frontModel.x;
		listenerOri[1] = frontModel.y;
		listenerOri[2] = frontModel.z;
		listenerOri[3] = upModel.x;
		listenerOri[4] = upModel.y;
		listenerOri[5] = upModel.z;

		// Listener for the First person camera
		/*listenerPos[0] = camera->getPosition().x;
		listenerPos[1] = camera->getPosition().y;
		listenerPos[2] = camera->getPosition().z;
		alListenerfv(AL_POSITION, listenerPos);
		listenerOri[0] = camera->getFront().x;
		listenerOri[1] = camera->getFront().y;
		listenerOri[2] = camera->getFront().z;
		listenerOri[3] = camera->getUp().x;
		listenerOri[4] = camera->getUp().y;
		listenerOri[5] = camera->getUp().z;*/
		alListenerfv(AL_ORIENTATION, listenerOri);

		for(unsigned int i = 0; i < sourcesPlay.size(); i++){
			if(sourcesPlay[i]){
				sourcesPlay[i] = false;
				alSourcePlay(source[i]);
			}
		}
	}
}

void prepareScene(){

	skyboxSphere.setShader(&shaderSkybox);

	terrain.setShader(&shaderTerrain);

	//Mayow
	mayowModelAnimate.setShader(&shaderMulLighting);
}

void prepareDepthScene(){

	skyboxSphere.setShader(&shaderDepth);

	terrain.setShader(&shaderDepth);

	//Mayow
	mayowModelAnimate.setShader(&shaderDepth);
}

void renderScene(bool renderParticles){
	/*******************************************
	 * Terrain Cesped
	 *******************************************/
	glm::mat4 modelCesped = glm::mat4(1.0);
	modelCesped = glm::translate(modelCesped, glm::vec3(0.0, 0.0, 0.0));
	modelCesped = glm::scale(modelCesped, glm::vec3(200.0, 0.001, 200.0));
	// Se activa la textura del background
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureTerrainBackgroundID);
	shaderTerrain.setInt("backgroundTexture", 0);
	// Se activa la textura de tierra
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, textureTerrainRID);
	shaderTerrain.setInt("rTexture", 1);
	// Se activa la textura de hierba
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, textureTerrainGID);
	shaderTerrain.setInt("gTexture", 2);
	// Se activa la textura del camino
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, textureTerrainBID);
	shaderTerrain.setInt("bTexture", 3);
	// Se activa la textura del blend map
	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_2D, textureTerrainBlendMapID);
	shaderTerrain.setInt("blendMapTexture", 4);
	shaderTerrain.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(40, 40)));
	terrain.render();
	shaderTerrain.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(0, 0)));
	glBindTexture(GL_TEXTURE_2D, 0);

	/*******************************************
	 * Custom objects obj
	 *******************************************/

	// Se regresa el cull faces IMPORTANTE para la capa
	glEnable(GL_CULL_FACE);

	/*******************************************
	 * Custom Anim objects obj
	 *******************************************/
	modelMatrixMayow[3][1] = terrain.getHeightTerrain(modelMatrixMayow[3][0], modelMatrixMayow[3][2]);
	glm::mat4 modelMatrixMayowBody = glm::mat4(modelMatrixMayow);
	modelMatrixMayowBody = glm::scale(modelMatrixMayowBody, glm::vec3(0.021, 0.021, 0.021));
	mayowModelAnimate.setAnimationIndex(animationIndex);
	mayowModelAnimate.render(modelMatrixMayowBody);

	/**********
	 * Update the position with alpha objects
	 */

	/**********
	 * Sorter with alpha objects
	 */
	std::map<float, std::pair<std::string, glm::vec3>> blendingSorted;
	std::map<std::string, glm::vec3>::iterator itblend;
	for(itblend = blendingUnsorted.begin(); itblend != blendingUnsorted.end(); itblend++){
		float distanceFromView = glm::length(camera->getPosition() - itblend->second);
		blendingSorted[distanceFromView] = std::make_pair(itblend->first, itblend->second);
	}

	/**********
	 * Render de las transparencias
	 */
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_CULL_FACE);
	for(std::map<float, std::pair<std::string, glm::vec3> >::reverse_iterator it = blendingSorted.rbegin(); it != blendingSorted.rend(); it++){
		

			/****************************+
			 * Open AL sound data
			 */

			/**********
			 * End Render particles systems
			 */
	}
	glEnable(GL_CULL_FACE);
}

int main(int argc, char **argv) {
	init(800, 700, "Window GLFW", false);
	applicationLoop();
	destroy();
	return 1;
}
