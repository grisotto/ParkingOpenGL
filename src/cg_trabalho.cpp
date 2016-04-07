#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>

void drawcarr();

// Variáveis para controles de navegação
GLfloat angle, fAspect;
GLfloat rotX, rotY, rotX_ini, rotY_ini;
GLfloat obsX, obsY, obsZ, obsX_ini, obsY_ini, obsZ_ini;
int x_ini,y_ini,bot;
static GLint carr_display_list;
int click = 0;
float flap1_angle = 0;
float flap2_angle = 0;
float center1_angle = 0;
float center2_angle = 0;
float wing1_angle = 0;
float wing2_angle = 0;

//adicionado depois
float theta=0.09; //angulo para curva
float aceleracaoX=0.5; //velocidade do carro
float aceleracaoZ=0,temp,theta1;

		float fx=-10,fz=10; //posicao do carro

// Luz selecionada
int luz = 0;




void DefineIlumincao1(void)
{
    GLfloat luzAmbiente[4]={0.2,0.2,0.2,1.0};
	GLfloat luzDifusa[4]={0.7,0.9,0.7,2.0};	   // "cor"
	GLfloat luzEspecular[4]={0.0, 0.0, 0.0, 0.0};// "brilho"
	GLfloat posicaoLuz[4]={0.0, 50.0, 50.0, 1.0};

	// Capacidade de brilho do material
	GLfloat especularidade[4]={1.0,1.0,1.0,1.0};
	GLint especMaterial = 160;

 	// Especifica que a cor de fundo da janela serÃ¡ preta
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	// Habilita o modelo de colorizaÃ§Ã£o de Gouraud
	glShadeModel(GL_SMOOTH);
	// Define a refletÃ¢ncia do material
	glMaterialfv(GL_FRONT,GL_SPECULAR, especularidade);
	// Define a concentração do brilho
	glMateriali(GL_FRONT,GL_SHININESS,especMaterial);
	// Ativa o uso da luz ambiente
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);

	// Define os parametros da luz de numero 0
	glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa );
	glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular );
	glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz );

//Função Iluminação 2===========================================================
    GLfloat luzAmbiente2[4]={0.2,0.2,0.2,1.0};
	GLfloat luzDifusa2[4]={10.7,0.9,0.7,2.0};	   // "cor"
	GLfloat luzEspecular2[4]={1.0, 1.0, 1.0, 1.0};// "brilho"
	GLfloat posicaoLuz2[4]={-10.0, 10.0, -10.0, 0.0};

	// Capacidade de brilho do material
	GLfloat especularidade2[4]={1.0,1.0,1.0,1.0};
	GLint especMaterial2 = 160;

 	// Especifica que a cor de fundo da janela serÃ¡ preta
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	// Habilita o modelo de colorizaÃ§Ã£o de Gouraud
	glShadeModel(GL_SMOOTH);
	// Define a refletÃ¢ncia do material
	glMaterialfv(GL_FRONT,GL_SPECULAR, especularidade2);
	// Define a concentração do brilho
	glMateriali(GL_FRONT,GL_SHININESS,especMaterial2);
	// Ativa o uso da luz ambiente
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente2);

	// Define os parametros da luz de numero 0
	glLightfv(GL_LIGHT1, GL_AMBIENT, luzAmbiente2);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, luzDifusa2 );
	glLightfv(GL_LIGHT1, GL_SPECULAR, luzEspecular2 );
	glLightfv(GL_LIGHT1, GL_POSITION, posicaoLuz2 );

	// Habilita a definição da cor do material a partir da cor corrente
	glEnable(GL_COLOR_MATERIAL);
	//Habilita o uso de iluminação
	glEnable(GL_LIGHTING);
	// Habilita a luz de numero 0
	glEnable(GL_LIGHT0);
	//glEnable(GL_LIGHT1);
	// Habilita o depth-buffering
	glEnable(GL_DEPTH_TEST);

}

void Arvores()
{
     //Folhas da arvore
     glPushMatrix();
         glColor3f(0.0,1.0,0.);
         glRotatef(-90,1,0,0);
         int d = 0;
         while(d<=220)
         {
            glPushMatrix();
               glTranslatef(-d,0,17);
               glutSolidCone(10,40,8,5);
               d=d+20;
            glPopMatrix();
         }
     glPopMatrix();
     //Tronco da arvore
     glPushMatrix();
         glColor3f(1.0,0.4,0.3);
         int f = 0;
         while(f<=220)
         {
            glPushMatrix();
               glTranslatef(-f,10,0);
               glScalef(1,10,1);
               glutSolidCube(2);
               f=f+20;
            glPopMatrix();
         }
     glPopMatrix();
}
void movecar(int key, int x, int y)
{

	switch (key)
	{
		case GLUT_KEY_LEFT :
							//guardo a aceleracao em x
							temp=aceleracaoX;
							//calculo a nova acelaracaoX conforme o angulo
							aceleracaoX=  aceleracaoX * cos(theta) + aceleracaoZ * sin(theta);
							//calculo a nova aceleracaoZ conforme o angulo
							aceleracaoZ=- temp * sin(theta) + aceleracaoZ * cos(theta);
							//incremento fx e fz conforme o valor da aceleracao
							fx+=aceleracaoX;
							fz+=aceleracaoZ;

							break;
		case GLUT_KEY_RIGHT :
								temp=aceleracaoX;
								aceleracaoX=aceleracaoX * cos(-theta) + aceleracaoZ * sin(-theta);
								aceleracaoZ=-temp * sin(-theta) +  aceleracaoZ * cos(-theta);
								fx+=aceleracaoX;
								fz+=aceleracaoZ;

							break;
						case GLUT_KEY_UP :
								//conforme a aceleracao eu irei alterando o valor da posicao do carro
								//para frente eu deveria preocupar apenas com x, mas o z eh minha variavel de movimento tambem, entao incremento ela igualmente
								fx+=aceleracaoX;
								fz+=aceleracaoZ;
						break;

						case GLUT_KEY_DOWN :
							//conforme a aceleracao eu irei alterando o valor da posicao do carro
								fx-=aceleracaoX;
			  	  	  	  	  	fz-=aceleracaoZ;
			  	  	  	  	  	break;

	}
	glutPostRedisplay();
}

