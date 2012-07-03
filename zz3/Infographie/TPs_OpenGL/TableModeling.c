
/*
 * OpenGL TP1 : Modélisation d'objet
 */
#include <windows.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <stdio.h>

/* Constantes pour le menu */
enum faces
{
  F_NONE, 
  F_FRONT,
  F_BACK,
  F_AXE
};

static int displayAxe = GL_TRUE; /* Affichage des axes de WCS */
enum faces displayFace=GL_BACK;  /* Face a  éliminer          */

static int width, height;        /* Dimension de la fenetre   */ 
static int curx, cury;           /* Position de la souris     */

static GLfloat rotx = 0.0;       /* Rotation autour de x      */
static GLfloat roty = 0.0;       /* Rotation autour de y      */

static GLfloat couleur_plateau[3] = {0.6, 0.4, 0.3}; /* Couleur du dessus de table */
static GLfloat couleur_pied[3] = {0.4, 0.4, 0.4};    /* Couleur des pieds de table */


/*  GL_SMOOTH is actually the default shading model.  */
void init (void)
{
  glClearColor (0.0, 0.0, 0.0, 1.0);    /* Couleur de fond en noir   */
  glShadeModel (GL_SMOOTH);				/* Model d'ombrage (Gouraud) */

  glFrontFace (GL_CCW);					/* Activation l'elimination de faces arrieres */
  glEnable (GL_CULL_FACE);
  
  glPolygonMode (GL_BACK, GL_LINE);     /* Mode d'affichage des faces */
  glPolygonMode (GL_FRONT, GL_FILL);


  glEnable (GL_DEPTH_TEST);				/* Activation de Z-buffer     */
  
}


/* -------------------------------------------------------------------- */
/* Modelisation d'un rectangle de longueur "width", de largeur "height" */
/* et de couleur "color". Les sommets sont ordonnes dans le sens CCW    */
/* -------------------------------------------------------------------- */
void drawRectangle(float width, float height, GLfloat *color)
{
	GLfloat demiw, demih;

	demiw = width/2.;
	demih = height/2.;

	glBegin (GL_POLYGON);
		glColor3fv(color);
		glVertex3f(-demiw, -demih, 0.0);

		glColor3fv(color);
		glVertex3f(demiw, -demih, 0.0);

		glColor3fv(color);
		glVertex3f(demiw, demih, 0.0);

		glColor3fv(color);
		glVertex3f(-demiw, demih, 0.0);
	glEnd ();
}


/* -------------------------------------------------------------------- */
/* Modelisation d'une parallelepipede a partir de drawRectangle         */
/* largueur, hauteur et profondeur de la parallelepipede sont :         */
/* width, height et depth.                                              */
/* -------------------------------------------------------------------- */
void drawParallelepipede(float width, float height, float depth, GLfloat *color)
{
	/* Face avant */
	glPushMatrix();
	glTranslatef(0.0, 0.0, depth/2.);
	drawRectangle(width, height, color);
	glPopMatrix();

	/* Face arriere */
	glPushMatrix();
	glTranslatef(0.0, 0.0, -depth/2.);
	glRotatef(180.0, 1.0, 0.0, 0.0);		/* pour l'ordre des sommets (en CCW) */
	drawRectangle(width, height, color);
	glPopMatrix();

	/* Faces haut/bas */
	glPushMatrix();
	glRotatef(90.0, 1.0, 0.0, 0.0);
	/* Face haut */
	glPushMatrix();
	glTranslatef(0.0, 0.0, height/2.);
	drawRectangle(width, depth, color);
	glPopMatrix();

	/* Face bas */
	glPushMatrix();
	glTranslatef(0.0, 0.0, -height/2.);
	glRotatef(180.0, 1.0, 0.0, 0.0);		/* pour l'ordre des sommets en CCW */
	drawRectangle(width, depth, color);
	glPopMatrix();
	glPopMatrix();

	/*Faces droite/gauche */
	glPushMatrix();
	glRotatef(90.0, 0.0, 1.0, 0.0);
	/* Face droite */
	glPushMatrix();
	glTranslatef(0.0, 0.0, width/2.);
	drawRectangle(depth, height, color);
	glPopMatrix();

	/* Face gauche */
	glPushMatrix();
	glTranslatef(0.0, 0.0, -width/2.);
	glRotatef(180.0, 0.0, 1.0, 0.0);		/* pour l'ordre des sommets en CCW */
	drawRectangle(depth, height, color);
	glPopMatrix();
	glPopMatrix();
}


