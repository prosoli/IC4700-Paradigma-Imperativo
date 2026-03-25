# IC4700 - I Proyecto - Paradiga Imperativo  

**Curso:** Lenguajes de Programación  
**Semestre:** Primer Semestre 2026  
**Institución:** Tecnológico de Costa Rica – Escuela de Ingeniería en Computación  

## Integrantes

| Carné       | Nombre completo                   | 
|-------------|-----------------------------------|
| 2024089174  | Carol Araya Conejo                |
| 2023332718  | Priscilla Romero Barquero         |
| 2024253434  | Angélica Cabrera Bermúdez         |
| 2023282470  | Daniel Sequeira Requenes          |

---
### [Repositorio de Github](https://github.com/prosoli/IC4700-Paradigma-Imperativo)

# Pasos de Instalación  

<details>
  <summary>Desplegar información</summary>

## 1) Requisitos previos

Antes de ejecutar el sistema, asegúrate de tener:

### Recomendación principal (entorno sugerido)

Se recomienda trabajar con:

- Visual Studio Code
- WSL (Windows Subsystem for Linux)
- Extensión oficial de VS Code: `WSL` (Microsoft)

Motivo:

- Permite abrir y ejecutar el proyecto Linux dentro de Windows con mejor compatibilidad para `g++`, `make` y sockets.

### Instalación de WSL y extensión de VS Code

1. Instala WSL en Windows (PowerShell como administrador):

```powershell
wsl --install
```

2. Reinicia la computadora cuando lo solicite Windows.

3. Abre la terminal de Ubuntu (u otra distro instalada) y actualiza paquetes:

```bash
sudo apt update && sudo apt upgrade -y
```

4. Instala herramientas de compilación:

```bash
sudo apt install -y build-essential gdb make
```

5. Instala Visual Studio Code en Windows desde su sitio oficial.

6. Instala la extensión en VS Code:
  - Nombre: `WSL`
  - Publicador: `Microsoft`
  - También aparece como `Open any folder in the Windows Subsystem for Linux...`

7. Abre el proyecto con WSL desde VS Code:
  - `Ctrl + Shift + P`
  - Ejecuta `WSL: Connect to WSL`
  - Luego `File > Open Folder...` y abre la carpeta del repositorio dentro de WSL (`/mnt/c/...` o ruta Linux).

8. Verifica que VS Code esté en sesión WSL:
  - Esquina inferior izquierda debe mostrar `WSL: <distro>`

Con esto tendrás el entorno recomendado para compilar y ejecutar este proyecto.

- Sistema operativo: Linux, macOS o Windows con WSL
- Compilador: `g++`
- Herramienta de compilación: `make`
- Git (opcional, para clonar/actualizar)

Verificación rápida:

```bash
g++ --version
make --version
```

## 2) Descargar o abrir el proyecto

Si ya lo tienes localmente:

```bash
cd IC4700-Paradigma-Imperativo
```

Si necesitas clonarlo:

```bash
git clone https://github.com/prosoli/IC4700-Paradigma-Imperativo.git
cd IC4700-Paradigma-Imperativo
```

## 3) Compilar

```bash
cd Proyecto
make
```

Este comando genera:

- `build/servidor`
- `build/cliente`

Si quieres recompilar desde cero:

```bash
make clean
make
```

## 4) Ejecutar servidor y cliente

Abre dos terminales diferentes.

Terminal 1 (Servidor):

```bash
cd Proyecto
./build/servidor
```

Terminal 2 (Cliente):

```bash
cd Proyecto
./build/cliente
```

## 5) Recomendación para Windows

- Usar WSL para evitar incompatibilidades de sockets.
- Ejecutar siempre desde la carpeta `Proyecto`.

  </details>  
  
# Manual de usuario  

<details>
  <summary>Desplegar información</summary>

## Guía rápida

### Paso 1: Levantar el servidor

Descripción:
Este paso inicia el motor principal del sistema. El servidor queda escuchando solicitudes del cliente y habilita también el menú administrativo local para gestionar productos, órdenes y mesas.

1. Ejecuta `./build/servidor`.
2. Verás el panel principal del restaurante.

### Paso 2: Crear catálogo de productos

Descripción:
Aquí defines el menú base del restaurante. Los productos que no estén registrados en este catálogo no podrán agregarse a una orden, por lo que conviene completar este paso antes de usar el cliente.

