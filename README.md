# Trapped in Dimensions — Juego 2D en C++/CLI

Juego de acción/plataformas desarrollado como Trabajo Final del curso de Algoritmos. El jugador elige entre dos héroes con estadísticas distintas, navega 3 niveles con enemigos, y debe encontrar portales para avanzar.

## Stack

- **Lenguaje:** C++/CLI (.NET Framework)
- **GUI:** Windows Forms
- **Rendering:** GDI+ (`System::Drawing`)
- **IDE:** Visual Studio 2022

## Características Técnicas

### Rendering
- Sprite sheets 4x4 con animación por dirección (arriba, abajo, izquierda, derecha)
- Double buffering con `BufferedGraphics` para evitar parpadeo
- Transparencia con `MakeTransparent()` usando color clave
- Escalado de sprites al 40%

### Colisiones
- AABB (Axis-Aligned Bounding Box) con `Rectangle::IntersectsWith()`
- Hitbox al 40% del tamaño del sprite
- Sistema de invulnerabilidad post-daño (120 frames ~2 segundos)
- CollisionMap para obstáculos estáticos con layouts por nivel

### Efectos Procedurales (Portal)
- 3 capas de elipses con alpha decreciente (100, 70, 40)
- 8 partículas orbitales con trigonometría (`sin`/`cos`)
- Animación pulsante modulada por frame

### Arquitectura
- **Singleton:** `GameStateManager` — estado global (score, nivel, héroe, vidas)
- **Template Method:** `Character` base class con `move()` virtual
- **Polimorfismo:** `Character` → `Hero1`/`Hero2`, `Enemy1`/`Enemy2`/`Enemy3`
- **Event-driven:** `Timer.Tick` como game loop (~60 FPS)

### Controles
- **Teclado:** WASD para movimiento
- **Mouse:** Click en menús
- **Escape:** Pausa

## Estructura del Proyecto

```
TF/
├── TF.sln                    # Solución Visual Studio
├── Assets/
│   ├── Sprites/              # Sprite sheets (PNG)
│   └── Background/           # Fondos de nivel (PNG)
├── Character.h               # Clase base de entidades
├── Hero1.h / Hero2.h         # Personajes jugables
├── Enemy1.h / Enemy2.h / Enemy3.h  # Enemigos con AI de patrulla
├── Controller.h              # Orquestador de lógica
├── CollisionMap.h            # Sistema de obstáculos estáticos
├── Portal.h                  # Efectos procedurales
├── GameStateManager.h        # Singleton de estado
├── GameConfig.h              # Constantes de configuración
├── MenuPrincipal.h           # Menú principal
├── SelectCharacterForm.h     # Selección de personaje
├── Nivel0.h - Nivel3.h       # 4 niveles con dificultad creciente
└── Main.cpp                  # Entry point
```

## Cómo Compilar

1. Abrir `TF.sln` en Visual Studio 2022
2. Seleccionar configuración `Release` o `Debug`
3. `Ctrl+Shift+B` para compilar
4. `F5` para ejecutar

> **Nota:** Requiere Windows con .NET Framework. Los assets PNG deben estar en `Assets/`.

## Diseño de Niveles

| Nivel | Nombre | Tiempo | Enemigos | Paredes | Portal |
|-------|--------|--------|----------|---------|--------|
| 0 | Tutorial | 30s | No | 8 | Al inicio |
| 1 | Caos | 60s | Sí | 3 | A los 30s |
| 2 | Pasado | 90s | Sí | 0 | A los 45s |
| 3 | Apocalipsis | 120s | Sí | 0 | A los 60s |
