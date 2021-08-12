#include <cstdlib>
#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>
 //memberikan fileheader yang dibutuhkan
GLuint texture[35];

GLint slices = 35;
GLint stacks = 35;

using namespace std;
static float ypos = 0, zpos = 0, xpos = 0,a = -9, b = -5,c =-30, kulkas1=0, kulkas2=0, jKiri=0, jKanan=0, lKanan=0, lKiri=0, oven=0, pintu=0;
int z=0;

struct Image {
        unsigned long sizeX;
        unsigned long sizeY;
        char *data;
};
typedef struct Image Image; //struktur data untuk
//ukuran image #bisa di set sesuai kebutuhan
#define checkImageWidth 164
#define checkImageHeight 164

GLubyte checkImage[checkImageWidth][checkImageHeight][3];
//mengambil gambar BMP
int ImageLoad(char *filename, Image *image) {
        FILE *file;
        unsigned long size; // ukuran image dalam bytes
        unsigned long i; // standard counter.
        unsigned short int plane; // number of planes in image

        unsigned short int bpp; // jumlah bits per pixel
        char temp; // temporary color storage for var warna sementara untuk memastikan filenya ada


        if ((file = fopen(filename, "rb")) == NULL) {
                printf("File Not Found : %s\n", filename);
                return 0;
        }
        // mencari file header bmp
        fseek(file, 18, SEEK_CUR);
        // read the width
        if ((i = fread(&image->sizeX, 4, 1, file)) != 1) {
                printf("Error reading width from %s.\n", filename);
                return 0;
        }
        //printf("Width of %s: %lu\n", filename, image->sizeX);
        // membaca nilai height
        if ((i = fread(&image->sizeY, 4, 1, file)) != 1) {
                printf("Error reading height from %s.\n", filename);
                return 0;
        }
        //printf("Height of %s: %lu\n", filename, image->sizeY);
        //menghitung ukuran image(asumsi 24 bits or 3 bytes per pixel).

        size = image->sizeX * image->sizeY * 3;
        // read the planes
        if ((fread(&plane, 2, 1, file)) != 1) {
                printf("Error reading planes from %s.\n", filename);
                return 0;
        }
        if (plane != 1) {
                printf("Planes from %s is not 1: %u\n", filename, plane);
                return 0;
        }
        // read the bitsperpixel
        if ((i = fread(&bpp, 2, 1, file)) != 1) {
                printf("Error reading bpp from %s.\n", filename);

                return 0;
        }
        if (bpp != 24) {
                printf("Bpp from %s is not 24: %u\n", filename, bpp);
                return 0;
        }
        // seek past the rest of the bitmap header.
        fseek(file, 24, SEEK_CUR);
        // read the data.
        image->data = (char *) malloc(size);
        if (image->data == NULL) {
                printf("Error allocating memory for color-corrected image data");
                return 0;
        }
        if ((i = fread(image->data, size, 1, file)) != 1) {
                printf("Error reading image data from %s.\n", filename);
                return 0;
        }
        for (i = 0; i < size; i += 3) { // membalikan semuan nilai warna (gbr - > rgb)
                temp = image->data[i];
                image->data[i] = image->data[i + 2];
                image->data[i + 2] = temp;
        }
        // we're done.
        return 1;
}
//mengambil tekstur
void init(void)
{
    glClearColor(0.5, 0.5, 0.5, 0.0);
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);

        // Generate texture/ membuat texture background
}

//fungsi kotak kosong, belum diisi koordinat. diisi di display()
void kotak(float x1,float y1,float z1,float x2,float y2,float z2)
{
        //depan
        glTexCoord2f(0.0, 0.0);
        glVertex3f(x1,y1,z1);
        glTexCoord2f(0.0, 1.0);
        glVertex3f(x2,y1,z1);
        glTexCoord2f(1.0, 1.0);
        glVertex3f(x2,y2,z1);
        glTexCoord2f(1.0, 0.0);
        glVertex3f(x1,y2,z1);
        //atas
        glTexCoord2f(0.0, 0.0);
        glVertex3f(x1,y2,z1);
        glTexCoord2f(0.0, 1.0);
        glVertex3f(x2,y2,z1);
        glTexCoord2f(1.0, 1.0);
        glVertex3f(x2,y2,z2);
        glTexCoord2f(1.0, 0.0);
        glVertex3f(x1,y2,z2);
        //belakang
        glTexCoord2f(0.0, 0.0);
        glVertex3f(x1,y2,z2);
        glTexCoord2f(0.0, 1.0);
        glVertex3f(x2,y2,z2);
        glTexCoord2f(1.0, 1.0);
        glVertex3f(x2,y1,z2);
        glTexCoord2f(1.0, 0.0);
        glVertex3f(x1,y1,z2);
        //bawah
        glTexCoord2f(0.0, 0.0);
        glVertex3f(x1,y1,z2);
        glTexCoord2f(1.0, 0.0);
        glVertex3f(x2,y1,z2);
        glTexCoord2f(1.0, 1.0);
        glVertex3f(x2,y1,z1);
        glTexCoord2f(0.0, 1.0);
        glVertex3f(x1,y1,z1);
        //samping kiri
        glTexCoord2f(0.0, 0.0);
        glVertex3f(x1,y1,z1);
        glTexCoord2f(1.0, 0.0);
        glVertex3f(x1,y2,z1);
        glTexCoord2f(1.0, 1.0);
        glVertex3f(x1,y2,z2);
        glTexCoord2f(0.0, 1.0);
        glVertex3f(x1,y1,z2);
        //samping kanan
        glTexCoord2f(0.0, 0.0);
        glVertex3f(x2,y1,z1);
        glTexCoord2f(1.0, 0.0);
        glVertex3f(x2,y2,z1);
        glTexCoord2f(1.0, 1.0);
        glVertex3f(x2,y2,z2);
        glTexCoord2f(0.0, 1.0);
        glVertex3f(x2,y1,z2);
}


