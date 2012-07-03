
/*
 * Auteur: Maxime ESCOURBIAC - Jean-Christophe SEPTIER
 * table_rgb.c
 * Ce programme permet d'afficher une table.
 */

#include <windows.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <stdio.h>

// Variable global
static GLfloat rotx = 0.0; /* Rotation autour de x */
static GLfloat roty = 0.0; /* Rotation autour de y */
static prex = -1;
static prey = -1;

double zoom = 1.5;  // Zoom pour changer la position de la caméra

// Couleur des différents objets
static GLfloat couleur_rectangle[4] = {1.0, 1.0, 1.0, 0.8}; // Couleur du socle
static GLfloat couleur_plan[4] = {0.8, 0.3, 0.0, 0.5};// Couleur du plan de la table
static GLfloat couleur_pieds[4] = {0.8, 0.3, 0.1, 0.5}; // Couleur des pieds de la table

// Propriété pour savoir si la lumière bouge avec la caméra
static BOOL moveTable = TRUE;

GLfloat plane[4]={0.0, 1.0, 0.0, 0.6}; /* Equation du sol  */
GLfloat shadowMat[4][4];
GLfloat light_position[] = {0.55, 0.55, 0.55, 1.0};		// Position de la lampe

/*
Initialisation de la table.
*/
void init (void)
{	
	glClearColor (0.0, 0.0, 0.0, 1.0);					// Couleur de fond
	glShadeModel (GL_SMOOTH);							// Définie le mode d'ombre		

	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE); // Modèle d'éclairage

	glFrontFace (GL_CCW);								// Fixer une face avant
	glEnable (GL_CULL_FACE);							// Permet d'éliminer les faces avant

	glEnable(GL_COLOR_MATERIAL);						// Activation des propriétés matérielles
	glColorMaterial (GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

	glPolygonMode (GL_BACK, GL_LINE);  // Mode d'affichage des faces
	glPolygonMode (GL_FRONT, GL_FILL);

	glEnable (GL_DEPTH_TEST);				// Z Buffer
	glDepthFunc(GL_LEQUAL);
}

/* 
	Permet de construire un rectangle.
*/  
void drawRectangle(float largeur, float hauteur, GLfloat * color)
{
	glBegin (GL_QUADS);
		glColor4fv(color);
		glNormal3f(0.0, 0.0, 1.0);
		glVertex3f(-largeur/2, -hauteur/2, 0.0);

		glColor4fv(color);
		glNormal3f(0.0, 0.0, 1.0);
		glVertex3f(largeur/2, -hauteur/2, 0.0);

		glColor4fv(color);
		glNormal3f(0.0, 0.0, 1.0);
		glVertex3f(largeur/2, hauteur/2, 0.0);

		glColor4fv(color);
		glNormal3f(0.0, 0.0, 1.0);
		glVertex3f(-largeur/2, hauteur/2, 0.0);
	glEnd ();	
}

/*
	Permet de construire un parallépipède grâce à des rectangles.
*/
void drawParallepipede(float largeur, float hauteur, float profondeur, GLfloat * color)
{
	//devant
	glPushMatrix();
	glTranslatef(0. , 0. , profondeur/2);
	drawRectangle(largeur, hauteur, color);
	glPopMatrix();

	//arrière
	glPushMatrix();
	glRotatef(180, 0, 1, 0);
	glTranslatef(0. , 0. , profondeur/2);
	drawRectangle(largeur, hauteur, color);
	glPopMatrix();

	//droite
	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glTranslatef(0. , 0. , largeur/2);
	drawRectangle(profondeur, hauteur, color);
	glPopMatrix();

	//gauche
	glPushMatrix();
	glRotatef(-90, 0, 1, 0);
	glTranslatef(0. , 0. , largeur/2);
	drawRectangle(profondeur, hauteur, color);
	glPopMatrix();

	//dessus
	glPushMatrix();
	glRotatef(90,1,0,0);
	glTranslatef(0. , 0. , hauteur/2);
	drawRectangle(largeur, profondeur, color);
	glPopMatrix();
	
	//dessous
	glPushMatrix();
	glRotatef(-90, 1, 0, 0);
	glTranslatef(0. , 0. , hauteur/2);
	drawRectangle(largeur, profondeur, color);
	glPopMatrix();
}



