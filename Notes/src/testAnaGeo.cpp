#include <cstdlib>

#include <iostream>
#include <vector>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <glm/gtx/norm.hpp>
#include <glm/gtc/epsilon.hpp>

using namespace std;

const float EPSILON = 0.00001f;

double point2LineDistance(const glm::vec3& a, const glm::vec3& b, const glm::vec3& p);
double point2SementDistance(const glm::vec3& a, const glm::vec3& b, const glm::vec3& p);
bool rayIntersectSegment(const glm::vec2& a, const glm::vec2& b, const glm::vec2& o, const glm::vec2& v);

struct Ray {
  glm::vec2 origin;
  glm::vec2 direction;
};

struct Test {
  Ray ray;
  bool expected_result;
};


int main (int argc, char* argv[]) {
  vector<Test> tests = {
    {{glm::vec2(0.0f,   2.0), glm::vec2( 2.0,  1.0)},  true},
    {{glm::vec2(14.0f, 12.0), glm::vec2( 0.0, -1.0)}, false},
    {{glm::vec2(12.0f,  2.0), glm::vec2(-1.0,  1.0)},  true},
    {{glm::vec2(6.0f,   8.0), glm::vec2( 2.0,  0.0)},  true},
    {{glm::vec2(13.0f,  6.0), glm::vec2(-2.0, -1.0)}, false},
    {{glm::vec2(14.0f,  9.0), glm::vec2( 2.0,  1.0)}, false}
  };

  const glm::vec2 a = glm::vec2(4.0f, 4.0f);
  const glm::vec2 b = glm::vec2(12.0f, 8.0f);

  for (auto t : tests) {
    const Ray r = t.ray;
    if (rayIntersectSegment(a, b, r.origin, r.direction) == t.expected_result) {
      cout << "Pass!";
    } else {
      cout << "Fail!";
    }
    cout << endl;
  }

  return EXIT_SUCCESS;
}

double point2LineDistance(const glm::vec3& a, const glm::vec3& b, const glm::vec3& p) {
  const float lenghtSquared = glm::distance2(a, b);
  if (glm::epsilonEqual(lenghtSquared, 0.0f, EPSILON)) {
    return glm::distance(a, p);
  }
  const float s = glm::dot((p - a), (b - a)) / lenghtSquared;
  const glm::vec3 q = a + s * (b - a);
  return glm::distance(p, q);
}

double point2SementDistance(const glm::vec3& a, const glm::vec3& b, const glm::vec3& p) {
  const float lenghtSquared = glm::distance2(a, b);
  if (glm::epsilonEqual(lenghtSquared, 0.0f, EPSILON)) {
    return glm::distance(a, p);
  }
  const float s = glm::clamp(glm::dot((p - a), (b - a)) / lenghtSquared, 0.0f, 1.0f);
  const glm::vec3 q = a + s * (b - a);
  return glm::distance(p, q);
}

bool rayIntersectSegment(const glm::vec2& a, const glm::vec2& b, const glm::vec2& o, const glm::vec2& v) {
  if (glm::epsilonEqual(glm::length(v), 0.0f, EPSILON)) {
    // There is no ray at all
    return false;
  }
  const float det = v.x * (a.y - b.y) - v.y * (a.x - b.x);
  const float det_s = (a.x - o.x) * (a.y - b.y) - (a.y - o.y) * (a.x - b.x);
  const float det_t = v.x * (a.y - o.y) - v.y * (a.x - o.x);
  // Normal case they are not parallel
  if (glm::epsilonNotEqual(det, 0.0f, EPSILON)) {
    const float s = det_s / det;
    const float t = det_t / det;
    if (t >= 0.0f && t <= 1.0f && s >= 0.0f) {
      return true;
    } else {
      return false;
    }
  }
  // If they are parallel but they are not in the same line
  if (glm::epsilonNotEqual(det_s, 0.0f, EPSILON)) {
    return false;
  }
  // They are parallel and in the same line (Check relative position)
  const float s_p = glm::dot(o - a, b - a) / glm::distance2(a, b);
  return s_p <= 1.0f;
}