void Estrada()
{
     //Fora da casa
     glColor3f(0.8,0.3,0.3);
     glPushMatrix();
         glTranslatef(-21,1,-73.5);
         glScalef(30,0.1,3);
         glutSolidCube(10);
     glPopMatrix();
}

// Funç¿o callback de redesenho da janela de visualização
void Desenha(void)
{
//	defineLuz();
	// Limpa a janela de visualização com a cor
	// de fundo definida previamente
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//	defineLuz();
//	DefineIluminacao();


	// Draw ground

	glPushMatrix();
	glColor3f(0.5f, 1.0f, 0.5f);
	glTranslatef(0,-2.8,-5);
	glScalef(10,1,10);
	glutSolidCube(6);


	glPopMatrix();
	glPushMatrix();


	glTranslatef(0,0.21,0);
		//glColor3f(0.0f, 0.0f, 0.0f);



		glColor3f(1.0f, 1.0f, 1.0f);
		glTranslatef(0,0,-28);
		glBegin(GL_QUADS);
		glVertex3f(-1.0f, 0.1f, -7.0f);
		glVertex3f(-1.0f, 0.1f,  7.0f);
		glVertex3f( 1.0f, 0.1f,  7.0f);
		glVertex3f( 1.0f, 0.1f, -7.0f);
		glEnd();
		glTranslatef(-10,0,0);
		glBegin(GL_QUADS);
		glVertex3f(-1.0f, 0.1f, -7.0f);
		glVertex3f(-1.0f, 0.1f,  7.0f);
		glVertex3f( 1.0f, 0.1f,  7.0f);
		glVertex3f( 1.0f, 0.1f, -7.0f);
		glEnd();
		glTranslatef(-10,0,0);
		glBegin(GL_QUADS);
		glVertex3f(-1.0f, 0.1f, -7.0f);
		glVertex3f(-1.0f, 0.1f,  7.0f);
		glVertex3f( 1.0f, 0.1f,  7.0f);
		glVertex3f( 1.0f, 0.1f, -7.0f);
		glEnd();

		glTranslatef(-9,0,0);
		glBegin(GL_QUADS);
		glVertex3f(-1.0f, 0.1f, -7.0f);
		glVertex3f(-1.0f, 0.1f,  7.0f);
		glVertex3f( 1.0f, 0.1f,  7.0f);
		glVertex3f( 1.0f, 0.1f, -7.0f);
		glEnd();

		glTranslatef(40,0,0);
		glBegin(GL_QUADS);
		glVertex3f(-1.0f, 0.1f, -7.0f);
		glVertex3f(-1.0f, 0.1f,  7.0f);
		glVertex3f( 1.0f, 0.1f,  7.0f);
		glVertex3f( 1.0f, 0.1f, -7.0f);
		glEnd();
		glTranslatef(10,0,0);
		glBegin(GL_QUADS);
		glVertex3f(-1.0f, 0.1f, -7.0f);
		glVertex3f(-1.0f, 0.1f,  7.0f);
		glVertex3f( 1.0f, 0.1f,  7.0f);
		glVertex3f( 1.0f, 0.1f, -7.0f);
		glEnd();

		glTranslatef(8,0,0);
		glBegin(GL_QUADS);
		glVertex3f(-1.0f, 0.1f, -7.0f);
		glVertex3f(-1.0f, 0.1f,  7.0f);
		glVertex3f( 1.0f, 0.1f,  7.0f);
		glVertex3f( 1.0f, 0.1f, -7.0f);
		glEnd();

	glPopMatrix();
    glPushMatrix();

    glColor3f(.4f, .8f, .8f);

    glRotatef(90,0,1,0);
    glTranslatef(30,0,-15);
	drawcarr();
    glPopMatrix();


    glPushMatrix();

    glColor3f(.3f, .8f, .5f);

    glRotatef(90,0,1,0);
    glTranslatef(30,0,15);
	drawcarr();
    glPopMatrix();




	//Desenha a estrada

	        glPushMatrix();
	        glColor3f(0.8f, .8f, .8f);
	        glScalef(0.2,0.2,0.2);
	        glTranslatef(20,0.5,125);

	            Estrada();
	        glPopMatrix();

	   	 //Desenha a estrada
	   	        glPushMatrix();
	   	     glColor3f(0.8f, .8f, .8f);
	   	        glScalef(0.2,0.2,0.2);
	   	        glTranslatef(20,0.5,160);

	   	            Estrada();
	   	        glPopMatrix();

	        //Desenha arvore redonda

        for (int var = 0; var < 230; var = var + 15) {
	        glPushMatrix();
	        glScalef(0.2,0.2,0.2);
		      	glTranslatef(-70+var,0.5,95);


		            glPopMatrix();
			}
        glPushMatrix();
        glScalef(0.2,0.2,0.2);
    	glTranslatef(90,0.5,30);
        Arvores();
        glPopMatrix();



		glPushMatrix();
		glRotatef(90,1,100,1);
		glTranslatef(20,0,-25);


				glRotatef(30,0,1,0);
				glTranslatef(3.0,0, 0.0);

				glCallList(carr_display_list);
				glPopMatrix();


				//carro torto
				glPushMatrix();
				glRotatef(90,1,100,1);
				glTranslatef(20,0,-25);


						glRotatef(-15,0,5,0);
						glTranslatef(20.0,0, 29.0);

						glCallList(carr_display_list);
						glPopMatrix();






	if(aceleracaoX!=0)
		//aqui eu descubro o angulo tang (aZ/aX) com aceleracao em x != 0
	theta1=( atan (aceleracaoZ/aceleracaoX)*180)/M_PI;
	else if(aceleracaoZ>0)
		//aceleracao em z, faz o calculo com o angulo -90
		theta1=-90.0;

	else
		//aqui quando aceleracaoZ <=0
		theta1=90.0;

	// neste caso o angulo é o angulo atual com sinal invertido
	if(aceleracaoX>0   &&   aceleracaoZ<0 || (aceleracaoX>0    &&   aceleracaoZ>0))
	{

		theta1=-theta1;
	}
	// neste caso eh 180 - o angulo atual, isto eh o angulo calculado ficou maior que 360
	else if(aceleracaoX< 0  && aceleracaoZ<0 || (aceleracaoX<0  &&     aceleracaoZ>0))
	{
		theta1=180-theta1;
	}


	//glLoadIdentity();
				glPushMatrix();
				//com fx e fz eu altero a posicao do carro conforme as teclas
				glTranslatef(fx,0,fz);
				//com o theta1 eu rotaciono o carro no eixo y
				glRotatef(theta1,0,1,0);
				//cor do carro
				glColor3f(1,1,1);
				glCallList(carr_display_list);
				glPopMatrix();



	// Executa os comandos OpenGL

	glutSwapBuffers();
}

