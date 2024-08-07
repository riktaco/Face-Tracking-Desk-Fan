import cv2
import serial
import time

# Initialize serial communication with Arduino
ser = serial.Serial('COM3', 115200) 

# Load the Haar cascade for face detection
face_cascade = cv2.CascadeClassifier(cv2.data.haarcascades + 'haarcascade_frontalface_default.xml')

# Capture video from the webcam
cap = cv2.VideoCapture(0)

while True:
    # Read a frame from the webcam
    ret, frame = cap.read()
    frame = cv2.flip(frame,1)  # Flip the frame horizontally
    if not ret:
        break

    # Convert the frame to grayscale
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

    # Detect faces in the frame
    faces = face_cascade.detectMultiScale(gray, 1.1, 4)

    # Draw rectangle around the faces and send coordinates to Arduino
    for (x, y, w, h) in faces:
        cv2.rectangle(frame, (x, y), (x+w, y+h), (255, 0, 0), 2)

        # Calculate the center of the face
        center_x = x + w // 2

        # frame.shape[1] is the width of the frame, map the center_x to an angle between 0 and 180
        angle = int((center_x / frame.shape[1]) * 180)

        # Send the angle to Arduino
        ser.write(str(angle).encode())
        print(angle)

        # Wait for 1 second
        time.sleep(1)

    # Display the resulting frame
    cv2.imshow('Face Tracking', frame)

    # Break the loop on 'q' key press
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# Release the capture and close windows
cap.release()
cv2.destroyAllWindows()
ser.close()
