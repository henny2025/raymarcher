#version 440 core

#define STEP_SIZE 0.1
#define MAX_STEPS 20
#define MIN_HIT_DIST 0.001
#define MAX_TRACE_DIST 101

out vec4 fragColor;
uniform float WindowHeight;

float dist_from_sphere(in vec3 point, in vec3 center, float radius) {
  return length(point - center) - radius;
}

vec3 march(in vec3 point, in vec3 ray) {
  // accumulate travel distance
  float total_distance_traveled = 0.0;

  for (int i = 0; i < MAX_STEPS; ++i) {
    // calculate current poisition along ray
    vec3 current_position = point + total_distance_traveled * ray;

    float distance_to_closest =
        dist_from_sphere(current_position, vec3(0.0), 1.0);
    if (distance_to_closest < MIN_HIT_DIST) {
      return vec3(1.0, 0.0, 0.0);
    }

    if (total_distance_traveled > MAX_TRACE_DIST) {
      break;
    }

    // ray marching algorithm says that we can safely add the distance to the
    // closest object to our current position
    total_distance_traveled += distance_to_closest;
  }
  return vec3(0.0);
}

void main() {
  // normalize coordinates so that our viewport has height 1
  vec2 viewport_coord = gl_FragCoord.xy / WindowHeight - WindowHeight / 2;
  // todo: make camera position mobile. Right now it is at z=5 with the viewport
  // positioned at z=4
  vec3 camera_position = vec3(0.0, 0.0, 5.0);

  vec3 ray = vec3(viewport_coord.xy, 4.0) - camera_position;

  vec3 shaded_color = march(camera_position, ray);

  fragColor = vec4(shaded_color, 1.0);
}