// Função usada para especificar a posição do observador virtual
void PosicionaObservador(void)
{
	// Especifica sistema de coordenadas do modelo
	glMatrixMode(GL_MODELVIEW);
	// Inicializa sistema de coordenadas do modelo
	glLoadIdentity();
	// Posiciona e orienta o observador
	glTranslatef(-obsX,-obsY,-obsZ);
	glRotatef(rotX,1,0,0);
	glRotatef(rotY,0,1,0);
}

// Função usada para especificar o volume de visualização
void EspecificaParametrosVisualizacao(void)
{
	// Especifica sistema de coordenadas de projeção
	glMatrixMode(GL_PROJECTION);
	// Inicializa sistema de coordenadas de projeção
	glLoadIdentity();

	// Especifica a projeção perspectiva(angulo,aspecto,zMin,zMax)
	gluPerspective(angle,fAspect,0.5,500);

	PosicionaObservador();
}

// Função callback chamada para gerenciar eventos de teclas normais (ESC)
void Teclado (unsigned char tecla, int x, int y)
{
	if(tecla==27) // ESC ?
		exit(0);

}



// Funç¿o callback para eventos de botões do mouse
void GerenciaMouse(int button, int state, int x, int y)
{
	if(state==GLUT_DOWN)
	{
		// Salva os parâmetros atuais
		x_ini = x;
		y_ini = y;
		obsX_ini = obsX;
		obsY_ini = obsY;
		obsZ_ini = obsZ;
		rotX_ini = rotX;
		rotY_ini = rotY;
		bot = button;
	}
	else bot = -1;
}

// Função callback para eventos de movimento do mouse
#define SENS_ROT	5.0
#define SENS_OBS	10.0
#define SENS_TRANSL	10.0
void GerenciaMovim(int x, int y)
{
	// Botão esquerdo ?
	if(bot==GLUT_LEFT_BUTTON)
	{
		// Calcula diferenças
		int deltax = x_ini - x;
		int deltay = y_ini - y;
		// E modifica ângulos
		rotY = rotY_ini - deltax/SENS_ROT;
		rotX = rotX_ini - deltay/SENS_ROT;
	}
	// Botão direito ?
	else if(bot==GLUT_RIGHT_BUTTON)
	{
		// Calcula diferença
		int deltaz = y_ini - y;
		// E modifica distância do observador
		obsZ = obsZ_ini + deltaz/SENS_OBS;
	}
	// Botão do meio ?
	else if(bot==GLUT_MIDDLE_BUTTON)
	{
		// Calcula diferenças
		int deltax = x_ini - x;
		int deltay = y_ini - y;
		// E modifica posições
		obsX = obsX_ini + deltax/SENS_TRANSL;
		obsY = obsY_ini - deltay/SENS_TRANSL;
	}
	PosicionaObservador();
	glutPostRedisplay();
}

