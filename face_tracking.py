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
        # Send the horizontal coordinate to Arduino
        angle = int((center_x / frame.shape[1]) * 180)
        ser.write(bytes(str(angle), 'utf-8'))
        print(center_x)
        time.sleep(1)  # Wait for a short period to prevent overwhelming the serial buffer

    # Display the resulting frame
    cv2.imshow('Face Tracking', frame)

    # Break the loop on 'q' key press
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# Release the capture and close windows
cap.release()
cv2.destroyAllWindows()
ser.close()