/**	Construction d'une table. 
*
*/
void drawTable()
{
	// Affichage des pieds de la table
	glPushMatrix();
	glRotatef(0, 0, 0, 0);
	glTranslatef(-0.3 , -0.45 , -0.15);
	drawParallepipede(0.05,0.25,0.05, couleur_pieds);
	glPopMatrix();

	glPushMatrix();
	glRotatef(0, 0, 0, 0);
	glTranslatef(0.3 , -0.45 , -0.15);
	drawParallepipede(0.05,0.25,0.05, couleur_pieds);
	glPopMatrix();

	glPushMatrix();
	glRotatef(0, 0, 0, 0);
	glTranslatef(0.3 , -0.45 , 0.15);
	drawParallepipede(0.05,0.25,0.05, couleur_pieds);
	glPopMatrix();

	glPushMatrix();
	glRotatef(0, 0, 0, 0);
	glTranslatef(-0.3 , -0.45 , 0.15);
	drawParallepipede(0.05,0.25,0.05, couleur_pieds);
	glPopMatrix();
	
	// Affichage du plan de la table
	glPushMatrix();
	glRotatef(0, 0, 0, 0);
	glTranslatef(0 , -0.30 , 0);
	drawParallepipede(0.8,0.05,0.5, couleur_plan);
	glPopMatrix();
}

// Fonction qui initialise la matrice de projection
void ShadowMatrix(GLfloat shadowMat[4][4],
                  GLfloat plane[4], GLfloat lightpos[4])
{
	GLfloat dot;

	dot = plane[0] * lightpos[0] + plane[1] * lightpos[1] + plane[2] * lightpos[2] +
		  plane[3] * lightpos[3];
	
	shadowMat[0][0] = dot - lightpos[0] * plane[0];
	shadowMat[1][0] = 0.f - lightpos[0] * plane[1];
	shadowMat[2][0] = 0.f - lightpos[0] * plane[2];
	shadowMat[3][0] = 0.f - lightpos[0] * plane[3];
	
	shadowMat[0][1] = 0.f - lightpos[1] * plane[0];
	shadowMat[1][1] = dot - lightpos[1] * plane[1];
	shadowMat[2][1] = 0.f - lightpos[1] * plane[2];
	shadowMat[3][1] = 0.f - lightpos[1] * plane[3];
	
	shadowMat[0][2] = 0.f - lightpos[2] * plane[0];
	shadowMat[1][2] = 0.f - lightpos[2] * plane[1];
	shadowMat[2][2] = dot - lightpos[2] * plane[2];
	shadowMat[3][2] = 0.f - lightpos[2] * plane[3];
	
	shadowMat[0][3] = 0.f - lightpos[3] * plane[0];
	shadowMat[1][3] = 0.f - lightpos[3] * plane[1];
	shadowMat[2][3] = 0.f - lightpos[3] * plane[2];
	shadowMat[3][3] = dot - lightpos[3] * plane[3];
}

/*
* Initialisation de l'ombrage avec utilisation du stencil
* buffer
*/
void InitCastShadows()
{
	glClear(GL_STENCIL_BUFFER_BIT);
	glEnable(GL_STENCIL_TEST);
	glStencilFunc(GL_ALWAYS, 1, 1);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
}


/*
* Affichage de l'ombre sur le sol                                      
*/
void EndCastShadows(GLfloat matrix[4][4])
{	
	glStencilFunc(GL_EQUAL, 1, 1);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);

	glPushMatrix();
		glMultMatrixf((GLfloat *) matrix);
		drawTable();
	glPopMatrix();
	
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_STENCIL_TEST);
	glEnable(GL_LIGHTING);
}