1. En el servidor, entra a `Productos`.
2. Agrega cada producto con su precio.
3. Verifica que se muestre en la lista.

Paso a paso sugerido:

1. Selecciona la opción `2. Agregar un producto` dentro del menú de productos.
2. Escribe el nombre exactamente como deseas que lo usen en cliente (ejemplo: `Pizza`).
3. Escribe el precio numérico (ejemplo: `3500`).
4. Repite hasta completar el catálogo mínimo del día.
5. Usa `1. Listar productos` para confirmar que todo quedó bien escrito.

Recomendación práctica:

- Evita nombres casi iguales para el mismo producto (ejemplo: `Pizza`, `pizza `, `PIZZA`) para no confundir al personal al tomar órdenes.

Importante:

- Si un producto no existe, el servidor no permitirá usarlo en una orden.

### Paso 3: Configurar mesas

Descripción:
En este punto ajustas la capacidad operativa del restaurante. El número de mesas sirve como referencia para la creación y organización de órdenes.

1. Entra a `Mesas`.
2. Modifica el número de mesas disponibles si es necesario.

### Paso 4: Usar el cliente

Descripción:
Este paso abre la interfaz orientada a atención de pedidos. Desde aquí el usuario final puede crear órdenes, consultarlas y modificarlas mediante un menú guiado.

1. Ejecuta `./build/cliente` en otra terminal.
2. Elige opciones del menú:
   - Ver órdenes
   - Crear orden
   - Modificar orden

``` bash
╔══════════════════════════════════════════════════════════════╗
              MENÚ PRINCIPAL DEL SISTEMA  
╠═◆═◆═◆═◆═◆═◆═◆═◆═◆═◆═◆═◆═◆═◆═◆═◆═◆═◆═◆═◆═◆═◆═◆═◆═◆═◆═◆═◆═╣
-> 1. Ver Órdenes
-> 2. Crear Orden
-> 3. Modificar Orden
X 4. Salir
╚══════════════════════════════════════════════════════════════╝
Ingrese una opción: 

```

### Paso 5: Crear orden correctamente

Descripción:
En esta etapa se registra una nueva orden enviando mesa, productos y cantidades al servidor. Si todo es válido, el servidor responde confirmación y la orden queda almacenada para su seguimiento.

1. Selecciona mesa.
2. Agrega productos y cantidades.
3. Confirma.
4. El cliente mostrará el mensaje que devolvió el servidor.

### Cómo manipular la parte de agregar productos (detalle)

Cuando el sistema te pregunte por productos, usa este flujo:

1. En `Ingrese el producto o platillo a agregar:`, escribe el nombre del producto exactamente como existe en el catálogo del servidor.
2. En `Ingrese la cantidad a agregar:`, escribe un entero positivo (`1`, `2`, `3`, ...).
3. En `¿Desea agregar otro producto? (s/n):`:
  - escribe `s` para continuar agregando más productos.
  - escribe `n` para terminar y pasar al resumen de la orden.

Ejemplo guiado:

1. Producto: `Pizza`
2. Cantidad: `2`
3. ¿Otro?: `s`
4. Producto: `Refresco`
5. Cantidad: `1`
6. ¿Otro?: `n`


Verificación antes de confirmar:

1. Revisa que la mesa sea la correcta.
2. Revisa que cada producto tenga la cantidad esperada.
3. Confirma solo si el resumen coincide con lo pedido por el cliente final.

``` bash

╔══════════════════════════════════════════════════════════════╗
                CREAR NUEVA ORDEN
╠══════════════════════════════════════════════════════════════╣
╔══════════════════════════════════════════════════════════════╗
                MESAS DISPONIBLES
╠══════════════════════════════════════════════════════════════╣

╚══════════════════════════════════════════════════════════════╝
Presione Enter para continuar...
Ingrese el número de mesa: 2
╔══════════════════════════════════════════════════════════════╗
                PRODUCTOS DISPONIBLES
╠══════════════════════════════════════════════════════════════╣
No se encontraron productos en la respuesta.
╚══════════════════════════════════════════════════════════════╝
Presione Enter para continuar...

Ingrese el producto o platillo a agregar: Pizza
Ingrese la cantidad a agregar: 2
¿Desea agregar otro producto? (s/n): n
──────────────────────────────────────────────────────────────
Orden creada:
Mesa: 2
Producto: Pizza | Cantidad: 2
──────────────────────────────────────────────────────────────
Presione Enter para continuar...

```

