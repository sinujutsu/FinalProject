// mesh.cpp: implementation of the mesh class.
//
// http://cggmwww.csie.nctu.edu.tw/courses/cgu/2002/prog1.htm
//
// Jung Hong Chuang
//
// Last updated by dakers on September 30, 2010
//
//////////////////////////////////////////////////////////////////////

#include "mesh.h"
#include <string.h>
#include <iostream>

//#ifdef WIN32
//#pragma warning(disable: 4786)
//#endif

const char* obj_database = "";  

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Mesh::Mesh(const char* obj_file)
{
  matTotal = 0;   // mat[0] reserved for default material
  vTotal = tTotal = nTotal = fTotal = 0;
  
  init(obj_file);
}

Mesh::Mesh()
{
  matTotal = 0;     
  vTotal = tTotal = nTotal = fTotal = 0;
}

Mesh::~Mesh()
{
}

void Mesh::loadMesh(string obj_file)
{
  char  token[100], buf[100], v[5][100];  // v[5] 
  float vec[3];

  int i;
  int n_vertex, n_texture, n_normal;
  int cur_mat = 0;        // state variable: material

  scenef = fopen(obj_file.c_str(),"r");
  s_file = obj_file;

  if (!scenef) 
  {
    cout<< string("Can not open object File \"") << obj_file << "\" !" << endl;
    return;
  }

  cout<<endl<<obj_file<<endl;
    
  while(!feof(scenef))
  {
    int retVal = 0;
    char *returnString;

    token[0] = 0;
    retVal = fscanf(scenef,"%s", token);    // token

    if (!strcmp(token,"g"))
    {
      retVal = fscanf(scenef,"%s",buf);
    }

    else if (!strcmp(token,"mtllib"))
    {
      retVal = fscanf(scenef,"%s", mat_file);
      loadMat(string(obj_database) + string(mat_file));
    }

    else if (!strcmp(token,"usemtl"))
    {
      retVal = fscanf(scenef,"%s",buf);
      cur_mat = matMap[s_file+string("_")+string(buf)];
    }

    else if (!strcmp(token,"v"))
    {
      retVal = fscanf(scenef,"%f %f %f",&vec[0],&vec[1],&vec[2]);
      vList.push_back(Vec3(vec));
    }

    else if (!strcmp(token,"vn"))
    {
      retVal = fscanf(scenef,"%f %f %f",&vec[0],&vec[1],&vec[2]);
      nList.push_back(Vec3(vec));
    }
    else if (!strcmp(token,"vt"))
    {
      retVal = fscanf(scenef,"%f %f",&vec[0],&vec[1]);
      tList.push_back(Vec3(vec));
    }

    else if (!strcmp(token,"f"))
    {
      for (i=0;i<3;i++)
      {
        retVal = fscanf(scenef,"%s",v[i]);
      }
      
      Vertex  tmp_vertex[3];    // for faceList structure

      for (i=0;i<3;i++)   // for each vertex of this face
      {
        char str[20], ch;
        int base,offset;
        base = offset = 0;

        // calculate vertex-list index
        while( (ch=v[i][base+offset]) != '/' && (ch=v[i][base+offset]) != '\0')
        {
          str[offset] = ch;
          offset++;
        }
        str[offset] = '\0';
        n_vertex = atoi(str);
        base += (ch == '\0')? offset : offset+1;
        offset = 0;

        // calculate texture-list index
        while( (ch=v[i][base+offset]) != '/' && (ch=v[i][base+offset]) != '\0')
        {
          str[offset] = ch;
          offset++;
        }
        str[offset] = '\0';
        n_texture = atoi(str);
        base += (ch == '\0')? offset : offset+1;
        offset = 0;

        // calculate normal-list index
        while( (ch=v[i][base+offset]) != '\0')
        {
          str[offset] = ch;
          offset++;
        }
        str[offset] = '\0';
        n_normal = atoi(str); 

        tmp_vertex[i].setVertexIndex(n_vertex);
        tmp_vertex[i].setTextureIndex(n_texture);
        tmp_vertex[i].setNormalIndex(n_normal);
        tmp_vertex[i].setMaterialIndex(cur_mat);
      }

      fList.push_back(Face(tmp_vertex[0],tmp_vertex[1],tmp_vertex[2]));
    }

    else if (!strcmp(token,"#"))   
      returnString = fgets(buf,100,scenef);

  }

  if (scenef) fclose(scenef);

  vTotal = vList.size();
  nTotal = nList.size();
  tTotal = tList.size();
  fTotal = fList.size();
  printf("vertex: %d, normal: %d, texture: %d, triangles: %d\n",vTotal, nTotal, tTotal, fTotal);
}