void keyboard(unsigned char key, int x, int y)
{
        switch (key)
        {
                //putar arah jarum jam (menambah derajat putaran)
                case 'z':
                ypos=ypos+5;
                if (ypos>360) ypos=0;
                glutPostRedisplay();
                break;
                //putar berlawanan arah jarum jam (mengurangi derajat putaran)
                case 'x':
                ypos=ypos-5;
                if (ypos>360) ypos=0;
                glutPostRedisplay();
                break;
                //vertikal bawah (menambah koordinat y)
                case 's':
                b = b + 1;
                glutPostRedisplay();
                break;
                //vertikal atas (mengurangi koordinat y)
                case 'w':
                b = b - 1;
                glutPostRedisplay();
                break;
                //horisontal kiri (mengurangi koordinat x)
                case 'a':
                a = a + 1;
                glutPostRedisplay();
                break;
                //horisontal kanan (menambah koordinat x)
                case 'd':
                a = a - 1;
                glutPostRedisplay();
                break;
                //memperbesar objek (menambah koordinat z)
                case 'q':
                c = c + 1;
                glutPostRedisplay();
                break;
                //memperkecil abjek(mengurangi koordinat z)
                case 'e':
                c = c - 1;
                glutPostRedisplay();
                break;


                //buka pintu kulkas atas
                case 'n':
                kulkas1=kulkas1-5;
                if (kulkas1<-100) kulkas1=-100;
                glutPostRedisplay();
                break;
                //tutup pintu kulkas atas
                case 'm':
                kulkas1=kulkas1+5;
                if (kulkas1>0) kulkas1=0;
                glutPostRedisplay();
                break;
                //buka pintu kulkas bawah
                case 'k':
                kulkas2=kulkas2-5;
                if (kulkas2<-100) kulkas2=-100;
                glutPostRedisplay();
                break;
                //tutup pintu kulkas bawah
                case 'l':
                kulkas2=kulkas2+5;
                if (kulkas2>0) kulkas2=0;
                glutPostRedisplay();
                break;

                //buka jendela kiri
                case '1':
                jKiri=jKiri+5;
                if (jKiri<-0) jKiri=-1;
                glutPostRedisplay();
                break;
                //tutup jendela kiri
                case '2':
                jKiri=jKiri-5;
                if (jKiri<-0) jKiri=-0;
                glutPostRedisplay();
                break;
                //buka jendela kanan
                case '3':
                jKanan=jKanan+5;
                if (jKanan<-0) jKanan=-1;
                glutPostRedisplay();
                break;
                //tutup jendela kanan
                case '4':
                jKanan=jKanan-5;
                if (jKanan<-0) jKanan=-0;
                glutPostRedisplay();
                break;

                //buka oven
                case '9':
                oven=oven+5;
                if (oven<-0) oven=-1;
                glutPostRedisplay();
                break;
                //tutup oven
                case '0':
                oven=oven-5;
                if (oven<-0) oven=-0;
                glutPostRedisplay();
                break;

                //buka pintu lemari kiri
                case 'u':
                lKiri=lKiri-5;
                if (lKiri<-100) lKiri=-100;
                glutPostRedisplay();
                break;
                //tutup pintu lemari kiri
                case 'i':
                lKiri=lKiri+5;
                if (lKiri>0) lKiri=0;
                glutPostRedisplay();
                break;
                //buka pintu lemari kanan
                case 'o':
                lKanan=lKanan+5;
                if (lKanan<-100) lKanan=-100;
                glutPostRedisplay();
                break;
                //tutup pintu lemari kanan
                case 'p':
                lKanan=lKanan-5;
                if (lKanan<0) lKanan=0;
                glutPostRedisplay();
                break;

                //buka pintu
                case 't':
                pintu=pintu-5;
                if (pintu>100) pintu=100;
                glutPostRedisplay();
                break;
                //tutup pintu
                case 'y':
                pintu=pintu+5;
                if (pintu>0) pintu=0;
                glutPostRedisplay();
                break;

                //putar arah jarum jam (menambah derajat putaran)
                case '[':
                xpos=xpos+5;
                if (xpos>360) xpos=0;
                glutPostRedisplay();
                break;
                //putar berlawanan arah jarum jam (mengurangi derajat putaran)
                case ']':
                xpos=xpos-5;
                if (xpos>360) xpos=0;
                glutPostRedisplay();

        }
}
void display()
{
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity ();
        glEnable(GL_DEPTH_TEST);
        //perpindahan
        glTranslatef(a,b,c);
        //putaran
        glRotatef(xpos,1,0,0);
        glRotatef(ypos,0,1,0);
        glRotatef(zpos,0,0,1);
//lantai
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, texture[1]);
                glBegin(GL_QUADS);
                    glColor3ub(70, 78, 240);
                        kotak(0,0,18,25,0.5,0);
                glEnd();
        glPopMatrix();
