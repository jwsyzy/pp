#include<iostream>
#include<ctime>
using namespace std;
struct student 
{
int age;  
float score; 
char sex;  
};
struct student a={ 20,79,'f'}; 

struct student 
{
int age;  
float score; 
char sex;  
}a={21,80,'n'};

struct  
{
int age;  
float score; 
char sex;  
}a={21,80,'n'};

class Box
{
   public:
      double length;   
      double breadth;  
      double height;   
};
Box Box1;

struct video_info{
    char *name;
    long address;
    int size;
    int alg;
    time_t time;
};

int get_video(struct video_info *vinfo)
{
   return 0;
}
struct video_info vinfo = {0};
int a=get_video(&vinfo);

struct base1 {
    int i1;
};
struct base2 {
    double d1, d2;
};
struct derive {
    int mine;
    struct base1 b1;
    struct base2 b2;
};

struct Bird{
    char name[20];
    char color;    
    char addr[30];   
    int other;     
};
struct fBird{
    struct Bird p;
    char fly[20]; 
    int scream;        
};

class Box
{
   public:
      double length;      
      double breadth;    
      double height;     
   
      double getVolume(void)
      {
         return length * breadth * height;
      }
};
//or
double Box::getVolume(void)
{
    return length * breadth * height;
}
Box box1;
float a=box1.getVolume();