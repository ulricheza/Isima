
/*
 * cube_rgb.c
 * This program demonstrates Color RVB and smooth shading.
 * Smooth shaded polygons are drawn in a 2D projection.
 */
#include <windows.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <stdio.h>

#define X 0.5

static GLfloat vecteurs[8][3] = {
	{X, -X, X}, {X, -X, -X}, {-X, -X, -X}, {-X, -X, X},
	{-X, X, X}, {X, X, X}, {X, X, -X}, {-X, X, -X}};

static GLuint indices[6][4] = {
	{0,3,2,1}, {4,5,6,7}, {0,5,4,3}, {1,2,7,6}, {1,6,5,0}, {2,3,4,7}}; //GL_CCW

static GLfloat couleurs[8][3] = {
	{1.0, 0.0, 0.0}, {1.0, 0.0, 1.0}, {0.0, 0.0, 1.0}, {0.0, 0.0, 0.0},
	{0.0, 1.0, 0.0}, {1.0, 1.0, 0.0}, {1.0, 1.0, 1.0}, {0.0, 1.0, 1.0}};

static GLfloat couleurs2[6][3] = {
	{1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 1.0},
	{1.0, 1.0, 0.0}, {1.0, 0.0, 1.0}, {0.0, 1.0, 1.0}};

static GLfloat rotx = 0.0; /* Rotation autour de x */
static GLfloat roty = 0.0; /* Rotation autour de y */
static prex = -1;
static prey = -1;


/*  GL_SMOOTH is actually the default shading model.  */
void init (void)
{
	glClearColor (0.0, 0.0, 0.0, 1.0);
	glShadeModel (GL_SMOOTH);

//  glFrontFace (GL_CCW);
	glEnable (GL_CULL_FACE);
//  glCullFace (GL_FRONT);
  
	glEnable (GL_DEPTH_TEST);
  
}

/* Fonction de modelisation du cube RGB */
void cube(void)
{
	GLint i;

	glPolygonMode (GL_BACK, GL_FILL);
   	glPolygonMode (GL_FRONT, GL_LINE);

	for (i=0; i<6; i++) {
		glBegin (GL_POLYGON);
			glColor3fv (couleurs[indices[i][0]]);
			glVertex3fv (vecteurs[indices[i][0]]);

			glColor3fv (couleurs[indices[i][1]]);
			glVertex3fv (vecteurs[indices[i][1]]);

			glColor3fv (couleurs[indices[i][2]]);
			glVertex3fv (vecteurs[indices[i][2]]);

			glColor3fv (couleurs[indices[i][3]]);
			glVertex3fv (vecteurs[indices[i][3]]);
		glEnd ();
	}
}

/* Fonction d'affichage du cube avec application de rotation */
void display(void)
{
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();
    glRotatef (rotx, 1.0, 0.0, 0.0);
    glRotatef (roty, 0.0, 1.0, 0.0);
    cube ();
    glPopMatrix();

    glutSwapBuffers ();
}

/* Redimensionnement de la taille de la fenetre graphique */
void reshape(int w, int h)
{
  glViewport(0, 0, (GLsizei)w, (GLsizei)h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  /* glFrustum(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0); */
  glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
  glMatrixMode(GL_MODELVIEW);
}

/* Fonction permettant l'utlisation des touches de fonction */
void specialFunc(int key, int x, int y)
{
	switch (key) {
		case GLUT_KEY_DOWN :
			rotx += 5.0;
			glutPostRedisplay ();
			break;
			
		case GLUT_KEY_UP :
			rotx -= 5.0;
			glutPostRedisplay ();
			break;
			
		case GLUT_KEY_RIGHT :
			roty += 5.0;
			glutPostRedisplay ();
			break;
			
		case GLUT_KEY_LEFT :
			roty -= 5.0;
			glutPostRedisplay ();
			break;
			
		case GLUT_KEY_END :
			exit (0);
			
		default :
			break;
	}
}

/* Fonction de traitement des actions des boutons de la souris */
void mouse (int button, int state, int x, int y)
{
  switch (button) {
  case GLUT_LEFT_BUTTON :
    if (state == GLUT_DOWN) {
      rotx += 5.0;
      if (rotx > 360.0) rotx -= 360.0;
      glutPostRedisplay ();
    }
      /*glutIdleFunc (spinDisplay );*/
    break;
  case GLUT_RIGHT_BUTTON :
    if (state == GLUT_DOWN) {
      roty += 5.0;
      if (roty > 360.0) roty -= 360.0;
      glutPostRedisplay ();
    }
    break;
    /* Inutile dans le cas ou on n'utilise pas glutIdleFunc */
  case GLUT_MIDDLE_BUTTON :
    if (state == GLUT_DOWN)
      glutIdleFunc(NULL);
    break;
  default :
    break;
  }
}

/* Fonction de traitement du mouvement de la souris */
void motion(int x, int y)
{
	if (prex != -1) {
		roty += x-prex;
	}
	
	if (prey != -1) {
		rotx += y-prey;
	} 
	
	glutPostRedisplay ();
	
	prex = x;	
	prey = y;
}

/*  Main Loop
 *  Open window with initial window size, title bar, 
 *  RGBA display mode, and handle input events.
 */
int main(int argc, char** argv)
{
	glutInit ( &argc, argv );
	glutInitDisplayMode (GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);

	glutInitWindowSize ( 500, 500 );
	glutInitWindowPosition ( 100, 100 );
	glutCreateWindow (argv[0]);

	init();
	
	glutDisplayFunc (display);
	glutReshapeFunc (reshape);
	glutMouseFunc (mouse);
  	glutMotionFunc(motion);
	glutSpecialFunc(specialFunc);
	glutMainLoop();

  return 0;
}
