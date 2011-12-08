// mesh.h: interface for the mesh class.
//
// http://cggmwww.csie.nctu.edu.tw/courses/cgu/2002/prog1.htm
//
// Jung Hong Chuang
//
//////////////////////////////////////////////////////////////////////

#ifndef _OBJ_MESH_H_
#define _OBJ_MESH_H_

#include <stdio.h>
#include <stdlib.h>
#include <map>
#include <vector>
#include <string>

//#ifdef WIN32
//#pragma warning(disable: 4786)
//#endif

using namespace std;


class Vertex    
{
private:
  int v;    // vertex (index of vList)
  int n;    // normal (index of nList)
  int t;    // texture (index of tList)
  int m;    // material (index of material)

public:
  int getVertexIndex() { return v;}
  int getNormalIndex() { return n; }
  int getTextureIndex() { return t; }
  int getMaterialIndex() { return m; }

  void setVertexIndex(int newV) { v = newV; }
  void setNormalIndex(int newN) { n = newN; }
  void setTextureIndex(int newT) { t = newT; }
  void setMaterialIndex(int newM) { m = newM; }

  Vertex() {};
  Vertex(int v_index, int n_index, int t_index=0, int m_index=0)
  {
    v = v_index;
    n = n_index;
    t = t_index;
    m = m_index;
  }
};

class Vec3
{
private:
  float ptr[3];
public:
  Vec3 (float *v) 
  {
    for (int i=0;i<3;i++)
      ptr[i] = v[i];
  }
  float& operator[](int index)
  {
    return ptr[index];
  }
};

class Face    
{
private:
  Vertex v[3]; // 3 vertices for each face
public:
  Face (Vertex &v1, Vertex &v2, Vertex &v3) 
  {
    v[0] = v1; 
    v[1] = v2;
    v[2] = v3;
  }
  Vertex& operator[](int index)
  {
    return v[index];
  }
};


class Material
{
public: // public fields - ewww..
  float Ka[4];
  float Kd[4];
  float Ks[4];
  float Ns; // shininess
  char texture_filename[512];

public:
  
  Material()
  { 
    for (int i=0;i<4;i++)
      Ka[i] = Kd[i] = Ks[i] = 1;
    Ns = 0;
    texture_filename[0] = '\0';
  }
};

class Mesh  
{
private:
  map<string,int> matMap;   // matMap[material_name] = material_ID
  FILE  *scenef, *materialf;
  string  s_file, m_file;
  char  mat_file[50];   // material file name

  int   matTotal; // total material 
  vector<Vec3> vList;    // Vertex List (Position) - world cord.
  vector<Vec3> nList;    // Normal List
  vector<Vec3> tList;    // Texture List
  vector<Face> fList; // Face List
  int vTotal, tTotal, nTotal, fTotal;
  Material  mat[100]; // material ID 

public:
  Material *getMaterial() { return mat; }
  int getVTotal() { return vTotal; }
  int getTTotal() { return tTotal; }
  int getNTotal() { return nTotal; }
  int getFTotal() { return fTotal; }

  vector<Vec3>& getVList() { return vList; }
  vector<Vec3>& getNList() { return nList; }
  vector<Vec3>& getTList() { return tList; }
  vector<Face>& getFList() { return fList; }

  /////////////////////////////////////////////////////////////////////////////
  // Methods for loading OBJ files
  /////////////////////////////////////////////////////////////////////////////

  void loadMesh(string scene_file);
  void loadMat(string mat_file);

  Mesh();
  Mesh(const char* obj_file);
  virtual ~Mesh();

  void init(const char* obj_file);
};

#endif
