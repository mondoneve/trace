#define GLEW_STATIC
#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include"Recorder.h"
#include<vector>
#include<stack>
#include<queue>
#include<iterator>
#include<fstream>
#include<iostream>

using namespace std;

void key_callback(GLFWwindow* window, int key, int scannode, int action, int mode) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) glfwSetWindowShouldClose(window, GL_TRUE);
}

void main() {
  ofstream out("out.txt");
  ofstream outRays("outRays.txt");
  double rayFrontCoordinateX = -1.3;
  double coeffInside = 1.33;
  double coeffOutside = 1.0;
  double aSize = 1.0;
  double bSize = 1.0;
  double angle = 0.0;
  int numOfRays = 100000;
  double weight = 1.0;
  double waveLength = 1.0;
  int maxReflections = 5;
  double resolution = 1;
  double distanceRecorder = 1.3;
  int totalRays = 0;

  vector<Ray> rayFront(numOfRays);
  Vector directionForRays(1.0, 0.0, 0.0);
  for (int i = 0; i < numOfRays; i++) {
    Point startingPoing(rayFrontCoordinateX, bSize - 2*bSize*i/numOfRays, 0.0);
    Ray thisRay(startingPoing, directionForRays, weight, 0.0, 0, waveLength);
    rayFront[i] = thisRay;
  }

  Recorder globalRecorder(resolution, distanceRecorder, coeffOutside);
  int recorderIdx = 0;
  for (int ang = 0; ang < 1; ang++) {
    CellModel cm(coeffInside, coeffOutside, aSize, bSize, 0.0);
    for (vector<Ray>::iterator r = rayFront.begin(); r != rayFront.end(); r++, recorderIdx++) {
      queue<Ray> raysToRun;
      stack<Ray> raysToCount;
      if(Intersection::isIntersect(*r, cm)) raysToRun.push(*r);
      while (!raysToRun.empty()) {
        Ray currentRay = raysToRun.front();
        if (currentRay.getReflectCounter() < maxReflections && currentRay.getWeight() > VERY_SMALL)
          if (Intersection::isIntersect(currentRay, cm)) {
            Intersection intersection(currentRay, cm);
            Ray refl = intersection.getReflected();
            Ray refr = intersection.getRefracted();
            raysToRun.push(refl);
            raysToRun.push(refr);
          /*if (cm.intersectsWith(*r)) raysToRun.push(*r);
          while (!raysToRun.empty()) {
            Ray currentRay = raysToRun.front();
            if (currentRay.getReflectCounter() < maxReflections && currentRay.getWeight() > VERY_SMALL)
            if (cm.intersectsWith(currentRay)) {
              Ray refl = cm.reflectRay(currentRay);
              Ray refr = cm.refractRay(currentRay);
              raysToRun.push(refl);
              raysToRun.push(refr);*/
            }
          else {
            raysToCount.push(currentRay);
          }
          raysToRun.pop();
      }
      while (!raysToCount.empty()) {
        globalRecorder.recordRay(raysToCount.top());
        raysToCount.pop();
        totalRays++;
      }
    }
  }
  
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
  GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", nullptr, nullptr);
  if (window == nullptr) {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return;
  }
  glfwMakeContextCurrent(window);
  glewExperimental = GL_TRUE;
  if (glewInit() != GLEW_OK) {
    cout << "Failed to initialize glew" << endl;
    return;
  }
  glfwSetKeyCallback(window, key_callback);
  int width, height;
  glfwGetFramebufferSize(window, &width, &height);
  glViewport(0, 0, width, height);
  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();
    glClearColor(0.2f, 0.2f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(window);
  }
  glfwTerminate();


  cout << "TR = " << totalRays;
  out.clear();
  vector<double> res(360 / resolution);
  double max = 0.0;
  for (int i = 0; i < 360 / resolution; i++) { res[i] = globalRecorder.getRec(i)*globalRecorder.getRec(i); if (res[i] > max) max = res[i]; }
  for (int i = 0; i < 360 / resolution; i++) { out << i * resolution << " " << 1512.65808417017 * res[i] / res[0] << endl; }
}
