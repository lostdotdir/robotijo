import serial
import time
import pyautogui
import requests

arduino = serial.Serial(port='COM7', baudrate=115200, timeout=.1)
# Leer el contenido de la página web
url = "https://tiebot2.vergolini.repl.co/"
response = requests.get(url)
content = response.text
previous_content = response.text


while True:    
    # Leer el contenido actual de la página web con tiempo de espera
    time.sleep(60)
    response = requests.get(url)
    current_content = response.text
    
    # Comparar el contenido actual con el contenido anterior
    if current_content != previous_content:
        # Enviar el contenido actual por el puerto serie
        arduino.write(current_content.encode())
        print(current_content)
        
        # Actualizar el contenido anterior con el contenido actual
        previous_content = current_content
