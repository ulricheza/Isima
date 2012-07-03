
/*
 * cube_rgb.c
 * This program demonstrates Color RVB and smooth shading.
 * Smooth shaded polygons are drawn in a 2D projection.
 */
#include <windows.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <stdio.h>

#define X 0.2
#define Y 0.8

void setLight(void);

static GLfloat vecteurs[8][3] = {
	{X, -X, X}, {X, -X, -X}, {-X, -X, -X}, {-X, -X, X},
	{-X, X, X}, {X, X, X}, {X, X, -X}, {-X, X, -X}};

// Vecteur du rectangle
static GLfloat vecteursRectangle[8][3] = {
	{X, -X, Y}, {X, -X, -Y}, {-X, -X, -Y}, {-X, -X, Y},
	{-X, X, Y}, {X, X, Y}, {X, X, -Y}, {-X, X, -Y}};

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

	glEnable (GL_CULL_FACE);
	glFrontFace (GL_CCW);
	glCullFace (GL_FRONT);

  	glEnable (GL_DEPTH_TEST);
	glutInitDisplayMode (GLUT_DEPTH | GLUT_RGB );
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}

/* Fonction de modelisation du cube RGB */
void cube(void)
{
	GLint i;

	GLfloat light0matAmb[4]  =  {0.20, 0.20, 0.20, 1.00};
    GLfloat light0matDif[4]  =  {1.0, 1.0, 1.0, 1.00};
    GLfloat light0matEmi[4]  =  {0.80, 0.80, 0.80, 1.00};
    GLfloat matZero[4] =  {0.00, 0.00, 0.00, 1.00};

  /* Definition de proprietes de la sphere qui represente la source 0 */
  glMaterialfv(GL_FRONT, GL_AMBIENT, light0matAmb);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, light0matDif);
  glMaterialfv(GL_FRONT, GL_EMISSION, light0matEmi);
  glMaterialfv(GL_FRONT, GL_SPECULAR, matZero);

	glPolygonMode (GL_BACK, GL_LINE);
   	glPolygonMode (GL_FRONT, GL_LINE);

	glClearColor(0.2,0.3,0.4,0.1);

	for (i=0; i<6; i++) {
		glBegin (GL_QUADS);
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

void drawRectangle(float width, float height, GLfloat color)
{

	GLfloat demiw, demih;

	demiw = width/2.;
	demih = height/2.;

	glBegin (GL_QUADS);
		glColor4fv(&color);
		glNormal3f(0.0, 0.0, 1.0);
		glVertex3f(-demiw, -demih, 0.0);

		glColor4fv(&color);
		glNormal3f(0.0, 0.0, 1.0);
		glVertex3f(demiw, -demih, 0.0);

		glColor4fv(&color);
		glNormal3f(0.0, 0.0, 1.0);
		glVertex3f(demiw, demih, 0.0);

		glColor4fv(&color);
		glNormal3f(0.0, 0.0, 1.0);
		glVertex3f(-demiw, demih, 0.0);
	glEnd ();	
}

void drawParallepipede(float width, float height, float depth, GLfloat color)
{
	//front
	glPushMatrix();
	glTranslatef(0. , 0. , depth/2);
	drawRectangle(width, height, color);
	glPopMatrix();

	//back
	glPushMatrix();
	glRotatef(180, 0, 1, 0);
	glTranslatef(0. , 0. , depth/2);
	drawRectangle(width, height, color);
	glPopMatrix();

	//right
	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glTranslatef(0. , 0. , width/2);
	drawRectangle(depth, height, color);
	glPopMatrix();

	//left
	glPushMatrix();
	glRotatef(-90, 0, 1, 0);
	glTranslatef(0. , 0. , width/2);
	drawRectangle(depth, height, color);
	glPopMatrix();

	glPushMatrix();
	glRotatef(90,1,0,0);
	glTranslatef(0. , 0. , height/2);
	drawRectangle(width, depth, color);
	glPopMatrix();
	
	glPushMatrix();
	glRotatef(-90, 1, 0, 0);
	glTranslatef(0. , 0. , height/2);
	drawRectangle(width, depth, color);
	glPopMatrix();




}

/* Fonction d'affichage du cube avec application de rotation */
void display(void)
{
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();
    glRotatef (rotx, 1.0, 0.0, 0.0);
    glRotatef (roty, 0.0, 1.0, 0.0);

	//GLfloat light_ambiant[]

	setLight();
    //cube ();

	glPushMatrix();
	glRotatef(0, 0, 0, 0);
	glTranslatef(-0.5 , -0.5 , -0.3);
	drawParallepipede(0.1,0.5,0.1, 1.0);
	glPopMatrix();

	glPushMatrix();
	glRotatef(0, 0, 0, 0);
	glTranslatef(0.5 , -0.5 , -0.3);
	drawParallepipede(0.1,0.5,0.1, 1.0);
	glPopMatrix();

	glPushMatrix();
	glRotatef(0, 0, 0, 0);
	glTranslatef(0.5 , -0.5 , 0.3);
	drawParallepipede(0.1,0.5,0.1, 1.0);
	glPopMatrix();

	glPushMatrix();
	glRotatef(0, 0, 0, 0);
	glTranslatef(-0.5 , -0.5 , 0.3);
	drawParallepipede(0.1,0.5,0.1, 1.0);
	glPopMatrix();
	
	glPushMatrix();
	glRotatef(0, 0, 0, 0);
	glTranslatef(0 , -0.25 , 0);
	drawParallepipede(1.2,0.05,1, 1.0);
	glPopMatrix();
	
	glPopMatrix();
	glEnable(GL_CULL_FACE);

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

void setLight(void)
{
  GLfloat light0Pos[4] = {0.50, 1.25, 0.00, 0.00};
  GLfloat light0Amb[4] = {1.00, 0.00, 0.0, 1.00};
  GLfloat light0Diff[4] = {1.00, 0.00, 0.00, 1.00};
  GLfloat light0Spec[4] = {1.00, 1.00, 1.00, 1.00};
 
  GLfloat light0SpotExp = 0.00;
  GLfloat light0SpotCutoff = 180.00;

  GLfloat light0matAmb[4]  =  {0.20, 0.20, 0.20, 1.00};
  GLfloat light0matDif[4]  =  {1.0, 1.0, 1.0, 1.00};
  GLfloat light0matEmi[4]  =  {0.80, 0.80, 0.80, 1.00};
  GLfloat matZero[4] =  {0.00, 0.00, 0.00, 1.00};

  glEnable(GL_LIGHTING);	/* Activation de model d'eclairage */
  glEnable(GL_LIGHT0);      /* Activer la source 0             */

  /* Definition de proprietes de la source 0 */
  glLightfv(GL_LIGHT0, GL_POSITION, light0Pos);
  glLightfv(GL_LIGHT0, GL_AMBIENT, light0Amb);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light0Diff);
  glLightfv(GL_LIGHT0, GL_SPECULAR, light0Spec);

  /* Definition de proprietes de la sphere qui represente la source 0 */
  glMaterialfv(GL_FRONT, GL_AMBIENT, light0matAmb);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, light0matDif);
  glMaterialfv(GL_FRONT, GL_EMISSION, light0matEmi);
  glMaterialfv(GL_FRONT, GL_SPECULAR, matZero);

  /* Positionnement de la sphere a la meme place que la source 0 */ 
  glPushMatrix();
  glTranslatef(light0Pos[0], light0Pos[1], light0Pos[2]);
  glutSolidSphere(0.05, 16, 16);
  glPopMatrix();

 // glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, light0SpotDir);
 // glLightf (GL_LIGHT0, GL_SPOT_EXPONENT, light0SpotExp);
 // glLightf (GL_LIGHT0, GL_SPOT_CUTOFF, light0SpotCutoff);
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