void Mesh::loadMat(string mat_file)
{
  char  token[100], buf[100];
  float r,g,b;

  int cur_mat = 0;       

  materialf = fopen(mat_file.c_str(),"r");
  m_file = mat_file;

  if (!materialf) 
  {
    cout << "Can't open material file \"" << mat_file << "\"!" << endl;
    return;
  }

  cout<<mat_file<<endl;

  while(!feof(materialf))
  {
    int retVal = 0;
    char *returnString;

    token[0] = 0;
    retVal = fscanf(materialf,"%s", token);    

    for(unsigned int i=0; i< strlen(token); i++) {
      token[i] = tolower(token[i]);
    }

    if (token[strlen(token)-1] == '\n') token[strlen(token)-1] = '\0';

    if (!strcmp(token,"newmtl"))
    {
      retVal = fscanf(materialf,"%s",buf);
      cur_mat = matTotal++;         
      matMap[s_file+string("_")+string(buf)] = cur_mat;   
    }

    else if (!strcmp(token,"ka"))
    {
      retVal = fscanf(materialf,"%f %f %f",&r,&g,&b);
      mat[cur_mat].Ka[0] = r;
      mat[cur_mat].Ka[1] = g;
      mat[cur_mat].Ka[2] = b;
    }

    else if (!strcmp(token,"kd"))
    {
      retVal = fscanf(materialf,"%f %f %f",&r,&g,&b);
      mat[cur_mat].Kd[0] = r;
      mat[cur_mat].Kd[1] = g;
      mat[cur_mat].Kd[2] = b;
    }

    else if (!strcmp(token,"ks"))
    {
      retVal = fscanf(materialf,"%f %f %f",&r,&g,&b);
      mat[cur_mat].Ks[0] = r;
      mat[cur_mat].Ks[1] = g;
      mat[cur_mat].Ks[2] = b;
    }

    else if (!strcmp(token,"ns"))
    {
      retVal = fscanf(materialf,"%f",&r);
      mat[cur_mat].Ns = r;
    }

    else if (!strcmp(token,"tr")) {
      float a;
      retVal = fscanf(materialf,"%f",&a);
      a = 1.0 - a;
      mat[cur_mat].Ka[3] = mat[cur_mat].Ks[3] = mat[cur_mat].Kd[3] = a;
    }

    else if (!strcmp(token,"map_kd"))
    {

      char line[512];

      returnString = fgets(line,512,materialf);
      if (line[strlen(line)-1] == '\n') line[strlen(line)-1] = '\0';

      char* tok = line;
      // Skip over whitespace
      while(*tok != '\0' && *tok == ' ') tok++;
      
      strcpy(mat[cur_mat].texture_filename,tok);
      printf("This material refers to a texture: %s\n",tok);
    }

    else if (!strcmp(token,"#"))   
      returnString = fgets(buf,100,materialf);
  }

  printf("total material:%d\n",(int) matMap.size());

  if (materialf) fclose(materialf);
}

void Mesh::init(const char* obj_file)
{
  float default_value[3] = {1,1,1};

  vList.clear();
  nList.clear();
  tList.clear();
  fList.clear();
  
  vList.push_back(Vec3(default_value)); 
  nList.push_back(Vec3(default_value)); 
  tList.push_back(Vec3(default_value));

  // default material: mat[0]
  mat[0].Ka[0] = 0.0; mat[0].Ka[1] = 0.0; mat[0].Ka[2] = 0.0; mat[0].Ka[3] = 1.0; 
  mat[0].Kd[0] = 1.0; mat[0].Kd[1] = 1.0; mat[0].Kd[2] = 1.0; mat[0].Kd[3] = 1.0; 
  mat[0].Ks[0] = 0.8; mat[0].Ks[1] = 0.8; mat[0].Ks[2] = 0.8; mat[0].Ks[3] = 1.0;
  mat[0].Ns = 32;
  matTotal++;

  loadMesh(string(obj_file));   
}

