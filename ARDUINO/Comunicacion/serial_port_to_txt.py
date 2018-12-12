##############
## Script listens to serial port and writes contents into a file
##############
## requires pySerial to be installed 
import serial
import matplotlib.pyplot as plt
import numpy as np
import pandas as pd

serial_port = 'COM5';
#serial_port = '/dev/cu.usbmodemfa131'
baud_rate = 9600; #In arduino, Serial.begin(baud_rate)
kp = 0.1
ki = 0.01
kd = 0.1
dt = 100 # en milisegundos
setpoint = 250
write_to_file_path = "output_sp{}_kp{}_ki{}_kd{}.txt".format(setpoint, kp, ki, kd);
#write_to_file_path = "pwm170.txt"; 

output_file = open(write_to_file_path, "w+");
#header = 'kp = {}, ki = {}, kd = {}, dt = {} ms, setpoint = {}'.format(kp, ki, kd, dt, setpoint)
#print(header)
#output_file.write(header)
distancia = []
input_actuador = []
cntd = 0
cnti = 0

with serial.Serial(serial_port, baud_rate) as ser:
    while True:
        line = ser.readline();
        line = line.decode("utf-8") #ser.readline returns a binary, convert to string
#        print(line);
        try: # decodificando lo que viene del puerto serie para meterlo en listas
            if line[0:9] == 'Distancia':
                a = line.split('\r', 1)
                a = a[0]
                a = a.split(' ', 2)
                distancia.append(int(a[2]))
#                cntd = cntd + dt
#                ax[0].cla()
#                ax[0].plot(distancia)
#                ax[0].axhline(y=setpoint, ls='--', c='r')
            elif line[0:14] == 'Input actuador':
                a = line.split('\r', 1)
                a = a[0]
                a = a.split(' ', 3)
                input_actuador.append(int(a[3]))
#                cnti = cnti + dt
#                ax[1].cla()
#                ax[1].plot(input_actuador)
        except:
            pass
#        fig.show()
#        plt.pause(0.001)
        output_file.write(line);

#%% Guardar
min_len = min(len(distancia), len(input_actuador))
distancia = np.asarray(distancia[:min_len])
input_actuador = np.asarray(input_actuador[:min_len])
df = pd.DataFrame(columns=['Distancia(mm)', 'Input actuador(pwm)'])
df['Distancia(mm)'] = distancia
df['Input actuador(pwm)'] = input_actuador
data_file = "datos_sp{}_kp{}_ki{}_kd{}_perturbacion.dat".format(setpoint, kp, ki, kd)
#data_file = "pwm170.dat"
df.to_csv(data_file)
#%% Figura

fig, ax = plt.subplots(2, figsize=(12, 6))
ax[0].plot(distancia)
ax[0].set_ylabel('Distancia (mm)')
#ax[0].axhline(y=setpoint, ls='--', c='r', label='setpoint')
ax[1].plot(input_actuador)
ax[1].set_ylabel('Input actuador (pwm)')
fig.savefig("datos_sp{}_kp{}_ki{}_kd{}_perturbacion.png".format(setpoint, kp, ki, kd))
#fig.savefig("pwm170.png")
