#include "header.h"
extern FILE * pFile1;
extern FILE * pFile2;

bool handle_exception(void (*f)(int),int para) {
    fprintf(pFile2,"\n");
    try{
        f(para);
        return 0;
    } catch(const char* msg) {
        fprintf(pFile2, "%s\n",msg);
        return 1;
    }
    
}

bool handle_exception(void (*f)()) {
    fprintf(pFile2,"\n");
    try{
        f();
        return 0;
    } catch(const char* msg) {
        fprintf(pFile2, "%s\n",msg);
        return 1;
    }
    
}


bool handle_exception(void (*f)(int,int),int para1, int para2) {
    fprintf(pFile2,"\n");
    try{
        f(para1,para2);
        return 0;
    } catch(const char* msg) {
        fprintf(pFile2, "%s\n",msg);
        return 1;
    }
    
    
}

bool handle_exception(int (*f)(int,int),int para1, int para2) {
    fprintf(pFile2,"\n");
    try{
        f(para1,para2);
        return 0;
        
    } catch(const char* msg) {
        fprintf(pFile2, "%s\n",msg);
        return 1;
    }
    
}

