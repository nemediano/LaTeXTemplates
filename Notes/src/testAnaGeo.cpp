#include <iostream>
#include <cstdlib>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/vec3.hpp>
#include <glm/gtx/norm.hpp>
#include <glm/gtc/epsilon.hpp>

using namespace std;

const float EPSILON = 0.00001f;

double point2LineDistance(const glm::vec3& a, const glm::vec3& b, const glm::vec3& p);
double point2SementDistance(const glm::vec3& a, const glm::vec3& b, const glm::vec3& p);
bool rayIntersectSegment(const glm::vec3& a, const glm::vec3& b, const glm::vec3& o, const glm::vec3& v);

int main (int argc, char* argv[]) {

  return EXIT_SUCCESS;
}


double point2LineDistance(const glm::vec3& a, const glm::vec3& b, const glm::vec3& p) {
  float l2 = glm::distance2(a, b);
  if (glm::epsilonEqual(l2, 0.0f, EPSILON)) {
    return glm::distance(a, p);
  }
  float s = glm::dot((p - a), (b - a)) / l2;
  glm::vec3 q = a + s * (b - a);
  return glm::distance(p, q);
}

double point2SementDistance(const glm::vec3& a, const glm::vec3& b, const glm::vec3& p) {
  float l2 = glm::distance2(a, b);
  if (glm::epsilonEqual(l2, 0.0f, EPSILON)) {
    return glm::distance(a, p);
  }
  float s = glm::max(0.0f, glm::min(1.0f, glm::dot((p - a), (b - a)) / l2));
  glm::vec3 q = a + s * (b - a);
  return glm::distance(p, q);
}

bool rayIntersectSegment(const glm::vec3& a, const glm::vec3& b, const glm::vec3& o, const glm::vec3& v) {
  return true;
}