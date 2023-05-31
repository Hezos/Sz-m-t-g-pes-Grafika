#include "scene.h"
#include "stdlib.h"
#include <obj/load.h>
#include <obj/draw.h>
#include "time.h"
#include "math.h"
#include "stdio.h"

#define PI 3.14159265359
int state = 1;
double arc = 180;
int OriginalState = 1;

//Jegyezd meg melyikhez tartozik melyik index!
char* ModelNevek[];
char Model1[] = "assets/models/genericchassis.obj";
char Model2[] = "assets/models/chassisfront.obj";
char Model3[] = "assets/models/belly.obj";
char Model4[] = "assets/models/bellyend.obj";
char Model5[] = "assets/models/head.obj";
char Model6[] = "assets/models/leg.obj";
char Model7[] = "assets/models/prt0001.obj";


void init_scene(Scene* scene)
{
    //Túl nagy a modell, 1 és 0 közötti méretek.
    load_model(&(scene->cube), "assets/models/cube.obj");
    // scene->texture_id = load_texture("assets/textures/cube.png");
    //The glBindTexture function enables the creation of a named texture that is bound to a texture target.
    //Parameters: target The target to which the texture is bound. Must have the value GL_TEXTURE_1D or GL_TEXTURE_2D.
    //texture The name of a texture; the texture name cannot currently be in use.
    // glBindTexture(GL_TEXTURE_2D, scene->texture_id);

    scene->material.ambient.red = 1.0;
    scene->material.ambient.green = 1.0;
    scene->material.ambient.blue = 1.0;

    scene->material.diffuse.red = 1.0;
    scene->material.diffuse.green = 1.0;
    scene->material.diffuse.blue = 1.0;

    scene->material.specular.red = 1.0;
    scene->material.specular.green = 1.0;
    scene->material.specular.blue = 1.0;

    scene->material.shininess = 0.0;

    ModelNevek[0] = "assets/models/henger.obj";
    ModelNevek[1] = "assets/models/chassisfront.obj";
}

void set_lighting()
{
    float ambient_light[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    float diffuse_light[] = { 1.0f, 1.0f, 1.0, 1.0f };
    float specular_light[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    float position[] = { 0.0f, 0.0f, 10.0f, 1.0f };

    // The glLightfv function returns light source parameter values. Parameters light The identifier of a light. 
    // The number of possible lights depends on the implementation, but at least eight lights are supported. 
    // They are identified by symbolic names of the form GL_LIGHTi where i is a value: 0 to GL_MAX_LIGHTS - 1.
    // pname A light source parameter for light. The following symbolic names are accepted.
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
}

void set_material(const Material* material)
{
    float ambient_material_color[] = {
        material->ambient.red,
        material->ambient.green,
        material->ambient.blue
    };

    float diffuse_material_color[] = {
        material->diffuse.red,
        material->diffuse.green,
        material->diffuse.blue
    };

    float specular_material_color[] = {
        material->specular.red,
        material->specular.green,
        material->specular.blue
    };
    // The glMaterialfv function specifies material parameters for the lighting model. Parameters: face The face or faces that 
    // are being updated. Must be one of the following: GL_FRONT, GL_BACK, or GL_FRONT and GL_BACK.
    // pname The material parameter of the face or faces being updated. The parameters that can be specified using glMaterialfv,
    // and their interpretations by the lighting equation, are as follows.
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_material_color);

    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &(material->shininess));
}
//?????????????????????????????????????????????????????????
void update_scene(Scene* scene)
{
}

float Convert(float degree)
{
    float pi = 3.14159265359;
    return (degree * (pi / 180));
}

void render_scene(const Scene* scene)
{
    //Üresre rajzol valamit.
    set_material(&(scene->material));
    set_lighting();
    draw_origin();
    /*
   clock_t start_time = clock();
        while (clock() < start_time + 800){;}
    
    //Radinánnal számol
    double sinValue;
    sinValue = sin(2.3);
    */
    //load_model(&(scene->cube),"assets/models/cube.obj");
   // StepState();
   // glPushMatrix();
   // glScalef(0.5, 0.5, 0.5);
    //glRotatef(-45, 1,0,0);
    //glTranslatef(4+state,0,0);
  //  glTranslatef(3,0,0); 
  //  draw_model(&(scene->cube));    
  //  glPopMatrix();
  
      float Radius = 5.1;

    for(int i = 0; i < 9; i++){
        glPushMatrix();
        glRotatef(arc/9*i, 0, 0, 1);
        glTranslatef(Radius, 0, 0);
        draw_model(&(scene->cube));
        glPopMatrix();
    }
    /*
   clock_t start_time = clock();
        while (clock() < start_time + 400){;}
    */
    
    arc += 0.01;
    if (arc >= 360)
    {
        arc = 180;
    }

    //
    /*for (int i = -4; i < 5; i++)
    {
        glPushMatrix();
        glScalef(0.25, 0.25, 0.25);
        //*20
        float tmp = (float)i/0.05;
        glTranslatef(0  + i*2 + sin(Convert(tmp))* Radius,0 + cos(Convert(tmp))*Radius,0);
        glRotatef(20*i, 0,1,0);
        draw_model(&(scene->cube));
        glPopMatrix();
    }*/
    /*
    for (int i = -4; i < 5; i++)
    {
        if (i==0)
        {
            glPushMatrix();
            glScalef(0.25, 0.25, 0.25);
            //*20
            float tmp = (float)i/0.05;
            glTranslatef(0  + i*2,0,0);
            glRotatef(20*i, 0,1,0);
            draw_model(&(scene->cube));
            glPopMatrix();
        }
    }
        */
}

void draw_origin()
{
    glBegin(GL_LINES);

    glColor3f(1, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(1, 0, 0);

    glColor3f(0, 1, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 1, 0);

    glColor3f(0, 0, 1);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 1);

    glEnd();
}

void StepState(){
    state++;
}
