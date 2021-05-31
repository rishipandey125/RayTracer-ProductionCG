#pragma once

//smallest value of x y and z
float compute_smallest(float x, float y, float z) {
  float smallest = x;
  if (y < smallest)
    smallest = y;
  if (z < smallest)
    smallest = z;
  return smallest;
}

//largest value of x y and z
float compute_largest(float x, float y, float z) {
  float largest = x;
  if (y > largest)
    largest = y;
  if (z > largest)
    largest = z;
  return largest;
}

//smallest value of x y z and w
float compute_smallest(float x, float y, float z, float w) {
  float smallest = x;
  if (y < smallest)
    smallest = y;
  if (z < smallest)
    smallest = z;
  if (w < smallest)
    smallest = w;
  return smallest;
}

//largest value of x y z and w
float compute_largest(float x, float y, float z, float w) {
  float largest = x;
  if (y > largest)
    largest = y;
  if (z > largest)
    largest = z;
  if (w > largest)
    largest = w;
  return largest;
}
