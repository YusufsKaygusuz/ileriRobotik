class LineFollowingRobot {
  private:
    // Pin definitions
    int leftMotorA;
    int leftMotorB;
    int rightMotorA;
    int rightMotorB;
    int rightSensor;
    int leftSensor;

  public:
    // Constructor method
    LineFollowingRobot(int pinLeftMotorA, int pinLeftMotorB, int pinRightMotorA, int pinRightMotorB, int pinLeftSensor, int pinRightSensor) {
      leftMotorA = pinLeftMotorA;
      leftMotorB = pinLeftMotorB;
      rightMotorA = pinRightMotorA;
      rightMotorB = pinRightMotorB;
      leftSensor = pinLeftSensor;
      rightSensor = pinRightSensor;

      // Set motor pins as output
      pinMode(leftMotorA, OUTPUT);
      pinMode(leftMotorB, OUTPUT);
      pinMode(rightMotorA, OUTPUT);
      pinMode(rightMotorB, OUTPUT);

      // Set sensor pins as input
      pinMode(leftSensor, INPUT);
      pinMode(rightSensor, INPUT);
    }

    // Move the robot forward
    void forward() {
      digitalWrite(leftMotorA, HIGH);
      digitalWrite(leftMotorB, LOW);
      digitalWrite(rightMotorA, HIGH);
      digitalWrite(rightMotorB, LOW);
    }

    // Move the robot backward
    void backward() {
      digitalWrite(leftMotorA, LOW);
      digitalWrite(leftMotorB, HIGH);
      digitalWrite(rightMotorA, LOW);
      digitalWrite(rightMotorB, HIGH);
    }

    // Turn the robot right
    void turnRight() {
      digitalWrite(leftMotorA, HIGH);
      digitalWrite(leftMotorB, LOW);
      digitalWrite(rightMotorA, LOW);
      digitalWrite(rightMotorB, HIGH);
    }

    // Turn the robot left
    void turnLeft() {
      digitalWrite(leftMotorA, LOW);
      digitalWrite(leftMotorB, HIGH);
      digitalWrite(rightMotorA, HIGH);
      digitalWrite(rightMotorB, LOW);
    }

    // Stop the robot
    void stop() {
      digitalWrite(leftMotorA, LOW);
      digitalWrite(leftMotorB, LOW);
      digitalWrite(rightMotorA, LOW);
      digitalWrite(rightMotorB, LOW);
    }

    // Read the left sensor value
    int readLeftSensor() {
      return analogRead(leftSensor);
    }

    // Read the right sensor value
    int readRightSensor() {
      return analogRead(rightSensor);
    }
};

// Create a LineFollowingRobot object
LineFollowingRobot robot(3, 5, 6, 9, A1, A0);

void setup() {
  // Start serial communication
  Serial.begin(9600);
}

void loop() {
  // Read sensor values
  int rightSensorValue = robot.readRightSensor();
  int leftSensorValue = robot.readLeftSensor();

  // Print sensor values to serial monitor
  Serial.print("Right Sensor Reading: ");
  Serial.print(rightSensorValue);
  Serial.print(" - Left Sensor Reading: ");
  Serial.println(leftSensorValue);

  // Move according to sensor values
  if (rightSensorValue > 600 && leftSensorValue > 600) {
    robot.forward(); // Go forward when both sensors detect white line
  } else if (rightSensorValue > 600 && leftSensorValue < 600) {
    robot.turnRight(); // Turn right when the right sensor detects black line
  } else if (rightSensorValue < 600 && leftSensorValue > 600) {
    robot.turnLeft(); // Turn left when the left sensor detects black line
  } else {
    robot.stop(); // Stop when both sensors detect black line
  }
  
  // Wait for a bit
  delay(100);
}
