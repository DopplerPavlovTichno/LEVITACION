##############
## Script listens to serial port and writes contents into a file
##############
## requires pySerial to be installed 
import serial
import matplotlib.pyplot as plt

serial_port = 'COM4';
serial_port = '/dev/cu.usbmodemfa131'
baud_rate = 9600; #In arduino, Serial.begin(baud_rate)
kp = 0.1
ki = 0.01
kd = 0
dt = 100 # en milisegundos
setpoint = 250
write_to_file_path = "output_sp{}_kp{}_ki{}_kd{}.txt".format(setpoint, kp, ki, kd);

output_file = open(write_to_file_path, "w+");
header = 'kp = {}, ki = {}, kd = {}, dt = {} ms, setpoint = {}'.format(kp, ki, kd, dt, setpoint)
print(header)
output_file.write(header)
#ser = serial.Serial(serial_port, baud_rate)
distancia = []
input_actuador = []
cntd = 0
cnti = 0
fig, ax = plt.subplots(2)
#while True:
with serial.Serial(serial_port, baud_rate) as ser:
    while True:
        line = ser.readline();
        line = line.decode("utf-8") #ser.readline returns a binary, convert to string
        print(line);
        if line[0:9] == 'Distancia':
            a = line.split('\r', 1)
            a = a[0]
            a = a.split(' ', 2)
            distancia.append(int(a[2]))
            cntd = cntd + dt
            ax[0].cla()
            ax[0].plot(distancia)
        elif line[0:14] == 'Input actuador':
            a = line.split('\r', 1)
            a = a[0]
            a = a.split(' ', 3)
            input_actuador.append(int(a[3]))
            cnti = cnti + dt
            ax[1].cla()
            ax[1].plot(input_actuador)
        fig.show()
        plt.pause(0.1)
        output_file.write(line);
    
#ser.close() luego de salir del programa.

#%%

data_file = "datos_sp{}_kp{}_ki{}_kd{}.dat".format(setpoint, kp, ki, kd);
np.savetxt(data_file, [np.asarray(distancia), np.asarray(input_actuador)])
#%%

), 
           delimiter=',', header='Distancia (mm), Input actuador (pwm)')
