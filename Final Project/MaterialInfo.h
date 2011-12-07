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
    float emit [4];
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
        return result/255.0;
    }
    
    
    //string for each component of material should be in the form of #fffffff
    //one string is needed for specualr ambient, and diffuse, and a number from 0 to 128 for shine level
    
    
    MaterialInfo (string specHex, string ambHex, string diffHex, string emitHex, float shine){ 
        spec[0] = hexToGL(specHex.substr(1,2));
        spec[1] = hexToGL(specHex.substr(3,2));
        spec[2] = hexToGL(specHex.substr(5,2));
        //spec[3] = hexToGL(specHex.substr(7,2));
        
        amb[0] = hexToGL(ambHex.substr(1,2));
        amb[1] = hexToGL(ambHex.substr(3,2));
        amb[2] = hexToGL(ambHex.substr(5,2));
        //amb[3] = hexToGL(ambHex.substr(7,2));
        
        diff[0] = hexToGL(diffHex.substr(1,2));
        diff[1] = hexToGL(diffHex.substr(3,2));
        diff[2] = hexToGL(diffHex.substr(5,2));
        //diff[3] = hexToGL(diffHex.substr(7,2));
        
        emit[0]= hexToGL(emitHex.substr(1,2));
        emit[1]= hexToGL(emitHex.substr(3,2));
        emit[2]= hexToGL(emitHex.substr(5,2));
        //emit[3]= hexToGL(emitHex.substr(7,2));
        
        spec[3]=amb[3]=diff[3]=emit[3]=1;
        
        shininess = shine;
    }
    
    MaterialInfo() { }
    
    float *getSpecular() { return spec; }
    float *getDiffuse() { return diff; }
    float *getAmbient() { return amb; }
    float *getEmitted() {return emit; }
    float getShininess() { return shininess; }
};
//***************************************************************************
//define new materials here__________Specular___Ambient__Diffuse___Emitted__Shine
static const MaterialInfo MAT_WHITE ("#F0F0F0","#F0F0F0","#ffffff","F7EDF0",90);
static const MaterialInfo MAT_GRAY  ("#ffffff","#ffffff","#ffffff","BAA9AE",90);
static const MaterialInfo MAT_BLUE  ("#7fff00","#3D00F5","#0000ff","3881CF",90);
static const MaterialInfo MAT_GREEN ("#7fff00","#00F53D","#7fff00","38CF79",90);
static const MaterialInfo MAT_RED   ("#ff0000","#B8002E","#ff0000","FA9039",90);
static const MaterialInfo MAT_YELLOW("#ffff00","#FF0000","#FF0000","FAF739",90);

#endif