// Função callback chamada quando o tamanho da janela é alterado
void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
	// Para previnir uma divisão por zero
	if ( h == 0 ) h = 1;

	// Especifica as dimensões da viewport
	glViewport(0, 0, w, h);

	// Calcula a correção de aspecto
	fAspect = (GLfloat)w/(GLfloat)h;

	EspecificaParametrosVisualizacao();
}


void drawcarr()
{
	glScalef(2.5f, 2.5f, 2.5f); // deixou o carro mais achatado
glTranslatef(.0,0.8,0.0);
glEnable(GL_BLEND);//TRANCPARENCY1
	 glBlendFunc(GL_ONE, GL_ZERO);//TRANCPARENCY2
   //glColor3f(1.0,1.0,1.0);
  // glBegin(
   //glVertex3f(

glBegin(GL_LINE_LOOP);
	glVertex3f(-1.12,-.48,0.7);//a
	glVertex3f(-0.86,-.48,0.7);//b
	glVertex3f(-.74,-0.2,0.7);//c
	glVertex3f(-.42,-.2,0.7);//d
	glVertex3f(-0.3,-.48,0.7);//e
	glVertex3f(.81,-0.48,0.7);//f
	glVertex3f(.94,-0.2,0.7);//g
	glVertex3f(1.24,-.2,0.7);//h
	glVertex3f(1.38,-.48,0.7);//i
	glVertex3f(1.52,-.44,0.7);//j
	glVertex3f(1.52,.14,0.7);//k
	glVertex3f(1.14,0.22,0.7);//l
	glVertex3f(0.76,.22,0.7);//m
	glVertex3f(.52,0.56,0.7);//n
	glVertex3f(-0.1,0.6,0.7);//0
	glVertex3f(-1.02,0.6,0.7);//p
	glVertex3f(-1.2,0.22,0.7);//q
	glVertex3f(-1.2,-.28,0.7);//r
 glEnd();

glBegin(GL_LINE_LOOP);
	glVertex3f(-1.12,-.48,-0.7);//a'
	glVertex3f(-0.86,-.48,-0.7);//b'
	glVertex3f(-.74,-0.2,-0.7);//c'
	glVertex3f(-.42,-.2,-0.7);//d'
	glVertex3f(-0.3,-.48,-0.7);//e'
	glVertex3f(.81,-0.48,-0.7);//f'
	glVertex3f(.94,-0.2,-0.7);//g'
	glVertex3f(1.24,-.2,-0.7);//h'
	glVertex3f(1.38,-.48,-0.7);//i'
	glVertex3f(1.52,-.44,-0.7);//j'
	glVertex3f(1.52,.14,-0.7);//k'
	glVertex3f(1.14,0.22,-0.7);//l'
	glVertex3f(0.76,.22,-0.7);//m'
	glVertex3f(.52,0.56,-0.7);//n'
	glVertex3f(-0.1,0.6,-0.7);//o'
	glVertex3f(-1.02,0.6,-0.7);//p'
	glVertex3f(-1.2,0.22,-0.7);//q'
	glVertex3f(-1.2,-.28,-0.7);//r'
 glEnd();

glBegin(GL_LINES);
	glVertex3f(-1.12,-.48,0.7);//a
	glVertex3f(-1.12,-.48,-0.7);//a'
	glVertex3f(-0.86,-.48,0.7);//b
	glVertex3f(-0.86,-.48,-0.7);//b'
	glVertex3f(-.74,-0.2,0.7);//c
	glVertex3f(-.74,-0.2,-0.7);//c'
	glVertex3f(-.42,-.2,0.7);//d
	glVertex3f(-.42,-.2,-0.7);//d'
	glVertex3f(-0.3,-.48,0.7);//e
	glVertex3f(-0.3,-.48,-0.7);//e'
	glVertex3f(.81,-0.48,0.7);//f
	glVertex3f(.81,-0.48,-0.7);//f'
	glVertex3f(.94,-0.2,0.7);//g
	glVertex3f(.94,-0.2,-0.7);//g'
	glVertex3f(1.24,-.2,0.7);//h
	glVertex3f(1.24,-.2,-0.7);//h'
	glVertex3f(1.38,-.48,0.7);//i
	glVertex3f(1.38,-.48,-0.7);//i'
	glVertex3f(1.52,-.44,0.7);//j
	glVertex3f(1.52,-.44,-0.7);//j'
	glVertex3f(1.52,.14,0.7);//k
	glVertex3f(1.52,.14,-0.7);//k'
	glVertex3f(1.14,0.22,0.7);//l
	glVertex3f(1.14,0.22,-0.7);//l'
	glVertex3f(0.76,.22,0.7);//m
	glVertex3f(0.76,.22,-0.7);//m'
	glVertex3f(.52,0.56,0.7);//n
	glVertex3f(.52,0.56,-0.7);//n'
	glVertex3f(-0.1,0.6,0.7);//0
	glVertex3f(-0.1,0.6,-0.7);//o'
	glVertex3f(-1.02,0.6,0.7);//p
	glVertex3f(-1.02,0.6,-0.7);//p'
	glVertex3f(-1.2,0.22,0.7);//q
	glVertex3f(-1.2,0.22,-0.7);//q'
	glVertex3f(-1.2,-.28,0.7);//r
	glVertex3f(-1.2,-.28,-0.7);//r'
glEnd();


// top filling
glBegin(GL_POLYGON);
	glVertex3f(-0.1,0.6,0.7);//o
	glVertex3f(-0.1,0.6,-0.7);//o'
	glVertex3f(-1.02,0.6,-0.7);//p'
	glVertex3f(-1.02,0.6,0.7);//p
glEnd();


glBegin(GL_POLYGON);
	glVertex3f(-0.1,0.6,0.7);//o
	glVertex3f(-0.1,0.6,-0.7);//o'
	glVertex3f(.52,0.56,-0.7);//n'
	glVertex3f(.52,0.56,0.7);//n
glEnd();

//back filling
glBegin(GL_POLYGON);
	glVertex3f(-1.2,0.22,0.7);//q
	glVertex3f(-1.2,0.22,-0.7);//q'
	glVertex3f(-1.2,-.28,-0.7);//r'
	glVertex3f(-1.2,-.28,0.7);//r
glEnd();






glBegin(GL_POLYGON);
	glVertex3f(1.52,.14,0.7);//k
	glVertex3f(1.14,0.22,0.7);//l
	glVertex3f(1.14,0.22,-0.7);//l'
	glVertex3f(1.52,.14,-0.7);//k'
glEnd();

glBegin(GL_POLYGON);
	glVertex3f(0.76,.22,0.7);//m
	glVertex3f(0.76,.22,-0.7);//m'
	glVertex3f(1.14,0.22,-0.7);//l'
	glVertex3f(1.14,0.22,0.7);//l
glEnd();

glBegin(GL_POLYGON);
	glVertex3f(-1.12,-.48,0.7);//a
	glVertex3f(-0.86,-.48,0.7);//b
	glVertex3f(-.74,-0.2,0.7);//c
	glVertex3f(-0.64,0.22,0.7);//cc
	glVertex3f(-1.08,0.22,0.7);//dd
	glVertex3f(-1.2,0.22,0.7);//q
	glVertex3f(-1.2,-.28,0.7);//r
glEnd();

glBegin(GL_POLYGON);
glVertex3f(-.74,-0.2,0.7);//c
glVertex3f(-0.64,0.22,0.7);//cc
glVertex3f(-0.5,0.22,0.7);//hh
glVertex3f(-0.5,-0.2,0.7);//pp
glEnd();
glBegin(GL_POLYGON);
glVertex3f(0.0,0.22,0.7);//gg
glVertex3f(1.14,0.22,0.7);//l
glVertex3f(1.24,-.2,0.7);//h
glVertex3f(0.0,-0.2,0.7);//oo



glEnd();
//
glBegin(GL_POLYGON);

	glVertex3f(-1.12,-.48,-0.7);//a'
	glVertex3f(-0.86,-.48,-0.7);//b'
	glVertex3f(-.74,-0.2,-0.7);//c'
	glVertex3f(-0.64,0.22,-0.7);//cc'
	glVertex3f(-1.08,0.22,-0.7);//dd'
	glVertex3f(-1.2,0.22,-0.7);//q'
	glVertex3f(-1.2,-.28,-0.7);//r'
glEnd();

glBegin(GL_POLYGON);

glVertex3f(-.74,-0.2,-0.7);//c'
glVertex3f(-0.64,0.22,-0.7);//cc'
glVertex3f(-0.5,0.22,-0.7);//hh'
glVertex3f(-0.5,-0.2,-0.7);//pp'

glEnd();
glBegin(GL_POLYGON);
glVertex3f(0.0,0.22,-0.7);//gg'
glVertex3f(1.14,0.22,-0.7);//l'
glVertex3f(1.24,-.2,-0.7);//h'
glVertex3f(0.0,-0.2,-0.7);//oo'

glEnd();


glBegin(GL_POLYGON);
glVertex3f(-1.2,0.22,0.7);//q
glVertex3f(-1.08,0.22,0.7);//dd
glVertex3f(-0.98,0.5,0.7);//aa
glVertex3f(-1.02,0.6,0.7);//p
glEnd();


glBegin(GL_POLYGON);
glVertex3f(-1.02,0.6,0.7);//p
glVertex3f(-0.98,0.5,0.7);//aa
glVertex3f(0.44,0.5,0.7);//jj
glVertex3f(.52,0.56,0.7);//n
glVertex3f(-0.1,0.6,0.7);//0
glEnd();

glBegin(GL_POLYGON);
glVertex3f(-0.64,0.5,0.7);//bb
glVertex3f(-0.64,0.22,0.7);//cc
glVertex3f(-0.5,0.22,0.7);//hh
glVertex3f(-0.5,0.5,0.7);//ee
glEnd();

glBegin(GL_POLYGON);
glVertex3f(0.0,0.5,0.7);//ff
glVertex3f(0.0,0.22,0.7);//gg
glVertex3f(0.12,0.22,0.7);//ll
glVertex3f(0.12,0.5,0.7);//ii
glEnd();

glBegin(GL_POLYGON);
glVertex3f(.52,0.56,0.7);//n
glVertex3f(0.44,0.5,0.7);//jj
glVertex3f(0.62,0.22,0.7);//kk
glVertex3f(0.76,.22,0.7);//m
glEnd();

glBegin(GL_POLYGON);
glVertex3f(-.42,-.2,0.7);//d
glVertex3f(.94,-0.2,0.7);//g
glVertex3f(.81,-0.48,0.7);//f
glVertex3f(-0.3,-.48,0.7);//e
glEnd();

glBegin(GL_POLYGON);
glVertex3f(1.14,0.22,0.7);//l
glVertex3f(1.52,.14,0.7);//k
glVertex3f(1.52,-.44,0.7);//j
glVertex3f(1.38,-.48,0.7);//i
glVertex3f(1.24,-.2,0.7);//h
glEnd();

glBegin(GL_POLYGON);
glVertex3f(-1.2,0.22,-0.7);//q'
glVertex3f(-1.08,0.22,-0.7);//dd'
glVertex3f(-0.98,0.5,-0.7);//aa'
glVertex3f(-1.02,0.6,-0.7);//p'
glEnd();

glBegin(GL_POLYGON);
glVertex3f(-1.02,0.6,-0.7);//p'
glVertex3f(-0.98,0.5,-0.7);//aa'
glVertex3f(0.44,0.5,-0.7);//jj'
glVertex3f(.52,0.56,-0.7);//n'
glVertex3f(-0.1,0.6,-0.7);//0'
glEnd();

glBegin(GL_POLYGON);
glVertex3f(-0.64,0.5,-0.7);//bb'
glVertex3f(-0.64,0.22,-0.7);//cc'
glVertex3f(-0.5,0.22,-0.7);//hh'
glVertex3f(-0.5,0.5,-0.7);//ee'
glEnd();

glBegin(GL_POLYGON);
glVertex3f(0.0,0.5,-0.7);//ff'
glVertex3f(0.0,0.22,-0.7);//gg'
glVertex3f(0.12,0.22,-0.7);//ll'
glVertex3f(0.12,0.5,-0.7);//ii'
glEnd();

glBegin(GL_POLYGON);
glVertex3f(.52,0.56,-0.7);//n'
glVertex3f(0.44,0.5,-0.7);//jj'
glVertex3f(0.62,0.22,-0.7);//kk'
glVertex3f(0.76,.22,-0.7);//m'
glEnd();

glBegin(GL_POLYGON);
glVertex3f(-.42,-.2,-0.7);//d'
glVertex3f(.94,-0.2,-0.7);//g'
glVertex3f(.81,-0.48,-0.7);//f'
glVertex3f(-0.3,-.48,-0.7);//e'
glEnd();

glBegin(GL_POLYGON);
glVertex3f(1.14,0.22,-0.7);//l'
glVertex3f(1.52,.14,-0.7);//k'
glVertex3f(1.52,-.44,-0.7);//j'
glVertex3f(1.38,-.48,-0.7);//i'
glVertex3f(1.24,-.2,-0.7);//h'
glEnd();


// door1 body- rear, near
glBegin(GL_POLYGON);
glVertex3f(-0.5,0.22,0.7);//hh
glVertex3f(0.0,0.22,0.7);//gg
glVertex3f(0.0,-0.2,0.7);//oo
glVertex3f(-0.5,-0.2,0.7);//pp
glEnd();

// door body- rear, far
glBegin(GL_POLYGON);
glVertex3f(-0.5,0.22,-0.7);//hh'
glVertex3f(0.0,0.22,-0.7);//gg'
glVertex3f(0.0,-0.2,-0.7);//oo'
glVertex3f(-0.5,-0.2,-0.7);//pp'
glEnd();

// door2  body- near, driver

glBegin(GL_POLYGON);
glVertex3f(0.12,0.22,0.7);//ll
glVertex3f(0.62,0.22,0.7);//kk
glVertex3f(0.62,-0.2,0.7);//mm
glVertex3f(0.12,-0.2,0.7);//nn
glEnd();



// door2  body- far, driver

glBegin(GL_POLYGON);
 glVertex3f(0.12,0.22,-0.7);//ll'
glVertex3f(0.62,0.22,-0.7);//kk'
glVertex3f(0.62,-0.2,-0.7);//mm'
glVertex3f(0.12,-0.2,-0.7);//nn'
glEnd();

glBegin(GL_POLYGON);//front**
	glVertex3f(1.52,.14,0.7);//k
	glVertex3f(1.52,.14,-0.7);//k'
	glVertex3f(1.52,-.44,-0.7);//j'
	glVertex3f(1.52,-.44,0.7);//j
glEnd();

glTranslatef(-.58,-.52,0.7);//translate to 1st tyre
//glColor3f(0.09,0.09,0.09);// tyre color********
glColor3f(1,1,1);// tyre color********
glutSolidTorus(0.12f, .14f, 10, 25);
glTranslatef(1.68,0.0,0.0);//translate to 2nd tyre
glutSolidTorus(0.12f, .14f, 10, 25);

glTranslatef(0.0,0.0,-1.4);//translate to 3rd tyre
glutSolidTorus(0.12f, .14f, 10, 25);
glTranslatef(-1.68,0.0,0.0);//translate to 4th tyre which is behind 1st tyre i.e rear .back
glutSolidTorus(0.12f, .14f, 10, 25);
glTranslatef(.58,.52,0.7);//translate to origin
glRotatef(90.0,0.0,1.0,0.0);
glTranslatef(0.0,0.0,-1.40);

glutSolidTorus(0.2f, .2f, 10, 25);

glTranslatef(0.0,0.0,1.40);
glRotatef(270.0,0.0,1.0,0.0);


//bottom filling
glBegin(GL_POLYGON);
glColor3f(0.25,0.25,0.25);
	glVertex3f(-0.3,-.48,0.7);//e
	glVertex3f(-0.3,-.48,-0.7);//e'
	glVertex3f(.81,-0.48,-0.7);//f'
	glVertex3f(.81,-0.48,0.7);//f
glEnd();




glBegin(GL_POLYGON);
	glVertex3f(-.42,-.2,0.7);//d
	glVertex3f(-.42,-.2,-0.7);//d'
	glVertex3f(-0.3,-.48,-0.7);//e'
	glVertex3f(-0.3,-.48,0.7);//e
glEnd();

glBegin(GL_POLYGON);

glVertex3f(-1.2,-.28,0.7);//r
glVertex3f(-1.2,-.28,-0.7);//r'
glVertex3f(-1.12,-.48,-0.7);//a'
glVertex3f(-1.12,-.48,0.7);//a

glEnd();

glBegin(GL_POLYGON);
	glVertex3f(-1.12,-.48,0.7);//a
	glVertex3f(-1.12,-.48,-0.7);//a'
	glVertex3f(-0.86,-.48,-0.7);//b'
	glVertex3f(-0.86,-.48,0.7);//b
glEnd();

glBegin(GL_POLYGON);
	glVertex3f(-0.86,-.48,0.7);//b
	glVertex3f(-0.86,-.48,-0.7);//b'
	glVertex3f(-.74,-0.2,-0.7);//c'
	glVertex3f(-.74,-0.2,0.7);//c
glEnd();

glBegin(GL_POLYGON);
	glVertex3f(-.74,-0.2,0.7);//c
	glVertex3f(-.74,-0.2,-0.7);//c'
	glVertex3f(-.42,-.2,-0.7);//d'
	glVertex3f(-.42,-.2,0.7);//d
glEnd();

glBegin(GL_POLYGON);
	glVertex3f(.81,-0.48,0.7);//f
	glVertex3f(.81,-0.48,-0.7);//f'
	glVertex3f(.94,-0.2,-0.7);//g'
	glVertex3f(.94,-0.2,0.7);//g
glEnd();

glBegin(GL_POLYGON);
	glVertex3f(.94,-0.2,0.7);//g
	glVertex3f(.94,-0.2,-0.7);//g'
	glVertex3f(1.24,-.2,-0.7);//h'
	glVertex3f(1.24,-.2,0.7);//h
glEnd();

glBegin(GL_POLYGON);
	glVertex3f(1.24,-.2,0.7);//h
	glVertex3f(1.24,-.2,-0.7);//h'
	glVertex3f(1.38,-.48,-0.7);//i'
	glVertex3f(1.38,-.48,0.7);//i
glEnd();

glBegin(GL_POLYGON);
	glVertex3f(1.38,-.48,0.7);//i
	glVertex3f(1.38,-.48,-0.7);//i'
	glVertex3f(1.52,-.44,-0.7);//j'
	glVertex3f(1.52,-.44,0.7);//j
glEnd();




//********************************************************************************************8


// door outline- rear, front
glBegin(GL_LINE_LOOP);
glColor3f(1.0,1.0,1.0);
glVertex3f(-0.5,0.22,0.7);//hh
glVertex3f(0.0,0.22,0.7);//gg
glVertex3f(0.0,-0.2,0.7);//oo
glVertex3f(-0.5,-0.2,0.7);//pp


glEnd();



// door2 outline- near, driver

glBegin(GL_LINE_LOOP);

glVertex3f(0.12,0.22,0.7);//ll
glVertex3f(0.62,0.22,0.7);//kk
glVertex3f(0.62,-0.2,0.7);//mm
glVertex3f(0.12,-0.2,0.7);//nn
glEnd();


glColor3f(0.0,0.0,0.0);
// door2  outline- far, driver

glBegin(GL_LINE_LOOP);

glVertex3f(0.12,0.22,-0.7);//ll'
glVertex3f(0.62,0.22,-0.7);//kk'
glVertex3f(0.62,-0.2,-0.7);//mm'
glVertex3f(0.12,-0.2,-0.7);//nn'
glEnd();

// door outline- rear, far
glBegin(GL_LINE_LOOP);

glVertex3f(-0.5,0.22,-0.7);//hh'
glVertex3f(0.0,0.22,-0.7);//gg'
glVertex3f(0.0,-0.2,-0.7);//oo'
glVertex3f(-0.5,-0.2,-0.7);//pp'


glEnd();
glBegin(GL_POLYGON);//front**
glVertex3f(1.52,.14,0.7);//k
glVertex3f(1.52,.14,-0.7);//k'
glVertex3f(1.52,-.44,-0.7);//j'
glVertex3f(1.52,-.44,0.7);//j

glEnd();

glColor3f(0.0,0.0,1.0);

// transparent objects are placed next ..

 glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);//TRANCPARENCY3

