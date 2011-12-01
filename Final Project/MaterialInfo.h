//
//  MaterialInfo.h

#ifndef MATERIAL_INFO
#define MATERIAL_INFO


class MaterialInfo {
private:
    
    float specular[4];
    float ambient [4];
    float diffuse [4];
    float shininess;
    
public:
    
    void setGLMaterial(MaterialInfo m);
    
    MaterialInfo (float r, float g, float b) {
        specular[0] = ambient[0] = diffuse[0] = r;
        specular[1] = ambient[1] = diffuse[1] = g;
        specular[2] = ambient[2] = diffuse[2] = b;
        specular[3] = ambient[3] = diffuse[3] = 1.0;
        shininess = 100.0;
    }
    
    MaterialInfo() { }
    
    float *getSpecular() { return specular; }
    float *getDiffuse() { return diffuse; }
    float *getAmbient() { return ambient; }
    float getShininess() { return shininess; }
    
};

static const MaterialInfo MAT_WHITE (1.0,1.0,1.0);
static const MaterialInfo MAT_GRAY  (0.5,0.5,0.5);
static const MaterialInfo MAT_BLUE  (0.1,0.1,0.6);
static const MaterialInfo MAT_GREEN (0.0,1.0,0.0);
static const MaterialInfo MAT_RED   (0.6,0.1,0.1);
static const MaterialInfo MAT_YELLOW(0.5,0.5,0.0);

#endif

