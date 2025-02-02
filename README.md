# Estacion-meteorologica-ESP32-BME280
Este repositorio contiene el código fuente desarrollado para un proyecto de estación meteorológica basada en un microcontrolador ESP32. El código obtiene datos ambientales de un sensor BME280, que mide temperatura, presión y humedad, y envía estos datos a la plataforma ThingSpeak para su visualización y análisis. La comunicación con ThingSpeak se realiza mediante solicitudes HTTP.

El repositorio contiene el archivo principal de código "EstacionMetESP32.src" que incluye la configuración de la red WiFi, la inicialización del sensor, la lectura de los datos del sensor y el envío a ThingSpeak. Además a continuación puedes obtener información sobre cómo configurar y probar el proyecto.

Instrucciones básicas para probar el código desarrollado:
1.	Conexión del hardware:
- Conecta el sensor BME280 al ESP32 utilizando las conexiones adecuadas para I2C.
- Asegúrate de tener una conexión estable a Internet para que el ESP32 pueda acceder a la red WiFi y enviar los datos a ThingSpeak.

2.	Configura el entorno de desarrollo:
- Asegúrate de tener Arduino IDE instalado.
- En el Arduino IDE, instala las librerías necesarias:
  - Adafruit BME280: Se puede instalar desde el Administrador de Librerías en el Arduino IDE. Busca “Adafruit BME280” e instala la versión más reciente.
  - WiFi.h y HTTPClient.h: Estas librerías vienen integradas en el entorno de desarrollo para ESP32, por lo que solo necesitas asegurarte de tener instalada la placa ESP32 en el gestor de placas de Arduino IDE.

3.	Configura las credenciales de la red WiFi y la API de ThingSpeak:
- Abre el archivo del código y cambia las siguientes líneas con las credenciales correctas de tu red WiFi:
  - const char* WIFI_SSID = "tu_red_wifi";
  -  const char* WIFI_PASS = "tu_contraseña_wifi";
- También necesitarás una API Key de ThingSpeak. Si no tienes una, crea una cuenta en ThingSpeak y genera una API Key para tu canal de datos. Reemplaza la API Key en el código donde dice:
  - const char* API_KEY = "tu_api_key";

4.	Carga el código al ESP32:
- Conecta el ESP32 a tu computadora a través del puerto USB y selecciona la placa correcta en el IDE de Arduino.
- Compila y carga el código al ESP32. Si todo está correctamente configurado, el dispositivo debería conectarse a la red WiFi y empezar a enviar los datos del sensor BME280 a ThingSpeak.

6.	Visualización de los datos:
- Una vez que el dispositivo esté enviando datos, puedes acceder a tu canal en ThingSpeak para ver los datos en tiempo real y crear gráficos con ellos.

Información adicional:
Si bien el código está optimizado para trabajar con el sensor BME280 y el ESP32, este proyecto puede ampliarse para incluir más sensores o características, como la visualización en una interfaz gráfica o la integración con otros servicios web. Además, este proyecto es completamente personalizable en cuanto a la frecuencia de las mediciones, el formato de los datos y los intervalos de tiempo entre actualizaciones.
Es importante recordar que la plataforma ThingSpeak tiene límites en la cantidad de datos que pueden enviarse de manera gratuita, por lo que se recomienda ajustar los intervalos de tiempo para evitar sobrepasar estos límites en proyectos más grandes.
