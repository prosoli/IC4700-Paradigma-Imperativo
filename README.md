# IC4700 - I Proyecto - Paradigma Imperativo  

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
Mesas disponibles:
[ 1 ]  [ 2 ]  [ 3 ]  [ 4 ]  [ 5 ]  [ 6 ]  [ 7 ]  [ 8 ]  [ 9 ]  [ 10 ]  
╚══════════════════════════════════════════════════════════════╝
Presione Enter para continuar...
Ingrese el número de mesa: 9
╔══════════════════════════════════════════════════════════════╗
                PRODUCTOS DISPONIBLES
╠══════════════════════════════════════════════════════════════╣
Productos disponibles:
Producto: "Taco" | Precio: 1200.0
Producto: "Sushi" | Precio: 12000.0
╚══════════════════════════════════════════════════════════════╝
Presione Enter para continuar...

Ingrese el producto o platillo a agregar: Sushi
Ingrese la cantidad a agregar: 1
¿Desea agregar otro producto? (s/n): n
──────────────────────────────────────────────────────────────
Orden creada:
Mesa: 9
Producto: Sushi | Cantidad: 1
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
Orden ID: 1
Mesa: 9
Productos:
  - Sushi: 1
──────────────────────────────────────────────────────────────
╚══════════════════════════════════════════════════════════════╝
Presione Enter para continuar...
╔══════════════════════════════════════════════════════════════╗
                MODIFICAR ORDEN
╠══════════════════════════════════════════════════════════════╣
Ingrese el ID de la orden a modificar: 1
╔══════════════════════════════════════════════════════════════╗
                PRODUCTOS DISPONIBLES
╠══════════════════════════════════════════════════════════════╣
Productos disponibles:
Producto: "Taco" | Precio: 1200.0
Producto: "Sushi" | Precio: 12000.0
╚══════════════════════════════════════════════════════════════╝
Presione Enter para continuar...Taco

Ingrese el producto o platillo a modificar/agregar: Taco
Ingrese la nueva cantidad (0 para eliminar): 2
¿Desea modificar/agregar otro producto? (s/n): n
──────────────────────────────────────────────────────────────
Modificación a aplicar en la orden 1:
Producto: Taco | Nueva cantidad: 2
──────────────────────────────────────────────────────────────
Presione Enter para continuar...

╔══════════════════════════════════════════════════════════════╗
¿Está seguro que desea realizar esta acción?
╠══════════════════════════════════════════════════════════════╣
1. Si
2. No
╚══════════════════════════════════════════════════════════════╝

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
Orden ID: 1
Mesa: 9
Productos:
  - Sushi: 1
──────────────────────────────────────────────────────────────
╚══════════════════════════════════════════════════════════════╝
Presione Enter para continuar...



```

### Paso 6: Gestión en servidor

Descripción: Este paso abre la interfaz orientada a la gestión del restaurante con respecto a productos, pedidos y mesas. Desde aquí el usuario final puede crear, consultar y modificar productos, ordenes y mesas mediante un menú guiado.  

Ejecuta ./build/servidor en otra terminal.

Elige opciones del menú:
  - Gestión de Productos 
  - Gestión de Ordenes
  - Gestión de Mesas

``` bash

╔══════════════════════════════════════════════════════╗
║               PANEL DEL RESTAURANTE                  ║
╠══════════════════════════════════════════════════════╣
   Gestion del Restaurante                         
╚══════════════════════════════════════════════════════╝
────────────────────────────────────────────────────────
  [1] Productos
  [2] Ordenes
  [3] Mesas
  [0] Salir
────────────────────────────────────────────────────────
Seleccione una opcion: 

```

### Paso 8: Gestión de Productos

Descripción: En esta etapa se gestionan los productos. Se puede visualizar la lista de productos, así como agregar, actualizar o eliminar un producto, e incluso vaciar la lista de productos.

```bash
╔══════════════════════════════════════════════════════╗
║               PANEL DEL RESTAURANTE                  ║
╠══════════════════════════════════════════════════════╣
   Gestion de Productos                             
╚══════════════════════════════════════════════════════╝
────────────────────────────────────────────────────────
  [1] Listar productos
  [2] Agregar un producto
  [3] Actualizar un producto
  [4] Eliminar un producto
  [5] Eliminar todos los productos
  [0] Volver al menu principal
