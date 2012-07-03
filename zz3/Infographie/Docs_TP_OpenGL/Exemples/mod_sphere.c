/*
 * icosahedron.c
 *  This program draws
 */
#include <windows.h>
#include <stdio.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <math.h>

#define X .525731112119133606
#define Z .850650808352039932

static GLfloat vdata[12][3] = {
  {-X, 0.0, Z}, {X, 0.0, Z},{-X, 0.0, -Z},{X, 0.0, -Z},
  {0.0, Z, X}, {0.0, Z, -X}, {0.0, -Z, X}, {0.0, -Z, -X},
  {Z, X, 0.0}, {-Z, X, 0.0},  {Z, -X, 0.0}, {-Z, -X, 0.0}
};

static GLuint tindices[20][3] = {
  {0,4,1}, {0,9,4}, {9,5,4}, {4,5,8}, {4,8,1},
  {8,10,1}, {8,3,10}, {5,3,8}, {5,2,3}, {2,7,3},
  {7,10,3}, {7,6,10}, {7,11,6}, {11,0,6}, {0,1,6},
  {6,1,10}, {9,0,11}, {9,11,2}, {9,2,5}, {7,2,11} };


void normalize(GLfloat v[3])
{
  GLfloat d = sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);

  if ( d == 0.0) {
    perror("Zero length vector");
    return;
  }

  v[0] /= d;  v[1] /= d;   v[2] /= d;
}

void normcrossprod(GLfloat v1[3], GLfloat v2[3], GLfloat out[3])
{
  out[0] = v1[1]*v2[2] - v1[2]*v2[1];
  out[1] = v1[2]*v2[0] - v1[0]*v2[2];
  out[2] = v1[0]*v2[1] - v1[1]*v2[0];
  normalize(out);
}

void drawTriangle(GLfloat *v1, GLfloat *v2, GLfloat *v3)
{
  GLfloat normale[3];
  GLint   i;

  for (i=0; i<3; i++)
	  normale[i] = (v1[i] + v2[i] + v3[i]) / 3.0;

  glBegin(GL_TRIANGLES);
    glNormal3fv (normale); 
//	glNormal3fv (v1); // pour GL_SMOOTH
	glVertex3fv (v1);
    
    glNormal3fv (normale);  // pour GL_SMOOTH
//    glNormal3fv (v2);
    glVertex3fv (v2);

    glNormal3fv (normale);  // pour GL_SMOOTH
//    glNormal3fv (v3);
    glVertex3fv (v3);
  glEnd();
}


void monsubdivide(GLfloat *v1, GLfloat *v2, GLfloat *v3, long depth)
{
  GLfloat v12[3], v23[3], v31[3];
  GLint i;

  if (depth == 0) {
    drawTriangle(v1, v2, v3);
    return;
  }

  /* Calculer les coordonnees du milieu de chaque arete du triangle */
  for (i=0; i<3; i++) {
    v12[i] = v1[i] + v2[i];
    v23[i] = v2[i] + v3[i];
    v31[i] = v3[i] + v1[i];
  }

  /* Normaliser les vecteurs afin que les points soient sur la sphere */
  normalize(v12);
  normalize(v23);
  normalize(v31);

  monsubdivide(v1, v12, v31, depth-1);
  monsubdivide(v2, v23, v12, depth-1);
  monsubdivide(v3, v31, v23, depth-1);
  monsubdivide(v12, v23, v31, depth-1);
}


void display (void)
{
  int i;

  GLfloat light_ambient[] = { 0.4, 0.4, 0.4, 1.0 };
  GLfloat light_diffuse[] = { 0.8, 0.8, 0.8, 1.0 };
  GLfloat light_speculaire[] = { 0.8, 0.8, 0.8, 1.0 };
  GLfloat light_nul[] = { 0.0, 0.0, 0.0, 1.0 };

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//  glColor3f(1.0, 1.0, 1.0); //Modelisation
  glPolygonMode (GL_FRONT, GL_LINE);
  glPolygonMode (GL_BACK, GL_FILL);

  glPushMatrix();

  /* Eclairage ambiant */
  glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
  glLightfv(GL_LIGHT0, GL_SPECULAR, light_nul);
  
 /* niveau de subdivision = 0 */
  glTranslatef(0.0, -1.5, 0.0);
  glTranslatef(-1.5, 0.0, 0.0);
  for (i=0; i<20; i++)
    monsubdivide(&vdata[tindices[i][0]][0],
	             &vdata[tindices[i][1]][0],
		         &vdata[tindices[i][2]][0],0);

  /* niveau de subdivision = 1 */
  glTranslatef(3.0, 0.0, 0.0);
  for (i=0; i<20; i++)
    monsubdivide(&vdata[tindices[i][0]][0],
	             &vdata[tindices[i][1]][0],
		         &vdata[tindices[i][2]][0],1);

  /* niveau de subdivision = 2 */
  glTranslatef(3.0, 0.0, 0.0);
  for (i=0; i<20; i++)
    monsubdivide(&vdata[tindices[i][0]][0],
	             &vdata[tindices[i][1]][0],
		         &vdata[tindices[i][2]][0],3);

    /* niveau de subdivision = 3 */
  glTranslatef(3.0, 0.0, 0.0);
  for (i=0; i<20; i++)
    monsubdivide(&vdata[tindices[i][0]][0],
	             &vdata[tindices[i][1]][0],
		         &vdata[tindices[i][2]][0],5);
  glPopMatrix();

 
  glFlush ();
}

void init (void) 
{
  GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
  GLfloat mat_shininess[] = { 50.0 };
  /* w=0, la position est une direction */
  GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };

  glClearColor (1.0, 1.0, 1.0, 1.0);
  glShadeModel (GL_FLAT);

  glFrontFace(GL_CCW);
  glEnable(GL_CULL_FACE);
  glCullFace(GL_FRONT);

  glDepthFunc(GL_LESS);
  glEnable(GL_DEPTH_TEST);

  glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

  /* Positionnement de la source blanche */
  glLightfv(GL_LIGHT0, GL_POSITION, light_position);

  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);

  /* Positionnement du camera */
  glTranslatef (-3.0, 1.5, 0.0); 
}

void reshape(int w, int h)
{
  glViewport(0, 0, (GLsizei) w, (GLsizei) h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  if (w > h)
    glOrtho(-2.0*(GLfloat)w/(GLfloat)h, 
	  2.0*(GLfloat)w/(GLfloat)h, 
	    -0.5*(GLfloat)w/(GLfloat)h, 
	    0.5*(GLfloat)w/(GLfloat)h, -10.0, 10.0);
  else 
    glOrtho(-0.5*(GLfloat)h/(GLfloat)w, 
	    0.5*(GLfloat)h/(GLfloat)w, 
	    -2.0*(GLfloat)h/(GLfloat)w, 
	    2.0*(GLfloat)h/(GLfloat)w, -10.0, 10.0);

  glMatrixMode(GL_MODELVIEW);
}



/*  Main Loop
 *  Open window with initial window size, title bar, 
 *  RGBA display mode, and handle input events.
 */
int main(int argc, char** argv)
{
  glutInit ( &argc, argv );
  glutInitDisplayMode ( GLUT_SINGLE | GLUT_RGB  | GLUT_DEPTH);
  glutInitWindowSize ( 1200, 400 );
  glutInitWindowPosition ( 100, 100 );
  glutCreateWindow (argv[0]);

  init();
  glutDisplayFunc (display);
  glutReshapeFunc (reshape);
  glutMainLoop();

  return 0;
}

