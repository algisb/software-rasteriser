#ifndef OBJ2_H
#define OBJ2_H
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <glm.hpp> 
#define COORD_SIZE 100
typedef float vType;


using namespace std;

struct face
{
	bool quad = false;
	vector<int> fV;
	vector<int> fVT;
	vector<int> fVN;

};
class Obj2
{
private:
	char * file;
	

	void loadV();
	void printV();

	void loadVT();
	void printVT();

	void loadVN();
	void printVN();

	void loadF();
	void printF();

	int numberGaps(string l);


	
	
	
public:
	bool v;
	bool vt;
	bool vn;

	vector<vType> V;
	vector<vType> VT;
	vector<vType> VN;

	vector<face> F;

	vector<vType> VRTE;
	vector<vType> VTRTE;
	vector<vType> VNRTE;
	
	vector<vType> TRTE; //tangent ready to eat
	vector<vType> BTRTE; //bit tangent ready to eat

	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;

	std::vector<glm::vec3> tangents;
	std::vector<glm::vec3> bitangents;

	//=======================================
	Obj2(char * fileName);
	~Obj2();
	
	
	void loadAll();
	void printAll();

	void convertVertexRTE();
	void printVertexRTE();

	void convertVertexTextureRTE();
	void printVertexTextureRTE();

	void convertVertexNormalRTE();
	void printVertexNormalRTE();

	void convertoObjToGlm();
	void computeTangentBasis();

};



#endif