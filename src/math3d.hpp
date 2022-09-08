#pragma once

#ifndef MATH3D_H
#define MATH3D_H

#define lmin(a, b) (a < b ? a : b)
#define lmax(a, b) (a > b ? a : b)
#define lrad(a) (a * M_PI / 180)
#define ldeg(a) (a * 180 / M_PI)

#define _USE_MATH_DEFINES

#include <iostream>
#include <math.h>

namespace loli {
	class vec2;
	class vec3;
	class quaternion;
	class mat4;
	
	template<unsigned int T>
	class vec {
		protected:
			float m[T];
		
		public:
			inline vec() { }
			
			inline float length() {
				float d = 0.0f;
				
				for (int i = 0; i < T; i++)
					d += m[i] * m[i];
				
				return sqrt(d);
			}

			inline void print() {
				for (int i = 0; i < T; i++)
					std::cout << m[i] << ", ";

				std::cout << std::endl;
			}
			
			inline float& operator[](unsigned int i) { return m[i]; }
			inline float operator[](unsigned int i) const { return m[i]; }
	};
	
	class vec2 : public vec<2> {
		public:
			vec2(float x = 0.0f, float y = 0.0f) {
				m[0] = x;
				m[1] = y;
			}
			
			inline float dot(vec2 v) {
				return get_x() * v.get_x() + get_y() * v.get_y();
			}
			
			inline vec2 normalize() {
				return (*this) / length();
			}
			
			inline vec2 rotate(float dir) {
				float c = cos(dir);
				float s = sin(dir);
				
				float x = get_x();
				float y = get_y();
				
				return vec2(x * c - y * s, x * s + y * c);
			}
			
			inline float get_x() { return m[0]; }
			inline float get_y() { return m[1]; }
			
			inline vec2 set_x(float v) { m[0] = v; return *this; }
			inline vec2 set_y(float v) { m[1] = v; return *this; }
			
			inline vec2 operator+(vec2 v) 	{ return vec2(m[0] + v[0], m[1] + v[1]); }
			inline vec2 operator-(vec2 v) 	{ return vec2(m[0] - v[0], m[1] - v[1]); }
			inline vec2 operator*(vec2 v) 	{ return vec2(m[0] * v[0], m[1] * v[1]); }
			inline vec2 operator/(vec2 v) 	{ return vec2(m[0] / v[0], m[1] / v[1]); }
			
			inline vec2 operator+(float f)	{ return vec2(m[0] + f, m[1] + f); }
			inline vec2 operator-(float f)	{ return vec2(m[0] - f, m[1] - f); }
			inline vec2 operator*(float f)	{ return vec2(m[0] * f, m[1] * f); }
			inline vec2 operator/(float f)	{ return vec2(m[0] / f, m[1] / f); }
			
			inline void operator+=(vec2 v)  { m[0] += v[0]; m[1] += v[1]; }
			inline void operator-=(vec2 v)  { m[0] -= v[0]; m[1] -= v[1]; }
			inline void operator*=(vec2 v)  { m[0] *= v[0]; m[1] *= v[1]; }
			inline void operator/=(vec2 v)  { m[0] /= v[0]; m[1] /= v[1]; }
	};
	
	class vec3 : public vec<3> {
		public:
			vec3(float x = 0.0f, float y = 0.0f, float z = 0.0f) {
				m[0] = x;
				m[1] = y;
				m[2] = z;
			}
			
			vec3(vec2 v, float z) {
				m[0] = v.get_x();
				m[1] = v.get_y();
				m[2] = z;
			}
			
			inline float dot(vec3 v) {
				return get_x() * v.get_x() + get_y() * v.get_y() + get_z() * v.get_z();
			}

			inline vec3 normalize() {
				float d = length();
				
				return d == 0 ? loli::vec3() : (*this) / d;
			}
			
			inline vec3 rotate(float angle) {
				float c = (float) cos(angle);
				float s = (float) sin(angle);
				
				return vec3(
					m[0] * c - m[1] * s,
					m[0] * s + m[1] * c
				);
			}
			
			inline vec3 cross(vec3 v) {
				float x = get_y() * v.get_z() - get_z() * v.get_y();
				float y = get_z() * v.get_x() - get_x() * v.get_z();
				float z = get_x() * v.get_y() - get_y() * v.get_x();
				
				return vec3(x, y, z);
			}
			
			inline float get_x() { return m[0]; }
			inline float get_y() { return m[1]; }
			inline float get_z() { return m[2]; }
			
			inline vec3 set_x(float v) { m[0] = v; return *this; }
			inline vec3 set_y(float v) { m[1] = v; return *this; }
			inline vec3 set_z(float v) { m[2] = v; return *this; }
			
