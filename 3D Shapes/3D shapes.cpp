#include <windows.h>  // for MS Windows
#include <GL/glut.h>  // GLUT, include glu.h and gl.h

/* Global variables */
char title[] = "3D Shapes";
GLfloat angleSphere = 0.0f;  // Rotational angle for sphere
GLfloat angleCube = 0.0f;     // Rotational angle for cube
int refreshMills = 15;        // refresh interval in milliseconds

/* Initialize OpenGL Graphics */
void initGL() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
    glClearDepth(1.0f);                   // Set background depth to farthest
    glEnable(GL_DEPTH_TEST);   // Enable depth testing for z-culling
    glDepthFunc(GL_LEQUAL);    // Set the type of depth-test
    glShadeModel(GL_SMOOTH);   // Enable smooth shading

    GLfloat ambient[] = { 0.0, 0.0, 0.0, 0.1 };
    GLfloat diffuse[] = { 1.0, 1.0, 0.0, 1.0 };
    GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat position[] = { 1.0, 1.0, 1.0, 0.0 };
    GLfloat positionn[] = { -1.0, 1.0, 1.0, 1.0 };

    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMaterialf(GL_FRONT, GL_SHININESS, 30);

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);//light0
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
    glLightfv(GL_LIGHT0, GL_POSITION, position);

    glLightfv(GL_LIGHT1, GL_AMBIENT, ambient);//light1
    glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, specular);
    glLightfv(GL_LIGHT1, GL_POSITION, positionn);

    glEnable(GL_LIGHTING);                // so the renderer considers light
    glEnable(GL_LIGHT0);                  // turn LIGHT0 on (Enable individual lights) (source: gl-light0)
    glEnable(GL_LIGHT1);                  // turn LIGHT1 on (Enable individual lights) (source: gl-light1)
    glEnable(GL_COLOR_MATERIAL);           //to work with currenct color of shape
}

/* Handler for window-repaint event. Called back when the window first appears and
   whenever the window needs to be re-painted. */
void display_3Dshapes() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers
    glMatrixMode(GL_MODELVIEW);     // To operate on model-view matrix

    // Render a sphere
    glPushMatrix();                 // Reset the model-view matrix
    glColor3f(1, 0, 0);
    glTranslatef(1.5f, 0.0f, -7.0f);  // Move right and into the screen
    glRotatef(angleSphere, 1.0f, 1.0f, 0.0f);  // Rotate about the (1,1,0)-axis
    glutSolidSphere(1, 16, 16); //SPEHERE
    glPopMatrix();

    // Render a cube 
    glPushMatrix();              // Reset the model-view matrix
    glColor3f(0, 0, 1);
    glTranslatef(-1.5f, 0.0f, -6.0f);  // Move left and into the screen
    glRotatef(angleCube, 1.0f, 1.0f, 1.0f);  // Rotate about (1,1,1)-axis
    glutSolidCube(1); //CUBE
    glPopMatrix();

    glutSwapBuffers();  // Swap the front and back frame buffers (double buffering)

    // Update the rotational angle after each refresh 
    angleSphere += 0.2f;
    angleCube -= 0.15f;
}

/* Called back when timer expired */
//for animating 3D shapes
void timer(int value) {
    glutPostRedisplay();      // Post re-paint request to activate display()
    glutTimerFunc(refreshMills, timer, 0); // next timer call milliseconds later
}

/* Handler for window re-size event. Called back when the window first appears and
   whenever the window is re-sized with its new width and height */
void reshape(GLsizei width, GLsizei height) {  // GLsizei for non-negative integer
   // Compute aspect ratio of the new window
    if (height == 0) height = 1;                // To prevent divide by 0
    GLfloat aspect = (GLfloat)width / (GLfloat)height;

    // Set the viewport to cover the new window
    glViewport(0, 0, width, height);

    // Set the aspect ratio of the clipping volume to match the viewport
    glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
    glLoadIdentity();             // Reset
    // Enable perspective projection with fovy, aspect, zNear and zFar
    gluPerspective(45.0f, aspect, 0.1f, 100.0f);
}

/* Main function: GLUT runs as a console application starting at main() */
int main(int argc, char** argv) {
    glutInit(&argc, argv);            // Initialize GLUT
    glutInitDisplayMode(GLUT_DOUBLE); // Enable double buffered mode
    glutInitWindowSize(640, 480);   // Set the window's initial width & height
    glutInitWindowPosition(50, 50); // Position the window's initial top-left corner
    glutCreateWindow(title);          // Create window with the given title
    glutDisplayFunc(display_3Dshapes);       // Register callback handler for window re-paint event
    glutReshapeFunc(reshape);       // Register callback handler for window re-size event
    initGL();                       // Our own OpenGL initialization
    glutTimerFunc(0, timer, 0);     // First timer call immediately [NEW]
    glutMainLoop();                 // Enter the infinite event-processing loop
    return 0;
}