//windscreen
 glBegin(GL_POLYGON);
glColor4f(0.0,0.0,0.0,0.7);   //COLOR =WHITE TRANSPARENT
	glVertex3f(0.562,.5,.6);//AAA
	glVertex3f(.562,.5,-.6);//AAA'
	glVertex3f(.76,.22,-.6);//MMM'
	glVertex3f(.76,.22,.6);//MMM

glEnd();
//rear window
glBegin(GL_POLYGON);
   //COLOR =WHITE TRANSPARENT

	glVertex3f(-1.068,0.5,0.6);//pp
	glVertex3f(-1.068,0.5,-0.6);//pp'
	glVertex3f(-1.2,0.22,-0.6);//qq'
	glVertex3f(-1.2,0.22,0.6);//qq

glEnd();
//leftmost window front
glBegin(GL_POLYGON);
	glVertex3f(-0.98,0.5,0.7);//aa
	glVertex3f(-0.64,0.5,0.7);//bb
	glVertex3f(-0.64,0.22,0.7);//cc
	glVertex3f(-1.08,0.22,0.7);//dd
glEnd();

//leftmost window back
glBegin(GL_POLYGON);

	glVertex3f(-0.98,0.5,-0.7);//aa
	glVertex3f(-0.64,0.5,-0.7);//bb
	glVertex3f(-0.64,0.22,-0.7);//cc
	glVertex3f(-1.08,0.22,-0.7);//dd