			inline vec3 operator+(vec3 v) 	{ return vec3(m[0] + v[0], m[1] + v[1], m[2] + v[2]); }
			inline vec3 operator-(vec3 v) 	{ return vec3(m[0] - v[0], m[1] - v[1], m[2] - v[2]); }
			inline vec3 operator*(vec3 v) 	{ return vec3(m[0] * v[0], m[1] * v[1], m[2] * v[2]); }
			inline vec3 operator/(vec3 v) 	{ return vec3(m[0] / v[0], m[1] / v[1], m[2] / v[2]); }
			
			inline vec3 operator+(float f)	{ return vec3(m[0] + f, m[1] + f, m[2] + f); }
			inline vec3 operator-(float f)	{ return vec3(m[0] - f, m[1] - f, m[2] - f); }
			inline vec3 operator*(float f)	{ return vec3(m[0] * f, m[1] * f, m[2] * f); }
			inline vec3 operator/(float f)	{ return vec3(m[0] / f, m[1] / f, m[2] / f); }
			
			inline void operator+=(vec3 v)  { m[0] += v[0]; m[1] += v[1]; m[2] += v[2]; }
			inline void operator-=(vec3 v)  { m[0] -= v[0]; m[1] -= v[1]; m[2] -= v[2]; }
			inline void operator*=(vec3 v)  { m[0] *= v[0]; m[1] *= v[1]; m[2] *= v[2]; }
			inline void operator/=(vec3 v)  { m[0] /= v[0]; m[1] /= v[1]; m[2] /= v[2]; }
			
			inline void operator+=(float f) { m[0] += f; m[1] += f; m[2] += f; }
			inline void operator-=(float f) { m[0] -= f; m[1] -= f; m[2] -= f; }
			inline void operator*=(float f) { m[0] *= f; m[1] *= f; m[2] *= f; }
			inline void operator/=(float f) { m[0] /= f; m[1] /= f; m[2] /= f; }
	};
	
	class vec4 : public vec<4> {
		public:
			vec4(float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 0.0f) {
				m[0] = x;
				m[1] = y;
				m[2] = z;
				m[2] = w;
			}
			
			inline float get_x() { return m[0]; }
			inline float get_y() { return m[1]; }
			inline float get_z() { return m[2]; }
			inline float get_w() { return m[3]; }
			
			inline vec4 set_x(float v) { m[0] = v; return *this; }
			inline vec4 set_y(float v) { m[1] = v; return *this; }
			inline vec4 set_z(float v) { m[2] = v; return *this; }
			inline vec4 set_w(float v) { m[3] = v; return *this; }
			
			inline vec4 operator+(vec4 v) 	{ return vec4(m[0] + v[0], m[1] + v[1], m[2] + v[2], m[3] + v[3]); }
			inline vec4 operator-(vec4 v) 	{ return vec4(m[0] - v[0], m[1] - v[1], m[2] - v[2], m[3] - v[3]); }
			inline vec4 operator*(vec4 v) 	{ return vec4(m[0] * v[0], m[1] * v[1], m[2] * v[2], m[3] * v[3]); }
			inline vec4 operator/(vec4 v) 	{ return vec4(m[0] / v[0], m[1] / v[1], m[2] / v[2], m[3] / v[3]); }
			
			inline vec4 operator+(float f)	{ return vec4(m[0] + f, m[1] + f, m[2] + f, m[3] + f); }
			inline vec4 operator-(float f)	{ return vec4(m[0] - f, m[1] - f, m[2] - f, m[3] - f); }
			inline vec4 operator*(float f)	{ return vec4(m[0] * f, m[1] * f, m[2] * f, m[3] * f); }
			inline vec4 operator/(float f)	{ return vec4(m[0] / f, m[1] / f, m[2] / f, m[3] / f); }
			
			inline void operator+=(vec4 v)  { m[0] += v[0]; m[1] += v[1]; m[2] += v[2]; m[3] += v[3]; }
			inline void operator-=(vec4 v)  { m[0] -= v[0]; m[1] -= v[1]; m[2] -= v[2]; m[3] -= v[3]; }
			inline void operator*=(vec4 v)  { m[0] *= v[0]; m[1] *= v[1]; m[2] *= v[2]; m[3] *= v[3]; }
			inline void operator/=(vec4 v)  { m[0] /= v[0]; m[1] /= v[1]; m[2] /= v[2]; m[3] /= v[3]; }
			
			inline void operator+=(float f) { m[0] += f; m[1] += f; m[2] += f; m[3] += f; }
			inline void operator-=(float f) { m[0] -= f; m[1] -= f; m[2] -= f; m[3] -= f; }
			inline void operator*=(float f) { m[0] *= f; m[1] *= f; m[2] *= f; m[3] *= f; }
			inline void operator/=(float f) { m[0] /= f; m[1] /= f; m[2] /= f; m[3] /= f; }
	};
	
	class mat4 {
		public:
			float m[16];
			