//dinding kiri
        glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, texture[2]);
                glBegin(GL_QUADS);
                    glColor3ub(104, 109, 212);
                        kotak(0,0.5,18,0.5,10,0);
                glEnd();
        glPopMatrix();
//dinding belakang
        glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, texture[2]);
                glBegin(GL_QUADS);
                    glColor3ub(104, 109, 212);
                        kotak(0.5,0.5,0.5,25,10,0.0);
                glEnd();
        glPopMatrix();
   //meja
    //atas
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, texture[2]);
                glBegin(GL_QUADS);
                    glColor3ub(68, 71, 148);
                        kotak(21,3.5,16,24.8,3.8,9.5);
                //kaki kanan belakang
                        kotak(24.3,0.5,15.9,24.6,3.6,15.6);
                //kaki kiri belakang
                        kotak(24.3,0.5,9.9,24.6,3.6,9.6);
                //kaki kiri depan
                        kotak(21.1,0.5,9.9,21.4,3.6,9.6);
                //kaki kanan depan
                        kotak(21.1,0.5,15.9,21.4,3.6,15.6);
                glEnd();
        glPopMatrix();

        //pc
        glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, texture[2]);
                glBegin(GL_QUADS);
                    glColor3ub(97, 97, 87);

                        //Monitor lcd
            kotak(23.3,3.8,15.0,23.4,5.3,13.0);
            //keyboard
            kotak(23.3,3.8,15.0,22,4,13.0);
        glEnd();
        glPopMatrix();
        //layar lcd
        glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, texture[8]);
                glBegin(GL_QUADS);
                    glColor3ub(242, 242, 235);
                        kotak(23.29,4.05,15.0,23.30,5.2,13.1);
                glEnd();
        glPopMatrix();
        //kursi
        //alas
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, texture[3]);
                glBegin(GL_QUADS);
                    glColor3ub(68, 71, 148);
                        kotak(18,2.2,15.5,20.8,2.5,12.8);
            //kiri depan
                        kotak(20.5,0.5,15.5,20.8,2.5,15.2);
            //kanan depan
                        kotak(20.5,0.5,13.1,20.8,2.5,12.8);
            //kanan belakang
                        kotak(18,0.5,13.1,18.3,5.2,12.8);
                //kiri belakang
                        kotak(18,0.5,15.5,18.3,5.2,15.2);
            //senderan
                        kotak(18,3.8,15.5,18.2,4.9,12.8);
                glEnd();
        glPopMatrix();

        //kasur
        //rangka alas
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, texture[2]);
                glBegin(GL_QUADS);
                    glColor3ub(142, 148, 126);
                        kotak(1.1,1.4,15.5,13.4,3,8.7);
                        //kaki 1
                        kotak(0.5,0.5,15.6,1.2,6,14.9);
                //kaki 2
                        kotak(0.5,0.5,9.4,1.1,6,8.7);
                //kaki 3
                        kotak(12.9,0.5,9.4,13.6,5,8.7);
                //kaki 4
                        kotak(12.9,0.5,15.6,13.6,5,14.9);
                //penyangga depan
                        kotak(0.6,3,15.4,1,5.1,8.9);
                //penyangga belakang
                        kotak(12.9,1.4,15.4,13.6,4.5,8.9);
                glEnd();
        glPopMatrix();
        //kasurnya
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, texture[1]);
                glBegin(GL_QUADS);
                    glColor3ub(127, 200, 240);
                        kotak(1.1,2.5,15.4,13.4,3.5,9);
                        //bantal
                    glColor3ub(219, 31, 200);
                        kotak(1.3,3.5,14.4,4,4,10);
                        //selimut
                        glColor3ub(227, 179, 222);
                        kotak(5,3.5,15.4,13.4,3.7,9);
                        //kanan
                        kotak(5,3,9,13.4,3.6,8.9);
                        //kiri
            kotak(5,3,15.5,13.4,3.6,15.4);
                glEnd();
        glPopMatrix();


        glFlush();
        glutSwapBuffers();
}

void reshape (int w, int h)
{

    glViewport(0, 0, w, h);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(60.0, 1.0 * (GLfloat) w / (GLfloat) h, 1.0, 40.0);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glTranslatef(0.0, 0.0, 0.0);
        gluLookAt (0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize (1024, 600);
    glutInitWindowPosition (20, 75);
    glutCreateWindow ("kamar tidur");

    init ();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
return 0;
}
