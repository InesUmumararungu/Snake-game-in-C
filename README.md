# Snake Game in C — Jeu du Serpent en C

| English | Français |
|---------|----------|
| This is a school assignment where it was required to create a classical snake game using C. | Ceci est un devoir scolaire dans lequel il était demandé de créer un jeu du serpent classique en langage C. |

## Gameplay — Principe du jeu

| English | Français |
|---------|----------|
| The gameplay of the snake game is simple. There are three game objects: | Le principe du jeu du serpent est simple. Il y a trois objets de jeu : |
| **Snake:** The snake automatically moves in a given direction until we change it. It has a head and a tail. | **Serpent :** Le serpent se déplace automatiquement dans une direction donnée jusqu'à ce qu'on la change. Il possède une tête et une queue. |
| **Fruit:** The object that the snake has to eat to grow. | **Fruit :** L'objet que le serpent doit manger pour grandir. |
| **Walls:** They are the boundary of the game area. | **Murs :** Ils constituent la limite de la zone de jeu. |

These objects work according to the following game rules — Ces objets fonctionnent selon les règles suivantes :

| English | Français |
|---------|----------|
| 1. The snake moves at a constant speed in one direction, and we can change its direction using the movement keys. However, the snake can only turn 90° at a time. | 1. Le serpent se déplace à vitesse constante dans une direction, et on peut changer sa direction à l'aide des touches de déplacement. Cependant, le serpent ne peut tourner que de 90° à la fois. |
| 2. The objective is to eat as many fruits as possible, which will make the snake grow in length. | 2. L'objectif est de manger autant de fruits que possible, ce qui fera grandir le serpent en longueur. |
| 3. The game ends if the snake collides with the boundary or its own body. | 3. La partie se termine si le serpent entre en collision avec la limite ou avec son propre corps. |

## Algorithm — Algorithme

![Snake Game Flowchart](images/Snake_algo_flow_chart.png)

| English | Français |
|---------|----------|
| The flowchart above illustrates the algorithm implemented. | L'organigramme ci-dessus illustre l'algorithme implémenté. |

### Functions — Fonctions

| Function | Role (EN) | Rôle (FR) |
|----------|-----------|-----------|
| `setup()` | Initializes the snake, direction, score, and the 3 apples. | Initialise le serpent, la direction, le score et les 3 pommes. |
| `draw()` | Renders the board, snake, apples, and HUD using ncurses. | Affiche le plateau, le serpent, les pommes et l'interface avec ncurses. |
| `input()` | Reads keyboard events (arrow keys, QDZW, speed, pause, save, load, quit). | Lit les événements clavier (flèches, QDZW, vitesse, pause, sauvegarde, chargement, quitter). |
| `logic()` | Moves the snake, checks wall/tail collisions, and handles apple consumption. | Déplace le serpent, vérifie les collisions avec les murs et la queue, et gère la consommation des pommes. |
| `saveGame()` / `loadGame()` | Persist and restore the full game state to `savegame.txt`. | Sauvegarde et restaure l'état complet du jeu dans `savegame.txt`. |
| `generateApples()` | Places 3 new apples at random positions after all 3 are eaten. | Place 3 nouvelles pommes à des positions aléatoires après que les 3 ont été mangées. |

## Features — Fonctionnalités

| English | Français |
|---------|----------|
| Playable with Arrow Keys or QDZW (AZERTY layout) | Jouable avec les flèches ou QDZW (clavier AZERTY) |
| 3 apples at a time — eat all 3 to grow | 3 pommes à la fois — mangez les 3 pour grandir |
| Two speeds (Slow / Fast) | Deux vitesses (Lent / Rapide) |
| Pause with `p` | Pause avec `p` |
| Save and Load game state with `s` and `l` | Sauvegarde et chargement avec `s` et `l` |

## Versions

| File | English | Français |
|------|---------|----------|
| `snake.c` | First version using Windows `conio.h` (does not compile on Linux) | Première version utilisant `conio.h` de Windows (ne compile pas sous Linux) |
| `snake2.c` | Basic ncurses (Linux library) version (single apple, no save/pause) | Version de base avec ncurses (bibliothèque Linux) — une seule pomme, sans sauvegarde ni pause |
| `snake3.c` | Final version with all features | Version finale avec toutes les fonctionnalités |

## Build & Run (Linux / Fedora) — Compilation et exécution

```bash
sudo dnf install ncurses-devel
gcc snake3.c -o snake3 -lncurses
./snake3