			inline mat4 identity() {
				m[0]	= 1;	m[1]	= 0;	m[2]	= 0;	m[3]	= 0;
				m[4]	= 0;	m[5]	= 1;	m[6]	= 0;	m[7]	= 0;
				m[8]	= 0;	m[9]	= 0;	m[10]	= 1;	m[11]	= 0;
				m[12]	= 0;	m[13]	= 0;	m[14]	= 0;	m[15]	= 1;
				
				return *this;
			}
			
			inline mat4 perspective(float ar, float fov, float n, float f) {
				m[0]	= 1 / (ar * tan(fov / 2));	m[1]	= 0;				m[2]	= 0;					m[3]	= 0;
				m[4]	= 0;						m[5]	= 1 / tan(fov / 2);	m[6]	= 0;					m[7]	= 0;
				m[8]	= 0;						m[9]	= 0;				m[10]	= (-n - f) / (n - f);	m[11]	= (2 * f * n) / (n - f);
				m[12]	= 0;						m[13]	= 0;				m[14]	= 1;					m[15]	= 0;
				
				return *this;
			}
			
			inline mat4 ortho(float l, float r, float t, float b, float n, float f) {
				m[0]	= 2 / (r - l);	m[1]	= 0;			m[2]	= 0;			m[3]	= -(r + l) / (r - l);
				m[4]	= 0;			m[5]	= 2 / (t - b);	m[6]	= 0;			m[7]	= -(t + b) / (t - b);
				m[8]	= 0;			m[9]	= 0;			m[10]	= -2 / (f - n);	m[11]	= -(f + n) / (f - n);
				m[12]	= 0;			m[13]	= 0;			m[14]	= 0;			m[15]	= 1;
				
				return *this;
			}
			
			inline mat4 isometric(float l, float r, float t, float b, float n, float f) {
				m[0]	= 2 / (r - l);	m[1]	= 0;			m[2]	= 0;			m[3]	= -(r + l) / (r - l);
				m[4]	= 0;			m[5]	= 2 / (t - b);	m[6]	=  2 / (f - n);	m[7]	= -(t + b) / (t - b);
				m[8]	= 0;			m[9]	= 0;			m[10]	= -2 / (f - n);	m[11]	= -(f + n) / (f - n);
				m[12]	= 0;			m[13]	= 0;			m[14]	= 0;			m[15]	= 1;
				
				return *this;
			}
			
			inline mat4 translate(vec3 v) {				
				m[0]	= 1;	m[1]	= 0;	m[2]	= 0;	m[3]	= v.get_x();
				m[4]	= 0;	m[5]	= 1;	m[6]	= 0;	m[7]	= v.get_y();
				m[8]	= 0;	m[9]	= 0;	m[10]	= 1;	m[11]	= v.get_z();
				m[12]	= 0;	m[13]	= 0;	m[14]	= 0;	m[15]	= 1;
				
				return *this;
			}
			
			inline mat4 rotate_z(float angle) {
				float c = (float) cos(angle);
				float s = (float) sin(angle);
				
				m[0]	= c;	m[1]	= -s;	m[2]	= 0;	m[3]	= 0;
				m[4]	= s;	m[5]	=  c;	m[6]	= 0;	m[7]	= 0;
				m[8]	= 0;	m[9]	=  0;	m[10]	= 1;	m[11]	= 0;
				m[12]	= 0;	m[13]	=  0;	m[14]	= 0;	m[15]	= 1;
				
				return *this;
			}
			
			inline mat4 scale(vec3 v) {				
				m[0]	= v.get_x();	m[1]	= 0;			m[2]	= 0;			m[3]	= 0;
				m[4]	= 0;			m[5]	= v.get_y();	m[6]	= 0;			m[7]	= 0;
				m[8]	= 0;			m[9]	= 0;			m[10]	= v.get_z();	m[11]	= 0;
				m[12]	= 0;			m[13]	= 0;			m[14]	= 0;			m[15]	= 1;
				
				return *this;
			}
			
			inline float get(int i) {
				return m[i];
			}
			
			inline void set(int i, float v) {
				m[i] = v;
			}
			
			inline mat4 operator*(mat4 r) {
				mat4 result;
				
				for (int i = 0; i < 4; i++) {
					for (int j = 0; j < 4; j++) {
						float sum = 0.0f;
						
						for (int k = 0; k < 4; k++)
							sum += m[i * 4 + k] * r.m[j + k * 4];
						
						result.m[i * 4 + j] = sum;
					}
				}
				
				return result;
			}
			
			inline void print() {
				for (int i = 0; i < 16; i++) {
					std::cout << m[i];
					
					if (i % 4 == 3)
						std::cout << std::endl;
					else
						std::cout << ", ";
				}
				
				std::cout << std::endl;
			}
	};
}

#endif