────────────────────────────────────────────────────────
Seleccione una opcion:

```

#### Paso 8.1: Listar productos 

Aquí consultas los detalles de las productos registrados. Sirve para revisar rápidamente qué productos hay disponibles, y para verificar si los cambios aplicados se reflejaron correctamente.
Flujo paso a paso recomendado:

  1. Selecciona Listar productos (1) en el menú de productos del servidor.
  2. Espera la respuesta del servidor.
  3. Revisa cada producto mostrado: Nombre y precio.
  4. Usa esta vista para validar si una creación/modificación se aplicó correctamente.

``` bash

======= Productos registrados =======
1. Pizza, CR3500
2. Hamburguesa, CR4800

```

#### Paso 8.2: Agregar un producto

Aquí registras un producto nuevo, indicando su nombre y su precio.
Flujo paso a paso recomendado:

  1. Selecciona Agregar un producto (2) en el menú de productos del servidor.
  2. Espera la respuesta del servidor.
  3. Ingresa el nombre que tendrá el producto.
  4. Ingresa el precio (en números) que tendrá el producto.
  5. Utiliza la opción Listar productos (1) en el menú de productos del servidor para confirmar que se registró el nuevo producto.

``` bash

--Agregar un producto--
Ingrese el nombre del producto:
Pizza
Ingrese el precio del producto: 3500

```

#### Paso 8.3: Actualizar un producto

Aquí actualizas la información de un producto previamente registrado, indicando su nuevo nombre y su nuevo precio.
Flujo paso a paso recomendado:

  1. Utiliza la opción Listar productos (1) en el menú de productos del servidor para verificar el índice (número identificador) del producto que quieres actualizar.
  2. Selecciona Actualizar un producto (3) en el menú de productos del servidor.
  3. Espera la respuesta del servidor.
  4. Ingresa el indice del producto.
  5. Ingresa el nuevo nombre que tendrá el producto.
  6. Ingresa el nuevo precio (en números) que tendrá el producto.
  7. Utiliza la opción Listar productos (1) en el menú de productos del servidor para confirmar que se registró el cambio en la información del producto.

``` bash

--Actualizar un producto--
Ingrese el indice del producto a actualizar: 2
Ingrese el nuevo nombre del producto:
Hamburguesa
Ingrese el nuevo precio del producto: 5000

```

#### Paso 8.4: Eliminar un producto

Aquí eliminas un producto de la lista de productos registrados.
Flujo paso a paso recomendado:

  1. Utiliza la opción Listar productos (1) en el menú de productos del servidor para verificar el índice (número identificador) del producto que quieres eliminar.
  2. Selecciona Eliminar un producto (4) en el menú de productos del servidor.
  3. Espera la respuesta del servidor.
  4. Ingresa el indice del producto.
  5. Utiliza la opción Listar productos (1) en el menú de productos del servidor para confirmar que se eliminó el producto.

``` bash

--Eliminar un producto--
Ingrese el indice del producto a eliminar: 1

```

#### Paso 8.5: Eliminar todos los productos

Aquí vacías por completo la lista de productos registrados.
Flujo paso a paso recomendado:

  1. Selecciona Eliminar todos los productos (5) en el menú de productos del servidor.
  2. Espera la respuesta del servidor (en este caso es una confirmación de borrado).
  3. Utiliza la opción Listar productos (1) en el menú de productos del servidor para confirmar que la lista de productos está vacía.

``` bash

--Lista eliminada--

```


### Paso 9: Gestión de Ordenes

Descripción: En esta etapa se gestionan las ordenes, se pueden visualizar las ordenes totales y pendientes asi como modificarse

```bash
╔══════════════════════════════════════════════════════╗
║               PANEL DEL RESTAURANTE                  ║
╠══════════════════════════════════════════════════════╣
   Gestion de Ordenes                              
╚══════════════════════════════════════════════════════╝
────────────────────────────────────────────────────────
  [1] Visualizar ordenes
  [2] Visualizar ordenes pendientes
  [3] Modificar ordenes
  [0] Volver al menu principal
────────────────────────────────────────────────────────
Seleccione una opcion:

