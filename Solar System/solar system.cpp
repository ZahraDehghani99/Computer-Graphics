#include <windows.h>  // for MS Windows
#include <GL/glut.h>  // GLUT, include glu.h and gl.h
#include <math.h>

/* Global variables */
char title[] = "Solar System";
GLfloat angleSun = 0.0f;      // Rotational angle for SUN 
GLfloat angleEarth_g = 0.0f;      // Rotational angle for cube 
GLfloat angleEarth_l = 0.0f;
GLfloat angelMoon_yl = 0.0;
GLfloat angelMoon_yg = 0.0;
GLfloat angelMoon_xe = 0.0;
GLfloat angelPlanet_yl = 0.0;
GLfloat angelPlanet_g = 0.0;
int refreshMills = 30;        // refresh interval in milliseconds 


/* Initialize OpenGL Graphics */
void initGL() {

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
    glClearDepth(1.0f);                   // Set background depth to farthest
    glEnable(GL_DEPTH_TEST);   // Enable depth testing for z-culling
    glDepthFunc(GL_LEQUAL);    // Set the type of depth-test
    glShadeModel(GL_SMOOTH);   // Enable smooth shading

    GLfloat light_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    GLfloat light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

    GLfloat mat_ambient[] = { 0.0f, 1.0f, 0.3f, 1.0f };
    GLfloat mat_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    GLfloat mat_specular[] = { 0.5f, 1.0f, 1.0f, 1.0f };
    GLfloat high_shininess[] = { 80.0f };

    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);//light0
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);

    
    glEnable(GL_LIGHTING);                // so the renderer considers light
    glEnable(GL_LIGHT0);                  // turn LIGHT0 on (Enable individual lights) (source: gl-light0)
    glEnable(GL_COLOR_MATERIAL);           //to work with currenct color of shape
}

/* Handler for window-repaint event. Called back when the window first appears and
   whenever the window needs to be re-painted. */
void display() {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers

    ///////////  SUN ///////////

    glPushMatrix();
    glColor3f(1, 1, 0);
    glRotatef(angleSun, 0.0f, 1.0f, 0.0f);  // Rotate about the (0,1,0)-axis 
    glutSolidSphere(5, 16, 16); //sun
    glPopMatrix();

    ///////////  EARTH ///////////

    glPushMatrix();
    glRotatef(angleEarth_g, 0, 1, 0);
    glTranslatef(10, 0.0, 0.0);
    glRotatef(angleEarth_l, 0, 1, 0);  // Rotate about (0,1,0)-axis
    glColor3f(0, 0, 1);
    glutSolidSphere(3, 16, 16); //earth
    glPopMatrix();

    ///////////  MOON ///////////

    glPushMatrix();
    glRotatef(angelMoon_yg, 0, 1, 0);
    glTranslatef(10, 0, 0);
    glRotatef(angelMoon_xe, 1, 0, 0);
    glTranslatef(0, 5, 0);
    glRotatef(angelMoon_yl, 0, 1, 0);  // Rotate about (0,1,0)-axis [NEW]
    glColor3f(0.5, 0.5, 0.5);
    glutSolidSphere(0.5, 16, 16); //moon
    glPopMatrix();

    ///////////  PLANET ///////////

    glPushMatrix();
    glTranslatef(8 * cos(angelPlanet_g), 0, 7 * sin(angelPlanet_g));    //elliptical orbit               
    glRotatef(angelPlanet_yl, 0, 1, 0);  // Rotate about (0,1,0)-axis 
    glColor3f(0.73, 0.16, 0.22);
    glutSolidSphere(2, 16, 16); //planet
    glPopMatrix();


    glutSwapBuffers();  // Swap the front and back frame buffers (double buffering)

    // Update the rotational angle after each refresh
    angleSun += 10;
    angleEarth_g += 10;
    angleEarth_l += 30;
    angelMoon_yl += 10;
    angelMoon_yg += 10;
    angelMoon_xe += 30;
    angelPlanet_yl += 30;
    angelPlanet_g += 10;
}

/* Called back when timer expired */
//for animating solar system
void timer(int value) {
    glutPostRedisplay();      // Post re-paint request to activate display()
    glutTimerFunc(refreshMills, timer, 0); // next timer call milliseconds later
}

/* Handler for window re-size event. Called back when the window first appears and
   whenever the window is re-sized with its new width and height */
void reshape(GLint w, GLint h) {

    glMatrixMode(GL_PROJECTION);
    gluPerspective(50.0, (GLfloat)w / (GLfloat)h, 3.0, 90.0);
    gluLookAt(8.0, 16.0, 80.0, 0, 0, 0, 0, 1, 0);
}
/* Main function: GLUT runs as a console application starting at main() */
int main(int argc, char** argv) {
    glutInit(&argc, argv);            // Initialize GLUT
    glutInitDisplayMode(GLUT_DOUBLE); // Enable double buffered mode
    glutInitWindowSize(1280, 800);   // Set the window's initial width & height
    glutInitWindowPosition(50, 50); // Position the window's initial top-left corner
    glutCreateWindow(title);          // Create window with the given title
    glutDisplayFunc(display);       // Register callback handler for window re-paint event
    glutReshapeFunc(reshape);       // Register callback handler for window re-size event
    initGL();                       // Our own OpenGL initialization
    glutTimerFunc(0, timer, 0);     // First timer call immediately [NEW]
    glutMainLoop();                 // Enter the infinite event-processing loop
    return 0;
}