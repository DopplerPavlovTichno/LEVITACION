##############
## Script listens to serial port and writes contents into a file
##############
## requires pySerial to be installed 
import serial

serial_port = 'COM4';
baud_rate = 9600; #In arduino, Serial.begin(baud_rate)
kp = 10
ki = 0.1
kd = 1000
dt = 1 # en milisegundos
write_to_file_path = "output.txt";

output_file = open(write_to_file_path, "w+");
header = 'kp = {}, ki = {}, kd = {}, dt = {} ms'.format(kp, ki, kd, dt)
print(header)
output_file.write(header)
ser = serial.Serial(serial_port, baud_rate)
while True:
    line = ser.readline();
    line = line.decode("utf-8") #ser.readline returns a binary, convert to string
    print(line);
    output_file.write(line);
#ser.close() luego de salir del programa