Reglas relevantes:

- La orden no debe repetir el mismo producto exacto más de una vez.
- Si repites producto exacto, el servidor rechazará la orden.

### Paso 5.2: Modificar orden correctamente

Este paso permite actualizar una orden existente: puedes agregar productos, cambiar cantidades o eliminar un producto (cantidad `0`). Es útil para cambios solicitados por el cliente después de ordenar.

Flujo paso a paso recomendado:

1. Selecciona `Modificar orden` en el menú principal del cliente.
2. Revisa primero la lista de órdenes para identificar el ID correcto.
3. Ingresa el `ID de la orden` que deseas modificar.
4. Ingresa producto por producto y su nueva cantidad.
5. Decide si continúas modificando más productos (`s`) o si terminas (`n`).
6. Revisa el resumen de cambios antes de confirmar.

### Cómo manipular la modificación de productos (detalle)

En esta pantalla, la cantidad define la acción:

1. Cantidad mayor a `0`:
  - actualiza el producto a esa nueva cantidad.
2. Cantidad igual a `0`:
  - elimina ese producto de la orden.

Ejemplo guiado de modificación:

1. ID de orden: `1`
2. Producto: `Pizza`, cantidad: `0` (eliminar)
3. ¿Otro?: `s`
4. Producto: `Arroz`, cantidad: `3` (agregar/actualizar)
5. ¿Otro?: `n`


``` bash

╔══════════════════════════════════════════════════════════════╗
                ÓRDENES ACTUALES
╠══════════════════════════════════════════════════════════════╣
No se encontraron órdenes en la respuesta.
╚══════════════════════════════════════════════════════════════╝
Presione Enter para continuar...
╔══════════════════════════════════════════════════════════════╗
                MODIFICAR ORDEN
╠══════════════════════════════════════════════════════════════╣
Ingrese el ID de la orden a modificar: 1
╔══════════════════════════════════════════════════════════════╗
                PRODUCTOS DISPONIBLES
╠══════════════════════════════════════════════════════════════╣
No se encontraron productos en la respuesta.
╚══════════════════════════════════════════════════════════════╝
Presione Enter para continuar...

Ingrese el producto o platillo a modificar/agregar: Pizza
Ingrese la nueva cantidad (0 para eliminar): 0
¿Desea modificar/agregar otro producto? (s/n): s
Ingrese el producto o platillo a modificar/agregar: Arroz
Ingrese la nueva cantidad (0 para eliminar): 3
¿Desea modificar/agregar otro producto? (s/n): n
──────────────────────────────────────────────────────────────
Modificación a aplicar en la orden 1:
Eliminar producto: Pizza
Producto: Arroz | Nueva cantidad: 3
──────────────────────────────────────────────────────────────
Presione Enter para continuar...

```

### Paso 5.3: Ver ordenes

Aquí consultas el estado actual de las órdenes registradas. Sirve para revisar rápidamente qué pedidos existen y verificar si los cambios aplicados se reflejaron correctamente.

Flujo paso a paso recomendado:

1. Selecciona `Ver Órdenes` en el menú principal del cliente.
2. Espera la respuesta del servidor.
3. Revisa cada orden mostrada: ID, mesa y productos.
4. Usa esta vista para validar si una creación/modificación se aplicó correctamente.

Cómo interpretar lo que ves:

1. Si aparecen órdenes:
  - el servidor está respondiendo y existen pedidos registrados.
2. Si aparece `No se encontraron órdenes en la respuesta`:
  - puede que no haya órdenes aún, o el endpoint aún no esté retornando datos en esa ejecución.

Qué revisar si no ves órdenes y esperabas verlas:

1. Confirma que el servidor esté encendido.
2. Crea una orden nueva y vuelve a consultar.
3. Verifica en el menú de órdenes del servidor si la orden existe allí.
4. Si en servidor sí existe pero en cliente no aparece, revisa la respuesta JSON del caso `ViewOrders`.


``` bash

╔══════════════════════════════════════════════════════════════╗
                ÓRDENES ACTUALES
╠══════════════════════════════════════════════════════════════╣
No se encontraron órdenes en la respuesta.
╚══════════════════════════════════════════════════════════════╝
Presione Enter para continuar...


```

