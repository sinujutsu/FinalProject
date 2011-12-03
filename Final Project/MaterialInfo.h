//
//  MaterialInfo.h

#ifndef MATERIAL_INFO
#define MATERIAL_INFO
#include <string>
#include <iostream>
using namespace std;

class MaterialInfo {
private:
    
    float spec[4];
    float amb [4];
    float diff [4];
    float shininess;
    
public:
    
    void setGLMaterial(MaterialInfo m);
    
    int hexToGL(string hh){
        int result = 0;
        int value = 0;
        for (int i = 0; i<2; i++) {
            string h = hh.substr(i,1);
            if (h == "0") {
                value = 0;
            } else if (h == "1") {
                value = 1;
            } else if (h == "2") {
                value = 2;
            } else if (h == "3") {
                value = 3;
            } else if (h == "4") {
                value = 4;
            } else if (h == "5") {
                value = 5;
            } else if (h == "6") {
                value = 6;
            } else if (h == "7") {
                value = 7;
            } else if (h == "8") {
                value = 8;
            } else if (h == "9") {
                value = 9;
            } else if (h == "a" || h == "A") {
                value = 10;
            } else if (h == "b" || h == "B") {
                value = 11;
            } else if (h == "c" || h == "C") {
                value = 12;
            } else if (h == "d" || h == "D") {
                value = 13;
            } else if (h == "e" || h == "E") {
                value = 14;
            } else if (h == "f" || h == "F") {
                value = 15;
            }
            if (i == 0) {
                result = 16*value;
            } else{
                result += value;
            }
        }
        cout << "Hex: " << hh << " Base 10: "<<result<< endl;
        return result/255.0;
    }
    
    
    //string for each component of material should be in the form of #ffffffff
    
    
    MaterialInfo (string specHex, string ambHex, string diffHex, float shine){ 
        //float redSpec, greenSpec, blueSpec, alphSpec, redAmb, greenAmb, blueAmb, alphAmb, redDiff, greenDiff, blueDiff, alphDiff;
        
        
        
        spec[0] = hexToGL(specHex.substr(1,2));
        spec[1] = hexToGL(specHex.substr(3,2));
        spec[2] = hexToGL(specHex.substr(5,2));
        spec[3] = hexToGL(specHex.substr(7,2));
        
        amb[0] = hexToGL(ambHex.substr(1,2));
        amb[1] = hexToGL(ambHex.substr(3,2));
        amb[2] = hexToGL(ambHex.substr(5,2));
        amb[3] = hexToGL(ambHex.substr(7,2));
        
        diff[0] = hexToGL(diffHex.substr(1,2));
        diff[1] = hexToGL(diffHex.substr(3,2));
        diff[2] = hexToGL(diffHex.substr(5,2));
        diff[3] = hexToGL(diffHex.substr(7,2));
        
        shininess = shine;
    }
    
    MaterialInfo() { }
    
    float *getSpecular() { return spec; }
    float *getDiffuse() { return diff; }
    float *getAmbient() { return amb; }
    float getShininess() { return shininess; }
    
    
};

static const MaterialInfo MAT_WHITE ("#ffffffff","#ffffffff","#ffffffff",50);
static const MaterialInfo MAT_GRAY  ("#70809080","#70809080","#70809080",50);
static const MaterialInfo MAT_BLUE  ("#7fff00ff","#0000ffff","#0000ffff",90);
//static const MaterialInfo MAT_GREEN ("#7fff00ff","#7fff00ff","#7fff00ff",100);
static const MaterialInfo MAT_RED   ("#ff0000ff","#ff0000ff","#ff0000ff",50);
//static const MaterialInfo MAT_YELLOW("#ffff00ff","#ffff00ff","#ffff00ff",100);




//MaterialInfo MAT_TREE   (57,230,0,      27,107,0,         27,107,0,     80);
//MaterialInfo MAT_GRASS  (0,184,46,      0,184,46,         0,184,46,       50);
//MaterialInfo MAT_TRUNK  (77,0,0,        77,0,0,           77,0,0,         90);
//MaterialInfo MAT_ROOF   (255,255,255,   100,100,100,      84,84,84,       10);
//MaterialInfo MAT_BARN   (221,59,62,      117,31,33,       153,70,58,      60);
//MaterialInfo MAT_SUN    (240,175,255,   226,202,79,       255,202,79,     30);

#endif