```

#### Paso 9.1: Visualización de ordenes  

Aquí consultas los detalles de las órdenes registradas. Sirve para revisar rápidamente qué pedidos existen tanto pendientes como completados y para verificar si los cambios aplicados se reflejaron correctamente.  

Flujo paso a paso recomendado:

  1. Selecciona Visualizar Órdenes en el menú de ordenes del servidor.
  2. Espera la respuesta del servidor.
  3. Revisa cada orden mostrada: ID, mesa, estado y productos.
  4. Usa esta vista para validar si una creación/modificación se aplicó correctamente.

Cómo interpretar lo que ves:

1. Si aparecen órdenes:
  - el cliente está funcionando correctamente y existen pedidos registrados.
2. Si aparece `No se encontraron órdenes en la respuesta`:
  - puede que no haya órdenes aún, o el endpoint aún no esté retornando datos en esa ejecución.

Qué revisar si no ves órdenes y esperabas verlas:

1. Confirma que el el cliente esté encendido.
2. Crea una orden nueva y vuelve a consultar.
3. Verifica en el menú de órdenes del servidor si la orden existe allí.

``` bash

╔════════════════════════════════════════════╗
║       ÓRDENES REGISTRADAS EN SISTEMA       ║
╚════════════════════════════════════════════╝
1.   ┌─ Orden #1
  ├─ Mesa: 1
  ├─ Productos:
  │   • Pizza (2 ud)
  └─ Estado: Pendiente

2.   ┌─ Orden #2
  ├─ Mesa: 5
  ├─ Productos:
  │   • Hamburguesa (2 ud)
  └─ Estado: Completada
```

#### Paso 9.2: Visualización de ordenes pendientes 

Aquí consultas el total de las ordenes que están pendientes. También, sirve para revisar rápidamente qué pedidos han sido completados y ya no debería de mostrarse en las ordenes pendientes o bien si hay nuevos pedidos.  

Flujo paso a paso recomendado:

  1. Selecciona Visualizar Órdenes Pendientes en el menú de ordenes del servidor.
  2. Espera la respuesta del servidor.
  3. Revisa cada orden mostrada: ID, mesa, estado y productos.
  4. Usa esta vista para validar si una creación/modificación se aplicó correctamente.

Cómo interpretar lo que ves:

1. Si aparecen órdenes:
  - el cliente está funcionando correctamente y existen pedidos registrados.
  - existen pedidos pendientes
2. Si aparece `No se encontraron órdenes en la respuesta`:
  - puede que no haya órdenes aún, todas las ordenes están en estado *completado* o el endpoint aún no esté retornando datos en esa ejecución.

Qué revisar si no ves órdenes y esperabas verlas:

1. Confirma que el el cliente esté encendido.
2. Crea una orden nueva y vuelve a consultar que se registró.

``` bash

╔════════════════════════════════════════════╗
║         ÓRDENES PENDIENTES POR ENTREGAR    ║
╚════════════════════════════════════════════╝

  ┌─ Orden #2
  ├─ Mesa: 1
  ├─ Productos:
  │   • Pizza (2 ud)
  └─ Estado: Pendiente

```

#### Paso 9.3: Modificación de ordenes  

Descripción: En esta etapa se modifican las ordenes creadas en el cliente, la modificación se hace solo para cambiar el estado del pedido de *Pendiente* a *Completada* enviando unicamente el ID de la orden. Si todo es válido, el servidor responde confirmación y la orden queda modificada.  

**Cómo manipular la parte de modificar ordenes (detalle)**
Cuando el sistema te pregunte por cual orden quiere completar, usa este flujo:

1.  Ingrese a la opcion de *Visualizar ordenes* en el menú de este.
2.  Visualice cual es la orden que desee completar y su ID.
3.  Ingrese al menu de modificación y digite el ID correspondiente.
4.  Espere respuesta del servidor para confirmar que la orden ha sido modificada.

```bash
╔════════════════════════════════════════════╗
║       MARCAR ORDEN COMO COMPLETADA         ║
╠════════════════════════════════════════════╣
║  [1] Marcar orden como completada         ║
║  [0] Volver                                 ║
╚════════════════════════════════════════════╝
Opción: 1

```


```bash
Ingrese el ID de la orden a completar: 1
✓ Orden 1 marcada como completada.

