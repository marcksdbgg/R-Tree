#include <string>
#include <vector>
#include <iostream>
#include "RTree.h"
#include <GL/glut.h>
#include <time.h>

using namespace std;

void print(const int& command, vector<vector<vector<pair<int, int>>>>& objects_n, string& output) {
    output.resize(0);
    output = command;

    switch (command)
    {
        case 0:// OBJECTS
            output += "|" + to_string(objects_n[0].size());
            for (auto& polygon : objects_n[0]) {
                output += "|" + to_string(polygon.size());

                for (auto& point : polygon) {
                    output += "|" + to_string(point.first) + "|" + to_string(point.second);
                }
            }
            break;

        case 1: //MBRS:
            cout<<" number of (objects) :"<< to_string(objects_n.size())<<endl;
            output += "|" + to_string(objects_n.size());
            for (auto& objects : objects_n) {
                output += "|" + to_string(objects.size());
                cout<<" number of polygons :"<< to_string(objects.size())<<endl;
                for (auto& polygon : objects) {
                    output += "|" + to_string(polygon.size());
                    cout<<" number of points :"<< to_string(polygon.size())<<endl;
                    for (auto& point : polygon) {
                        output += "|" + to_string(point.first) + "|" + to_string(point.second);
                        cout<<"   point:"<< to_string(point.first) << " | " << to_string(point.second)<<endl;

                    }
                }
                cout<<endl<<"--------------------"<< endl;
            }
            break;
        default:
            output += "|0";
            break;
    }

    output += "|END";
    //cout<<output;
}

void print_pair(vector<pair<int, int>> output){
    for(auto &x:output)
    {
        cout<<" ( "<<x.first<<" , "<<x.second<< " ) ";
    }
}

RTree rtree; // RTree Global

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    int width, height;
    rtree.GetWindowSize(width, height);

    glColor3f(1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, width, 0, height);

    // Draw RTree
    rtree.DrawTree(rtree.m_root);

    // Draw points
    glColor3f(1.0, 0.0, 0.0);
    glPointSize(5.0f); // Change point size
    for (int i = 0; i < rtree.mObjs.size(); i++)
    {
        for (int j = 0; j < rtree.mObjs[i].size(); j++)
        {
            int x = rtree.mObjs[i][j].first;
            int y = rtree.mObjs[i][j].second;
            float xf = (float)x / (float)rtree.m_unitSize * (float)width;
            float yf = (float)y / (float)rtree.m_unitSize * (float)height;
            glBegin(GL_POINTS);
            glVertex2f(xf, yf);
            glEnd();
        }
    }

    glFlush();
}

int main(int argc, char *argv[])
{
    vector<vector<pair<int, int>>> vpoints;

    // Generate 50 random points
    srand(time(NULL));
    for (int i = 0; i < 100; i++)
    {
        vector<pair<int, int>> points;
        int x1 = rand() % 100;
        int y1 = rand() % 100;
        int x2 = x1 + rand() % (100 - x1);
        int y2 = y1 + rand() % (100 - y1);
        points.push_back(make_pair(x1, y1));
        points.push_back(make_pair(x2, y2));
        vpoints.push_back(points);
    }

    string output;
    vector<vector<vector<pair<int, int>>>> objects_n;

    // Insert the points into the R-Tree
    for (auto &x : vpoints)
    {
        Rect rect = rtree.MBR(x);
        rtree.Insert(rect.m_min, rect.m_max, x);
    }

    // -------------------------- Parte de graficacion --------------------------
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    int width , height;
    rtree.GetWindowSize(width, height);
    glutInitWindowSize(width, height); // tamano de la ventana
    glutCreateWindow("RTree"); // titulo de la ventana
    glClearColor(0.0, 0.0, 0.0, 0.0); // color de fondo
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 500.0, 0.0, 500.0); // modo de proyeccion
    glutDisplayFunc(display); // funcion de dibujo
    glutMainLoop(); // bucle de dibujo

    return 0;
}