glEnd();

//middle window front

glBegin(GL_POLYGON);

glVertex3f(-0.5,0.5,0.7);
glVertex3f(0.0,0.5,0.7);
glVertex3f(0.0,0.22,0.7);
glVertex3f(-0.5,0.22,0.7);

glEnd();




//middle window back

glBegin(GL_POLYGON);

glVertex3f(-0.5,0.5,-0.7);
glVertex3f(0.0,0.5,-0.7);
glVertex3f(0.0,0.22,-0.7);
glVertex3f(-0.5,0.22,-0.7);

glEnd();
//rightmost window front

glBegin(GL_POLYGON);

glVertex3f(0.12,0.5,0.7);//ii
glVertex3f(0.44,0.5,0.7);//jj
glVertex3f(0.62,0.22,0.7);//kk
glVertex3f(0.12,0.22,0.7);//ll


glEnd();


//rightmost window back

glBegin(GL_POLYGON);

glVertex3f(0.12,0.5,-0.7);//ii'
glVertex3f(0.44,0.5,-0.7);//jj'
glVertex3f(0.62,0.22,-0.7);//kk'
glVertex3f(0.12,0.22,-0.7);//ll'


glEnd();


////car code ends here
glColor3f(0.0,0.0,1.0);

}

GLuint createDL() {
	GLuint carrDL;

	// Create the id for the list
	carrDL = glGenLists(1);

	// start list
	glNewList(carrDL,GL_COMPILE);

	// call the function that contains the rendering commands
		drawcarr();

	// endList
	glEndList();

	return(carrDL);
}


