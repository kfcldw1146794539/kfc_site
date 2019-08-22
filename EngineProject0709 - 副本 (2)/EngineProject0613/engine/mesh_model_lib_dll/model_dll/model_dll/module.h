#pragma once
using namespace std;
#include<string>
#include<vector>
#include <glm/glm.hpp>
#include"MakeDll.h"

//class Render;


struct Vertex {
	// position
	glm::vec3 Position;
	// normal
	glm::vec3 Normal;
	// texCoords
	glm::vec2 TexCoords;
	// tangent
	glm::vec3 Tangent;
	// bitangent
	glm::vec3 Bitangent;
};

struct Texture {
	unsigned int id;
	string type;
	string path;
};


typedef unsigned int (*Create_shader_func)(const char* vs,const char* fs);
//typedef unsigned int(*Create_shader_func)(const char* vs, const char* fs);
typedef void(*Use_shader_func)(unsigned int id);
typedef void(*Set_shader_bool_func)(unsigned int ID,const std::string &name, bool value);
typedef void(*Set_shader_int_func)(unsigned int ID,const std::string &name, int value);
typedef void(*Set_shader_float_func)(unsigned int ID,const std::string &name, float value);
typedef void(*Set_shader_vec2_func)(unsigned int ID, const std::string &name, float x, float y);
typedef void(*Set_shader_vec2_func2)(unsigned int ID, const std::string &name, const glm::vec2 &value);
typedef void(*Set_shader_vec3_func)(unsigned int ID, const std::string &name, float x, float y, float z);
typedef void(*Set_shader_vec3_func2)(unsigned int ID, const std::string &name, const glm::vec3 &value);
typedef void(*Set_shader_vec4_func)(unsigned int ID, const std::string &name, float x, float y, float z, float w);
typedef void(*Set_shader_vec4_func2)(unsigned int ID, const std::string &name, const glm::vec4 &value);
typedef void(*Set_shader_mat2_func)(unsigned int ID, const std::string &name, const glm::mat2 &mat);
typedef void(*Set_shader_mat3_func)(unsigned int ID, const std::string &name, const glm::mat3 &mat);
typedef void(*Set_shader_mat4_func)(unsigned int ID, const std::string &name, const glm::mat4 &mat);
typedef int(*Get_vs_shader_UniformPos_func)(unsigned int id, const char* name);

typedef struct 
{
	Create_shader_func c_s_func;
	Use_shader_func u_s_func;
	Set_shader_bool_func s_s_bool_func;
	Set_shader_int_func s_s_int_func;
	Set_shader_float_func s_s_float_func;
	Set_shader_vec2_func s_s_vec2_func;
	Set_shader_vec2_func2 s_s_vec2_func2;
	Set_shader_vec3_func s_s_vec3_func;
	Set_shader_vec3_func2 s_s_vec3_func2;
	Set_shader_vec4_func s_s_vec4_func;
	Set_shader_vec4_func2 s_s_vec4_func2;
	Set_shader_mat2_func s_s_mat2_func;
	Set_shader_mat3_func s_s_mat3_func;
	Set_shader_mat4_func s_s_mat4_func;
	Get_vs_shader_UniformPos_func g_vs_u_func;
} shader_helper;

static shader_helper* s_helper;



typedef unsigned int(*Gen_gpu_texture)(unsigned char *data, int width, int height ,int nrComponents);
typedef  int(*Bind_gpu_texture)(int textureId);
typedef  int(*Bind_gpu_cubetexture)(int textureId);
typedef  int(*Get_fs_uniform_pos)(int shaderId,const char* name);
typedef  int(*Link_fs_uniform)(int pos, int x);
typedef  int(*Active_texture)(int i);
typedef  unsigned int(*LoadCubemap)(vector<std::string> faces);


typedef struct {
	Gen_gpu_texture g_g_t_func;
	Bind_gpu_texture b_g_t_func;
	Bind_gpu_cubetexture bind_gpu_cube_texture;
	Get_fs_uniform_pos g_f_u_p_func;
	Link_fs_uniform l_f_u_func;
	Active_texture a_t_func;
	LoadCubemap loadCubemap;
}texture_helper;
static texture_helper* t_helper;




typedef int (*Get_point_property)(unsigned int id, const char* name);
typedef void (*Gen_point_buf)(unsigned int &VBOid, unsigned int &EBOid, vector<Vertex>& vectex, vector<unsigned short>& indices);
typedef void(*Gen_bound_point_buf)(unsigned int &VBOid, unsigned int &EBOid, vector<Vertex>& vertices, vector<unsigned short>& indices);
typedef void(*Bind_point_vboebobuf)(unsigned int VBOid, unsigned int EBOid);
typedef void(*Bind_bound_point_vbobuf)(unsigned int VBOid, unsigned int EBOid);

