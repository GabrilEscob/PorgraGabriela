
# Bitácora del Sistema - Asignación de Códigos (3000-3999)

## Estructura General
| Rango        | Módulo          | Acciones Asignadas                     | Disponibles  |
|--------------|-----------------|----------------------------------------|--------------|
| 3000-3049    | Autenticación   | Login, Registro, Usuarios              | 3000-3003, 3005-3049 |
| 3050-3099    | *Reservado*     | Expansión autenticación                | 50           |
| 3100-3149    | Usuarios        | IDs de usuarios (3004-3104) + acciones | 3105-3106, 3108-3149 |
| 3150-3199    | Clientes        | Gestión de clientes                    | 3107-3157    |
| 3200-3249    | Proveedores     | Gestión de proveedores                 | 3158-3208    |
| 3250-3299    | Productos       | Gestión de productos                   | 3209-3259    |
| 3300-3349    | Almacenes       | Gestión de almacenes                   | 3260-3310    |
| 3350-3399    | Transportistas  | Gestión de transportistas              | 3311-3361    |
| 3400-3999    | *Libres*        | Para futuras expansiones               | 3362-3999    |

---

## Detalle por Módulo

### 🔐 Autenticación (3000-3049)
| Código | Acción               | Descripción                          |
|--------|-----------------------|--------------------------------------|
| 3000   | `LOGIN`              | Inicio de sesión exitoso.            |
| 3001   | `REGISTRO`           | Registro de nuevo usuario.           |
| 3003   | `CONSULTAR_USUARIOS` | Listado de usuarios.                 |
| 3004-3104 | `ID_USUARIOS`      | Identificadores únicos de usuarios.  |
| 3105   | `CERRAR_SESION`      | Usuario cerró sesión.                |
| 3106   | `BACKUP`             | Respaldo de bitácora generado.       |

### 👥 Clientes (3107-3157)
| Código | Acción               | Descripción                          |
|--------|-----------------------|--------------------------------------|
| 3107   | `CLIENTE_CREADO`      | Nuevo cliente registrado.            |
| 3108   | `CLIENTE_ACTUALIZADO` | Datos de cliente modificados.        |
| ...    | ...                   | ... (hasta 3157)                     |

### 📦 Productos (3209-3259)
| Código | Acción               | Descripción                          |
|--------|-----------------------|--------------------------------------|
| 3209   | `PRODUCTO_AGREGADO`   | Nuevo producto en inventario.        |
| 3210   | `STOCK_ACTUALIZADO`   | Ajuste de unidades en almacén.       |
| ...    | ...                   | ... (hasta 3259)                     |

---

## Ejemplos de Uso
```cpp
// En usuarios.cpp
auditoria.registrar("3001", "AUTENTICACION", "Usuario registrado: Jennifer3001");

// En clientes.cpp
auditoria.registrar("3150", "CLIENTES", "Cliente actualizado (ID: CLT-557)");
