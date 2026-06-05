A Peggle-inspired arcade game developed in C++ using SDL2. 
This project demonstrates object-oriented programming, wrapper functionality, collision detection, game state management, audio integration, HUD rendering, and gameplay system design.
```
FIEAPeggleClone/
│
├── Assets/
│   ├── Audio/              # Sound effects (launcher, peg hits, bucket, multiball)
│   ├── Fonts/              # HUD and UI fonts
│   └── Textures/           # Future sprites/UI assets (if applicable)
│
├── Engine/
│   ├── AudioManager.h/.cpp # SDL_mixer wrapper for sound loading & playback
│   ├── Renderer.h/.cpp     # Rendering utilities (circles, lines, colors)
│   ├── Time.h/.cpp         # Delta time and frame timing system
│   ├── Vector2.h/.cpp      # 2D vector math operations
│   └── Window.h/.cpp       # SDL window creation and management
│
├── Game/
│   ├── Ball.h/.cpp         # Ball physics, movement, collision response
│   ├── Bucket.h/.cpp       # Moving free-ball bucket logic
│   ├── HUD.h/.cpp          # HUD rendering and win/loss screens
│   └── Peg.h/.cpp          # Peg behavior, rendering, scoring data
│
├── Docs/
│   ├── README.md           # Project overview and architecture
│   ├── InstallationGuide.pdf # Build and setup instructions
│   └── GameplayDemo.mp4    # Gameplay showcase video
│
├── Main.cpp                # Game loop, scoring, input, state management
│
├── Builds/
│   ├── Debug/              # Debug builds
│   └── Release/            # Final executable builds
│
└── External/
    ├── SDL2/               # SDL2 dependencies
    ├── SDL_ttf/            # Font rendering library
    └── SDL_mixer/          # Audio playback library
```