/*
* Affiche la lumière.
*/
void setLight(void)
{
	GLfloat light_ambient[] = {0.40, 0.40, 0.40, 1.00};		// Lumière ambiante
	GLfloat light_diffuse[] = {1.0, 1.0, 1.0, 1.0};			// Lumière diffuse
	GLfloat light_specular[] = {0.80, 0.80, 0.80, 1.00};	// Lumiaire speculaire

	// Propriété de la sphère
	GLfloat light0_Amb[]  =  {0.20, 0.20, 0.20, 1.00};
	GLfloat light0_Dif[]  =  {1.0, 1.0, 1.0, 1.00};
	GLfloat light0_Emi[]  =  {0.80, 0.80, 0.80, 1.00};
	GLfloat matZero[] =  {0.00, 0.00, 0.00, 1.00};


	// Définition de la lampe
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

	glEnable(GL_LIGHTING);	/* Activation de model d'eclairage */
	glEnable(GL_LIGHT0);  
	

	// Propriété de la sphère
    glMaterialfv(GL_FRONT, GL_AMBIENT, light0_Amb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, light0_Dif);
	glMaterialfv(GL_FRONT, GL_EMISSION, light0_Emi);
	glMaterialfv(GL_FRONT, GL_SPECULAR, matZero);

	// Construit la sphère
	glPushMatrix();
	glTranslatef(light_position[0], light_position[1], light_position[2]);
	glutSolidSphere(0.05, 10, 10);
	glPopMatrix();
}

/**	Donne les propriétés matérielles au objets affichés.
*/
void setMaterial()
{
	//Propriétés matérielles
  GLfloat matAmb[4]  =  {0.25, 0.25, 0.25, 1.00};
  GLfloat matDiff[4] =  {0.75, 0.00, 0.00, 1.00};
  GLfloat matSpec[4] =  {0.50, 0.50, 0.50, 1.00};
  GLfloat matShine   = 15.00;

  GLfloat matZero[4] =  {0.00, 0.00, 0.00, 1.00};	

  glMaterialfv(GL_FRONT, GL_AMBIENT, matAmb);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, matDiff);
  glMaterialfv(GL_FRONT, GL_SPECULAR, matSpec);
  glMaterialf (GL_FRONT, GL_SHININESS, matShine);

  glMaterialfv(GL_FRONT, GL_EMISSION, matZero);
}


/* Fonction d'affichage de la table avec application de rotation */
void display(void)
{

    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if(!moveTable)
		setLight(); // La lampe est fixe

	InitCastShadows();
	ShadowMatrix(shadowMat, plane, light_position);

	glPushMatrix();
		glRotatef (rotx, 1.0, 0.0, 0.0);
		glRotatef (roty, 0.0, 1.0, 0.0); 
		if(moveTable)
			setLight(); // La lampe bouge

			// Affichage du Socle
			glEnable(GL_BLEND) ;									// Activation de la transparence de la table
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			glPushMatrix();
				glTranslatef(0.0, -0.60, 0.0);
				glRotatef(-90, 1.0, 0.0, 0.0);
				drawRectangle(2.0, 2.0, couleur_rectangle);
			glPopMatrix();
			
			EndCastShadows(shadowMat);

			setMaterial();
			drawTable();

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
  glOrtho(-1.0 * zoom , 1.0 * zoom, -1.0 * zoom , 1.0 * zoom , -1.0 * zoom , 1.0 * zoom);
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



/** Fonction main.
*	Ouvre la fenêtre et affiche notre table.
*/	
int main(int argc, char** argv)
{
	glutInit ( &argc, argv );
	glutInitDisplayMode (GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);

	glutInitWindowSize ( 500, 500 );		// Taille de la fenêtre
	glutInitWindowPosition ( 100, 100 );	// Position de la fenêtre
	glutCreateWindow (argv[0]);				

	init();									// Initialisation de la table

	glutDisplayFunc (display);
	glutReshapeFunc (reshape);
	glutMouseFunc (mouse);
  	glutMotionFunc(motion);
	glutSpecialFunc(specialFunc);
	glutMainLoop();

  return 0;
}