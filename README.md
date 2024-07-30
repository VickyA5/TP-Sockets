# Taller de Programacion - TP Sockets

El presente trabajo práctico aborda la comunicación entre un solo cliente y un servidor respecto de los combos del juego Jazz Jackrabbit. Se comunican a través de sockets, cuya implementación es la dada por la cátedra:

[Repositorio de Sockets de la cátedra](https://github.com/eldipa/sockets-en-cpp)

## Compilacion

Desde el root del proyecto

`make`

Esto generara los ejecutables
## Uso

* Para ejecutar el servidor

`./server <puerto>`
* Para ejecutar el cliente

`./client <hostname> <servicio>`

## Modelo

![img](https://www.plantuml.com/plantuml/png/TL9DJyCm3BtdLqGxROBz0mv3Eu4q2J71TN9JRvYbIUKu4n_QVoUZJMaAzEJusS_Fprq50PROMFL2DMfiMddN8C9KHS7GPGsniQYKQi4SuO1wTkS4UGyVEg5F8GAJdsdzgPJMna88Ucq9dMo0NChgz5qrAPulKdnMunBCEBwYYG8yNtHlQbgcXlZM6F8EGz6xWHOoqFVxIj0XFuFrtDUUHueVs8ittdOwIva3bgMu4m7lO3mvfHaDLSGxnj1630Bzc4osHJuXbsIvQyAMXvHaKysFM1TgjzuSKR9X0LqDrexKdT9pe1dnt4Syz7iNOgds_C-99bNPc21GMJJ8E-CTlf5tatCb09mKo_vcM_kcylbkv0IvPHJuENKLztlaQttXoicEwNknv8k-MIxrOBKQeal-xz-phCccABL2LyV6VW40)

El trabajo se dividió en dos partes:

### Cliente

El cliente es quien se encarga de leer las acciones ingresadas por el usuario. Las mismas son enviadas al servidor mediante ClientProtocolo (quien se comunica con el socket) con el protocolo establecido por el juego. Se utiliza a MapaAcciones para mapear el string de una accion a su valor hexadecimal.

Luego, recibe la respuesta del servidor e imprime por pantalla las acciones que recibió.


![img](https://www.plantuml.com/plantuml/png/ZP91Ynin38Nl_XK-UcZsNeObREcvK2ZqEcWyIiUDRGLPJc2N_lVQdYIJPYaRyC6Idj_x47v90YmvUAMiXvJqL-ym2ketfNKvdywrcIb9X80RdP2FpZhgwXX_eyq2R5hbme5TS3o0BOA8oOnvjyErxjIVkw3lJ4AMF5qIdnAo0-zUWStrMQ-FQ8NuERiedmVPQhN2NIt-2ncF3cwWl8i8RS9etLXu6TCXOn8mQvITWRShxpSum9UpmvKrt3HxdIFnX8pJKFhFIQQ-Jy8k_jheWhrjo3GAHkIVu8bDf30oBWRT6lM3x1xbJIths4jVdzUxzPHmwlL8v6kz24sPwYBhccJU3-K-40yxSDvqBNKHtksdthgRwJ-zX75A5D1C853qhnjzWZGi1Ds5g2xm-82ike7t3vXzh09hyI2cD1RkvZzdcUWKpKodXjyUcRRJouz-shxxS-g-KKLdr_UZ6b3cjnz1gHUCKmx-Bm00)

_Diagrama de clases de Cliente_

### Servidor

Servidor se encarga de recibir las acciones enviadas por el cliente. Le delega la comunicación con el socket a ServidorProtocolo. ServidorCombos es quien interpreta las acciones para identificar combos y devolver las acciones interpretadas.

Antes de finalizar el programa, Servidor imprime por pantalla la cantidad de acciones realizadas.



![img](https://www.plantuml.com/plantuml/png/hLFjgjim3FsVf_1FXwKlS1dbZli2Wpr0K1oryUfOGNRIIyVUVN8Iz-FcGiSO5Ef8HqVdsD9hYC1nx5rH60SXg1_8ass9rQz2AVbzoG7jgMyOQp0uH910cR8ezOr3WrmRylXkoUloHLaVKzRs0zlUIWvyb4eZQGowB7v_RFUTAP8XHxdlBfLyMoiouGwkWGbD9FvgEk1zaNfjc3uNp6XiO_ac9iasAR_uyPC5hXd3C2PlUeuUCRw97Dj2coLbbnidRzALmjK6JE0lmjYCXmEojhx5zqe5Uy4wAhEIbWafRCW3OnJqpx4Vz59IgRKcAwvlm1P2fUulQaFay13_2r5d_vq7Zen7o7UkbxzAjH3f0tpb5cGSmPNh2Dxho4spcCTkZtEXxbw7p0bZVfHmYjUHCeu2jY-g8NBfUq5goIg1bJEaEzLohedh0rYdosNW5c178NheiL81UKgdyYxx40lesq0zQd4EWhzKwWoXNXJSjeRHJ4zWcGsS-mkovoWmQKcq11RTCtytnfRENXoUP_bpqRAyUTZLRhzTuM8JKRj4TCNc9VaCkCyAYbVnD_Rk3m00)

_Diagrama de clases de Servidor_


## Diagramas de secuencia

### Cliente
![img](https://www.plantuml.com/plantuml/png/ZP91IpCn48RFNtv5JcKNsky7z22jjU1542k2fp1DHfcQPCeaMz5VxzPTubgMnTl2FFEyxmxvfrOfW-GcU1M0eh6UC6RKYokzwJwN6WzecvQgQhMv7DyBPxRikSNYYK0CM4iSCLMU8aAjBhZHrOH2uEaJP6Bh3ewmxkLBpVkC4UK9F4lLPTPgYEZ5M99bHw_SCMCXExPlcC-DeWFlgzBCyNy76QfwhZC4YCHpFNjfq5WKQQUrcZoEeAKzYH5CnmRJMJGLt-AdS_oip_hPc-lhvyVjpjnkrpVRXxR3EoHZFITqfeV_P2x2yblxZup9z4L_YmF610SS4G_VIL4EBr6c58v2OVG4-Eqfxw-NPQLM65qJ_1S0)

_Diagrama de secuencia un caso de uso de cliente_


### Servidor

<img src="Diagramas/img_9.png" width="700" height="500">

_Imagen 5 ->  Diagrama de secuencia servidor inicia comunicacion_
