<div align="center">

<img src="https://cem.epn.edu.ec/imagenes/logos_institucionales/big_png/BUHO_EPN_big.png" alt="Logo EPN" height="200">

# ESCUELA POLITECNICA NACIONAL

## ONE-POS Sistema de Punto de Venta

**Desarrolladores:**

- 💻 Mateo Villavicencio
- 💻 Marcos Quimba

---

</div>

Sistema de punto de venta desarrollado en lenguaje C para la gestión de productos, ventas e inventario de un negocio.

## Descripción

ONE-POS es un sistema básico de punto de venta que permite gestionar productos, realizar ventas, controlar el inventario y generar reportes. Fue desarrollado como proyecto académico utilizando programación estructurada en C.

## Características Principales

- **Gestión de Productos**: Registro y consulta de productos con categorías, precios e IVA
- **Sistema de Ventas**: Realización de ventas con cálculo automático de IVA y descuentos
- **Control de Inventario**: Actualización de stock y alertas de productos con stock bajo
- **Gestión de Cajas**: Apertura y cierre de cajas registradoras (hasta 3 cajas)
- **Reportes**: Generación de reportes de inventario, ventas y productos con stock bajo

## Requisitos

- Sistema operativo Windows
- Compilador de C (recomendado: MinGW, Dev-C++, o Visual Studio)
- Biblioteca estándar de C

## Estructura del Sistema

El sistema está organizado en los siguientes módulos:

1. **Módulo de Productos**: Permite registrar nuevos productos, ver la lista de productos y editar el valor del IVA
2. **Módulo de Ventas**: Realiza ventas de productos con cálculo de subtotal, IVA y descuentos
3. **Módulo de Inventario**: Permite aumentar o disminuir el stock de los productos
4. **Módulo de Reportes**: Genera reportes de inventario, ventas y productos con stock bajo
5. **Módulo de Cajas**: Gestiona la apertura y cierre de cajas registradoras

## Funcionalidades

### Productos

- Registro de productos con nombre, precio, categoría y stock inicial
- Configuración de IVA por producto (0%, 12% o 15%)
- Visualización de lista completa de productos
- Actualización del valor de IVA del sistema

### Ventas

- Selección de producto a vender
- Validación de stock disponible
- Aplicación de descuentos opcionales
- Cálculo automático de subtotal, IVA y total
- Registro de ventas en la caja abierta
- Alerta cuando un producto queda con stock bajo

### Inventario

- Consulta de stock actual de productos
- Aumento de stock
- Disminución de stock (con validación)

### Cajas

- Apertura de caja con monto inicial
- Cierre de caja con resumen de ventas
- Solo se puede tener una caja abierta a la vez
- Registro de todas las ventas realizadas

### Reportes

- Reporte de inventario completo
- Reporte de ventas de la caja actual
- Reporte de productos con stock bajo

## Categorías de Productos

El sistema incluye 4 categorías predefinidas:

1. LIMPIEZA
2. BEBIDAS
3. CONSUMIBLES
4. HOGAR

## Compilación y Ejecución

### Compilar el programa:

```bash
gcc onePosSystem.c -o onePosSystem.exe
```

### Ejecutar el programa:

```bash
./onePosSystem.exe
```

O simplemente hacer doble clic en el archivo ejecutable si se compiló en Windows.

## Uso del Sistema

1. Al iniciar el programa, se mostrará el menú principal con las opciones disponibles
2. Primero debes abrir una caja desde el módulo "CAJAS" para poder realizar ventas
3. Puedes registrar productos desde el módulo "PRODUCTOS"
4. Para realizar una venta, selecciona el módulo "VENTAS" y sigue las instrucciones
5. El sistema calculará automáticamente el IVA y aplicará descuentos si los hay
6. Puedes consultar reportes en cualquier momento desde el módulo "REPORTES"

## Datos Iniciales

El sistema viene con 3 productos de ejemplo:

- Chocolate (Código: 1, Precio: $2.54, Con IVA)
- Pepsi (Código: 2, Precio: $4.54, Sin IVA)
- Guitig (Código: 3, Precio: $0.75, Con IVA)

## Limitaciones

- Máximo de 20 productos
- Máximo de 3 cajas registradoras
- Máximo de 10 ventas por caja
- Solo se puede tener una caja abierta a la vez
- Los datos no se guardan al cerrar el programa (solo en memoria)

## Notas Técnicas

- El sistema utiliza estructuras (structs) para organizar los datos
- Se implementaron funciones para validar entrada de datos
- El IVA por defecto es del 12%
- El stock mínimo para alertas es de 2 unidades
- El sistema está diseñado para Windows (usa windows.h)

## Observaciones

Este proyecto fue desarrollado como parte de un curso de programación en C. Es un sistema básico que demuestra el uso de estructuras de datos, funciones, validación de entrada y programación estructurada.

---

**Nota**: Este es un proyecto académico básico. Para uso en producción se recomendarían mejoras como persistencia de datos, interfaz gráfica, y validaciones más robustas.
