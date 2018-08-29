#pragma config(Sensor, dgtl7,  sonarSensorInput, sensorSONAR_cm)
#pragma config(Motor,  port8,           leftMotor,     tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port9,           rightMotor,    tmotorServoContinuousRotation, openLoop, reversed)

void forward(){
	motor[leftMotor] = 34;
	motor[rightMotor] = 30;
}

void stopMotors(){
	motor[leftMotor] = 0;
	motor[rightMotor] = 0;
	wait1Msec(1200);
}

void turnLeft(){
	motor[leftMotor] = -26;
	motor[rightMotor] = 30;
	wait1Msec(560);
}

void turnRight(){
	motor[leftMotor] = 30;
	motor[rightMotor] = -26;
	wait1Msec(570);
}

task main(){
	float distanciaDerecha = 0;
	float distanciaIzquierda = 0;
	float distanciaFrente = 0;

	while (true){
		distanciaFrente = SensorValue[sonarSensorInput];
		if(distanciaFrente > 0){
			if (distanciaFrente <= 25){
				stopMotors();
				turnRight();
				distanciaDerecha = SensorValue[sonarSensorInput];
				turnLeft();
				turnLeft();
				distanciaIzquierda = SensorValue[sonarSensorInput];
				turnRight();

				if (distanciaDerecha > 2) {
					if(distanciaDerecha > distanciaIzquierda){
						turnRight();
					}
				}
				else if (distanciaDerecha > 2) {
					if(distanciaIzquierda > distanciaDerecha){
						turnLeft();
					}
				}
				else {
					turnRight();
					turnRight();
				}
			}
			else {
				forward();
			}
		}
	}
}