/* -------------------------------------------------------------------- */
/* Modelisation d'une table ayant un plateau, un cadre et 4 pieds       */
/* -------------------------------------------------------------------- */
void drawTable(float plateau_w, float plateau_h, float plateau_d,
			   float pied_w, float pied_h, float pied_d)
{
	/* Plateau */
	glPushMatrix();
	glTranslatef(0.0, plateau_h/2., 0.0);
	drawParallelepipede(plateau_w+plateau_h, plateau_h/2., plateau_d+plateau_h, couleur_plateau);
	glPopMatrix();

	/* cadres */
	glPushMatrix();
	glTranslatef(0.0, 0.0, plateau_d/2.0-pied_d/2.0);
	drawParallelepipede(plateau_w, plateau_h/2., pied_d, couleur_pied);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 0.0, -plateau_d/2.0+pied_d/2.0);
	drawParallelepipede(plateau_w, plateau_h/2., pied_d, couleur_pied);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(plateau_w/2.0-pied_w/2.0, 0.0, 0.0);
	drawParallelepipede(pied_w, plateau_h/2., plateau_d, couleur_pied);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-plateau_w/2.0+pied_w/2.0, 0.0, 0.0);
	drawParallelepipede(pied_w, plateau_h/2., plateau_d, couleur_pied);
	glPopMatrix();

	/* Pieds */
	glPushMatrix();
	glTranslatef(-plateau_w/2.0+pied_w/2.0, -pied_h/2.0, -plateau_d/2.0+pied_d/2.0);
	drawParallelepipede(pied_w, pied_h, pied_d, couleur_pied);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-plateau_w/2.0+pied_w/2.0, -pied_h/2.0, plateau_d/2.0-pied_d/2.0);
	drawParallelepipede(pied_w, pied_h, pied_d, couleur_pied);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(plateau_w/2.0-pied_w/2.0, -pied_h/2.0, -plateau_d/2.0+pied_d/2.0);
	drawParallelepipede(pied_w, pied_h, pied_d, couleur_pied);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(plateau_w/2.0-pied_w/2.0, -pied_h/2.0, plateau_d/2.0-pied_d/2.0);
	drawParallelepipede(pied_w, pied_h, pied_d, couleur_pied);
	glPopMatrix();

}


/* -------------------------------------------------------------------- */
/*                      Affichage des axes de WCS                       */
/* -------------------------------------------------------------------- */
void drawAxes(float lx, float ly, float lz)
{
	glBegin(GL_LINES);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(0, 0, 0);
	glVertex3f(lx, 0, 0);

	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, ly, 0);

	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, lz);
	glEnd();
}



/* -------------------------------------------------------------------- */
/* Les fonctions glut :  display, reshape, specialkey, menu             */
/* -------------------------------------------------------------------- */
void display(void)
{
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();
    glRotatef (rotx, 1.0, 0.0, 0.0);
    glRotatef (roty, 0.0, 1.0, 0.0);

	if (displayAxe) drawAxes(0.5, 0.4, 0.4);

	drawTable(0.8, 0.1, 0.5, 0.04, 0.6, 0.04);
    glPopMatrix();

    glutSwapBuffers ();
}

void reshape(int w, int h)
{
  glViewport(0, 0, (GLsizei)w, (GLsizei)h);
  width = w; height = h;

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  /*glFrustum(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);*/
      glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
  glMatrixMode(GL_MODELVIEW);
}

void specialkey (int key, int x, int y)
{
	switch (key) {
	case GLUT_KEY_LEFT :
      roty -= 5.0;
      if (roty < 0.0) roty += 360.0;
		break;
	case GLUT_KEY_RIGHT :
     roty += 5.0;
      if (roty > 360.0) roty -= 360.0;
		break;
	case GLUT_KEY_UP :
     rotx -= 5.0;
      if (rotx < 0.0) rotx += 360.0;
		break;
	case GLUT_KEY_DOWN :
      rotx += 5.0;
      if (rotx > 360.0) rotx -= 360.0;
		break;
	}
    glutPostRedisplay ();
}


void menu(int value)
{
  switch (value) 
  {
  case F_NONE:
    break;
  case F_FRONT:
     displayFace = GL_BACK;
    break;
  case F_BACK:
     displayFace = GL_FRONT;
    break;
  case F_AXE:
    displayAxe = !displayAxe;
     break;

  }

  glCullFace (displayFace);
  glutPostRedisplay();
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

  glutCreateMenu(menu);
  glutAddMenuEntry("Display Face :", F_NONE          );  
  glutAddMenuEntry("   Front      ", F_FRONT      );
  glutAddMenuEntry("   Back       ", F_BACK     );
  glutAddMenuEntry("              ", F_NONE          );
  glutAddMenuEntry("Axes :        ", F_NONE          );  
  glutAddMenuEntry("   Toggle Axes", F_AXE      );
  glutAttachMenu(GLUT_RIGHT_BUTTON);

  init();
  glutDisplayFunc (display);
  glutReshapeFunc (reshape);
  glutSpecialFunc (specialkey);
  glutMainLoop();

  return 0;
}
