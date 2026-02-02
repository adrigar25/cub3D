# Cub3D Multiplayer

Tu juego Cub3D ahora soporta multijugador en red para conectar desde diferentes máquinas.

## Instrucciones de Uso

### Modo Servidor
Para iniciar el juego como servidor:
```bash
./cub3D -s <puerto> <mapa.cub>
```

Ejemplo:
```bash
./cub3D -s 8080 MAPS/map1.cub
```

El servidor:
- Iniciará el juego y esperará conexiones de clientes
- Mostrará el estado de red en pantalla
- Será autoritativo (controla la lógica del juego)

### Modo Cliente
Para conectarse a un servidor:
```bash
./cub3D -c <ip_servidor> <puerto> <mapa.cub>
```

Ejemplo:
```bash
./cub3D -c 192.168.1.100 8080 MAPS/map1.cub
```

El cliente:
- Se conectará al servidor especificado
- Recibirá las posiciones de otros jugadores
- Enviará sus movimientos al servidor

### Modo Un Jugador
Para jugar en modo tradicional:
```bash
./cub3D <mapa.cub>
```

## Controles
- **WASD**: Movimiento
- **Flechas izq/der**: Rotación de cámara
- **ESC**: Salir

## Características Multijugador

### Sincronización de Jugadores
- Todos los jugadores se ven entre sí en tiempo real
- Los movimientos se sincronizan automáticamente
- Cada jugador tiene un color diferente para distinguirlos

### Arquitectura de Red
- **Protocolo**: TCP para confiabilidad
- **Threading**: Comunicación en hilos separados
- **Autoridad**: El servidor controla el estado del juego
- **Frecuencia**: 30 actualizaciones por segundo

### Visualización de Estado
En pantalla se muestra:
- Estado de conexión (Conectado/Desconectado)
- Número de jugadores conectados
- Tu ID de jugador

## Configuración de Red

### Firewall
Asegúrate de que el puerto elegido esté abierto en el firewall del servidor.

### IP Local vs IP Pública
- Para jugar en la misma red local, usa la IP privada (192.168.x.x)
- Para jugar a través de Internet, necesitarás configurar port forwarding

### Puertos Comunes
- Usa puertos altos (8080, 9000, etc.) para evitar conflictos
- Evita puertos del sistema (< 1024)

## Resolución de Problemas

### "Connection refused"
- Verifica que el servidor esté ejecutándose
- Confirma la IP y puerto correctos
- Revisa el firewall

### "Address already in use"
- El puerto ya está siendo usado
- Cambia a un puerto diferente
- Espera unos segundos antes de reiniciar

### Lag o desconexiones
- Verifica la calidad de la conexión de red
- Reduce la distancia física entre máquinas en LAN
- Considera usar un puerto diferente

## Ejemplos de Configuración

### Red Local (LAN)
1. **Servidor**: `./cub3D -s 8080 MAPS/map1.cub`
2. **Cliente**: `./cub3D -c 192.168.1.100 8080 MAPS/map1.cub`

### Múltiples Clientes
1. **Servidor**: `./cub3D -s 8080 MAPS/map1.cub`
2. **Cliente 1**: `./cub3D -c servidor_ip 8080 MAPS/map1.cub`
3. **Cliente 2**: `./cub3D -c servidor_ip 8080 MAPS/map1.cub`

¡Disfruta jugando Cub3D con tus amigos!
