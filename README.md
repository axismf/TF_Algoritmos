# 🎮 Redefiniendo el Futuro

[![C++](https://img.shields.io/badge/C%2B%2B-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)](https://isocpp.org/)
[![Windows Forms](https://img.shields.io/badge/Windows%20Forms-0078D6?style=for-the-badge&logo=windows&logoColor=white)](https://docs.microsoft.com/en-us/dotnet/desktop/winforms/)
[![Visual Studio](https://img.shields.io/badge/Visual%20Studio-5C2D91?style=for-the-badge&logo=visual-studio&logoColor=white)](https://visualstudio.microsoft.com/)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg?style=for-the-badge)](https://opensource.org/licenses/MIT)

> *Un juego 2D de supervivencia desarrollado en C++/CLI donde luchas contra la dominación de la IA a través de diferentes dimensiones temporales.*

[🎥 Ver Demo](#) | [📖 Documentación](docs/GAME_DESIGN.md) | [🐛 Reportar Bug](../../issues)

---

## 📋 Tabla de Contenidos

- [Sobre el Proyecto](#-sobre-el-proyecto)
- [Características](#-características)
- [Tecnologías](#️-tecnologías)
- [Instalación](#-instalación)
- [Cómo Jugar](#-cómo-jugar)
- [Arquitectura](#-arquitectura)
- [Roadmap](#-roadmap)
- [Contribuir](#-contribuir)
- [Créditos](#-créditos)

---

## 🎯 Sobre el Proyecto

**Redefiniendo el Futuro** es un juego de supervivencia 2D donde encarnas a un héroe atrapado en diferentes dimensiones temporales dominadas por la Inteligencia Artificial. Deberás sobrevivir oleadas de enemigos robóticos mientras buscas portales dimensionales para escapar.

### 🎬 Historia

Después de un extraño sueño, descubres que no fue solo una pesadilla: la IA ha tomado el control de múltiples dimensiones temporales. Debes navegar a través del **Pasado**, el **Presente Caótico** y enfrentar tu destino para restaurar el equilibrio.

### 🎮 Gameplay

- **Nivel Tutorial**: Aprende los controles básicos mientras exploras un nivel con colisiones
- **Nivel 1 - Dimensión del Caos**: Sobrevive 30 segundos contra enemigos en un entorno fragmentado
- **Nivel 2 - Dimensión del Pasado**: Batalla final contra oleadas intensas por 45 segundos

---

## ✨ Características

### 🎭 Sistema de Personajes
- **Héroe 1 "Velocista"**: Alta velocidad (15), 5 vidas - Para jugadores ágiles
- **Héroe 2 "Tanque"**: Baja velocidad (8), 8 vidas - Para jugadores defensivos
- **Opción IA**: Easter egg humorístico (¡no seleccionable!)

### ⚔️ Mecánicas de Juego
- ✅ Sistema de colisiones avanzado con mapas personalizados
- ✅ 3 tipos de enemigos con patrones de movimiento únicos
- ✅ Sistema de invulnerabilidad temporal (2 segundos después del daño)
- ✅ Portales dimensionales animados con efectos visuales
- ✅ Sistema de puntuación progresivo
- ✅ Narrativa integrada con diálogos entre niveles

### 🎨 Elementos Visuales
- Sistema de sprites animados (4 frames de animación)
- Portales con efectos de partículas y resplandor
- UI moderna con efectos hover
- Fondos temáticos por nivel
- Indicadores visuales de estado (vidas, escudo de invulnerabilidad)

### 🏗️ Arquitectura Técnica
- Patrón **Singleton** para GameStateManager
- Separación de responsabilidades (MVC parcial)
- Double buffering para renderizado fluido (60 FPS)
- Sistema de configuración centralizado (GameConfig)

---

## 🛠️ Tecnologías

| Tecnología | Uso |
|------------|-----|
| **C++/CLI** | Lenguaje principal |
| **Windows Forms** | Framework de UI |
| **GDI+** | Renderizado 2D (System::Drawing) |
| **Visual Studio 2022** | IDE y compilador |
| **.NET Framework 4.8** | Runtime |

### Librerías Utilizadas
- `System::Drawing` - Gráficos 2D
- `System::Windows::Forms` - Interfaz de usuario
- `<vector>` - Gestión dinámica de enemigos

---

## 📥 Instalación

### Requisitos Previos
- Windows 10/11 (64-bit)
- Visual Studio 2022 con soporte C++/CLI
- .NET Framework 4.8 Runtime

### Pasos de Instalación

1. **Clonar el repositorio**
```bash
git clone https://github.com/tu-usuario/redefiniendo-el-futuro.git
cd redefiniendo-el-futuro
```

2. **Abrir en Visual Studio**
```bash
# Doble clic en TF.sln
# O desde línea de comandos:
start TF.sln
```

3. **Configurar Assets**
Asegúrate de tener la carpeta `Assets/` en el directorio del ejecutable:
```
Assets/
├── Sprites/
│   ├── prota.png
│   ├── IA.png
│   └── roboto.png
└── Background/
    ├── menu.png
    ├── fondo0.png
    ├── fondo1.png
    └── fondo2.png
```

4. **Compilar y Ejecutar**
- Seleccionar configuración: `Release | x64`
- Presionar `F5` o `Ctrl + F5`

---

## 🎮 Cómo Jugar

### Controles
```
W - Mover arriba
A - Mover izquierda
S - Mover abajo
D - Mover derecha
ESC - Pausar juego
```

### Objetivo
1. **Sobrevive** el tiempo requerido en cada nivel
2. **Evita** colisiones con enemigos (pierdes 1 vida por impacto)
3. **Encuentra** el portal cuando aparezca
4. **Entra** al portal para avanzar al siguiente nivel

### Tips
- Aprovecha los 2 segundos de invulnerabilidad después de recibir daño
- Los enemigos rebotan en los bordes de sus zonas
- El portal aparece después de cumplir el tiempo mínimo de supervivencia
- Hero1 es mejor para speedruns, Hero2 para completar el juego

---

## 🏛️ Arquitectura

### Estructura de Carpetas
```
TF/
├── Assets/              # Recursos gráficos
├── Controladores/       # Lógica del juego
│   ├── Controller.h     # Controlador principal
│   ├── GameConfig.h     # Configuraciones
│   └── GameStateManager.h  # Estado global
├── Forms/               # Vistas (Windows Forms)
│   ├── MenuPrincipal.h
│   ├── SelectCharacterForm.h
│   ├── Nivel0.h         # Tutorial
│   ├── Nivel1.h         # Nivel principal
│   └── Nivel2.h         # Nivel final
├── Personajes/          # Entidades del juego
│   ├── Character.h      # Clase base
│   ├── Hero1.h / Hero2.h
│   ├── Enemy1.h / Enemy2.h / Enemy3.h
│   ├── Portal.h
│   └── CollisionMap.h   # Sistema de colisiones
└── main.cpp             # Punto de entrada
```

### Diagrama de Clases (Simplificado)
```
Character (Base)
├── Hero1
├── Hero2
├── Enemy1
├── Enemy2
└── Enemy3

Controller
├── Gestiona héroes
├── Gestiona enemigos
├── Detecta colisiones
└── Controla portal

GameStateManager (Singleton)
├── Héroe seleccionado
├── Nivel actual
├── Puntuación
└── Estado del juego
```

### Flujo del Juego
```
MenuPrincipal → SelectCharacterForm → Nivel0 (Tutorial)
                                         ↓
                                      Nivel1
                                         ↓
                                      Nivel2 → Victoria
```

---

## 🚀 Roadmap

### ✅ Implementado (v1.0)
- [x] Sistema de personajes con stats diferenciados
- [x] 3 niveles jugables (Tutorial + 2 niveles)
- [x] Sistema de colisiones por nivel
- [x] Portales animados
- [x] Sistema de puntuación
- [x] Narrativa integrada
- [x] 3 tipos de enemigos

### 🚧 En Desarrollo
- [ ] Sistema de audio (música y efectos)
- [ ] Más niveles (Nivel 3, 4, 5)
- [ ] Power-ups y objetos coleccionables
- [ ] Sistema de high scores persistente
- [ ] Efectos de partículas mejorados

### 💭 Futuras Mejoras
- [ ] Migración a Qt Framework (multiplataforma)
- [ ] Modo multijugador local
- [ ] Editor de niveles
- [ ] Achievements y estadísticas
- [ ] Modos de dificultad

---

## 🤝 Contribuir

¡Las contribuciones son bienvenidas! Si quieres mejorar el juego:

1. Fork el proyecto
2. Crea una rama para tu feature (`git checkout -b feature/AmazingFeature`)
3. Commit tus cambios (`git commit -m 'Add some AmazingFeature'`)
4. Push a la rama (`git push origin feature/AmazingFeature`)
5. Abre un Pull Request

Lee [CONTRIBUTING.md](CONTRIBUTING.md) para más detalles.

---

## 📝 Licencia

Distribuido bajo la licencia MIT. Ver `LICENSE` para más información.

---

## 👨‍💻 Créditos

**Desarrollador Principal**: Axis(https://github.com/axismf)

**Desarrollado como proyecto académico/portafolio - 2024**

### Tecnologías y Herramientas
- Microsoft Visual Studio 2022
- Windows Forms Framework
- GDI+ Graphics Library

---

## 📬 Contacto

- **GitHub**: [@axismf](https://github.com/axismf)
- **LinkedIn**: [Sebastian]((https://www.linkedin.com/in/sebastianmartinf/))

---

## 🙏 Agradecimientos

- Inspirado en clásicos juegos de supervivencia 2D
- Recursos gráficos propios/[Menciona fuentes si usaste assets externos]
- Comunidad de C++ y Windows Forms

---

<div align="center">

⭐ **Si te gustó el proyecto, considera darle una estrella en GitHub** ⭐

[⬆ Volver arriba](#-redefiniendo-el-futuro)

</div>