// Função responsável por inicializar parâmetros e variáveis
void Inicializa (void)
{
    glPushMatrix();
       glTranslatef(0,0,0);
       DefineIlumincao1();
    glPopMatrix();
	// Define a cor de fundo da janela de visualização como branca
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	// Habilita a definição da cor do material a partir da cor corrente
//		glEnable(GL_COLOR_MATERIAL);
////		//Habilita o uso de iluminação
//		glEnable(GL_LIGHTING);
////		// Habilita as fontes de luz
//		glEnable(GL_LIGHT0);
//		glEnable(GL_LIGHT1);
//		glEnable(GL_LIGHT2);
//   glEnable(GL_DEPTH_TEST);
//	defineLuz();
//	// Habilita o modelo de colorização de Gouraud
//	glShadeModel(GL_SMOOTH);
	carr_display_list = createDL();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

	// Inicializa a variável que especifica o ângulo da projeção
	// perspectiva
	angle=45;

	// Inicializa as variáveis usadas para alterar a posição do
	// observador virtual
	rotX = 30;
	rotY = 0;
	obsX = obsY = 0;
	obsZ = 70;
	//adicionado
	glLineWidth(2.0);

}

// Programa Principal
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	// Define o modo de operação da GLUT
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	// Especifica a posição inicial da janela GLUT
	glutInitWindowPosition(5,5);

	// Especifica o tamanho inicial em pixels da janela GLUT
	glutInitWindowSize(800,800);

	// Cria a janela passando como argumento o título da mesma
	glutCreateWindow("Estacione no mato");

	// Registra a função callback de redesenho da janela de visualização
	glutDisplayFunc(Desenha);

	// Registra a função callback de redimensionamento da janela de visualização
	glutReshapeFunc(AlteraTamanhoJanela);

	// Registra a função callback para tratamento das teclas normais
	glutKeyboardFunc (Teclado);

	// Registra a função callback para tratamento das teclas especiais
//	glutSpecialFunc (TeclasEspeciais);
	glutSpecialFunc (movecar);


	// Registra a função callback para eventos de botões do mouse
	glutMouseFunc(GerenciaMouse);

	// Registra a função callback para eventos de movimento do mouse
	glutMotionFunc(GerenciaMovim);

	// Chama a função responsável por fazer as inicializações
	Inicializa();

	// Inicia o processamento e aguarda interação do usuário
	glutMainLoop();

	return 0;
}

