#include<iostream>
#include <GL/glut.h>


GLfloat rotate_angle1 = 0.0;
GLfloat dSize = 0.3; //立方体大小
GLfloat translate_x = 0.0f;
GLfloat zoom = 1.0f;
GLfloat winW = 0.0f;//宽度
GLfloat winH = 0.0f;//高度
void myDisplay(void)
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glLoadIdentity();
	//设置光照
	gluLookAt(0.5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	{
		GLfloat light_position[] = { 0.5f,0.0f,0.0f,1.0f };//（xyzw,w为1时代表点光源，为0时代表方向光源）
		GLfloat light_ambient[] = { 0.5f,0.5f,0.5f,1.0f };//环境光
		GLfloat light_diffuse[] = { 1.0f,1.0f,1.0f,1.0f };//漫射光
		GLfloat light_specular[] = { 1.0f,1.0f,1.0f,1.0f };//镜面光
		glLightfv(GL_LIGHT0, GL_POSITION, light_position);
		glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);//光源环境光强值
		glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);//光源漫反射强值
		glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);//光源镜面反射强值
		glEnable(GL_LIGHT0);//打开光源
		glEnable(GL_LIGHTING);//打开光照
		glEnable(GL_COLOR_MATERIAL);//设置光照后需要启动颜色材料模式，才能使模型的颜色起作用
	}

	{
		glRotatef(rotate_angle1, 0.0f, 1.0f, 0.0f);
	}

	glRotatef(rotate_angle1, -0.3, 0.3, -0.3);//旋转点
	glBegin(GL_QUADS);
	//上  
	glColor3f(0.0, 0.0, 1.0);  //蓝
	glNormal3d(0.0, 0.0, 1.0); //上
	glVertex3d(dSize, dSize, dSize);
	glVertex3d(-dSize, dSize, dSize);
	glVertex3d(-dSize, -dSize, dSize);
	glVertex3d(dSize, -dSize, dSize);
	//下  
	glColor3f(0.0, 1.0, 1.0);  //青
	glNormal3d(0.0, 0.0, -1.0);//下
	glVertex3d(dSize, dSize, -dSize);
	glVertex3d(-dSize, dSize, -dSize);
	glVertex3d(-dSize, -dSize, -dSize);
	glVertex3d(dSize, -dSize, -dSize);
	//前  
	glColor3f(1.0, 0.0, 1.0); //紫
	glNormal3d(1.0, 0.0, 0.0);//前
	glVertex3d(dSize, dSize, dSize);
	glVertex3d(dSize, -dSize, dSize);
	glVertex3d(dSize, -dSize, -dSize);
	glVertex3d(dSize, dSize, -dSize);
	//后  
	glColor3f(1.0, 1.0, 0.0);  //黄
	glNormal3d(-1.0, 0.0, 0.0);//后  
	glVertex3d(-dSize, dSize, dSize);
	glVertex3d(-dSize, -dSize, dSize);
	glVertex3d(-dSize, -dSize, -dSize);
	glVertex3d(-dSize, dSize, -dSize);
	//左  
	glColor3f(0.0, 1.0, 0.0);  //绿
	glNormal3d(0.0, -1.0, 0.0);//左  
	glVertex3d(dSize, -dSize, dSize);
	glVertex3d(dSize, -dSize, -dSize);
	glVertex3d(-dSize, -dSize, -dSize);
	glVertex3d(-dSize, -dSize, dSize);
	//右   
	glColor3f(1.0, 0.0, 0.0); //红
	glNormal3d(0.0, 1.0, 0.0);//右  
	glVertex3d(dSize, dSize, dSize);
	glVertex3d(dSize, dSize, -dSize);
	glVertex3d(-dSize, dSize, -dSize);
	glVertex3d(-dSize, dSize, dSize);
	

	rotate_angle1 += 3;//旋转速度
	glEnd();
	glFlush();
}

void OnReshape(int w, int h)//缩放
{
	GLfloat aspectRatio = (GLfloat)w / (GLfloat)h;
	winW = w;
	winH = h;

	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);//将当前矩阵指定为投影矩阵
	glLoadIdentity();
	if (w <= h)
	{
		glOrtho(-3.0f*zoom, 3.0f*zoom, -3.0f*zoom / aspectRatio, 3.0f*zoom / aspectRatio, -10.0f*zoom, 10.0f*zoom);
		//创建一个正射投影矩阵，六个参数，前两个是x轴最小坐标和最大坐标，中间是y轴，最后两个是z轴
	}
	else {
		glOrtho(-3.0f*zoom*aspectRatio, 3.0f*zoom*aspectRatio, -3.0f*zoom, 3.0f*zoom, -10.0f*zoom, 10.0f*zoom);

	}
	glMatrixMode(GL_MODELVIEW);//视图矩阵
	glLoadIdentity();//将当前用户坐标系的原点移到屏幕中心
}



void myIdle(void)
{
	myDisplay();
	Sleep(25);  //减慢旋转速度
}

void OnKeyUpDown(int key, int x, int y)//键盘控制缩放速度
{
	if (key == GLUT_KEY_UP) {
		zoom -= 0.2;

	}
	else if (key == GLUT_KEY_DOWN) {
		zoom += 0.2;
	}
	OnReshape(winW, winH);
	glutPostRedisplay();
}


int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(200, 50);
	glutInitWindowSize(500, 500);
	glutCreateWindow("3d");
	glutDisplayFunc(&myDisplay);
	//glutIdleFunc(&myIdle);
	glutSpecialFunc(OnKeyUpDown);//键盘控制缩放速度
	glutReshapeFunc(OnReshape);//缩放
	glutMainLoop();//循环
	return 0;
}
