#include "app.h"

#include <SDL2/SDL_image.h>

void init_app(App* app, int width, int height)
{
    int error_code;
    int inited_loaders;
    app->is_running = false;

    //Hiba esetén hibakód
    error_code = SDL_Init(SDL_INIT_EVERYTHING);
    if (error_code != 0) {
        printf("[ERROR] SDL initialization error: %s\n", SDL_GetError());
        return;
    }

    //Ablak készítése: ablaknév, középre vertikálisan, horizontálisan, milyen széles és milyen magas, OpenGL elemek hozzáadása
    app->window = SDL_CreateWindow( "Cube!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
    if (app->window == NULL) {
        printf("[ERROR] Unable to create the application window!\n");
        return;
    }


    //This function loads dynamic libraries that SDL_image needs, and prepares them for use.
    // This must be the first function you call in SDL_image, and if it fails you should not continue with the library.
    //PNG flag gondolom
    inited_loaders = IMG_Init(IMG_INIT_PNG);
    if (inited_loaders == 0) {
        printf("[ERROR] IMG initialization error: %s\n", IMG_GetError());
        return;
    }


    //Melyik ablakon dolgozunk OpenGL-el
    app->gl_context = SDL_GL_CreateContext(app->window);
    if (app->gl_context == NULL) {
        printf("[ERROR] Unable to create the OpenGL context!\n");
        return;
    }

    //Initialize the OpenGL context.
    init_opengl();
    //Reshapes the window
    reshape(width, height);

    //Initializing camera and scenen
    init_camera(&(app->camera));
    init_scene(&(app->scene));

    app->is_running = true;
}

void init_opengl()
{
    //The glShadeModel function selects flat or smooth shading
    glShadeModel(GL_SMOOTH);

    //Initialize the scene by loading models
    glEnable(GL_NORMALIZE);
    glEnable(GL_AUTO_NORMAL);

    //The glClearColor function specifies clear values for the color buffers parameters: RGB aplha
    glClearColor(0.1, 0.1, 0.1, 1.0);

    //The glMatrixMode function specifies which matrix is the current matrix, parameters: mode, Not sure of matrix mode.
    glMatrixMode(GL_MODELVIEW);

    //The glLoadIdentity function replaces the current matrix with the identity matrix.
    glLoadIdentity();

    //New scene innitialization by loading models. Parameters: cap A symbolic constant indicating an OpenGL capability.
    glEnable(GL_DEPTH_TEST);

    //The glClearDepth function specifies the clear value for the depth buffer. parameters depth: value used when the depth buffer is cleared.
    glClearDepth(1.0);

    glEnable(GL_TEXTURE_2D);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
}

void reshape(GLsizei width, GLsizei height)
{
    int x, y, w, h;
    double ratio;

    //Szélesség és magasság arány
    ratio = (double)width / height;
    if (ratio > VIEWPORT_RATIO) {
        w = (int)((double)height * VIEWPORT_RATIO);
        h = height;
        x = (width - w) / 2;
        y = 0;
    }
    else {
        w = width;
        h = (int)((double)width / VIEWPORT_RATIO);
        x = 0;
        y = (height - h) / 2;
    }

    //The glViewport function sets the viewport. Parameters: x The lower-left corner of the viewport rectangle, in pixels. The default is (0,0).
    //y The lower-left corner of the viewport rectangle, in pixels. The default is (0,0).
    //width The width of the viewport. When an OpenGL context is first attached to a window, width and height 
    //are set to the dimensions of that window.
    //height The height of the viewport. When an OpenGL context is first attached to a window, 
    //width and height are set to the dimensions of that window.
    glViewport(x, y, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    //The glFrustum function multiplies the current matrix by a perspective matrix. Parameters:
    //left The coordinate for the left-vertical clipping plane.
    //right The coordinate for the right-vertical clipping plane.
    //bottom The coordinate for the bottom-horizontal clipping plane.
    //top The coordinate for the bottom-horizontal clipping plane.
    //zNear The distances to the near-depth clipping plane. Must be positive.
    //zFar The distances to the far-depth clipping planes. Must be positive.
    glFrustum(
        -.08, .08,
        -.06, .06,
        .1, 10
    );
}

void handle_app_events(App* app)
{
    SDL_Event event;
    static bool is_mouse_down = false;
    static int mouse_x = 0;
    static int mouse_y = 0;
    int x;
    int y;

    //Beérkező esemény kezeltetése:
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_KEYDOWN:
            switch (event.key.keysym.scancode) {
            //Kilépés kezelése
            case SDL_SCANCODE_ESCAPE:
                app->is_running = false;
                break;
            //Mozgatások
            case SDL_SCANCODE_W:
                set_camera_speed(&(app->camera), 1);
                break;
            case SDL_SCANCODE_S:
                set_camera_speed(&(app->camera), -1);
                break;
            case SDL_SCANCODE_A:
                set_camera_side_speed(&(app->camera), 1);
                break;
            case SDL_SCANCODE_D:
                set_camera_side_speed(&(app->camera), -1);
                break;
            default:
                break;
            }
            break;
        case SDL_KEYUP:
            switch (event.key.keysym.scancode) {
            case SDL_SCANCODE_W:
            //Megállítjuk a kamerát
            case SDL_SCANCODE_S:
                set_camera_speed(&(app->camera), 0);
                break;
            case SDL_SCANCODE_A:
            case SDL_SCANCODE_D:
                set_camera_side_speed(&(app->camera), 0);
                break;
            default:
                break;
            }
            break;
        case SDL_MOUSEBUTTONDOWN:
            is_mouse_down = true;
            break;
        case SDL_MOUSEMOTION:
            //Retrieve the current state of the mouse. x and y
            SDL_GetMouseState(&x, &y);
            if (is_mouse_down) {
                //Where does x and y get a value?????????????
                rotate_camera(&(app->camera), mouse_x - x, mouse_y - y);
            }
            mouse_x = x;
            mouse_y = y;
            break;
        case SDL_MOUSEBUTTONUP:
            is_mouse_down = false;
            break;
        case SDL_QUIT:
            app->is_running = false;
            break;
        default:
            break;
        }
    }
}

void update_app(App* app)
{
    double current_time;
    double elapsed_time;

    //Time handling for movement
    current_time = (double)SDL_GetTicks() / 1000;
    //Mennyi idő telt el a legutolsó frissítés óta:
    elapsed_time = current_time - app->uptime;
    //Újraszámoltatjuk a frissítés idejét
    app->uptime = current_time;

    //Frissítjük a kamerát
    update_camera(&(app->camera), elapsed_time);
    //Frissítjük a képernyőt:
    update_scene(&(app->scene));
}

void render_app(App* app)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);

    // The glPushMatrix and glPopMatrix functions push and pop the current matrix stack.
    glPushMatrix();
    // Camera function
    set_view(&(app->camera));
    render_scene(&(app->scene));
    // The glPushMatrix and glPopMatrix functions push and pop the current matrix stack.
    glPopMatrix();

    if (app->camera.is_preview_visible) {
        show_texture_preview();
    }
    // Update a window with OpenGL rendering. params: window the window to change
    SDL_GL_SwapWindow(app->window);
}

void destroy_app(App* app)
{
    if (app->gl_context != NULL) {
        SDL_GL_DeleteContext(app->gl_context);
    }

    if (app->window != NULL) {
        SDL_DestroyWindow(app->window);
    }

    SDL_Quit();
}
