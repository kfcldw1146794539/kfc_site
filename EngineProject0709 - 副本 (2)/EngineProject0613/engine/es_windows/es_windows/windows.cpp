#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <GLES2/gl2.h>
#include <glm/glm.hpp>
#include<Windows.h>
#include <module.h>
#include <render.h>
#include <iostream>
#define GL_MULTISAMPLE                                 0x809D

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_move_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);	
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void processInput(GLFWwindow *window);

bool Init(GLFWwindow* window, RenderHelper* p_helper);
void Draw(GLFWwindow* window, Module * a);
void Update(GLFWwindow* window, Module * a);
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

// settings
const unsigned int SCR_WIDTH = 1280;
const unsigned int SCR_HEIGHT = 800;

float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = NULL;
bool button_state = false;
// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

//float xoffset = 0.0;
//float yoffset = 0.0;

RenderHelper* r_helper = NULL;
Module * a = NULL;





typedef Module*(_stdcall *CM)();
typedef RenderHelper*(_stdcall *CR)();
int main()
{
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES,16);
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

														 // glfw window creation
														 // --------------------
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "model_es", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	
    glfwSetCursorPosCallback(window, mouse_move_callback);
	
	glfwSetMouseButtonCallback(window,mouse_button_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetKeyCallback(window, key_callback);
	
	
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLES2Loader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_MULTISAMPLE);

	
	HMODULE hActive = LoadLibrary("model_dll.dll");

	if (hActive == NULL)
	{
		cout << "dll disappear " << endl;
		
	}

	CM creat_model = (CM)GetProcAddress(hActive, "create_model");
	CR create_render_helper = (CR)GetProcAddress(hActive, "create_render_help");
	


	if (create_render_helper)
	{
		//r_helper = create_render_helper();
		r_helper = new RenderHelper();

	}
	if (!Init(window, r_helper))
		return 0;
	if (creat_model)
	{
		a = creat_model();
		a->CreateEngine(r_helper);
		a->InitEngnie("config.json");
		
	}
	
	//a->PlayAnimation("ani_test");

	//a->PlayAnimation("bonnet_move");
	


	// render loop
	// -----------
	while (!glfwWindowShouldClose(window))
	{
		// per-frame time logic
		// --------------------
		float currentFrame = glfwGetTime();
		
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		//printf("%f\n", deltaTime);
		// input
		// -----
		processInput(window);

		// render
		// ------
		Draw(window,a);
		Update(window, a);
		
		
		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
	return 0;
}

void Draw(GLFWwindow* window, Module * a)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
	
	a->RenderEngine();
	

}

void Update(GLFWwindow* window, Module * a)
{
	

	a->UpdeteEngin(deltaTime);
}

bool  Init(GLFWwindow* window, RenderHelper* p_helper)
{

	p_helper->m_s_helper->c_s_func = &create_shader;
	p_helper->m_s_helper->g_vs_u_func = &get_vs_shader_UniformPos_func;
	p_helper->m_s_helper->s_s_bool_func = &setBool;      
	p_helper->m_s_helper->s_s_int_func = &setInt;
	p_helper->m_s_helper->s_s_float_func = &setFloat;
	p_helper->m_s_helper->s_s_vec2_func = &setVec2;
	p_helper->m_s_helper->s_s_vec2_func2 = &setVec2_2;
	p_helper->m_s_helper->s_s_vec3_func = &setVec3;
	p_helper->m_s_helper->s_s_vec3_func2 = &setVec3_2;
	p_helper->m_s_helper->s_s_vec4_func = &setVec4;
	p_helper->m_s_helper->s_s_vec4_func2 = &setVec4_2;
	p_helper->m_s_helper->s_s_mat2_func = &setMat2;
	p_helper->m_s_helper->s_s_mat3_func = &setMat3;
	p_helper->m_s_helper->s_s_mat4_func = &setMat4;
	p_helper->m_s_helper->u_s_func = &use;


	p_helper->m_t_helper->a_t_func = &active_texture;
	p_helper->m_t_helper->b_g_t_func = &bind_gpu_texture;
	p_helper->m_t_helper->g_f_u_p_func = &get_fs_uniform_pos;
	p_helper->m_t_helper->g_g_t_func = &gen_gpu_texture;
	p_helper->m_t_helper->l_f_u_func = &link_fs_uniform;
	p_helper->m_t_helper->loadCubemap = &loadCubemap;
	p_helper->m_t_helper->bind_gpu_cube_texture = &bind_gpu_cube_texture;



	p_helper->m_p_helper->b_p_b_func = &bind_pont_vboebobuf;
	p_helper->m_p_helper->b_b_p_v_func = &bind_bound_point_vbobuf;
	p_helper->m_p_helper->g_b_p_p_func = &gen_bound_point_buf;
	p_helper->m_p_helper->g_p_b_func = &gen_point_buf;
	p_helper->m_p_helper->g_p_p_func = &get_point_property;
	p_helper->m_p_helper->p_p_p_func = &push_point_property;
	p_helper->m_p_helper->skybox_vbo = &skybox_vbo;


	p_helper->m_d_helper->d_e_func = &draw_element;
	p_helper->m_d_helper->draw_bound_func = &draw_bound;
	p_helper->m_d_helper->d_a_func = &draw_array;
	p_helper->m_d_helper->depthFunc_LEQUAL = &depthFunc_LEQUAL;
	p_helper->m_d_helper->depthFunc_LESS = &depthFunc_LESS;
	p_helper->set_glabal();
	return true;
}


// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	char* dirction = "";
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		dirction = "FORWARD";
		a->updatakeyborad(dirction, deltaTime);\
			cout  << dirction << endl;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		dirction = "BACKWARD";
	    a->updatakeyborad(dirction, deltaTime);
		cout << "keyPressed" << dirction << endl;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		dirction = "LEFT";
		a->updatakeyborad(dirction, deltaTime);
		cout << "keyPressed" << dirction << endl;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		dirction = "RIGHT";
		a->updatakeyborad(dirction, deltaTime);
		cout << "keyPressed" << dirction << endl;
	}
	
}

void mouse_move_callback(GLFWwindow* window, double xpos, double ypos)
{
	//printf("xpos=%f  ypos =%f  \n", xpos, ypos);
	//scroll
	if (button_state)
	{
		if (firstMouse)
		{
			lastX = xpos;
			lastY = ypos;
			firstMouse = false;
		}


		float xoffset = xpos-lastX  ;
		float yoffset =  lastY-ypos; // reversed since y-coordinates go from bottom to top

		
		lastX = xpos;
		lastY = ypos;
	
		//printf("xoffset=%lf  yoffset =%lf  \n", xoffset, yoffset);
		//printf("xoffset=%lf  yoffset =%lf  \n", xoffset, yoffset);
		
		a->updatamousemovement(xoffset, yoffset);
		
		//camera.ProcessMouseMovement(xoffset, yoffset);
	}
	else {
		lastX = xpos;
		lastY = ypos;
		//glm::vec2 mouse_pos=glm::vec2(xpos, ypos);
		
	     }
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (action == GLFW_HAT_LEFT_UP)switch (button)
	{
		case GLFW_MOUSE_BUTTON_LEFT:
			int a = 1;
			printf("MOUSE_BUTTON_LEFT UP\n");

	}
	if (action == GLFW_PRESS) switch (button)
	{
	case GLFW_MOUSE_BUTTON_LEFT:
		button_state = true;
		printf("MOUSE_BUTTON_LEFT PRESS\n");
		break;

	default:
		return;
	}

	else if (action == GLFW_RELEASE) switch (button)
	{
	case GLFW_MOUSE_BUTTON_LEFT:
		button_state = false;
		a->dispatchmsg(lastX, lastY);
		printf("MOUSE_BUTTON_LEFT RELEASE\n");
		break;

	default:
		return;
	}
	//if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS);
	return;
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	//printf("xoffset=%lf  yoffset =%lf  \n", xoffset, yoffset);
	a->updataMouseScroll( yoffset);
	//camera.ProcessMouseScroll(yoffset);
}
// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	
	if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS)
	{
		
		a->PlayAnimation("ani_wheel_turn");
		
	}
	if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
	{

		a->PlayAnimation("ani_wheel_run");

	}
	if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
	{

		a->PlayAnimation("l_door_turn");

	}
	if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
	{

		a->PlayAnimation("r_door_turn");

	}
	if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
	{

	//	a->PlayAnimation("back_skylight_turn");

	}
	
	if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS)
	{

		a->PlayAnimation("all_wheel_run");

	}
	if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS)
	{

		a->PlayAnimation("front_wheel_turn");

	}
	if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
	{

		a->PlayAnimation("left_back_door_move");
		a->PlayAnimation("left_back_door_move1"); 

	}
	if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
	{

		a->PlayAnimation("right_back_door_move");
		a->PlayAnimation("right_back_door_move1");

	}
	if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS)
	{

		//a->PlayAnimation("front_skyligt_move");	
		//a->PlayAnimation("front_skyligt_up");
	}
	if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS)
	{

		//a->PlayAnimation("back_skyligt_move");
		//a->PlayAnimation("back_skyligt_up");
	}
}




