import cv2
from roboflow import Roboflow
import time
import serial.tools.list_ports

rf = Roboflow(api_key="XXXXXXXXXXX")

project = rf.workspace().project("thesis-xjhyc")
model = project.version(1).model

cap = cv2.VideoCapture(0)

last_print_time = 0
print_interval = 2

ports = serial.tools.list_ports.comports()
for num , port in enumerate(ports):
    print(str(num+1)  +": " + port.device)

option = int(input("enter your option of port : "))


option = str(ports[option-1].device)

arduino_port = option
baud_rate = 9600

current_position = 10

print("the initial position is assumed to be 10/20 ")
while True:
    ret, frame = cap.read()
    if not ret:
        print("Failed to capture image")
        break
    small_frame = cv2.resize(frame, (640, 480))

    inference = model.predict(small_frame, confidence=40, overlap=30)

    predictions = inference.json()

    for pred in predictions['predictions']:
        x1 = int(pred['x'])
        width = int(pred['width'])

        rel_x = int(20 - (x1 / (640 / 20))) + 1

        current_time = time.time()
        if current_time - last_print_time >= print_interval and rel_x!= current_position:

            print(f"mouth position x: {rel_x}/20")
            try:

                ser = serial.Serial(arduino_port, baud_rate, timeout=1)
                time.sleep(2)


                ser.write(str(rel_x).encode('utf-8'))


                time.sleep(1)

            except serial.SerialException as e:
                print(f"Error: {e}")
            finally:

                if ser.is_open:
                    ser.close()
            last_print_time = current_time
            current_position = rel_x

    cv2.imshow('Webcam Predictions', frame)

    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cap.release()
cv2.destroyAllWindows()




