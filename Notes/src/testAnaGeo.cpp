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
bool rayHitsPoint(const glm::vec2& o, const glm::vec2& v, const glm::vec2& p);
bool pointInSegment(const glm::vec2& a, const glm::vec2& b, const glm::vec2& p);
bool pointInPolygon(const std::vector<glm::vec2>& polygon, const glm::vec2& p);

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
  if (glm::epsilonEqual(glm::distance2(a, b), 0.0f, EPSILON)) {
    // There is no segment it's just a point
    return rayHitsPoint(o, v, a);
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

bool rayHitsPoint(const glm::vec2& o, const glm::vec2& v, const glm::vec2& p) {
  if (glm::epsilonEqual(glm::length(v), 0.0f, EPSILON)) {
    // There is no ray at all
    return false;
  }
  const float s_q = glm::dot(p - o, v) / glm::length2(v);
  // Point is behind the ray cannot be hit
  if (s_q < 0.0f) {
    return false;
  }
  // Project point into ray
  const glm::vec2 q = o + s_q * v;
  // See if the point is the projection
  return glm::epsilonEqual(glm::distance2(p, q), 0.0f, EPSILON);
}

bool pointInSegment(const glm::vec2& a, const glm::vec2& b, const glm::vec2& p) {
  if (glm::epsilonEqual(glm::distance2(a, b), 0.0f, EPSILON)) {
    // There is no segment it's just a point
    return glm::epsilonEqual(glm::distance2(a, p), 0.0f, EPSILON);
  }
  const float s_q = glm::dot((a - p), (b - a)) / glm::length2(b - a);
  if (s_q < 0.0f || s_q > 1.0f) {
    // We cannot be inside: our projection fails outside the segment
    return false;
  }
  // Project point into segment
  const glm::vec2 q = a + s_q * (b - a);
  // See if the point is the projection
  return glm::epsilonEqual(glm::distance2(p, q), 0.0f, EPSILON); 
}

bool pointInPolygon(const std::vector<glm::vec2>& polygon, const glm::vec2& p) {
  if (polygon.size() < 3U) {
    // There is no polygon
    return false;
  }
  // Counter for the number of times the cross an edge
  size_t hitsCount = 0U;
  // Loop trough all the edges
  for (size_t i = 0; i < polygon.size(); ++i) {
    // An edge is form by the current vertice and the next one
    const glm::vec2 a = polygon[i];
    const glm::vec2 b = polygon[(i + 1) % polygon.size()];
    // If we are on the edge we say we are inside and break
    if (pointInSegment(a, b, p)) {
      return true;
    }
    // If this edge it's horizontal skip
    if (glm::epsilonEqual(a.y, b.y, EPSILON)) {
      // Calculate potential intersection
      const float s = (a.x - p.x) * (a.y - b.y) / (a.y - b.y);
      const float t = (a.y - p.y) / (a.y - b.y);
      // See if the ray hits the edge
      if (t >= 0.0f && t <= 1.0f && s >= 0.0f) {
        hitsCount++;
      }  
    }
  }
  // If the number of hits is odd
  return hitsCount % 2U == 1U;
}
