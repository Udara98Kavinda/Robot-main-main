#ifndef TURNING_H
#define TURNING_H

void turnLeft();
void turnRight();
void turn180(bool left);

void turn180_gyro(float currentHeading); // Accepts current heading for more accurate turns
void turn90(bool clockwise, float currentHeading);



#endif // TURNING_H