### Paso 6: Gestión en servidor

EN CONSTRUCCION

### Paso 7: Cerrar sistema

Descripción:
Finaliza la sesión de trabajo de forma segura. Al cerrar desde el flujo correcto, se evitan procesos colgados y se libera el puerto del servidor.

1. Cierra cliente.
2. En servidor, usa `Salir` en el menú principal.
3. Esto detiene la escucha y apaga el servidor.

---

## Manual técnico

### Comunicación cliente-servidor

Se utiliza socket TCP local con mensajes JSON.

Ejemplo solicitud de crear orden:

```json
{
  "Type": 1,
  "Mesa": 4,
  "Productos": [["Pizza", 2], ["Refresco", 1]]
}
```

Ejemplo respuesta exitosa:

```json
{
  "ok": true,
  "Type": 1,
  "message": "Orden creada correctamente.",
  "idOrden": 8,
  "mesa": 4,
  "cantidadProductos": 2
}
```

Ejemplo respuesta con error:

```json
{
  "ok": false,
  "Type": 1,
  "error": "Producto repetido en la orden: Pizza"
}
```

### Validaciones implementadas en creación de orden

- JSON válido
- Campos obligatorios (`Mesa`, `Productos`)
- Tipos correctos
- Producto existente en catálogo
- Producto no repetido exacto en la misma orden



  </details>  

# Arquitectura lógica  

<details>
  <summary>Desplegar información</summary>

## Modelo general

Arquitectura cliente-servidor con procesamiento en memoria.

```text
Cliente (UI consola) -> JSON -> Socket TCP -> Servidor (lógica + listas enlazadas)
```

## Capas y responsabilidades

### Cliente

- Interfaz y flujo de usuario
- Construcción de mensajes JSON
- Envío/recepción por socket

### Servidor

- Escucha conexiones
- Procesa solicitud por `Type`
- Ejecuta reglas de negocio
- Devuelve respuesta JSON

### Dominio y datos

- Productos
- Órdenes
- Mesas
- Estructuras de apoyo (listas enlazadas y operaciones CRUD)

## Persistencia actual

La información se guarda en memoria mientras el servidor está encendido.

Advertencia:

- Al apagar servidor, se pierde estado temporal.

## Flujo de orden

1. Cliente captura datos.
2. Cliente envía JSON.
3. Servidor valida.
4. Si es válido, crea e inserta orden en `ListaOrdenes`.
5. Servidor responde éxito/error.
6. Cliente muestra respuesta.

  </details>  


# Librerias Utilizadas

<details>
  <summary>Desplegar información</summary>

## 1) Librerías externas (de terceros)

### `nlohmann/json.hpp` (JSON for Modern C++)

Uso en el proyecto:

- Serializar y deserializar mensajes entre cliente y servidor.
- Construcción de requests/responses JSON para operaciones como crear orden y consultar datos.

Dónde se utiliza principalmente:

- Cliente: `cliente_service.cpp`, `cliente_menus.cpp`, `cliente_service.h`, `cliente_menus.h`
- Servidor: `server_service.cpp`, `server_service.h`

Ventaja:

- Simplifica mucho el manejo de JSON sin depender de un parser manual.

Nota de integración en este proyecto:

- Se utiliza en formato header-only y está incluida localmente en `Proyecto/include/nlohmann/json.hpp`.
- No requiere instalación adicional con `apt` si ese archivo ya está presente en el repositorio.

---

## 2) Librerías del sistema (red/sockets)

Estas librerías son del entorno POSIX (Linux/WSL) y permiten comunicación por sockets TCP:

- `<sys/socket.h>`
- `<netinet/in.h>`
- `<arpa/inet.h>`
- `<unistd.h>`

Uso en el proyecto:

- Crear socket servidor
- Aceptar clientes
- Enviar y recibir mensajes
- Cerrar conexiones

Dónde se utilizan:

- `server/server_socket.cpp`
- `client/cliente_socket.cpp`
- Archivos de arranque relacionados (`server.cpp`, `cliente.cpp`)

---

## 3) Resumen práctico de dependencias

Para compilar y ejecutar:

1. `g++`
2. `make`
3. Entorno Linux/WSL para sockets POSIX
4. Archivo `nlohmann/json.hpp` incluido en el repositorio

Si eso está disponible, el proyecto no requiere instalar frameworks adicionales.

</details> 