typedef void(*Push_point_property)(int pos,int size,int stride,const void*ptr);
typedef void(*Skybox_vbo)(unsigned int &VBOid, float *skyboxVertices);

typedef struct {
	Get_point_property g_p_p_func;
	Gen_bound_point_buf g_b_p_p_func;
	Gen_point_buf g_p_b_func;
	Bind_point_vboebobuf b_p_b_func;
	Bind_bound_point_vbobuf b_b_p_v_func;
	Push_point_property p_p_p_func;
	Skybox_vbo skybox_vbo;

}point_helper;
static point_helper* p_helper;
typedef void(*Draw_Bound)(int indices_size);
typedef void(*Draw_element)(int indices_size);
typedef void(*Draw_array)(int size);
typedef void(*DepthFunc_LEQUAL)();
typedef void(*DepthFunc_LESS)();

typedef struct
{
	Draw_Bound draw_bound_func;
	Draw_element d_e_func;
	Draw_array d_a_func;
	DepthFunc_LEQUAL depthFunc_LEQUAL;
	DepthFunc_LESS depthFunc_LESS;
}draw_helper;
static draw_helper* d_helper;


class RenderHelper 
{
public :
	RenderHelper()
	{
		init();
	};
	~RenderHelper()
	{
		free();
	};
	void init() 
	{
		m_s_helper = new shader_helper;
		m_t_helper = new texture_helper;
		m_p_helper = new point_helper;
		m_d_helper = new draw_helper;
	}
	void set_glabal()
	{
		s_helper = m_s_helper ;
		t_helper = m_t_helper ;
		p_helper = m_p_helper ;
		d_helper = m_d_helper ;
	}
	void free() 
	{
		s_helper = NULL;
		t_helper = NULL;
		p_helper = NULL;
		d_helper = NULL;
		delete m_s_helper;
		delete m_t_helper;
		delete m_p_helper;
		delete m_d_helper;
	};

	shader_helper* m_s_helper;
	texture_helper* m_t_helper;
	point_helper* m_p_helper;
	draw_helper* m_d_helper;
private:
	

};


class DLL_API Module
{
public :
	//---------��ʼ�� 
	


		//----------

	virtual bool CreateEngine(RenderHelper * m_r_helper) = 0;
	virtual bool InitEngnie(const char* config) = 0;
	virtual void UpdeteEngin(float delta_time) = 0;

	virtual void updatakeyborad(char * direction, float deltaTime) = 0;
	virtual void updatamousemovement(float xoffset, float yoffset) = 0;
	virtual void updataMouseScroll(float yoffset) = 0;

	virtual void RenderEngine() = 0;

	virtual void Release() = 0;
	virtual void set_r_helper(RenderHelper* r_helper) = 0;

	virtual void PlayAnimation(const char* name) = 0;
	virtual bool dispatchmsg(double xpos, double ypos) = 0;
	//virtual void RightDoorOpen() = 0;
	//virtual void WheelRun() = 0;
	//virtual void WheelTurnRight() = 0;
	//virtual void WheelTurnLeft() = 0;

	/*

	virtual bool Load(const char* model, const char* vs_shader_byte_path, const char* fs_shader_byte_path)=0;
	virtual void Draw()=0;
	//virtual void use_shader(int id) = 0;

	//virtual void Set_shader(Shader * shader) = 0;
	virtual int Get_shader_id()=0;

	

	virtual void use_shader(int id) = 0;

	virtual void setBool(const std::string &name, bool value) = 0;

	// ------------------------------------------------------------------------
	virtual void setInt(const std::string &name, int value) = 0;

	// ------------------------------------------------------------------------
	virtual void setFloat(const std::string &name, float value) = 0;

	// ------------------------------------------------------------------------
	virtual void setVec2(const std::string &name, const glm::vec2 &value) = 0;

	virtual void setVec2(const std::string &name, float x, float y) = 0;

	// ------------------------------------------------------------------------
	virtual void setVec3(const std::string &name, const glm::vec3 &value) = 0;

	virtual void setVec3(const std::string &name, float x, float y, float z) = 0;

	// ------------------------------------------------------------------------
	virtual void setVec4(const std::string &name, const glm::vec4 &value) = 0;

	virtual void setVec4(const std::string &name, float x, float y, float z, float w) = 0;

	// ------------------------------------------------------------------------
	virtual void setMat2(const std::string &name, const glm::mat2 &mat) = 0;

	// ------------------------------------------------------------------------
	virtual void setMat3(const std::string &name, const glm::mat3 &mat) = 0;

	// ------------------------------------------------------------------------
	virtual void setMat4(const std::string &name, const glm::mat4 &mat) = 0;

	virtual void set_r_helper(RenderHelper* r_helper) = 0;
	*/
protected:

	RenderHelper * m_r_helper;
	
private :
	
	
	
};