```



### Paso 10: Gestión de Mesas

- Descripción:
En esta etapa se administra la configuración de las mesas del restaurante. El sistema permite modificar el listado de mesas disponibles, agregando nuevos números de mesa, eliminando los que ya no se usan o estableciendo una lista completa desde cero.

#### Paso 10.1: Acceder al menú de mesas

Desde el panel principal del servidor, selecciona la opción `3. Mesas`.

Verás el menú de gestión de mesas con la lista actual de mesas y las opciones disponibles.

```bash
╔══════════════════════════════════════════════════════╗
║               PANEL DEL RESTAURANTE                  ║
╠══════════════════════════════════════════════════════╣
   Gestion de Mesas                                
╚══════════════════════════════════════════════════════╝
────────────────────────────────────────────────────────
Mesas actuales: [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
────────────────────────────────────────────────────────
  [1] Agregar una mesa (por ID)
  [2] Eliminar una mesa (por ID)
  [3] Establecer lista completa de mesas
  [0] Volver al menu principal
────────────────────────────────────────────────────────

Seleccione una opcion: 
```

#### Paso 10.2: Agregar una mesa (opción 1)
Agrega un nuevo número de mesa al sistema. El sistema verificará que el ID no exista ya y lo insertará ordenado automáticamente.

Elige `1`.

Ingresa el ID numérico de la nueva mesa (entero positivo).

Si el ID es válido y no está repetido, se mostrará un mensaje de éxito.

```bash
Seleccione una opcion: 1

Ingrese el ID de la nueva mesa: 15
Mesa 15 agregada.

Presione Enter para continuar...
```

Resultado: La lista de mesas se actualiza y se ordena de menor a mayor. Si se intenta agregar un ID ya existente, el sistema lo ignora sin duplicar.

#### Paso 10.3: Eliminar una mesa (opción 2)
Remueve un número de mesa del listado. El sistema buscará el ID y, si existe, lo eliminará.

Elige `2`.

Ingresa el ID de la mesa a eliminar.

Si el ID existe, se confirma la eliminación.

```bash
Seleccione una opcion: 2

Ingrese el ID de la mesa a eliminar: 4
Mesa 4 eliminada.

Presione Enter para continuar...
```

Resultado: El ID desaparece de la lista. Si el ID no existe, se muestra un mensaje de error y la lista permanece igual.

#### Paso 10.4: Establecer lista completa de mesas (opción `3`)
Reemplaza toda la lista de mesas por una nueva, ingresada manualmente como una secuencia de números separados por espacios. Es útil para configurar rápidamente la disposición actual del salón.

Elige `3`.

Ingresa los IDs separados por espacios (ejemplo: 1 3 5 8).

El sistema ordenará los números y eliminará duplicados automáticamente.

```bash
Seleccione una opcion: 3

Ingrese los IDs separados por espacios (ejemplo: 1 3 5 8): 1 3 4 2
Lista de mesas actualizada.

Presione Enter para continuar...
```

Resultado: La lista de mesas se convierte en la nueva secuencia, ordenada y sin repetidos. En el ejemplo, se obtiene [1, 2, 3, 4].

- Verificación de cambios
Después de cualquier operación, el menú mostrará la lista actualizada automáticamente. Puedes salir y volver a entrar para confirmar.

```bash
Mesas actuales: [1, 2, 3, 4]
────────────────────────────────────────────────────────
  [1] Agregar una mesa (por ID)
  [2] Eliminar una mesa (por ID)
  [3] Establecer lista completa de mesas
  [0] Volver al menu principal
```

### Paso 11: Cerrar sistema

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
- Ejecuta reglas de negocio como gestionar ordnees, productos y mesas
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

1. El usuario interactúa con el menú en el cliente.
2. El cliente genera un JSON con un Type.
   - ViewTables
   - CreateOrder
   - ViewOrders
   - ModifyOrder
   - ViewProducts
4. El cliente envía este JSON al servidor a través de un socket TCP.
5. El servidor recibe el mensaje, lo procesa y enruta la solicitud según el Type.
6. El servidor usa servicios de negocio como manejo de órdenes, productos, mesas para procesar la solicitud.
7. El servidor responde con un JSON.
8. El cliente parsea la respuesta y la muestra en la consola.

## Diagrama de arquitectura  

![Diag1](https://github.com/prosoli/IC4700-Paradigma-Imperativo/blob/main/Imagenes/Arquitectura%20Logica-P%C3%A1gina-2.drawio.svg)

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
