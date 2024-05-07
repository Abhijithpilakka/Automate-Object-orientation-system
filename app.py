import cv2
import numpy as np
import serial
from keras.models import load_model
import time

# Disable scientific notation for clarity
np.set_printoptions(suppress=True)

# Load the model
model = load_model("keras_Model_new.h5", compile=False)

# Load the labels
with open("labels_new.txt", "r") as file:
    class_names = file.readlines()

# CAMERA can be 0 or 1 based on the default camera of your computer
camera = cv2.VideoCapture(1)

# Initialize PySerial
ser = serial.Serial('COM17', 9600)  # Change 'COM1' to the appropriate port and baud rate

while True:
    # Grab the webcam's image.
    ret, image = camera.read()

    # Resize the raw image to (224-height, 224-width) pixels
    image = cv2.resize(image, (224, 224), interpolation=cv2.INTER_AREA)

    # Show the image in a window
    cv2.imshow("Webcam Image", image)

    # Make the image a numpy array and reshape it to the model's input shape
    image = np.asarray(image, dtype=np.float32).reshape(1, 224, 224, 3)

    # Normalize the image array
    image = (image / 127.5) - 1

    # Predict the model
    prediction = model.predict(image)
    index = np.argmax(prediction)
    class_name = class_names[index].strip()  # Remove leading/trailing whitespaces
    confidence_score = prediction[0][index]

    # # Print prediction and confidence score
    # print("Class:", class_name, end="")
    # print("Confidence Score:", str(np.round(confidence_score * 100))[:-2], "%")

    # Listen to the keyboard for presses
    keyboard_input = cv2.waitKey(1)

    # 27 is the ASCII for the esc key on your keyboard
    if keyboard_input == 27:
        break

    # Check if "Start" command is received via PySerial
    if ser.in_waiting > 0:
        command = ser.readline().decode().strip()
        if command == "Start":
            print("Start command received. Waiting for 10 seconds before sending class name...")
            time.sleep(10)  # Delay for 10 seconds
            
            ser.write(class_name.encode())  # Send class name
            print("Sending class name:", class_name)
camera.release()
cv2.destroyAllWindows()
