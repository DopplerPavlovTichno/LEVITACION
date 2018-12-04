import numpy as np
import matplotlib.pyplot as plt

tau_1 = 2 # tiempo caracteristico de respuesta de la altura ante un salto tipo escalon en la frecuencia de la PWM
tau_2 = 0.01 # no lo voy a usar, lo desprecio frente a tau_1 

# valores criticos (no tiene en cuenta histeresis)
pwm_lower = 100 # abajo de este valor el objeto se cae hasta el fondo
pwm_upper = 230 # arriba de este valor llega a lo mas alto que puede (seguir aumentando pwm no lo sube mas)

d_lower = 40 # distancia medida cuando el objeto esta en el punto mas bajo posible
d_upper = 4 # distancia medida cuando el objeto esta en el punto mas alto posible
alpha = 1 # exponente en la relacion frecuencia de PWM - altura
dt_sensor = 0.1 # tiempo entre lecturas del sensor (en segundos)
#dt_actuador = 1 # por si el dt del actuador fuese distinto 
n = 2000 # pasos de la iteracion
memoria = -1 # memoria del termino integral (debe ser entero, si no es positivo, integra todo el error, si es positivo, integra solamente "memoria" terminos. Si "memoria" es mayor o igual al numero de iteraciones actua igual que si tuviera memoria infinita)

# respuesta ante impulso

def d(t, d0, deq): # distancia al sensor como funcion de la distancia inicial d0, la distancia de equilibrio deq y el tiempo t
    r = d0 + (deq - d0) * (1 - np.exp(-t / tau_1))
    return r

# altura de equilibrio en funcion del nivel de pwm

def deq(pwm):
    if pwm > pwm_upper:
        r = d_upper
    elif pwm < pwm_lower:
        r = d_lower
    else:
        m = (d_upper - d_lower) / (pwm_upper**alpha - pwm_lower**alpha)
        r = (d_lower - m * pwm_lower**alpha) + m * pwm**alpha
    return r

# grafico "calibracion" de altura de equilibrio contra nivel de pwm

pwm = []
ds = []

for p in range(256):
    pwm.append(p)
    ds.append(deq(p))
    
#plt.plot(pwm, ds)

def G(outPID): # funcion que agarra la salida del PID y devuelve la entrada al actuador
    if outPID < 0:
        in_actuador = 255
    elif outPID > 255:
        in_actuador = 0
    else:
        in_actuador = 255 - outPID
    return in_actuador

# inicio el algoritmo de PID

kp = 10
ki = 1
kd = 0
d_inicial = d_lower # arranca desde abajo de todo (pegado al ventilador)
setpoint = 20
integral = 0
lastError = 0
errors = []

def PID(d, sp, integral, lastError, cnt = 1):
    error = sp - d
    integral = integral + error * dt_sensor
    derivative = (error - lastError) / dt_sensor
    if memoria > 0:
        errors.append(error)
        if cnt > memoria:
            errors.pop(0)
        integral = sum(errors) * dt_sensor
    r = kp * error + ki * integral + kd * derivative
    lastError = error
    cnt = cnt + 1
    return r, integral, lastError, cnt

lecturas_sensor = []
salidas_PID = []
seniales_actuador = []
lectura_sensor = d_inicial
lecturas_sensor.append(lectura_sensor)
integral_inicial = 0
lastError = 0
tiempo = []
setpoints = []
cnt = 1

for i in range(n):
    tiempo.append(dt_sensor*i)
    setpoints.append(setpoint)
    [output_PID, integral, lastError, cnt] = PID(lecturas_sensor[i], setpoint, integral, lastError, cnt)
    salidas_PID.append(output_PID)
    senial_actuador = G(output_PID)
    seniales_actuador.append(senial_actuador)
    lectura_sensor = d(dt_sensor, lectura_sensor, deq(senial_actuador))
    lecturas_sensor.append(lectura_sensor)

tiempo.append(dt_sensor * n)
setpoints.append(setpoint)

plt.figure(1)
plt.plot(tiempo,lecturas_sensor)
plt.plot(tiempo,setpoints)

# casos interesantes: kp = 1, ki = 0.1, kd = 0, tau_1 = 0.5, dt_sensor = 1
# kp = 1, ki = 0.1, kd = 0, tau_1 = 0.5, pero con dt_sensor = 0.01 (error esteacionario)
# kp = 10, ki = 1000, kd = 0, tau_1 = 0.5, dt_sensor = 0.01
# tanto en los casos en que dt_sensor << tau_1 como si dt_sensor > tau_1 se encuentran valores de las constantes que hacen que el sistema converja al valor de equilibrio, pero los valores de las constantes son muy distintos en cada caso
