#include <windows.h>  // for MS Windows
#include <GL/glut.h>  // GLUT, include glu.h and gl.h
#include <math.h>

/* Global variables */
char title[] = "Articulated Arm";
int partOneRotation = 0, partTwoRotation = 0, partThreeRotation = 0, n = 0;
float x_partThree, y_partThree, z_partThree, x_sphere = 0.68, y_sphere = 0, z_sphere = 0, distance;
int refreshMills = 415;        // refresh interval in milliseconds

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
    GLfloat light_position[] = { 1.0f, 1.0f, 1.0f, 0.0f };

    GLfloat mat_ambient[] = { 0.0f, 1.0f, 0.3f, 1.0f };
    GLfloat mat_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    GLfloat mat_specular[] = { 0.5f, 1.0f, 1.0f, 1.0f };
    GLfloat high_shininess[] = { 100.0f };

    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);

    glEnable(GL_LIGHT0);		//Enabling the light
    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);

}

// Displays the arm in its current position and orientation.  The whole
// function is bracketed by glPushMatrix and glPopMatrix calls because every
// time we call it we are in an "environment" in which a gluLookAt is in
// effect.  (Note that in particular, replacing glPushMatrix with
// glLoadIdentity makes you lose the camera setting from gluLookAt).
void display_Articulated_Arm() {
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers
    
    ////// Fixed part //////
    glPushMatrix();					
    glTranslatef(-0.1, 0, 0);
    glScalef(0.2, 0.4, 1.0);
    glColor3f(1, 0, 0);
    glutSolidCube(1);
    glPopMatrix();				

    // Draw the upper arm, rotated shoulder degrees about the z-axis.  Note that
    // the thing about glutWireBox is that normally its origin is in the middle
    // of the box, but we want the "origin" of our box to be at the left end of
    // the box, so it needs to first be shifted 0.15 (half of its length) unit in the x direction, then
    // rotated.

    ////// First part //////

    glPushMatrix();

    glRotatef(partOneRotation,0,0,1);
    glTranslatef(0.15,0,0);         //set the pivot point of part one
    
    glPushMatrix();
    glScalef(0.3, 0.1, 1.0);
    glColor3f(1, 0, 1);
    glutSolidCube(1);
    glPopMatrix();

    ////// second part ////// 
  

    glTranslatef(0.15, 0, 0);          // we have to position middle arm at the end of upper arm
    glRotatef(partTwoRotation, 0, 0, 1);
    glTranslatef(0.1, 0, 0);          //set the pivot point of part two
    
    glPushMatrix();
    glScalef(0.2, 0.06, 1.0);
    glColor3f(1, 1, 0);
    glutSolidCube(1);
    glPopMatrix();

    ////// last part //////

    glTranslatef(0.1, 0, 0);           // we have to position lower arm at the end of middle arm
    glRotatef(partThreeRotation, 0, 0, 1);
    glTranslatef(0.09, 0, 0);         //set the pivot point of part three
    
    glPushMatrix();
    glScalef(0.18, 0.035, 1.0);
    glColor3f(0, 1, 0);
    glutSolidCube(1);
    glPopMatrix();

    glPopMatrix();

    ////// sphere //////

    glPushMatrix();

    glTranslatef(x_sphere, y_sphere, z_sphere);
    glScalef(0.05,0.05,0.05);
    glColor3f(1,1,1);
    glutSolidSphere(1, 16, 16);

    glPopMatrix();

    
    glutSwapBuffers();  // Swap the front and back frame buffers (double buffering)

    

}

//Calculate the distance of the lower arm and the sphere, and when their 
//distance is equal, the arm gets the sphere and puts it in another place.
// In this section, we just move the lower arm.
void timer(int value) {

    //Coordinates of the end of the last part
    x_partThree = 0.5 + 0.18 * cos(partThreeRotation);
    y_partThree = 0.18 * sin(partThreeRotation); //doroste????
    z_partThree = 0;

    distance = sqrt(pow(x_partThree - x_sphere, 2) + pow(y_partThree - y_sphere, 2) + pow(z_partThree - z_sphere, 2));

    if (distance == 0 && n <=3) {
        x_sphere = x_partThree;
        y_sphere = y_partThree;
        z_sphere = z_partThree;
    }

    partThreeRotation = (partThreeRotation + 2) % 360;
    n += 1;

    glutPostRedisplay();      // Post re-paint request to activate display()
    glutTimerFunc(refreshMills, timer, 0); // next timer call milliseconds later
    
    
}

/* Handler for window re-size event. Called back when the window first appears and
   whenever the window is re-sized with its new width and height */
void reshape(GLsizei width, GLsizei height) {  // GLsizei for non-negative integer
    
    glViewport(0, 0, (GLsizei)width, (GLsizei)height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// Handle movements of the arms with keyboard
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        //Shoulder
    case 's':
        partOneRotation = (partOneRotation + 5) % 360;
        glutPostRedisplay();
        break;
    case 'S':
        partOneRotation = (partOneRotation - 5) % 360;
        glutPostRedisplay();
        break;
        //Elbow
    case 'e':
        if (partTwoRotation < 180)
            partTwoRotation = (partTwoRotation + 5) % 360;
        glutPostRedisplay();
        break;
    case 'E':
        if (partTwoRotation > 0)
            partTwoRotation = (partTwoRotation - 5) % 360;
        glutPostRedisplay();
        break;
        //Hand
    case 'h':
        if (partThreeRotation < 90)
            partThreeRotation = (partThreeRotation + 5) % 360;
        glutPostRedisplay();
        break;
    case 'H':
        if (partThreeRotation > 0)
            partThreeRotation = (partThreeRotation - 5) % 360;
        glutPostRedisplay();
        break;
    }


}



/* Main function: GLUT runs as a console application starting at main() */
int main(int argc, char** argv) {
    glutInit(&argc, argv);            // Initialize GLUT
    glutInitDisplayMode(GLUT_DOUBLE); // Enable double buffered mode
    glutInitWindowSize(640, 480);   // Set the window's initial width & height
    glutInitWindowPosition(50, 50); // Position the window's initial top-left corner
    glutCreateWindow(title);          // Create window with the given title
    glutDisplayFunc(display_Articulated_Arm);       // Register callback handler for window re-paint event
    glutReshapeFunc(reshape);       // Register callback handler for window re-size event
    initGL();                       // Our own OpenGL initialization
    glutTimerFunc(0, timer, 0);     // First timer call immediately 
    //glutKeyboardFunc(keyboard);		//Getting input from keyboard !
    glutMainLoop();                 // Enter the infinite event-processing loop
    return 0;
}