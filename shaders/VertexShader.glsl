#version 330

layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_normal;
layout(location = 2) in vec2 v_coord;
layout(location = 3) in vec3 v_color;

// Uniform properties
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform vec4 CarPos;

// Output
// TODO(student): Output values to fragment shader
out vec3 f_position;
out vec3 f_normal;
out vec2 f_coord;
out vec3 f_color;


void main()
{
    f_position = v_position;
    f_color = v_color;
    f_normal = v_normal;
    f_coord = v_coord;
  
    gl_Position = Projection * View * Model * vec4(v_position,1.0);
    vec4 car = CarPos - gl_Position;
    gl_Position[1] = gl_Position[1] - (car[0] * car[0] + car[1] * car[1] + car[2] * car[2] + car[3] * car[3]) * 0.01;
}
