#version 440 core

#define STEP_SIZE 0.1
#define MAX_STEPS 20
#define MIN_HIT_DIST 0.001
#define MAX_TRACE_DIST 101

out vec4 fragColor;
uniform vec2 WindowDims;

float dist_from_sphere(in vec3 point, in vec3 center, float radius) {
  return length(point - center) - radius;
}

float map_world(in vec3 point) {
  // generate some interesting distortion geometry
  float displacement = sin(5.0 * point.x) * sin(5.0 * point.y) * sin(5.0 * point.z) * 0.25;
  float sphere_dist = dist_from_sphere(point, vec3(0), 1.0);

  return sphere_dist + displacement;
}

vec3 calculate_normal(in vec3 p)
{
    const vec3 small_step = vec3(0.01, 0.0, 0.0);

    float gradient_x = map_world(p + small_step.xyy) - map_world(p - small_step.xyy);
    float gradient_y = map_world(p + small_step.yxy) - map_world(p - small_step.yxy);
    float gradient_z = map_world(p + small_step.yyx) - map_world(p - small_step.yyx);

    vec3 normal = vec3(gradient_x, gradient_y, gradient_z);

    return normalize(normal);
}

vec3 march(in vec3 point, in vec3 ray) {
  // accumulate travel distance
  float total_distance_traveled = 0.0;

  for (int i = 0; i < MAX_STEPS; ++i) {
    // calculate current poisition along ray
    vec3 current_position = point + total_distance_traveled * ray;

    float distance_to_closest =
        map_world(current_position);
    if (distance_to_closest < MIN_HIT_DIST) {
      vec3 norm = calculate_normal(current_position);

      vec3 light_pos = vec3(-2.0, 5.0, 5.0);

      vec3 direction_to_light = normalize(light_pos - current_position);
      float diffuse_intensity = max(0.0, dot(norm, direction_to_light));
      return vec3(1.0, 0, 0)*diffuse_intensity;
    }

    if (total_distance_traveled > MAX_TRACE_DIST) {
      break;
    }

    // ray marching algorithm says that we can safely add the distance to the
    // closest object to our current position
    total_distance_traveled += distance_to_closest;
  }
  return vec3(0.0, 0.0, 0.0);
}

void main() {
  // normalize coordinates so that our viewport has height 1
  vec2 viewport_coord = vec2(gl_FragCoord.x - WindowDims[0] / 2,
                             gl_FragCoord.y - WindowDims[1] / 2) /
                        WindowDims[1];
  // todo: make camera position mobile. Right now it is at z=5 with the viewport
  // positioned at z=4
  vec3 camera_position = vec3(0.0, 0.0, 5.0);

  vec3 ray = vec3(viewport_coord.xy, 4.0) - camera_position;

  vec3 shaded_color = march(camera_position, ray);

  fragColor = vec4(shaded_color, 1.0);
}
